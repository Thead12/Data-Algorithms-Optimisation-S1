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
	std::vector<double> vector = { 0, 0, 1, 2, 3.2, 0, 0, 1.0, 5.5546, 0, 0, 4.5, 0, 216 };

	BinaryTree::Balanced::SparseVector<double> sparseVector(vector);

	sparseVector.insert(2, 3.5);
	sparseVector.insert(5, 1.2);
	sparseVector.insert(3, -4.0);

	sparseVector.print();

	LineBreak();

	sparseVector.printBFRange();

	LineBreak();

	Print(sparseVector.getValue(2));

}
