#pragma once

#include <vector>
#include <cassert>

//Uncomment to remove debug
//#define NDEBUG

using std::vector;
using std::cout;
using std::endl;

//Matrix class using 1d row major order
class Matrix {

public:

    //Constructor to create empty Matrix
    Matrix(int initRows, int initCols) {
        rows = initRows; cols = initCols;

        ptr = new double[rows * cols]; //Array of pointers to store the Matrix

        int index = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                *(ptr + index) = 0;
                index++;
            }
        }
        //checking to see if the Matrix is size N = 2^m
#ifndef NDEBUG
        if (rows != cols && isdigit(log2(rows))) {
            conquerable = false;
        }
        else {
            conquerable = true;
        }
#endif
    }

    // Overload of constructor to make matrix from given vector
    Matrix(int initRows, int initCols, vector<vector<double> > grid) {
        rows = initRows; cols = initCols;

        ptr = new double[rows * cols];   //Array of pointers to store the Matrix
        assert(("Vector and Matrix size to not match.", grid.size() == rows && grid[0].size() == cols));
        int index = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                *(ptr + index) = grid[i][j];
                index++;
            }
        }
        //checking to see if the Matrix is size N = 2^m
#ifndef NDEBUG
        if (rows != cols && isdigit(log2(rows))) {
            conquerable = false;
        }
        else {
            conquerable = true;
        }
#endif
    }

    //Overload of constructor to fill Matrix with repeating number
    Matrix(int initRows, int initCols, double repeating) {
        rows = initRows; cols = initCols;
        //Array of pointers to store the Matrix
        ptr = new double[rows * cols];
        int index = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                *(ptr + index) = repeating;
                index++;
            }
        }
        //checking to see if the Matrix is size N = 2^m
#ifndef NDEBUG
        if (rows != cols && isdigit(log2(rows))) {
            conquerable = false;
        }
        else {
            conquerable = true;
        }
#endif
    }

    int getCols() {
        return cols;
    }

    int getRows() {
        return rows;
    }

    double get(int i, int j) {
        assert(("Index out of range", i < rows&& j < cols));
        return ptr[(i * cols) + j];
    }

    void set(int i, int j, double x) {
        assert(("Index out of range", i < rows&& j < cols));
        ptr[(i * cols) + j] = x;
    }

    void AddSet(int i, int j, double x) {
        assert(("Index out of range", i < rows&& j < cols));
        ptr[(i * cols) + j] += x;
    }

    Matrix sum(Matrix b) {
        assert(("Matrices are not the same size", rows == b.getRows() && cols == b.getCols()));
        Matrix c(rows, cols);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                double sum = get(i, j) + b.get(i, j);
                c.set(i, j, sum);
            }
        }

        return c;
    }

    Matrix sub(Matrix b) {
        assert(("Matrices are not the same size", rows == b.getRows() && cols == b.getCols()));
        Matrix c(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                double sum = get(i, j) - b(i, j);
                c.set(i, j, sum);
            }
        }
        return c;
    }

    Matrix SimpleProduct(Matrix b) {
        assert(("Dimensions of matrices are not compatible", cols == b.getRows()));
        Matrix  c(rows, b.getCols());
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < b.getCols(); j++) {
                for (int k = 0; k < cols; k++) {
                    c.AddSet(i, j, (get(i, k) * b(k, j)));
                }
            }
        }

        return c;
    }

    Matrix Conquer(Matrix b) {
        Matrix finalMatrix(rows, cols);
        assert(("Matrices are not of the form 2^m", conquerable == true && rows == b.getCols()));
        int index = rows / 2;

        if (rows == 1) {
            finalMatrix.set(0, 0, get(0, 0) * b(0, 0));
        }
        else {

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

            //Start of recursion
            //c00 = a00*b00 + a01*b10
            c00 = (a00.Conquer(b00)) + (a01.Conquer(b10));
            //c01 = a00*b01 + a01*b11
            c01 = (a00.Conquer(b01)) + (a01.Conquer(b11));
            //c10 = a10*b00 + a11*b01
            c10 = (a10.Conquer(b00)) + (a11.Conquer(b01));
            //c11 = a10*b01 + a11*b11
            c11 = (a10.Conquer(b01)) + (a11.Conquer(b11));

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

    void Print() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << get(i, j) << ", ";
            }
            cout << endl;
        }
    }

    double operator () (int i, int j) {
        return get(i, j);
    }
    Matrix operator + (Matrix b) {
        return sum(b);
    }
    Matrix operator - (Matrix b) {
        return sub(b);
    }

private:
    int rows; int cols;

    double* ptr;
    //denotes whether the Matrix is of size 2^m
    bool conquerable = true;
};
