#ifndef PROGRAMMING_DYNAMIC_ARRAY_H
#define PROGRAMMING_DYNAMIC_ARRAY_H

#include <iostream>

template<class T>
class DynamicArray {
private:
    T* data;
    unsigned long long size;
    unsigned long long capacity;

public:
    explicit DynamicArray(unsigned long long new_capacity) {    // создание пустого массива
        size = 0;
        capacity = new_capacity;
        data = new T[capacity];
        if (data == nullptr) {
            std::cerr << "Memory is not allocated" << std::endl;
            exit(2);
        }
    }

    DynamicArray(T* array, unsigned long long size); // создание динамического массива по обычному
    DynamicArray(const DynamicArray &array);         // конструктор копирования
    ~DynamicArray() { delete[] data; }               // диструктор, удаляет данные

    DynamicArray& operator=(const DynamicArray& array); // оператор копирующего присваивания

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
DynamicArray<T>::DynamicArray(T *array, unsigned long long array_size) : DynamicArray(array_size) {
    size = array_size;
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
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T> &array) {
    if (this == &array) return *this;
    delete[] data;
    data = new T[array.size];
    size = array.size;
    capacity = array.capacity;
    memcpy(data, array.data, capacity * sizeof(T));
    return *this;
}


template<typename T>
T& DynamicArray<T>::operator[](unsigned long long idx) {
    if (idx < capacity) return data[idx];
    std::cerr << "Index is out of defined values area";
    exit(1);
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
    if (size == capacity) {
        std::cerr << "Can't push due to array being full";
        exit(1);
    }
    data[size++] = el;
}


#endif //PROGRAMMING_DYNAMIC_ARRAY_H


