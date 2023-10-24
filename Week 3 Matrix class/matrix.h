#pragma once

#include <vector>
#include <cassert>

//Uncomment to remove debug
//#define NDEBUG
using namespace std;

//Matrix class
class matrix {

public: //public variables
    //Constructor
    matrix(int x, int y, vector<vector<double> > grid) {
        rows = x;
        columns = y;

        ptr = new double[rows * columns];   //Array of pointers to store the matrix
        assert(("Vector and Matrix size to not match.", grid.size() == rows && grid[0].size() == columns));
        int index = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                *(ptr + index) = grid[i][j];
                index++;
            }
        }
#ifndef NDEBUG
        if (rows != columns && isdigit(log2(rows))) {
            conquerable = false;
        }
        else {
            conquerable = true;
        }
#endif
    }

    matrix(int x, int y) {  //overload of constructor to create empty matrix
        rows = x;
        columns = y;

        ptr = new double[rows * columns];   //Array of pointers to store the matrix

        int index = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                *(ptr + index) = 0;
                index++;
            }
        }
#ifndef NDEBUG
        if (rows != columns && isdigit(log2(rows))) {
            conquerable = false;
        }
        else {
            conquerable = true;
        }
#endif
    }

    matrix(int x, int y, double repeating) { //Overload of constructor to fill matrix with repeating number
        rows = x;
        columns = y;
        //Array of pointers to store the matrix
        ptr = new double[rows * columns];
        int index = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                *(ptr + index) = repeating;
                index++;
            }
        }

#ifndef NDEBUG
        if (rows != columns && isdigit(log2(rows))) { //checking to see if the matrix is size N = 2^m
            conquerable = false;
        }
        else {
            conquerable = true;
        }
#endif
    }

    int getcolumns() {
        return columns;
    }

    int getrows() {
        return rows;
    }

    double get(int i, int j) {
        assert(("Index out of range", i < rows&& j < columns));
        return ptr[(i * columns) + j];
    }

    void set(int i, int j, double x) {
        assert(("Index out of range", i < rows&& j < columns));
        ptr[(i * rows) + j] = x;
    }

    void addset(int i, int j, double x) {
        assert(("Index out of range", i < rows&& j < columns));
        ptr[(i * rows) + j] += x;
    }

    matrix sum(matrix b) {
        assert(("Matrices are not the same size", rows == b.getrows() && columns == b.getcolumns()));
        matrix c(rows, columns);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                double sum = get(i, j) + b(i, j);
                c.set(i, j, sum);
            }
        }
        return c;
    }

    matrix sub(matrix b) {
        assert(("Matrices are not the same size", rows == b.getrows() && columns == b.getcolumns()));
        matrix c(rows, columns);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                double sum = get(i, j) - b(i, j);
                c.set(i, j, sum);
            }
        }
        return c;
    }

    matrix simpleproduct(matrix b) {
        assert(("Dimensions of matrices are not compatible", columns == b.getrows()));
        matrix  c(rows, b.getcolumns());
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < b.getcolumns(); j++) {
                for (int k = 0; k < columns; k++) {
                    c.addset(i, j, (get(i, k) * b(k, j)));
                }
            }
        }

        return c;
    }

    matrix conquer(matrix b) {
        matrix finalMatrix(rows, columns);
        assert(("Matrices are not of the form 2^m", conquerable == true && rows == b.getcolumns()));
        int index = rows / 2;

        if (rows == 1) {
            finalMatrix.set(0, 0, get(0, 0) * b(0, 0));
        }
        else {

            matrix c00(index, index);
            matrix c01(index, index);
            matrix c10(index, index);
            matrix c11(index, index);

            matrix a00(index, index);
            matrix a01(index, index);
            matrix a10(index, index);
            matrix a11(index, index);

            matrix b00(index, index);
            matrix b01(index, index);
            matrix b10(index, index);
            matrix b11(index, index);

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
            c00 = (a00.conquer(b00)) + (a01.conquer(b10));
            //c01 = a00*b01 + a01*b11
            c01 = (a00.conquer(b01)) + (a01.conquer(b11));
            //c10 = a10*b00 + a11*b01
            c10 = (a10.conquer(b00)) + (a11.conquer(b01));
            //c11 = a10*b01 + a11*b11
            c11 = (a10.conquer(b01)) + (a11.conquer(b11));

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

    void print() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                cout << get(i, j) << ", ";
            }
            cout << endl;
        }
    }

    double operator () (int i, int j) {
        return get(i, j);
    }
    matrix operator + (matrix b) {
        return sum(b);
    }
    matrix operator - (matrix b) {
        return sub(b);
    }

private:
    int rows;
    int columns;

    double* ptr;
    //denotes whether the matrix is of size 2^m
    bool conquerable = true;
};