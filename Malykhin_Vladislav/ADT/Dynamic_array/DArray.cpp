#include <cstring>
#include "DArray.h"


template <typename T>
DArray<T>::DArray(const std::list<T> in_list,int new_cache_size) {
    auto iter = in_list.begin(); // typename std::list<T>::iterator iter = in_list.begin();
    size = in_list.size();
    cache_size = new_cache_size;
    data = new T [size + cache_size];
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
T& DArray<T>::operator[] (unsigned int idx){
return data[idx];
}


template <typename T>
void DArray<T>::resize(unsigned int new_size) {
    if (new_size <= size + cache_size) {
        cache_size -= new_size - size;
        size = new_size;
        return ;
    }
    T *new_data = new T[new_size];
    std::memcpy(new_data, data, sizeof(T) * size); //умножать на std::minimum(new_data, data)
    size = new_size;
    delete (data);
    data = new_data;
}


template class DArray<int>;
template class DArray<double>;
template class DArray<float>;