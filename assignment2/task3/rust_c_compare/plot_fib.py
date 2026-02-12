import subprocess
import matplotlib.pyplot as plt

def parse_output(output):
    sizes, times = [], []
    for line in output.strip().split('\n'):
        n, t = line.split(',')
        sizes.append(int(n))
        times.append(float(t))
    return sizes, times

c_out = subprocess.run(['./bench_fib_c'], capture_output=True, text=True).stdout
rs_out = subprocess.run(['./bench_fib_rs'], capture_output=True, text=True).stdout

c_sizes, c_times = parse_output(c_out)
rs_sizes, rs_times = parse_output(rs_out)

fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 6))

# Log-log plot
ax1.plot(c_sizes, c_times, 'o-', label='C (gcc -O3)', color='#1f77b4', linewidth=2, markersize=6)
ax1.plot(rs_sizes, rs_times, 's-', label='Rust (rustc -O)', color='#ff7f0e', linewidth=2, markersize=6)
ax1.set_xscale('log')
ax1.set_yscale('log')
ax1.set_xlabel('n (Fibonacci index)', fontsize=12)
ax1.set_ylabel('Average time per call (us)', fontsize=12)
ax1.set_title('Fibonacci Bottom-Up: C vs Rust (log-log)', fontsize=13)
ax1.legend(fontsize=11)
ax1.grid(True, which='both', alpha=0.3)

speedup = [c / r for c, r in zip(c_times, rs_times)]
colors = ['#2ca02c' if s > 1 else '#d62728' for s in speedup]
bars = ax2.bar(range(len(c_sizes)), speedup, color=colors, alpha=0.8)
ax2.set_xticks(range(len(c_sizes)))
ax2.set_xticklabels([str(s) for s in c_sizes], rotation=45, ha='right', fontsize=9)
ax2.axhline(y=1.0, color='black', linestyle='--', linewidth=1, label='Equal performance')
ax2.set_xlabel('n (Fibonacci index)', fontsize=12)
ax2.set_ylabel('Speedup (C time / Rust time)', fontsize=12)
ax2.set_title('Relative Performance (>1 = Rust faster)', fontsize=13)
ax2.legend(fontsize=10)
ax2.grid(True, axis='y', alpha=0.3)

for i, s in enumerate(speedup):
    ax2.text(i, s + 0.05, f'{s:.1f}x', ha='center', va='bottom', fontsize=8, fontweight='bold')

plt.tight_layout()
plt.savefig('fibonacci_benchmark.png', dpi=150)
plt.show()
print("Plot saved to fibonacci_benchmark.png")
