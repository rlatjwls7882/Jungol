import glob
import time
from tqdm import tqdm
from curl_cffi import requests

HANDLE = "rlatjwls3333"
API_BASE_URL = "https://api.jungol.co.kr"
WEB_BASE_URL = "https://jungol.co.kr"

PAGE_LIMIT = 20
TITLE_CACHE = {}

def request_json(path, params=None):
    url = API_BASE_URL + path
    response = requests.get(
        url,
        params=params or {},
        impersonate="chrome",
        timeout=20,
        headers={
            "Accept": "application/json",
            "Accept-Language": "ko-KR,ko;q=0.9,en-US;q=0.8,en;q=0.7",
            "Referer": "https://jungol.co.kr/",
            "Origin": "https://jungol.co.kr",
        },
    )
    response.raise_for_status()

    try:
        return response.json()
    except Exception:
        raise RuntimeError(f"JSON 응답이 아닙니다: {response.text[:300]}")

def unwrap_submission_response(payload):
    """
    예상 형태:
    {
        "data": {
            "data": [...],
            "cursor": "..."
        }
    }
    """
    root = payload.get("data", payload) if isinstance(payload, dict) else payload

    if isinstance(root, list):
        return root, None

    if not isinstance(root, dict):
        return [], None

    items = []
    for key in ("data", "items", "submissions", "results"):
        if isinstance(root.get(key), list):
            items = root[key]
            break

    cursor = (
        root.get("cursor")
        or root.get("nextCursor")
        or root.get("next_cursor")
        or root.get("next")
    )

    return items, cursor

def extract_problem_id(submission):
    for key in ("problemId", "problem_id", "pid"):
        if key in submission and submission[key] is not None:
            return int(submission[key])

    problem = submission.get("problem")
    if isinstance(problem, dict):
        for key in ("problemId", "id", "problem_id"):
            if key in problem and problem[key] is not None:
                return int(problem[key])

    return None

def is_accepted(submission):
    values = [
        submission.get("m_reason"),
        submission.get("reason"),
        submission.get("result"),
        submission.get("status"),
    ]

    for value in values:
        text = str(value).upper()
        if text in ("AC", "ACCEPTED"):
            return True
        if "정답" in str(value):
            return True

    # 정올은 점수형 문제도 있을 수 있으므로 보조 조건으로 둠
    try:
        if int(submission.get("m_score", 0)) == 100:
            return True
    except Exception:
        pass

    return False

def find_title(obj):
    if isinstance(obj, dict):
        for key in ("titleKo", "title_ko", "title", "name"):
            value = obj.get(key)

            if isinstance(value, str) and value.strip():
                return value.strip()

            if isinstance(value, dict):
                for lang_key in ("ko", "kr", "ko_KR", "ko-KR"):
                    text = value.get(lang_key)
                    if isinstance(text, str) and text.strip():
                        return text.strip()

        for value in obj.values():
            title = find_title(value)
            if title:
                return title

    if isinstance(obj, list):
        for value in obj:
            title = find_title(value)
            if title:
                return title

    return None

def fetch_problem_title(problem_id):
    if problem_id in TITLE_CACHE:
        return TITLE_CACHE[problem_id]

    try:
        payload = request_json(f"/problem/{problem_id}")
        title = find_title(payload)
    except Exception:
        title = None

    if not title:
        title = f"Problem {problem_id}"

    TITLE_CACHE[problem_id] = title
    time.sleep(0.15)
    return title

def get_solved_problems(max_pages=1000):
    problems = {}
    cursor = None
    seen_cursors = set()

    for _ in tqdm(range(max_pages)):
        params = {
            "account": HANDLE,
            "limit": PAGE_LIMIT,
        }

        if cursor:
            params["cursor"] = cursor

        payload = request_json("/submission", params=params)
        submissions, next_cursor = unwrap_submission_response(payload)

        if not submissions:
            break

        for submission in submissions:
            if not is_accepted(submission):
                continue

            problem_id = extract_problem_id(submission)
            if problem_id is None:
                continue

            if problem_id not in problems:
                problems[problem_id] = fetch_problem_title(problem_id)

        if not next_cursor:
            break

        if next_cursor in seen_cursors:
            break

        seen_cursors.add(next_cursor)
        cursor = next_cursor

        time.sleep(0.3)

    return sorted(problems.items())

def get_problem_url(problem_id):
    return f"https://jungol.co.kr/problem/{problem_id}"

def escape_problem_title(title):
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
        title = escape_problem_title(title)
        path = get_solution_path(problem_id)

        table += f"| [{problem_id}]({url}) | {title} | {path} |\n"

    return table

if __name__ == "__main__":
    problems = get_solved_problems()

    if not problems:
        raise RuntimeError(
            "정답 문제를 하나도 가져오지 못했습니다. "
            "api.jungol.co.kr/submission 응답 구조 또는 account 파라미터를 확인해야 합니다."
        )

    with open("README.md", "w", encoding="utf-8") as f:
        f.write(get_header(HANDLE) + get_table(problems))
