//Contains various tests for Week 5's - LinkedList SparseMatrix task

#include <iostream>
#include<vector>

//Uncomment to remove debug
//#define NDEBUG
#include<cassert>

#include "matrix.h"
#include "LinkedListSparseMatrix.h"

int main()
{
    vector<vector<double>> denseVectorA = {
        {0, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 2, 0},
        {0, 0, 0, 3},
        {0, 0, 0, 0}
    };

    vector<vector<double>> denseVectorB = {
        {0, 2, 0, 0},
        {0, 1, 3, 5},
        {4, 9, 2, 1},
        {5, 7, 6, 3},
        {8, 6, 4, 0}
    };

    Matrix denseA = Matrix(5, 4, denseVectorA);
    Matrix denseB = Matrix(5, 4, denseVectorB);


    SparseMatrix sparseA = SparseMatrix(5, 4, denseVectorA);
    SparseMatrix sparseB = SparseMatrix(5, 4, denseVectorB);

    SparseMatrix sparseAdditionTest = sparseA.SubtractSparse(sparseB);
    Matrix denseAdditionTest = sparseA.SubtractDense(denseB);

    sparseAdditionTest.PrintDense();

    cout << endl;

    denseAdditionTest.Print();
}
