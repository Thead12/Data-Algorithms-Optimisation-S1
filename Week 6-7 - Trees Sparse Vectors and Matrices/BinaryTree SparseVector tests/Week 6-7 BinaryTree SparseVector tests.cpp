//============== Required includes ============== 
#include <iostream>
#include<vector>

//Uncomment to remove debug
//#define NDEBUG
#include<cassert>

//============== Dependent headerfiles ==============
#include "BinaryTreeSparseVector.h"

int main()
{
    using namespace BinaryTree;

    // Test Unbalanced SparseVector
    Unbalanced::SparseVector<double> unbalancedVector;
    unbalancedVector.insert(2, 5.6);
    unbalancedVector.insert(5, -3.2);
    unbalancedVector.insert(0, 8.1);
    unbalancedVector.insert(3, 2.7);

    std::cout << "Unbalanced Sparse Vector:" << std::endl;
    unbalancedVector.print();
    std::cout << "Value at index 5: " << unbalancedVector.getValue(5) << std::endl;
    assert(unbalancedVector.getValue(5) == -3.2);
    std::cout << std::endl;

    // Test Balanced SparseVector
    Balanced::SparseVector<double> balancedVector;
    balancedVector.insert(2, 5.6);
    balancedVector.insert(5, -3.2);
    balancedVector.insert(0, 8.1);
    balancedVector.insert(3, 2.7);

    std::cout << "Balanced Sparse Vector:" << std::endl;
    balancedVector.print();
    std::cout << "Value at index 5: " << balancedVector.getValue(5) << std::endl;
    assert(balancedVector.getValue(5) == -3.2);
    balancedVector.printBFRange();
    std::cout << std::endl;
}
