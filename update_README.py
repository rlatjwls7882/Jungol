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
ACCOUNT_INFO_CACHE = None

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

TIER = {
    0: "Unrated",
    1: "Bronze 5", 2: "Bronze 4", 3: "Bronze 3", 4: "Bronze 2", 5: "Bronze 1",
    6: "Silver 5", 7: "Silver 4", 8: "Silver 3", 9: "Silver 2", 10: "Silver 1",
    11: "Gold 5", 12: "Gold 4", 13: "Gold 3", 14: "Gold 2", 15: "Gold 1",
    16: "Platinum 5", 17: "Platinum 4", 18: "Platinum 3", 19: "Platinum 2", 20: "Platinum 1",
    21: "Diamond 5", 22: "Diamond 4", 23: "Diamond 3", 24: "Diamond 2", 25: "Diamond 1",
    26: "Ruby 5", 27: "Ruby 4", 28: "Ruby 3", 29: "Ruby 2", 30: "Ruby 1",
}

TIER_TO_LEVEL = {name.lower(): level for level, name in TIER.items()}
TIER_GROUP_BASE = {
    "bronze": 0,
    "silver": 5,
    "gold": 10,
    "platinum": 15,
    "diamond": 20,
    "ruby": 25,
}
ROMAN_TO_DIVISION = {
    "i": 1,
    "ii": 2,
    "iii": 3,
    "iv": 4,
    "v": 5,
}

# JUNGOL 화면의 Material Symbols 텍스트와 문제 속성 배지는 get_text()에 섞인다.
# README에는 실제 문제 제목만 남기기 위해 제목 앞쪽에서만 제거한다.
TITLE_PREFIXES = [
    "auto_awesome",
    "component_exchange",
    "call_split",
    "upload",
    "done",
    "how_to_reg",
    "keep",
    "bookmark",
    "star",
    "check",
    "code",
    "language",
    "translate",
    "help",
    "info",
    "스페셜 저지",
    "스페셜저지",
    "서브태스크",
    "인터랙티브",
]

MATERIAL_ICON_CLASSES = {
    "material-icons",
    "material-icons-outlined",
    "material-icons-round",
    "material-icons-sharp",
    "material-symbols-outlined",
    "material-symbols-rounded",
    "material-symbols-sharp",
}

LEVEL_PATTERN = r"(?:[1-9]|[1-2]\d|30)"
DIVISION_PATTERN = r"(?:[1-5]|I|II|III|IV|V)"
TIER_NAME_PATTERN = rf"(?:Bronze|Silver|Gold|Platinum|Diamond|Ruby)\s+{DIVISION_PATTERN}"


def normalize(text):
    return re.sub(r"\s+", " ", str(text)).strip()


def escape_markdown(text):
    return normalize(text).replace("|", "\\|")


def get_problem_tier(level):
    try:
        level = int(level)
    except Exception:
        level = 0

    if level not in TIER:
        level = 0

    return f'<img alt="{TIER[level]}" src="assets/{level}.svg" height="24">'


def request_html(url):
    last_error = None

    for _ in range(3):
        try:
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
        except Exception as e:
            last_error = e
            time.sleep(1)

    raise last_error


def get_problem_url(problem_id):
    return f"{BASE_URL}/problem/{problem_id}"


def make_markdown_path(path):
    return quote(path.as_posix(), safe="/._-")


def format_problem_no(problem_id):
    return f"{problem_id:05d}"


def remove_noise_tags(soup):
    for tag in soup(["script", "style", "noscript", "svg"]):
        tag.decompose()

    for tag in soup.find_all(True):
        classes = set(tag.get("class", []))
        if classes & MATERIAL_ICON_CLASSES:
            tag.decompose()


def tier_name_to_level(tier_name):
    m = re.fullmatch(
        r"(Bronze|Silver|Gold|Platinum|Diamond|Ruby)\s+([1-5]|I|II|III|IV|V)",
        normalize(tier_name),
        re.I,
    )

    if not m:
        return ""

    group = m.group(1).lower()
    division = m.group(2).lower()

    if division in ROMAN_TO_DIVISION:
        division = ROMAN_TO_DIVISION[division]
    else:
        division = int(division)

    return str(TIER_GROUP_BASE[group] + (6 - division))


def remove_trailing_tier(title):
    while True:
        new_title = re.sub(
            rf"\s*(?:[·•|/\\-]\s*)?{TIER_NAME_PATTERN}\s*$",
            "",
            title,
            flags=re.I,
        ).strip()

        if new_title == title:
            return title

        title = new_title


def remove_problem_prefix(title, problem_id):
    if problem_id is None:
        return title

    problem_id = int(problem_id)
    no = format_problem_no(problem_id)
    patterns = [
        rf"^#?{problem_id}\s*(?:정답)?\s*(?:{LEVEL_PATTERN}|\?)?\s+",
        rf"^#?{no}\s*(?:정답)?\s*(?:{LEVEL_PATTERN}|\?)?\s+",
    ]

    for pattern in patterns:
        title = re.sub(pattern, "", title).strip()

    return title


