#include <stdio.h>

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

    int left_arr[n_left], right_arr[n_right];
    for (int i = 0; i < n_left; i++) {
        left_arr[i] = arr[left + i];
    }
    for (int i = 0; i < n_right; i++) {
        right_arr[i] = arr[mid + i +1];
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


int main(void) {
    int arr[] = {10, 7, 8, 9, 1, 5};
    constexpr int n = sizeof(arr) / sizeof(arr[0]);
    quick_sort(arr, 0, n - 1);
    printf("Sorted array: \n");
    print_array(arr, n);
    printf("\n");

    printf("Testing merge sort:\n");
    int arr2[] = {12, 11, 13, 5, 6, 7};
    constexpr int m = sizeof(arr2) / sizeof(arr2[0]);
    merge_sort(arr2, 0, m - 1);
    printf("Sorted array: \n");
    print_array(arr2, m);
    printf("\n");

    printf("Test insertion sort:\n");
    int arr3[] = {12, 11, 13, 5, 6};
    constexpr int k = sizeof(arr3) / sizeof(arr3[0]);
    insertion_sort(arr3, k);
    printf("Sorted array: \n");
    print_array(arr3, k);
    printf("\n");

    printf("Test heap sort:\n");
    int arr4[] = {12, 11, 13, 5, 6, 7};
    constexpr int l = sizeof(arr4) / sizeof(arr4[0]);
    heap_sort(arr4, l);
    printf("Sorted array: \n");
    print_array(arr4, l);
    return 0;
}