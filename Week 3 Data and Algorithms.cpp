// Week 3 Data and Algorithms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;

/*struct Matrix {
    let rows : Int, columns : Int
        var grid : [Double] = Array()

        init(rows : Int, columns : Int) {
        self.rows = rows
            self.columns = columns
            self.grid = Array(repeating: 0.0, count : rows * columns)
    }
    func indexIsValid(row: Int, column : Int) -> Bool {
        return row >= 0 && row < rows&& column >= 0 && column < columns
    }
    subscript(row: Int, column : Int) -> Double {
        get{
            assert(indexIsValid(row: row, column : column), "Index out of range")
            return grid[(row * columns) + column]
        }
            set{
                assert(indexIsValid(row: row, column : column), "Index out of range")
                grid[(row * columns) + column] = newValue
        }
    }
}*/

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
        if (grid.size() == columns && grid[0].size() == rows) {
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
        return ptr[(i * rows) + j];
    }

    void set(int i, int j, double x) {
        ptr[(i * rows) + j] = x;
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

    matrix multiply(matrix b) {

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
        return ptr[(i * rows) + j];
    }

    matrix operator + (matrix b) {
        return sum(b);
    }

    matrix operator - (matrix b) {
        return sub(b);
    }

private:
    double* ptr;

    /*Matrix(int x, int y, double* ptr) {

    }*/


};


int main()
{

    vector<vector<double> > arr1 = {
        {1.1, 1.2, 1.3},
        {2.1, 2.2, 2.3},
        {3.1, 3.2, 3.3}
    };

    vector<vector<double> > arr2 = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };

    matrix matrix1(3, 3, arr1);

    matrix matrix2(3, 3, arr2);

    matrix matrix3 = matrix2 - matrix1;

    matrix3.print();

    /*cout << "The base address is " << ptr << endl;
    cout << "The value at base address is " << *ptr << endl;
    cout << "Value at base address + 1 is " << *ptr + 1 << endl;
    cout << "Value at first index is " << *(ptr + 1) << endl;
    cout << "Address of first index is " << (ptr + 1) << endl;
    cout << "Value at second index is " << ptr[2] << endl;
    cout << "Changing the value at second index\n";
    *(ptr + 2) = 200;
    cout << "New value at second index is " << *(ptr + 2) << endl;
    cout << "Moving the pointer ahead\n";
    ptr++;
    cout << "The pointer now points to " << *ptr << endl;
    cout << "The value at first index is now " << ptr[1] << endl;
    cout << "The value at first index is now " << *(ptr + 1) << endl;*/

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
