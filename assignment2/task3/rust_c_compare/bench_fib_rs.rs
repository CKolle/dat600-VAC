use std::time::Instant;

#[inline(never)]
fn fibonacci_bu(n: u32) -> u64 {
    if n <= 1 {
        return n as u64;
    }

    (2..n + 1).fold((0u64, 1u64), |(a, b), _| (b, a.wrapping_add(b))).1
}

fn main() {
    let sizes: Vec<u32> = vec![10, 50, 100, 500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000];
    let iterations = 10000;

    for &n in &sizes {
        let start = Instant::now();
        let mut result: u64 = 0;
        for _ in 0..iterations {
            result = fibonacci_bu(n);
            std::hint::black_box(result);
        }
        let elapsed = start.elapsed();
        let avg_us = elapsed.as_nanos() as f64 / iterations as f64 / 1000.0;
        println!("{},{:.4}", n, avg_us);
    }
}
