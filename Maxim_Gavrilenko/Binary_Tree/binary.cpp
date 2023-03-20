#include "iostream"
#include "Binary_tree.h"

int main() {
    BinaryTree A;
    A.addNode(25);
    A.addNode(5);
    A.addNode(12);
    A.addNode(18);
    A.addNode(3);
    A.addNode(18);
    A.addNode(50);
    A.addNode(99);

    A.print();
    std::cout << "Search 50" << std::endl;
    A.search(50) ? std::cout << "yes": std::cout << "no"; std::cout<<std::endl;
    std::cout << "Remove 12" << std::endl;
    A.remove(12);
    A.print();
    std::cout << "Get_max " <<A.get_max()<< std::endl;
    std::cout << "Get_min " <<A.get_min()<< std::endl;
    return 0;
}
