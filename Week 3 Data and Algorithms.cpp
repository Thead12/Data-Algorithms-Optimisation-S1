// Week 3 Data and Algorithms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;

//Matrix class
class matrix {
    //public variables
public:
    int rows;
    int columns;
    //Constructor
    matrix(int x, int y, vector<vector<double> > grid) {
        rows = x;
        columns = y;
        //Array of pointers to store the matrix
        ptr = new double[rows * columns];
        if (grid.size() == rows && grid[0].size() == columns) {
            int index = 0;
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    *(ptr + index) = grid[i][j];
                    index++;
                }
            }
        }
        else
        {
        cout << "Vector and Matrix size to not match." << endl;
        }

        //checking to see if the matrix is size N = 2^m
        if (rows != columns && isdigit(log2(rows))) {
            conquerable = false;
        }
        else {
            conquerable = true;            
        }
    }
    //overload of constructor to create empty matrix
    matrix(int x, int y) {
        rows = x;
        columns = y;
        //Array of pointers to store the matrix
        ptr = new double[rows * columns];

        int index = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                *(ptr + index) = 0;
                index++;
            }
        }

        //checking to see if the matrix is size N = 2^m
        if (rows != columns && isdigit(log2(rows))) {
            conquerable = false;
        }
        else {
            conquerable = true;
        }
    }
    //Overload of constructor to fill matrix with repeating number
    matrix(int x, int y, double repeating) {
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

        //checking to see if the matrix is size N = 2^m
        if (rows != columns && isdigit(log2(rows))) {
            conquerable = false;
        }
        else {
            conquerable = true;
        }
    }
    double get(int i, int j) {
        if (i < rows && j < columns) {
            return ptr[(i * columns) + j];
        }
        else {
            cout << "Index out of  range" << endl;
            return 0;
        }
    }

    void set(int i, int j, double x) {
        ptr[(i * rows) + j] = x;
    }

    void addset(int i, int j, double x) {
        ptr[(i * rows) + j] += x;
    }

    matrix sum(matrix b) {
        matrix c(rows, columns);
        if (rows == b.rows && columns == b.columns) {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    double sum = get(i, j) + b(i, j);
                    c.set(i, j, sum);
                }
            }
            return c;
        }
        else {
            cout << "Matrices are not the same size, empty matrix returned" << endl;
            return c;
        }
    }

    matrix sub(matrix b) {
        matrix c(rows, columns);
        if (rows == b.rows && columns == b.columns) {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    double sum = get(i, j) - b(i, j);
                    c.set(i, j, sum);
                }
            }
            return c;
        }
        else {
            cout << "Matrices are not the same size, empty matrix returned" << endl;
            return c;
        }
    }

    matrix simpleproduct(matrix b) {
        matrix  c(rows, b.columns);
        if (columns == b.rows) {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < b.columns; j++) {
                    for (int k = 0; k < columns; k++) {
                        c.addset(i, j, (get(i, k) * b(k, j)));
                    }
                }
            }
            return c;
        }
        else {
            cout << "Dimensions of matrices are not compatible, returning empty matrix" << endl;
            return c;
        }


    }

    matrix conquer(matrix b) {
        matrix finalMatrix(rows, columns);
        if (conquerable == true && rows == b.columns) {
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
                        a10.set(i, j, get(i +  index, j));
                        a11.set(i, j, get(i +  index, j + index));

                        b00.set(i, j, b.get(i, j));
                        b01.set(i, j, b.get(i, j + index));
                        b10.set(i, j, b.get(i + index, j));
                        b11.set(i, j, b.get(i + index, j + index));

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
       else {
            cout << "These matrices are not of the form 2^m" << endl;
            return finalMatrix;
       }
    }

    /*matrix multiply(matrix b) {
        if (b.rows * b.columns)
    }*/

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
    double* ptr;
    //denotes whether the matrix is of size 2^m
    bool conquerable;

};


int main()
{

    vector<vector<double> > arr1 = {
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1}
    };

    vector<vector<double> > arr2 = {
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1}
    };

    matrix matrix1(8, 8, 5.7);

    matrix matrix2(8, 8, 6.989);

    matrix matrix3 = matrix2.conquer(matrix1);

    //matrix1.print();
    //matrix2.print();
    matrix3.print();
}
