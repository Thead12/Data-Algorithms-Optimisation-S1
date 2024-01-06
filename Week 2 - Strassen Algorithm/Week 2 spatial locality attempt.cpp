// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

using namespace std;

#define SIZE 4
#define INDEX SIZE/2

namespace matrix {

    //Initializing submatrices
    vector<double> rows(INDEX, 0);

    vector<vector<double>> A00(INDEX, rows);
    vector<vector<double>> A01(INDEX, rows);
    vector<vector<double>> A10(INDEX, rows);
    vector<vector<double>> A11(INDEX, rows);
             
    vector<vector<double>> B00(INDEX, rows);
    vector<vector<double>> B01(INDEX, rows);
    vector<vector<double>> B10(INDEX, rows);
    vector<vector<double>> B11(INDEX, rows);

    vector<vector<double>> M1(INDEX, rows);
    vector<vector<double>> M2(INDEX, rows);
    vector<vector<double>> M3(INDEX, rows);
    vector<vector<double>> M4(INDEX, rows);
    vector<vector<double>> M5(INDEX, rows);
    vector<vector<double>> M6(INDEX, rows);
    vector<vector<double>> M7(INDEX, rows);

    //vector<vector<double>> M[7] = { M1, M2, M3, M4, M5, M6, M7 };

    //Create temporary matrices for storing in-place calculations
    std::vector<std::vector<double>> tempA(INDEX, rows);
    std::vector<std::vector<double>> tempB(INDEX, rows);
}

void NaiveMultiplication(const vector<vector<double>>& matrixA, const vector<vector<double>>& matrixB, vector<vector<double>>& result, int size)
{
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
}

void AddMatrices(const vector<vector<double>>& matrixA, const vector<vector<double>>& matrixB, vector<vector<double>>& result, int size)
{
    result.resize(size, vector<double>(size, 0.0));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }
}

void SubMatrices(const vector<vector<double>>& matrixA, const vector<vector<double>>& matrixB, vector<vector<double>>& result, int size)
{
    result.resize(size, vector<double>(size, 0.0));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = matrixA[i][j] - matrixB[i][j];
        }
    }
}

vector<vector<double>> DivideAndConquer(const vector<vector<double>> &matrixA, const vector<vector<double>> &matrixB, int size) {
    //Creating the final matrix which will contain the completed multiplication
    vector<double> finalRows(size, 0);
    vector<vector<double> > finalMatrix(size, finalRows);

    //Break statement to end recursion and begin back through stack
    if (size <= 2) {
        NaiveMultiplication(matrixA, matrixB, finalMatrix, size);
    }
    else {
        //Dividing size by 2
        int index = (size / 2);

        //Initializing submatrices
        vector<double> rows(index, 0);
        vector<vector<double> > matrixC00(index, rows);
        vector<vector<double> > matrixC01(index, rows);
        vector<vector<double> > matrixC10(index, rows);
        vector<vector<double> > matrixC11(index, rows);

        vector<vector<double> > matrixA00(index, rows);
        vector<vector<double> > matrixA01(index, rows);
        vector<vector<double> > matrixA10(index, rows);
        vector<vector<double> > matrixA11(index, rows);

        vector<vector<double> > matrixB00(index, rows);
        vector<vector<double> > matrixB01(index, rows);
        vector<vector<double> > matrixB10(index, rows);
        vector<vector<double> > matrixB11(index, rows);

        //Filling submatrices
        for (int i = 0; i < index; i++) {
            for (int j = 0; j < index; j++) {

                matrixA00[i][j] = matrixA[i][j];
                matrixA01[i][j] = matrixA[i][j + index];
                matrixA10[i][j] = matrixA[i + index][j];
                matrixA11[i][j] = matrixA[i + index][i + index];

                matrixB00[i][j] = matrixB[i][j];
                matrixB01[i][j] = matrixB[i][j + index];
                matrixB10[i][j] = matrixB[i + index][j];
                matrixB11[i][j] = matrixB[i + index][i + index];
            }
        }

        //Start of recursion
        //c00 = a00*b00 + a01*b10
        AddMatrices(DivideAndConquer(matrixA00, matrixB00, index), DivideAndConquer(matrixA01, matrixB10, index), matrixC00, index);
        //c01 = a00*b01 + a01*b11                                                        
        AddMatrices(DivideAndConquer(matrixA00, matrixB01, index), DivideAndConquer(matrixA01, matrixB11, index), matrixC01, index);
        //c10 = a10*b00 + a11*b01                                                 
        AddMatrices(DivideAndConquer(matrixA10, matrixB00, index), DivideAndConquer(matrixA11, matrixB10, index), matrixC10, index);
        //c11 = a10*b01 + a11*b11                                             
        AddMatrices(DivideAndConquer(matrixA10, matrixB01, index), DivideAndConquer(matrixA11, matrixB11, index), matrixC11, index);

        //Returning values into finalMatrix
        for (int i = 0; i < index; i++) {
            for (int j = 0; j < index; j++) {
                finalMatrix[i][j] = matrixC00[i][j];
                finalMatrix[i][j + index] = matrixC01[i][j];
                finalMatrix[i + index][j] = matrixC10[i][j];
                finalMatrix[i + index][j + index] = matrixC11[i][j];
            }
        }
    }

    return finalMatrix;
}

