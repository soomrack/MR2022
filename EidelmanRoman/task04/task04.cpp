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
    matrix_size = rows * cols;
    data = new double[matrix_size];
    values = new double *[rows];
    if (data == nullptr || values == nullptr) {
        delete[] data;
        delete[] values;
        throw MatrixException("Memory error!");
    }
    for (int row = 0; row < rows; ++row)
        values[row] = data + row * cols;
}

Matrix::Matrix(const Matrix& X) {
    if (this != &X) {
        rows = X.rows;
        cols = X.cols;
        matrix_size = X.matrix_size;
        data = new double[matrix_size];
        values = new double *[rows];
        memcpy(data, X.data,  matrix_size * sizeof(double));
        for (int row = 0; row < rows; ++row)
            values[row] = data + row * cols;

    }
}

Matrix::Matrix(unsigned int input_rows, unsigned int input_cols, double x): Matrix(input_rows, input_cols) {
    for (int i = 0; i < matrix_size; ++i) {
        data[i] = x;
    }
}

Matrix::~Matrix() {
    delete[] data;
    delete[] values;
}

//void Matrix::swap(Matrix& X) {
//    std::swap(matrix_size, X.matrix_size);
//    std::swap(data, X.data);
//    std::swap(values, X.values);
//}

Matrix& Matrix::operator=(const Matrix& X) {
    if (this != &X) {
        rows = X.rows;
        cols = X.cols;
        matrix_size = X.matrix_size;
        data = new double[matrix_size];
        values = new double *[rows];
        memcpy(data, X.data,  matrix_size * sizeof(double));
        for (int row = 0; row < rows; ++row)
            values[row] = data + row * cols;
    }
    return *this;
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

//Matrix& Matrix::operator*=(const Matrix& X) {
//    Matrix zero(rows, cols, 0);
//    for (int row = 0; row < zero.rows; ++row) {
//        for (int col = 0; col < zero.cols; ++col) {
//            for (int k = 0; k < zero.rows; ++k) {
//                zero.values[rows][cols] += values[rows][k] * X.values[k][cols];
//            }
//        }
//    }
//    *this = zero;
//    return *this;
//}

//Matrix Matrix::operator*(const Matrix& X) {
//    Matrix copy = *this;
//    copy *= X;
//    return copy;
//}
//
//Matrix Matrix::operator^(unsigned int b) {
//    for (int i = 1; i < b; ++i)
//        *this *= *this;
//    return *this;
//}

//Matrix Matrix::operator/(double b) {
//    for (int i = 0; i < matrix_size; ++i)
//        data[i] /= b;
//    return *this;
//}
//
//Matrix Matrix::T() {
//    for (int row = 0; rows < rows; ++row) {
//        for (int col = 0; cols < cols; ++col) {
//            values[rows][cols] = values[cols][rows];
//        }
//    }
//    return *this;
//}


void Matrix::print() {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++)
            std::cout << values[row][col] << "  ";
        std::cout << "\n";
    }
    std::cout << "\n";
}

int main() {
    short n = 2;
    short m = 2;

    Matrix A(n, m, 1);
    A.print();
    Matrix B;
    B += A;
    B.print();


//    try {
//        Matrix T(n, m);
//    }
//    catch(MatrixException &Exception_object) {
//        std::cout << Exception_object.getMessage();
//    }



    return 0;
}