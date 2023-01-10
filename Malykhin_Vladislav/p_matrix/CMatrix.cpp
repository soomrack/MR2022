#include "CMatrix.h"


unsigned int CMatrix::calcMemory(int c_rows, int c_cols) {
    return c_rows * c_cols * sizeof(double) + c_rows * sizeof(double *);
}



CMatrix::CMatrix(): Matrix() {
    counter++;
    memory_size = 0;
}



[[maybe_unused]] CMatrix::CMatrix(int input_rows, int input_cols): Matrix(input_rows, input_cols) {
    counter++;
    memory_size = calcMemory(input_rows, input_cols);
    general_size += memory_size;
}



CMatrix::CMatrix(int input_rows, int input_cols, double number): Matrix(input_rows, input_cols, number) {
    counter++;
    memory_size = calcMemory(input_rows, input_cols);
    general_size += memory_size;
}



CMatrix::CMatrix(int input_rows, int input_cols, const std::vector<double> &v):Matrix(input_rows, input_cols, v) {
    counter++;
    memory_size = calcMemory(input_rows, input_cols);
    general_size += memory_size;
}




CMatrix::CMatrix(const CMatrix &other): Matrix(other) {
    memory_size = other.memory_size;
}



CMatrix::CMatrix(CMatrix &&other) noexcept: Matrix(other) {
    memory_size = other.memory_size;
    other.memory_size = 0;
}



CMatrix::~CMatrix() {
    counter--;
    general_size -= memory_size;
    memory_size = 0;
}



CMatrix& CMatrix::operator=(const CMatrix &other) {
    Matrix::operator=(other);
    general_size += other.memory_size - memory_size;
    memory_size = other.memory_size;
    return *this;
}



CMatrix& CMatrix::operator=(CMatrix &&other) noexcept {
    Matrix::operator=(other);
    general_size += other.memory_size - memory_size;
    memory_size = other.memory_size;
    other.memory_size = 0;
    return *this;
}



unsigned int CMatrix::get_counter() {
    return counter;
}



unsigned int CMatrix::get_gen_size() {
    return general_size;
}



unsigned int CMatrix::get_mem_size() {
    return memory_size;
}
