//Various tests for Week 6-7's CRS SparseMatrix class

#include <iostream>
#include<vector>

//Uncomment to remove debug
//#define NDEBUG
#include<cassert>

#include "matrix.h"
#include "LinkedListSparseMatrix.h"
#include "CSRSparseMatrix.h"

void LineBreak() {
    std::cout << '\n';
}

void Print(std::string message) {
    std::cout << message << std::endl;
}


int main() {
    std::vector<std::vector<double>> denseVectorA = {
        {1, 0, 0},
        {0, 2, 0},
        {0, 0, 3},
        {0, 0, 0}
    };

    std::vector<std::vector<double>> denseVectorB = {
       {1, 0, 0, 0},
       {0, 2, 0, 0},
       {0, 0, 3, 0}
    };

    Dense::Matrix<double> denseMatrixA(denseVectorA);
    Dense::Matrix<double> denseMatrixB(denseVectorB);

    CSR::SparseMatrix<double> sparseMatrixA(denseVectorA);
    CSR::SparseMatrix<double> sparseMatrixB(denseVectorB);

    CSR::SparseMatrix<double> productTest = sparseMatrixA.multiply(sparseMatrixB);

    Print("Sparse matrix A");
    sparseMatrixA.printDense();
    LineBreak();
    Print("Sparse matrix B");
    sparseMatrixB.printDense();
    LineBreak();
    Print("A x B = ");
    productTest.printDense();
    LineBreak();
    Print("Sparse form: ");
    productTest.printSparse();
    LineBreak();
    Print("Addition test: ");
    productTest.add(productTest).printDense();
    LineBreak();
    Print("Sparse form: ");
    productTest.add(productTest).printSparse();
    LineBreak();
    Print("Subtraction test: ");
    productTest.subtract(productTest).printDense();
    LineBreak();
    Print("Sparse form: ");
    productTest.subtract(productTest).printSparse();
    LineBreak();
    productTest.set(3, 3, 1);
    productTest.printDense();
}
