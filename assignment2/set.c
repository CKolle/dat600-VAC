//
// Created by christopher on 27.01.2026.
//

#include "set.h"

#include <stdlib.h>
#include <string.h>

// ============== Notes ==============
// Note 1:
// IMPORTANT: We need to assign the result to a variable before using it.
// As C evaluates  s->nodes[idx].left first. If a realloc happens this will now be pointing to invalid memory.
// Thus we first store it and then evaluates the left child.

// ============== AVL Tree Helper Functions ==============

static int height(const struct set *s, const size_t idx) {
    return idx == NULL_IDX ? 0 : s->nodes[idx].height;
}

static void update_height(const struct set *s, const size_t idx) {
    const int hl = height(s, s->nodes[idx].left);
    const int hr = height(s, s->nodes[idx].right);
    s->nodes[idx].height = 1 + (hl > hr ? hl : hr);
}

static int balance_factor(const struct set *s, const size_t idx) {
    return height(s, s->nodes[idx].left) - height(s, s->nodes[idx].right);
}

static size_t rotate_right(const struct set *s, const size_t y) {
    const size_t x = s->nodes[y].left;
    s->nodes[y].left = s->nodes[x].right;
    s->nodes[x].right = y;
    update_height(s, y);
    update_height(s, x);
    return x;
}

static size_t rotate_left(const struct set *s, const size_t x) {
    const size_t y = s->nodes[x].right;
    s->nodes[x].right = s->nodes[y].left;
    s->nodes[y].left = x;
    update_height(s, x);
    update_height(s, y);
    return y;
}

static size_t rebalance(const struct set *s, const size_t idx) {
    update_height(s, idx);
    const int bf = balance_factor(s, idx);
    if (bf > 1) {
        if (balance_factor(s, s->nodes[idx].left) < 0)
            s->nodes[idx].left = rotate_left(s, s->nodes[idx].left);
        return rotate_right(s, idx);
    }
    if (bf < -1) {
        if (balance_factor(s, s->nodes[idx].right) > 0)
            s->nodes[idx].right = rotate_right(s, s->nodes[idx].right);
        return rotate_left(s, idx);
    }
    return idx;
}

// ============== Node Allocation ==============

static size_t alloc_node(struct set *s) {
    if (s->free_list && s->free_count > 0)
        return s->free_list[--s->free_count];
    if (s->size >= s->capacity) {
        const size_t new_cap = s->capacity == 0 ? 8 : s->capacity * 2;
        struct avl_node *new_nodes = realloc(s->nodes, new_cap * sizeof(struct avl_node));
        size_t *new_free = realloc(s->free_list, new_cap * sizeof(size_t));
        if (!new_nodes || !new_free) return NULL_IDX;
        s->nodes = new_nodes;
        s->free_list = new_free;
        s->capacity = new_cap;
    }
    return s->size++;
}

static void free_node(struct set *s, const size_t idx) {
    s->free_list[s->free_count++] = idx;
}

// ============== Recursive Insert ==============

static size_t insert_node(struct set *s, const size_t idx, const struct set_element e, bool *inserted) {
    if (idx == NULL_IDX) {
        const size_t new_idx = alloc_node(s);
        if (new_idx == NULL_IDX) return NULL_IDX;
        s->nodes[new_idx].element = e;
        s->nodes[new_idx].left = NULL_IDX;
        s->nodes[new_idx].right = NULL_IDX;
        s->nodes[new_idx].height = 1;
        *inserted = true;
        return new_idx;
    }
    if (e.key < s->nodes[idx].element.key) {
        // See note 1:
        const size_t res = insert_node(s, s->nodes[idx].left, e, inserted);
        s->nodes[idx].left = res;
    } else if (e.key > s->nodes[idx].element.key) {
        // See note 1:
        const size_t res = insert_node(s, s->nodes[idx].right, e, inserted);
        s->nodes[idx].right = res;
    }
    // else: key exists, do nothing
    return rebalance(s, idx);
}

// ============== Recursive Delete ==============

static size_t find_min_idx(const struct set *s, size_t idx) {
    while (s->nodes[idx].left != NULL_IDX)
        idx = s->nodes[idx].left;
    return idx;
}

static size_t delete_node(struct set *s, const size_t idx, const int key, bool *deleted) {
    if (idx == NULL_IDX) return NULL_IDX;

    if (key < s->nodes[idx].element.key) {
        // See note 1:
        const size_t res = delete_node(s, s->nodes[idx].left, key, deleted);
        s->nodes[idx].left = res;
    } else if (key > s->nodes[idx].element.key) {
        // See note 1:
        const size_t res = delete_node(s, s->nodes[idx].right, key, deleted);
        s->nodes[idx].right = res;
    } else {
        *deleted = true;
        if (s->nodes[idx].left == NULL_IDX || s->nodes[idx].right == NULL_IDX) {
            const size_t temp = s->nodes[idx].left != NULL_IDX ? s->nodes[idx].left : s->nodes[idx].right;
            free_node(s, idx);
            return temp;
        }
        const size_t min_idx = find_min_idx(s, s->nodes[idx].right);
        const struct set_element min_element = s->nodes[min_idx].element;
        s->nodes[idx].element = min_element;
        s->nodes[idx].right = delete_node(s, s->nodes[idx].right, min_element.key, deleted);
    }
    return rebalance(s, idx);
}

// ============== Merge Sort for Build ==============

