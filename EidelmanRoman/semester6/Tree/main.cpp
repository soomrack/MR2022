#include <iostream>
#include "Tree.h"


int main() {

    Node node1(3, 4);
    Node node2(6, 10);
    Node node3(8, 90);

    Tree tree;
    tree.insert(node1, 3, 4);
    return 0;
}