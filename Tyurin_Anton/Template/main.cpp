#include <iostream>
#include "Matrix.h"
#include "Matrix_test.h"
#include <cmath>
#include "Matrix_exception.h"

MatrixException WRONG_SIZES("Размеры некорректны для вычисления");
MatrixException MEMORY_DIDNOT_ALLOCATED("Память не выделилась");
MatrixException DIVIDE_BY_ZERO("Деление на ноль");

template <typename T>
Matrix<T>::Matrix(const unsigned int cols_m, const unsigned int rows_m){  // Инициализация матрицы
    cols = cols_m;
    rows = rows_m;
    values = new double[cols * rows];
    for (unsigned int idx = 0; idx < cols * rows; idx++){
        values[idx] = 0.0;
    }
}

template <typename T>
Matrix<T>::Matrix(const Matrix &A) {  // Конструктор копирования
    rows = A.rows;
    cols = A.cols;
    values = new double[rows * cols];
    if (A.values != nullptr) {
        if (values == nullptr) {
            throw MEMORY_DIDNOT_ALLOCATED;
        }
    }
    for (unsigned int idx = 0; idx < rows * cols; idx++) {
        values[idx] = A.values[idx];
    }
}

template <typename T>
Matrix<T>::Matrix(Matrix&& A)  noexcept {  // Конструктор переноса
    rows = A.rows;
    cols = A.cols;
    values = A.values;
    A.values = nullptr;
}

template <typename T>
Matrix<T>::~Matrix() {  // Деструктор
    delete[] values;
}

template <typename T>
Matrix<T> Matrix<T>::data_input(Matrix *matrix, const double arr[]){  // Заполнение матрицы данными массива
    for (unsigned int idx = 0; idx < matrix->cols * matrix->rows; idx++) {
        matrix->values[idx] = arr[idx];
    }
    return *matrix;
}

template <typename T>
void Matrix<T>::print_matrix(const Matrix& X) {  // Вывод матрицы на экран
    std::cout << "Matrix\n";
    for (unsigned int row = 0; row < X.rows; row++) {
        for (unsigned int col = 0; col < X.cols; col++) {
            std::cout << X.values[row * X.cols + col] << "\t";
        }
        std::cout << "\n";
    }
}

template <typename T>
void Matrix<T>::print_matrix(const Matrix& matrix, char symbol){  // Вывод матрицы на экран
    std::cout << "Matrix";
    switch(symbol){
        case '+': std::cout << "\tsumm\n"; break;
        case '-': std::cout << "\tsubstruction\n"; break;
        case '*': std::cout << "\tmultiplication\n"; break;
        case 'e': std::cout << "\texponent\n"; break;
        default:;
    }
    for (unsigned int row = 0; row < matrix.rows; row++) {
        for (unsigned int col = 0; col < matrix.cols; col++) {
            std::cout << round(matrix.values[row * matrix.cols + col] * 1000) / 1000 << "\t";
        }
        std::cout << "\n";
    }
}

template <typename T>
Matrix<T>::Matrix(unsigned int cols_m) {  // Конструктор единичной матрицы
    cols = cols_m;
    rows = cols_m;
    values = new double[cols * rows];
    // delete[] matrix.values;
    for (unsigned int row = 0; row < rows; row++) {
        for (unsigned int col = 0; col < cols; col++) {
            values[row * cols + col] = (row == col) ? 1.0 : 0.0;

        }
    }
}

template <typename T>
Matrix<T> Matrix<T>::operator+ (const Matrix& X) const { // Перегрузка оператора сложения
    if((cols != X.cols) && (rows != X.rows)){
        throw WRONG_SIZES;
    }
    Matrix sum(X.cols, X.rows);
    for (unsigned int idx = 0; idx < X.cols * X.rows; idx++) {
        sum.values[idx] = values[idx] + X.values[idx];
    }
    return sum;
}

template <typename T>
Matrix<T> Matrix<T>::operator- (const Matrix& X) const { // Перегрузка оператора вычитания
    if((cols != X.cols) && (rows != X.rows)){
        throw WRONG_SIZES;
    }
    Matrix sub(X.cols, X.rows);
    for (unsigned int idx = 0; idx < X.cols * X.rows; idx++) {
        sub.values[idx] = values[idx] - X.values[idx];
    }
    return sub;
}

