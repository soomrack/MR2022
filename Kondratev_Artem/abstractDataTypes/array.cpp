//
// Created by user on 08.02.23.
//

#include "array.h"


template<typename T>
array<T>::array(uint64_t len, T number) {
    length = len;
    data = new T[length];
    for (int idx = 0; idx < length; idx++) {
        data[idx] = number;
    }
}

/*
template<typename T>
array<T>::array(T array[]) {
    T *a = array;
    length = sizeof(*a) / sizeof(a[0]);
}
*/

template<typename T>
T array<T>::operator[](uint64_t idx) {
    return data[idx];
}


template<typename T>
array<T>& array<T>::operator=(const array<T> &other) {
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
array<T>& array<T>::operator=(array<T> &&other) noexcept {
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
uint64_t array<T>::len() {
    return length;
}


template<typename T>
void array<T>::append(T object) {
    delete[] data;

}


template<typename T>
void array<T>::print() {
    std::cout << "[";
    for (int idx = 0; idx < length - 1; idx++) {
        std::cout << data[idx] << ", ";
    }
    std::cout << data[length-1] << "]";
}


template<typename T>
void array<T>::setData(uint64_t idx, T object) {
    data[idx] = object;
}


template
class array<double>;

template
class array<int>;
