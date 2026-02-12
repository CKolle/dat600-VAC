# How to use

Compile the C code with:

```bash
clang -O3 -o bench_fib_c bench_fib_c.c
```

Compile the Rust code with:

```bash
rustc -C opt-level=3  -o bench_fib_rs bench_fib_rs.rs
```

Then run python in the same folder and execute the following code:

```bash
python plot_fib.py
```