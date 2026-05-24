# Parallel Matrix Multiplication Benchmark

This project benchmarks different implementations of matrix multiplication in C++ to study performance tradeoffs in linear algebra workloads. Matrix multiplication is a core operation in scientific computing, machine learning, graphics, and high-performance computing.

The project compares:

1. Naive matrix multiplication
2. Cache-friendly optimized matrix multiplication
3. OpenMP parallel matrix multiplication

The goal is to understand how algorithm structure, memory access patterns, and parallel execution affect runtime performance.

## Why This Project

Modern AI and scientific computing workloads rely heavily on linear algebra operations. Although production systems often use highly optimized libraries and GPU acceleration, implementing matrix multiplication from scratch is a useful way to understand:

- Algorithmic complexity
- Cache locality
- Memory access patterns
- Parallel programming
- Runtime benchmarking
- Performance scaling across input sizes

This project was built as a small performance-oriented C++ project to connect mathematical foundations with systems-level software optimization.

## Technologies Used

- C++
- OpenMP
- Makefile
- Linux/macOS terminal
- High-resolution timing with `std::chrono`

## Implementations

### 1. Naive Matrix Multiplication

The naive implementation uses the traditional triple-loop structure:

```cpp
for i
  for j
    for k
      C[i][j] += A[i][k] * B[k][j]
