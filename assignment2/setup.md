# Setup

On linux or macOS systems make sure you have CMake and a C compiler installed that supports C23. And make sure you have CMake version 3.5 or higher.
Look up your distribution's package manager for installation instructions.

Each task has its own directory with a separate CMakeLists.txt.

## Task 1 - Set (AVL Tree)

```bash
cd task1
cmake -B build
cmake --build build
./build/set_tests
```

## Task 2 - Disjoint Set (Union-Find)

```bash
cd task2
cmake -B build
cmake --build build
./build/disjoint_set_tests
```

## Task 3 - Dynamic and Greedy Algorithms (Fibonacci)

```bash
cd task3
cmake -B build
cmake --build build
```