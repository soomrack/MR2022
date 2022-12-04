
// Created by delta on 30.10.2022.

#ifndef UNTITLED4_MATRIX_H
#define UNTITLED4_MATRIX_H
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <exception>
using namespace std;
// Template для float и double


class Matrix {
private:
    unsigned int rows;
    unsigned int cols;
    double *values;
public:
    //конструкторы
    Matrix(); //создаёт пустую матрицу размера 0 x 0
    Matrix(unsigned int rows, unsigned int cols); //выделяет память, элементы не инициализирует
    Matrix(const Matrix &other); //создаёт матрицу тех же размеров и копирует в неё данные из other
    ~Matrix(); //освобождает память, выделенную под матрицу, если она не пустая
    Matrix one_number(double n);
    Matrix i_number(); //заполнение матрицы значениями от 1 до n
    Matrix rand_number(int min, int bar);
    void output();
    Matrix zero(unsigned int rows, unsigned int cols);
    Matrix single(unsigned int rows, unsigned int cols);
    bool is_equal(const Matrix &other);
    bool is_multiply(const Matrix &other);
    bool is_determinant(const Matrix);
    Matrix operator+(const Matrix &other);
    Matrix operator-(const Matrix &other);
    Matrix operator*(double num);
    Matrix operator*(const Matrix &other);
    Matrix operator/(double num);
    Matrix& operator=(const Matrix &other);
    double get(int i, int j) const;
    Matrix transpose();
    Matrix Minor(const Matrix matrix, const unsigned int size, const unsigned int row, const unsigned int col);
    double determinant(const Matrix matrix, unsigned int);
    friend std::ostream& operator<<(std::ostream& out, Matrix matrix);
    Matrix from_array(double* array);
    Matrix(Matrix&& mat) noexcept; //конструктор переноса
    Matrix& operator=(Matrix&& matrix) noexcept; //оператор переноса
};



class Matrix_Exception : public domain_error //в clion написана библиотека, где вместо exception используется domain_error
{
public:
    Matrix_Exception(const char* const msg): domain_error(msg) {}
};




#endif //UNTITLED4_MATRIX_H
