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

    dynamic_array& operator=(const dynamic_array& array);
    dynamic_array& operator=(dynamic_array&& array) noexcept;

    T operator[](unsigned long long idx);
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


template<typename T>
dynamic_array<T>& dynamic_array<T>::operator=(const dynamic_array<T> &array) {
    if (this == &array) return *this;
    delete[] data;
    size = array.size;
    memcpy(data, array.data, size);
    return *this;
}


template<typename T>
dynamic_array<T>& dynamic_array<T>::operator=(dynamic_array<T> &&array)  noexcept {
    if (this == &array) return *this;
    delete[] data;
    data = array.data;
    size = array.size;

    array.data = nullptr;
    array.size = 0;
    return *this;
}


template<typename T>
T dynamic_array<T>::operator[](unsigned long long idx) {
    if (idx < size) return data[idx];
    std::cerr << "Index is out of range" << std::endl;
    exit(2);
}


template<typename T>
void dynamic_array<T>::resize(unsigned long long new_size) {
    if (size >= new_size) size = new_size;
    else {
        T* new_data = new T[new_size];
        memcpy(new_data, data, size);
        size = new_size;
        delete[] data;
        data = new_data;
    }
}


#endif //PROGRAMMING_DYNAMIC_ARRAY_H
