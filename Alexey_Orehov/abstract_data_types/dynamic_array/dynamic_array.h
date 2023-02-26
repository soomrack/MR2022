#ifndef PROGRAMMING_DYNAMIC_ARRAY_H
#define PROGRAMMING_DYNAMIC_ARRAY_H

#include <iostream>


template<class T>
class dynamic_array {
private:
    T* data;
    unsigned long long size;

public:
    dynamic_array();
    dynamic_array(T* array, unsigned long long size);
    dynamic_array(const dynamic_array &array);
    dynamic_array(dynamic_array &&array) noexcept;
    ~dynamic_array() { delete[] data; }


    unsigned long long length() { return size; }
};


template<typename T>
dynamic_array<T>::dynamic_array() : data(nullptr), size(0) {}


template<typename T>
dynamic_array<T>::dynamic_array(T *array, unsigned long long array_size) : size(array_size) {
    data = new T[size];
    if (data == nullptr) {
        std::cerr << "Unable to allocate memory" << std::endl;
        exit(1);
    }
    memcpy(data, array, size);
}


template<typename T>
dynamic_array<T>::dynamic_array(const dynamic_array &array) {
    data = new T[array.size];
    size = array.size;
    memcpy(data, array.data, size);
}


template<typename T>
dynamic_array<T>::dynamic_array(dynamic_array<T> &&array) noexcept {
    data = array.data;
    size = array.size;

    array.data = nullptr;
    array.size = 0;
}


#endif //PROGRAMMING_DYNAMIC_ARRAY_H
