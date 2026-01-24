import time
import sys
import os

# Add parent directory to path
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..'))

from python_impl.insertion_sort import insertion_sort
from python_impl.merge_sort import merge_sort
from python_impl.heap_sort import heap_sort
from python_impl.quick_sort import quick_sort


def load_dataset(filename):
    """Load numbers from a file into a list."""
    with open(filename, 'r') as f:
        return [int(line.strip()) for line in f]


def benchmark_sorting_algorithms():
    """Benchmark all sorting algorithms on all datasets."""
    
    datasets = [
        ("../dataset/small/random_100.txt", 100),
        ("../dataset/small/random_500.txt", 500),
        ("../dataset/small/random_1000.txt", 1000),
        ("../dataset/medium/random_5000.txt", 5000),
        ("../dataset/medium/random_10000.txt", 10000),
        ("../dataset/large/random_50000.txt", 50000),
        ("../dataset/large/random_100000.txt", 100000),
        ("../dataset/large/random_500000.txt", 500000)
    ]
    
    algorithms = [
        ("insertion_sort", lambda arr: insertion_sort(arr)),
        ("merge_sort", lambda arr: merge_sort(arr, 0, len(arr) - 1)),
        ("heap_sort", lambda arr: heap_sort(arr)),
        ("quick_sort", lambda arr: quick_sort(arr, 0, len(arr) - 1))
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


def write_results_to_tsv(results, filename='results.tsv'):
    """Write results to a TSV file."""
    with open(filename, 'w') as f:
        # Write header
        f.write("algorithm\tn\ttime\n")
        
        # Write data
        for result in results:
            f.write(f"{result['algorithm']}\t{result['n']}\t{result['time']:.6f}\n")
    
    print(f"\nResults written to {filename}")


if __name__ == "__main__":
    print("Starting benchmark...")
    results = benchmark_sorting_algorithms()
    write_results_to_tsv(results)
    print("Benchmark complete!")
