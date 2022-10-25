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

//    TODO: Аттрибуты класса могут содержать в себе определенные значения матрицы,
//     которые можно вызывать, не пересчитывая
//    bool redacted = true;
//    double* inv_values = nullptr;
//    double det = NAN;

    Matrix(unsigned int, unsigned int, double*);

public:
    unsigned int rows;
    unsigned int cols;

    // Базовый конструктор, создает матрицу m строк и n столбцов и заполняет каждую ячейку default_value
    Matrix(unsigned int m, unsigned int n, double default_value = NAN);
    static Matrix null() {return {0, 0, nullptr};}               // Пустая матрица
    Matrix copy();                                               // Возвращает копию данной матрицы

    double get(unsigned int, unsigned int);                      // Доступ к произвольному элементу матрицы
    void set(unsigned int, unsigned int, double);                // Изменение произвольного элемента матрицы

    Matrix fill_random(int min_value, int max_value);            // Заполняет созданную матрицу случайными значениями
    Matrix fill_identity();                                      // Делает матрицу единичной
    Matrix fill_from_array(double* array);                       // Заполняет матрицу значениями из заданного массива

    Matrix add(Matrix);                                          // Сложение матриц

    bool operator==(Matrix mat);

    double* operator[](unsigned int idx);
    Matrix operator+(const Matrix& mat) {return this->add(mat);}

    explicit operator bool() {                                   // Определение преобразования матрицы в логический тип
        for (int idx = 0; idx < rows * cols; idx++){
            if (!(bool)values[idx]) return false;
        }
        return true;
    }

    bool is_identity();
    void print();
};


void printm(Matrix mat);

#endif //PROGRAMMING_MATRIX_H
