

def insertion_sort(arr: list) -> int:
    steps = 0
    for i in range(1, len(arr)):
        j = i
        current = arr[i]

        while j > 0 and current < arr[j-1]:
            arr[j] = arr[j-1]
            j -= 1

        arr[j] = current


    return steps