//
// Created by user on 08.11.22.
//

#ifndef MATRIX_H
#define MATRIX_H


#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <cstring>
#include "MatrixException.h"


template <typename T>
class Matrix {
private:
    int rows;
    int cols;
    int size;
    T **data;
    T *values;
public:
    inline static const T EPSILON = 0.000001;
    inline static const int DEFAULT_EXP_STEPS = 177;

    Matrix();  //  empty matrix
    Matrix(int input_rows, int input_cols);
    Matrix(int input_rows, int input_cols, T number);
    Matrix(int input_rows, int input_cols, const std::vector<T>& vector);
    explicit Matrix(int identity_size);
    ~Matrix();
    Matrix(const Matrix<T> &other);
    Matrix(Matrix<T> &&other) noexcept;

    int get_rows() const;
    int get_cols() const;
    int get_size() const;
    T get_value(int cell) const;
    T get_value(int row, int col) const;
    void set_value(int cell, T number);
    void set_value(int row, int col, T number);
    void output() const;
    void test();

    Matrix& operator= (Matrix const &other);
    Matrix& operator= (Matrix<T> &&other) noexcept;
    Matrix<T> operator+ (const Matrix<T> &matrix) const;
    Matrix operator+ (T number) const;
    Matrix operator- (const Matrix<T> &matrix) const;
    Matrix operator* (const Matrix<T> &matrix) const;
    Matrix operator* (T number) const;
    Matrix operator/ (const Matrix<T> &matrix) const;
    Matrix operator/ (T number) const;

    Matrix minor_init(int excluded_row, int excluded_col) const;
    T determinant() const;
    Matrix transposition() const;
private:
    static Matrix minor_transformation(const Matrix<T> &matrix);
public:
    Matrix inversion() const;
    Matrix power(int power) const;
    static Matrix exp(const Matrix<T> &matrix, int STEPS=DEFAULT_EXP_STEPS);
    static int is_equal(Matrix<T> matrix1, Matrix<T> matrix2);
};


#endif //MATRIX_H
