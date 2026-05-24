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

def get_problem_tier(level):
    tier = {
        0: "Unrated",
        1: "Bronze 5", 2: "Bronze 4", 3: "Bronze 3", 4: "Bronze 2", 5: "Bronze 1",
        6: "Silver 5", 7: "Silver 4", 8: "Silver 3", 9: "Silver 2", 10: "Silver 1",
        11: "Gold 5", 12: "Gold 4", 13: "Gold 3", 14: "Gold 2", 15: "Gold 1",
        16: "Platinum 5", 17: "Platinum 4", 18: "Platinum 3", 19: "Platinum 2", 20: "Platinum 1",
        21: "Diamond 5", 22: "Diamond 4", 23: "Diamond 3", 24: "Diamond 2", 25: "Diamond 1",
        26: "Ruby 5", 27: "Ruby 4", 28: "Ruby 3", 29: "Ruby 2", 30: "Ruby 1",
    }

    try:
        level = int(level)
    except Exception:
        level = int(0)

    if level not in tier:
        level = int(0)

    return f'<img alt="{tier[level]}" src="assets/{level}.svg" height="24">'

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


def format_problem_no(problem_id):
    return f"{problem_id:05d}"


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

    for m in re.finditer(r"/problem/(\d+)", block):
        problem_ids.add(int(m.group(1)))

    if not problem_ids:
        soup = BeautifulSoup(block, "html.parser")
        text = normalize(soup.get_text(" ", strip=True))

        for m in re.finditer(r"(?<!\d)(\d{3,6})(?!\d)", text):
            problem_ids.add(int(m.group(1)))

    return sorted(problem_ids)


def extract_title_from_html(html, problem_id):
    soup = BeautifulSoup(html, "html.parser")

    # 1순위: 브라우저 title 태그에서 가져오기
    if soup.title and soup.title.string:
        title = normalize(soup.title.string)
        title = re.sub(r"\s*-\s*JUNGOL\s*$", "", title).strip()

        if title and title.lower() != "jungol":
            return title

    # 2순위: 본문 텍스트에서 가져오기
    text = normalize(soup.get_text(" ", strip=True))

    marker = f"#{problem_id}"
    index = text.find(marker)

    if index != -1:
        segment = text[index:index + 500]

        # #1000 정답 5 keep 두 정수 더하기 (A+B) timer 1s memory 4MB
        m = re.search(
            rf"#{problem_id}\s*(?:정답)?\s*(?:[1-9]|[1-2]\d|30)?\s*(.*?)\s+(?:timer|시간|메모리|memory)\s+",
            segment,
            re.I,
        )

        if m:
            title = normalize(m.group(1))

            # Material Icon 텍스트 제거
            title = re.sub(
                r"^(upload|done|how_to_reg|keep|bookmark|star|check|timer|memory|\d+|\s)+",
                "",
                title,
                flags=re.I,
            ).strip()

            if title:
                return title

    return ""
    

def extract_difficulty_from_html(html, problem_id, title):
    soup = BeautifulSoup(html, "html.parser")
    text = normalize(soup.get_text(" ", strip=True))

    marker = f"#{problem_id}"
    index = text.find(marker)

    if index != -1:
        segment = text[index:index + 500]

        if title:
            title_index = segment.find(title)

            if title_index != -1:
                before_title = segment[:title_index]
                before_title = before_title.replace(marker, " ")
                before_title = before_title.replace("정답", " ")

                numbers = re.findall(r"(?<!\d)([1-9]|[1-2]\d|30)(?!\d)", before_title)

                if numbers:
                    return numbers[-1]

        # title 추출 실패 시 보조 파싱
        m = re.search(rf"#{problem_id}\s*(?:정답)?\s*([1-9]|[1-2]\d|30)\s+", segment)
        if m:
            return m.group(1)

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

    return ""


def get_problem_info(problem_id):
    if problem_id in INFO_CACHE:
        return INFO_CACHE[problem_id]

    title = ""
    difficulty = ""

    try:
        html = request_html(get_problem_url(problem_id))
        title = extract_title_from_html(html, problem_id)
        difficulty = extract_difficulty_from_html(html, problem_id, title)
    except Exception:
        title = ""
        difficulty = ""

    INFO_CACHE[problem_id] = {
        "title": title,
        "difficulty": difficulty,
    }

    time.sleep(0.2)
    return INFO_CACHE[problem_id]


def collect_solution_files():
    result = {}

    for file in Path(".").glob("*xxx/*"):
        if not file.is_file():
            continue

        extension = file.suffix.lower()

        if extension == ".md":
            continue

        if extension not in EXT:
            continue

        if len(file.parts) < 2:
            continue

        group_dir = file.parts[0]
        filename = file.name

        if not re.fullmatch(r"\d+xxx", group_dir):
            continue

        # 1000.cpp, 1001.py, 12260.java
        m = re.match(r"^(\d+)\.[^.]+$", filename)
        if not m:
            continue

        problem_id = int(m.group(1))
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

        no = format_problem_no(problem_id)
        title = escape_markdown(info["title"])
        difficulty = get_problem_tier(info["difficulty"])
        url = get_problem_url(problem_id)
        solution = make_solution_links(solution_files.get(problem_id, []))

        table += f"| [{no}]({url}) | {title} | {difficulty} | {solution} |\n"

    return table


if __name__ == "__main__":
    solved_problem_ids = get_solved_problem_ids()
    solution_files = collect_solution_files()

    with open("README.md", "w", encoding="utf-8") as f:
        f.write(get_header() + get_table(solved_problem_ids, solution_files))
