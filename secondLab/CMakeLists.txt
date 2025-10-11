cmake_minimum_required(VERSION 3.10)
project(lab2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main
    src/batcher_sort.cpp
    src/main.cpp
    src/mutex.cpp
    src/os_linux.cpp
    src/glob.cpp
)

