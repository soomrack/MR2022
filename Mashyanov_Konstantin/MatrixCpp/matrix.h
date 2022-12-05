//
// Created by mashy on 05.12.2022.
//

#include <iostream>

const double EPS = 10e-6;  // Точность при сравнении величин с плавающей точкой


class Matrix {
private:
    unsigned int rows;
    unsigned int cols;
    double* values;

public:
    Matrix();
    Matrix(unsigned int rows, unsigned int cols);
    Matrix(const Matrix &);
    Matrix(Matrix &&mat) noexcept;

    Matrix set_value(double value);                                 // Заполнение созданной матрицы одним числом
    Matrix set_random(int min_value, int max_value);                // Заполнение созданной матрицы случайно
    Matrix set_identity();                                          // Преобразование матрицы в единичную
    Matrix fill_from_array(double* array);                           // Заполнение матрицы значениями из массива

    double get(unsigned int row, unsigned int col);                  // Получение произвольного элемента матрицы
    void set(unsigned int row, unsigned int col, double val);        // Изменение произвольного элемента матрицы

    Matrix& operator=(const Matrix& mat);
    Matrix& operator=(Matrix&& mat) noexcept;
    bool operator==(const Matrix& mat);
    bool operator!=(const Matrix& mat) { return !(*this == mat); }
    double* operator[](unsigned int row);                            // Доступ к заданной строке матрицы
    bool is_identity();
    bool is_diagonal();

    Matrix operator+(const Matrix& mat) const;
    Matrix operator-(const Matrix& mat) const;
    Matrix operator*(double scalar) const;
    Matrix operator*(const Matrix& mat2) const;
    Matrix operator/(double scalar) const;

    void operator+=(const Matrix& mat) { *this = *this + mat; }
    void operator-=(const Matrix& mat) { *this = *this - mat; }
    void operator*=(const Matrix& mat) { *this = *this * mat; }
    void operator*=(double scalar) { *this = *this * scalar; }

    void print();

    ~Matrix() { delete[] this->values; }
};
