#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <windows.h>
#include <cmath>

const double EPS = 0.000001;

class Matrix_Exception : public std::exception
{
public:
    Matrix_Exception(const char* const& msg) : exception(msg)
    {}
};

Matrix_Exception NOT_SQUARE("Make matrix square\n");
Matrix_Exception SIZE_ERROR("Change a size\n");
Matrix_Exception DIVISION_ERROR("Can't divide by zero\n");

class Matrix {
private:
    unsigned int cols;
    unsigned int rows;
    double* values;

public:
    Matrix();
    Matrix(unsigned int col, unsigned int row);
    Matrix(unsigned int col);
    Matrix(const Matrix& matrix);
    Matrix(Matrix&& matrix);
    ~Matrix();

    void output();
    void set_rand_values(int max_value);

    Matrix operator+(const Matrix& matrix) const;
    Matrix operator-(const Matrix& matrix) const;
    Matrix operator*(const Matrix& matrix) const;
    Matrix operator*(double number) const;
    Matrix operator=(Matrix& matrix);
    Matrix operator=(Matrix&& matrix);
    Matrix operator^(const int number) const;
    Matrix operator/(const double number) const;

    static Matrix  exp(const Matrix& A, const unsigned int accuracy);
    Matrix minor(const Matrix, const unsigned int, const unsigned int, const unsigned int);
    Matrix transpose();
    double determinant(const Matrix, unsigned int);

};


Matrix::~Matrix() {
    if (values != nullptr)
        delete[] values;
}


Matrix::Matrix() {
    cols = 0;
    rows = 0;
    values = nullptr;
}


Matrix::Matrix(unsigned int col, unsigned int row) {
    cols = col;
    rows = row;
    unsigned int n_values = cols * rows;
    values = new double[cols * rows];
    
}


Matrix::Matrix(const Matrix& matrix) {
    cols = matrix.cols;
    rows = matrix.rows;
    values = new double[rows * cols];
    memcpy(values, matrix.values, rows * cols * sizeof(double));
}


Matrix::Matrix(Matrix&& matrix) {
    cols = matrix.cols;
    rows = matrix.rows;
    values = matrix.values;
    matrix.values = nullptr;
}


