//============== Required includes ============== 
#include <iostream>
#include<vector>

//Uncomment to remove debug
//#define NDEBUG
#include<cassert>

//============== Dependent headerfiles ==============
#include "matrix.h"
#include "LinkedListSparseMatrix.h"

int main()
{
    using namespace LinkedList;

    // Test SparseLinkedList
    SparseLinkedList<double> sparseList;
    sparseList.InsertTail(1, 10.5);
    sparseList.InsertTail(3, 7.2);
    sparseList.InsertTail(5, -3.8);

    std::cout << "Sparse Linked List:" << std::endl;
    sparseList.PrintList();
    std::cout << std::endl;

    // Test SparseMatrix
    std::vector<std::vector<double>> denseVector = {
        {0, 0, 0, 0, 0},
        {0, 2.3, 0, 0, 0},
        {0, 0, 0, 1.8, 0},
        {0, 0, 0, 0, 0}
    };

    SparseMatrix<double> sparseMatrix(denseVector);

    std::cout << "Original Sparse Matrix:" << std::endl;
    sparseMatrix.PrintSparse();
    std::cout << std::endl;

    // Test matrix operations
    SparseMatrix<double> sparseMatrix2(4, 5);
    sparseMatrix2.set(1, 1, 3.7);
    sparseMatrix2.set(2, 3, -2.1);

    SparseMatrix<double> addedMatrix = sparseMatrix.AddSparse(sparseMatrix2);
    assert(addedMatrix.get(1, 1) == (2.3 + 3.7));
    assert(addedMatrix.get(2, 3) == (1.8 + -2.1));
    std::cout << "Sparse Matrix Addition:" << std::endl;
    addedMatrix.PrintSparse();
    std::cout << std::endl;

    Dense::Matrix<double> denseMatrix(denseVector);

    Dense::Matrix<double> subtractedMatrix = sparseMatrix.SubtractDense(denseMatrix);
    std::cout << "Sparse Matrix - Dense Matrix Subtraction:" << std::endl;
    subtractedMatrix.Print();
    std::cout << std::endl;
}
