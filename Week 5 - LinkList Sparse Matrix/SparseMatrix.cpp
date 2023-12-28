// Week 5 - LinkedList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cassert>
#include <vector>

#include "matrix.h"

//Uncomment to remove debug
//#define NDEBUG

using namespace std;

//Node class
class Node
{
public: //public methods
    vector<double> value; //Value in node
    Node* next; //Pointer to next node
    //Constructors
    Node()
    {
        value = { 0.0, 0.0 };
        next = NULL;
    }

    Node(double col, double data)
    {
        value = { col, data };
        next = NULL;
    }
    //Add destructors
};

class LinkedList {
private:
    Node* head; //Pointer to head of list
    int length; //Stores length of list
public:

    //Constructors
    LinkedList()
    {
        //Node();
        head = NULL;
        length = 0;
    }

    //Overloading [] operator to access elements in array style
    vector<double> operator[](int index)
    {
        return get(index);
    }

    vector<double> get(int index)
    {
        assert(("Index not valid.", 0 <= index && index <= length));
        Node* temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        return temp->value;
    }

    void set(int index, double data)
    {
        assert(("Index not valid.", 0 <= index && index <= length - 1));
        Node* temp = head;
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

            Node* temp = head;
            //Assign next node as head
            head = head->next;
            //Delete old head node
            delete temp;

            length--;
            return;
        }
        else {
            //Traverse till index
            Node* temp1 = head;
            Node* temp2 = head->next;

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
    void InsertBehind(int index, double col, double data)
    {
        //Create new Node
        Node* newNode = new Node(col, data);

        //If list is empty
        if (head == NULL) {
            head = newNode;

            length++;
            return;
        } else if (index == 0) { //Edge case where insertion point is at the start of the LinkedList
            InsertHead(col, data);
        } else {
            //Traverse till index
            Node* temp = head;
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
    void InsertForward(int index, double col, double data) {
        //Creat new node
        Node* newNode = new Node(col, data);

        //If list if empty
        if (head == NULL) {
            head = newNode;

            length++;
        } else if (index == length) { //Edge case where the insertion point is at the end of the LinkedList
            InsertTail(col, data);
        } else {
            //Traverse till index
            Node* temp = head;
            for (int i = 0; i < index; i++) {
                temp = temp->next;
            }
            //Insert at index
            newNode->next = temp->next;
            temp->next = newNode;

            length++;
        }
    }

    void InsertHead(double col, double data)
    {
        //Create new node
        Node* newNode = new Node(col, data);

        //If list is empty
        if (head == NULL) {
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

    void InsertTail(double col, double data)
    {
        //Create new Node
        Node* newNode = new Node(col, data);

        //If list is empty
        if (head == NULL) {
            head = newNode;

            length++;
            return;
        }
        else {
            //Traverse till end of list
            Node* temp = head;
            while (temp->next != NULL) {

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
        Node* temp = head;

        //Check for empty list
        if (head == NULL) {
            cout << "List empty" << endl;
            return;
        }

        while (temp != NULL) {
            cout << temp->value[0] << ", " << temp->value[1] << endl;
            temp = temp->next;
        }
    }
};

//Sparse matrix class using LinkedList approach
class SparseMatrix
{
private:
    int rows;
    int cols;

    vector<LinkedList> rowsArray;
public:

    //Constructor for converting from vectors
    SparseMatrix(int initRows, int initCols, vector<vector<double>> denseMatrix) //Constructor to make matrix from vector
    {
        //Initialising rows and columns
        rows = initRows;
        cols = initCols;

        vector<LinkedList> temp(rows); //Creating empty temp LinkedList vector to store future contents of rowsArray

        assert(("Size of matrices do not match", denseMatrix.size() == rows && denseMatrix[0].size() == cols));

        for (int i = 0; i < rows; i++) {

            temp[i] = LinkedList(); //Initialising LinkedList for row i

            for (int j = 0; j < cols; j++) {
                if (denseMatrix[i][j] != 0.0) {
                    temp[i].InsertTail(j, denseMatrix[i][j]); //Takes none 0 values and created a new node at the tail
                }
            }
        }

        rowsArray = temp;
        return;
    }

    //Constructor for converting from denseMatrices
    SparseMatrix(int initRows, int initCols, Matrix denseMatrix) //Constructor to make sparse matrix from dense Matrix class
    {
        rows = initRows;
        cols = initCols;

        vector<LinkedList> temp(rows); //Creating empty temp LinkedList vector to store future contents of rowsArray

        assert(("Size of matrices do not match", denseMatrix.getrows() == rows && denseMatrix.getcolumns() == cols));

        for (int i = 0; i < rows; i++) {

            temp[i] = LinkedList(); //Initialising LinkedList for row i

            for (int j = 0; j < cols; j++) {
                if (denseMatrix(i, j) != 0.0) {
                    temp[i].InsertTail(j, denseMatrix(i, j)); //Takes none 0 values and creates a new node at the tail
                }
            }
        }

        rowsArray = temp;
        return;
    }

    double get(int i, int j)
    {
        //checking if indexes are valid
        assert(("Row index not valid.", 0 <= i && i < rows));
        assert(("Column index not valid.", 0 <= j && j < cols));

        //Loop to traverse SparseMatrix
        for (int m = 0; m < rows; m++) { //Looping through row arrays
            int lengthOfList = rowsArray[m].size();
            for (int n = 0; n < lengthOfList; n++) { //Looping through all nodes in column LinkedList

                double columnIndex = rowsArray[m].get(n)[0]; //Gets column data from node

                if (m == i && columnIndex == j) {
                    return rowsArray[m].get(n)[1];
                }
            }
        }

        return 0; // If i,j coords do not match in sparse matrix then it must be zero
    }

    //This function can both replace an existing node and create a new one depending on the current value in the matrix
    void set(int row, int col, double data) {
        assert(("Row index not valid.", 0 <= row && row < rows));
        assert(("Column index not valid.", 0 <= col && col < cols));
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
        assert(("Row index not valid.", 0 <= row && row < rows));
        assert(("Column index not valid.", 0 <= col && col < cols));

        for (int n = 0; n < rowsArray[col].size(); n++) { //Traversing linked list to find correct place to delete
            int columnIndex = rowsArray[col].get(n)[0]; //Gets column data from node
            if (row == columnIndex) {
                rowsArray[col].DeleteNode(n); //Deleting node effectively turns value to zero
                return;
            }
        }
    }

    void PrintSparse()
    {
        for (int i = 0; i < rows; i++) {
            int lengthOfList = rowsArray[i].size();
            for (int j = 0; j < lengthOfList; j++) {
                cout << i << "," << rowsArray[i].get(j)[0] << " --- " << rowsArray[i].get(j)[1] << endl;
            }
        }
        return;
    }
};


int main()
{
    
    /*
    LinkedList list;


    list.InsertTail(0, 1);
    list.InsertTail(1, 2);
    list.InsertTail(2, 3);
    list.InsertTail(3, 4);

    list.InsertBehind(3, -1, 0);

    list.PrintList();
    cout << endl;
    */
    
    

    

    vector<vector<double>> denseVector = {
        {0, 0, 0, 0},
        {100, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };

    Matrix denseMatrix = Matrix(5, 4, denseVector);

    SparseMatrix sparse = SparseMatrix(5, 4, denseVector);

    sparse.set(1, 3, 4);
    sparse.set(1, 2, 5);

    sparse.PrintSparse();
    cout << endl;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            cout << sparse.get(i, j) << ", ";
        }
        cout << endl;
    }

}
