#include <cstring>
#include "DArray.h"


template <typename T>
DArray<T>::DArray() noexcept {
    size = 0;
    data = nullptr;
}


template <typename T>
DArray<T>::DArray(unsigned int size_in) {
    size = size_in;
    data = new T *[size];
    for(int  id = 0; id < size; ++id)
    data[id] = 0;
}


template <typename T>
DArray<T>::DArray(unsigned int size_in, T element) {
    size = size_in;
    data = new T *[size];
    for(int id = 0; id < size; ++id)
        data[id] = element;
}


template <typename T>
DArray<T>::~DArray() noexcept{
    size = 0;
    delete data;
}


template <typename T>
DArray<T>::DArray(const DArray<T> &other){
    size = other.size;
    data = new T *[size];
    std::memcpy(data, other.data, sizeof(T)* size);
}


template <typename T>
DArray<T>::DArray(DArray<T> &&other) noexcept {
    size = other.size;
    data = other.data;
    other.size = 0;
    other.data = nullptr;
}


template <typename T>
unsigned int DArray<T>::get_size() const {
    return size;
}

template <typename T>
void DArray<T>::set(unsigned int id, T element) {
    data[id] = element;
}


template <typename T>
void DArray<T>::resize(unsigned int new_size){
    T buffer[new_size];
    std::memcpy(buffer, data, sizeof(T)* size);
    delete(data);
    data = new T *[new_size];
    std::memcpy(data, buffer, sizeof(T)* size);
}


template<typename T>
T DArray<T>::get_data(unsigned int id) const {
    return data[id];
}


template<typename T>
void DArray<T>::print() const {
    for (int id = 0; id < size; ++id)
        std::cout << data[id];
}