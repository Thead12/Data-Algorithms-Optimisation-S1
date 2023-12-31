//Various tests for Week 5's challenge - LinkedList class 


#int main()
{   
    LinkedList list;

    list.InsertTail(1);
    list.InsertTail(2);
    list.InsertTail(3);
    list.InsertHead(4);

    list.InsertBehind(0, 3.5);

    list.PrintList();
    cout << endl;

    list.PrintList();
    cout << endl;
}
