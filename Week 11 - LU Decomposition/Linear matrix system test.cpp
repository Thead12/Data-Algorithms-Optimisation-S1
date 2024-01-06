// Week 11 - LU Decomposition : This file contains a test for the A*X = B algorithm using LU decomposition
//

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

    //std::vector<double> b = { 1, -1, 1 };
    Matrix b(vectorA);

    Print("Original matrix: ");
    Matrix matrixA(vectorA);
    matrixA.Print();
    LineBreak();

    Print("LU decomposition: ");
    LUdcmp::LUdcmp LU(matrixA);
    LU.lu.Print();
    LineBreak();

    Print("b matrix: ");
    b.Print();
    LineBreak();

    Print("x solution matrix: ");
    LU.solve(b, b);
    b.Print();
    LineBreak();

    Print("Multiplication test: A*x = b");
    (Matrix(vectorA) * b).Print();
}

void gaussElimination(Dense::Matrix<double> &A) // The problem is here --------------- !!!!!!!!!!!!!!
{
    int m = A.getNumRows();
    int n = A.getNumCols();

    int h = 0; // Initialise pivot row
    int k = 0; // Initialise pivot column

    while (h < m && k < n)
    {
        // Find k-th pivot
        int  i_max = h;
        for (int i = h + 1; i < m; i++)
        {
            if (abs(A(i_max, k)) < abs(A(i, k)))
            {
                i_max = i;
            }
        }

        if (A(i_max, k) == 0)
        {
            // No pivot in this column, pass to next column
            k++;
        }
        else
        {
            A.swapRows(h, i_max);
            // Do for all rows below pivot: 
            for (int i = h + 1; i < m; i++)
            {
                double f = A(i, k) / A(h, k);
                // Fill with zeros the lower part of pivot column
                A(i, k) = 0;
                // Do for all remaining elements in current row
                for (int j = k + 1; j < n; j++)
                {
                    A(i, j) = A(i, j) - A(h, j) * f;
                }
            }
            // Increase pivot row and column
            h++;
            k++;
        }
    }
}

Dense::Matrix<double> backSubstitution(Dense::Matrix<double> A)
{
    int N = A.getNumRows();
    Dense::Matrix<double> x(N, 1);

    // Start calculating from last equation up to the first
    for (int i = N-1; i >= 0; i--)
    {
        //double rhs = A(i, N);
        x(i, 0) = A(i, N); // RHS of equation

        for (int j = i+1; j < N; j++)
        {
            // Subtract all lhs values
            x(i, 0) -= A(i, j) * x(j, 0);
        }
        // Divide the RHS by coefficient of the unkown
        //x(i, 0) = rhs / A(i, i);
        x(i, 0) = x(i, 0) / A(i, i);
    }
    return x;
}

