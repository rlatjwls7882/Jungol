import re
import time
from pathlib import Path
from urllib.parse import quote

from bs4 import BeautifulSoup
from curl_cffi import requests
from tqdm import tqdm

HANDLE = "rlatjwls3333"
BASE_URL = "https://jungol.co.kr"

INFO_CACHE = {}

EXT = {
    ".ada": "Ada",
    ".a68": "Algol 68",
    ".bas": "FreeBASIC",
    ".c": "C",
    ".cc": "C++",
    ".cpp": "C++",
    ".f": "Fortran",
    ".gs": "Golfscript",
    ".java": "Java",
    ".py": "Python",
    ".txt": "Text",
    ".vb": "Visual Basic",
    ".swift": "Swift",
    ".kt": "Kotlin",
    ".rs": "Rust",
}


def get_problem_url(problem_id):
    return f"{BASE_URL}/problem/{problem_id}"


def escape_markdown(text):
    return text.replace("|", "\\|").strip()


def normalize(text):
    return re.sub(r"\s+", " ", text).strip()


def make_markdown_path(path):
    return quote(path.as_posix(), safe="/._-")


def request_html(url):
    response = requests.get(
        url,
        impersonate="chrome",
        timeout=20,
        headers={
            "Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8",
            "Accept-Language": "ko-KR,ko;q=0.9,en-US;q=0.8,en;q=0.7",
            "Referer": BASE_URL + "/",
        },
    )
    response.raise_for_status()
    return response.text


def parse_problem_dir(dirname):
    # 1000
    # 01000
    # 1000.문제이름 형태도 일단 허용
    m = re.match(r"^(\d+)(?:\..*)?$", dirname)
    if not m:
        return None

    problem_id_text = m.group(1)
    problem_id = int(problem_id_text)

    return problem_id, problem_id_text


def extract_title_from_html(html, problem_id):
    soup = BeautifulSoup(html, "html.parser")

    # 가장 안정적: <title>두 정수 더하기 (A+B) - JUNGOL</title>
    if soup.title and soup.title.string:
        title = normalize(soup.title.string)
        title = re.sub(r"\s*-\s*JUNGOL\s*$", "", title)
        if title:
            return title

    # fallback: 본문 텍스트에서 #번호 뒤쪽을 사용
    text = normalize(soup.get_text(" ", strip=True))
    marker = f"#{problem_id}"
    index = text.find(marker)

    if index != -1:
        segment = text[index:index + 300]

        # #1000 ... 제목 timer 1s memory 4MB 형태에서 제목 추출
        m = re.search(rf"#{problem_id}.*?([가-힣A-Za-z0-9].*?)\s+timer\s+", segment)
        if m:
            title = normalize(m.group(1))
            title = re.sub(r"^(upload|done|how_to_reg|\d+|\s)+", "", title).strip()
            if title:
                return title

    return f"Problem {problem_id}"


def extract_difficulty_from_html(html):
    # 정올 난이도 아이콘 URL/속성에서 숫자 추출
    # 예: /solved/5.svg, /difficulty/5.svg, level-5 등
    patterns = [
        r"/solved/([1-9]|[1-2]\d|30)\.svg",
        r"/level/([1-9]|[1-2]\d|30)\.svg",
        r"/tier/([1-9]|[1-2]\d|30)\.svg",
        r"/difficulty/([1-9]|[1-2]\d|30)\.svg",
        r"(?:level|tier|difficulty|rank)[-_:/ ]([1-9]|[1-2]\d|30)",
        r'"(?:level|tier|difficulty|rank)"\s*:\s*([1-9]|[1-2]\d|30)',
    ]

    for pattern in patterns:
        m = re.search(pattern, html, re.I)
        if m:
            return m.group(1)

    soup = BeautifulSoup(html, "html.parser")

    for tag in soup.find_all(True):
        values = [
            tag.get("alt", ""),
            tag.get("title", ""),
            tag.get("aria-label", ""),
            tag.get("src", ""),
            " ".join(tag.get("class", [])) if isinstance(tag.get("class"), list) else "",
        ]

        for value in values:
            value = str(value)

            for pattern in patterns:
                m = re.search(pattern, value, re.I)
                if m:
                    return m.group(1)

    return "Unrated"


def get_problem_info(problem_id):
    if problem_id in INFO_CACHE:
        return INFO_CACHE[problem_id]

    try:
        html = request_html(get_problem_url(problem_id))
        title = extract_title_from_html(html, problem_id)
        difficulty = extract_difficulty_from_html(html)
    except Exception:
        title = f"Problem {problem_id}"
        difficulty = "Unrated"

    INFO_CACHE[problem_id] = {
        "title": title,
        "difficulty": difficulty,
    }

    time.sleep(0.2)
    return INFO_CACHE[problem_id]


def collect_problems():
    problems = {}

    for file in Path(".").glob("*xxx/*/*"):
        if not file.is_file():
            continue

        extension = file.suffix.lower()

        if extension == ".md":
            continue

        if extension not in EXT:
            continue

        if len(file.parts) < 3:
            continue

        group_dir = file.parts[0]
        problem_dir = file.parts[1]

        if not re.fullmatch(r"\d+xxx", group_dir):
            continue

        parsed = parse_problem_dir(problem_dir)
        if parsed is None:
            continue

        problem_id, problem_id_text = parsed

        if problem_id not in problems:
            problems[problem_id] = {
                "id_text": problem_id_text,
                "files": [],
            }

        problems[problem_id]["files"].append(file)

    return problems


def make_solution_links(files):
    links = []

    for file in sorted(files, key=lambda x: x.as_posix()):
        extension = file.suffix.lower()

        if extension not in EXT:
            continue

        language = EXT[extension]
        path = make_markdown_path(file)

        links.append(f"[{language}](./{path})")

    return " ".join(links)


def get_header():
    return "# JUNGOL Solutions\n\n"


def get_table(problems):
    table = "| No. | Title | Difficulty | Solution |\n"
    table += "|:---|:---|:---:|:---:|\n"

    for problem_id in tqdm(sorted(problems)):
        problem = problems[problem_id]
        info = get_problem_info(problem_id)

        no = problem["id_text"]
        title = escape_markdown(info["title"])
        difficulty = info["difficulty"]
        url = get_problem_url(problem_id)
        solution = make_solution_links(problem["files"])

        table += f"| [{no}]({url}) | {title} | {difficulty} | {solution} |\n"

    return table


if __name__ == "__main__":
    problems = collect_problems()

    with open("README.md", "w", encoding="utf-8") as f:
        f.write(get_header() + get_table(problems))
