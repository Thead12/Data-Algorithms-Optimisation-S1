#pragma once

//LinkedList class for week 5

//============== Required includes ============== 
//#include <iostream>
//#include<vector>

//Uncomment to remove debug
//#define NDEBUG
//#include<cassert>

//Node class
class Node
{
public: //public methods
    double value; //Value in node
    Node* next; //Pointer to next node

    //==================== Constructors ==================
    Node(); // Default constructor for Node

    Node(double data); // Constructor for Node with given data
};

class LinkedList {
private:
    Node* head; //Pointer to head of list
    int length; //Stores length of list
public:

    //==================== Constructors ==================
    LinkedList(); // Default constructor for LinkedList

    //Getters ==================== Setters 
    double& get(int index); // Getter for retrieving data at a given index
    void set(int index, double data); // Setter for updating data at a given index

    void DeleteNode(int index); // Function to delete a node at a given index
    void InsertNode(int index, double col, double data); // Function to insert a node at a given index with specific data
    void InsertBehind(int index, double data); // Function to insert a node behind a given index with specific data
    void InsertForward(int index, double data); // Function to insert a node in front of a given index with specific data
    void InsertHead(double data); // Function to insert a node at the head with specific data
    void InsertTail(double data); // Function to insert a node at the tail with specific data
    void PrintList(); // Function to print the linked list
};

// Node Class

// Default constructor for Node
Node::Node()
{
    value = 0.0;
    next = nullptr;
}

// Constructor for Node with given data
Node::Node(double data)
{
    value = data;
    next = nullptr;
}


// LinkedList Class

// Default constructor for LinkedList
LinkedList::LinkedList()
{
    head = nullptr;
    length = 0;
}

// Getter for retrieving data at a given index
double& LinkedList::get(int index)
{
    assert(("Index not valid.", 0 <= index && index <= length));
    Node* temp = head;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    return temp->value;
}

// Setter for updating data at a given index
void LinkedList::set(int index, double data)
{
    assert(("Index not valid.", 0 <= index && index <= length - 1));
    Node* temp = head;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    temp->value = data;
}

// Function to delete a node at a given index
void LinkedList::DeleteNode(int index)
{
    assert(("Index not valid.", 0 <= index && index <= length - 1));
    if (index == 0) {
        Node* temp = head;
        head = head->next;
        delete temp;
        length--;
        return;
    }
    else {
        Node* temp1 = head;
        Node* temp2 = head->next;
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

// Function to insert a node at a given index with specific data
void LinkedList::InsertNode(int index, double col, double data)
{
    assert(("Index not valid.", 0 <= index && index <= length - 1));
    Node* newNode = new Node(data);
    if (head == nullptr) {
        head = newNode;
        length++;
        return;
    }
    else {
        Node* temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
        length++;
        return;
    }
}

// Function to insert a node behind a given index with specific data
void LinkedList::InsertBehind(int index, double data)
{
    Node* newNode = new Node(data);
    if (head == nullptr) {
        head = newNode;
        length++;
        return;
    }
    else if (index == 0) {
        InsertHead(data);
    }
    else {
        Node* temp = head;
        for (int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
        length++;
        return;
    }
}

// Function to insert a node in front of a given index with specific data
void LinkedList::InsertForward(int index, double data)
{
    Node* newNode = new Node(data);
    if (head == nullptr) {
        head = newNode;
        length++;
    }
    else if (index == length) {
        InsertTail(data);
    }
    else {
        Node* temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
        length++;
    }
}

// Function to insert a node at the head with specific data
void LinkedList::InsertHead(double data)
{
    Node* newNode = new Node(data);
    if (head == nullptr) {
        head = newNode;
        length++;
        return;
    }
    newNode->next = head;
    head = newNode;
    length++;
    return;
}

// Function to insert a node at the tail with specific data
void LinkedList::InsertTail(double data)
{
    Node* newNode = new Node(data);
    if (head == nullptr) {
        head = newNode;
        length++;
        return;
    }
    else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
        length++;
        return;
    }
}

// Function to print the linked list
void LinkedList::PrintList()
{
    Node* temp = head;
    if (head == nullptr) {
        std::cout << "List empty" << std::endl;
        return;
    }
    while (temp != nullptr) {
        std::cout << temp->value << std::endl;
        temp = temp->next;
    }
}
