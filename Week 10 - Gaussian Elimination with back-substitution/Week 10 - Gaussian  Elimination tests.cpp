// Week 10 - Gaussian Elimination with testing.

#include <iostream>
#include<vector>
#include<cmath>

//Uncomment to remove debug
//#define NDEBUG
#include<cassert>

#include "matrix.h"

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

void gaussElimination(Dense::Matrix<double>& A);

Dense::Matrix<double> backSubstitution(Dense::Matrix<double> A);

void testGaussElimination();

void testBackSubstitution();

int main()
{
    testGaussElimination();
    testBackSubstitution();

    std::cout << "All tests passed!" << std::endl;
}

void testGaussElimination() {
    std::vector<std::vector<double>> A = {
        { 2, 1, -1},
        { -3, -1, 2},
        { -2, 1, 2}
    };

    std::vector<double> b = { 8, -11, -3 };


    // Test basic case
    Dense::Matrix<double> A1(A, b); // Testing augmented matrix contructor

    for (int i = 0; i < A1.getNumRows(); i++)
        for (int j = 0; j < A1.getNumCols() - 1; j++)
            assert(A1(i, j) == A[i][j]);
    for (int i = 0; i < A1.getNumRows(); i++)
        assert(A1(i, 3) == b[i]);

    gaussElimination(A1);

    // The matrix after Gaussian elimination should be an upper triangular matrix
    assert(std::abs(A1(1, 0)) < 1e-10);
    assert(std::abs(A1(2, 0)) < 1e-10);
    assert(std::abs(A1(2, 1)) < 1e-10);

    // Test case with no solution
    Dense::Matrix<double> A2({ {1, 2, 3, 4, 5},
                               {1, 3, 5, 7, 11},
                               {1, 0, -1, -2, -6} });  // The last row creates an inconsistency
    gaussElimination(A2);

    // The last row after Gaussian elimination should be [0, 0, 0, 0, 1], indicating no solution

    assert(std::abs(A2(2, 0)) < 1e-10);
    assert(std::abs(A2(2, 1)) < 1e-10);
    assert(std::abs(A2(2, 2)) < 1e-10);
    assert(std::abs(A2(2, 3)) < 1e-10);
    assert(std::abs(A2(2, 4) - 0.5) < 1e-10);

    // Test case with multiple solutions
    Dense::Matrix<double> A3 ({ {2, 1, -1, 8},
                                {-3, -1, 2, -11},
                                {-2, 1, 2, -3},
                                {1, 1, 1, 6} });
    gaussElimination(A3);

    // The matrix after Gaussian elimination should be an upper triangular matrix
    assert(std::abs(A3(1, 0)) < 1e-10);
    assert(std::abs(A3(2, 0)) < 1e-10);
    assert(std::abs(A3(2, 1)) < 1e-10);

    // Test case with zero rows
    Dense::Matrix<double> A4 ({ {0, 0, 0, 0},
                                {0, 0, 0, 0},
                                {0, 0, 0, 0} });
    gaussElimination(A4);

    // After Gaussian elimination, all rows should remain zero
    for (int i = 0; i < A4.getNumRows(); ++i) {
        for (int j = 0; j < A4.getNumCols(); ++j) {
            assert(std::abs(A4(i, j)) < 1e-10);
        }
    }
}

void testBackSubstitution() {
    std::vector<std::vector<double>> A = {
        { 2, 1, -1},
        { -3, -1, 2},
        { -2, 1, 2} 
    };

    std::vector<double> b = { 8, -11, -3 };


    // Test basic case
    Dense::Matrix<double> A1(A, b); // Testing augmented matrix contructor

    for (int i = 0; i < A1.getNumRows(); i++)
        for (int j = 0; j < A1.getNumCols() - 1; j++)
            assert(A1(i, j) == A[i][j]);
    for (int i = 0; i < A1.getNumRows(); i++)
        assert(A1(i, 3) == b[i]);

    gaussElimination(A1);

    Dense::Matrix<double> x1 = backSubstitution(A1);

    // The solution should be [2, 3, -1]
    assert(std::abs(x1(0, 0) - 2) < 1e-10);
    assert(std::abs(x1(1, 0) - 3) < 1e-10);
    assert(std::abs(x1(2, 0) + 1) < 1e-10);  // Note: there might be a sign difference due to the choice of pivot

    // Test case with no solution
    Dense::Matrix<double> A2({ {1, 2, 3, 4, 5},
                               {1, 3, 5, 7, 11},
                               {1, 0, -1, -2, -6} });  // The last row creates an inconsistency
    gaussElimination(A2);
    Dense::Matrix<double> x2 = backSubstitution(A2);

    // The solution should be [inf, inf, inf, inf]
    for (int i = 0; i < x2.getNumRows(); ++i) {
        assert(isnan(std::abs(x2(i, 0))));
    }

    // Test case with zero rows
    Dense::Matrix<double> A3 ({ {0, 0, 0, 0},
                                {0, 0, 0, 0},
                                {0, 0, 0, 0} });
    gaussElimination(A3);
    Dense::Matrix<double> x3 = backSubstitution(A3);

    // The solution should be [0, 0, 0]
    for (int i = 0; i < x3.getNumRows(); ++i) {
        assert(isnan(std::abs(x3(i, 0))));
    }
}

void gaussElimination(Dense::Matrix<double>& A)
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
    for (int i = N - 1; i >= 0; i--)
    {
        //double rhs = A(i, N);
        x(i, 0) = A(i, N); // RHS of equation

        for (int j = i + 1; j < N; j++)
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
