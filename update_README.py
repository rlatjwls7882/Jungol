import glob
import re
import time
from tqdm import tqdm
from bs4 import BeautifulSoup
from curl_cffi import requests

HANDLE = "rlatjwls3333"
BASE_URL = "https://jungol.co.kr"

def request_html(path, params=None):
    url = BASE_URL + path
    response = requests.get(
        url,
        params=params or {},
        impersonate="chrome",
        timeout=20,
        headers={
            "Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8",
            "Accept-Language": "ko-KR,ko;q=0.9,en-US;q=0.8,en;q=0.7",
            "Referer": "https://jungol.co.kr/",
        },
    )
    response.raise_for_status()
    return response.text

def normalize(text):
    return re.sub(r"\s+", " ", text).strip()

def parse_submission_page(html):
    soup = BeautifulSoup(html, "html.parser")
    result = []

    # 문제 링크 주변 블록에서 제출자, 결과를 같이 확인
    for a in soup.find_all("a", href=re.compile(r"/problem/\d+")):
        href = a.get("href", "")
        m = re.search(r"/problem/(\d+)", href)
        if not m:
            continue

        problem_id = int(m.group(1))
        title = normalize(a.get_text(" ", strip=True))
        title = re.sub(r"\s*#\d+\s*$", "", title).strip()

        block = a
        text = ""
        for _ in range(8):
            if block.parent is None:
                break
            block = block.parent
            text = normalize(block.get_text(" ", strip=True))

            if HANDLE in text and ("정답" in text or "Accepted" in text):
                break

        if HANDLE not in text:
            continue
        if "정답" not in text and "Accepted" not in text:
            continue

        result.append((problem_id, title))

    return result

def get_solved_problems(max_pages=1000):
    problems = {}
    empty_streak = 0

    for page in tqdm(range(1, max_pages + 1)):
        html = request_html("/submission", params={
            "account": HANDLE,
            "page": page,
        })

        items = parse_submission_page(html)

        new_count = 0
        for problem_id, title in items:
            if problem_id not in problems:
                problems[problem_id] = title
                new_count += 1

        if len(items) == 0:
            empty_streak += 1
        else:
            empty_streak = 0

        if empty_streak >= 3:
            break

        time.sleep(0.4)

    return sorted(problems.items())

def get_problem_url(problem_id):
    return f"https://jungol.co.kr/problem/{problem_id}"

def get_problem_title(title):
    title = title.replace("|", "\\|")
    return title

def get_solution_path(problem_id):
    tmp_id = problem_id

    id_for_dir = problem_id
    if problem_id < 10000:
        id_for_dir = f"0{problem_id}"

    directory = f"{str(id_for_dir)[:2]}xxx"

    ext = {
        ".ada"   : "Ada",
        ".a68"   : "Algol 68",
        ".bas"   : "FreeBASIC",
        ".c"     : "C",
        ".cc"    : "C++",
        ".cpp"   : "C++",
        ".f"     : "Fortran",
        ".gs"    : "Golfscript",
        ".java"  : "Java",
        ".py"    : "Python",
        ".txt"   : "Text",
        ".vb"    : "Visual Basic",
        ".swift" : "Swift"
    }

    files = glob.glob(f"{directory}/{tmp_id}.*/*")
    files.sort()

    solution = ""
    for file in files:
        extension = file[file.rfind("."):]

        if extension == ".md":
            continue

        if extension not in ext:
            continue

        file = file.replace(" ", "%E2%80%85")
        solution += f"[{ext[extension]}](./{file}) "

    return solution

def get_header(handle):
    header = "# JUNGOL Solutions\n\n"
    header += f"### Handle: `{handle}`\n\n"
    header += "정올에서 정답을 받은 문제 목록입니다.\n\n"
    return header

def get_table(problems):
    table = "| No. | Title | Solution |\n"
    table += "|:---|:---|:---:|\n"

    for problem_id, title in tqdm(problems):
        url = get_problem_url(problem_id)
        title = get_problem_title(title)
        path = get_solution_path(problem_id)

        table += f"| [{problem_id}]({url}) | {title} | {path} |\n"

    return table

if __name__ == "__main__":
    problems = get_solved_problems()

    with open("README.md", "w", encoding="utf-8") as f:
        f.write(get_header(HANDLE) + get_table(problems))
