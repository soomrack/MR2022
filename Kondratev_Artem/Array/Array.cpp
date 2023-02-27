//
// Created by user on 08.02.23.
//

#include "Array.h"


template<typename T>
Array<T>::Array(uint64_t length, T number) {
    size = length;
    data = new T[size];
    for (int idx = 0; idx < size; idx++) {
        data[idx] = number;
    }
}


template<typename T>
Array<T>::Array(uint64_t length, T array[]) {
    size = length;
    data = new T[size];
    for (int idx = 0; idx < size; idx++) {
        data[idx] = array[idx];
    }
}


template<typename T>
Array<T>::~Array() {
    delete[] data;
}


template<typename T>
Array<T>::Array(const Array<T> &other) {
    size = other.size;
    data = new T[size];
    memcpy(data, other.data, sizeof(T) * size);
}


template<typename T>
Array<T>::Array(Array<T> &&other) noexcept {
    size = other.size;
    data = other.data;
    other.data = nullptr;
}


template<typename T>
T Array<T>::operator[](uint64_t index) {
    return data[index];
}


template<typename T>
Array<T>& Array<T>::operator=(const Array<T> &other) {
    if (this == &other) {
        return *this;
    }
    size = other.size;
    delete[] data;
    data = new T[size];
    std::memcpy(data, other.data, sizeof(T) * size);
    return *this;
}


template<typename T>
Array<T>& Array<T>::operator=(Array<T> &&other) noexcept {
    if (this == &other) {
        return *this;
    }
    size = other.size;
    delete[] data;
    data = other.data;
    other.data = nullptr;
    return *this;
}


template<typename T>
Array<T> Array<T>::operator+(const Array<T> &other) {
    Array<T> result(size + other.size);
    memcpy(result.data, data, sizeof(T) * size);
    memcpy(result.data + size, other.data, sizeof(T) * other.size);
    return result;
}


template<typename T>
uint64_t Array<T>::len() {
    return size;
}


template<typename T>
void Array<T>::print() {
    if (size == 0) {
        return;
    }
    std::cout << "[";
    for (int idx = 0; idx < size - 1; idx++) {
        std::cout << data[idx] << ", ";
    }
    std::cout << data[size - 1] << "]" << std::endl;
}


template<typename T>
void Array<T>::setData(T object, uint64_t index) {
    if (index >= size) {
        throw Exception("error: bad index");
    }
    data[index] = object;
}


template<typename T>
void Array<T>::append(T object) {
    size++;
    T* buffer = data;
    data = new T[size];
    std::memcpy(data, buffer, sizeof(T) * (size - 1));
    data[size - 1] = object;
    delete[] buffer;
}


template<typename T>
void Array<T>::append(T object, uint64_t index) {
    if (index > size) {
        throw Exception("error: bad index");
    }
    size++;
    T* buffer = data;
    data = new T[size];
    std::memcpy(data, buffer, sizeof(T) * (index));
    data[index] = object;
    std::memcpy(data + index + 1, buffer, sizeof(T) * (size - index - 1));
    delete[] buffer;
}


template<typename T>
void Array<T>::pop() {
    size--;
    T* buffer = data;
    data = new T[size];
    std::memcpy(data, buffer, sizeof(T) * size);
    delete[] buffer;
}


template<typename T>
void Array<T>::pop(uint64_t index) {
    if(index >= size) {
        throw Exception("error: bad index");
    }
    size--;
    T* buffer = data;
    data = new T[size];
    std::memcpy(data, buffer, sizeof(T) * index);
    for (uint64_t idx = size; idx > index; idx--) {
        data[idx-1] = buffer[idx];
    }
    delete[] buffer;
}


template<typename T>
void Array<T>::clear() {
    size = 0;
    delete[] data;
    data = nullptr;
}


template<typename T>
void Array<T>::sort() {
    if (size < 2) {
        return;
    }
    T barrier = data[size/2];
    Array<T> left(0);
    uint64_t middle_cnt = 0;
    Array<T> right(0);
    for (int idx = 0; idx < size; idx++) {
        if (data[idx] < barrier) {
            left.append(data[idx]);
        }
        if (data[idx] == barrier) {
            middle_cnt++;
        }
        if (data[idx] > barrier) {
            right.append(data[idx]);
        }
    }
    left.sort();
    right.sort();
    *this = left + Array<T>(middle_cnt, barrier) + right;
}


template
class Array<double>;

template
class Array<int>;
