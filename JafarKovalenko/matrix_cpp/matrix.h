#include "matrix_exception.h"
#include <cmath>

#ifndef MATRIX_CLION_MATRIX_H
#define MATRIX_CLION_MATRIX_H

class Matrix{
private:
    int ROW;
    int COL;
public:
    double *array;

    void set_size(int row, int col);

    int get_row() const{ return this->ROW; }
    int get_col() const{ return this->COL; }

    Matrix();
    Matrix(int row, int col);
    Matrix(int row, int col, double *input);


    void fill_zero() const;
    void fill_unit() const;
    void identity_matrix() const;
    void copy_matrix(const Matrix& matrix);
    void input_matrix(double *input_matrix);

    void addition_matrix(const Matrix& summand1, const Matrix& summand2);
    void subtraction_matrix(const Matrix& summand1, const Matrix& summand2);
    void multiplication_by_number_matrix(const Matrix& matrix, double number);
    void multiplication_matrix(const Matrix& multiplier1, const Matrix& multiplier2);
    void power_matrix(const Matrix& matrix, int degree);
    void transpose_matrix(const Matrix& matrix);
    void minor_matrix(const Matrix& matrix, int minor_row, int minor_col);

    bool swap_matrix(Matrix& matrix, int row);
    void diagonalize_matrix(Matrix& matrix);
    void determinant_matrix(const Matrix& matrix);

    void exponential_matrix(const Matrix& matrix);
};


#endif