def clean_title(title, problem_id=None):
    title = normalize(title)
    title = re.sub(r"\s*-\s*JUNGOL\s*$", "", title, flags=re.I).strip()
    title = re.sub(r"\s*\|\s*JUNGOL\s*$", "", title, flags=re.I).strip()
    title = re.sub(r"\s+(?:timer|시간)\s+\S+.*$", "", title, flags=re.I).strip()
    title = re.sub(r"\s+(?:memory|메모리)\s+\S+.*$", "", title, flags=re.I).strip()
    title = re.sub(r"\s+(?:문제|입력|출력|제출|채점)\s+.*$", "", title).strip()

    # '#5539 정답 16 제목'처럼 실제 문제 번호가 앞에 붙은 경우만 제거한다.
    # '2048'처럼 숫자로만 된 실제 제목까지 지우지 않도록 임의의 앞자리 숫자는 제거하지 않는다.
    title = remove_problem_prefix(title, problem_id)

    changed = True
    while changed:
        old_title = title
        title = remove_trailing_tier(title)

        for prefix in TITLE_PREFIXES:
            pattern = rf"^{re.escape(prefix)}(?:\s+|$)"
            title = re.sub(pattern, "", title, flags=re.I).strip()

        title = re.sub(r"^[-:·•|/]+\s*", "", title).strip()
        changed = title != old_title

    if title in ("", "문제", "JUNGOL"):
        return ""

    if problem_id is not None and re.fullmatch(r"#?\d{3,6}", title):
        number = int(title.lstrip("#"))

        if number == int(problem_id):
            return ""

    return title


def find_solved_block(html):
    start = html.find("해결한 문제")

    if start == -1:
        return html

    end_candidates = [
        html.find("틀린 문제", start),
        html.find("티어 관련 정보", start),
        html.find("소속 인증", start),
    ]
    end_candidates = [x for x in end_candidates if x != -1]
    end = min(end_candidates) if end_candidates else len(html)

    return html[start:end]


def extract_level_from_text(text):
    for m in re.finditer(TIER_NAME_PATTERN, normalize(text), re.I):
        level = tier_name_to_level(m.group(0))

        if level:
            return level

    return ""


def extract_level_from_html(html):
    patterns = [
        r"assets/([0-9]|[1-2]\d|30)\.svg",
        r"/solved/([0-9]|[1-2]\d|30)\.svg",
        r"/level/([0-9]|[1-2]\d|30)\.svg",
        r"/tier/([0-9]|[1-2]\d|30)\.svg",
        r"/difficulty/([0-9]|[1-2]\d|30)\.svg",
        r"(?:level|tier|difficulty|rank)[-_:/ ]([0-9]|[1-2]\d|30)",
        r'"(?:level|tier|difficulty|rank)"\s*:\s*([0-9]|[1-2]\d|30)',
    ]

    for pattern in patterns:
        m = re.search(pattern, html, re.I)
        if m:
            return m.group(1)

    soup = BeautifulSoup(html, "html.parser")

    for tag in soup.find_all(True):
        for attr in ("alt", "title", "aria-label"):
            value = normalize(tag.get(attr, ""))
            level = TIER_TO_LEVEL.get(value.lower())

            if level is not None:
                return str(level)

            level = tier_name_to_level(value)

            if level:
                return level

    level = extract_level_from_text(soup.get_text(" ", strip=True))

    if level:
        return level

    return ""


def extract_title_from_container(container, problem_id):
    html = str(container)
    soup = BeautifulSoup(html, "html.parser")
    remove_noise_tags(soup)

    text = normalize(soup.get_text(" ", strip=True))
    no = format_problem_no(problem_id)

    patterns = [
        rf"(?:#?{problem_id}|#?{no})\s*(?:정답)?\s*(?:{LEVEL_PATTERN}|\?)?\s+(.+)",
        rf"(?:정답)?\s*(?:{LEVEL_PATTERN}|\?)?\s+(.+)",
    ]

    for pattern in patterns:
        m = re.search(pattern, text, re.I)
        if not m:
            continue

        title = clean_title(m.group(1), problem_id)

        if title:
            return title

    return clean_title(text, problem_id)


