#include <stdio.h>
#include "fibonacci.h"

int main(void) {
    printf("fib(10) top-down:  %lu\n", fibonacci_td(10));
    printf("fib(10) bottom-up: %lu\n", fibonacci_bu(10));
    return 0;
}
