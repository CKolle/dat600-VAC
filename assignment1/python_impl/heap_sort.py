


def heap_sort(arr):

    def left(i):
        return 2*i+1

    def right(i):
        return 2*i+2

    def max_heapify(heap_size, i):
        l = left(i)
        r = right(i)
        largest = i
        if l < heap_size and arr[l] > arr[largest]:
            largest = l
        if r < heap_size and arr[r] > arr[largest]:
            largest = r

        if largest != i:
            arr[i], arr[largest] = arr[largest], arr[i]
            max_heapify(heap_size, largest)

    def build_max_heap():
        heap_size = len(arr)
        for i in range((heap_size // 2) - 1, -1, -1):
            max_heapify(heap_size, i)

    n = len(arr)
    if n < 2:
        return arr

    build_max_heap()

    for end in range(n - 1, 0, -1):
        arr[0], arr[end] = arr[end], arr[0]
        max_heapify(end, 0)

    return arr