def get_solved_problem_infos():
    global ACCOUNT_INFO_CACHE

    if ACCOUNT_INFO_CACHE is not None:
        return ACCOUNT_INFO_CACHE

    html = request_html(ACCOUNT_URL)
    block = find_solved_block(html)
    soup = BeautifulSoup(block, "html.parser")
    remove_noise_tags(soup)

    infos = {}

    for a in soup.find_all("a", href=re.compile(r"/problem/(\d+)")):
        href = a.get("href", "")
        m = re.search(r"/problem/(\d+)", href)

        if not m:
            continue

        problem_id = int(m.group(1))
        title = ""
        difficulty = ""

        # 표나 카드형 목록 모두 처리하기 위해 가까운 부모부터 검사한다.
        parent = a
        for _ in range(6):
            if parent is None:
                break

            candidate_title = extract_title_from_container(parent, problem_id)
            candidate_difficulty = extract_level_from_html(str(parent))

            if candidate_title and len(candidate_title) <= 120:
                title = candidate_title

            if candidate_difficulty:
                difficulty = candidate_difficulty

            if title:
                break

            parent = parent.parent

        if problem_id not in infos:
            infos[problem_id] = {"title": "", "difficulty": ""}

        if title:
            infos[problem_id]["title"] = title

        if difficulty:
            infos[problem_id]["difficulty"] = difficulty

    if not infos:
        text = normalize(BeautifulSoup(block, "html.parser").get_text(" ", strip=True))

        for m in re.finditer(r"(?<!\d)(\d{3,6})(?!\d)", text):
            problem_id = int(m.group(1))
            infos.setdefault(problem_id, {"title": "", "difficulty": ""})

    ACCOUNT_INFO_CACHE = infos
    return ACCOUNT_INFO_CACHE


def get_solved_problem_ids():
    return sorted(get_solved_problem_infos())


def extract_title_from_html(html, problem_id):
    soup = BeautifulSoup(html, "html.parser")
    remove_noise_tags(soup)

    # 구조화된 제목을 먼저 본다. get_text() 전체를 먼저 보면 배지명이 제목 앞에 섞일 수 있다.
    selectors = [
        ('meta[property="og:title"]', "content"),
        ('meta[name="title"]', "content"),
        ("h1", None),
        ("h2", None),
    ]

    for selector, attr in selectors:
        for tag in soup.select(selector):
            raw = tag.get(attr, "") if attr else tag.get_text(" ", strip=True)
            title = clean_title(raw, problem_id)

            if title:
                return title

    if soup.title and soup.title.string:
        title = clean_title(soup.title.string, problem_id)

        if title:
            return title

    text = normalize(soup.get_text(" ", strip=True))
    marker = f"#{problem_id}"
    index = text.find(marker)

    if index == -1:
        marker = str(problem_id)
        index = text.find(marker)

    if index != -1:
        segment = text[index:index + 1000]

        patterns = [
            rf"#?{problem_id}\s*(?:정답)?\s*(?:{LEVEL_PATTERN}|\?)?\s*(.*?)\s+(?:timer|시간|memory|메모리)\s+",
            rf"#?{problem_id}\s*(?:정답)?\s*(?:{LEVEL_PATTERN}|\?)?\s*(.*?)\s+문제\s+",
            rf"#?{problem_id}\s*(?:정답)?\s*(?:{LEVEL_PATTERN}|\?)?\s*(.*)",
        ]

        for pattern in patterns:
            m = re.search(pattern, segment, re.I)

            if m:
                title = clean_title(m.group(1), problem_id)

                if title:
                    return title

    return ""


def extract_difficulty_from_html(html, problem_id, title):
    text = normalize(BeautifulSoup(html, "html.parser").get_text(" ", strip=True))
    marker = f"#{problem_id}"
    index = text.find(marker)

    if index == -1:
        marker = str(problem_id)
        index = text.find(marker)

    if index != -1:
        segment = text[index:index + 500]

        if title:
            title_index = segment.find(title)

            if title_index != -1:
                before_title = segment[:title_index]
                before_title = before_title.replace(f"#{problem_id}", " ")
                before_title = before_title.replace(str(problem_id), " ")
                before_title = before_title.replace("정답", " ")

                numbers = re.findall(rf"(?<!\d)({LEVEL_PATTERN})(?!\d)", before_title)

                if numbers:
                    return numbers[-1]

        m = re.search(rf"#?{problem_id}\s*(?:정답)?\s*({LEVEL_PATTERN})\s+", segment)
        if m:
            return m.group(1)

    level = extract_level_from_html(html)

    if level:
        return level

    return extract_level_from_text(text)


def get_problem_info(problem_id):
    if problem_id in INFO_CACHE:
        return INFO_CACHE[problem_id]

    account_info = get_solved_problem_infos().get(problem_id, {})
    title = account_info.get("title", "")
    difficulty = account_info.get("difficulty", "")

    try:
        html = request_html(get_problem_url(problem_id))
        page_title = extract_title_from_html(html, problem_id)
        page_difficulty = extract_difficulty_from_html(html, problem_id, page_title or title)

        if page_title:
            title = page_title

        if page_difficulty:
            difficulty = page_difficulty
    except Exception:
        pass

    title = clean_title(title, problem_id)

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