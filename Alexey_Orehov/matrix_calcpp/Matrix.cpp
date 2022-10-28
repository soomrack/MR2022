//
// Created by user on 24.10.2022.
//

#include "Matrix.h"


Matrix::Matrix(){
    rows = 0;
    cols = 0;
    values = nullptr;
}

Matrix::Matrix(unsigned int r_num, unsigned int c_num) {
    rows = r_num;
    cols = c_num;
    values = new double[rows * cols];
}


Matrix::Matrix(const Matrix &mat) {
    rows = mat.rows;
    cols = mat.cols;
    values = new double[rows * cols];
    memcpy(values, mat.values, sizeof(double) * rows * cols);
}


Matrix Matrix::fill_number(double val) {
    for (int idx = 0; idx < rows * cols; idx++) values[idx] = val;
    return *this;
}


double Matrix::get(unsigned int row, unsigned int col) {
    if (row > rows || col > cols) return NAN;
    return values[col + row * cols];
}


void Matrix::set(unsigned int row, unsigned int col, double value) {
    if (row > rows || col > cols) return;
    values[col + row * cols] = value;
}


double* Matrix::operator[](unsigned int idx) {
    if (idx > rows) return nullptr;
    return values + idx * cols;
}


bool Matrix::operator==(const Matrix& mat) {
    Matrix mat1 = *this;
    if (mat1.cols != mat.cols || mat1.rows != mat.rows) return false;
    for (unsigned int idx = 0; idx < mat1.cols * mat1.rows; idx++){
        if (abs(mat1.values[idx] - mat.values[idx]) > EPS) return false;
    }
    return true;
}


Matrix Matrix::fill_random(int min_value, int max_value) {
    for (int idx = 0; idx < rows * cols; idx++){
        values[idx] = min_value + (double) rand() / (double) RAND_MAX * (max_value - min_value);
    }
    return *this;
}


Matrix Matrix::fill_identity() {
    if (rows != cols){
        return {};
    }
    for (unsigned int idx = 0; idx < rows * cols; idx++){
        this->values[idx] = idx % (rows + 1) == 0 ? 1.0 : 0.0;
    }
    return *this;
}


Matrix Matrix::fill_from_array(double* array) {
    memcpy(values, array, rows * cols * sizeof(double));
    return *this;
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


Matrix Matrix::operator+(const Matrix& mat2) const {
    Matrix res = {rows, cols};
    for (int idx = 0; idx < rows * cols; idx++){
        res.values[idx] = this->values[idx] + mat2.values[idx];
    }
    return res;
}


Matrix Matrix::operator-(const Matrix& mat2) const {
    Matrix res = {rows, cols};
    for (int idx = 0; idx < rows * cols; idx++){
        res.values[idx] = this->values[idx] - mat2.values[idx];
    }
    return res;
}