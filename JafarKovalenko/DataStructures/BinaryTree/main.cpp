#include <iostream>
#include "BinaryTree.h"

int main() {
    BinaryTree<int> tree(7);
    tree.append(3);
    tree.append(12);
    tree.append(1);
    tree.append(5);
    tree.append(9);
    tree.append(13);
    tree.append(2);
    tree.append(4);
    tree.append(6);
    tree.append(11);
    tree.append(10);
    tree.append(8);
    tree.append(12);
    tree.append(13);
    tree.append(14);
    tree.append(15);
    tree.append(16);

    tree.showTree();
    std::cout << "Size: " << tree.getSize() << "\n\n";

    tree.remove(7);
    tree.showTree();
    std::cout << "Size: " << tree.getSize() << "\nHeight: " << tree.getHeight();
    std::cout << "\nHeight again: " << tree.getHeight();
    tree.remove(16);
    std::cout << "\nHeight another one " << tree.getHeight();
    return 0;
}
