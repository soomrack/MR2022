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


class Matrix {
    friend class MatrixTest;
private:
    int rows;
    int cols;
    int size;
    double **data;
    double *values;
public:
    inline static const double EPSILON = 0.000001;
    inline static const int DEFAULT_EXP_STEPS = 177;

    Matrix();  //  empty matrix
    Matrix(int input_rows, int input_cols, double number=NAN);
    ~Matrix();
    Matrix(const Matrix &other);
    Matrix(Matrix &&other) noexcept;

    void fillFromVector(std::vector<double> vector);
    void set_identity();
    int get_rows() const;
    int get_cols() const;
    int get_size() const;
    double get_value(int row, int col) const;
    void output() const;

    Matrix &operator= (Matrix const &other);
    Matrix &operator= (Matrix &&other) noexcept;
    Matrix operator+ (const Matrix &matrix) const;
    Matrix operator+ (double number) const;
    Matrix operator- (const Matrix &matrix) const;
    Matrix operator* (const Matrix &matrix) const;
    Matrix operator* (double number) const;
    Matrix operator/ (const Matrix &matrix) const;
    Matrix operator/ (double number) const;

    Matrix minor_init(int excluded_row, int excluded_col) const;
    double determinant() const;
    Matrix transposition() const;
private:
    static Matrix minor_transformation(const Matrix &matrix);
public:
    Matrix inversion() const;
    Matrix power(int power) const;
    static Matrix exp(const Matrix &matrix, int STEPS=DEFAULT_EXP_STEPS);
};


#endif //MATRIX_H
