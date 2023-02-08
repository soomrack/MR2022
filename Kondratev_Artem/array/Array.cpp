//
// Created by user on 08.02.23.
//

#include "Array.h"


template<typename T>
Array<T>::Array(uint64_t len, T number) {
    length = len;
    data = new T[length];
    for (int idx = 0; idx < length; idx++) {
        data[idx] = number;
    }
}

/*
template<typename T>
Array<T>::Array(T Array[]) {
    T *a = Array;
    length = sizeof(*a) / sizeof(a[0]);
}
*/

template<typename T>
T Array<T>::operator[](uint64_t idx) {
    return data[idx];
}


template<typename T>
Array<T>& Array<T>::operator=(const Array<T> &other) {
    if (this == &other) {
        return *this;
    }
    length = other.length;
    delete[] data;
    data = new T[length];
    std::memcpy(data, other.data, sizeof(T) * length);
    return *this;
}


template<typename T>
Array<T>& Array<T>::operator=(Array<T> &&other) noexcept {
    if (this == &other) {
        return *this;
    }
    length = other.length;
    delete[] data;
    data = other.data;
    other.data = nullptr;
    return *this;
}


template<typename T>
uint64_t Array<T>::len() {
    return length;
}


template<typename T>
void Array<T>::print() {
    std::cout << "[";
    for (int idx = 0; idx < length - 1; idx++) {
        std::cout << data[idx] << ", ";
    }
    std::cout << data[length-1] << "]" << std::endl;
}


template<typename T>
void Array<T>::setData(uint64_t idx, T object) {
    if (idx >= length) {
        throw ArrayException("error: bad index");
    }
    data[idx] = object;
}


template<typename T>
void Array<T>::append(T object) {
    length++;
    T* buffer = data;
    data = new T[length];
    std::memcpy(data, buffer, sizeof(T) * (length - 1));
    data[length-1] = object;
    delete[] buffer;
}


template<typename T>
void Array<T>::pop() {
    length--;
    T* buffer = data;
    data = new T[length];
    std::memcpy(data, buffer, sizeof(T) * length);
    delete[] buffer;
}


template
class Array<double>;

template
class Array<int>;
