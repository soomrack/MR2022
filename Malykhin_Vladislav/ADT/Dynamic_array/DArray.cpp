#include <cstring>
#include "DArray.h"


template <typename T>
DArray<T>::DArray(const std::list<T> in_list, int new_cache_size) {
    auto iter = in_list.begin(); // typename std::list<T>::iterator iter = in_list.begin();
    size = in_list.size();
    if(new_cache_size >= 0){
        default_cache = new_cache_size;
    }
    real_cache = default_cache;
    data = new T [size + default_cache];
    for(int id = 0; id < size; ++id) {
        data[id] = *iter;
        iter++;
    }
}

template <typename T>
DArray<T>::~DArray() noexcept{
    size = 0;
    delete data;
}



template <typename T>
unsigned int DArray<T>::get_size() const {
    return size;
}


template <typename T>
unsigned int DArray<T>::get_default_cache_size() const {
    return default_cache;
}


template <typename T>
unsigned int DArray<T>::get_reserved() const{
    return real_cache;
};



template <typename T>
unsigned int DArray<T>::get_capacity() const{
    return real_cache + size;
};


template <typename T>
void DArray<T>::set_default_cache_size(unsigned int new_cache_size) {
    default_cache = new_cache_size;
}



template <typename T>
T& DArray<T>::operator[] (unsigned int idx){
return data[idx];
}


template <typename T>
void DArray<T>::resize(unsigned int new_size) {
    if (new_size <= size + real_cache) {
        real_cache -= new_size - size;
        size = new_size;
        return ;
    }
    T *new_data = new T[new_size + default_cache];
    std::memcpy(new_data, data, sizeof(T) * size); //умножать на std::minimum(new_data, data)
    size = new_size;
    delete (data);
    data = new_data;
    real_cache = default_cache;
}


template class DArray<int>;
template class DArray<double>;
template class DArray<float>;