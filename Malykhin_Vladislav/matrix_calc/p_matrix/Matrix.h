#ifndef MR2022_MATRIX_H
#define MR2022_MATRIX_H


#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <cstring>
#include "MatrixException.h"


class Matrix{
protected:
    int rows;
    int cols;
    double **data;
    double *values;
public:
    inline static const double EPSILON = 0.000001;

    Matrix() noexcept;  //  empty matrix
    Matrix(int input_rows, int input_cols);
    Matrix(int input_rows, int input_cols, double number);
    ~Matrix() noexcept;
    Matrix(const Matrix &other) ;
    Matrix(Matrix &&other) noexcept;
    Matrix(int input_rows, int input_columns, const std::vector<double> &vector);
    explicit Matrix(int identity_size);


    int get_rows() const;
    int get_cols() const;
    int get_size() const;
    double get_cell(int row, int column) const;
    void print() const;

    Matrix &operator= (Matrix const &other) ;
    Matrix &operator= (Matrix &&other) noexcept;
    Matrix  operator+ (const Matrix &matrix) const;
    Matrix  operator+ (double number) const;
    Matrix  operator- (const Matrix &matrix) const;
    Matrix  operator- (double number) const;
    Matrix  operator* (const Matrix &matrix) const;
    Matrix  operator* (double number) const;
    Matrix  operator/ (const Matrix &matrix) const;
    Matrix  operator/ (double number) const;

    Matrix minor_matrix(int excluded_row, int excluded_col) const;
    double determinant() const;
    Matrix transposition() const;
public:
    Matrix inversion() const;
    Matrix power(int power) const;
    static Matrix exp(const Matrix &matrix, int STEPS=177);
};


#endif //MR2022_MATRIX_H
