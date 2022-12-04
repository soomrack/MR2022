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
    Matrix(const unsigned int r);  // square matrix
    Matrix(const unsigned int row, const unsigned int col);  // rectangle matrix
    ~Matrix();  // destructor

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
    Matrix minor(const unsigned int row, const unsigned int col);

    void set_values(const unsigned int l, const double* array);
    void set_random(const unsigned int range = 21);
    void output(bool f = false);

    friend Matrix exponent(const Matrix m, const unsigned int e);
    friend Matrix power(const Matrix m, const unsigned int n);
    friend bool operator==(const Matrix &m1, const Matrix &m2);
};

int main() {
    return 0;
}