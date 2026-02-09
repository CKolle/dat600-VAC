#include <stdio.h>
#include <assert.h>
#include "fibonacci.h"

void test_fibonacci() {
#define EXPECTED 12586269025UL
    printf("Testing Fibonacci...\n");
    uint64_t fib_td = fibonacci_td(50);
    uint64_t fib_bu = fibonacci_bu(50);
    assert(fib_td == EXPECTED);
    assert(fib_bu == EXPECTED);
    puts("Passed!");
}

int main(void) {
    test_fibonacci();
    printf("All tests passed!\n");
    return 0;
}
