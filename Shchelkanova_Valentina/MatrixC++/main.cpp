#include <iostream>
#include <stdlib.h>
#include <math.h>




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
    static Matrix  exp(const Matrix& one, const unsigned int n);
    Matrix Minor(Matrix& A, unsigned int row, unsigned int col);


};

Matrix::Matrix() {
    cols = 0;
    rows = 0;
}


Matrix::Matrix(unsigned int col, unsigned int row) {
    cols = col;
    rows = row;
    unsigned int n_values = cols * rows;
    values = new double[cols*rows]; // (new double[cols*rows] delete[])заменить везде маллок (memcpy(копирование памяти))
    for (unsigned int idx = 0; idx < n_values; ++idx) {
        values[idx] = 0.0;
    }
}


Matrix::Matrix(const Matrix& matrix) {
    cols = matrix.cols;
    rows = matrix.rows;
    values = new double[rows*cols];
    for (unsigned int idx = 0; idx < rows * cols; ++idx) { //сделать копирование память с помощью memcpy
        values[idx] = matrix.values[idx];
    }
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
            values[row * cols + col] = (row == col) ? 1 : 0;

        }
    }
}


Matrix Matrix::operator+ (const Matrix& One) const {
    Matrix res(One);
    for (unsigned int idx = 0; idx < One.cols * One.rows; idx++) {
        res.values[idx] += values[idx];
    }
    return res;
}


Matrix Matrix::operator- (const Matrix& One) const { //Вычитание исправить так же как и сложение
    Matrix Res(One);
    for (unsigned int idx = 0; idx < One.cols * One.rows; idx++) {
        Res.values[idx] -= values[idx];
    }
    return Res;
}


Matrix Matrix::operator* (const Matrix& One) const {
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


Matrix Matrix::operator^(int coefficient) const { // Возведение матрицы в степень Избавиться от лишних переменных
    Matrix Res(*this);
    if (coefficient == 0) {
        Matrix one(cols);
        return one;
    }
    if (coefficient == 1) {
        return Res;
    }
    else {
        const Matrix &start(Res);
        Matrix Res1(Res.cols, Res.rows);
        for (unsigned int idx = 0; idx < coefficient; idx++){
            Res1 = Res1 * start;
        }
        Res = Res1;
        return Res;
    }
}


Matrix Matrix::operator/(const double coefficient) const {
    Matrix Res(cols, rows);
    for(unsigned int idx = 0; idx < rows * cols; ++idx) {
        Res.values[idx] = values[idx]/coefficient;
    }
    return Res;
}


Matrix Matrix::exp(const Matrix& A, const unsigned int n = 10){ // Матричная экспонента  Подумать над эффективностью кода
    Matrix one(A.cols);
    Matrix Res = one + A;
    double factorial = 1;
    for (int step = 2; step < n; step++) {
        factorial *= n;
        Res = Res + (A ^ n) / factorial;
    }
    return Res;
}


Matrix Matrix::Minor(Matrix& A, unsigned int row, unsigned int col) { //лучше через двойной цикл
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
    Matrix Exponent = Matrix::exp(A);
    return 0;
}