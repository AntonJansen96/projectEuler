#!/bin/bash

set -e
if [ ! -f "build/CMakeCache.txt" ]; then cmake -B build; fi
make -j -C build
./build/p729
