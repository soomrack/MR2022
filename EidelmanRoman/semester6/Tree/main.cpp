#include "Tree.h"


int main() {

    Node node1(3, 4);
    Node node2(6, 10);
    Node node3(8, 90);
    Node my_node;
    my_node = node2;

    Tree tree(my_node);
    std::cout<<tree.root->key<<"\n";
    return 0;
}