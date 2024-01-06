#pragma once

//Generic dense matrix class using 1d row-major representation
//============== Basic functions ==============
//add()

//============== Required includes ============== 
//#include <iostream>
#include<vector>

//Uncomment to remove debug
//#define NDEBUG
//#include<cassert>

namespace Dense{
    //Matrix class using 1d row major order

    template<typename T>
    class Matrix {

    private:
        int numRows; int numCols;

        T* valueArray;
        //denotes whether the Matrix is of size 2^m
        bool conquerable;

    public:
        //==================== Constructors ====================
        
        Matrix(int initRows, int initCols);               // Constructor to create empty Matrix
        Matrix(std::vector<std::vector<T>> grid);         // Overload of constructor to make matrix from given vector
        Matrix(std::vector<T> grid);                      // Overload of constructor to make column matrix from given 1d vector
        Matrix(int initRows, int initCols, T repeating);  // Overload of constructor to fill Matrix with repeating number
        Matrix(Dense::Matrix<T> a, std::vector<T> b);     // Overload of constructor to initialise an augmented matrix

        //Getters ==================== Setters 

        int getNumCols();                   // Returns number of columns
        int getNumRows();                   // Returns number of rows
        bool getConquerable();               // Returns whether matrix is conquerable
        T& get(int i, int j);               // Returns by reference value at (i, j)
        void set(int i, int j, T x);        // Sets value at (i, j)
        void AddSet(int i, int j, T x);     // Adds value at (i, j) to input x
        Matrix add(Matrix &b);              // Adds two matrices 
        void add(Matrix &b, Matrix &c);     // Adds two matrices in-place, storing output in c
        Matrix subtract(Matrix &b);         // Subtracts two matrices
        void subtract(Matrix &b, Matrix &c);// Subtracts two matrices in-place, storing output in c
        Matrix SimpleProduct(Matrix &b);    // Uses naive multiplication to multiply two matrices
        void SimpleProduct(Matrix &b, Matrix &c); // Uses naive multiplication to multiply two matrices in-place, storing output in c
        Matrix Conquer(Matrix &b, int breakPoint, int size);          // Uses divide and conquer to multiply two matrices
        void swapRows(unsigned int rowA, unsigned int rowB); // Swaps two rows
        void Print(); // Prints whole matrix

        T& operator () (int i, int j) {
            return get(i, j);
        }
        Matrix operator + (Matrix b) {
            return add(b);
        }
        Matrix operator - (Matrix b) {
            return subtract(b);
        }
        Matrix operator * (Matrix b) {
            return SimpleProduct(b);
        }      
    };

    
    template<typename T>
    //Constructor to create empty Matrix
    Matrix<T>::Matrix(int initRows, int initCols) {
        numRows = initRows; numCols = initCols;

        valueArray = new T[numRows * numCols]; //Array of pointers to store the Matrix

        int index = 0;
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                *(valueArray + index) = 0;
                index++;
            }
        }
        //checking to see if the Matrix is size N = 2^m
#ifndef NDEBUG
        if (numRows == numCols && isdigit(log2(numRows))) {
            conquerable = true;
        }
        else {
            conquerable = false;
        }
#endif
    }

    template<typename T>
    // Overload of constructor to make matrix from given vector
    Matrix<T>::Matrix(std::vector<std::vector<T> > grid) : numRows(grid.size()), numCols(grid[0].size())
    {

        valueArray = new T[numRows * numCols];   //Array of pointers to store the Matrix
        //assert(("Vector and Matrix size to not match.", grid.size() == numRows && grid[0].size() == numCols));
        int index = 0;
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                *(valueArray + index) = grid[i][j];
                index++;
            }
        }
        //checking to see if the Matrix is size N = 2^m
#ifndef NDEBUG
        if (numRows == numCols && isdigit(log2(numRows))) {
            conquerable = true;
        }
        else {
            conquerable = false;
        }
