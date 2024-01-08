// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

#define SIZE 1024
#define INDEX SIZE/2

namespace matrix {

    //Initializing submatrices
    vector<double> rows(INDEX, 0);

    vector<vector<double>> A00(INDEX, rows);
    vector<vector<double>> A01(INDEX, rows);
    vector<vector<double>> A10(INDEX, rows);
    vector<vector<double>> A11(INDEX, rows);

    vector<vector<double>> B00(INDEX, rows);
    vector<vector<double>> B01(INDEX, rows);
    vector<vector<double>> B10(INDEX, rows);
    vector<vector<double>> B11(INDEX, rows);

    vector<vector<double>> C00(INDEX, rows);
    vector<vector<double>> C01(INDEX, rows);
    vector<vector<double>> C10(INDEX, rows);
    vector<vector<double>> C11(INDEX, rows);

    vector<vector<double>> M1(INDEX, rows);
    vector<vector<double>> M2(INDEX, rows);
    vector<vector<double>> M3(INDEX, rows);
    vector<vector<double>> M4(INDEX, rows);
    vector<vector<double>> M5(INDEX, rows);
    vector<vector<double>> M6(INDEX, rows);
    vector<vector<double>> M7(INDEX, rows);
}

void NaiveMultiplication(const vector<vector<double>>& matrixA, const vector<vector<double>>& matrixB, vector<vector<double>>& result, int size)
{
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
}

void AddMatrices(const vector<vector<double>>& matrixA, const vector<vector<double>>& matrixB, vector<vector<double>>& result, int size)
{
    result.resize(size, vector<double>(size, 0.0));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }
}

void SubMatrices(const vector<vector<double>>& matrixA, const vector<vector<double>>& matrixB, vector<vector<double>>& result, int size)
{
    result.resize(size, vector<double>(size, 0.0));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = matrixA[i][j] - matrixB[i][j];
        }
    }
}

vector<vector<double>> DivideAndConquer(const vector<vector<double>>& matrixA, const vector<vector<double>>& matrixB, int size) {
    //Creating the final matrix which will contain the completed multiplication
    vector<double> finalRows(size, 0);
    vector<vector<double> > finalMatrix(size, finalRows);

    //Break statement to end recursion and begin back through stack
    if (size <= 2) {
        NaiveMultiplication(matrixA, matrixB, finalMatrix, size);
    }
    else {
        //Dividing size by 2
        int index = (size / 2);

        //Initializing submatrices
        vector<double> rows(index, 0);
        vector<vector<double> > matrixC00(index, rows);
        vector<vector<double> > matrixC01(index, rows);
        vector<vector<double> > matrixC10(index, rows);
        vector<vector<double> > matrixC11(index, rows);

        vector<vector<double> > matrixA00(index, rows);
        vector<vector<double> > matrixA01(index, rows);
        vector<vector<double> > matrixA10(index, rows);
        vector<vector<double> > matrixA11(index, rows);

        vector<vector<double> > matrixB00(index, rows);
        vector<vector<double> > matrixB01(index, rows);
        vector<vector<double> > matrixB10(index, rows);
        vector<vector<double> > matrixB11(index, rows);

        //Filling submatrices
        for (int i = 0; i < index; i++) {
            for (int j = 0; j < index; j++) {

                matrixA00[i][j] = matrixA[i][j];
                matrixA01[i][j] = matrixA[i][j + index];
                matrixA10[i][j] = matrixA[i + index][j];
                matrixA11[i][j] = matrixA[i + index][j + index];

                matrixB00[i][j] = matrixB[i][j];
                matrixB01[i][j] = matrixB[i][j + index];
                matrixB10[i][j] = matrixB[i + index][j];
                matrixB11[i][j] = matrixB[i + index][j + index];
            }
        }

        //Start of recursion
        //c00 = a00*b00 + a01*b10
        AddMatrices(DivideAndConquer(matrixA00, matrixB00, index), DivideAndConquer(matrixA01, matrixB10, index), matrixC00, index);
        //c01 = a00*b01 + a01*b11                                                        
        AddMatrices(DivideAndConquer(matrixA00, matrixB01, index), DivideAndConquer(matrixA01, matrixB11, index), matrixC01, index);
        //c10 = a10*b00 + a11*b01                                                 
        AddMatrices(DivideAndConquer(matrixA10, matrixB00, index), DivideAndConquer(matrixA11, matrixB10, index), matrixC10, index);
        //c11 = a10*b01 + a11*b11                                             
        AddMatrices(DivideAndConquer(matrixA10, matrixB01, index), DivideAndConquer(matrixA11, matrixB11, index), matrixC11, index);

        //Returning values into finalMatrix
        for (int i = 0; i < index; i++) {
            for (int j = 0; j < index; j++) {
                finalMatrix[i][j] = matrixC00[i][j];
                finalMatrix[i][j + index] = matrixC01[i][j];
                finalMatrix[i + index][j] = matrixC10[i][j];
                finalMatrix[i + index][j + index] = matrixC11[i][j];
            }
        }
    }

    return finalMatrix;
}

