from typing import List
import tomllib as toml
import subprocess
import shutil
import os

outDir: str = "out"
binDir: str = "out/bin"
objectDir: str = "out/objects"
srcDir: str = "src"
includePaths: List[str] = []

def execCmd(args: List[str]) -> None:
    subprocess.run(args)
    return

def compileSrc(src: str) -> None:
    execCmd([
        "clang++",
        "-std=c++23",
        *includePaths,
        "-c",
        src,
        "-o",
        f"{objectDir}/{os.path.basename(src)[:-3]}o"
    ])
    return

def main() -> None:
    os.mkdir(outDir)
    os.mkdir(binDir)
    os.mkdir(objectDir)

    execCmd(["clang++", "--version"])

    config: dict
    with open(f"{srcDir}/build.toml", "rb") as f:
        config = toml.load(f)

    for path in config["include_paths"]:
        includePaths.append(f"-I{path}")

    objects: List[str] = []
    for src in config["sources"]:
        compileSrc(f"{srcDir}/{src}.cxx")
        objects.append(f"{objectDir}/{os.path.basename(src)}.o")

    shared: List[str] = []
    for so in config["dynamic_linkage"]:
        shutil.copy(so, binDir)
        shared.append(f"{binDir}/{os.path.basename(so)}")

    execCmd([
        "clang++",
        "-std=c++23",
        "-Wl,-rpath,$ORIGIN",
        *shared,
        *objects,
        "-o",
        f"{binDir}/manor_game",
    ])

    return

if __name__ == "__main__": main()