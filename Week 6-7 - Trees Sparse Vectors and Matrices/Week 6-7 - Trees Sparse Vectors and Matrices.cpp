// Week 6-7 - Trees Sparse Vectors and Matrices.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<cassert>
#include<vector>

#include "matrix.h"

//Uncomment to remove debug
//#define NDEBUG

template<typename T>
class CSRSparseMatrix
{
private:
    int numRows; int numCols;

    std::vector<int> rowPtrs;
    std::vector<int> colIndices;
    std::vector<T> values;

    void addElement(int col, int value)
    {
        assert(("Column index out of range", 0 <= col && col < numCols));
        if (value != 0) {
            values.push_back(value);
            colIndices.push_back(col);
        }
    }

    //Adds entry to rowPointers for the end of the last row
    void finaliseRow()
    {
        rowPtrs.push_back(values.size());
    }

public:

    //Constructor for empty Matrix
    CSRSparseMatrix(int initRows, int initCols) : numRows(initRows), numCols(initCols)
    {
        assert(("Matrix dimensions cannot be zero or negative", initRows > 0 && initCols > 0));
        rowPtrs.push_back(0); //Initialise with 0 for first row        
    } 

    // Constructor for converting from vector
    CSRSparseMatrix(std::vector<std::vector<T>> denseVector) : numRows(denseVector.size()), numCols(denseVector[0].size())
    {
        //Initialise rowPtrs
        rowPtrs.push_back(0);

        for (size_t i = 0; i < numRows; i++) {
            for (size_t j = 0; j < numCols; j++) {
                addElement(j, denseVector[i][j]); //Use column index
            }
            finaliseRow();
        }
    }

    //Constructor for converting from dense matrix
    CSRSparseMatrix(Matrix denseMatrix) : numRows(denseMatrix.getRows()), numCols(denseMatrix.getCols())
    {
        //Initialise rowPtrs
        rowPtrs.push_back(0);

        for (size_t i = 0; i < numRows; i++) {
            for (size_t j = 0; j < numCols; j++) {
                addElement(j, denseMatrix(i, j));
            }
            finaliseRow();
        }
    }

    //Getters ==================== Setters 
    int getNumRows() {
        return numRows;
    }

    int getNumCols() 
    {
        return numCols;
    }

    //Getter for values
    T get(int row, int col) const
    {
        assert(("Index out of range", 0 <= row && row < numRows && 0 <= col && col < numCols));

        // Find the range of indices for the specified row
        int start = rowPtrs[row];
        int end = rowPtrs[row + 1];

        // Search for the column index in the specified range
        for (int i = start; i < end; ++i) {
            if (colIndices[i] == col)
                return values[i]; // Found the element
        }

        return 0;
    }

    void printSparse() const {
        std::cout << "Values: ";
        for (int val : values) {
            std::cout << val << ' ';
        }
        std::cout << std::endl;

        std::cout << "Column Indices: ";
        for (int colIndex : colIndices) {
            std::cout << colIndex << ' ';
        }
        std::cout << std::endl;

        std::cout << "Row pointers: ";
        for (int rowPtr : rowPtrs) {
            std::cout << rowPtr << ' ';
        }
        std::cout << std::endl;
    }

    void printDense() const {
        for (int i = 0; i < numRows; ++i) {
            for (int j = 0; j < numCols; j++)
            {
                std::cout << get(i, j) << ", ";
            }
            std::cout << '\n';
        }
    }

    T operator () (int i, int j) {
        return get(i, j);
    }
};

void LineBreak() {
    std::cout << '\n';
}


int main() {
    std::vector<std::vector<int>> denseMatrix = {
        {0, 0, 0, 0},
        {0, 2, 0, 0},
        {0, 0, 3, 0}
    };

    CSRSparseMatrix<int> sparseMatrix(denseMatrix);

    // Print the sparse matrix
    sparseMatrix.printSparse();

    LineBreak();

    // Test the get function
    std::cout << "Value at (0, 0): " << sparseMatrix(2, 2) << std::endl; // Should print 1

    LineBreak();

    //Print matrix in dense form
    sparseMatrix.printDense();

    return 0;
}

