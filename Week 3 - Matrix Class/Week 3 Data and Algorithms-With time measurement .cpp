#include <iostream>
#include <vector>
#include <cassert>
#include <chrono>

#include "matrix.h"

int main() {

    const int matrixSize = pow(2, 6);
    // Loops through increasing subproblem sizes
    for (int i = 1; i <= matrixSize/2; i++)
    {
        // Set the matrix size for testing
        
        // Generate random matrices
        Dense::Matrix<double> matrixA(matrixSize, matrixSize, 1.0);
        Dense::Matrix<double> matrixB(matrixSize, matrixSize, 2.0);
        Dense::Matrix<double> resultMatrix(matrixSize, matrixSize, 0.0);

        // Measure execution time for DivideAndConquer
        auto start_time_dc = std::chrono::high_resolution_clock::now();
        resultMatrix = matrixA.Conquer(matrixB, i, matrixSize);
        auto end_time_dc = std::chrono::high_resolution_clock::now();
        auto duration_dc = std::chrono::duration_cast<std::chrono::microseconds>(end_time_dc - start_time_dc);

        std::cout << duration_dc.count() << std::endl;
    }
}
