import time
import sys
import matplotlib.pyplot as plt

sys.setrecursionlimit(2000)

# 1. Naive Recursive Approach
def fib_naive(n):
    if n <= 1:
        return n
    return fib_naive(n-1) + fib_naive(n-2)

# 2. Top-Down with Memoization
memo = {}
def fib_memo(n):
    if n in memo:
        return memo[n]
    if n <= 1:
        return n
    memo[n] = fib_memo(n-1) + fib_memo(n-2)
    return memo[n]

# 3. Bottom-Up (Tabulation)
def fib_tabulation(n):
    if n <= 1:
        return n
    table = [0] * (n + 1)
    table[1] = 1
    for i in range(2, n + 1):
        table[i] = table[i-1] + table[i-2]
    return table[n]

# 4.  This is also bottom up
def fib_bu2(n):
    if n <= 1: return n
    a, b = 0, 1
    for _ in range(2, n + 1):
        a, b = b, a + b
    return b

def measure_time(func, arg):
    start = time.perf_counter()
    func(arg)
    end = time.perf_counter()
    return end - start

n_values = range(0, 40, 2)  # 

times_naive = []
times_memo = []
times_tab = []
times_bu2 = []

print(f"Calculating for n = {list(n_values)}...")

for n in n_values:
    print(f"Processing n={n}...")
    
    # 1. Naive
    times_naive.append(measure_time(fib_naive, n))
    
    # 2. Memoization (Clear cache first for fair timing)
    memo = {} 
    times_memo.append(measure_time(fib_memo, n))
    
    # 3. Tabulation
    times_tab.append(measure_time(fib_tabulation, n))
    
    # 4. Greedy
    times_bu2.append(measure_time(fib_bu2, n))


plt.figure(figsize=(10, 6))

plt.plot(n_values, times_naive, label='Naive Recursive', marker='o')
plt.plot(n_values, times_memo, label='Memoization', marker='o')
plt.plot(n_values, times_tab, label='Tabulation', marker='o')
plt.plot(n_values, times_bu2, label='Bottom up 2', marker='o')

plt.title('Fibonacci Algorithm Performance')
plt.xlabel('n (Fibonacci Term)')
plt.ylabel('Time (seconds)')
plt.legend()
plt.grid(True)

plt.yscale('log') 

plt.show()