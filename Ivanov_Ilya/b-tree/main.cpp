
#include "tree.h"
#include <iostream>

int main () {

    Tree bst;
    int a;
    bst.insert(55);
    bst.insert(40);
    bst.insert(65);
    bst.insert(60);
    bst.insert(75);
    bst.insert(56);
    bst.insert(41);
    bst.insert(555);
    bst.insert(42);
    bst.insert(57);
    bst.insert(5);
    bst.insert(1);
    bst.insert(69);
    bst.insert(90);
    bst.insert(91);
    bst.insert(68);
    bst.insert(85);
    bst.insert(86);
    bst.insert(7);
    bst.insert(6);






    bst.print();

    std::cout << "\n"
              << "After deleting" << "\n";
    bst.del(75);


    bst.print();

    a = bst.search(960);
    std::cout << "\n"
              << a << "\n";


    return 0;
}
