//============== Required includes ============== 
#include <iostream>
#include<vector>

//Uncomment to remove debug
//#define NDEBUG
#include<cassert>

//============== Dependent headerfiles ==============
#include "CSRSparseMatrix.h"

int main()
{
    using namespace CSR;
    
    // Test constructor and getters
    std::vector<std::vector<double>> vectorA = { {4, 0, 0},{0, 0, 1},{0, 2, 0} };
    SparseMatrix<double> matrixA(vectorA);
    assert(matrixA.getNumRows() == 3);
    assert(matrixA.getNumCols() == 3);

    // Test set and get methods
    matrixA.set(0, 0, 1.5);
    matrixA.set(1, 2, -3.2);
    matrixA.set(2, 1, 2.0);

    assert(matrixA.get(0, 0) == 1.5);
    assert(matrixA.get(1, 2) == -3.2);
    assert(matrixA.get(2, 1) == 2.0);

    // Test addition and subtraction
    std::vector<std::vector<double>> vectorB = { {4, 0, 0},{0, 0, 1},{0, 2, 0} };
    SparseMatrix<double> matrixB(vectorB);
    matrixB.set(0, 0, 0.5);
    matrixB.set(1, 2, 1.2);
    matrixB.set(2, 1, -1.0);

    SparseMatrix<double> resultAddition = matrixA.add(matrixB);
    SparseMatrix<double> resultSubtraction = matrixA.subtract(matrixB);

    assert(resultAddition.get(0, 0) == 2.0);
    assert(resultAddition.get(1, 2) == -2.0);
    assert(resultAddition.get(2, 1) == 1.0);

    assert(resultSubtraction.get(0, 0) == 1.0);
    assert(resultSubtraction.get(1, 2) == -4.4);
    assert(resultSubtraction.get(2, 1) == 3.0);

    // Test multiplication
    std::vector<std::vector<double>> vectorC = { {4, 0},{0, 5},{6, 0} };
    SparseMatrix<double> matrixC(vectorC);
    matrixC.set(0, 0, 2.0);
    matrixC.set(1, 1, -1.5);
    matrixC.set(2, 0, 3.0);

    SparseMatrix<double> resultMultiplication = matrixA.multiply(matrixC);

    assert(resultMultiplication.get(0, 0) == 3.0);
    assert(resultMultiplication.get(1, 1) == 0.0);
    assert(resultMultiplication.get(2, 1) == -3);

    // Test print methods
    std::cout << "Sparse Matrix A:" << std::endl;
    matrixA.printSparse();
    std::cout << std::endl;

    std::cout << "Dense Matrix A:" << std::endl;
    matrixA.printDense();
    std::cout << std::endl;

    std::cout << "Sparse Matrix B:" << std::endl;
    matrixB.printSparse();
    std::cout << std::endl;

    std::cout << "Dense Matrix B:" << std::endl;
    matrixB.printDense();
    std::cout << std::endl;

    std::cout << "Sparse Matrix C:" << std::endl;
    matrixC.printSparse();
    std::cout << std::endl;

    std::cout << "Dense Matrix C:" << std::endl;
    matrixC.printDense();
    std::cout << std::endl;

    std::cout << "Result of Multiplication:" << std::endl;
    resultMultiplication.printSparse();
    std::cout << std::endl;

    std::cout << "Result of Multiplication:" << std::endl;
    resultMultiplication.printDense();
    std::cout << std::endl;
}
