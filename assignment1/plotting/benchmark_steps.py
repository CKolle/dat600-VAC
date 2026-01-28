"""
Benchmark step counts for sorting algorithms.
Generates results/results_steps.tsv for Task 1 analysis.
"""

import sys
import os

sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..'))
from python_impl.sortering import insertion_sort, merge_sort, heap_sort, quick_sort

def load_dataset(filename):
    with open(filename, 'r') as f:
        return [int(line.strip()) for line in f]


def run_step_benchmarks():
    dataset_files = [
        ("../dataset/small/random_10.txt", 10),
        ("../dataset/small/random_25.txt", 25),
        ("../dataset/small/random_75.txt", 75),
        ("../dataset/small/random_100.txt", 100),
        ("../dataset/small/random_250.txt", 250),
        ("../dataset/small/random_500.txt", 500),
        ("../dataset/small/random_750.txt", 750),
        ("../dataset/small/random_1000.txt", 1000)
    ]
    
    algorithms = {
        'insertion': insertion_sort,
        'merge': merge_sort,
        'heap': heap_sort,
        'quick': quick_sort
    }
    
    results = []
    
    for dataset_path, n in dataset_files:
        print(f"Processing n={n}")
        
        # Average case: load from dataset file
        data_random = load_dataset(dataset_path)
        
        # Worst case: reverse sorted
        data_worst = sorted(data_random, reverse=True)
        
        for algo_name, algo_func in algorithms.items():
            # Average case
            data_copy = data_random.copy()
            if algo_name in ['merge', 'quick']:
                steps_avg = algo_func(data_copy, 0, len(data_copy) - 1)
            else:
                steps_avg = algo_func(data_copy)
            
            results.append({
                'algorithm': algo_name,
                'n': n,
                'case': 'average',
                'steps': steps_avg
            })
            
            # Worst case
            data_copy = data_worst.copy()
            if algo_name in ['merge', 'quick']:
                steps_worst = algo_func(data_copy, 0, len(data_copy) - 1)
            else:
                steps_worst = algo_func(data_copy)
            
            results.append({
                'algorithm': algo_name,
                'n': n,
                'case': 'worst',
                'steps': steps_worst
            })
    
    return results


def write_results_to_tsv(results, filename='../results/results_steps.tsv'):
    os.makedirs(os.path.dirname(filename), exist_ok=True)
    
    with open(filename, 'w') as f:
        f.write("algorithm\tn\tcase\tsteps\n")
        for result in results:
            f.write(f"{result['algorithm']}\t{result['n']}\t{result['case']}\t{result['steps']}\n")
    
    print(f"\nResults written to {os.path.abspath(filename)}")


if __name__ == "__main__":
    print("Running step count benchmarks...")
    results = run_step_benchmarks()
    write_results_to_tsv(results)
    print("Done!")
