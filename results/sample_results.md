## Analysis

The benchmark results show that optimization benefits become more visible as matrix size increases. For the 128 x 128 case, the naive version was faster because the workload was small and optimization/parallel overhead outweighed the benefit. However, for 256 x 256 and 512 x 512 matrices, the cache-friendly implementation achieved around 1.6x speedup over the naive implementation.

The OpenMP version also improved performance for larger matrices, but the speedup was limited because this Codespaces environment only used 2 threads. This shows that parallel performance depends not only on the algorithm, but also on hardware resources, thread count, memory bandwidth, and overhead from parallel execution.

Overall, this project demonstrates how loop ordering, memory locality, and parallel execution can affect the performance of linear algebra workloads.