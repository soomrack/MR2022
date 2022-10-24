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


double* Matrix::operator[](unsigned int idx){
    if (idx > rows){
        return nullptr;
    }
    return values + idx * cols;
}


Matrix Matrix::random(int min_value, int max_value) {
    std::srand(std::time(nullptr));
    for (int idx = 0; idx < rows * cols; idx++){
        values[idx] = min_value + (double) rand() / (double) RAND_MAX * (max_value - min_value);
    }
    return {rows, cols, values};
}

Matrix Matrix::identity(){
    if (rows != cols){
        return {0, 0, nullptr};
    }
    for (unsigned int idx = 0; idx < rows * cols; idx++){
        values[idx] = idx % (rows + 1) == 0 ? 1.0 : 0.0;
    }
    return {rows, cols, values};
}


Matrix Matrix::from_array(double* array){
    memcpy(values, array, rows * cols * sizeof(double));
    return {rows, cols, values};
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