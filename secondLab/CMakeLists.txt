cmake_minimum_required(VERSION 3.10)
project(lab2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


if(UNIX)
    set(PLATFORM_SOURCES src/os_linux.cpp)
elseif(WIN32)
    set(PLATFORM_SOURCES src/os_win.cpp)
endif()


add_executable(main
    src/batcher_sort.cpp
    src/main.cpp
    src/mutex.cpp
    src/glob.cpp
    ${PLATFORM_SOURCES}
)

