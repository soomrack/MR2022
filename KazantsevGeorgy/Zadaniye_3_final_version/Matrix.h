
// Created by delta on 30.10.2022.

#ifndef UNTITLED4_MATRIX_H
#define UNTITLED4_MATRIX_H
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <exception>
using namespace std;
// Template для float и double

static unsigned int memory = 0;

long int total;
template <typename T>
class Matrix {
protected:
    unsigned int rows;
    unsigned int cols;
    T *values;
public:

    //конструкторы
    Matrix();
    Matrix(unsigned int rows, unsigned int cols);
    Matrix(const Matrix &other);

    //деструкторы
    ~Matrix();

    //методы
    Matrix<T> one_number(T n);
    Matrix<T> i_number();
    Matrix<T> rand_number(int min, int bar);
    Matrix from_array(T* array);
    Matrix<T> zero(unsigned int rows, unsigned int cols);
    Matrix<T> single(unsigned int rows, unsigned int cols);
    void fill_certain(const unsigned int len, const T *array);

    Matrix(Matrix&& mat) noexcept; //конструктор переноса

    void transpose();
    void output();
    void exponent(const unsigned int degree);
    void pow(const unsigned int n);
    Matrix Minor(const Matrix<T> matrix, const unsigned int size, const unsigned int row, const unsigned int col);
    double determinant(const Matrix<T> matrix, unsigned int);
    T get(int i, int j) const;

    bool is_equal(const Matrix &other);
    bool is_multiply(const Matrix &other);
    bool is_determinant(const Matrix);

    // операты перегрузки
    bool operator==(const Matrix<T>);
    Matrix operator+(const Matrix<T> &other);
    Matrix operator-(const Matrix<T> &other);
    Matrix operator*(T num);
    Matrix operator*(const Matrix<T> &other);
    Matrix operator/(T num);
    Matrix& operator=(const Matrix<T> &other);
    Matrix& operator=(Matrix<T>&& matrix) noexcept; //оператор переноса
    template <typename R>friend std::ostream& operator<<(std::ostream& out, Matrix<R> matrix); //для оператора вывода необходимо использовать другой шаблон
};

class Matrix_Exception : public domain_error //в clion написана библиотека, где вместо exception используется domain_error
{
public:
    Matrix_Exception(const char* const msg): domain_error(msg) {}
};

#endif //UNTITLED4_MATRIX_H
