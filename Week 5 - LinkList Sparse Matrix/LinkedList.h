#include <iostream>

//Uncomment to remove debug
//#define NDEBUG
#include <cassert>

#include "LinkedList.h"

int main() {
    // Create a linked list
    LinkedList myList;

    // Insert some elements
    myList.InsertTail(5.0);
    myList.InsertTail(10.0);
    myList.InsertTail(15.0);

    // Print the initial list
    std::cout << "Initial Linked List:" << std::endl;
    myList.PrintList();
    std::cout << std::endl;

    // Update an element at index 1
    myList.set(1, 12.0);

    // Print the updated list
    std::cout << "Updated Linked List using set:" << std::endl;
    myList.PrintList();
    std::cout << std::endl;

    // Update an element at index 2 using by reference get
    myList.get(2) = 20.0;

    // Print the updated list
    std::cout << "Updated Linked List using get:" << std::endl;
    myList.PrintList();
    std::cout << std::endl;

    // Insert a new node at the head
    myList.InsertHead(2.5);

    // Print the list after insertion at the head
    std::cout << "Linked List after Inserting at the Head:" << std::endl;
    myList.PrintList();
    std::cout << std::endl;

    // Delete a node at index 2
    myList.DeleteNode(2);

    // Print the list after deletion
    std::cout << "Linked List after Deleting Node at Index 2:" << std::endl;
    myList.PrintList();
    std::cout << std::endl;
}
