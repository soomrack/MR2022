#include <iostream>
#include <stack>
#include "except.h"
using namespace std;

template <typename T>
struct Node {
    T data;
    Node *left;
    Node *right;
};

template <typename T>
using NodePtr = Node<T>*;

template <typename T>
using NodePtrPtr = NodePtr<T>*;

template <typename T>
class Tree{
public:
    Tree();
    bool search(T k) ;
    void del(T key);
    void print();
    void insert(T key);

private:
    NodePtr<T> root;
    NodePtr<T> default_node;
    NodePtr<T> search(NodePtr<T> node, T key);
    void print(NodePtr<T> root, string out_st, bool last);
    NodePtrPtr<T> min(NodePtrPtr<T> node);
    NodePtrPtr<T> parent_min(NodePtrPtr<T> node);
};

template <typename T>
Tree<T>::Tree(){
    default_node = new Node<T>;
    default_node->left = nullptr;
    default_node->right = nullptr;

    root = default_node;
}

template <typename T>
void Tree<T>:: insert(T key) {
    auto node = new Node<T>;
    node->data = key;
    node->left = default_node;
    node->right = default_node;
    NodePtr<T> leaf = nullptr;
    NodePtr<T> temp = this->root;

    while (temp != default_node) {
        leaf = temp;
        temp = (node->data <  temp->data) ? temp->left : temp->right;
    }

    if (leaf == nullptr){
        root = node;
        return;
    }
    (node->data <  leaf->data) ? leaf->left = node : leaf->right = node;
}



template <typename T>
NodePtrPtr<T> Tree<T>::min(NodePtrPtr<T> node) {
    while ((*node)->left != default_node)
        node = &((*node)->left);
    return node;
}

template <typename T>
NodePtrPtr<T> Tree<T>:: parent_min(NodePtrPtr<T> node) {
    while ((*node)->left->left != default_node)
        node = &((*node)->left);
    return node;
}

template <typename T>
void Tree<T>:: del(T key) {
    //iterate from the root of the tree
    NodePtrPtr<T> deleting_node_ptr = &(this->root);

    //finding the deleting element in the tree
    while ((*deleting_node_ptr) != default_node){
        if ((*deleting_node_ptr)->data == key) break;
        deleting_node_ptr = ((*deleting_node_ptr)->data > key) ? &((*deleting_node_ptr)->left) : &((*deleting_node_ptr)->right);
    }

    if ((*deleting_node_ptr) == default_node) return;

    if ((*deleting_node_ptr)->right == default_node) {
        *deleting_node_ptr = (*deleting_node_ptr)->left;
        return;
    }

    if ((*deleting_node_ptr)->left == default_node) {
        *deleting_node_ptr = (*deleting_node_ptr)->right;
        return;
    }

    //view images in the repository
    if ((*deleting_node_ptr)->right->left == default_node){
        (*deleting_node_ptr)->right->left = (*deleting_node_ptr)->left;
        (*deleting_node_ptr) = (*deleting_node_ptr)->right;
        return;
    }

    NodePtrPtr<T> minimum = (min(&((*deleting_node_ptr)->right)));
    const NodePtr<T> temp = *deleting_node_ptr; // A
    const NodePtr<T> temp_min = (*minimum)->right; // F
    const NodePtrPtr<T> parent_min_ptr = parent_min(&((*deleting_node_ptr)->right)); // C

    (*deleting_node_ptr) = *minimum;
    (*minimum)->left = (temp)->left;
    (*minimum)->right = (temp)->right;
    (*parent_min_ptr)->left = temp_min ;

}

template <typename T>
NodePtr<T> Tree<T>:: search(NodePtr<T> node, T key) {
    while (node != default_node and key != node->data)
        node = (node->data <= key) ? node->right: node->left;
    return node;
}

template <typename T>
void Tree<T>::print(NodePtr<T> _root, string out_st, bool last) {
    if (_root != default_node) {
        cout << out_st;
        if (last) {
            out_st += "\t\t";
        } else {
            out_st += "|\t\t";
        }
        cout << _root->data  << "\n";
        print(_root->left, out_st, false);
        print(_root->right, out_st, true);
    }
}

template <typename T>
bool Tree<T>:: search(T k) {
    NodePtr<T> temp =search(this->root, k);
    return (temp != default_node);
}

template <typename T>
void Tree<T>:: print() {
    if (root) {
        print(this->root, "<>", true);
    }
}


int main ()
{
    Tree <int>tree;
    tree.insert(15);
    tree.insert(2);
    tree.insert(20);
    tree.insert(21);
    tree.insert(19);
    tree.print();
    std::cout << "\n find 15? -- " << tree.search(15) << "\n";
    tree.del(15);
    tree.print();
    std::cout << "\n find 15? -- " << tree.search(15) << "\n";
    return 0;
}