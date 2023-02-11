//
// Created by user on 11.02.23.
//

#ifndef HELLO_WORLD_LIST_H
#define HELLO_WORLD_LIST_H


#include <cstdint>
#include <iostream>
#include "Node.h"


template<typename T>
class List {
private:
    uint64_t size;
    Node<T>* first;
    Node<T>* last;
public:
    List();
    bool isFirstEmpty();
    void append(T object);
    uint64_t len();
    void print();
};


#endif //HELLO_WORLD_LIST_H
