//
// Created by christopher on 27.01.2026.
//

#ifndef ASSGINMENT2_SET_H
#define ASSGINMENT2_SET_H

#include <stddef.h>

#define NULL_IDX ((size_t)-1)

struct set_element {
    int key;
    void *value;
};

struct avl_node {
    struct set_element element;
    size_t left;
    size_t right;
    int height;
};

struct set {
    struct avl_node *nodes;
    size_t root;
    size_t size;
    size_t capacity;
    size_t *free_list;
    size_t free_count;
};

struct set *set_build(size_t size, struct set_element elements[]);

bool set_find(const struct set *s, int key, int *key_out, void **data_out);

void set_insert(struct set *s, struct set_element element);

void set_delete(struct set *s, int key);

struct set_element *set_find_min(struct set *s);

struct set_element *set_find_max(struct set *s);

struct set_element *set_find_prev(struct set *s, int key);

struct set_element *set_find_next(struct set *s, int key);

void set_free(struct set *s);


#endif //ASSGINMENT2_SET_H