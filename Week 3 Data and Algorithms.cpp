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
        if (rows == columns && isdigit(log2(rows))) {
            conquerable = true;;
        }
        else {
            conquerable = false;
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

    /*matrix conquer(matrix b) {

    }

    matrix multiply(matrix b) {
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
        {1, 2, 3},
        {1, 2, 3}
    };

    vector<vector<double> > arr2 = {
        {1, 2},
        {1, 2},
        {1, 2}
    };

    matrix matrix1(2, 3, arr1);

    matrix matrix2(3, 2, arr2);

    matrix matrix3 = matrix2.simpleproduct(matrix1);

    matrix1.print();
    matrix2.print();
    matrix3.print();
}
