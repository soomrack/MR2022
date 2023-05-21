#include "BinaryTree.h"


int main(){
    auto tree = BinaryTree();
    tree.add_node(10);
    tree.add_node(9);
    tree.add_node(11);
    tree.add_node(6);
    tree.add_node(8);
    tree.add_node(13);
    tree.add_node(12);
    tree.add_node(4);
    tree.add_node(5);
    tree.print(10);
    tree.print(9);
    tree.print(11);
    tree.print(6);
    tree.print(8);
    tree.print(13);
    tree.print(12);
    tree.print(4);
    tree.print(5);

    std::cout<<"\nRemove test****************\n";
    tree.remove(10);
    tree.print(10);
    tree.print(9);
    tree.print(11);
    tree.print(6);
    tree.print(8);
    tree.print(13);
    tree.print(12);
    tree.print(4);
    tree.print(5);
}
