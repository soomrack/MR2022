//
// Created by user on 08.02.23.
//

#ifndef HELLO_WORLD_ARRAY_H
#define HELLO_WORLD_ARRAY_H


#include <cstdint>
#include <cstring>
#include <iostream>


class Exception: std::exception {
private:
    std::string message;
public:
    explicit Exception(std::string _message) {message = std::move(_message);};

    std::string getMessage() const {return message;};
};


template<typename T>
class Array {
private:
    T* data;
    uint64_t size;
public:
    explicit Array(uint64_t length, T number = 0);
    explicit Array(uint64_t length, T array[]);
    ~Array();
    Array(const Array<T>& other);
    Array(Array<T>&& other) noexcept;

    T operator[](uint64_t index);
    Array<T>& operator=(const Array<T> &other);
    Array<T>& operator=(Array<T>&& other) noexcept;
    Array<T> operator+(const Array<T>& other);

    uint64_t len();
    void print();
    void setData(T object, uint64_t index);
    void append(T object);
    void append(T object, uint64_t index);
    void pop();
    void pop(uint64_t index);
    void clear();
    void sort();
};


#endif //HELLO_WORLD_ARRAY_H
