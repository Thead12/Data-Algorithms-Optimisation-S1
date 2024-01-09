//Contains various tests for Week 5's - LinkedList SparseMatrix task

#include <iostream>
#include<vector>

//Uncomment to remove debug
//#define NDEBUG
#include<cassert>

#include "matrix.h"
#include "LinkedListSparseMatrix.h"+

int main()
{
    LinkedList::SparseMatrix<double> sparseMat(3, 4);
    assert(sparseMat.getNumRows() == 3);
    assert(sparseMat.getNumCols() == 4);

    sparseMat.set(0, 0, 1.0);
    sparseMat.set(1, 1, 2.0);
    sparseMat.set(1, 0, 3.0);

    assert(sparseMat(0, 0) == 1.0);
    assert(sparseMat(1, 1) == 2.0);
    assert(sparseMat(1, 0) == 3.0);
    assert(sparseMat(0, 1) == 0.0);


    LinkedList::SparseMatrix<double> sparseMat1(3, 3);
    sparseMat1.set(0, 0, 1.0);
    sparseMat1.set(1, 1, 2.0);

    LinkedList::SparseMatrix<double> sparseMat2(3, 3);
    sparseMat2.set(0, 0, 3.0);
    sparseMat2.set(2, 2, 4.0);


    LinkedList::SparseMatrix<double> result1 = sparseMat1.AddSparse(sparseMat2);
    assert(result1(0, 0) == 4.0);
    assert(result1(1, 1) == 2.0);
    assert(result1(2, 2) == 4.0);
    assert(result1(1, 0) == 0.0);

    LinkedList::SparseMatrix<double> result2 = sparseMat1.SubtractSparse(sparseMat2);
    assert(result2(0, 0) == -2.0);
    assert(result2(1, 1) == 2.0);
    assert(result2(2, 2) == -4.0);
    assert(result2(1, 0) == 0.0);

    Dense::Matrix<double> denseMat(2, 2);
    denseMat.set(0, 0, 1.0);
    denseMat.set(1, 1, 2.0);

    sparseMat = LinkedList::SparseMatrix<double>(denseMat);
    assert(sparseMat(0, 0) == 1.0);
    assert(sparseMat(1, 1) == 2.0);
    assert(sparseMat(1, 0) == 0.0);

    std::cout << "All tests passed!" << std::endl;
}
