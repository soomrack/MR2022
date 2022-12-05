
// Created by delta on 30.10.2022.

#ifndef UNTITLED4_MATRIX_H
#define UNTITLED4_MATRIX_H
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <exception>
using namespace std;
// Template для float и double

template <typename T>
class Matrix {
private:
    unsigned int rows;
    unsigned int cols;
    T *values;
public:
    //конструкторы
    Matrix(); //создаёт пустую матрицу размера 0 x 0
    Matrix(unsigned int rows, unsigned int cols); //выделяет память, элементы не инициализирует
    Matrix(const Matrix &other); //создаёт матрицу тех же размеров и копирует в неё данные из other
    ~Matrix(); //освобождает память, выделенную под матрицу, если она не пустая

    //методы
    Matrix<T> one_number(T n);
    Matrix<T> i_number(); //заполнение матрицы значениями от 1 до n
    Matrix<T> rand_number(int min, int bar);
    Matrix(Matrix&& mat) noexcept; //конструктор переноса
    Matrix from_array(T* array);
    void output();
    Matrix<T> zero(unsigned int rows, unsigned int cols);
    Matrix<T> single(unsigned int rows, unsigned int cols);
    bool is_equal(const Matrix &other);
    bool is_multiply(const Matrix &other);
    bool is_determinant(const Matrix);
    // операты перегрузки
    Matrix operator+(const Matrix<T> &other);
    Matrix operator-(const Matrix<T> &other);
    Matrix operator*(T num);
    Matrix operator*(const Matrix<T> &other);
    Matrix operator/(T num);
    Matrix& operator=(const Matrix<T> &other);
    Matrix& operator=(Matrix<T>&& matrix) noexcept; //оператор переноса
    friend std::ostream& operator<<(std::ostream& out, Matrix<T> matrix);
    //
    T get(int i, int j) const;
    Matrix transpose();
    Matrix Minor(const Matrix<T> matrix, const unsigned int size, const unsigned int row, const unsigned int col);
    double determinant(const Matrix<T> matrix, unsigned int);




};



class Matrix_Exception : public domain_error //в clion написана библиотека, где вместо exception используется domain_error
{
public:
    Matrix_Exception(const char* const msg): domain_error(msg) {}
};




#endif //UNTITLED4_MATRIX_H
