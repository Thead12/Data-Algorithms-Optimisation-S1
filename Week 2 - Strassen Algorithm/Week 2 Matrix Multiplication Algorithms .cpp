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
                matrixC[i][j] = matrixC[i][j] + (matrixA[i][k]*matrixB[k][j]);
            }
        }
    }
}

void AddMatrix(
    vector<vector<int> > matrixA,
    vector<vector<int> > matrixB,
    vector<vector<int> >& matrixC,
    int index) {
    for (int i = 0; i <= index; i++) {
        for (int j = 0; j <= index; j++) {
            matrixC[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }
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
        {1,1,1,1},
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

    //AddMatrix(matrixA, matrixB, matrixC, size);
    NaiveMultiplication(matrixA, matrixB, matrixC, size);

    printMatrix(matrixC, size);
    
    
}



