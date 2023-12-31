#pragma once

//LinkedList class for week 5

#include <iostream>
#include <vector>

//Uncomment to remove debug
//#define NDEBUG
#include <cassert>

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
        value = 0.0;
        next = NULL;
    }

    Node(double data)
    {
        value = data;
        next = NULL;
    }
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

    //Constructor to set the first value in LinkedList
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
        assert(("Index not valid.", 0 <= index && index <= length - 1));
        Node* temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        temp->value = data;
    }

    void DeleteNode(int index)
    {
        assert(("Index not valid.", 0 <= index && index <= length - 1));
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

    void InsertNode(int index, double col, double data)
    {
        assert(("Index not valid.", 0 <= index && index <= length - 1));
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

    //Inserts new node behind given index
    void InsertBehind(int index, double data)
    {
        //Create new Node
        Node* newNode = new Node(data);

        //If list is empty
        if (head == NULL) {
            head = newNode;

            length++;
            return;
        }
        else if (index == 0) { //Edge case where insertion point is at the start of the LinkedList
            InsertHead(data);
        }
        else {
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
    void InsertForward(int index, double data) {
        //Creat new node
        Node* newNode = new Node(data);

        //If list if empty
        if (head == NULL) {
            head = newNode;

            length++;
        }
        else if (index == length) { //Edge case where the insertion point is at the end of the LinkedList
            InsertTail(data);
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
            cout << temp->value << endl;
            temp = temp->next;
        }
    }
};
