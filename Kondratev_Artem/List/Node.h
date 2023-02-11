//
// Created by user on 11.02.23.
//

#ifndef HELLO_WORLD_NODE_H
#define HELLO_WORLD_NODE_H


#include <cstdint>


template<typename T>
class List;


template<typename T>
class Node {
    friend class List<T>;
private:
    T data;
    Node<T>* next;
public:
    explicit Node(T object);
};


#endif //HELLO_WORLD_NODE_H
