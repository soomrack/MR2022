//
// Created by user on 28.11.22.
//

#include "EMatrix.h"


template<typename T>
unsigned int EMatrix<T>::calcMemory(int c_rows, int c_cols) {
    return c_rows * c_cols * sizeof(T) + c_rows * sizeof(T *);
}


template<typename T>
EMatrix<T>::EMatrix(): Matrix<T>() {
    counter++;
    memory_size = 0;
}


template<typename T>
EMatrix<T>::EMatrix(int input_rows, int input_cols): Matrix<T>(input_rows, input_cols) {
    counter++;
    memory_size = calcMemory(input_rows, input_cols);
    general_size += memory_size;
}


template<typename T>
EMatrix<T>::EMatrix(int input_rows, int input_cols, T number): Matrix<T>(input_rows, input_cols, number) {
    counter++;
    memory_size = calcMemory(input_rows, input_cols);
    general_size += memory_size;
}


template<typename T>
EMatrix<T>::EMatrix(int input_rows, int input_cols, const std::vector<T> &v):Matrix<T>(input_rows, input_cols, v) {
    counter++;
    memory_size = calcMemory(input_rows, input_cols);
    general_size += memory_size;
}


template<typename T>
EMatrix<T>::EMatrix(int identity_size): Matrix<T>(identity_size) {
    counter++;
    memory_size = calcMemory(identity_size, identity_size);
    general_size += memory_size;
}


template<typename T>
EMatrix<T>::EMatrix(const EMatrix<T> &other): Matrix<T>(other) {
    memory_size = other.memory_size;
}


template<typename T>
EMatrix<T>::EMatrix(EMatrix<T> &&other) noexcept: Matrix<T>(other) {
    memory_size = other.memory_size;
    other.memory_size = 0;
}


template<typename T>
EMatrix<T>::~EMatrix() {
    counter--;
    general_size -= memory_size;
    memory_size = 0;
}


template<typename T>
EMatrix<T>& EMatrix<T>::operator=(const EMatrix<T> &other) {
    Matrix<T>::operator=(other);
    general_size += other.memory_size - memory_size;
    memory_size = other.memory_size;
    return *this;
}


template<typename T>
EMatrix<T>& EMatrix<T>::operator=(EMatrix<T> &&other) noexcept {
    Matrix<T>::operator=(other);
    general_size += other.memory_size - memory_size;
    memory_size = other.memory_size;
    other.memory_size = 0;
    return *this;
}


template<typename T>
unsigned int EMatrix<T>::getCounter() {
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
