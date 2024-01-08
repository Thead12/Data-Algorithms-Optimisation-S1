#include <iostream>
#include <vector>
#include <cassert>
#include <chrono>

#include "matrix.h"
#include "CSRSparseMatrix.h"
#include "LinkedListSparseMatrix.h"

using namespace std;

// Test vector for intialisation: More sparse then vectorB
vector<vector<double>> vectorA = {
    {0, 0, 0, 0},
    {1, 0, 0, 4},
    {0, 0, 0, 0},
    {0, 7, 0, 0}
};

// Test vector for intialisation: More dense then vectorA
vector<vector<double>> vectorB = {
    {0, 0, 2, 0},
    {4, 0, 0, 5},
    {0, 7, 0, 0},
    {0, 0, 9, 0}
};

// Function to test the efficiency of CSR Sparse Matrix addition
void testCSRSparseMatrixAddition() {
    // Create CSR Sparse Matrices A and B

    // Test speed of initialisation A
    auto start_time_dc = std::chrono::high_resolution_clock::now();
    CSR::SparseMatrix<double> matrixA(vectorA);
    auto end_time_dc = std::chrono::high_resolution_clock::now();
    auto duration_dc = std::chrono::duration_cast<std::chrono::microseconds>(end_time_dc - start_time_dc);
    cout << "CSR Sparse Matrix Initialisation time - vectorA: " << duration_dc.count() << " microseconds" << endl;

    //Test speed of initialisation B
    start_time_dc = std::chrono::high_resolution_clock::now();
    CSR::SparseMatrix<double> matrixB(vectorB);
    end_time_dc = std::chrono::high_resolution_clock::now();
    duration_dc = std::chrono::duration_cast<std::chrono::microseconds>(end_time_dc - start_time_dc);
    cout << "CSR Sparse Matrix Initialisation time - vectorB: " << duration_dc.count() << " microseconds" << endl;

    //Test speed setting values
    start_time_dc = std::chrono::high_resolution_clock::now();
    matrixA.set(0, 0, 1);
    matrixA.set(1, 1, 1);
    matrixA.set(2, 2, 1);
    end_time_dc = std::chrono::high_resolution_clock::now();
    duration_dc = std::chrono::duration_cast<std::chrono::microseconds>(end_time_dc - start_time_dc);
    cout << "CSR Sparse Matrix time taken to set 3 non zero values: " << duration_dc.count() << " microseconds" << endl;

    //Test speed setting zero values
    start_time_dc = std::chrono::high_resolution_clock::now();
    matrixA.set(0, 0, 0);
    matrixA.set(1, 1, 0);
    matrixA.set(2, 2, 0);
    end_time_dc = std::chrono::high_resolution_clock::now();
    duration_dc = std::chrono::duration_cast<std::chrono::microseconds>(end_time_dc - start_time_dc);
    cout << "CSR Sparse Matrix time taken to set 3 zero values: " << duration_dc.count() << " microseconds" << endl;

    //Test speed getting non zero values
    start_time_dc = std::chrono::high_resolution_clock::now();
    matrixA.get(1, 0);
    matrixA.get(1, 3);
    matrixA.get(3, 1);
    end_time_dc = std::chrono::high_resolution_clock::now();
    duration_dc = std::chrono::duration_cast<std::chrono::microseconds>(end_time_dc - start_time_dc);
    cout << "CSR Sparse Matrix time taken to get 3 non zero values: " << duration_dc.count() << " microseconds" << endl;

    //Test speed getting zero values
    start_time_dc = std::chrono::high_resolution_clock::now();
    matrixA.get(1, 1);
    matrixA.get(2, 3);
    matrixA.get(3, 2);
    end_time_dc = std::chrono::high_resolution_clock::now();
    duration_dc = std::chrono::duration_cast<std::chrono::microseconds>(end_time_dc - start_time_dc);
    cout << "CSR Sparse Matrix time taken to get 3 zero values: " << duration_dc.count() << " microseconds" << endl;

    // Measure the time taken for addition
    start_time_dc = std::chrono::high_resolution_clock::now();
    CSR::SparseMatrix<double> result = matrixA.add(matrixB);
    end_time_dc = std::chrono::high_resolution_clock::now();
    duration_dc = std::chrono::duration_cast<std::chrono::microseconds>(end_time_dc - start_time_dc);
    cout << "CSR Sparse Matrix Addition Time: " << duration_dc.count() << " microseconds" << endl;
}

