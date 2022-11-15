//
// Created by user on 08.11.22.
//

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include "MatrixException.h"

class Matrix {
    friend class MatrixTest;
private:
    int rows;
    int cols;
    int size;
    double **pointers;
    double *data;

public:
    inline static const double EPSILON = 0.000001;
    inline static const int EXP_STEP = 177;
    Matrix();  //  empty matrix
    Matrix(int input_rows, int input_cols, int identity_flag);
    Matrix(int input_rows, int input_cols, double number);  //  number filled matrix
    Matrix(int input_rows, int input_cols, std::vector<double> array);  // filling from array
    ~Matrix();
    Matrix(const Matrix &other);
    Matrix(Matrix &&other) noexcept;

    Matrix &operator= (Matrix const &other);
    Matrix &operator= (Matrix &&other) noexcept;
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
