//
// Created by user on 08.02.23.
//

#ifndef HELLO_WORLD_ARRAY_H
#define HELLO_WORLD_ARRAY_H


#include <cstdint>
#include <cstring>
#include <iostream>
#include <iterator>


template<typename T>
class array {
private:
    T* data;
    uint64_t length;
public:
    explicit array(uint64_t length, T number = 0);
    //explicit array(T array[]);
    T operator[](uint64_t idx);
    array<T>& operator=(const array<T> &other);
    array<T>& operator=(array<T> &&other) noexcept ;
    uint64_t len();
    void append(T object);
    void print();
};


#endif //HELLO_WORLD_ARRAY_H
