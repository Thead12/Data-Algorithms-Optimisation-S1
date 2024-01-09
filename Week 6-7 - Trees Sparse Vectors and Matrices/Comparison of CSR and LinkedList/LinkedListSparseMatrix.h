#pragma once

// SparseMatrix class using LinkedList representation
//============== Basic functions ==============
// SparseNode and SparseLinkedList act as a backend for the SparseMatrix class
// AddSparse() and SubSparse() takes LinkedListSparseMatrix as input
// AddDense() and SubDense() takes DenseMatrix inputs and outputs DenseMatrices - Could further improve this functionality

//============== Required includes ============== 
#include <iostream>
#include<vector>

//Uncomment to remove debug
//#define NDEBUG
#include<cassert>

//============== Dependent headerfiles ==============
#include "matrix.h"

namespace LinkedList {

    //Node class
    template<typename T>
    class SparseNode
    {
    public: //public methods
        std::vector<T> value; //Value in node
        SparseNode<T>* next; //Pointer to next SparseNode
        //Constructors
        SparseNode()
        {
            value = { nullptr, nullptr };
            next = nullptr;
        }

        SparseNode(T col, T data)
        {
            assert(("Column index must be an integer", floor(col) == ceil(col)));
            value = { col, data };
            next = nullptr;
        }
    };

    template<typename T>
    class SparseLinkedList {
    private:
        SparseNode<T>* head; //Pointer to head of list
        int length; //Stores length of list
    public:

        //Constructors
        SparseLinkedList()
        {
            //SparseNode();
            head = nullptr;
            length = 0;
        }

        //Overloading [] operator to access elements in array style
        std::vector<T> operator[](int index)
        {
            return get(index);
        }

        std::vector<T> get(int index)
        {
            assert(("Index not valid.", 0 <= index && index <= length));
            SparseNode<T>* temp = head;
            for (int i = 0; i < index; i++) {
                temp = temp->next;
            }
            return temp->value;
        }

        void set(int index, double data)
        {
            assert(("Index not valid.", 0 <= index && index <= length - 1));
            SparseNode<T>* temp = head;
            for (int i = 0; i < index; i++) {
                temp = temp->next;
            }
            temp->value[1] = data;
        }

        int size()
        {
            return length;
        }

        void DeleteNode(int index)
        {
            assert(("Index not valid.", 0 <= index && index < length));
            //Delete at head
            if (index == 0) {
                SparseNode<T>* temp = head;
                //Assign next node as head
                head = head->next;
                //Delete old head SparseNode
                delete temp;

                length--;
                return;
            }
            else {
                //Traverse till index
                SparseNode<T>* temp1 = head;
                SparseNode<T>* temp2 = head->next;

                //Traverse till indexx
                for (int i = 0; i < index - 1; i++) {
                    temp1 = temp2;
                    temp2 = temp2->next;
                }

                temp1->next = temp2->next;

                delete temp2;

                length--;
                return;
            }
        }

        //Inserts new node behind given index
        void InsertBehind(int index, double col, T data)
        {
            //Create new Node
            SparseNode<T>* newNode = new SparseNode<T>(col, data);

            //If list is empty
            if (head == nullptr) {
                head = newNode;

                length++;
                return;
            }
            else if (index == 0) { //Edge case where insertion point is at the start of the LinkedList
                InsertHead(col, data);
            }
            else {
                //Traverse till index
                SparseNode<T>* temp = head;
                for (int i = 0; i < index - 1; i++) {
                    temp = temp->next;
                }

                //Insert at index
                newNode->next = temp->next;
                temp->next = newNode;

                length++;
                return;
            }
        }

        //Inserts new node infront of given index
        void InsertForward(int index, double col, T data) {
            //Creat new node
            SparseNode<T>* newNode = new SparseNode(col, data);

            //If list if empty
            if (head == nullptr) {
                head = newNode;

                length++;
            }
            else if (index == length) { //Edge case where the insertion point is at the end of the LinkedList
                InsertTail(col, data);
            }
            else {
                //Traverse till index
                SparseNode<T>* temp = head;
                for (int i = 0; i < index; i++) {
                    temp = temp->next;
                }
                //Insert at index
                newNode->next = temp->next;
                temp->next = newNode;

                length++;
            }
        }

        void InsertHead(double col, T data)
        {
            //Create new node
            SparseNode<T>* newNode = new SparseNode<T>(col, data);

            //If list is empty
            if (head == nullptr) {
                head = newNode;

                length++;
                return;
            }

            //Make new node point to head
            newNode->next = head;

            //Make new node into head
            head = newNode;

            length++;
            return;
        }

        void InsertTail(T col, T data)
        {
            assert(("Column index must be an integer", floor(col) == ceil(col)));
            //Create new SparseNode
            SparseNode<T>* newNode = new SparseNode<T>(col, data);

            //If list is empty
            if (head == nullptr) {
                head = newNode;

                length++;
                return;
            }
            else {
                //Traverse till end of list
                SparseNode<T>* temp = head;
                while (temp->next != nullptr) {

                    //Update temp
                    temp = temp->next;
                }

                //Insert at the last
                temp->next = newNode;

                length++;
                return;
            }

        }

