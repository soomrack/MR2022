#include "iostream"
#include "Binary_tree.h"

int main() {
    BinaryTree A;
    A.add(25);
    A.add(13);
    A.add(3);
    A.add(32);
    A.add(7);
    A.add(36);
    A.add(28);
    A.add(26);

    A.add(15);
    A.add(2);
    A.add(91);
    A.add(8);
    A.add(6);
    A.add(5);
    A.add(7);
    A.add(9);
    A.print();
    A.remove(7);
    std::cout << std::endl;
    A.print();
    std::cout << "Search 25" << std::endl;
    A.search(25) ? std::cout << "yes": std::cout << "no"; std::cout<<std::endl;
    return 0;
}
