"""
Generate all plots for the LaTeX report.
Saves PNG files to results/ directory.
"""

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt


def load_step_results():
    return pd.read_csv('../results/results_steps.tsv', sep='\t')


def load_time_results():
    df_c = pd.read_csv('../results/results_c.tsv', sep='\t')
    df_python = pd.read_csv('../results/results_python.tsv', sep='\t')
    return df_c, df_python


def plot_task1_avg_vs_worst(df_steps):
    fig, axes = plt.subplots(2, 2, figsize=(14, 10))
    
    algos = ['insertion', 'merge', 'heap', 'quick']
    sizes = sorted(df_steps['n'].unique())
    
    for ax, algo in zip(axes.flat, algos):
        data_avg = df_steps[(df_steps['algorithm'] == algo) & (df_steps['case'] == 'average')]
        data_worst = df_steps[(df_steps['algorithm'] == algo) & (df_steps['case'] == 'worst')]
        
        ax.plot(sizes, data_avg['steps'].values, 'o-', color='blue', linewidth=2, label='Average case (random)')
        ax.plot(sizes, data_worst['steps'].values, 's--', color='red', linewidth=2, label='Worst case (reverse sorted)')
        
        ax.set_xlabel('Input size (n)')
        ax.set_ylabel('Number of steps')
        ax.set_title(f'{algo.capitalize()} Sort: Average vs Worst Case')
        ax.legend()
        ax.grid(True, alpha=0.3)
    
    plt.suptitle('Task 1: Average Case vs Worst Case Comparison', fontsize=14)
    plt.tight_layout()
    plt.savefig('../results/task1_avg_vs_worst.png', dpi=150, bbox_inches='tight')
    plt.close()
    print("Saved: task1_avg_vs_worst.png")


def plot_task1_all_algorithms(df_steps):
    fig, axes = plt.subplots(1, 2, figsize=(16, 6))
    
    sizes = sorted(df_steps['n'].unique())
    n_arr = np.array(sizes)
    n_squared = n_arr ** 2
    n_log_n = n_arr * np.log2(n_arr)
    
    algos = ['insertion', 'merge', 'heap', 'quick']
    
    # Left: Worst case
    ax1 = axes[0]
    for algo in algos:
        data = df_steps[(df_steps['algorithm'] == algo) & (df_steps['case'] == 'worst')]
        ax1.plot(sizes, data['steps'].values, 'o-', label=algo.capitalize(), linewidth=2, markersize=6)
    
    ax1.plot(sizes, n_squared * 0.5, '--', color='gray', alpha=0.5, label='n² (reference)')
    ax1.plot(sizes, n_log_n * 10, ':', color='gray', alpha=0.5, label='n log n (reference)')
    ax1.set_xlabel('Input size (n)')
    ax1.set_ylabel('Number of steps')
    ax1.set_title('All Algorithms - Worst Case')
    ax1.legend()
    ax1.grid(True, alpha=0.3)
    ax1.set_yscale('log')
    ax1.set_xscale('log')
    
    # Right: Average case
    ax2 = axes[1]
    for algo in algos:
        data = df_steps[(df_steps['algorithm'] == algo) & (df_steps['case'] == 'average')]
        ax2.plot(sizes, data['steps'].values, 'o-', label=algo.capitalize(), linewidth=2, markersize=6)
    
    ax2.plot(sizes, n_squared * 0.5, '--', color='gray', alpha=0.5, label='n² (reference)')
    ax2.plot(sizes, n_log_n * 10, ':', color='gray', alpha=0.5, label='n log n (reference)')
    ax2.set_xlabel('Input size (n)')
    ax2.set_ylabel('Number of steps')
    ax2.set_title('All Algorithms - Average Case (Random)')
    ax2.legend()
    ax2.grid(True, alpha=0.3)
    ax2.set_yscale('log')
    ax2.set_xscale('log')
    
    plt.suptitle('Task 1: Step Count Comparison (Log Scale)', fontsize=14)
    plt.tight_layout()
    plt.savefig('../results/task1_all_algorithms.png', dpi=150, bbox_inches='tight')
    plt.close()
    print("Saved: task1_all_algorithms.png")


def plot_all_algorithms(df, language, save=True):
    plt.figure(figsize=(10, 6))
    
    for algo in ['insertion', 'merge', 'heap', 'quick']:
        data = df[df['algorithm'] == algo]
        plt.plot(data['n'], data['time'], marker='o', linewidth=2, label=algo)
    
    plt.xlabel('n (number of elements)')
    plt.ylabel('Time (seconds)')
    plt.title(f'All Sorting Algorithms ({language})')
    plt.legend()
    plt.grid(True, alpha=0.3)
    plt.xscale('log')
    plt.yscale('log')
    if save:
        plt.savefig(f'../results/all_algorithms_{language.lower()}.png', dpi=150, bbox_inches='tight')
    plt.close()
    print(f"Saved: all_algorithms_{language.lower()}.png")


if __name__ == "__main__":
    print("Generating plots for LaTeX report...\n")
    
    # Task 1: Step count plots
    print("Task 1: Loading step count results...")
    df_steps = load_step_results()
    plot_task1_avg_vs_worst(df_steps)
    plot_task1_all_algorithms(df_steps)
    
    # Task 2: Execution time plots
    print("\nTask 2: Loading timing benchmark results...")
    df_c, df_python = load_time_results()
    
    plot_all_algorithms(df_c, 'C')
    plot_all_algorithms(df_python, 'Python')
    
    print("\nAll plots saved to results/ directory")