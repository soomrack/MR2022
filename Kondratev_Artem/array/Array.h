//
// Created by user on 08.02.23.
//

#ifndef HELLO_WORLD_ARRAY_H
#define HELLO_WORLD_ARRAY_H


#include <cstdint>
#include <cstring>
#include <iostream>
#include <iterator>
#include "ArrayException.h"


template<typename T>
class Array {
private:
    T* data;
    uint64_t length;
public:
    explicit Array(uint64_t length, T number = 0);
    //explicit Array(T Array[]);
    T operator[](uint64_t idx);
    Array<T>& operator=(const Array<T> &other);
    Array<T>& operator=(Array<T> &&other) noexcept;
    uint64_t len();
    void print();
    void setData(uint64_t idx, T object);
    void append(T object);
    void pop();
};


#endif //HELLO_WORLD_ARRAY_H
