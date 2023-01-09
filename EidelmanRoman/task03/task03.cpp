#include <iostream>
#include <cstring>
#include <cmath>

class Matrix {
private:
    unsigned int rows = 0;
    unsigned int cols = 0;
    unsigned int matrix_size = rows * cols;
    unsigned int memory_size = matrix_size + rows;
    double** values = nullptr;
    double* data = nullptr;

    void swap(Matrix& X);
public:
    Matrix() = default;
    Matrix(unsigned int input_rows, unsigned int input_cols);
    Matrix(const Matrix& X);
    Matrix(unsigned int input_rows, unsigned int input_cols, double x);
    ~Matrix();

    Matrix& operator=(const Matrix& X);
    Matrix& operator+=(const Matrix& X);
    Matrix operator+(const Matrix& X);
    Matrix& operator-=(const Matrix& X);
    Matrix operator-(const Matrix& X);
    Matrix& operator*=(const Matrix& X);
    Matrix operator*(const Matrix& X);
    Matrix operator^(unsigned b);
    Matrix operator/(double b);

    Matrix T();
    void print();
};


Matrix::Matrix(unsigned int input_rows, unsigned int input_cols) {
    rows = input_rows;
    cols = input_cols;
    data = new double[memory_size];
    for (int row = 0; row < rows; ++row)
        values[row] = data + row * cols;
}

Matrix::Matrix(const Matrix& X) {
    matrix_size = X.matrix_size;
    data = new double[memory_size];
    memcpy(data, X.data, memory_size * sizeof(double));
}

Matrix::Matrix(unsigned int input_rows, unsigned int input_cols, double x): Matrix(input_rows, input_cols) {
    for (int i = 0; i < matrix_size; ++i) {
        data[i] = x;
    }
}

Matrix::~Matrix() {
    delete[] data;
}


Matrix& Matrix::operator=(const Matrix& X) {
    Matrix copy = X;
    swap(copy);
}

Matrix& Matrix::operator+=(const Matrix& X) {
    for (int i = 0; i < matrix_size; ++i)
        data[i] += X.data[i];
    return *this;
}

Matrix Matrix::operator+(const Matrix& X) {
    Matrix copy = *this;
    copy += X;
    return copy;
}

Matrix& Matrix::operator-=(const Matrix& X) {
    for (int i = 0; i < matrix_size; ++i)
        data[i] -= X.data[i];
    return *this;
}

Matrix Matrix::operator-(const Matrix& X) {
    Matrix copy = *this;
    copy -= X;
    return copy;
}

Matrix& Matrix::operator*=(const Matrix& X) {
    Matrix zero(rows, cols, 0);
    for (int row = 0; row < zero.rows; ++row) {
        for (int col = 0; col < zero.cols; ++col) {
            for (int k = 0; k < zero.rows; ++k) {
                zero.values[rows][cols] += values[rows][k] * X.values[k][cols];
            }
        }
    }
    *this = zero;
    return *this;
}

Matrix Matrix::operator*(const Matrix& X) {
    Matrix copy = *this;
    copy *= X;
    return copy;
}

Matrix Matrix::operator^(unsigned int b) {
    for (int i = 1; i < b; ++i)
        *this *= *this;
    return *this;
}

Matrix Matrix::operator/(double b) {
    for (int i = 0; i < matrix_size; ++i)
        data[i] /= b;
    return *this;
}

Matrix Matrix::T() {
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            values[rows][cols] = values[cols][rows];
        }
    }
    return *this;
}


void Matrix::swap(Matrix& X) {
    std::swap(memory_size, X.memory_size);
    std::swap(data, X.data);
}

void Matrix::print() {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++)
            std::cout << values[row][col] << " ";
        std::cout << "\n";
    }
    std::cout << "\n";
}


class Square_Matrix: public Matrix {
private:
    unsigned int dimension = 0;
    unsigned int rows = dimension;
    unsigned int cols = dimension;
    unsigned int matrix_size = pow(dimension, 2);
    unsigned int memory_size = matrix_size + dimension;
    double** values = nullptr;
    double* data = nullptr;
public:
    Square_Matrix() = default;
    Square_Matrix(unsigned int input_dimension);
    Square_Matrix(const Square_Matrix& X);
    Square_Matrix(unsigned int input_dimension, double x);
    ~Square_Matrix();
};


int main() {
    short n = 2;
    short m = 2;
    Matrix A(n, m);

    return 0;
}