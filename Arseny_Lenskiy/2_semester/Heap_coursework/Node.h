#ifndef NODE_H
#define NODE_H

#include "LinkedList.h"

template<typename T>
struct Node {
    T data;
    LinkedList<Node<T> *> children;

    Node(const T &data) : data(data), children() {};
};

#endif
