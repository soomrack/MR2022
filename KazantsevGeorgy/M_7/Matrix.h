
// Created by delta on 30.10.2022.

#ifndef UNTITLED4_MATRIX_H
#define UNTITLED4_MATRIX_H
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <exception>

using namespace std;
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
    Matrix ite_rant();
    Matrix rand_number(int min, int bar);
    void m_output();
    Matrix zero_matrix(unsigned int rows, unsigned int cols);
    Matrix single_matrix(unsigned int rows, unsigned int cols);
    bool is_matrixequal(const Matrix &other);
    bool can_multiply(const Matrix &other);
    bool can_determinant(const Matrix);
    Matrix operator+(const Matrix &other);
    Matrix operator-(const Matrix &other);
    Matrix operator*(double num);
    Matrix operator*(const Matrix &other);
    Matrix operator/(double num);
    Matrix& operator=(const Matrix &other);
    double get(int i, int j) const;
    Matrix transpose();
    Matrix Minor(const Matrix, const unsigned int, const unsigned int, const unsigned int);
    double determinant(const Matrix, unsigned int);
    friend std::ostream& operator<<(std::ostream& out, Matrix matrix);
    Matrix from_array(double* array);
};


#endif //UNTITLED4_MATRIX_H
