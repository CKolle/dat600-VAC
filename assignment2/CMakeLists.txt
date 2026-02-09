cmake_minimum_required(VERSION 3.5)
project(assignment2 C)

set(CMAKE_C_STANDARD 23)

add_executable(assignment2 main.c
        set.c
        set.h
        fibonacci.c
        fibonacci.h
)

add_executable(tests tests.c
        set.c
        set.h
        fibonacci.c
        fibonacci.h
)

enable_testing()
add_test(NAME Tests COMMAND set_tests)
