//
// Created by user on 08.11.22.
//

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <iomanip>
#include <vector>
#include "MatrixException.h"

class Matrix {
    friend class MatrixTest;
private:
    int rows;
    int cols;
    int size;
    double **values;
    double *start;

public:
    inline static const double EPSILON = 0.000001;
    inline static const int EXP_STEP = 177;
    Matrix();  //  empty matrix
    Matrix(int input_rows, int input_cols);
    Matrix(int input_rows, int input_cols, double number);  //  number filled matrix
    explicit Matrix(int row_number);  //  identity matrix
    Matrix(int input_rows, int input_cols, std::vector<double> array);  // filling from array
    ~Matrix();
    Matrix(Matrix const &matrix);
    Matrix(Matrix &&matrix) noexcept;

    Matrix &operator= (Matrix const &matrix);
    Matrix &operator= (Matrix const &&matrix) noexcept;
    Matrix operator+ (Matrix matrix) const;
    Matrix operator+ (double number) const;
    Matrix operator- (Matrix matrix) const;
    Matrix operator* (Matrix matrix) const;
    Matrix operator* (double number) const;
    Matrix operator/ (Matrix matrix) const;
    Matrix operator/ (double number) const;

    int get_rows() const;
    int get_cols() const;
    int get_size() const;
    void output() const;
    Matrix minor_init(int excluded_row, int excluded_col) const;
    double determinant() const;
    Matrix transposition() const;
private:
    static Matrix minor_transformation(Matrix matrix);
public:
    Matrix inversion() const;
    Matrix power(int power) const;
    static Matrix exp(Matrix matrix);
};

#endif //MATRIX_H
