// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;

#define SIZE 4
#define INDEX SIZE/2

namespace matrix {

    //Initializing submatrices
    vector<int> rows(INDEX, 0);

    vector<vector<int> > A00(INDEX, rows);
    vector<vector<int> > A01(INDEX, rows);
    vector<vector<int> > A10(INDEX, rows);
    vector<vector<int> > A11(INDEX, rows);
                         
    vector<vector<int> > B00(INDEX, rows);
    vector<vector<int> > B01(INDEX, rows);
    vector<vector<int> > B10(INDEX, rows);
    vector<vector<int> > B11(INDEX, rows);

}

using namespace matrix;

void NaiveMultiplication(
    vector<vector<int> > matrixA,
    vector<vector<int> > matrixB,
    vector<vector<int> >& matrixC,
    int size) {
    for (int i = 0; i <= size; i++) {
        for (int j = 0; j <= size; j++) {
            for (int k = 0; k <= size; k++) {
                matrixC[i][j] = matrixC[i][j] + (matrixA[i][k] * matrixB[k][j]);
            }
        }
    }
}

void AddMatrix(
    vector<vector<int> > matrixA,
    vector<vector<int> > matrixB,
    vector<vector<int> >& matrixC,
    int index) {
    for (int i = 0; i <= index - 2; i++) {
        for (int j = 0; j <= index - 2 ; j++) {
            matrixC[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }
}

vector<vector<int> > AddStrassen(
    vector<vector<int> > matrixA,
    vector<vector<int> > matrixB,
    int index) {
    vector<int> rows(index, 0);
    vector<vector<int> > matrixC(index, rows);
    for (int i = 0; i <= index - 1; i++) {
        for (int j = 0; j <= index - 1; j++) {
            matrixC[i][j] = (matrixA[i][j] + matrixB[i][j]);
        }
    }
    return matrixC;
}

vector<vector<int> > SubStrassen(
    vector<vector<int> > matrixA,
    vector<vector<int> > matrixB,
    int index) {
    vector<int> rows(index, 0);
    vector<vector<int>>matrixC(index, rows);
    for (int i = 0; i <= index - 1; i++) {
        for (int j = 0; j <= index - 1; j++) {
            matrixC[i][j] = (matrixA[i][j] - matrixB[i][j]);
        }
    }
    return matrixC;
}

vector<vector<int> > DivideAndConquer(
    vector<vector<int> > matrixA,
    vector<vector<int> > matrixB) {

    int size = matrixA.size();

    //Dividing size by 2
    int index = (size / 2);

    //Creating the final matrix which will contain the completed multiplication
    vector<int> finalRows(size, 0);
    vector<vector<int> > finalMatrix(size, finalRows);

    //Break statement to end recursion and begin back through stack
    if (size == 1) {
        finalMatrix[0][0] = matrixA[0][0] * matrixB[0][0];
    }
    else {

        //Initializing submatrices
        vector<int> rows(index, 0);
        vector<vector<int> > matrixC00(index, rows);
        vector<vector<int> > matrixC01(index, rows);
        vector<vector<int> > matrixC10(index, rows);
        vector<vector<int> > matrixC11(index, rows);

        vector<vector<int> > matrixA00(index, rows);
        vector<vector<int> > matrixA01(index, rows);
        vector<vector<int> > matrixA10(index, rows);
        vector<vector<int> > matrixA11(index, rows);

        vector<vector<int> > matrixB00(index, rows);
        vector<vector<int> > matrixB01(index, rows);
        vector<vector<int> > matrixB10(index, rows);
        vector<vector<int> > matrixB11(index, rows);

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
        AddMatrix(DivideAndConquer(matrixA00, matrixB00), DivideAndConquer(matrixA01, matrixB10), matrixC00, index);
        //c01 = a00*b01 + a01*b11
        AddMatrix(DivideAndConquer(matrixA00, matrixB01), DivideAndConquer(matrixA01, matrixB11), matrixC01, index);
        //c10 = a10*b00 + a11*b01
        AddMatrix(DivideAndConquer(matrixA10, matrixB00), DivideAndConquer(matrixA11, matrixB10), matrixC10, index);
        //c11 = a10*b01 + a11*b11
        AddMatrix(DivideAndConquer(matrixA10, matrixB01), DivideAndConquer(matrixA11, matrixB11), matrixC11, index);

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

vector<vector<int> > DivideAndStrassen(
    vector<vector<int> > matrixA,
    vector<vector<int> > matrixB, 
    int size) {

    //Dividing size by 2
    int index = (size / 2);

    //Creating the final matrix which will contain the completed multiplication
    vector<int> finalRows(size, 0);
    vector<vector<int> > finalMatrix(size, finalRows);



    vector<vector<int> > M1(INDEX, rows);
    vector<vector<int> > M2(INDEX, rows);
    vector<vector<int> > M3(INDEX, rows);
    vector<vector<int> > M4(INDEX, rows);
    vector<vector<int> > M5(INDEX, rows);
    vector<vector<int> > M6(INDEX, rows);
    vector<vector<int> > M7(INDEX, rows);

    //Break statement to end recursion and begin back through stack
    if (size == 1) {
        finalMatrix[0][0] = matrixA[0][0] * matrixB[0][0];
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
                        M1 = DivideAndStrassen(AddStrassen(A00, A11, index), AddStrassen(B00, B11, index), index);
                        break;
                    case 2:
                        M2 = DivideAndStrassen(AddStrassen(A10, A11, index), B00, index);
                        break;
                    case 3:
                        M3 = DivideAndStrassen(A00, SubStrassen(A10, A11, index), index);
                        break;
                    case 4:
                        M4 = DivideAndStrassen(A11, SubStrassen(B10, B00, index), index);
                        break;
                    case 5:
                        M5 = DivideAndStrassen(AddStrassen(A00, A01, index), B11, index);
                        break;
                    case 6:
                        M6 = DivideAndStrassen(SubStrassen(A10, A00, index), AddStrassen(B00, B01, index), index);
                        break;
                    case 7:
                        M7 = DivideAndStrassen(SubStrassen(A01, A11, index), AddStrassen(B10, B11, index), index);
                        break;
                    }

                }
            }
        }
        

        /*//Computing the new matrices

        //M1 = (A00 + A11)(B00 + B11)
        M1 = DivideAndStrassen(AddStrassen(A00, A11, index), AddStrassen(B00, B11, index), index);
        //M2 = (A10 + A11)B00
        //Filling submatrices
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
            }
        }
        M2 = DivideAndStrassen(AddStrassen(A10, A11, index), B00, index);
        //M3 = A00(B01 - B11)
        //Filling submatrices
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
            }
        }
        M3 = DivideAndStrassen(A00, SubStrassen(A10, A11, index), index);
        //M4 = A11(B10 - B00)
        //Filling submatrices
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
            }
        }
        M4 = DivideAndStrassen(A11, SubStrassen(B10, B00, index), index);
        //M5 = (A00 + A01)B11
        //Filling submatrices
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
            }
        }
        M5 = DivideAndStrassen(AddStrassen(A00, A01, index), B11, index);
        //M6 = (A10 - A00)(B00 + B01)
        //Filling submatrices
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
            }
        }
        M6 = DivideAndStrassen(SubStrassen(A10, A00, index), AddStrassen(B00, B01, index), index);
        //M7 = (A01 - A11)(B10 + B11)
        //Filling submatrices
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
            }
        }
        M7 = DivideAndStrassen(SubStrassen(A01, A11, index), AddStrassen(B10, B11, index), index);*/

        //Returning values into finalMatrix
        for (int i = 0; i < index; i++) {
            for (int j = 0; j < index; j++) {
                //C00 = M1 + M4 - M5 + M7
                finalMatrix[i][j] = SubStrassen(AddStrassen(M1, M4, index), AddStrassen(M5, M7, index), index)[i][j];
                //C01 = M3 + M5
                finalMatrix[i][j + index] = AddStrassen(M3, M5, index)[i][j];
                //C10 = M2 + M4
                finalMatrix[i + index][j] = AddStrassen(M2, M4, index)[i][j];
                //C11 = M1 + M2 + M3 + M6
                finalMatrix[i + index][j + index] = AddStrassen(SubStrassen(M1, M2, index), AddStrassen(M3, M6, index), index)[i][j];
            }
        }
    }

    return finalMatrix;

}

void printMatrix(vector<vector<int> > matrix, int size) {
    for (int i = 0; i <= size - 1; i++) {
        for (int j = 0; j <= size - 1; j++) {
            cout << matrix[i][j] << ",";
        }
        cout << endl;
    }
}

int main()
{
    

    vector<vector<int>> matrixA = {
        {2,1,1,1},
        {1,1,1,1},
        {1,1,1,1},
        {1,1,1,1},
    };
    vector<vector<int>> matrixB = {
        {1,1,1,1},
        {1,1,1,1},
        {1,1,1,1},
        {1,1,1,1},
    };
    vector<vector<int>> matrixC = {
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0},
    };

    //Matrix(matrixA, matrixB, matrixC, size);

    /*Naive Multiplication display
    NaiveMultiplication(matrixA, matrixB, matrixC, size);
    printMatrix(matrixC, size);*/

    /*Divide and conquer display
    printMatrix(DivideAndConquer(matrixA, matrixB), size);*/

    //Divide and Strassen
    printMatrix(DivideAndStrassen(matrixA, matrixB, SIZE), SIZE);

}


