cmake_minimum_required(VERSION 3.10)
project(Lab4)
set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_library(impl1 SHARED libs/libimpl1.cpp)
set_target_properties(impl1 PROPERTIES OUTPUT_NAME "impl1")

add_library(impl2 SHARED libs/libimpl2.cpp)
set_target_properties(impl2 PROPERTIES OUTPUT_NAME "impl2")

add_executable(program1 src/program1.cpp)
target_link_libraries(program1 impl1)

add_executable(program2 src/program2.cpp)