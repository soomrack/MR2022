#include "iostream"
#include "Binary_tree.h"

int main() {
    BinaryTree A;
    A.add(25);
    A.add(5);
    A.add(13);
    A.add(18);
    A.add(3);
    A.add(16);
    A.add(15);
    A.add(17);
    A.add(50);
    A.add(99);
    A.add(11);
    A.add(10);
    A.add(12);
    A.print();
    A.remove(13);
    std::cout << std::endl;
    A.print();
    std::cout << "Search 25" << std::endl;
    A.search(25) ? std::cout << "yes": std::cout << "no"; std::cout<<std::endl;
    return 0;
}
