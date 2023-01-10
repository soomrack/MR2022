#include <iostream>
#include <cstring>
#include <cmath>


class MatrixException: public std::exception {
private:
    std::string message;
public:
    explicit MatrixException(std::string input_message);
    MatrixException(const MatrixException &other) = default;
    MatrixException(MatrixException &&other) = default;
    ~MatrixException() override = default;

    std::string getMessage() const;
};

MatrixException::MatrixException(std::string input_message) {
    message = std::move(input_message);
}

std::string MatrixException::getMessage() const {
    return message;
}


class Matrix {
private:
    unsigned int rows = 0;
    unsigned int cols = 0;
    unsigned int matrix_size = rows * cols;
    double** values = nullptr;
    double* data = nullptr;

//    void swap(Matrix& X);
public:
    Matrix() = default;
    Matrix(unsigned int input_rows, unsigned int input_cols);
    Matrix(const Matrix& X);
    Matrix(Matrix&& X) noexcept;
    Matrix(unsigned int input_rows, unsigned int input_cols, double x);
    ~Matrix();

    Matrix& operator=(const Matrix& X);
    Matrix& operator=(Matrix&& X) noexcept;
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
    matrix_size = rows * cols;
    data = new double[matrix_size];
    values = new double *[rows];
    for (int row = 0; row < rows; ++row)
        values[row] = data + row * cols;
}


Matrix::Matrix(const Matrix& X) {
    rows = X.rows;
    cols = X.cols;
    matrix_size = X.matrix_size;
    data = new double[matrix_size];
    values = new double *[rows];
    memcpy(data, X.data,  matrix_size * sizeof(double));
    for (int row = 0; row < rows; ++row)
        values[row] = data + row * cols;
}


Matrix::Matrix(Matrix&& X) noexcept {
    rows = X.rows;
    cols = X.cols;
    matrix_size = X.matrix_size;
    data = X.data;
    values = X.values;
    X.data = nullptr;
    X.values = nullptr;
    for (int row = 0; row < rows; ++row)
        values[row] = data + row * cols;
}


Matrix::Matrix(unsigned int input_rows, unsigned int input_cols, double x): Matrix(input_rows, input_cols) {
    for (int i = 0; i < matrix_size; ++i)
        data[i] = x;
}


Matrix::~Matrix() {
    delete[] data;
    delete[] values;
}


Matrix& Matrix::operator=(Matrix const &X) {
    if (this == &X) {
        return *this;
    }
    delete[] data;
    delete[] values;
    rows = X.rows;
    cols = X.cols;
    matrix_size = X.matrix_size;
    data = new double[matrix_size];
    values = new double *[rows];
    memcpy(data, X.data,  matrix_size * sizeof(double));
    for (int row = 0; row < rows; ++row)
        values[row] = data + row * cols;
    return *this;
}


Matrix &Matrix::operator=(Matrix&& X) noexcept {
    if (this == &X) {
        return *this;
    }
    delete[] data;
    delete[] values;
    rows = X.rows;
    cols = X.cols;
    matrix_size = X.matrix_size;
    data = X.data;
    values = X.values;
    X.data = nullptr;
    X.values = nullptr;
    for (int row = 0; row < rows; ++row)
        values[row] = data + row * cols;
    return *this;
}


Matrix& Matrix::operator+=(const Matrix& X) {
    if (rows != X.rows || cols != X.cols) {
        throw MatrixException("Sizes don't match!\n");
    }
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
    if (rows != X.rows || cols != X.cols) {
        throw MatrixException("Sizes don't match!\n");
    }
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
    if (cols != X.rows) {
        throw MatrixException("Wrong size for multiplication!\n");
    }
    Matrix zero(rows, cols, 0);
    for (int row = 0; row < zero.rows; ++row) {
        for (int col = 0; col < zero.cols; ++col) {
            for (int k = 0; k < zero.rows; ++k) {
                zero.values[row][col] += values[row][k] * X.values[k][col];
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
    Matrix copy(rows, cols, 1);
    for (int i = 1; i < b; ++i)
        copy = copy * *this;
    return *this;
}

Matrix Matrix::operator/(double b) {
    if (b == 0)
        throw MatrixException("Division by zero!\n");
    for (int i = 0; i < matrix_size; ++i)
        data[i] /= b;
    return *this;
}


void Matrix::print() {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++)
            std::cout << values[row][col] << "  ";
        std::cout << "\n";
    }
    std::cout << "\n";
}


int main() {
    short a = 2;
    short b = 3;
    short y = 4;
    short z = 4;

    Matrix A(a, a, 2);
    A.print();
    Matrix B(b, b, 3);
    B.print();

    try {
        B += A;
    }
    catch(MatrixException &Exception_object) {
        std::cout << Exception_object.getMessage();
    }

    try {
        B *= A;
    }
    catch(MatrixException &Exception_object) {
        std::cout << Exception_object.getMessage();
    }

    try {
        A / 0;
    }
    catch(MatrixException &Exception_object) {
        std::cout << Exception_object.getMessage();
    }



    return 0;
}