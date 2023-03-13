#include <cstring>
#include "DArray.h"
/* добавить кеш (не занятую память для последующего расширения, как новый аргумент класса),
заменить вектор на какое-нибудь заполнение из списка (зачем нужен наш класс, если есть вектор?),
удалить не нужный buffer, копировать напрямую в "нововыделенную" память, можно перегрузить квадратные скобочки */


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


/*template <typename T>
DArray<T>&:: operator[] (int index){

}*/

template <typename T>
void DArray<T>::set(unsigned int id, T element) {
    data[id] = element;
}


template <typename T>
void DArray<T>::resize(unsigned int new_size) {
    if (new_size <= size + cache_size) {
        cache_size -= new_size - size;
        size = new_size;
    } else {
        cache_size = 5;
        T *new_data = new T[new_size + cache_size];
        std::memcpy(new_data, data, sizeof(T) * size);
        size = new_size;
        delete (data);
        data = new_data;
    }
}



template<typename T>
T DArray<T>::get(unsigned int id) const {
    return data[id];
}


template<typename T>
void DArray<T>::print() const {
    std::cout << "{";
    for (int id = 0; id < size; ++id)
        std::cout << data[id] << ", ";
    std::cout << "}" << "\n" << std::endl;
}


template class DArray<int>;
template class DArray<double>;
template class DArray<float>;