#endif
    }

    template<typename T>
    // Overload of constructor to make column matrix from given 1d vector
    Matrix<T>::Matrix(std::vector<T> grid) : numRows(grid.size()), numCols(1)
    {
        valueArray = new T[numRows * numCols];   //Array of pointers to store the Matrix
        //assert(("Vector and Matrix size to not match.", grid.size() == numRows && grid[0].size() == numCols));
        int index = 0;
        for (int i = 0; i < numRows; i++) {
            *(valueArray + index) = grid[i];
            index++;
        }
        //checking to see if the Matrix is size N = 2^m
#ifndef NDEBUG
        if (numRows != numCols && !isdigit(int(log2(numRows)))) {
            conquerable = false;
        }
        else {
            conquerable = true;
        }
#endif
    }

    template<typename T>
    //Overload of constructor to fill Matrix with repeating number
    Matrix<T>::Matrix(int initRows, int initCols, T repeating) {
        numRows = initRows; numCols = initCols;
        //Array of pointers to store the Matrix
        valueArray = new T[numRows * numCols];
        int index = 0;
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                *(valueArray + index) = repeating;
                index++;
            }
        }
        //checking to see if the Matrix is size N = 2^m
#ifndef NDEBUG
        if (numRows == numCols && isdigit(log2(numRows))) {
            conquerable = true;
        }
        else {
            conquerable = false;
        }
#endif
    }

    template<typename T>
    //Overload of constructor to initialise an augmented matrix
    Matrix<T>::Matrix(Dense::Matrix<T> a, std::vector<T> b)
    {
        numRows = a.getNumRows();
        numCols = a.getNumCols() + 1;

        assert(("Matrix rows and length of vector are not compatible", numRows == b.size()));

        //Array of pointers to store the Matrix
        valueArray = new T[numRows * numCols];
        // Fill augmented matrix with matrix a
        int index = 0;
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols - 1; j++) {
                get(i, j) = a(i, j);
            }
        }

        //Fill augmented matrix with vector b
        for (int i = 0; i < numRows; i++)
        {
            get(i, numCols - 1) = b[i];
        }

#ifndef NDEBUG
        if (numRows == numCols && isdigit(log2(numRows))) {
            conquerable = true;
        }
        else {
            conquerable = false;
        }
