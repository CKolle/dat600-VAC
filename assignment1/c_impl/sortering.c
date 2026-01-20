#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// QUICK SORT ALGORITHM


int partition(int arr[], const int p, const int r) {
    const int x = arr[r];
    int i = p - 1;
    int temp;
    for (int j = p; j < r; j++) {
        if (arr[j] <= x) {
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    temp = arr[i + 1];
    arr[i + 1] = arr[r];
    arr[r] = temp;
    return i + 1;
}



void quick_sort(int arr[], const int p, const int r) {
    if (p < r) {
        const int q = partition(arr, p, r);
        quick_sort(arr, p, q - 1);
        quick_sort(arr, q + 1, r);
    }
}


// MERGE SORT ALGORITHM

void merge(int arr[], const int left, const int mid, const int right) {
    const int n_left = mid - left + 1;
    const int n_right = right - mid;

    int *left_arr = malloc(n_left * sizeof(int));
    int *right_arr = malloc(n_right * sizeof(int));
    if (!left_arr || !right_arr) {
        goto cleanup;
    }

    for (int i = 0; i < n_left; i++) {
        left_arr[i] = arr[left + i];
    }
    for (int i = 0; i < n_right; i++) {
        right_arr[i] = arr[mid + i + 1];
    }

    int i = 0, j = 0, k = left;
    while (i < n_left && j < n_right) {
        if (left_arr[i] <= right_arr[j]) {
            arr[k++] = left_arr[i++];
        } else {
            arr[k++] = right_arr[j++];
        }
    }

    while (i < n_left)
        arr[k++] = left_arr[i++];

    while (j < n_right)
        arr[k++] = right_arr[j++];

cleanup:
    free(left_arr);
    free(right_arr);
}

void merge_sort(int arr[], const int left, const int right) {
    if (left >= right) {
        return;
    }

    const int mid = left + (right - left) / 2;
    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}


// INSERTION SORT

void insertion_sort(int arr[], const int n) {
    for (int i = 1; i < n; i++) {
        int j = i;
        int cur = arr[i];

        while (j > 0 && cur < arr[j-1]) {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = cur;
    }
}

// HEAP SORT

int left(const int i) {
    return  2 * i + 1;
}

int right(const int i) {
    return 2 * i + 2;
}

void max_heapify(int arr[], const int n, const int i) {
    int l = left(i);
    int r = right(i);
    int largest = i;

    if (l < n && arr[l] > arr[largest])
        largest = l;
    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        max_heapify(arr, n, largest);
    }
}

void build_max_heap(int arr[], const int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        max_heapify(arr, n, i);
    }
}

void heap_sort(int arr[], const int n) {
    if (n <= 1)
        return;

    build_max_heap(arr, n);
    for (int i = n - 1; i >= 1; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        max_heapify(arr, i, 0);
    }
}



void print_array(int arr[], const int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int* read_data(const char *filename, int *size) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Failed to open file");
        return nullptr;
    }

    int capacity = 1024;
    int *arr = malloc(capacity * sizeof(int));
    if (!arr) {
        goto cleanup_file;
    }
    int n = 0;

    char line[64];
    while (fgets(line, sizeof(line), fp) != nullptr) {
        char *endptr;
        const long val = strtol(line, &endptr, 10);
        if (endptr == line) {
            continue;  // No valid conversion
        }
        arr[n] = (int)val;
        n++;
        if (n >= capacity) {
            capacity *= 2;
            int *new_arr = realloc(arr, capacity * sizeof(int));
            if (!new_arr) {
                goto cleanup_all;
            }
            arr = new_arr;
        }
    }
    fclose(fp);
    *size = n;
    return arr;

cleanup_all:
    free(arr);
cleanup_file:
    fclose(fp);
    return nullptr;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <datafile> <algorithm>\n", argv[0]);
        printf("Algorithms: quick, merge, insertion, heap\n");
        return 1;
    }

    const char *filename = argv[1];
    const char *algorithm = argv[2];

    int size;
    int *arr = read_data(filename, &size);
    if (!arr) return 1;

    const clock_t start = clock();

    if (strcmp(algorithm, "quick") == 0) {
        quick_sort(arr, 0, size - 1);
    } else if (strcmp(algorithm, "merge") == 0) {
        merge_sort(arr, 0, size - 1);
    } else if (strcmp(algorithm, "insertion") == 0) {
        insertion_sort(arr, size);
    } else if (strcmp(algorithm, "heap") == 0) {
        heap_sort(arr, size);
    } else {
        printf("Unknown algorithm: %s\n", algorithm);
        free(arr);
        return 1;
    }

    const clock_t end = clock();
    const double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Algorithm: %s\n", algorithm);
    printf("Elements: %d\n", size);
    printf("Time: %.6f seconds\n", time_spent);

    free(arr);
    return 0;
}