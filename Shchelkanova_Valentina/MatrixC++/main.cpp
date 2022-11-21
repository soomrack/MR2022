#include <iostream>
#include <stdlib.h>
#include <malloc.h>

class Matrix {
    unsigned int cols;
    unsigned int rows;
    double* values;

public:
    Matrix();  // Конструктор пустой матрицы
    Matrix(unsigned int col, unsigned int row);  // Конструктор прямоугольной матрицы
    Matrix(const Matrix& matrix);  // Конструктор копирования матрицы
    Matrix(Matrix&& matrix);  // Конструктор переноса матрицы
    ~Matrix();  // Деструктор


    void print_matrix();
    void set_values();

    Matrix operator+(const Matrix& One) const;
    Matrix operator-(const Matrix& One) const;
    Matrix operator*(const Matrix& One) const;
    Matrix operator*(const double COEFFICIENT) const;


};

Matrix::Matrix() {
    cols = 0;
    rows = 0;
}


Matrix::Matrix(unsigned int col, unsigned int row) {
    cols = col;
    rows = row;
    unsigned int n_values = cols * rows;
    values = (double*)malloc(n_values * sizeof(double));
    for (unsigned int idx = 0; idx < n_values; ++idx) {
        values[idx] = 0.0;
    }
}


Matrix::Matrix(const Matrix& matrix) {
    cols = matrix.cols;
    rows = matrix.rows;
    unsigned int n_values = cols * rows;
    values = (double*)malloc(n_values * sizeof(double));
    for (unsigned int idx = 0; idx < n_values; ++idx) {
        values[idx] = matrix.values[idx];
    }
}


Matrix::Matrix(Matrix&& matrix) {
    cols = matrix.cols;
    rows = matrix.rows;
    unsigned int n_values = cols * rows;
    values = (double*)malloc(n_values * sizeof(double));
    for (unsigned int idx = 0; idx < n_values; ++idx) {
        values[idx] = matrix.values[idx];
    }
    matrix.~Matrix();
}


Matrix::~Matrix() {
    free(values);
}


void Matrix::print_matrix() {
    for (unsigned int row = 0; row < rows; ++row) {
        for (unsigned int col = 0; col < cols; ++col) {
            std::cout << values[row * cols + col] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}


void Matrix::set_values() {
    for (unsigned int index = 0; index < rows * cols; ++index) {
        values[index] = (double)rand();
    }
}


Matrix Matrix::operator+ (const Matrix& One) const {
    Matrix Res(One.cols, One.rows);
    for (unsigned int idx = 0; idx < One.cols * One.rows; idx++) {
        Res.values[idx] = values[idx] + One.values[idx];
    }
    return Res;
}


Matrix Matrix::operator- (const Matrix& One) const {
    Matrix Res(One.cols, One.rows);
    for (unsigned int idx = 0; idx < One.cols * One.rows; idx++) {
        Res.values[idx] = values[idx] - One.values[idx];
    }
    return Res;
}


Matrix Matrix::operator* (const Matrix& One) const {
    Matrix Res(One.cols, One.rows);
    for (unsigned int row = 0; row < Res.rows; row++) {
        for (unsigned int col = 0; col < Res.cols; col++) {
            Res.values[row* Res.rows + col] = 0.00;
            for (unsigned int k = 0; k < Res.cols; k++) {
                Res.values[row * Res.cols + col] += values[row * cols + k] * One.values[k * Res.cols + col];
            }
        }
    }
    return Res;
}


Matrix Matrix::operator* (const double COEFFICIENT) const {
    Matrix Res(cols, rows);
    for (unsigned int idx = 0; idx < rows * cols; idx++) {
        Res.values[idx] = values[idx] * COEFFICIENT;
    }
    return Res;
}


int main() {
    Matrix A(5,5);
    A.set_values();
    A.print_matrix();
    Matrix B(5, 5);
    B.set_values();
    B.print_matrix();
    Matrix Sum = A + B;
    Sum.print_matrix();
    Matrix Sub = A - B;
    Sub.print_matrix();
    Matrix Mult = A * B;
    Mult.print_matrix();
    Matrix Mult_double = A * 4;
    Mult_double.print_matrix();
    return 0;
}