// Week 10 - Gaussian Elimination with testing.

#include <iostream>
#include<vector>
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

void testLUdcmp();

int main()
{
    testLUdcmp();

    std::cout << "All tests passed!" << std::endl;
}

void testLUdcmp() {
    // Test basic case
    Dense::Matrix<double> A1({ {2, 1, -1},
                                {-3, -1, 2},
                                {-2, 1, 2} });
    LUdcmp::LUdcmp lu1(A1);

    std::vector<double> b1 = { 8, -11, -3 };
    std::vector<double> x1(b1.size());
    lu1.solve(b1, x1);

    // The solution should be [2, 3, -1]
    assert(std::abs(x1[0] - 2) < 1e-10);
    assert(std::abs(x1[1] - 3) < 1e-10);
    assert(std::abs(x1[2] + 1) < 1e-10);

    // Test case with multiple right-hand sides
    Dense::Matrix<double> A3({ {2, 1, -1},
                                {-3, -1, 2},
                                {-2, 1, 2} });
    LUdcmp::LUdcmp lu3(A3);

    Dense::Matrix<double> B3({ {8, 7},
                                {-11, -1},
                                {-3, 5} });
    Dense::Matrix<double> X3(B3.getNumRows(), B3.getNumCols());
    lu3.solve(B3, X3);

    // The solution matrix X3 should be [[2, 3], [-1, 1], [1, -2]]
    assert(std::abs(X3(0, 0) - 2) < 1e-10);
    assert(std::abs(X3(1, 0) - 3) < 1e-10);
    assert(std::abs(X3(2, 0) + 1) < 1e-10);  // Note: there might be a sign difference due to the choice of pivot
    assert(std::abs(X3(0, 1) - (20)) < 1e-10);
    assert(std::abs(X3(1, 1) + 7) < 1e-10);
    assert(std::abs(X3(2, 1) - 26) < 1e-10);  // Note: there might be a sign difference due to the choice of pivot
}
