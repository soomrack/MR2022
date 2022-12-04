#include <iostream>
#include <algorithm>
#include <iomanip>
#include <math.h>


const double EPS_CONST = pow(10, -5);


class Matrix {
private:
    unsigned int rows;
    unsigned int cols;
    double *value;

public:
    Matrix();  //
    Matrix(const Matrix& m);  // copy
    Matrix(const unsigned int n);  // square matrix
    Matrix(const unsigned int row, const unsigned int col);  // rectangle matrix
    ~Matrix();  // destructor
    Matrix(Matrix&& m);

    Matrix& operator= (const Matrix &m);
    Matrix& operator+= (const Matrix &m);
    Matrix& operator-= (const Matrix &m);
    Matrix& operator*= (const Matrix &m);
    Matrix& operator*= (const double num);

    void zero_matrix();  // нулевая матрица
    void unit_matrix();  // едничная матрица
    void mult_bu_num(const double num);  // умножение на число
    void transponation();  // траспонирование
    void determinant();  // определитель
    void invert();  // обратная матрица
    void power(const unsigned int n);  // возведение матрицы в степень
    void exponent(const unsigned int e = 5);  // матричная экспонента
    Matrix minor(const unsigned int r, const unsigned int c);

    void set_values(const unsigned int l, const double* array);
    void set_random(const unsigned int range = 21);
    void output(bool f = false);

    friend Matrix exponent(const Matrix m, const unsigned int e);
    friend Matrix power(const Matrix m, const unsigned int n);
    friend bool operator==(const Matrix &m1, const Matrix &m2);
};


/*
добавить exceptions
*/


Matrix operator+ (const Matrix &m1, const Matrix &m2);
Matrix operator- (const Matrix &m1, const Matrix &m2);
Matrix operator* (const double num, const Matrix &m);
Matrix operator* (const Matrix &m1, const Matrix &m2);
Matrix operator* (const Matrix &m, const double num);


Matrix::Matrix() {
    rows = 0;
    cols = 0;
}


Matrix::Matrix(const unsigned int r, const unsigned int c) {
    rows = r;
    cols = c;
    value = new double [rows * cols];
}


Matrix::Matrix(const unsigned int n) {
    rows = n;
    cols = n;
    value = new double [pow(n, 2)];
}


Matrix::Matrix(const Matrix &m) {
    rows = m.rows;
    cols = m.cols;
    int total_num = rows * cols;
    value = new double [total_num];
    for (unsigned int number = 0; number < total_num; number++) {
        value[number] = m.value[number];
    }
}


Matrix::Matrix(Matrix&& m) {
    rows = m.rows;
    cols = m.cols;
    value = m.value;
    m.rows = 0;
    m.cols = 0;
    m.value = nullptr;
}


Matrix& Matrix::operator=(const Matrix &m) {
    rows = m.rows;
    cols = m.cols;
    int total_num = rows * cols;
    this->value = new double [total_num];
    for (unsigned int number = 0; number < total_num; number++) {
        value[number] = m.value[number];
    }
    return *this;
}


Matrix& Matrix::operator+=(const Matrix &m) {
    rows = m.rows;
    cols = m.cols;
    int total_num = rows * cols;
    for (unsigned int number = 0; number < total_num; number++) {
        value[number] = +m.value[number];
    }
    return *this;
}


Matrix& Matrix::operator-=(const Matrix &m) {
    rows = m.rows;
    cols = m.cols;
    int total_num = rows * cols;
    for (unsigned int number = 0; number < total_num; number++) {
        value[number] -= m.value[number];
    }
    return *this;
}


Matrix& Matrix::operator*=(const double num) {
    for (unsigned int number = 0; number < rows * cols; number++){
        value[number] *= num;
    }
}


Matrix& Matrix::operator*=(const Matrix &m) {
    Matrix itog = Matrix(rows, cols);
    itog.zero_matrix();
    for (unsigned int row = 0; row < itog.rows; row++) {
        for (unsigned int col = 0; col < itog.cols; col++) {
            for (unsigned int number = 0; number < m.rows; number++) {
                itog.value[row * itog.cols + col] += value[row * col + number] * m.value[number * m.cols + col];
            }
        }
    }
    *this = itog;
    return *this;
}





Matrix::~Matrix() {
    delete[] value;
}


int main() {
    return 0;
}