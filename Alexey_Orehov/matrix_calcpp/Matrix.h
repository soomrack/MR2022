#ifndef PROGRAMMING_MATRIX_H
#define PROGRAMMING_MATRIX_H

#include <cmath>
#include <malloc.h>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <malloc.h>

const double EPS = 10e-6;  // Точность при сравнении величин с плавающей точкой


class Matrix{
private:
    double* values;

public:
    unsigned int rows;
    unsigned int cols;

    Matrix();
    Matrix(unsigned int rows, unsigned int cols);
    Matrix(const Matrix&);

    Matrix fill_number(double);                                      // Заполнение созданной матрицы одним числом
    Matrix fill_random(int min_value, int max_value);                // Заполнение созданной матрицы случайно
    Matrix fill_identity();                                          // Преобразование матрицы в единичную
    Matrix fill_from_array(double* array);                           // Заполнение матрицы значениями из массива

    double get(unsigned int, unsigned int);                          // Получение произвольного элемента матрицы
    void set(unsigned int, unsigned int, double);                    // Изменение произвольного элемента матрицы

    bool operator==(const Matrix& mat);
    bool operator!=(const Matrix& mat) {return !(*this == mat);}
    double* operator[](unsigned int row);                            // Доступ к заданной строке матрицы
    bool is_identity();

    Matrix operator+(const Matrix&) const;
    Matrix operator-(const Matrix&) const;

    friend std::ostream& operator<<(std::ostream& os, Matrix& mat){  // Перегрузка << для вывода матрицы через std::cout
        os << "\n";
        for (unsigned int row = 0; row < mat.rows; row++){
            for (unsigned int col = 0; col < mat.cols; col++){
                os << mat.values[col + row * mat.cols] << " ";
            }
            if (row != mat.rows - 1) os << "\n";
        }
        return os;
    }

    explicit operator bool() {  // Определение преобразования матрицы в логический тип
        for (int idx = 0; idx < rows * cols; idx++){
            if (!(bool)values[idx]) return false;
        }
        return true;
    }

    void print() {std::cout << *this << std::endl;}
    ~Matrix(){delete[] this->values;}
};


#endif //PROGRAMMING_MATRIX_H