void Matrix::output() {
    for (unsigned int row = 0; row < rows; ++row) {
        for (unsigned int col = 0; col < cols; ++col) {
            std::cout << values[row * cols + col] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}


void Matrix::set_rand_values(int max_value = 10) {
    for (unsigned int index = 0; index < rows * cols; ++index) {
        values[index] = rand() % max_value;
    }
}


Matrix::Matrix(unsigned int col) {
    cols = col;
    rows = col;
    values = new double[cols * rows];
    for (unsigned int row = 0; row < rows; row++) {
        for (unsigned int col = 0; col < cols; col++) {
            values[row * cols + col] = (row == col) ? 1.0 : 0.0;

        }
    }
}


double Matrix::determinant(const Matrix matrix, unsigned int size)
{
    if (matrix.rows != matrix.cols) throw NOT_SQUARE;
    double det = 0;
    int k = 1;
    if (size == 0)
        return 0;
    if (size == 1)
        return matrix.values[0];
    if (size == 2) {
        return (matrix.values[0] * matrix.values[3] - matrix.values[2] * matrix.values[1]);
    }
    for (unsigned int idx = 0; idx < size; idx++) {
        det += k * matrix.values[idx] * determinant(minor(matrix, size, 0, idx), size - 1);
        k = -k;
    }
    return det;
}


Matrix Matrix::operator+ (const Matrix& matrix) const {
    if (rows != matrix.rows) throw SIZE_ERROR;
    Matrix result(matrix);
    for (unsigned int idx = 0; idx < matrix.cols * matrix.rows; idx++) {
        result.values[idx] += values[idx];
    }
    return result;
}


Matrix Matrix::operator- (const Matrix& matrix) const {
    if (rows != matrix.rows) throw SIZE_ERROR;
    Matrix result(matrix);
    for (unsigned int idx = 0; idx < matrix.cols * matrix.rows; idx++) {
        result.values[idx] -= values[idx];
    }
    return result;
}


Matrix Matrix::operator* (const Matrix& matrix) const {
    if (rows != matrix.rows) throw SIZE_ERROR;
    Matrix result(matrix);
    for (unsigned int row = 0; row < result.rows; row++) {
        for (unsigned int col = 0; col < result.cols; col++) {
            result.values[row * result.rows + col] = 0.00;
            for (unsigned int k = 0; k < result.cols; k++) {
                result.values[row * result.cols + col] += values[row * cols + k] * matrix.values[k * result.cols + col];
            }
        }
    }
    return result;
}


Matrix Matrix::operator* (const double coefficient) const {
    Matrix result(cols, rows);
    for (unsigned int idx = 0; idx < rows * cols; idx++) {
        result.values[idx] = values[idx] * coefficient;
    }
    return result;
}


Matrix Matrix::operator= (Matrix& matrix) {
    if (this == &matrix) {
        return *this;
    }
    rows = matrix.rows;
    cols = matrix.cols;
    delete[]values;
    values = new double[cols * rows];
    memcpy(values, matrix.values, rows * cols * sizeof(double));
    return *this;
}


Matrix Matrix::operator= (Matrix&& matrix) {
    if (this == &matrix) {
        return *this;
    }
    rows = matrix.rows;
    cols = matrix.cols;
    delete[]values;
    values = matrix.values;
    matrix.values = nullptr;
    return *this;
}


Matrix Matrix::operator^(int number) const {
    if (cols != rows) throw NOT_SQUARE;
    Matrix result(*this);
    if (number == 0) {
        Matrix matrix(cols);
        return matrix;
    }
    if (number == 1) {
        return result;
    }
    const Matrix& start(result);
    for (int idx = 0; idx < number; idx++) {
        result = result * start;
    }
    return result;
}


Matrix Matrix::operator/(const double number) const {
    if (number == 0) throw DIVISION_ERROR;
    Matrix result(cols, rows);
    for (unsigned int idx = 0; idx < rows * cols; ++idx) {
        result.values[idx] = values[idx] / number;
    }
    return result;
}


Matrix Matrix::exp(const Matrix& A, unsigned int accuracy = 30) {
    if (A.rows != A.cols) throw NOT_SQUARE;
    Matrix result(A.cols);
    Matrix temp(A.cols);
    double factorial = 1.0;
    for (unsigned int step = 1; step < accuracy; step++) {
        factorial *= step;
        temp = temp * A;
        result = result + temp / factorial;
    }
    return result;
}


Matrix Matrix::minor(const Matrix matrix, const unsigned int size, const unsigned int row, const unsigned int col)
{
    Matrix minor(size - 1, size - 1);
    unsigned int shiftrow = 0; 
    unsigned int shiftcol; 
    for (unsigned int rows = 0; rows < size - 1; rows++) {
        
        if (rows == row) { shiftrow = 1; }
        
        shiftcol = 0; 
        for (unsigned int cols = 0; cols < size - 1; cols++) {
            if (cols == col) { shiftcol = 1; }
            minor.values[rows * (size - 1) + cols] = matrix.values[(rows + shiftrow)
                * size + (cols + shiftcol)];
        }
    }
    return minor;
}


Matrix Matrix::transpose() {
    Matrix result = { cols, rows };
    for (unsigned int row = 0; row < result.rows; row++) {
        for (unsigned int col = 0; col < result.cols; col++) {
            result.values[row * result.cols + col] = values[col * result.cols + row];
        }
    }
    return result;
}


void main() {
    Matrix matrix1(3, 3);
    matrix1.set_rand_values();
    matrix1.output();
    Matrix matrix2(3, 3);
    matrix2.set_rand_values();
    matrix2.output();
    Matrix sum = matrix1 + matrix2;
    sum.output();
    Matrix sub = matrix1 - matrix2;
    sub.output();
    Matrix mult = matrix1 * matrix2;
    mult.output();
    Matrix mult_number = matrix1 * 2;
    mult_number.output();
    Matrix pow = matrix1 ^ 2;
    pow.output();
    Matrix exp = Matrix::exp(matrix1);
    exp.output();
}