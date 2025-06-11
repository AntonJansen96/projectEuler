#!/usr/bin/env python3

import sys, os, subprocess

# === CONFIGURATION ===
project_name = sys.argv[1]
compiler = "/opt/homebrew/bin/gcc-15"
cxx_compiler = "/opt/homebrew/bin/g++-15"
compiler_flags = "-Wall -std=c++23 -O3 -fopenmp -march=native -funroll-loops -ffast-math -flto -Wl,-w"
libraries = "euler fileio fractions math stopwatch utility"
# =====================

main_cpp = f"""#include "cpplib/euler.h"
#include "cpplib/fileio.h"
#include "cpplib/fractions.h"
#include "cpplib/math.h"
#include "cpplib/probability.h"
#include "cpplib/pythonlike.h"
#include "cpplib/stopwatch.h"
#include "cpplib/utility.h"

using namespace pythonlike;

int main()
{{
    stopwatch::Stopwatch timer;
    timer.start();
    print("Hello world from project {project_name}!");
    timer.time();
}}
"""

# =====================

run_sh = f"""#!/bin/bash

set -e
if [ ! -f "build/CMakeCache.txt" ]; then cmake -B build; fi
make -j -C build
./build/{project_name}
"""

# =====================

cmake_lists = f"""cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER "{compiler}")
set(CMAKE_CXX_COMPILER "{cxx_compiler}")
set(CMAKE_CXX_FLAGS "{compiler_flags}")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project({project_name})

include_directories(/usr/local/include)
link_directories(/usr/local/lib)
add_executable({project_name} {project_name}.cpp)
target_link_libraries({project_name} {libraries})
"""

# =====================

# Create directory.
os.mkdir(project_name)

# Create C++ files.
with open(f"{project_name}/{project_name}.cpp", "w") as f:
    f.write(main_cpp)

with open(f"{project_name}/run.sh", "w") as f:
    f.write(run_sh)

with open(f"{project_name}/CMakeLists.txt", "w") as f:
    f.write(cmake_lists)

# Create project.py file.
open(f"{project_name}/{project_name}.py", "w+").write("#!/usr/bin/env python3\n\n")

# Make run.sh and project.py executable.
os.chmod(f"{project_name}/run.sh", 0o755)
os.chmod(f"{project_name}/{project_name}.py", 0o755)

# Open source files in VSCode.
subprocess.run(["code", f"{project_name}/{project_name}.cpp"])
subprocess.run(["code", f"{project_name}/{project_name}.py"])

# Already do run.sh once.
os.chdir(f"{project_name}")
subprocess.run(["bash", "run.sh"])
