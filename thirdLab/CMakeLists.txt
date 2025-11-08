cmake_minimum_required(VERSION 3.10)
project(lab1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

set(UTILS_SOURCES src/utils.cpp)

if(UNIX)
    set(PLATFORM_SOURCES src/os_linux.cpp)
elseif(WIN32)
    set(PLATFORM_SOURCES src/os_win.cpp)
endif()

add_executable(parent
    src/parent.cpp
    src/parent_process.cpp
    src/child_process.cpp
    ${PLATFORM_SOURCES}
)

add_executable(child
    src/child.cpp
    src/child_process.cpp      
    ${PLATFORM_SOURCES}         
)

if(WIN32)
    target_link_libraries(parent ws2_32)
endif()