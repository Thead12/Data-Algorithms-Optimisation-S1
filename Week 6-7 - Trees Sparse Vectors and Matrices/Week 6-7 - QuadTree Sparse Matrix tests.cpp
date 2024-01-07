//============== Required includes ============== 
#include <iostream>
#include<vector>

//Uncomment to remove debug
//#define NDEBUG
#include<cassert>

//============== Dependent headerfiles ==============
#include "matrix.h"
#include "QuadTreeSparseMatrix.h"

void testEmptyMatrix() {
    QuadTree::SparseMatrix<int> emptyMatrix(4, 4);

    assert(emptyMatrix.getNumRows() == 4);
    assert(emptyMatrix.getNumCols() == 4);

    for (int i = 0; i < emptyMatrix.getNumRows(); ++i) {
        for (int j = 0; j < emptyMatrix.getNumCols(); ++j) {
            assert(emptyMatrix.getValue(i, j) == 0);
        }
    }
}

void testInitializationFromVector() {
    std::vector<std::vector<int>> vectorMatrix = { {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16} };
    QuadTree::SparseMatrix<int> fromVector(vectorMatrix);

    assert(fromVector.getNumRows() == 4);
    assert(fromVector.getNumCols() == 4);

    for (int i = 0; i < fromVector.getNumRows(); ++i) {
        for (int j = 0; j < fromVector.getNumCols(); ++j) {
            assert(fromVector.getValue(i, j) == vectorMatrix[i][j]);
        }
    }
}

void testInitializationFromDenseMatrix() {
    Dense::Matrix<int> denseMatrix(4, 4, 1);
    QuadTree::SparseMatrix<int> fromDense(denseMatrix);

    assert(fromDense.getNumRows() == 4);
    assert(fromDense.getNumCols() == 4);

    for (int i = 0; i < fromDense.getNumRows(); ++i) {
        for (int j = 0; j < fromDense.getNumCols(); ++j) {
            assert(fromDense.getValue(i, j) == 1);
        }
    }
}

void testSetValueAndGet() {
    QuadTree::SparseMatrix<int> testMatrix(4, 4);

    testMatrix.setValue(1, 1, 42);
    assert(testMatrix.getValue(1, 1) == 42);

    testMatrix.setValue(0, 0, 10);
    testMatrix.setValue(2, 2, 20);

    assert(testMatrix.getValue(0, 0) == 10);
    assert(testMatrix.getValue(1, 1) == 42);
    assert(testMatrix.getValue(2, 2) == 20);
}

void testOutOfBounds() {
    QuadTree::SparseMatrix<int> testMatrix(4, 4);

    // Attempt to set value out of bounds should not affect the matrix
    testMatrix.setValue(4, 4, 100);
    assert(testMatrix.getValue(4, 4) == 0);
}

int main()
{
    testEmptyMatrix();
    testInitializationFromVector();
    testInitializationFromDenseMatrix();
    testSetValueAndGet();
    //testOutOfBounds(); When uncommented, correct index out of bounds error is thrown

    std::cout << "All tests passed!" << std::endl;
}