template <typename T>
Matrix<T> Matrix<T>::operator* (const Matrix& X) const { // Перегрузка оператора умножения
    if(cols != X.rows){
        throw WRONG_SIZES;
    }
    Matrix mult(X.cols, X.rows);
    for (unsigned int row = 0; row < rows; row++) {
        for (unsigned int col = 0; col < X.cols; col++) {
            mult.values[row * mult.rows + col] = 0;
            for (unsigned int k = 0; k < cols; k++) {
                mult.values[row * mult.cols + col] += values[row * cols + k] * X.values[k * X.cols + col];
            }
        }
    }
    return mult;
}

template <typename T>
Matrix<T> Matrix<T>::operator= (Matrix&& X) noexcept { // Перегрузка оператора присваивания
    if (this == &X) {
        return *this;
    }
    rows = X.rows;
    cols = X.cols;
    delete[]values;
    values = X.values;
    X.values = nullptr;
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator= (Matrix& X)  { // Перегрузка оператора присваивания
    if (this == &X) {
        return *this;
    }
    rows = X.rows;
    cols = X.cols;
    delete[]values;
    values = new double [cols * rows];
    if(values == nullptr){
        throw MEMORY_DIDNOT_ALLOCATED;
    }
    memcpy(values, X.values, rows * cols * sizeof(double));
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator^ (double X) const { // Перегрузка оператора ^(возведение матрицы в степень)
    Matrix power(*this);
    if (X == 0.0) {
        Matrix one(rows);
        return one;
    }
    if (X == 1.0) {
        return power;
    }
    const Matrix &start(power);
    Matrix power1(power.cols);
    for (unsigned int idx = 0; idx < X; idx++) {
        power1 = power1 * start;
    }
    power = power1;
    return power;
}

template <typename T>
Matrix<T> Matrix<T>::operator/ (const double X) const { // Перегрузка оператора деления(на числа)
    if(abs(X) < PRECISION){
        throw DIVIDE_BY_ZERO;
    }
    Matrix divide(cols, rows);
    for (unsigned int idx = 0; idx < rows * cols; idx++) {
        divide.values[idx] = values[idx] / X;
    }
    return divide;
}

template <typename T>
Matrix<T> Matrix<T>::exp(const Matrix& A){ // Матричная экспонента
    Matrix one(A.cols);
    Matrix exp = one + A;
    double factorial = 1;
    for (int n = 2; n < 11; n++) {
        factorial *= n;
        exp = exp + (A ^ n) / factorial;
    }
    return exp;
}

template <typename T>
void Matrix<T>::fill_with(double Number) {
    for(unsigned int idx = 0; idx < cols * rows; idx++){
        values[idx] = Number;
    }
}

template <typename T>
void Matrix<T>::is_equal(const Matrix& X) {
    int error = 0;
    if ((rows == X.rows) && (cols == X.cols)) {
        for (unsigned int idx = 0; idx < cols * rows; idx++) {
            if (abs(values[idx] - X.values[idx]) > PRECISION) {
                error++;
            }
        }
    }
    if (error != 0){
        std::cout << "Calculation error" << std::endl;
    }
}

int main() {
    // Создание матриц
    Matrix A(3, 3);
    double arr_A[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    Matrix::data_input(&A, arr_A);
    Matrix B(3, 3);
    double arr_B[] = {9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0};
    Matrix<T>::data_input(&B, arr_B);
    // Тест вычислений
    Matrix_test::test();
    // Блок вычислений
    Matrix Sum = A + B;
    Matrix Sub = A - B;
    Matrix Mult = A * B;
    Matrix exp = Matrix::exp(A);
    // Блок вывода
    Matrix::print_matrix(A);
    Matrix::print_matrix(B);
    Matrix::print_matrix(Sum, '+');
    Matrix::print_matrix(Sub, '-');
    Matrix::print_matrix(Mult, '*');
    Matrix::print_matrix(exp, 'e');
    return 0;
}