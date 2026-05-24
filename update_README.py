import glob
import os
import re
from pathlib import Path
from tqdm import tqdm

HANDLE = "rlatjwls3333"

EXT = {
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

def get_problem_url(problem_id):
    return f"https://jungol.co.kr/problem/{problem_id}"

def escape_problem_title(title):
    return title.replace("|", "\\|")

def parse_problem_dir_name(dirname):
    # 예: 1000.문제 제목
    # 예: 1000. A+B
    m = re.match(r"^(\d+)\.(.*)$", dirname)
    if not m:
        return None, None

    problem_id = int(m.group(1))
    title = m.group(2).strip()

    if not title:
        title = f"Problem {problem_id}"

    return problem_id, title

def get_solved_problems():
    problems = {}

    for file in glob.glob("[0-9][0-9]xxx/*/*"):
        path = Path(file)

        if not path.is_file():
            continue

        extension = path.suffix
        if extension == ".md":
            continue

        if extension not in EXT:
            continue

        problem_dir = path.parent.name
        problem_id, title = parse_problem_dir_name(problem_dir)

        if problem_id is None:
            continue

        if problem_id not in problems:
            problems[problem_id] = title

    return sorted(problems.items())

def get_solution_path(problem_id):
    id_for_dir = problem_id

    if problem_id < 10000:
        id_for_dir = f"0{problem_id}"

    directory = f"{str(id_for_dir)[:2]}xxx"

    files = glob.glob(f"{directory}/{problem_id}/*")
    files.sort()

    solution = ""

    for file in files:
        extension = file[file.rfind("."):]

        if extension == ".md":
            continue

        if extension not in EXT:
            continue

        file = file.replace(" ", "%E2%80%85")
        solution += f"[{EXT[extension]}](./{file}) "

    return solution

def get_header(handle):
    header = "# JUNGOL Solutions\n\n"
    header += f"### Handle: `{handle}`\n\n"
    header += "정올 풀이 저장소에 업로드된 문제 목록입니다.\n\n"
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

    with open("README.md", "w", encoding="utf-8") as f:
        f.write(get_header(HANDLE) + get_table(problems))
