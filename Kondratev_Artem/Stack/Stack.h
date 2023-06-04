//
// Created by user on 18.02.23.
//

#ifndef HELLO_WORLD_STACK_H
#define HELLO_WORLD_STACK_H


#include <cstdint>
#include <iostream>
#include "../List/List.h"


template<typename T>
class Stack {
private:
    uint64_t size;
    List<T> list;
public:
    Stack();
    ~Stack() = default;

    void append(T object);
    T pop();
    uint64_t getSize();
};


template<typename T>
Stack<T>::Stack() {
    list = List<T>();
    size = 0;
}


template<typename T>
void Stack<T>::append(T object) {
    list.append(object);
    size++;
}


template<typename T>
T Stack<T>::pop() {
    if (size == 0) {
        throw Exception("error: bad access");
    }
    size--;
    return list.pop();
}


template<typename T>
uint64_t Stack<T>::getSize() {
    return size;
}


#endif //HELLO_WORLD_STACK_H
