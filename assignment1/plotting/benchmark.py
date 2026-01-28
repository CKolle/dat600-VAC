import time
import sys
import os

# Add parent directory to path
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..'))

from python_impl.sortering import (
    insertion_sort,
    merge_sort, 
    heap_sort,
    quick_sort
)


def load_dataset(filename):
    with open(filename, 'r') as f:
        return [int(line.strip()) for line in f]


def benchmark_sorting_algorithms():
    
    datasets = [
        ("../dataset/small/random_10.txt", 10),
        ("../dataset/small/random_25.txt", 25),
        ("../dataset/small/random_75.txt", 75),
        ("../dataset/small/random_100.txt", 100),
        ("../dataset/small/random_250.txt", 250),
        ("../dataset/small/random_500.txt", 500),
        ("../dataset/small/random_750.txt", 750),
        ("../dataset/small/random_1000.txt", 1000),
        ("../dataset/medium/random_2500.txt", 2500),
        ("../dataset/medium/random_5000.txt", 5000),
        ("../dataset/medium/random_7500.txt", 7500),
        ("../dataset/medium/random_10000.txt", 10000),
        ("../dataset/large/random_25000.txt", 25000),
        ("../dataset/large/random_50000.txt", 50000),
        ("../dataset/large/random_75000.txt", 75000),
        ("../dataset/large/random_100000.txt", 100000),
        ("../dataset/large/random_250000.txt", 250000),
        ("../dataset/large/random_500000.txt", 500000)
    ]
    
    algorithms = [
        ("insertion", lambda arr: insertion_sort(arr)),
        ("merge", lambda arr: merge_sort(arr, 0, len(arr) - 1)),
        ("heap", lambda arr: heap_sort(arr)),
        ("quick", lambda arr: quick_sort(arr, 0, len(arr) - 1))
    ]
    
    results = []
    
    for dataset_path, n in datasets:
        print(f"Processing dataset: {dataset_path} (n={n})")
        
        for algo_name, algo_func in algorithms:
            print(f"  Running {algo_name}...")
            
            # Load fresh data for each algorithm
            data = load_dataset(dataset_path)
            
            # Measure time
            start_time = time.time()
            algo_func(data)
            end_time = time.time()
            
            elapsed_time = end_time - start_time
            results.append({
                'algorithm': algo_name,
                'n': n,
                'time': elapsed_time
            })
            print(f"    Time: {elapsed_time:.6f} seconds")
    
    return results


def write_results_to_tsv(results, filename='../results/results_python.tsv'):
    with open(filename, 'w') as f:
        f.write("algorithm\tn\ttime\n")
        
        for result in results:
            f.write(f"{result['algorithm']}\t{result['n']}\t{result['time']:.6f}\n")
    
    print(f"\nResults written to {os.path.abspath(filename)}")


if __name__ == "__main__":
    print("Starting benchmark...")
    results = benchmark_sorting_algorithms()
    write_results_to_tsv(results)
    print("Benchmark complete!")
