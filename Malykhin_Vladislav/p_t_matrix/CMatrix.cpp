#include "CMatrix.h"//добавить в конструкторы копии и переноса изменения counter и  memory и general memory

template<typename T>
unsigned int CMatrix<T>::calcMemory(int c_rows, int c_cols) {
    return c_rows * c_cols * sizeof(T) + c_rows * sizeof(T *);
}


template<typename T>
CMatrix<T>::CMatrix(): Matrix<T>() {
    counter++;
    memory_size = 0;
}


template<typename T>
[[maybe_unused]] CMatrix<T>::CMatrix(int input_rows, int input_cols): Matrix<T>(input_rows, input_cols) {
    counter++;
    memory_size = calcMemory(input_rows, input_cols);
    general_size += memory_size;
}


template<typename T>
CMatrix<T>::CMatrix(int input_rows, int input_cols, T number): Matrix<T>(input_rows, input_cols, number) {
    counter++;
    memory_size = calcMemory(input_rows, input_cols);
    general_size += memory_size;
}


template<typename T>
CMatrix<T>::CMatrix(int input_rows, int input_cols, const std::vector<T> &v):Matrix<T>(input_rows, input_cols, v) {
    counter++;
    memory_size = calcMemory(input_rows, input_cols);
    general_size += memory_size;
}



template<typename T>
CMatrix<T>::CMatrix(const CMatrix<T> &other): Matrix<T>(other) { //ошибка
    counter++;
    memory_size = other.memory_size;
    general_size += memory_size;
}


template<typename T>
CMatrix<T>::CMatrix(CMatrix<T> &&other) noexcept: Matrix<T>(other) { // ошибка
    counter++;
    memory_size = other.memory_size;
    other.memory_size = 0;
}


template<typename T>
CMatrix<T>::~CMatrix() {
    counter--;
    general_size -= memory_size;
    memory_size = 0;
}


template<typename T>
CMatrix<T>& CMatrix<T>::operator=(const CMatrix<T> &other) {
    Matrix<T>::operator=(other);
    general_size += other.memory_size - memory_size;
    memory_size = other.memory_size;
    return *this;
}


template<typename T>
CMatrix<T>& CMatrix<T>::operator=(CMatrix<T> &&other) noexcept {
    Matrix<T>::operator=(other);
    general_size += other.memory_size - memory_size;
    memory_size = other.memory_size;
    other.memory_size = 0;
    return *this;
}


template<typename T>
unsigned int CMatrix<T>::get_counter() {
    return counter;
}


template<typename T>
unsigned int CMatrix<T>::get_gen_size() {
    return general_size;
}


template<typename T>
unsigned int CMatrix<T>::get_mem_size() {
    return memory_size;
}


template
class CMatrix<double>;

template
class CMatrix<float>;

