#include "matrix.h"
#include "matrix_exception.h"
#include <iostream>


Matrix::Matrix(int row, int col){
    this->ROW = row;
    this->COL = col;
    this->array = new double[this->ROW * this->COL];
    this->fill_zero();
}

Matrix::Matrix():Matrix(3, 3){
    fill_unit();
}

Matrix::Matrix(int row, int col, double *input):Matrix(row, col){
    input_matrix(input);
}


void Matrix::set_size(int row, int col) {
    this->ROW = row;
    this->COL = col;
}


void Matrix::fill_zero() const{
    for (int row = 0; row < this->ROW; row++){
        for (int col = 0; col < this->COL; col++){
            this->array[row * this->COL + col] = 0.0;
        }
    }
}


void Matrix::fill_unit() const{
    for (int row = 0; row < this->ROW; row++){
        for (int col = 0; col < this->COL; col++){
            this->array[row * this->COL + col] = 1.0;
        }
    }
}


void Matrix::identity_matrix() const{
    this->fill_zero();
    for (int row = 0; row < this->ROW; row++)
        this->array[row * this->COL + row] = 1;
}


void Matrix::copy_matrix(const Matrix &matrix){
    this->set_size(matrix.ROW, matrix.COL);
    for (int item = 0; item < this->ROW * this->COL; item++)
        this->array[item] = matrix.array[item];
}


void Matrix::input_matrix(double *input_matrix){
    for (int row = 0; row < this->ROW; row++){
        for (int col = 0; col < this->COL; col++)
            this->array[row * this->COL + col] = input_matrix[row * this->COL + col];
    }
}


void Matrix::addition_matrix(const Matrix &summand1, const Matrix &summand2){
    if ((summand1.ROW != summand2.ROW) || (summand1.COL != summand2.COL)){
        throw Matrix_exception(1);
        return;
    }


    this->set_size(summand1.ROW, summand1.COL);

    for (int item = 0; item < (this->ROW * this->COL); item++)
        this->array[item] = summand1.array[item] + summand2.array[item];
}


void Matrix::subtraction_matrix(const Matrix &summand1, const Matrix &summand2){
    if ((summand1.ROW != summand2.ROW) || (summand1.COL != summand2.COL)){
        throw Matrix_exception(1);
        return;
    }

    this->set_size(summand1.ROW, summand1.COL);

    for (int item = 0; item < (this->ROW * this->COL); item++)
        this->array[item] = summand1.array[item] - summand2.array[item];
}


void Matrix::multiplication_matrix(const Matrix &multiplier1, const Matrix &multiplier2){
    if (multiplier1.COL != multiplier2.ROW){
        throw Matrix_exception(2);
        return;
    }

    this->set_size(multiplier1.ROW, multiplier2.COL);
    this->fill_zero();

    for (int row = 0; row < this->ROW; row++) {
        for (int col = 0; col < this->COL; col++) {
            for (int k = 0; k < multiplier1.COL; k++)
                this->array[row * this->COL + col] +=
                        multiplier1.array[row * multiplier1.COL + k]
                        * multiplier2.array[col + multiplier2.COL * k];
        }
    }
}


void Matrix::multiplication_by_number_matrix(const Matrix &matrix, double number){
    this->set_size(matrix.ROW, matrix.COL);

    for (int item = 0; item < (this->ROW * this->COL); item++)
        this->array[item] = matrix.array[item] * number;
}


void Matrix::transpose_matrix(const Matrix &matrix){
    this->set_size(matrix.COL, matrix.ROW);

    for (int row = 0; row < this->ROW; row++){
        for (int col = 0; col < this->COL; col++)
            this->array[row * this->COL + col] = matrix.array[col * matrix.COL + row];
    }
}


void Matrix::power_matrix(const Matrix &matrix, int degree){
    if (degree < 0){
        throw Matrix_exception(5);
    }

    if (degree == 0){
        this->set_size(matrix.ROW, matrix.COL);
        this->identity_matrix();
        return;
    } else if (degree == 1) {
        this->copy_matrix(matrix);
        return;
    }

    this->set_size(matrix.ROW, matrix.COL);
    Matrix tmp(matrix.ROW, matrix.COL);
    this->copy_matrix(matrix);

    for (int i = 0; i < degree - 1; i++){
        tmp.multiplication_matrix(*this, matrix);
        this->copy_matrix(tmp);
    }
}


void Matrix::minor_matrix(const Matrix &matrix, int minor_row, int minor_col){
    if ((minor_row > matrix.ROW) || (minor_col > matrix.COL)){
        throw Matrix_exception(4);
    }


    this->set_size(matrix.ROW - 1, matrix.COL - 1);

    int col_offset = 0; // смещение по строке, чтобы "перепрыгнуть" вычеркнутую строку
    int row_offset = 0; // смещение по столбцу, чтобы "перепрыгнуть" вычеркнутый столбец

    for (int row = 0; row < this->ROW; ++row) {
        if (row == minor_row)
            row_offset = 1;
        for (int col = 0; col < this->COL; ++col) {
            if (col == minor_col)
                col_offset = 1;
            this->array[row * this->COL + col] = matrix.array[(row + row_offset) * this->COL + col + col_offset];
        }
        col_offset = 0;
    }
}


bool Matrix::swap_matrix(Matrix &matrix, int rows){
    bool was_swap = false;

    for (int row = rows; row < matrix.ROW; row++){
        if (matrix.array[row * matrix.COL + row] == 0)
            continue;
        for (int col = 0; col < matrix.COL; col++){
            std::swap(matrix.array[rows * matrix.COL + col], matrix.array[row * matrix.COL + col]);
            was_swap = true;
        }
    }

    return was_swap;
}

void Matrix::diagonalize_matrix(Matrix &matrix){
    double ratio = 0;

    for (int row = 0; row < matrix.ROW; row++){
        for (int col = row + 1; col < matrix.COL; col++){
            if (matrix.array[row * matrix.COL + row] == 0){
                if (!swap_matrix(matrix, row)){
                    throw Matrix_exception(5);
                    return;
                }
            }

            ratio = matrix.array[col * matrix.COL + row] / matrix.array[row * matrix.COL + row];
            for(int k = 0; k < matrix.COL; k++)
                matrix.array[col * matrix.COL + k] -= ratio * matrix.array[row * matrix.COL + k];
        }
    }
}


void Matrix::determinant_matrix(const Matrix &matrix){
    if (matrix.ROW != matrix.COL){
        throw Matrix_exception(3);
        return;
    }

    this->set_size(1, 1);
    this->fill_unit();

    Matrix tmp(matrix.ROW, matrix.COL);
    tmp.copy_matrix(matrix);

    tmp.diagonalize_matrix(tmp);

    for (int row = 0; row < tmp.ROW; row++)
        this->array[0] *= tmp.array[row * tmp.COL + row];
}


size_t factorial(int n){
    if ((n == 0) || (n == 1))
        return 1;

    size_t factorial = 1;
    for (int i = 2; i < n + 1; i++)
        factorial *= i;
    return factorial;
}


void Matrix::exponential_matrix(const Matrix &matrix){
    if (matrix.ROW != matrix.COL){
        throw Matrix_exception(3);
        return;
    }

    this->set_size(matrix.ROW, matrix.COL);
    double eps = 1.0/10;

    Matrix tmp(matrix.ROW, matrix.COL);

    for (int deg = 0; fabs(this->array[0]) > eps; deg++){
        tmp.power_matrix(matrix, deg);
        this->addition_matrix(*this, tmp);
        this->multiplication_by_number_matrix(*this, 1.0 / factorial(deg));
    }
}

