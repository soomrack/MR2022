#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cstring>




class Matrix {
private:
    unsigned int cols;
    unsigned int rows;
    double* values;

public:
    Matrix();  // Конструктор пустой матрицы
    Matrix(unsigned int col, unsigned int row);  // Конструктор прямоугольной матрицы
    Matrix(unsigned int col);  // Конструктор единичной матрицы
    Matrix(const Matrix& matrix);  // Конструктор копирования матрицы
    Matrix(Matrix&& matrix);  // Конструктор переноса матрицы
    ~Matrix();  // Деструктор


    void print_matrix();
    void set_values(int max_value);

    Matrix operator+(const Matrix& one) const;
    Matrix operator-(const Matrix& one) const;
    Matrix operator*(const Matrix& one) const;
    Matrix operator*(double coefficient) const;
    Matrix operator=(Matrix& one);
    Matrix operator=(Matrix&& one);
    Matrix operator^(const int coefficient) const;
    Matrix operator/(const double coefficient) const;
    static Matrix  exp_m(const Matrix& one, const unsigned int accuracy);
    Matrix minor(Matrix& A, unsigned int row, unsigned int col);
    Matrix transpose();


};


class Matrix_Exception : public std::domain_error
{
public:
    Matrix_Exception(const char* const message) : std::domain_error(message)
    {}
};


Matrix_Exception NotSquare("The matrix should be square\n");
Matrix_Exception WrongSize("The matrix should have another size\n");
Matrix_Exception MemoryError("Memory has not been allocated\n");
Matrix_Exception DivisionError ("Can't divide by zero\n")

Matrix::Matrix() {
    cols = 0;
    rows = 0;
}


Matrix::Matrix(unsigned int col, unsigned int row) {
    cols = col;
    rows = row;
    unsigned int n_values = cols * rows;
    values = new double[cols*rows];
    for (unsigned int idx = 0; idx < n_values; ++idx) {
        values[idx] = 0.0;
    }
}


Matrix::Matrix(const Matrix& matrix) {
    cols = matrix.cols;
    rows = matrix.rows;
    values = new double[rows * cols];
    if (!values) throw MemoryError;
    memcpy(values,matrix.values,rows * cols * sizeof(double));
}


Matrix::Matrix(Matrix&& matrix) {
    cols = matrix.cols;
    rows = matrix.rows;
    values = matrix.values;
    matrix.values = nullptr;
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


void Matrix::set_values(int max_value = 10) {
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


Matrix Matrix::operator+ (const Matrix& One) const {
    if (rows != One.rows) throw WrongSize;
    Matrix res(One);
    for (unsigned int idx = 0; idx < One.cols * One.rows; idx++) {
        res.values[idx] += values[idx];
    }
    return res;
}


Matrix Matrix::operator- (const Matrix& One) const {
    if (rows != One.rows) throw WrongSize;
    Matrix Res(One);
    for (unsigned int idx = 0; idx < One.cols * One.rows; idx++) {
        Res.values[idx] -= values[idx];
    }
    return Res;
}


Matrix Matrix::operator* (const Matrix& One) const {
    if (rows != One.rows) throw WrongSize;
    Matrix Res(One);
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


Matrix Matrix::operator* (const double coefficient) const {
    Matrix Res(cols, rows);
    for (unsigned int idx = 0; idx < rows * cols; idx++) {
        Res.values[idx] = values[idx] * coefficient;
    }
    return Res;
}



Matrix Matrix::operator= (Matrix& one)  { // Перегрузка оператора присваивания
    if (this == &one) {
        return *this;
    }
    rows = one.rows;
    cols = one.cols;
    delete[]values;
    values = new double [cols * rows];
    memcpy(values, one.values, rows * cols * sizeof(double));
    return *this;
}


Matrix Matrix::operator= (Matrix&& one)  { // Перегрузка оператора присваивания
    if (this == &one) {
        return *this;
    }
    rows = one.rows;
    cols = one.cols;
    delete[]values;
    values = one.values;
    one.values = nullptr;
    return *this;
}


Matrix Matrix::operator^(int coefficient) const { // Возведение матрицы в степень
    if(cols != rows) throw NotSquare;
    Matrix Res(*this);
    if (coefficient == 0) {
        Matrix one(cols);
        return one;
    }
    if (coefficient == 1) {
        return Res;
    }
        const Matrix &start(Res);
        for (unsigned int idx = 0; idx < coefficient; idx++){
            Res = Res * start;
        }
        return Res;
}


Matrix Matrix::operator/(const double coefficient) const {
    if (coefficient == 0) throw DivisionError;
    Matrix Res(cols, rows);
    for(unsigned int idx = 0; idx < rows * cols; ++idx) {
        Res.values[idx] = values[idx]/coefficient;
    }
    return Res;
}


Matrix Matrix::Exp(const Matrix& A, const unsigned int accuracy = 10){ // Матричная экспонента
    if (A.rows != A.cols) throw NotSquare;
    Matrix one(A.cols);
    Matrix Res = one + A;
    double factorial = 1;
    for (int step = 1; step < accuracy; step++) {
        factorial *= step;
        Res = Res + (A ^ step) / factorial;
    }
    return Res;
}


Matrix Matrix::Minor(Matrix& A, unsigned int row, unsigned int col) {
    int new_row = A.rows -1;
    int new_col = A.cols - 1;
    if (row >= A.rows) new_row++;
    if (col >= A.cols) new_col++;

    Matrix Res = Matrix(new_row, new_col);
    unsigned int k = 0;

    for (unsigned int idx = 0; idx < rows * cols; idx++){
        if ((idx % cols == col) or (idx / cols == row)) continue;
        Res.values[k++] = A.values[idx];
    }

    return Res;
}

Matrix Matrix::transpose() {
    Matrix res = {cols, rows};
    for (unsigned int row = 0; row < res.rows; row++) {
        for (unsigned int col = 0; col < res.cols; col++) {
            res.values[row * res.cols + col] = values[col * res.cols + row];
        }
    }
    return res;
}

double Matrix::determinant(const Matrix matrix)
{
    double det = 0;
    int sign = 1;
    if (rows == 0)
        return 0;
    if (rows == 1)
        return matrix.values[0];
    if (rows == 2) {
        return (matrix.values[0] * matrix.values[3] - matrix.values[2] * matrix.values[1]);
    }
    for (unsigned int idx = 0; idx < rows; idx++) {
        det += sign * matrix.values[idx] * determinant(Minor(matrix, 0, idx), rows - 1);
        sign = -sign;
    }
    return det;
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
    Matrix Power = A^2;
    Power.print_matrix();
    Matrix Exponent = Matrix::Exp(A);
    return 0;
}