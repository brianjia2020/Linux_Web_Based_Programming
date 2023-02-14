#!/usr/local/bin/python3

import os
from os.path import isdir,isfile,join
import subprocess
import shutil

def run():
    cwd = os.getcwd()
    if isdir(join(cwd, "build")):
        shutil.rmtree(join(cwd, "build"))
        os.mkdir(join(cwd, "build"))
    else:
        os.mkdir(join(cwd, "build"))
    os.chdir(join(cwd, "build"))
    subprocess.run(["cmake", ".."])
    # subprocess.run(["chmod", "-R", "755", join(cwd, "build", "CMakeFiles", "add.dir", "src")])

if __name__ == "__main__":
    run()