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

public:
    DynamicArray();
    explicit DynamicArray(unsigned long long array_size);
    DynamicArray(T* array, unsigned long long size);
    DynamicArray(const DynamicArray &array);
    DynamicArray(DynamicArray &&array) noexcept;
    ~DynamicArray() { delete[] data; }

    DynamicArray& operator=(const DynamicArray& array);
    DynamicArray& operator=(DynamicArray&& array) noexcept;

    T& operator[](unsigned long long idx);
    void resize(unsigned long long new_size);

    explicit operator bool() {
        for (unsigned int idx = 0; idx < size; idx++) {
            if (!(bool) data[idx]) return false;
        }
        return true;
    }

    unsigned long long length() { return size; }
};


template<typename T>
DynamicArray<T>::DynamicArray() : data(nullptr), size(0) {}


template<typename T>
DynamicArray<T>::DynamicArray(unsigned long long array_size) : size(array_size) {
    data = new T[size];
    if (data == nullptr) throw ArrayException("Memory is not allocated");;
}

template<typename T>
DynamicArray<T>::DynamicArray(T *array, unsigned long long size) : DynamicArray(size) {
    memcpy(data, array, size * sizeof(T));
}


template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray &array) {
    data = new T[array.size];
    size = array.size;
    memcpy(data, array.data, size * sizeof(T));
}


template<typename T>
DynamicArray<T>::DynamicArray(DynamicArray<T> &&array) noexcept {
    data = array.data;
    size = array.size;

    array.data = nullptr;
    array.size = 0;
}


template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T> &array) {
    if (this == &array) return *this;
    delete[] data;
    size = array.size;
    memcpy(data, array.data, size * sizeof(T));
    return *this;
}


template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray<T> &&array)  noexcept {
    if (this == &array) return *this;
    delete[] data;
    data = array.data;
    size = array.size;

    array.data = nullptr;
    array.size = 0;
    return *this;
}


template<typename T>
T& DynamicArray<T>::operator[](unsigned long long idx) {
    if (idx < size) return data[idx];
    throw ArrayException("Index is put of range");
}


template<typename T>
void DynamicArray<T>::resize(unsigned long long new_size) {
    if (size >= new_size) size = new_size;
    else {
        T* new_data = new T[new_size];
        memcpy(new_data, data, size * sizeof(T));
        size = new_size;
        delete[] data;
        data = new_data;
    }
}


#endif //PROGRAMMING_DYNAMIC_ARRAY_H
