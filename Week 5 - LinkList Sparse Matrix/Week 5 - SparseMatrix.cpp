// Week 5 - LinkedList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cassert>
#include <vector>

//#include "matrix.h"

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
        assert(("Index not valid.", 0 <= index && index <= length-1));
        Node* temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        temp->value[1] = data;
    }

    void DeleteNode(int index)
    {
        assert(("Index not valid.", 0 <= index && index <= length-1));
        //Delete at head
        if (index == 0) {

            Node* temp = head;
            //Assign next node as head
            head = head->next;
            //Delete old head node
            delete[] temp;

            length--;
            return;
        }
        else {
            //Traverse till index
            Node* temp1 = head;
            Node* temp2 = head->next;
            
            //Traverse till indexx
            for (int i = 0; i < index-1; i++) {
                temp1 = temp2;
                temp2 = temp2->next;
            }

            temp1->next = temp2->next;

            delete temp2;

            length--;
            return;
        }
    }

    void InsertNode(int index, double col, double data)
    {
        assert(("Index not valid.", 0 <= index && index <= length-1));
        //Create new Node
        Node* newNode = new Node(col, data);

        //If list is empty
        if (head == NULL) {
            head = newNode;

            length++;
            return;
        }
        else {
            //Traverse till index
            Node* temp = head;
            for (int i = 0; i < index; i++) {
                temp = temp->next;
            }

            //Insert at index
            newNode->next = temp->next;
            temp->next = newNode;

            length++;
            return;
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


class SparseMatrix
{
private:
    int rows;
    int cols;

    vector<LinkedList> rowsArray;
public:

    SparseMatrix(int initRows, int initCols, vector<vector<double>> denseMatrix)
    {
        rows = initRows;
        cols = initCols;

        vector<LinkedList> temp(rows);

        assert(("Size of matrices do not match", denseMatrix.size() == rows && denseMatrix[0].size() == cols));

        for (int i = 0; i < rows-1; i++) {

            temp[i] = LinkedList();

            for (int j = 0; j < cols-1; j++) {
                if (denseMatrix[i][j] != 0.0) {

                    temp[i].InsertTail(j, denseMatrix[i][j]);

                }
            }
        }

        rowsArray = temp;
    }

    vector<double> get(int i, int j)
    {
        assert(("Row index not valid.", 0 <= i && i <= rows));
        assert(("Column index not valid.", 0 <= j && j <= cols));

        return rowsArray[i].get(j);
    }

    void PrintMatrix()
    {
        for (int i = 0; i < rows-1; i++) {
            for (int j = 0; j < cols-1; j++) {
                cout << rowsArray[i].get(j)[0] << ", " << rowsArray[i].get(j)[1];
            }
            cout << endl;
        }
    }

};


int main()
{
    /*
    LinkedList list;


    list.InsertTail(0, 1);
    list.InsertTail(1, 2);
    list.InsertTail(2, 3);
    list.InsertHead(3, 4);

    list.PrintList();
    cout << endl;

    list.PrintList();
    cout << endl;
    */

    vector<vector<double>> dense = {
        {0, 1, 0, 0},
        {2, 0, 3, 0},
        {0, 0, 5, 2},
        {3, 0, 0, 0},
        {0, 1, 1, 0}
    };

    SparseMatrix sparse = SparseMatrix(5, 4, dense);

    sparse.PrintMatrix();
}