void DivideAndStrassen(vector<vector<double>>& matrixA, vector<vector<double>>& matrixB, vector<vector<double>>& matrixC, int size) {
    using namespace matrix;

    //Dividing size by 2
    int index = (size / 2);

    //Break statement to end recursion and begin back through stack
    if (size <= 2) {
        NaiveMultiplication(matrixA, matrixB, matrixC, size);
    }
    else {
        //Filling submatrices
        for (int i = 0; i < index; i++) {
            for (int j = 0; j < index; j++) {

                A00[i][j] = matrixA[i][j];
                A01[i][j] = matrixA[i][j + index];
                A10[i][j] = matrixA[i + index][j];
                A11[i][j] = matrixA[i + index][j + index];

                B00[i][j] = matrixB[i][j];
                B01[i][j] = matrixB[i][j + index];
                B10[i][j] = matrixB[i + index][j];
                B11[i][j] = matrixB[i + index][j + index];
            }
        }

        // Calculating M
        SubMatrices(B01, B11, M1, index);
        DivideAndStrassen(A00, M1, C00, index);

        AddMatrices(A00, A01, M2, index);
        DivideAndStrassen(M2, B00, C01, index);

        AddMatrices(A10, A11, M3, index);
        DivideAndStrassen(M3, B00, C10, index);

        SubMatrices(B10, B00, M4, index);
        DivideAndStrassen(A11, M4, C00, index);

        AddMatrices(B00, B11, M5, index);
        AddMatrices(A00, A11, M6, index);
        DivideAndStrassen(M6, M5, C00, index);

        SubMatrices(B01, B11, M7, index);
        AddMatrices(A10, A11, M1, index);
        DivideAndStrassen(M1, M7, C11, index);

        //Returning values into matrixC
        for (int i = 0; i < index; i++) {
            for (int j = 0; j < index; j++) {
                matrixC[i][j] = C00[i][j];
                matrixC[i][j + index] = C01[i][j];
                matrixC[i + index][j] = C10[i][j];
                matrixC[i + index][j + index] = C11[i][j];
            }
        }
    }
}

void printMatrix(vector<vector<double>> matrix, int size) {
    for (int i = 0; i <= size - 1; i++) {
        for (int j = 0; j <= size - 1; j++) {
            cout << matrix[i][j] << ",";
        }
        cout << endl;
    }
}

int main()
{
    // Loop to iterate through the different matrix sizes
    for (int i = 0; i <= 10; i++)
    {
        // Set the matrix size for testing
        const int matrixSize = pow(2, i);  // You can change this to test different matrix sizes

        // Generate random matrices
        std::vector<std::vector<double>> matrixA(matrixSize, std::vector<double>(matrixSize, 1.0));
        std::vector<std::vector<double>> matrixB(matrixSize, std::vector<double>(matrixSize, 2.0));
        std::vector<std::vector<double>> resultMatrix(matrixSize, std::vector<double>(matrixSize, 0.0));

        // Measure execution time for DivideAndConquer
        auto start_time_dc = std::chrono::high_resolution_clock::now();
        DivideAndStrassen(matrixA, matrixB, resultMatrix, matrixSize);
        auto end_time_dc = std::chrono::high_resolution_clock::now();
        auto duration_dc = std::chrono::duration_cast<std::chrono::microseconds>(end_time_dc - start_time_dc);

        std::cout << duration_dc.count() << std::endl;
    }

    //Test vlock for Naive

    // Test block for Divide and Conquer
    /*
    // Generate random matrices
    std::vector<std::vector<double>> matrixA(matrixSize, std::vector<double>(matrixSize, 1.0));
    std::vector<std::vector<double>> matrixB(matrixSize, std::vector<double>(matrixSize, 2.0));
    std::vector<std::vector<double>> resultMatrix(matrixSize, std::vector<double>(matrixSize, 0.0));

    // Measure execution time for DivideAndConquer
    auto start_time_dc = std::chrono::high_resolution_clock::now();
    DivideAndConquer(matrixA, matrixB, matrixSize);
    auto end_time_dc = std::chrono::high_resolution_clock::now();
    auto duration_dc = std::chrono::duration_cast<std::chrono::microseconds>(end_time_dc - start_time_dc);

    std::cout << duration_dc.count() << std::endl;
    */

    // Test block for Strassen
    /*
    // Set the matrix size for testing
    const int matrixSize = SIZE;  // You can change this to test different matrix sizes

    // Generate random matrices
    std::vector<std::vector<double>> matrixA(matrixSize, std::vector<double>(matrixSize, 1.0));
    std::vector<std::vector<double>> matrixB(matrixSize, std::vector<double>(matrixSize, 2.0));
    std::vector<std::vector<double>> resultMatrix(matrixSize, std::vector<double>(matrixSize, 0.0));

    // Measure execution time for DivideAndStrassen
    auto start_time_strassen = std::chrono::high_resolution_clock::now();
    DivideAndStrassen(matrixA, matrixB, resultMatrix, matrixSize);
    auto end_time_strassen = std::chrono::high_resolution_clock::now();
    auto duration_strassen = std::chrono::duration_cast<std::chrono::microseconds>(end_time_strassen - start_time_strassen);

    std::cout << duration_strassen.count() <<  std::endl;
    */
    }