// Function to test the efficiency of LinkedList Sparse Matrix addition
void testLinkedListSparseMatrixAddition() {
    // Create LinkedList Sparse Matrices A and B

    // Test speed of initialisation A
    auto start_time_dc = std::chrono::high_resolution_clock::now();
    LinkedList::SparseMatrix<double> matrixA(vectorA);
    auto end_time_dc = std::chrono::high_resolution_clock::now();
    auto duration_dc = std::chrono::duration_cast<std::chrono::microseconds>(end_time_dc - start_time_dc);
    cout << "LinkedList Sparse Matrix Initialisation time - vectorA: " << duration_dc.count() << " microseconds" << endl;

    //Test speed of initialisation B
    start_time_dc = std::chrono::high_resolution_clock::now();
    LinkedList::SparseMatrix<double> matrixB(vectorB);
    end_time_dc = std::chrono::high_resolution_clock::now();
    duration_dc = std::chrono::duration_cast<std::chrono::microseconds>(end_time_dc - start_time_dc);
    cout << "LinkedList Sparse Matrix Initialisation time - vectorB: " << duration_dc.count() << " microseconds" << endl;

    //Test speed setting values
    start_time_dc = std::chrono::high_resolution_clock::now();
    matrixA.set(0, 0, 1);
    matrixA.set(1, 1, 1);
    matrixA.set(2, 2, 1);
    end_time_dc = std::chrono::high_resolution_clock::now();
    duration_dc = std::chrono::duration_cast<std::chrono::microseconds>(end_time_dc - start_time_dc);
    cout << "LinkedList Sparse Matrix time taken to set 3 non zero values: " << duration_dc.count() << " microseconds" << endl;

    //Test speed setting zero values
    start_time_dc = std::chrono::high_resolution_clock::now();
    matrixA.Remove(0, 0);
    matrixA.Remove(1, 1);
    matrixA.Remove(2, 2);
    end_time_dc = std::chrono::high_resolution_clock::now();
    duration_dc = std::chrono::duration_cast<std::chrono::microseconds>(end_time_dc - start_time_dc);
    cout << "LinkedList Sparse Matrix time taken to set 3 zero values: " << duration_dc.count() << " microseconds" << endl;

    //Test speed getting non zero values
    start_time_dc = std::chrono::high_resolution_clock::now();
    matrixA.get(1, 0);
    matrixA.get(1, 3);
    matrixA.get(3, 1);
    end_time_dc = std::chrono::high_resolution_clock::now();
    duration_dc = std::chrono::duration_cast<std::chrono::microseconds>(end_time_dc - start_time_dc);
    cout << "LinkedList Sparse Matrix time taken to get 3 non zero values: " << duration_dc.count() << " microseconds" << endl;

    //Test speed getting zero values
    start_time_dc = std::chrono::high_resolution_clock::now();
    matrixA.get(1, 1);
    matrixA.get(2, 3);
    matrixA.get(3, 2);
    end_time_dc = std::chrono::high_resolution_clock::now();
    duration_dc = std::chrono::duration_cast<std::chrono::microseconds>(end_time_dc - start_time_dc);
    cout << "LinkedList Sparse Matrix time taken to get 3 zero values: " << duration_dc.count() << " microseconds" << endl;

    // Measure the time taken for addition
    start_time_dc = std::chrono::high_resolution_clock::now();
    LinkedList::SparseMatrix<double> result = matrixA.AddSparse(matrixB);
    end_time_dc = std::chrono::high_resolution_clock::now();
    duration_dc = std::chrono::duration_cast<std::chrono::microseconds>(end_time_dc - start_time_dc);
    cout << "LinkedList Sparse Matrix Addition time: " << duration_dc.count() << " microseconds" << endl;
}

int main() {
    // Test CSR Sparse Matrix Addition
    testCSRSparseMatrixAddition();
    std::cout << std::endl;
    // Test LinkedList Sparse Matrix Addition
    testLinkedListSparseMatrixAddition();
}
