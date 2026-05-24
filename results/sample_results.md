## Analysis
The optimized implementation reached up to 1.66x speedup over the naive implementation for the 512 x 512 matrix size. The benchmark results show that optimization benefits became more visible as matrix size increased. For the 128 x 128 case, the naive version was faster because the workload was small and optimization/parallel overhead outweighed the benefit.

The OpenMP version also improved performance for larger matrices, but speedup was limited by the 2-thread Codespaces environment. This shows that parallel performance depends not only on the algorithm, but also on hardware resources, thread count, memory bandwidth, and overhead from parallel execution.

This project demonstrates how loop ordering, memory locality, and parallel execution can affect the performance of linear algebra workloads.