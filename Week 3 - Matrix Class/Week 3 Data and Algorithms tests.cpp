#include <iostream>
#include <vector>
#include <cassert>

#include "matrix.h"

int main() {
    using namespace Dense;

    // Test Constructors
    Matrix<int> matrix1(3, 3);
    assert(matrix1.getNumRows() == 3);
    assert(matrix1.getNumCols() == 3);

    std::vector<std::vector<int>> grid = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
    Matrix<int> matrix2(grid);
    assert(matrix2.getNumRows() == 3);
    assert(matrix2.getNumCols() == 3);

    std::vector<int> vectorGrid = { 1, 2, 3 };
    Matrix<int> matrix3(vectorGrid);
    assert(matrix3.getNumRows() == 3);
    assert(matrix3.getNumCols() == 1);

    Matrix<int> matrix4(2, 2, 5);
    assert(matrix4(0, 0) == 5);

    Matrix<int> matrix5(matrix2, vectorGrid);
    assert(matrix5.getNumRows() == 3);
    assert(matrix5.getNumCols() == 4);

    // Test Getters and Setters
    matrix1.set(1, 1, 10);
    assert(matrix1(1, 1) == 10);

    // Test Matrix Operations
    Matrix<int> addResult = matrix2 + matrix1;
    assert(addResult(0, 0) == 1);

    Matrix<int> subtractResult = matrix2 - matrix1;
    assert(subtractResult(0, 0) == 1);

    Matrix<int> productResult = matrix2 * matrix1;
    assert(productResult(0, 0) == 0);
    assert(productResult(1, 1) == 50);

    // Test Matrix Printing
    std::cout << "Matrix 2:" << std::endl;
    matrix2.Print();

    // Test Conquer (if applicable)
    if (matrix2.getConquerable()) {
        Matrix<int> conquerResult = matrix2.Conquer(matrix1, 1, matrix2.getNumRows());
        assert(conquerResult(0, 0) == 0);
    }

    Matrix<int> conquer1(16, 16, 1);
    Matrix<int> conquer2(16, 16, 2);
    Matrix<int> conquerResult = conquer2.Conquer(conquer1, 2, conquer2.getNumRows());
    assert(conquerResult(0, 0) == (conquer1 * conquer2)(0, 0));

    // Test swapRows
    matrix1.swapRows(0, 1);
    assert(matrix1(0, 0) == 0);

    std::cout << "All tests passed successfully!" << std::endl;
}
