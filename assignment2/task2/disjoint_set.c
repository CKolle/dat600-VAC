#include "disjoint_set.h"
#include <stdlib.h>

struct disjoint_set *disjoint_set_create(size_t capacity) {
    struct disjoint_set *ds = malloc(sizeof(struct disjoint_set));
    ds->parent = malloc(capacity * sizeof(size_t));
    ds->rank = calloc(capacity, sizeof(size_t));
    ds->capacity = capacity;

    // Initialize everyone as their own parent to prevent segfaults
    for (size_t i = 0; i < capacity; i++) {
        ds->parent[i] = i;
    }
    return ds;
}

void disjoint_set_free(struct disjoint_set *ds) {
    if (ds) {
        free(ds->parent);
        free(ds->rank);
        free(ds);
    }
}

void disjoint_set_make(struct disjoint_set *ds, size_t x) {
    if (x < ds->capacity) {
        ds->parent[x] = x;
        ds->rank[x] = 0;
    }
}

size_t disjoint_set_find(struct disjoint_set *ds, size_t x) {
    if (x >= ds->capacity) return (size_t)-1;

    if (ds->parent[x] != x) {
        // PATH COMPRESSION:
        // Make x point directly to the root, speeding up future lookups.
        ds->parent[x] = disjoint_set_find(ds, ds->parent[x]);
    }
    return ds->parent[x];
}

void disjoint_set_union(struct disjoint_set *ds, size_t x, size_t y) {
    size_t root_x = disjoint_set_find(ds, x);
    size_t root_y = disjoint_set_find(ds, y);

    if (root_x == root_y) return;

    // UNION BY RANK:
    // Always attach the shorter tree to the taller tree.
    if (ds->rank[root_x] < ds->rank[root_y]) {
        ds->parent[root_x] = root_y;
    } else if (ds->rank[root_x] > ds->rank[root_y]) {
        ds->parent[root_y] = root_x;
    } else {
        ds->parent[root_y] = root_x;
        ds->rank[root_x]++;
    }
}