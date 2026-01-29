#include <stdio.h>
#include "set.h"

// Basic showcase TODO: Do something more useful

int main(void) {
    struct set_element elements[] = {
        {5, "five"}, {3, "three"}, {7, "seven"},
        {1, "one"}, {9, "nine"}
    };

    struct set *s = set_build(5, elements);

    int key;
    void *data;
    if (set_find(s, 5, &key, &data)) {
        printf("Found: %d -> %s\n", key, (char*)data);
    }

    set_insert(s, (struct set_element){6, "six"});

    struct set_element *min = set_find_min(s);
    printf("Min: %d\n", min->key);

    set_free(s);
    return 0;
}