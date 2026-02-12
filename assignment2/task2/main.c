#include <stdio.h>
#include "disjoint_set.h"

int main(void) {
    struct disjoint_set *ds = disjoint_set_create(6);

    for (size_t i = 0; i < 6; i++)
        disjoint_set_make(ds, i);

    disjoint_set_union(ds, 0, 1);
    disjoint_set_union(ds, 2, 3);
    disjoint_set_union(ds, 0, 2);

    disjoint_set_free(ds);
    return 0;
}