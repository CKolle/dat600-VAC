cmake_minimum_required(VERSION 3.5)
project(assignment2_tests C)

set(CMAKE_C_STANDARD 23)

add_executable(all_tests tests.c
        task1/set.c
        task2/disjoint_set.c
        task3/fibonacci.c
)

add_executable(fibonacci_bench
        task3/fibonacci_bench.c
        task3/fibonacci.c
)

enable_testing()
add_test(NAME Tests COMMAND tests)
