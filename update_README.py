import re
import time
from pathlib import Path
from urllib.parse import quote

from bs4 import BeautifulSoup
from curl_cffi import requests
from tqdm import tqdm

HANDLE = "rlatjwls3333"
BASE_URL = "https://jungol.co.kr"

DIFFICULTY_CACHE = {}

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


def parse_problem_dir(dirname):
    # 1000
    # 1000.문제이름
    # 1000. 문제이름
    # 0001
    m = re.match(r"^(\d+)(?:\.(.*))?$", dirname)
    if not m:
        return None

    problem_id_text = m.group(1)
    problem_id = int(problem_id_text)

    title = m.group(2)
    if title is None or title.strip() == "":
        title = f"Problem {problem_id}"
    else:
        title = title.strip()

    return problem_id, problem_id_text, title


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


def extract_difficulty_from_text(text, problem_id, title):
    text = normalize(text)
    title = normalize(title)

    marker = f"#{problem_id}"
    index = text.find(marker)

    if index == -1:
        return None

    segment = text[index:index + 250]

    if title in segment:
        before_title = segment[:segment.find(title)]
    else:
        before_title = segment

    before_title = before_title.replace(marker, " ")
    before_title = before_title.replace("정답", " ")

    numbers = re.findall(r"(?<!\d)([1-9]|[1-2]\d|30)(?!\d)", before_title)

    if numbers:
        return numbers[-1]

    return None


def extract_difficulty_from_html(html, problem_id, title):
    soup = BeautifulSoup(html, "html.parser")

    # 1순위: 화면에 렌더링된 텍스트 기준
    text = soup.get_text(" ", strip=True)
    difficulty = extract_difficulty_from_text(text, problem_id, title)
    if difficulty:
        return difficulty

    # 2순위: img/svg/태그 속성 안의 난이도 숫자
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

            patterns = [
                r"(?:level|tier|difficulty|rank)[/-]?(\d+)",
                r"/(?:level|tier|difficulty|rank)/(\d+)",
            ]

            for pattern in patterns:
                m = re.search(pattern, value, re.I)
                if m:
                    return m.group(1)

    # 3순위: raw HTML 내부 JSON/스크립트 데이터
    patterns = [
        r'"(?:level|tier|difficulty|rank)"\s*:\s*(\d+)',
        r"'(?:level|tier|difficulty|rank)'\s*:\s*(\d+)",
        r"(?:level|tier|difficulty|rank)\D{0,20}([1-9]|[1-2]\d|30)",
    ]

    for pattern in patterns:
        m = re.search(pattern, html, re.I)
        if m:
            return m.group(1)

    return "Unrated"


def get_problem_difficulty(problem_id, title):
    if problem_id in DIFFICULTY_CACHE:
        return DIFFICULTY_CACHE[problem_id]

    try:
        html = request_html(get_problem_url(problem_id))
        difficulty = extract_difficulty_from_html(html, problem_id, title)
    except Exception:
        difficulty = "Unrated"

    DIFFICULTY_CACHE[problem_id] = difficulty
    time.sleep(0.2)

    return difficulty


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

        problem_id, problem_id_text, title = parsed

        if problem_id not in problems:
            problems[problem_id] = {
                "id_text": problem_id_text,
                "title": title,
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


def get_header(handle):
    return "# JUNGOL Solutions\n\n"


def get_table(problems):
    table = "| No. | Title | Difficulty | Solution |\n"
    table += "|:---|:---|:---:|:---:|\n"

    for problem_id in tqdm(sorted(problems)):
        problem = problems[problem_id]

        no = problem["id_text"]
        title = escape_markdown(problem["title"])
        difficulty = get_problem_difficulty(problem_id, problem["title"])
        url = get_problem_url(problem_id)
        solution = make_solution_links(problem["files"])

        table += f"| [{no}]({url}) | {title} | {difficulty} | {solution} |\n"

    return table


if __name__ == "__main__":
    problems = collect_problems()

    with open("README.md", "w", encoding="utf-8") as f:
        f.write(get_header(HANDLE) + get_table(problems))