        void PrintList()
        {
            SparseNode<T>* temp = head;

            //Check for empty list
            if (head == nullptr) {
                std::cout << "List empty" << std::endl;
                return;
            }

            while (temp != nullptr) {
                std::cout << temp->value[0] << ", " << temp->value[1] << std::endl;
                temp = temp->next;
            }
        }

    };

    //Sparse matrix class using LinkedList approach
    template<typename T>
    class SparseMatrix
    {
    private:
        int numRows; int numCols;

        std::vector<SparseLinkedList<T>> rowsArray;
    public:

        //================ Constructors =====================

        //Constructor for creating empty Sparse matrix
        SparseMatrix(int initRows, int initCols)
        {
            //Initialising numRows and cols
            numRows = initRows; numCols = initCols;

            std::vector<SparseLinkedList<T>> temp(numRows);

            rowsArray = temp;
        }

        //Constructor for converting from vectors
        SparseMatrix(std::vector<std::vector<T>> denseVector) : numRows(denseVector.size()), numCols(denseVector[0].size()) //Constructor to make matrix from vector
        {
            std::vector<SparseLinkedList<T>> temp(numRows); //Creating empty temp LinkedList vector to store future contents of rowsArray

            assert(("Size of matrices do not match", denseVector.size() == numRows && denseVector[0].size() == numCols));

            for (int i = 0; i < numRows; i++) {
                temp[i] = SparseLinkedList<T>(); //Initialising LinkedList for row i
                for (int j = 0; j < numCols; j++) {
                    if (denseVector[i][j] != 0.0) {
                        temp[i].InsertTail(j, denseVector[i][j]); //Takes none 0 values and created a new node at the tail
                    }
                }
            }

            rowsArray = temp;
            return;
        }

        //Constructor for converting from denseMatrices
        SparseMatrix(Dense::Matrix<T> denseMatrix) : numRows(denseMatrix.getNumRows()), numCols(denseMatrix.getNumCols()) //Constructor to make sparse matrix from dense Matrix class
        {
            std::vector<SparseLinkedList<T>> temp(numRows); //Creating empty temp LinkedList vector to store future contents of rowsArray

            assert(("Size of matrices do not match", denseMatrix.getNumRows() == numRows && denseMatrix.getNumCols() == numCols));

            for (int i = 0; i < numRows; i++) {

                temp[i] = SparseLinkedList<T>(); //Initialising LinkedList for row i

                for (int j = 0; j < numCols; j++) {
                    if (denseMatrix(i, j) != 0.0) {
                        temp[i].InsertTail(j, denseMatrix(i, j)); //Takes none 0 values and creates a new node at the tail
                    }
                }
            }

            rowsArray = temp;
            return;
        }

        //Getters ==================== Setters 
        int getNumRows()
        {
            return numRows;
        }

        int getNumCols()
        {
            return numCols;
        }

        T get(int i, int j)
        {
            //checking if indexes are valid
            assert(("Row index not valid.", 0 <= i && i < numRows));
            assert(("Column index not valid.", 0 <= j && j < numCols));

            //Loop to traverse SparseMatrix
            for (int m = 0; m < numRows; m++) { //Looping through row arrays
                int lengthOfList = rowsArray[m].size();
                for (int n = 0; n < lengthOfList; n++) { //Looping through all nodes in column LinkedList

                    double columnIndex = rowsArray[m].get(n)[0]; //Gets column data from node

                    if (m == i && columnIndex == j) {
                        return rowsArray[m].get(n)[1];
                    }
                }
            }

            return T(); // If i,j coords do not match in sparse matrix then it must be zero
        }

        //This function can both replace an existing node and create a new one depending on the current value in the matrix
        void set(int row, int col, double data) {
            assert(("Row index not valid.", 0 <= row && row < numRows));
            assert(("Column index not valid.", 0 <= col && col < numCols));
            assert(("Cannot set 0 value, use .Remove() instead.", data != 0));

            int currentValue = get(row, col);

            if (currentValue == 0 && rowsArray[row].size() == 0) { // Insert a new node if the current value is 0 and there is no node
                rowsArray[row].InsertTail(col, data);
            }
            else if (currentValue == 0) { // Insert the new node at the appropriate position
                int columnIndex = 0;
                for (int n = 0; n < rowsArray[row].size(); ++n) {
                    columnIndex = rowsArray[row].get(n)[0];
                    if (col < columnIndex) {
                        rowsArray[row].InsertBehind(n, col, data); // Insert before the current node
                        return;
                    }
                }
                rowsArray[row].InsertTail(col, data); // Insert at the end if col is greater than all existing columns
            }
            else { // Non-zero current value, update or set the value
                for (int n = 0; n < rowsArray[row].size(); ++n) {
                    int columnIndex = rowsArray[row].get(n)[0];
                    if (col == columnIndex) {
                        rowsArray[row].set(n, data); // Update the existing node
                        return;
                    }
                    else if (col < columnIndex) {
                        rowsArray[row].InsertBehind(n, col, data); // Insert before the current node
                        return;
                    }
                }
                rowsArray[row].InsertTail(col, data); // Insert at the end if col is greater than all existing columns
            }
        }


