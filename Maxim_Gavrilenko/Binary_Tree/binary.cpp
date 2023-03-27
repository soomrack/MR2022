#include "iostream"
#include "Binary_tree.h"

int main() {
    BinaryTree A;
    A.add_node(25);
    A.add_node(5);
    A.add_node(12);
    A.add_node(18);
    A.add_node(3);
    A.add_node(16);
    A.add_node(50);
    A.add_node(99);

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
