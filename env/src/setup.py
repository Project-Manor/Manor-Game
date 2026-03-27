import os
import platform
import requests
import tarfile
from typing import List
import tomllib as toml

if __name__ == "__main__":
    vendorDir: str = "vnd"
    tmpDir: str = "tmp"
    os.mkdir(vendorDir)
    os.mkdir(tmpDir)

    renamedLibs: List[str] = []

    with open("env/vnd.toml", "rb") as f:
        config: dict = toml.load(f)
    
        for key, value in config["vendors"].items():
            print(f"Installing {key}")
            with open(f"{tmpDir}/{key}", 'wb') as file:
                file.write (
                    requests.get(value[platform.system()]).content
                )

            print(f"Extracting {key}")
            with tarfile.open(f"{tmpDir}/{key}", "r:*") as tar:
                tar.extractall(path=f"{vendorDir}")

            for path in os.listdir(vendorDir):
                if path not in renamedLibs:
                    os.rename(f"{vendorDir}/{path}", f"{vendorDir}/{key}")
                    renamedLibs.append(key)