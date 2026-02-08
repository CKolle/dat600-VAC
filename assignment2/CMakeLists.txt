cmake_minimum_required(VERSION 3.5)
project(assignment2 C)

set(CMAKE_C_STANDARD 23)

add_executable(assignment2 main.c
        set.c
        set.h
)

add_executable(set_tests tests.c
        set.c
        set.h
)

enable_testing()
add_test(NAME SetTests COMMAND set_tests)
