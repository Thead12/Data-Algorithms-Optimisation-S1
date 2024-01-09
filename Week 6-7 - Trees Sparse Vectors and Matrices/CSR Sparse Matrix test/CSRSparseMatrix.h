#pragma once

// SparseMatrix class using LinkedList representation
// SparseMatrix class using CSR representation
//============== Basic functions ==============
// Various constructors for instantiating from Vectors, DenseMatrices and LinkedListSparseMatrices
// get() and set()
// add() and subtract() for two CSRSparseMatrices
// multiply between two CRSSparseMatrices
// PrintSparse() prints matrix in CRS format to console
// PrintDense() prints matrix in dense representation to console

//============== Required includes ============== 
#include <iostream>
#include<vector>

//Uncomment to remove debug
//#define NDEBUG
#include<cassert>

//============== Dependent headerfiles ==============
#include "matrix.h"
#include "LinkedListSparseMatrix.h"

namespace CSR {

    template<typename T>
    class SparseMatrix
    {
    private:
        int numRows; int numCols;

        std::vector<int> rowPointers;
        std::vector<int> columnIndices;
        std::vector<T> values;

        SparseMatrix(int initRows, int initCols) : numRows(initRows), numCols(initCols)
        {
            assert(("Matrix dimensions cannot be zero or negative", initRows > 0 && initCols > 0));
            rowPointers.push_back(0); //Initialise with 0 for first row        
        }

        void addElement(int col, T value)
        {
            assert(("Column index out of range", 0 <= col && col < numCols));
            if (value != 0) {
                values.push_back(value);
                columnIndices.push_back(col);
            }
        }

        //Adds entry to rowPointers for the end of the last row
        void finaliseRow()
        {
            rowPointers.push_back(values.size());
        }

    public:
        //==================== Constructors ==================
        // Constructor for converting from 2d vector
        SparseMatrix(std::vector<std::vector<T>> denseVector) : numRows(denseVector.size()), numCols(denseVector[0].size())
        {
            //Initialise rowPointers
            rowPointers.push_back(0);

            for (int i = 0; i < numRows; i++) {
                for (int j = 0; j < numCols; j++) {
                    addElement(j, denseVector[i][j]); //Use column index
                }
                finaliseRow();
            }
        }

        //Constructor for converting from dense matrix
        SparseMatrix(Dense::Matrix<T> denseMatrix) : numRows(denseMatrix.getNumRows()), numCols(denseMatrix.getNumCols())
        {
            //Initialise rowPointers
            rowPointers.push_back(0);

            for (int i = 0; i < numRows; i++) {
                for (int j = 0; j < numCols; j++) {
                    addElement(j, denseMatrix(i, j));
                }
                finaliseRow();
            }
        }

        //Constructor for converting from LinkedListSparseMatrix
        SparseMatrix(LinkedList::SparseMatrix<T> linkedListSparseMatrix) : numRows(linkedListSparseMatrix.getNumRows()), numCols(linkedListSparseMatrix.getNumCols())
        {
            //Initialise rowPointers
            rowPointers.push_back(0);

            for (int i = 0; i < numRows; i++) {
                for (int j = 0; j < numCols; j++) {
                    addElement(j, linkedListSparseMatrix(i, j));
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
            int start = rowPointers[row];
            int end = rowPointers[row + 1];

            // Search for the column index in the specified range
            for (int i = start; i < end; ++i) {
                if (columnIndices[i] == col)
                    return values[i]; // Found the element
            }

            return 0;
        }

        //Setter for values
        void set(int row, int col, T value)
        {
            assert(("Index out of range", 0 <= row && row < numRows && 0 <= col && col < numCols));
            //Find the range of indices for the specified row
            int start = rowPointers[row];
            int end = rowPointers[row + 1];

            //Search for the colum index in the specified range
            for (int i = start; i < end; ++i) {
                //If column already exists, update the value

                if (columnIndices[i] == col) {
                    values[i] = value;
                    return;
                }
                //If column index is greater, insert the new element in appropriate position
                else if (col < columnIndices[i]) {
                    columnIndices.insert(columnIndices.begin() + i, col);
                    values.insert(values.begin() + i, value);

                    //Update the row pointers for subsequent rows
                    for (int j = row + 1; j < numRows + 1; j++) rowPointers[j] += 1;

                    return;
                }
            }
            //If column index is greater than all existing indices in the row, insert at rowPointer[row+1]
            columnIndices.insert(columnIndices.begin() + rowPointers[row + 1], col);
            values.insert(values.begin() + rowPointers[row + 1], value);

            //Update row pointers for subsequent rows
            for (int i = row + 1; i < numRows + 1; i++) rowPointers[i] += 1;

            return;
        }

        SparseMatrix<T> add(SparseMatrix<T> matrixB)
        {
            assert(("Matrix dimensions are not compatible", numRows == matrixB.getNumRows() && numCols == matrixB.getNumCols()));

            SparseMatrix<T> resultMatrix(numRows, numCols);

            //Iterate through rows of first matrix
            for (int i = 0; i < numRows; i++) {
                for (int j = 0; j < numCols; j++) {

                    T sum = get(i, j) + matrixB(i, j);

                    resultMatrix.addElement(j, sum);
                }
                resultMatrix.finaliseRow(); //Change column pointer to next column
            }
            return resultMatrix;
        }

        SparseMatrix<T> subtract(SparseMatrix<T> matrixB)
        {
            assert(("Matrix dimensions are not compatible", numRows == matrixB.getNumRows() && numCols == matrixB.getNumCols()));

            SparseMatrix<T> resultMatrix(numRows, numCols);

            //Iterate through rows of first matrix
            for (int i = 0; i < numRows; i++) {
                for (int j = 0; j < numCols; j++) {

                    T difference = get(i, j) - matrixB(i, j);

                    resultMatrix.addElement(j, difference);
                }
                resultMatrix.finaliseRow(); //Change column pointer to next column
            }
            return resultMatrix;
        }

        SparseMatrix<T> multiply(SparseMatrix<T> matrixB)
        {
            assert(("Matrix dimensions are not compatible", numCols == matrixB.getNumRows()));

            //Initialise result matrix
            SparseMatrix<T> resultMatrix(numRows, matrixB.getNumCols());

            //Iterate through rows of first matrix
            for (int i = 0; i < numRows; i++) {
                for (int j = 0; j < matrixB.getNumCols(); j++) {

                    T dotProduct = 0;

                    //Iterate through columns of the second matrix
                    for (int k = rowPointers[i]; k < rowPointers[i + 1]; k++) {
                        //Multiply corresponding elements
                        dotProduct += values[k] * matrixB(columnIndices[k], j);
                    }
                    //update result matrix
                    resultMatrix.addElement(j, dotProduct);
                }
                resultMatrix.finaliseRow(); //Change column pointer to next column
            }
            return resultMatrix;
        }

        void printSparse() const {
            std::cout << "Values: ";
            for (T value : values) {
                std::cout << value << ' ';
            }
            std::cout << std::endl;

            std::cout << "Column Indices: ";
            for (int columnIndex : columnIndices) {
                std::cout << columnIndex << ' ';
            }
            std::cout << std::endl;

            std::cout << "Row pointers: ";
            for (int rowPointer : rowPointers) {
                std::cout << rowPointer << ' ';
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
}
