#include <iostream>
#include "Binary_tree.h"

int main() {
    BinaryTree A;
    A.add(25);
    A.add(13);
    A.add(32);
    A.add(9);
    A.add(6);
    A.add(12);
    A.add(7);
    A.remove(9);
    std::cout << std::endl;
    std::cout << "Search 25" << std::endl;
    A.search(25) ? std::cout << "yes": std::cout << "no"; std::cout<<std::endl;
    return 0;
}
