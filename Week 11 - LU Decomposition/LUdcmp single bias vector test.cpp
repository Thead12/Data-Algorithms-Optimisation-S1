// Week 10 - LU Decomposition 
// File contains a test for a function that solves the linear system Ax=b
// for a single bias vector b based on LU decomposition.

#include <iostream>
#include<vector>
#include<complex>
#include<cmath>

//Uncomment to remove debug
//#define NDEBUG
#include<cassert>

#include "matrix.h"
#include "LUdcmp.h"

void LineBreak() {
    std::cout << '\n';
}

template<typename T>
void Print(T message) {
    std::cout << message << std::endl;
}

template<typename T>
void Print(std::string message, T data)
{
    std::cout << message << data << std::endl;
}

typedef Dense::Matrix<double> Matrix;

int main()
{    
    std::vector<std::vector<double>> vectorA= {
        {1, 1, 1},
        {1, 2, 4},
        {1, 3, 9}
    };

    std::vector<double> b = { 1, -1, 1 };
    
    Print("Original matrix: ");
    Matrix matrixA(vectorA);
    matrixA.Print();
    LineBreak();

    Print("LU decomposition: ");
    LUdcmp::LUdcmp LU(matrixA);
    LU.lu.Print();
    LineBreak();

    Print("b vector: ");
    for (int i = 0; i < b.size(); i++) std::cout << b[i] << ", " << std::endl;
    LineBreak();

    Print("x solution vector: ");
    LU.solve(b, b);
    for (int i = 0; i < b.size(); i++) std::cout << b[i] << ", " << std::endl;
    LineBreak();

    Print("Multiplication test: A*x = b");
    (Matrix(vectorA) * Matrix(b)).Print();
}
