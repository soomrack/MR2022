//
// Created by User on 05.12.2022.
//

#ifndef MR2022_MATRIX_H
#define MR2022_MATRIX_H


#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>


class Matrix{
private:
    int rows;
    int columns;
    std::vector <std::vector <double>> cells;
public:
    inline static const double EPSILON = 0.000001;
    inline static const int DEFAULT_EXP_STEPS = 177;

    Matrix() noexcept;  //  empty matrix
    Matrix(int input_rows, int input_cols, double number = NAN);
    ~Matrix() noexcept;
    Matrix(const Matrix &other) noexcept;
    Matrix(Matrix &&other) noexcept;

    void vector_fill(std::vector<double> vector);
    void vector_fill(const std::vector<std::vector<double>>&);
    void set_identity();
    unsigned int get_rows() const;
    unsigned int get_columns() const;
    unsigned int get_size() const;
    double get_cell(int row, int column) const;
    void output() const;

    Matrix &operator= (Matrix const &other);
    Matrix &operator= (Matrix &&other) noexcept;
    Matrix operator+ (const Matrix &matrix) const;
    Matrix operator+ (double number) const;
    Matrix operator- (const Matrix &matrix) const;
    Matrix operator- (double number) const;
    Matrix operator* (const Matrix &matrix) const;
    Matrix operator* (double number) const;
    Matrix operator/ (const Matrix &matrix) const;
    Matrix operator/ (double number) const;

    Matrix minor_matrix(int excluded_row, int excluded_col) const;
    double determinant() const;
    Matrix transposition() const;
public:
    Matrix inversion() const;
    Matrix power(int power) const;
    static Matrix exp(const Matrix &matrix, int STEPS=DEFAULT_EXP_STEPS);
};


#endif //MR2022_MATRIX_H
