import random
from assignment1.python_impl.quick_sort import quick_sort

def test_basic_cases():
    cases = [
        [],
        [1],
        [2, 1],
        [1, 2, 3],
        [3, 2, 1],
        [5, 1, 5, 2, 5],
        [0, -1, 3, -10, 8, 8],
    ]
    for arr in cases:
        original = arr[:]
        quick_sort(arr, 0, len(arr) - 1)
        assert arr == sorted(original)

def test_random_cases():
    for _ in range(500):
        arr = [random.randint(-1000, 1000) for _ in range(random.randint(0, 200))]
        original = arr[:]
        quick_sort(arr, 0, len(arr) - 1)
        assert arr == sorted(original)
