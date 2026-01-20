def merge_sort(A, left, right):
    if left >= right:
        return

    mid = left + (right - left) // 2
    merge_sort(A, left, mid)
    merge_sort(A, mid + 1, right)
    merge(A, left, mid, right)


def merge(A, left, mid, right):
    n_left =  mid - left + 1
    n_right = right - mid

    L = [0] * n_left
    R = [0] * n_right
    for i in range(n_left):
        L[i] = A[left + i]

    for i in range(n_right):
        R[i] = A[mid + i + 1]

    i = j = 0
    k = left
    while i < n_left and j < n_right:
        if L[i] <= R[j]:
            A[k] = L[i]
            i += 1
        else:
            A[k] = R[j]
            j += 1
        k += 1

    while i < n_left:
        A[k] = L[i]
        i += 1
        k += 1
    while j < n_right:
        A[k] = R[j]
        j += 1
        k += 1
