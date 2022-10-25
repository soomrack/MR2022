//
// Created by user on 24.10.2022.
//

#include "Matrix.h"


Matrix::Matrix(unsigned int r_num, unsigned int c_num, double* values_ptr){
    rows = r_num;
    cols = c_num;
    values = values_ptr;
}


Matrix::Matrix(unsigned int r_num, unsigned int c_num, double default_value) {
    // Создание матрицы без значений
    rows = r_num;
    cols = c_num;
    values = (double *)malloc(sizeof(double) * rows * cols);
    if (values == nullptr) {
        rows = 0;
        cols = 0;
    }
    if (default_value == default_value){
        for (int idx = 0; idx < rows * cols; idx++) values[idx] = default_value;
    }
}


Matrix Matrix::copy(){
    Matrix res = Matrix(rows, cols);
    memcpy(res.values, values, rows * cols * sizeof(double));
    return res;
}


double Matrix::get(unsigned int row, unsigned int col){
    if (row > rows || col > cols) return NAN;
    return values[col + row * cols];
}


void Matrix::set(unsigned int row, unsigned int col, double value){
    if (row > rows || col > cols) return;
    values[col + row * cols] = value;
}


double* Matrix::operator[](unsigned int idx){
    if (idx > rows) return nullptr;
    return values + idx * cols;
}


bool Matrix::operator==(Matrix mat2) {
    Matrix mat1 = *this;
    if (mat1.cols != mat2.cols || mat1.rows != mat2.rows) return false;
    for (unsigned int idx = 0; idx < mat1.cols * mat1.rows; idx++){
        if (abs(mat1.values[idx] - mat2.values[idx]) > EPS) return false;
    }
    return true;
}


Matrix Matrix::fill_random(int min_value, int max_value) {
    std::srand(std::time(nullptr));
    for (int idx = 0; idx < rows * cols; idx++){
        values[idx] = min_value + (double) rand() / (double) RAND_MAX * (max_value - min_value);
    }
    return {rows, cols, values};
}


Matrix Matrix::fill_identity(){
    if (rows != cols){
        return {0, 0, nullptr};
    }
    for (unsigned int idx = 0; idx < rows * cols; idx++){
        values[idx] = idx % (rows + 1) == 0 ? 1.0 : 0.0;
    }
    return {rows, cols, values};
}


Matrix Matrix::fill_from_array(double* array){
    memcpy(values, array, rows * cols * sizeof(double));
    return {rows, cols, values};
}


bool Matrix::is_identity() {
    if (cols != rows) return false;
    for (unsigned int idx = 0; idx < rows * cols; idx++){
        if (idx % (rows + 1) == 0){
            if (abs(values[idx] - 1) > EPS)  return false;
        }
        else{
            if (abs(values[idx]) > EPS) return false;
        }
    }
    return true;
}


Matrix Matrix::add(Matrix mat) {
    if (cols != mat.cols || rows != mat.rows){
        return null();
    }
    Matrix res = this->copy();
    for (unsigned int idx = 0; idx < rows * cols; idx++){
        res.values[idx] += mat.values[idx];
    }
    return res;
}


void Matrix::print() {
    printf("\n");
    for (unsigned int row = 0; row < rows; row++){
        for (unsigned int col = 0; col < cols; col++){
            printf(" %f", values[row * cols + col]);
        }
        printf("\n");
    }
}


void printm(Matrix mat){
    std::cout << std::endl;
    for (unsigned int row = 0; row < mat.rows; row++){
        for (unsigned int col = 0; col < mat.cols; col++){
            std::cout << " " << mat[row][col] << " ";
        }
        std::cout << std::endl;
    }
}