        //Used to set values of the matrix back to zero
        void Remove(int col, int row)
        {
            assert(("Row index not valid.", 0 <= row && row < numRows));
            assert(("Column index not valid.", 0 <= col && col < numCols));

            for (int n = 0; n < rowsArray[col].size(); n++) { //Traversing linked list to find correct place to delete
                int columnIndex = rowsArray[col].get(n)[0]; //Gets column data from node
                if (row == columnIndex) {
                    rowsArray[col].DeleteNode(n); //Deleting node effectively turns value to zero
                    return;
                }
            }
        }

        SparseMatrix AddSparse(SparseMatrix matrix2)
        {
            int matrix2Rows = matrix2.getNumRows(); int matrix2Cols = matrix2.getNumCols(); //Getting the number of columns and numRows in matrix 2
            assert(("Matrix dimensions do not match.", numRows == matrix2Rows && numCols == matrix2Cols)); //Ensuring the dimensions of the two matrices are the same

            SparseMatrix result = SparseMatrix(numRows, numCols);

            double sum = 0; //Variable to store the result of the addition operation

            for (int i = 0; i < numRows; i++) {
                for (int j = 0; j < numCols; j++) {

                    sum = get(i, j) + matrix2.get(i, j); //Sums values from matrix1 (self) and matrix2

                    if (sum != 0) {
                        result.set(i, j, sum);
                    }

                }
            }

            return result;
        }

        SparseMatrix SubtractSparse(SparseMatrix matrix2)
        {
            int matrix2Rows = matrix2.getNumRows(); int matrix2Cols = matrix2.getNumCols(); //Getting the number of columns and numRows in matrix 2
            assert(("Matrix dimensions do not match.", numRows == matrix2Rows && numCols == matrix2Cols)); //Ensuring the dimensions of the two matrices are the same

            SparseMatrix result = SparseMatrix(numRows, numCols);

            double difference = 0; //Variable to store the result of the addition operation

            for (int i = 0; i < numRows; i++) {
                for (int j = 0; j < numCols; j++) {

                    difference = get(i, j) - matrix2.get(i, j); //Subtracts values from matrix1 (self) and matrix2

                    if (difference != 0) {
                        result.set(i, j, difference);
                    }

                }
            }

            return result;
        }

        Dense::Matrix<T> AddDense(Dense::Matrix<T> matrix2)
        {
            int matrix2Rows = matrix2.getNumRows(); int matrix2Cols = matrix2.getNumCols(); //Getting the number of columns and rows in matrix 2
            assert(("Matrix dimensions do not match.", numRows == matrix2Rows && numCols == matrix2Cols)); //Ensuring the dimensions of the two matrices are the same

            Dense::Matrix result = Dense::Matrix(numRows, numCols);

            //Traversing Sparse matrix and adding that to the dense result matrix first
            for (int row = 0; row < numRows; row++) {
                int lengthOfList = rowsArray[row].size();

                for (int j = 0; j < lengthOfList; j++) {

                    std::vector<double> colAndValue = rowsArray[row].get(j); //Columns value is stores in [0] and value is stored in [1] of the vector

                    result.set(row, colAndValue[0], colAndValue[1]);
                }
            }

            result = result.sum(matrix2); //Adding dense matrix2 to dense matrix version of original sparse matrix

            return result;
        }

        Dense::Matrix<T> SubtractDense(Dense::Matrix<T> matrix2)
        {
            int matrix2Rows = matrix2.getNumRows(); int matrix2Cols = matrix2.getNumCols(); //Getting the number of columns and rows in matrix 2
            assert(("Matrix dimensions do not match.", numRows == matrix2Rows && numCols == matrix2Cols)); //Ensuring the dimensions of the two matrices are the same

            Dense::Matrix<T> result(numRows, numCols);

            //Traversing Sparse matrix and adding that to the dense result matrix first
            for (int row = 0; row < numRows; row++) {
                int lengthOfList = rowsArray[row].size();
                for (int j = 0; j < lengthOfList; j++) {

                    std::vector<double> colAndValue = rowsArray[row].get(j); //Columns value is stored in [0] and value is stored in [1] of the vector

                    result.set(row, colAndValue[0], colAndValue[1]);
                }
            }

            result = result.subtract(matrix2); //Subtracting dense matrix2 from dense matrix version of original sparse matrix

            return result;
        }

        void PrintSparse()
        {
            for (int i = 0; i < numRows; i++) {
                int lengthOfList = rowsArray[i].size();
                for (int j = 0; j < lengthOfList; j++) {
                    std::cout << i << "," << rowsArray[i].get(j)[0] << " --- " << rowsArray[i].get(j)[1] << std::endl;
                }
            }
            return;
        }

        void PrintDense()
        {
            for (int i = 0; i < numRows; i++) {
                for (int j = 0; j < numCols; j++) {
                    std::cout << get(i, j) << ", ";
                }
                std::cout << std::endl;
            }
        }

        T operator () (int i, int j) {
            return get(i, j);
        }
    };
}
