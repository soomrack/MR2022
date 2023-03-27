//
// Created by user on 3/19/23.
//

#ifndef HELLO_WORLD_BINARYTREE_H
#define HELLO_WORLD_BINARYTREE_H


#include <cstdint>


template<typename T>
class BinaryTree;


template<typename T>
class Node {
    friend class BinaryTree<T>;
private:
    T data;
    Node<T>* parent;
    Node<T>* left;
    Node<T>* right;
public:
    Node(T _data, Node<T>* _parent, Node<T>* _left, Node<T>* _right);
};


template<typename T>
class BinaryTree {
private:
    uint64_t level;

public:
    BinaryTree();
    void append();
    T pop();
    void find(T data);
    void go();
};


template<typename T>
Node<T>::Node(T _data, Node<T>* _parent, Node<T>* _left, Node<T>* _right) {
    parent = _parent;
    left = _left;
    right = _right;
    data = _data;
}


template<typename T>
BinaryTree<T>::BinaryTree() {
    level = 0;
}


template<typename T>
void BinaryTree<T>::append() {

}


template<typename T>
T BinaryTree<T>::pop() {
    return nullptr;
}


template<typename T>
void BinaryTree<T>::find(T data) {

}


#endif //HELLO_WORLD_BINARYTREE_H
