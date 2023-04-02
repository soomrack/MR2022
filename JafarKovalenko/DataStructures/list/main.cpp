#include <iostream>
#include "list.h"

int main()
{
    using namespace std;

    LinkedList<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    lst.push_front(4); // 4 1 2 3
    
    lst.insert(2, 5); // 4 1 5 2 3
    

    LinkedList<int> oper = lst;
    cout << (oper == lst ? "operator= works" : "operator= doesnt work") << endl;
    
    for (int i = 0; i < oper.size(); ++i)
        cout << oper.get_node(i)->data << " ";
    cout << endl;
    
    for (int i = 0; i < lst.size(); ++i)
        cout << lst.get_node(i)->data << " ";
    cout << endl;
    
    lst.delete_back(); // 4 1 5 2
    

    LinkedList<int> copylst(lst);
    for (int i = 0; i < copylst.size(); ++i)
        cout << copylst.get_node(i)->data << " ";
    cout << endl;

    lst.delete_front(); // 1 5 2
    lst.push_front(6); // 6 1 5 2
    lst.erase(3); // 6 1 5
    
    for (int i = 0; i < lst.size(); ++i)
        cout << lst.get_node(i)->data << " ";

    cout << endl;
    lst.clear();
    cout << (lst.empty() ? "Now it's empty" : "Still not empty") << "\nSize: " << lst.size() <<  endl;
}

