//
// Created by user on 08.02.23.
//

#include "array.h"


template<typename T>
array<T>::array(uint64_t len, T number) {
    length = len;
    data = new T[length];
    for (int cell = 0; cell < length; cell++) {
        data[cell] = number;
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
uint64_t array<T>::len() {
    return length;
}

/*
template<typename T>
void array<T>::append(T object) {
    delete[] data;

}
*/

template
class array<double>;

template
class array<int>;
