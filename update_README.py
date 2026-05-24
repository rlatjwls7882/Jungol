import re
from pathlib import Path
from urllib.parse import quote
from tqdm import tqdm

HANDLE = "rlatjwls3333"

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
    return f"https://jungol.co.kr/problem/{problem_id}"

def escape_markdown(text):
    return text.replace("|", "\\|").strip()

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
    header = "# JUNGOL Solutions\n\n"
    header += f"### Handle: `{handle}`\n\n"
    header += "정올 풀이 저장소에 업로드된 문제 목록입니다.\n\n"
    return header

def get_table(problems):
    table = "| No. | Title | Solution |\n"
    table += "|:---|:---|:---:|\n"

    for problem_id in tqdm(sorted(problems)):
        problem = problems[problem_id]

        no = problem["id_text"]
        title = escape_markdown(problem["title"])
        url = get_problem_url(problem_id)
        solution = make_solution_links(problem["files"])

        table += f"| [{no}]({url}) | {title} | {solution} |\n"

    return table

if __name__ == "__main__":
    problems = collect_problems()

    with open("README.md", "w", encoding="utf-8") as f:
        f.write(get_header(HANDLE) + get_table(problems))
