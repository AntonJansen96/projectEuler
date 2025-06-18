cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER "/opt/homebrew/bin/gcc-15")
set(CMAKE_CXX_COMPILER "/opt/homebrew/bin/g++-15")
set(CMAKE_CXX_FLAGS "-Wall -std=c++23 -O3 -fopenmp -march=native -funroll-loops -ffast-math -flto -Wl,-w")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(p729)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)
add_executable(p729 p729.cpp)
target_link_libraries(p729 euler fileio fractions math stopwatch utility gmp mpfr flint)
