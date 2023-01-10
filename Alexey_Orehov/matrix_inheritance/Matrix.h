#ifndef PROGRAMMING_MATRIX_H
#define PROGRAMMING_MATRIX_H

#include <iostream>

const double EPS = 10e-6;  // Точность при сравнении величин с плавающей точкой


class MatrixException: public std::exception {
public:
    MatrixException(const char* msg): std::exception() {}
};


class Matrix {
protected:
    unsigned int rows;
    unsigned int cols;
    double* values;

public:
    Matrix();
    Matrix(unsigned int rows, unsigned int cols);

    Matrix(const Matrix &);
    Matrix(Matrix &&mat) noexcept;

    Matrix set_value(double value);                                  // Заполнение созданной матрицы одним числом
    Matrix set_random(int min_value, int max_value);                 // Заполнение созданной матрицы случайно
    Matrix set_identity();                                           // Преобразование матрицы в единичную
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

    Matrix transpose();
    void swap_rows(unsigned int row1, unsigned int row2);
    unsigned int upper_triangle();
    double det();
    double trace();

    Matrix minor(unsigned int minor_row, unsigned int minor_col);
    Matrix inv();
    Matrix exp();

    friend std::ostream& operator<<(std::ostream &os, Matrix &mat);
    friend std::ostream& operator<<(std::ostream &os, Matrix &&mat);
    friend std::istream& operator>>(std::istream &is, Matrix &mat);

    explicit operator bool() {
        for (unsigned int idx = 0; idx < rows * cols; idx++) {
            if (!(bool) values[idx]) return false;
        }
        return true;
    }

    void print() { std::cout << *this << std::endl; }

    ~Matrix() { delete[] this->values; }
};


class MatrixMemory : public Matrix {
private:
    unsigned long int memory_size = 0;
    static unsigned long int total_memory;
public:
    MatrixMemory() { memory_size = 0; }
    MatrixMemory(unsigned int rows, unsigned int cols) {
        memory_size = rows * cols * sizeof(double);
        total_memory += memory_size;
    }
    MatrixMemory(MatrixMemory&& mat) { memory_size = mat.memory_size; }

    unsigned long int get_total_memory() { return total_memory; }

    ~MatrixMemory() { total_memory -= memory_size; };
};


#endif //PROGRAMMING_MATRIX_H
