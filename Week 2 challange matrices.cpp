// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;

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
    for (int i = 0; i <= index - 1; i++) {
        for (int j = 0; j <= index - 1; j++) {
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

        vector<vector<int> > matrixA00(index, rows);
        vector<vector<int> > matrixA01(index, rows);
        vector<vector<int> > matrixA10(index, rows);
        vector<vector<int> > matrixA11(index, rows);

        vector<vector<int> > matrixB00(index, rows);
        vector<vector<int> > matrixB01(index, rows);
        vector<vector<int> > matrixB10(index, rows);
        vector<vector<int> > matrixB11(index, rows);

        vector<vector<int> > matrixM1(index, rows);
        vector<vector<int> > matrixM2(index, rows);
        vector<vector<int> > matrixM3(index, rows);
        vector<vector<int> > matrixM4(index, rows);
        vector<vector<int> > matrixM5(index, rows);
        vector<vector<int> > matrixM6(index, rows);
        vector<vector<int> > matrixM7(index, rows);

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

        //Computing the new matrices

        //M1 = (A00 + A11)(B00 + B11)
        matrixM1 = DivideAndStrassen(AddStrassen(matrixA00, matrixA11, index), AddStrassen(matrixB00, matrixB11, index));
        //M2 = (A10 + A11)B00
        matrixM2 = DivideAndStrassen(AddStrassen(matrixA10, matrixA11, index), matrixB00);
        //M3 = A00(B01 - B11)
        matrixM3 = DivideAndStrassen(matrixA00, SubStrassen(matrixA10, matrixA11, index));
        //M4 = A11(B10 - B00)
        matrixM4 = DivideAndStrassen(matrixA11, SubStrassen(matrixB10, matrixB00, index));
        //M5 = (A00 + A01)B11
        matrixM5 = DivideAndStrassen(AddStrassen(matrixA00, matrixA01, index), matrixB11);
        //M6 = (A10 - A00)(B00 + B01)
        matrixM6 = DivideAndStrassen(SubStrassen(matrixA10, matrixA00, index), AddStrassen(matrixB00, matrixB01, index));
        //M7 = (A01 - A11)(B10 + B11)
        matrixM7 = DivideAndStrassen(SubStrassen(matrixA01, matrixA11, index), AddStrassen(matrixB10, matrixB11, index));

        //Returning values into finalMatrix
        for (int i = 0; i < index; i++) {
            for (int j = 0; j < index; j++) {
                //C00 = M1 + M4 - M5 + M7
                finalMatrix[i][j] = SubStrassen(AddStrassen(matrixM1, matrixM4, index), AddStrassen(matrixM5, matrixM7, index), index)[i][j];
                //C01 = M3 + M5
                finalMatrix[i][j + index] = AddStrassen(matrixM3, matrixM5, index)[i][j];
                //C10 = M2 + M4
                finalMatrix[i + index][j] = AddStrassen(matrixM2, matrixM4, index)[i][j];
                //C11 = M1 + M2 + M3 + M6
                finalMatrix[i + index][j + index] = AddStrassen(SubStrassen(matrixM1, matrixM2, index), AddStrassen(matrixM3, matrixM6, index), index)[i][j];
            }
        }
    }

    return finalMatrix;

}

void printMatrix(vector<vector<int> > matrix, int size) {
    for (int i = 0; i <= size; i++) {
        for (int j = 0; j <= size; j++) {
            cout << matrix[i][j];
        }
        cout << endl;
    }
}

int main()
{
    int size = 3;

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
    printMatrix(DivideAndStrassen(matrixA, matrixB), size);

}



