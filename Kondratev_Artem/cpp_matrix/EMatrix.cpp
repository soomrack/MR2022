//
// Created by user on 28.11.22.
//

#include "EMatrix.h"


template<typename T>
unsigned int EMatrix<T>::calc_memory(int rows, int cols) {
    return rows * cols * sizeof(T) + rows * sizeof(T *);
}


template<typename T>
EMatrix<T>::EMatrix(): Matrix<T>() {
    counter++;
    memory_size = 0;
}


template<typename T>
EMatrix<T>::EMatrix(int input_rows, int input_cols): Matrix<T>(input_rows, input_cols) {
    counter++;
    memory_size = calc_memory(input_rows, input_cols);
    general_size += memory_size;
}


template<typename T>
EMatrix<T>::EMatrix(int input_rows, int input_cols, T number): Matrix<T>(input_rows, input_cols, number) {
    counter++;
    memory_size = calc_memory(input_rows, input_cols);
    general_size += memory_size;
}


template<typename T>
EMatrix<T>::EMatrix(int input_rows, int input_cols, const std::vector<T> &v):Matrix<T>(input_rows, input_cols, v) {
    counter++;
    memory_size = calc_memory(input_rows, input_cols);
    general_size += memory_size;
}


template<typename T>
EMatrix<T>::EMatrix(int identity_size): Matrix<T>(identity_size) {
    counter++;
    memory_size = calc_memory(identity_size, identity_size);
    general_size += memory_size;
}


template<typename T>
EMatrix<T>::~EMatrix() {
    counter--;
    general_size -= memory_size;
    memory_size = 0;
}


template<typename T>
unsigned int EMatrix<T>::get_counter() {
    return counter;
}


template<typename T>
unsigned int EMatrix<T>::getGenSize() {
    return general_size;
}


template<typename T>
unsigned int EMatrix<T>::getMemSize() {
    return memory_size;
}


template
class EMatrix<double>;

template
class EMatrix<float>;
