#ifndef PROGRAMMING_DYNAMIC_ARRAY_H
#define PROGRAMMING_DYNAMIC_ARRAY_H

#include <iostream>
#include <exception>

class ArrayException: public std::exception {
public:
    explicit ArrayException(const char* msg): std::exception(msg) {};
};


ArrayException OUT_OF_RANGE("Index is out of range");

template<class T>
class DynamicArray {
private:
    T* data;
    unsigned long long size;
    unsigned long long capacity;

public:
    DynamicArray();
    explicit DynamicArray(unsigned long long capacity);
    DynamicArray(T* array, unsigned long long array_size);
    DynamicArray(const DynamicArray &array);
    DynamicArray(DynamicArray &&array) noexcept;
    ~DynamicArray() { delete[] data; }

    DynamicArray& operator=(const DynamicArray& array);
    DynamicArray& operator=(DynamicArray&& array) noexcept;

    T& operator[](unsigned long long idx);
    void resize(unsigned long long new_capacity);

    void push_back(const T& el);

    explicit operator bool() {
        for (unsigned int idx = 0; idx < capacity; idx++) {
            if (!(bool) data[idx]) return false;
        }
        return true;
    }

    unsigned long long length() { return capacity; }
};


template<typename T>
DynamicArray<T>::DynamicArray() : data(nullptr), size(0), capacity(0) {}


template<typename T>
DynamicArray<T>::DynamicArray(unsigned long long capacity) : size(0), capacity(capacity) {
    data = new T[capacity];
    if (data == nullptr) throw ArrayException("Memory is not allocated");;
}

template<typename T>
DynamicArray<T>::DynamicArray(T *array, unsigned long long size) : DynamicArray(size), size(size) {
    memcpy(data, array, size * sizeof(T));
}


template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray &array) {
    data = new T[array.capacity];
    capacity = array.capacity;
    size = array.size;
    memcpy(data, array.data, capacity * sizeof(T));
}


template<typename T>
DynamicArray<T>::DynamicArray(DynamicArray<T> &&array) noexcept {
    data = array.data;
    size = array.size;
    capacity = array.capacity;

    array.data = nullptr;
    array.capacity = 0;
}


template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T> &array) {
    if (this == &array) return *this;
    delete[] data;
    size = array.size;
    capacity = array.capacity;
    memcpy(data, array.data, capacity * sizeof(T));
    return *this;
}


template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray<T> &&array)  noexcept {
    if (this == &array) return *this;
    delete[] data;
    data = array.data;
    size = array.size;
    capacity = array.capacity;

    array.data = nullptr;
    array.capacity = 0;
    return *this;
}


template<typename T>
T& DynamicArray<T>::operator[](unsigned long long idx) {
    if (idx < capacity) return data[idx];
    throw ArrayException("Index is out of defined values area");
}


template<typename T>
void DynamicArray<T>::resize(unsigned long long new_capacity) {
    if (capacity >= new_capacity) capacity = new_capacity;
    else {
        T* new_data = new T[new_capacity];
        memcpy(new_data, data, capacity * sizeof(T));
        capacity = new_capacity;
        delete[] data;
        data = new_data;
    }
}

template<typename T>
void DynamicArray<T>::push_back(const T &el) {
    if (size == capacity) throw ArrayException("Can't push due to array being full");
    data[size++] = el;
}


#endif //PROGRAMMING_DYNAMIC_ARRAY_H
