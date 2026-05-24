#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>
#include <cmath>

#ifdef _OPENMP
#include <omp.h>
#endif

using Matrix = std::vector<std::vector<double>>;

Matrix createRandomMatrix(int size) {
    Matrix matrix(size, std::vector<double>(size));
    std::mt19937 generator(42);
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = distribution(generator);
        }
    }
    return matrix;
}

Matrix createZeroMatrix(int size) {
    return Matrix(size, std::vector<double>(size, 0.0));
}

Matrix multiplyNaive(const Matrix& A, const Matrix& B) {
    int size = A.size();
    Matrix C = createZeroMatrix(size);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            for (int k = 0; k < size; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

Matrix multiplyOptimized(const Matrix& A, const Matrix& B) {
    int size = A.size();
    Matrix C = createZeroMatrix(size);

    for (int i = 0; i < size; ++i) {
        for (int k = 0; k < size; ++k) {
            double temp = A[i][k];
            for (int j = 0; j < size; ++j) {
                C[i][j] += temp * B[k][j];
            }
        }
    }
    return C;
}

Matrix multiplyOpenMP(const Matrix& A, const Matrix& B) {
    int size = A.size();
    Matrix C = createZeroMatrix(size);

#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (int i = 0; i < size; ++i) {
        for (int k = 0; k < size; ++k) {
            double temp = A[i][k];
            for (int j = 0; j < size; ++j) {
                C[i][j] += temp * B[k][j];
            }
        }
    }
    return C;
}

bool matricesAreClose(const Matrix& A, const Matrix& B, double tolerance = 1e-6) {
    int size = A.size();

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (std::fabs(A[i][j] - B[i][j]) > tolerance) {
                return false;
            }
        }
    }
    return true;
}

template <typename Function>
double benchmark(Function multiplyFunction, const Matrix& A, const Matrix& B, Matrix& result) {
    auto start = std::chrono::high_resolution_clock::now();
    result = multiplyFunction(A, B);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    return elapsed.count();
}

void runBenchmark(int size) {
    std::cout << "Matrix size: " << size << " x " << size << std::endl;

    Matrix A = createRandomMatrix(size);
    Matrix B = createRandomMatrix(size);

    Matrix resultNaive;
    Matrix resultOptimized;
    Matrix resultOpenMP;

    double naiveTime = benchmark(multiplyNaive, A, B, resultNaive);
    double optimizedTime = benchmark(multiplyOptimized, A, B, resultOptimized);
    double openmpTime = benchmark(multiplyOpenMP, A, B, resultOpenMP);

    bool optimizedCorrect = matricesAreClose(resultNaive, resultOptimized);
    bool openmpCorrect = matricesAreClose(resultNaive, resultOpenMP);

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Naive time:     " << naiveTime << " seconds" << std::endl;
    std::cout << "Optimized time: " << optimizedTime << " seconds" << std::endl;
    std::cout << "OpenMP time:    " << openmpTime << " seconds" << std::endl;

    std::cout << "Optimized correct: " << (optimizedCorrect ? "Yes" : "No") << std::endl;
    std::cout << "OpenMP correct:    " << (openmpCorrect ? "Yes" : "No") << std::endl;

    if (optimizedTime > 0) {
        std::cout << "Optimized speedup vs naive: "
                  << naiveTime / optimizedTime << "x" << std::endl;
    }

    if (openmpTime > 0) {
        std::cout << "OpenMP speedup vs naive:    "
                  << naiveTime / openmpTime << "x" << std::endl;
    }

#ifdef _OPENMP
    std::cout << "OpenMP enabled with " << omp_get_max_threads() << " threads" << std::endl;
#else
    std::cout << "OpenMP not enabled. OpenMP version ran as normal single-threaded C++." << std::endl;
#endif

    std::cout << "--------------------------------------------------" << std::endl;
}

int main() {
    std::cout << "Parallel Matrix Multiplication Benchmark" << std::endl;
    std::cout << "==================================================" << std::endl;

    std::vector<int> sizes = {128, 256, 512};

    for (int size : sizes) {
        runBenchmark(size);
    }

    return 0;
}
