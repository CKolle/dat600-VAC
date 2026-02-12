#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#include <stddef.h>
#include <stdbool.h>

struct disjoint_set {
    size_t *parent;
    size_t *rank;
    size_t capacity;
};

// Creates the set and initializes "everyone is their own parent" to prevent crashes
struct disjoint_set *disjoint_set_create(size_t capacity);

void disjoint_set_free(struct disjoint_set *ds);

// O(1) - Makes x a singleton set (resets it)
void disjoint_set_make(struct disjoint_set *ds, size_t x);

// O(a(n)) - Finds the representative ID with Path Compression
size_t disjoint_set_find(struct disjoint_set *ds, size_t x);

// O(a(n)) - Merges two sets using Union by Rank
void disjoint_set_union(struct disjoint_set *ds, size_t x, size_t y);

#endif