static void merge(struct set_element arr[], const int left, const int mid, const int right) {
    const int n_left = mid - left + 1;
    const int n_right = right - mid;

    struct set_element *left_arr = malloc(n_left * sizeof(struct set_element));
    struct set_element *right_arr = malloc(n_right * sizeof(struct set_element));
    if (!left_arr || !right_arr) {
        free(left_arr);
        free(right_arr);
        return;
    }

    for (int i = 0; i < n_left; i++)
        left_arr[i] = arr[left + i];
    for (int i = 0; i < n_right; i++)
        right_arr[i] = arr[mid + i + 1];

    int i = 0, j = 0, k = left;
    while (i < n_left && j < n_right) {
        if (left_arr[i].key <= right_arr[j].key)
            arr[k++] = left_arr[i++];
        else
            arr[k++] = right_arr[j++];
    }
    while (i < n_left)
        arr[k++] = left_arr[i++];
    while (j < n_right)
        arr[k++] = right_arr[j++];

    free(left_arr);
    free(right_arr);
}

static void merge_sort(struct set_element arr[], const int left, const int right) {
    if (left >= right) return;
    const int mid = left + (right - left) / 2;
    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// Build balanced AVL from sorted array - O(n)
static size_t build_balanced(struct set *s, struct set_element arr[], const int start, const int end) {
    if (start > end) return NULL_IDX;

    const int mid = start + (end - start) / 2;
    const size_t idx = alloc_node(s);
    if (idx == NULL_IDX) return NULL_IDX;

    s->nodes[idx].element = arr[mid];
    s->nodes[idx].left = build_balanced(s, arr, start, mid - 1);
    s->nodes[idx].right = build_balanced(s, arr, mid + 1, end);
    update_height(s, idx);

    return idx;
}

// ============== Public API ==============

struct set *set_build(const size_t size, struct set_element elements[]) {
    struct set *s = malloc(sizeof(struct set));
    if (!s) return nullptr;

    s->nodes = nullptr;
    s->root = NULL_IDX;
    s->size = 0;
    s->capacity = 0;
    s->free_list = nullptr;
    s->free_count = 0;

    if (size == 0) return s;

    struct set_element *temp = malloc(size * sizeof(struct set_element));
    if (!temp) {
        free(s);
        return nullptr;
    }
    memcpy(temp, elements, size * sizeof(struct set_element));
    merge_sort(temp, 0, (int)size - 1);

    // Remove duplicates
    size_t unique_count = 1;
    for (size_t i = 1; i < size; i++) {
        if (temp[i].key != temp[i - 1].key)
            temp[unique_count++] = temp[i];
    }

    // Pre-allocate capacity
    s->nodes = malloc(unique_count * sizeof(struct avl_node));
    s->free_list = malloc(unique_count * sizeof(size_t));
    if (!s->nodes || !s->free_list) {
        free(temp);
        free(s->nodes);
        free(s->free_list);
        free(s);
        return nullptr;
    }
    s->capacity = unique_count;

    // Build the balanced tree from sorted array - O(n)
    s->root = build_balanced(s, temp, 0, (int)unique_count - 1);
    free(temp);

    return s;
}

bool set_find(const struct set *s, const int key, int *key_out, void **data_out) {
    if (!s) return false;

    size_t idx = s->root;
    while (idx != NULL_IDX) {
        if (key == s->nodes[idx].element.key) {
            if (key_out) *key_out = s->nodes[idx].element.key;
            if (data_out) *data_out = s->nodes[idx].element.value;
            return true;
        }
        if (key < s->nodes[idx].element.key)
            idx = s->nodes[idx].left;
        else
            idx = s->nodes[idx].right;
    }
    return false;
}

void set_insert(struct set *s, const struct set_element element) {
    if (!s) return;
    bool inserted = false;
    s->root = insert_node(s, s->root, element, &inserted);
}

void set_delete(struct set *s, const int key) {
    if (!s) return;
    bool deleted = false;
    s->root = delete_node(s, s->root, key, &deleted);
}

struct set_element *set_find_min(struct set *s) {
    if (!s || s->root == NULL_IDX) return nullptr;

    size_t idx = s->root;
    while (s->nodes[idx].left != NULL_IDX)
        idx = s->nodes[idx].left;
    return &s->nodes[idx].element;
}

struct set_element *set_find_max(struct set *s) {
    if (!s || s->root == NULL_IDX) return nullptr;

    size_t idx = s->root;
    while (s->nodes[idx].right != NULL_IDX)
        idx = s->nodes[idx].right;
    return &s->nodes[idx].element;
}

struct set_element *set_find_next(struct set *s, const int key) {
    if (!s || s->root == NULL_IDX) return nullptr;

    size_t idx = s->root;
    size_t successor = NULL_IDX;

    while (idx != NULL_IDX) {
        if (s->nodes[idx].element.key > key) {
            successor = idx;
            idx = s->nodes[idx].left;
        } else {
            idx = s->nodes[idx].right;
        }
    }

    return successor == NULL_IDX ? nullptr : &s->nodes[successor].element;
}

struct set_element *set_find_prev(struct set *s, const int key) {
    if (!s || s->root == NULL_IDX) return nullptr;

    size_t idx = s->root;
    size_t predecessor = NULL_IDX;

    while (idx != NULL_IDX) {
        if (s->nodes[idx].element.key < key) {
            predecessor = idx;
            idx = s->nodes[idx].right;
        } else {
            idx = s->nodes[idx].left;
        }
    }

    return predecessor == NULL_IDX ? nullptr : &s->nodes[predecessor].element;
}

void set_free(struct set *s) {
    if (s) {
        free(s->nodes);
        free(s->free_list);
        free(s);
    }
}