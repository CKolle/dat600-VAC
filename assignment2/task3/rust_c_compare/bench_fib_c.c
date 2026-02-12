#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <stdlib.h>

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

int main(void) {
    uint32_t sizes[] = {10, 50, 100, 500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    int iterations = 10000;

    for (int s = 0; s < num_sizes; s++) {
        uint32_t n = sizes[s];
        struct timespec start, end;
        volatile uint64_t result;

        clock_gettime(CLOCK_MONOTONIC, &start);
        for (int i = 0; i < iterations; i++) {
            result = fibonacci_bu(n);
        }
        clock_gettime(CLOCK_MONOTONIC, &end);

        double elapsed_ns = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
        double avg_us = elapsed_ns / iterations / 1000.0;
        printf("%u,%.4f\n", n, avg_us);
    }
    return 0;
}
