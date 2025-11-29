cmake_minimum_required(VERSION 3.10)
project(lab4)

set(CMAKE_C_STANDARD 99)

include_directories(include)

# Библиотека 1
add_library(impl1 SHARED
    libs/impl1/gcf_impl1.c
    libs/impl1/square_impl1.c
)

# Библиотека 2
add_library(impl2 SHARED
    libs/impl2/gcf_impl2.c
    libs/impl2/square_impl2.c
)

# Программа 1 с реализацией 1
add_executable(prog1_impl1 prog1/main.c)
target_link_libraries(prog1_impl1 impl1)

# Программа 1 с реализацией 2
add_executable(prog1_impl2 prog1/main.c)
target_link_libraries(prog1_impl2 impl2)

# Программа 2 (динамическая загрузка)
add_executable(prog2 prog2/main.c)
target_link_libraries(prog2 ${CMAKE_DL_LIBS})
