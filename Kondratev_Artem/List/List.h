//
// Created by user on 11.02.23.
//

#ifndef HELLO_WORLD_LIST_H
#define HELLO_WORLD_LIST_H


#include <cstdint>
#include <iostream>
#include "Exception.h"
#include "Node.h"


template<typename T>
class List {
private:
    uint64_t size;
    Node<T>* first;
    Node<T>* last;
public:
    List();
    List(uint64_t _size, T array[]);
    ~List() = default;
    List(const List<T>& other);
    List(List<T>&& other) noexcept ;
    bool isFirstEmpty();
    List<T>& operator=(const List<T>& other);
    List<T>& operator=(List<T>&& other) noexcept ;
    Node<T>* operator[](uint64_t index);
    List<T> operator+(List<T> other);
    void append(T object);
    void append(T object, uint64_t index);
    void pop();
    void pop(uint64_t index);
    uint64_t len();
    void print();
    uint64_t getSize();
    T getData(uint64_t index);
    void clear();
};


#endif //HELLO_WORLD_LIST_H
