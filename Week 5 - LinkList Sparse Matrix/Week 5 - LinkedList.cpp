// Week 5 - LinkedList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cassert>
#include <tuple>

//Uncomment to remove debug
//#define NDEBUG

using namespace std;

//Node class
class Node 
{
public: //public methods
    double value; //Value in node
    Node* next; //Pointer to next node
    //Constructors
    Node()
    {
        value = 0;
        next = NULL;
    }

    Node(double data)
    {
        value = data;
        next = NULL;
    }
    //Add destructors
};

class LinkedList {
private:
    Node* head; //Pointer to head of list
public:

    //Constructorss
    LinkedList()
    {
        //Node();
        head = NULL;
        length = -1;
    }

    //Overloading [] operator to access elements in array style
    double operator[](int index)
    {
        return get(index);
    }

    int length; //Stores length of list

    double get(int index)
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
        assert(("Index not valid.", 0 <= index && index <= length));
        Node* temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        temp->value = data;
    }

    void DeleteNode(int index)
    {
        assert(("Index not valid.", 0 <= index && index <= length));
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

    void InsertNode(int index, double data)
    {
        assert(("Index not valid.", 0 <= index && index <= length));
        //Create new Node
        Node* newNode = new Node(data);

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

    void InsertHead(double data)
    {
        //Create new node
        Node* newNode = new Node(data);

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

    void InsertTail(double data)
    {
        //Create new Node
        Node* newNode = new Node(data);

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
            cout << temp->value << " ";
            temp = temp->next;
        }
    }

};

/*
class SparseMatrix
{
private:
    int rows;
    int cols;

    LinkedList rowArray[];
public:

    SparseMatrix(int initRows, int initCols)
    {
        rows = initRows;
        cols = initCols;

        rowArray = {}
    }

};
*/



int main()
{
    LinkedList list;


    list.InsertTail(1.0);
    list.InsertTail(2.0);
    list.InsertTail(3.0);
    list.InsertHead(0.0);

    list.PrintList();
    cout << endl;

    cout << list[2] << endl;


    list.PrintList();
    cout << endl;
}