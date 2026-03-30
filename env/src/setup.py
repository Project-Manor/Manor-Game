import os
import sys
import platform
import requests
import tarfile
from enum import Enum
from typing import List
import tomllib as toml

def wrapSquare(string: str) -> str:
    return "[" + string + "]"

def jsonIndent(string: str, level: int = 1) -> str:
    indents: str = ""
    indentLiteral: str = "  "

    for i in range(0, level):
        indents += indentLiteral

    return indents + string

def attemptEditorFiles() -> None:
    class Editor(Enum):
        NONE = 0
        ZED = 1

    editor: Editor = Editor.NONE
    for arg in sys.argv:
        if arg.startswith("editor="):
            match arg.removeprefix("editor="):
                case "zed": editor = Editor.ZED
                case _: return#attemptEditorFiles()

    match editor:
        case ZED:
            print("Generating Zed Project Files...")
            os.mkdir(".zed")

            with open(".zed/tasks.json", "wb") as file:
                content: str = ""

                for script in os.listdir("run/linux"):
                    if script == ".inc.sh": continue

                    task: str = jsonIndent(f"\"label\": \"{script.removesuffix(".sh").upper()}\",\n", 2)
                    task     += jsonIndent("\"command\": \"sh\",\n", 2)
                    task     += jsonIndent(f"\"args\": [\"run/linux/{script}\"],\n", 2)
                    task     += jsonIndent("\"cwd\": \"$ZED_WORKTREE_ROOT\",\n", 2)
                    content  += "\n" + jsonIndent(f"{f"{{\n{task}"}")
                    content  += jsonIndent("},")

                file.write(wrapSquare(f"{content}\n").encode("utf-8"))

    return#attemptEditorFiles()

def fetchVendors() -> None:
    vendorDir: str = "vnd"
    tmpDir: str = "tmp"
    os.mkdir(vendorDir)
    os.mkdir(tmpDir)

    renamedLibs: List[str] = []

    with open("env/vnd.toml", "rb") as f:
        config: dict = toml.load(f)

        for key, value in config["vendors"].items():
            print(f"Installing {key}...")
            with open(f"{tmpDir}/{key}", 'wb') as file:
                file.write (
                    requests.get(value[platform.system()]).content
                )

            print(f"Extracting {key}...")
            with tarfile.open(f"{tmpDir}/{key}", "r:*") as tar:
                tar.extractall(path=f"{vendorDir}")

            for path in os.listdir(vendorDir):
                if path not in renamedLibs:
                    os.rename(f"{vendorDir}/{path}", f"{vendorDir}/{key}")
                    renamedLibs.append(key)

    return#fetchVendors()

def main() -> None:
    attemptEditorFiles()
    fetchVendors()
    return#main()

if __name__ == "__main__": main()