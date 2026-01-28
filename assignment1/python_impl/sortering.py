
def insertion_sort(arr: list) -> int:
    steps = 0
    for i in range(1, len(arr)):
        j = i
        current = arr[i]
        steps += 1  # comparison in loop condition

        while j > 0 and current < arr[j-1]:
            steps += 2  # two comparisons in while condition
            arr[j] = arr[j-1]
            j -= 1
            steps += 1  # assignment operation

        arr[j] = current
        steps += 1  # final assignment

    return steps




def heap_sort(arr):
    steps = [0]

    def left(i):
        return 2*i+1

    def right(i):
        return 2*i+2

    def max_heapify(heap_size, i):
        l = left(i)
        r = right(i)
        largest = i
        steps[0] += 3  # three assignments
        
        if l < heap_size and arr[l] > arr[largest]:
            steps[0] += 2  # two comparisons
            largest = l
        else:
            steps[0] += 1  # one comparison (short-circuit)
            
        if r < heap_size and arr[r] > arr[largest]:
            steps[0] += 2  # two comparisons
            largest = r
        else:
            steps[0] += 1  # one comparison

        if largest != i:
            steps[0] += 1  # comparison
            arr[i], arr[largest] = arr[largest], arr[i]
            steps[0] += 1  # swap operation
            max_heapify(heap_size, largest)

    def build_max_heap():
        heap_size = len(arr)
        for i in range((heap_size // 2) - 1, -1, -1):
            max_heapify(heap_size, i)

    n = len(arr)
    if n < 2:
        return steps[0]

    build_max_heap()

    for end in range(n - 1, 0, -1):
        arr[0], arr[end] = arr[end], arr[0]
        steps[0] += 1  # swap
        max_heapify(end, 0)

    return steps[0]

def merge_sort(A, left, right, steps=None):
    is_initial_call = steps is None
    if steps is None:
        steps = [0]
    
    if left >= right:
        steps[0] += 1
        return steps[0] if is_initial_call else None

    steps[0] += 1
    mid = left + (right - left) // 2
    merge_sort(A, left, mid, steps)
    merge_sort(A, mid + 1, right, steps)
    merge(A, left, mid, right, steps)
    
    return steps[0] if is_initial_call else None


def merge(A, left, mid, right, steps=None):
    if steps is None:
        steps = [0]
        
    n_left = mid - left + 1
    n_right = right - mid

    L = [0] * n_left
    R = [0] * n_right
    
    for i in range(n_left):
        L[i] = A[left + i]
        steps[0] += 1

    for i in range(n_right):
        R[i] = A[mid + i + 1]
        steps[0] += 1

    i = j = 0
    k = left
    while i < n_left and j < n_right:
        steps[0] += 2  # two comparisons in while
        if L[i] <= R[j]:
            steps[0] += 1  # comparison
            A[k] = L[i]
            i += 1
        else:
            A[k] = R[j]
            j += 1
        k += 1
        steps[0] += 1  # assignment

    while i < n_left:
        steps[0] += 1  # comparison
        A[k] = L[i]
        i += 1
        k += 1
        steps[0] += 1

    while j < n_right:
        steps[0] += 1  # comparison
        A[k] = R[j]
        j += 1
        k += 1
        steps[0] += 1
        


def quick_sort(arr, p, r, steps=None):
    is_initial_call = steps is None
    if steps is None:
        steps = [0]
    
    if p < r:
        steps[0] += 1
        q = partition(arr, p, r, steps)
        quick_sort(arr, p, q - 1, steps)
        quick_sort(arr, q + 1, r, steps)
    else:
        steps[0] += 1
    
    return steps[0] if is_initial_call else None


def partition(arr, p, r, steps=None):
    if steps is None:
        steps = [0]
        
    x = arr[r]
    i = p - 1
    steps[0] += 1
    
    for j in range(p, r):
        if arr[j] <= x:
            steps[0] += 1  # comparison
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
            steps[0] += 1  # swap
        else:
            steps[0] += 1  # comparison

    arr[i + 1], arr[r] = arr[r], arr[i + 1]
    steps[0] += 1  # swap
    return i + 1