vector<vector<double> > DivideAndStrassen(vector<vector<double>>& matrixA, vector<vector<double>>& matrixB, int size) {
    using namespace matrix;

    //Dividing size by 2
    int index = (size / 2);

    //Creating the final matrix which will contain the completed multiplication
    vector<double> finalRows(size, 0);
    vector<vector<double> > finalMatrix(size, finalRows);

    //Break statement to end recursion and begin back through stack
    if (size <= 2) {
        NaiveMultiplication(matrixA, matrixB, finalMatrix, size);
    }
    else {

        //Filling submatrices
        for (int state = 1; state < 8; state++) {
            for (int i = 0; i < index; i++) {
                for (int j = 0; j < index; j++) {
                    A00[i][j] = matrixA[i][j];
                    A01[i][j] = matrixA[i][j + index];
                    A10[i][j] = matrixA[i + index][j];
                    A11[i][j] = matrixA[i + index][i + index];

                    B00[i][j] = matrixB[i][j];
                    B01[i][j] = matrixB[i][j + index];
                    B10[i][j] = matrixB[i + index][j];
                    B11[i][j] = matrixB[i + index][i + index];

                    switch (state) {
                    case 1:
                        AddMatrices(A00, A11, tempA, index);
                        AddMatrices(B00, B11, tempB, index);
                        M1 = DivideAndStrassen(tempA, tempB, index);
                        break;
                    case 2:
                        AddMatrices(A10, A11, tempA, index);
                        M2 = DivideAndStrassen(tempA, B00, index);
                        break;
                    case 3:
                        SubMatrices(A10, A11, tempA, index);
                        M3 = DivideAndStrassen(A00, tempA, index);
                        break;
                    case 4:
                        SubMatrices(B10, B00, tempA, index);
                        M4 = DivideAndStrassen(A11, tempA, index);
                        break;
                    case 5:
                        AddMatrices(A00, A01, tempA, index);
                        M5 = DivideAndStrassen(tempA, B11, index);
                        break;
                    case 6:
                        SubMatrices(A10, A00, tempA, index);
                        AddMatrices(B00, B01, tempB, index);
                        M6 = DivideAndStrassen(tempA, tempB, index);
                        break;
                    case 7:
                        SubMatrices(A01, A11, tempA, index);
                        AddMatrices(B10, B11, tempB, index);
                        M7 = DivideAndStrassen(tempA, tempB, index);
                        break;
                    }

                }
            }
        }
        //Returning values into finalMatrix
        for (int i = 0; i < index; i++) {
            for (int j = 0; j < index; j++) {
                //C00 = M1 + M4 - M5 + M7
                AddMatrices(M1, M4, tempA, index);
                AddMatrices(M5, M7, tempB, index);
                SubMatrices(tempA, tempB, tempA, index);
                finalMatrix[i][j] = tempA[i][j];
                //C01 = M3 + M5
                AddMatrices(M3, M5, tempA, index);
                finalMatrix[i][j + index] = tempA[i][j];
                //C10 = M2 + M4
                AddMatrices(M2, M4, tempA, index);
                finalMatrix[i + index][j] = tempA[i][j];
                //C11 = M1 + M2 + M3 + M6
                SubMatrices(M1, M2, tempA, index);
                AddMatrices(M3, M6, tempB, index);
                AddMatrices(tempA, tempB, tempA, index);
                finalMatrix[i + index][j + index] = tempA[i][j];
            }
        }
    }
    return finalMatrix;
}

void printMatrix(vector<vector<double>> matrix, int size) {
    for (int i = 0; i <= size - 1; i++) {
        for (int j = 0; j <= size - 1; j++) {
            cout << matrix[i][j] << ",";
        }
        cout << endl;
    }
}

int main()
{


    vector<vector<double>> matrixA = {
        {2,1,1,1},
        {1,1,1,1},
        {1,1,1,1},
        {1,1,1,1},
    };
    vector<vector<double>> matrixB = {
        {1,1,1,1},
        {1,1,1,1},
        {1,1,1,1},
        {1,1,1,1},
    };
    vector<vector<double>> matrixC = {
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
    };

    //Matrix(matrixA, matrixB, matrixC, size);

    /*
    //Naive Multiplication display
    AddMatrices(matrixA, matrixB, matrixC, SIZE);
    printMatrix(matrixC, SIZE);

    cout << endl;
    */
    //Divide and conquer display
    printMatrix(DivideAndConquer(matrixA, matrixB, SIZE), SIZE);
    cout << endl;
    //Divide and Strassen
    printMatrix(DivideAndStrassen(matrixA, matrixB, SIZE), SIZE);

}
