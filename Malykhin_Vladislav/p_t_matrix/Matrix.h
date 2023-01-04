#ifndef MR2022_MATRIX_H
#define MR2022_MATRIX_H


#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <cstring>
#include "MatrixException.h"


template <typename T>
class Matrix{
protected:
    int rows;
    int cols;
    T **data;
    T *values;
public:
    inline static const double EPSILON = 0.000001;

    Matrix() noexcept;  //  empty matrix
    Matrix(int input_rows, int input_cols);
    Matrix(int input_rows, int input_cols, T number);
    ~Matrix() noexcept;
    Matrix(const Matrix<T> &other) ;
    Matrix(Matrix<T> &&other) noexcept;
    Matrix(int input_rows, int input_columns, const std::vector<T> &vector);
    explicit Matrix(int identity_size);


    int get_rows() const;
    int get_cols() const;
    int get_size() const;
    T get_cell(int row, int column) const;
    void print() const;

    Matrix<T>& operator= (Matrix<T> const &other) ;
    Matrix<T>& operator= (Matrix<T> &&other) noexcept;
    Matrix<T> operator+ (const Matrix<T> &matrix) const;
    Matrix<T> operator+ (T number) const;
    Matrix<T> operator- (const Matrix<T> &matrix) const;
    Matrix<T> operator- (T number) const;
    Matrix<T> operator* (const Matrix<T> &matrix) const;
    Matrix<T> operator* (T number) const;
    Matrix<T> operator/ (const Matrix<T> &matrix) const;
    Matrix<T> operator/ (T number) const;

    Matrix<T> minor_matrix(int excluded_row, int excluded_col) const;
    T determinant() const;
    Matrix<T> transposition() const;
public:
    Matrix<T> inversion() const;
    Matrix<T> power(int power) const;
    static Matrix<T> exp(const Matrix<T> &matrix, int STEPS=177);
};


#endif //MR2022_MATRIX_H
