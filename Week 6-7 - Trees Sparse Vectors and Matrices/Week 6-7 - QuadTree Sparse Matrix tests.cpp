// Week 6-7 - Trees Sparse Vectors and Matrices.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<vector>
#include<algorithm>

//Uncomment to remove debug
//#define NDEBUG
#include<cassert>

#include "matrix.h"
#include "LinkedListSparseMatrix.h"
#include "CSRSparseMatrix.h"
#include "SparseVector.h"
#include "QuadTreeSparseMatrix.h"

void LineBreak() {
    std::cout << '\n';
}

void Print(std::string message) {
    std::cout << message << std::endl;
}

template<typename T>
void Print(T message) {
    std::cout << message << std::endl;
}


int main() {

    std::vector<std::vector<int>> vector =
    {
        {0, 0, 0, 0},
        {1, 0, 4, 0},
        {0, 8, 5, 0},
        {0, 0, 0, 0}
    };

    QuadTree::SparseMatrix<int> myMatrix(vector);

    myMatrix.setValue(0, 0, 2);

    Print(myMatrix.getValue(0, 0));

    LineBreak();

    myMatrix.printDense();

    return 0;
}

