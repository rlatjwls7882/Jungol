import re
import time
from pathlib import Path
from urllib.parse import quote

from bs4 import BeautifulSoup
from curl_cffi import requests
from tqdm import tqdm

HANDLE = "rlatjwls3333"
BASE_URL = "https://jungol.co.kr"
ACCOUNT_URL = f"{BASE_URL}/account/@{HANDLE}"

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


def normalize(text):
    return re.sub(r"\s+", " ", text).strip()


def escape_markdown(text):
    return text.replace("|", "\\|").strip()


def get_problem_url(problem_id):
    return f"{BASE_URL}/problem/{problem_id}"


def make_markdown_path(path):
    return quote(path.as_posix(), safe="/._-")


def get_group_dir(problem_id):
    # 1000 -> 01xxx
    # 12260 -> 12xxx
    return f"{problem_id // 1000:02d}xxx"


def get_solved_problem_ids():
    html = request_html(ACCOUNT_URL)

    start = html.find("해결한 문제")
    if start == -1:
        raise RuntimeError("계정 페이지에서 '해결한 문제' 영역을 찾지 못했습니다.")

    end_candidates = [
        html.find("틀린 문제", start),
        html.find("티어 관련 정보", start),
        html.find("소속 인증", start),
    ]

    end_candidates = [x for x in end_candidates if x != -1]
    end = min(end_candidates) if end_candidates else len(html)

    block = html[start:end]

    problem_ids = set()

    # 1순위: 링크에서 추출
    for m in re.finditer(r"/problem/(\d+)", block):
        problem_ids.add(int(m.group(1)))

    # 2순위: 텍스트에서 추출
    if not problem_ids:
        soup = BeautifulSoup(block, "html.parser")
        text = normalize(soup.get_text(" ", strip=True))

        # 난이도 숫자 1~30을 피하려고 3자리 이상만 문제 번호로 취급
        for m in re.finditer(r"(?<!\d)(\d{3,6})(?!\d)", text):
            problem_ids.add(int(m.group(1)))

    return sorted(problem_ids)


def extract_title_from_html(html, problem_id):
    soup = BeautifulSoup(html, "html.parser")

    if soup.title and soup.title.string:
        title = normalize(soup.title.string)
        title = re.sub(r"\s*-\s*JUNGOL\s*$", "", title)

        if title:
            return title

    text = normalize(soup.get_text(" ", strip=True))
    marker = f"#{problem_id}"
    index = text.find(marker)

    if index != -1:
        segment = text[index:index + 300]
        m = re.search(rf"#{problem_id}.*?([가-힣A-Za-z0-9].*?)\s+timer\s+", segment)

        if m:
            title = normalize(m.group(1))
            title = re.sub(r"^(upload|done|how_to_reg|\d+|\s)+", "", title).strip()

            if title:
                return title

    return f"Problem {problem_id}"


def extract_difficulty_from_html(html):
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
    text = normalize(soup.get_text(" ", strip=True))

    # 문제 상단: #1000 ... 5 두 정수 더하기 ...
    m = re.search(r"#\d+.*?(?<!\d)([1-9]|[1-2]\d|30)(?!\d)", text)
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


def collect_solution_files():
    result = {}

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

        if not re.fullmatch(r"\d+", problem_dir):
            continue

        problem_id = int(problem_dir)
        result.setdefault(problem_id, []).append(file)

    return result


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


def get_table(problem_ids, solution_files):
    table = "| No. | Title | Difficulty | Solution |\n"
    table += "|:---|:---|:---:|:---:|\n"

    for problem_id in tqdm(problem_ids):
        info = get_problem_info(problem_id)

        title = escape_markdown(info["title"])
        difficulty = info["difficulty"]
        url = get_problem_url(problem_id)
        solution = make_solution_links(solution_files.get(problem_id, []))

        table += f"| [{problem_id}]({url}) | {title} | {difficulty} | {solution} |\n"

    return table


if __name__ == "__main__":
    solved_problem_ids = get_solved_problem_ids()
    solution_files = collect_solution_files()

    with open("README.md", "w", encoding="utf-8") as f:
        f.write(get_header() + get_table(solved_problem_ids, solution_files))
