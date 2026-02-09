//
// Created by christopher on 28.01.2026.
//

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "set.h"

// Helper to check tree height (basic validation)
static int get_height(struct set *s, size_t idx) {
    if (idx == NULL_IDX) return 0;
    int lh = get_height(s, s->nodes[idx].left);
    int rh = get_height(s, s->nodes[idx].right);
    return 1 + (lh > rh ? lh : rh);
}

static void assert_balanced(struct set *s, size_t idx) {
    if (idx == NULL_IDX) return;
    int lh = get_height(s, s->nodes[idx].left);
    int rh = get_height(s, s->nodes[idx].right);
    int diff = lh - rh;
    assert(diff >= -1 && diff <= 1);
    assert_balanced(s, s->nodes[idx].left);
    assert_balanced(s, s->nodes[idx].right);
}

void test_insert_find() {
    printf("Testing insert and find...\n");
    struct set *s = set_build(0, nullptr);
    assert(s != nullptr);
    assert(s->size == 0);

    struct set_element e1 = {10, (void*)"ten"};
    struct set_element e2 = {20, (void*)"twenty"};
    struct set_element e3 = {5, (void*)"five"};

    set_insert(s, e1);
    set_insert(s, e2);
    set_insert(s, e3);

    int k;
    void *v;
    assert(set_find(s, 10, &k, &v) == true);
    assert(k == 10);
    assert(strcmp((char*)v, "ten") == 0);

    assert(set_find(s, 20, &k, &v) == true);
    assert(set_find(s, 5, &k, &v) == true);
    assert(set_find(s, 15, &k, &v) == false);

    assert_balanced(s, s->root);
    set_free(s);
    printf("Passed!\n");
}

void test_delete() {
    printf("Testing delete...\n");
    struct set *s = set_build(0, nullptr);
    
    int keys[] = {10, 20, 30, 40, 50, 25};
    for (int i = 0; i < 6; i++) {
        set_insert(s, (struct set_element){keys[i], nullptr});
    }

    assert(set_find(s, 30, nullptr, nullptr) == true);
    set_delete(s, 30);
    assert(set_find(s, 30, nullptr, nullptr) == false);
    assert_balanced(s, s->root);

    set_delete(s, 10);
    assert(set_find(s, 10, nullptr, nullptr) == false);
    assert_balanced(s, s->root);

    set_delete(s, 50);
    assert(set_find(s, 50, nullptr, nullptr) == false);
    assert_balanced(s, s->root);

    set_free(s);
    printf("Passed!\n");
}

void test_min_max_prev_next() {
    printf("Testing min/max/prev/next...\n");
    struct set_element elems[] = {
        {10, nullptr}, {20, nullptr}, {5, nullptr}, {15, nullptr}, {25, nullptr}
    };
    struct set *s = set_build(5, elems);

    assert(set_find_min(s)->key == 5);
    assert(set_find_max(s)->key == 25);

    assert(set_find_next(s, 10)->key == 15);
    assert(set_find_next(s, 15)->key == 20);
    assert(set_find_next(s, 25) == nullptr);

    assert(set_find_prev(s, 15)->key == 10);
    assert(set_find_prev(s, 10)->key == 5);
    assert(set_find_prev(s, 5) == nullptr);

    set_free(s);
    printf("Passed!\n");
}

void test_duplicates() {
    printf("Testing duplicates...\n");
    struct set *s = set_build(0, nullptr);
    set_insert(s, (struct set_element){10, (void*)"first"});
    set_insert(s, (struct set_element){10, (void*)"second"});

    int k;
    void *v;
    assert(set_find(s, 10, &k, &v) == true);
    // In this implementation, duplicates are ignored in insert_node
    assert(strcmp((char*)v, "first") == 0);

    set_free(s);
    printf("Passed!\n");
}

void test_large_insert() {
    printf("Testing large insertion...\n");
    struct set *s = set_build(0, nullptr);
    for (int i = 0; i < 1000; i++) {
        set_insert(s, (struct set_element){i, nullptr});
    }
    assert_balanced(s, s->root);
    for (int i = 0; i < 1000; i++) {
        assert(set_find(s, i, nullptr, nullptr) == true);
    }
    set_free(s);
    printf("Passed!\n");
}

void test_set_build() {
    printf("Testing set_build...\n");
    struct set_element elems[] = {
        {30, nullptr}, {10, nullptr}, {20, nullptr}, {10, nullptr}, {40, nullptr}
    };
    struct set *s = set_build(5, elems);
    assert(s != nullptr);
    assert(set_find(s, 10, nullptr, nullptr));
    assert(set_find(s, 20, nullptr, nullptr));
    assert(set_find(s, 30, nullptr, nullptr));
    assert(set_find(s, 40, nullptr, nullptr));
    assert_balanced(s, s->root);
    set_free(s);
    printf("Passed!\n");
}

int main() {
    test_insert_find();
    test_delete();
    test_min_max_prev_next();
    test_duplicates();
    test_large_insert();
    test_set_build();
    printf("All tests passed successfully!\n");
    return 0;
}