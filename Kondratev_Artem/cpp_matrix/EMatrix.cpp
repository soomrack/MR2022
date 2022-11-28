//
// Created by user on 28.11.22.
//

#include "EMatrix.h"


unsigned int EMatrix::calc_memory(int rows, int cols) {
    return rows * cols * sizeof(double) + rows * sizeof(double*);
}


EMatrix::EMatrix(): Matrix() {
    counter++;
}


EMatrix::EMatrix(int input_rows, int input_cols): Matrix(input_rows, input_cols) {
    counter++;
    memory_size = calc_memory(input_rows, input_cols);
    general_size += memory_size;
}


EMatrix::EMatrix(int input_rows, int input_cols, double number): Matrix(input_rows, input_cols, number) {
    counter++;
    memory_size = calc_memory(input_rows, input_cols);
    general_size += memory_size;
}


EMatrix::EMatrix(int input_rows, int input_cols, const std::vector<double>& v):Matrix(input_rows, input_cols,v) {
    counter++;
    memory_size = calc_memory(input_rows, input_cols);
    general_size += memory_size;
}


EMatrix::EMatrix(int identity_size): Matrix(identity_size) {
    counter++;
    memory_size = calc_memory(identity_size, identity_size);
    general_size += memory_size;
}


EMatrix::~EMatrix() {
    counter--;
    general_size -= memory_size;
}


unsigned int EMatrix::get_counter() {
    return counter;
}
