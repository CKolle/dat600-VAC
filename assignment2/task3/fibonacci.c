//
// Created by christopher on 09.02.2026.
//

#include "fibonacci.h"

#include <stdlib.h>
#include <string.h>

static uint64_t *memo;

uint64_t fibonacci_naive(const uint32_t n) {
    if (n <= 1) return n;
    if (n == 2) return 1;
    return fibonacci_naive(n - 1) + fibonacci_naive(n - 2);
}

uint64_t fibonacci_td(const uint32_t n) {
    if (n <= 1) return n;

    if (!memo || n > memo[0]) {
        const uint64_t new_cap = (uint64_t)n + 1;
        uint64_t *new_memo = calloc(new_cap, sizeof(uint64_t));
        if (memo) {
            memcpy(new_memo, memo, (memo[0] + 1) * sizeof(uint64_t));
            free(memo);
        }
        new_memo[0] = n;
        memo = new_memo;
    }

    if (memo[n] != 0) return memo[n];

    uint64_t result;
    if (n == 2) {
        result = 1;
    } else {
        result = fibonacci_td(n - 1) + fibonacci_td(n - 2);
    }

    memo[n] = result;
    return result;
}


uint64_t fibonacci_bu(const uint32_t n) {
    if (n <= 1) return n;

    uint64_t a = 0;
    uint64_t b = 1;

    for (uint32_t i = 2; i <= n; i++) {
        uint64_t next = a + b;
        a = b;
        b = next;
    }
    return b;
}
