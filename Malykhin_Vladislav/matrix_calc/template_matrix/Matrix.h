#ifndef MR2022_MATRIX_H
#define MR2022_MATRIX_H


#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include "MatrixException.h"


template <typename T>
class Matrix{
protected:
    int rows;
    int columns;
    std::vector <std::vector <T>> cells;
public:
    inline static const double EPSILON = 0.000001;
    inline static const int DEFAULT_EXP_STEPS = 177;

    Matrix() noexcept;  //  empty matrix
    Matrix(int input_rows, int input_cols);
    Matrix(int input_rows, int input_cols, T number);
    ~Matrix() noexcept = default;
    Matrix(const Matrix<T> &other) noexcept;
    Matrix(Matrix<T> &&other) noexcept;
    Matrix(int input_rows, int input_columns, const std::vector<T> &vector);

    void set_identity();
    int get_rows() const;
    int get_columns() const;
    int get_size() const;
    T get_cell(int row, int column) const;
    void print() const;

    Matrix<T>& operator= (Matrix<T> const &other);
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
    static Matrix<T> exp(const Matrix<T> &matrix, int STEPS=DEFAULT_EXP_STEPS);
};


#endif //MR2022_MATRIX_H
