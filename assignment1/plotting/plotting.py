import pandas as pd

import matplotlib.pyplot as plt

def plot_time_complexity(tsv_file, x_column='n', y_column='time', title='Time Complexity Analysis'):
    
    df = pd.read_csv(tsv_file, sep='\t')
    
    plt.figure(figsize=(10, 6))
    plt.plot(df[x_column], df[y_column], marker='o', linewidth=2)
    plt.xlabel(x_column)
    plt.ylabel(y_column)
    plt.title(title)
    plt.grid(True, alpha=0.3)
    plt.show()


if __name__ == "__main__":
    plot_time_complexity('results.tsv')