#endif
    }

    template<typename T>
    int Matrix<T>::getNumCols() {
        return numCols;
    }

    template<typename T>
    int Matrix<T>::getNumRows() {
        return numRows;
    }

    template<typename T>
    bool Matrix<T>::getConquerable() {
        return conquerable;
    }

    template<typename T>
    T& Matrix<T>::get(int i, int j) {
        assert(("Index out of range", i < numRows&& j < numCols));
        return valueArray[(i * numCols) + j];
    }

    template<typename T>
    void Matrix<T>::set(int i, int j, T x) {
        assert(("Index out of range", i < numRows&& j < numCols));
        valueArray[(i * numCols) + j] = x;
    }

    template<typename T>
    void Matrix<T>::AddSet(int i, int j, T x) {
        assert(("Index out of range", i < numRows&& j < numCols));
        valueArray[(i * numCols) + j] += x;
    }

    template<typename T>
    Matrix<T> Matrix<T>::add(Matrix<T> &b) {
        assert(("Matrices are not the same size", numRows == b.getNumRows() && numCols == b.getNumCols()));
        Matrix c(numRows, numCols);

        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                c(i, j) = get(i, j) + b.get(i, j);
            }
        }
        return c;
    }

    template<typename T>
    void Matrix<T>::add(Matrix<T> &b, Matrix<T> &c) {
        assert(("Matrices are not the same size", numRows == b.getNumRows() && numCols == b.getNumCols()));

        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                c(i, j) = get(i, j) + b.get(i, j);
            }
        }
    }

    template<typename T>
    Matrix<T> Matrix<T>::subtract(Matrix &b) {
        assert(("Matrices are not the same size", numRows == b.getNumRows() && numCols == b.getNumCols()));
        Matrix c(numRows, numCols);
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                T difference = get(i, j) - b(i, j);
                c.set(i, j, difference);
            }
        }
        return c;
    }

    template<typename T>
    void Matrix<T>::subtract(Matrix& b, Matrix<T>& c) {
        assert(("Matrices are not the same size", numRows == b.getNumRows() && numCols == b.getNumCols()));
        Matrix c(numRows, numCols);
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                T difference = get(i, j) - b(i, j);
                c.set(i, j, difference);
            }
        }
    }

    template<typename T>
    Matrix<T> Matrix<T>::SimpleProduct(Matrix &b) {
        assert(("Dimensions of matrices are not compatible", numCols == b.getNumRows()));
        Matrix  c(numRows, b.getNumCols());
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < b.getNumCols(); j++) {
                for (int k = 0; k < numCols; k++) {
                    c.AddSet(i, j, (get(i, k) * b(k, j)));
                }
            }
        }

        return c;
    }

    template<typename T>
    void Matrix<T>::SimpleProduct(Matrix& b, Matrix<T>& c) {
        assert(("Dimensions of matrices are not compatible", numCols == b.getNumRows()));
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < b.getNumCols(); j++) {
                for (int k = 0; k < numCols; k++) {
                    c.AddSet(i, j, (get(i, k) * b(k, j)));
                }
            }
        }
    }

    template<typename T>
    Matrix<T> Matrix<T>::Conquer(Matrix &b, int breakPoint, int size) {
        assert(("Matrices are not of the form 2^m", conquerable == true && numRows == b.getNumCols()));
        //Creating the final matrix which will contain the completed multiplication
        Matrix finalMatrix(numRows, numCols);

        //Break statement to end recursion and begin back through stack
        if (size <= breakPoint) {
            SimpleProduct(b, finalMatrix);
        }
        else {
            //Dividing size by 2
            int index = (size / 2);

            //Initializing submatrices
            Matrix c00(index, index);
            Matrix c01(index, index);
            Matrix c10(index, index);
            Matrix c11(index, index);

            Matrix a00(index, index);
            Matrix a01(index, index);
            Matrix a10(index, index);
            Matrix a11(index, index);

            Matrix b00(index, index);
            Matrix b01(index, index);
            Matrix b10(index, index);
            Matrix b11(index, index);

            //Filling submatrices
            for (int i = 0; i < index; i++) {
                for (int j = 0; j < index; j++) {

                    //Filling submatrices
                    for (int i = 0; i < index; i++) {
                        for (int j = 0; j < index; j++) {

                            a00.set(i, j, get(i, j));
                            a01.set(i, j, get(i, j + index));
                            a10.set(i, j, get(i + index, j));
                            a11.set(i, j, get(i + index, j + index));

                            b00.set(i, j, b(i, j));
                            b01.set(i, j, b(i, j + index));
                            b10.set(i, j, b(i + index, j));
                            b11.set(i, j, b(i + index, j + index));

                        }
                    }
                }
            }

            //Start of recursion
             //c00 = a00*b00 + a01*b10
            c00 = (a00.Conquer(b00, breakPoint, index)) + (a01.Conquer(b10, breakPoint, index));
            //c01 = a00*b01 + a01*b11
            c01 = (a00.Conquer(b01, breakPoint, index)) + (a01.Conquer(b11, breakPoint, index));
            //c10 = a10*b00 + a11*b01
            c10 = (a10.Conquer(b00, breakPoint, index)) + (a11.Conquer(b01, breakPoint, index));
            //c11 = a10*b01 + a11*b11
            c11 = (a10.Conquer(b01, breakPoint, index)) + (a11.Conquer(b11, breakPoint, index));

            //Returning values into finalMatrix
            for (int i = 0; i < index; i++) {
                for (int j = 0; j < index; j++) {
                    finalMatrix.set(i, j, c00(i, j));
                    finalMatrix.set(i, j + index, c01(i, j));
                    finalMatrix.set(i + index, j, c10(i, j));
                    finalMatrix.set(i + index, j + index, c11(i, j));
                }
            }
        }

        return finalMatrix;
    }

    template<typename T>
    void Matrix<T>::swapRows(unsigned int rowA, unsigned int rowB)
    {
        assert(("rowA is an invalid input", 0 <= rowA && rowA < numRows));
        assert(("rowB is an invalid input", 0 <= rowB && rowB < numRows));

        for (int j = 0; j < numCols; j++)
        {
            std::swap(get(rowA, j), get(rowB, j));
        }
    }

    template<typename T>
    void Matrix<T>::Print() {
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                std::cout << get(i, j) << ", ";
            }
            std::cout << std::endl;
        }
    }
}
