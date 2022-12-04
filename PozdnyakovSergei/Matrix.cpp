include <iostream>
#include <cmath>
#include <ctime>
#include <windows.h>

const double tochn = pow(10, -5);

class Matrix {
private:
    unsigned int cols;
    unsigned int rows;
    double* values;

public:
    Matrix(unsigned int cols, unsigned int rows, double*);
    Matrix(unsigned int cols, unsigned int rows);
    Matrix();
    Matrix(const Matrix&);
    ~Matrix();
    Matrix(Matrix&&) noexcept;

    Matrix fill();
    Matrix ZERO();
    Matrix minor();
    Matrix exponent();
    Matrix determinant();
    Matrix transpose();
    Matrix unit_matrix();

    void output();

    Matrix operator+ (const Matrix&);
    Matrix operator- (const Matrix&);
    Matrix operator* (const Matrix&);
    Matrix operator* (const double);
    Matrix operator/ (const double);

    Matrix& operator=(Matrix&&) noexcept;
    Matrix& operator=(const Matrix&);
    Matrix& operator+=(const Matrix&);
    Matrix& operator-=(const Matrix&);
    Matrix& operator*=(const Matrix&);
    Matrix& operator*=(const double);
    Matrix& operator/=(double);

    bool operator!=(const Matrix& mat);
    bool operator==(const Matrix& mat);
    friend std::ostream& operator<<(std::ostream& out, Matrix m);

};

Matrix Matrix::fill() {
    for (unsigned int number = 0; number < cols * rows; number++) {
        this->values[number] = double(rand()%10);
    }
    return (*this);
}

Matrix Matrix::ZERO() {
    for (unsigned int number = 0; number < this->cols * this->rows; number++) {
        this->values[number] = 0;
    }
    return *this;
}

Matrix Matrix::unit_matrix() {
    ZERO();
    for (unsigned int number = 0; number < this->cols * this->rows; number += this->rows + 1) {
        this->values[number] = 1.0;
    }
    return *this;
}

void Matrix::output() {
    std::cout << *this << std::endl;
}

Matrix Matrix::operator+ (const Matrix& matrix) const {
    Matrix sum(matrix.cols, matrix.rows);
    for (unsigned int number = 0; number < matrix.cols * matrix.rows; number++) {
        sum.values[number] = values[number] + matrix.values[number];
    }
    return sum;
}



int main() {

}
