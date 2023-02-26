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
    Stack(const Stack<T>& other);
    Stack(Stack<T>&& other) noexcept;

    Stack<T> &operator=(const Stack<T>& other);
    Stack<T> &operator=(Stack<T>&& other) noexcept;

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
Stack<T>::Stack(const Stack<T>& other) {
    size = other.size;
    list = other.list;
}


template<typename T>
Stack<T>::Stack(Stack<T>&& other) noexcept {
    size = other.size;
    list = other.list;
    other.size = 0;
    other.list = nullptr;
}


template<typename T>
Stack<T> &Stack<T>::operator=(const Stack<T> &other) {
    if (this != &other) {
        size = other.size;
        list = other.list;
    }
    return *this;
}


template<typename T>
Stack<T> &Stack<T>::operator=(Stack<T> &&other) noexcept {
    if (this != &other) {
        size = other.size;
        list = other.list;
        other.size = 0;
        other.list = 0;
    }
    return *this;
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
