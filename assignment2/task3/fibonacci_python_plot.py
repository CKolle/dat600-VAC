import time
import sys
import matplotlib.pyplot as plt

# Increase recursion depth for naive/memo approaches
sys.setrecursionlimit(2000)

# 1. Naive Recursive Approach - O(2^n)
def fib_naive(n):
    if n <= 1:
        return n
    return fib_naive(n-1) + fib_naive(n-2)

# 2. Top-Down with Memoization - O(n)
memo = {}
def fib_memo(n):
    if n in memo:
        return memo[n]
    if n <= 1:
        return n
    memo[n] = fib_memo(n-1) + fib_memo(n-2)
    return memo[n]

# 3. Bottom-Up Tabulation - O(n)
def fib_tabulation(n):
    if n <= 1:
        return n
    table = [0] * (n + 1)
    table[1] = 1
    for i in range(2, n + 1):
        table[i] = table[i-1] + table[i-2]
    return table[n]

# 4. Space-Optimized Bottom-Up - O(n)
def fib_bu2(n):
    if n <= 1: return n
    a, b = 0, 1
    for _ in range(2, n + 1):
        a, b = b, a + b
    return b

# Settings
n_values = range(0, 36, 2) 
num_trials = 100  # Number of runs to average

times_naive = []
times_memo = []
times_tab = []
times_bu2 = []

print(f"Calculating averages over {num_trials} trials for each n...")

for n in n_values:
    print(f"Processing n={n}...", end="\r")
    
    t_naive_sum = 0
    t_memo_sum = 0
    t_tab_sum = 0
    t_bu2_sum = 0
    
    for _ in range(num_trials):
        # 1. Naive
        start = time.perf_counter()
        fib_naive(n)
        t_naive_sum += (time.perf_counter() - start)
        
        # 2. Memoization 
        memo.clear()  # Clear the memoization cache before each run
        memo = {} 
        start = time.perf_counter()
        fib_memo(n)
        t_memo_sum += (time.perf_counter() - start)
        
        # 3. Tabulation
        start = time.perf_counter()
        fib_tabulation(n)
        t_tab_sum += (time.perf_counter() - start)
        
        # 4. Space-Optimized
        start = time.perf_counter()
        fib_bu2(n)
        t_bu2_sum += (time.perf_counter() - start)

    # Store the averages
    times_naive.append(t_naive_sum / num_trials)
    times_memo.append(t_memo_sum / num_trials)
    times_tab.append(t_tab_sum / num_trials)
    times_bu2.append(t_bu2_sum / num_trials)

print("\nDone!")

# Plotting
plt.figure(figsize=(10, 6))

plt.plot(n_values, times_naive, label='Naive Recursive', marker='o')
plt.plot(n_values, times_memo, label='Memoization', marker='o')
plt.plot(n_values, times_tab, label='Tabulation', marker='o')
plt.plot(n_values, times_bu2, label='Tabulation (Optimized)', marker='o')

plt.title(f'Fibonacci Algorithm Performance (Average of {num_trials} trials)')
plt.xlabel('n (Fibonacci Term)')
plt.ylabel('Time (seconds)')
plt.yscale('log') # Log scale is necessary to see the DP lines vs the Naive line
plt.legend()
plt.grid(True, which="major", ls="-", alpha=0.5)

plt.show()