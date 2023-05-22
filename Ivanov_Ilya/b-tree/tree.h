#ifndef tree_h
#define tree_h
#include <iostream>
#include <stack>

struct Node {
    int data;
    Node *left;
    Node *right;

};
typedef Node* NodePtr;
typedef NodePtr* NodePtrPtr;


class Tree{
public:
    Tree();
    bool search(int k) ;
    void del(int data);
    void print();
    void insert(int key);

private:
    NodePtr root;
    NodePtr TNULL;
    NodePtr search(NodePtr node, int key);
    void print(NodePtr root, std::string indent, bool last);
    NodePtrPtr min(NodePtrPtr node);
    NodePtrPtr parent_min(NodePtrPtr  node);
};


Tree:: Tree(){
    TNULL = new Node;
    TNULL->left = nullptr;
    TNULL->right = nullptr;
    root = TNULL;
}


void Tree:: insert(int key) {
    NodePtr node = new Node;
    node->data = key;
    node->left = TNULL;
    node->right = TNULL;
    NodePtrPtr link = &root;
    while (*link != TNULL)
       {
           link = (*link)->data < key ? &(*link)->left : &(*link)->right;
       }
    *link = node;
}


NodePtrPtr Tree:: min(NodePtrPtr node) {
    while ((*node)->left != TNULL)
        node = &((*node)->left);
    return node;
}


NodePtrPtr Tree:: parent_min(NodePtrPtr   node) {
    while ((*node)->left->left != TNULL)
        node = &((*node)->left);
    return node;
}



void Tree::del(int key) {
    NodePtrPtr node_to_del_ptr = &(this->root);
    while (*node_to_del_ptr != TNULL && (*node_to_del_ptr)->data != key) {
        node_to_del_ptr = ((*node_to_del_ptr)->data > key) ? &((*node_to_del_ptr)->left) : &((*node_to_del_ptr)->right);
    }

    if (*node_to_del_ptr == TNULL) {
        return; // Узел не найден, выходим из метода
    }

    if ((*node_to_del_ptr)->right == TNULL) {
        *node_to_del_ptr = (*node_to_del_ptr)->left;
        return;
    }

    if ((*node_to_del_ptr)->left == TNULL) {
        *node_to_del_ptr = (*node_to_del_ptr)->right;
        return;
    }

    NodePtrPtr minimum = min(&((*node_to_del_ptr)->right)); 
    (*node_to_del_ptr)->data = (*minimum)->data;
    *minimum = (*minimum)->right;
}

NodePtr Tree:: search(NodePtr node, int key) {
    while (node != TNULL and key != node->data)
        node = (node->data <= key) ? node->right: node->left;
    return node;
}


void Tree::print(NodePtr root, std::string indent, bool last) {
    if (root != TNULL) {
        std::cout << indent;
        if (last) {
            std::cout << "R----";
            indent += "   ";
        } else {
            std::cout << "L----";
            indent += "|  ";
        }
        std::cout << root->data  << "\n";
        print(root->left, indent, false);
        print(root->right, indent, true);
    }
}
bool Tree:: search(int k) {
    NodePtr buffer =search(this->root, k);
    return (buffer != TNULL);
}



void Tree:: print() {
    if (root) {
        print(this->root, "", true);
    }
}

#endif /* tree_h */
