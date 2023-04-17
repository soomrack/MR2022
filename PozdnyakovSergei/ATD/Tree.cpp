#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Node {
public:
    Node *left;
    Node *right;
    int key;
    Node(int k);
};

Node::Node(int k) {
    key = k;
    left = nullptr;
    right = nullptr;
}


class Tree {
private:
    Node *root;
public:
    Tree();
    ~Tree();
    void insert();
    void remove();
    
};