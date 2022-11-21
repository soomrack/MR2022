#include <iostream>
#include "matrix.h"

Matrix::Matrix(const unsigned int cols_m, const unsigned int rows_m){  // Инициализация матрицы
        cols = cols_m;
        rows = rows_m;
        values = new double[cols * rows];
        for (unsigned int idx = 0; idx < cols * rows; idx++){
            values[idx] = 0.0;
        }
}

Matrix::Matrix(const Matrix &A) {  // Конструктор копирования
    rows = A.rows;
    cols = A.cols;
    values = new double[rows * cols];
    for (unsigned int idx = 0; idx < rows * cols; idx++) {
        values[idx] = A.values[idx];
    }
}

Matrix::Matrix(Matrix&& A) {  // Конструктор переноса
    rows = A.rows;
    cols = A.cols;
    values = A.values;
    A.values = nullptr;
}

Matrix::~Matrix() {  // Деструктор
    delete[] values;
}

Matrix Matrix::data_input(Matrix *matrix, const double arr[]){  // Заполнение матрицы данными массива
        for (unsigned int idx = 0; idx < matrix->cols * matrix->rows; idx++){
            matrix->values[idx] = arr[idx];
        }
        return *matrix;
}

void Matrix::print_matrix(const Matrix& X) {  // Вывод матрицы на экран
    std::cout << "Matrix\n";
    for (unsigned int row = 0; row < X.rows; row++) {
        for (unsigned int col = 0; col < X.cols; col++) {
            std::cout << X.values[row * X.cols + col] << "\t";
        }
        std::cout << "\n";
    }
}

void Matrix::print_matrix(const Matrix& matrix, char symbol){  // Вывод матрицы на экран
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
            std::cout << matrix.values[row * matrix.cols + col] << "\t";
        }
        std::cout << "\n";
    }
}

Matrix::Matrix(unsigned int cols_m) {  // Конструктор единичной матрицы
    cols = cols_m;
    rows = cols_m;
    values = new double[cols * rows];
    // delete[] matrix.values;
    for (unsigned int row = 0; row < rows; row++) {
        for (unsigned int col = 0; col < cols; col++) {
            values[row * cols + col] = (row == col) ? 1 : 0;

        }
    }
}

Matrix Matrix::error(){
    Matrix error(0,0);
    error.values = nullptr;
    return error;
}

Matrix Matrix::operator+ (const Matrix& X) const { // Перегрузка оператора сложения
    Matrix sum(X.cols, X.rows);
    for (unsigned int idx = 0; idx < X.cols * X.rows; idx++) {
      sum.values[idx] = values[idx] + X.values[idx];
    }
    return sum;
}

Matrix Matrix::operator- (const Matrix& X) const { // Перегрузка оператора вычитания
    Matrix sub(X.cols, X.rows);
    for (unsigned int idx = 0; idx < X.cols * X.rows; idx++) {
        sub.values[idx] = values[idx] - X.values[idx];
    }
    return sub;
}

Matrix Matrix::operator* (const Matrix& X) const { // Перегрузка оператора умножения
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

Matrix Matrix::operator= (Matrix&& X)  { // Перегрузка оператора присваивания
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

Matrix Matrix::operator= (Matrix& X)  { // Перегрузка оператора присваивания
    if (this == &X) {
    return *this;
    }
    rows = X.rows;
    cols = X.cols;
    delete[]values;
    values = new double [cols * rows];
    memcpy(values, X.values, rows * cols * sizeof(double));
    return *this;
}

Matrix Matrix::operator^ (double X) const { // Перегрузка оператора ^(возведение матрицы в степень)
    Matrix power(*this);
    if (X == 0.0) {
        Matrix one(rows);
        return one;
    }
    if (X == 1.0) {
        return power;
    }
    else {
       const Matrix &start(power);
       Matrix power1(power.cols);
        for (unsigned int idx = 0; idx < X; idx++) {
            power1 = power1 * start;
        }
        power = power1;
        return power;
    }
}

Matrix Matrix::operator/ (const double X) const { // Перегрузка оператора деления(на числа)
    Matrix divide(cols, rows);
    for (unsigned int idx = 0; idx < rows * cols; idx++) {
                divide.values[idx] = values[idx] / X;
            }
    return divide;
}

Matrix Matrix::exp(const Matrix& A){ // Матричная экспонента
    Matrix one(A.cols);
    Matrix exp = one + A;
    double factorial = 1;
    for (int n = 2; n < 11; n++) {
        factorial *= n;
        exp = exp + (A ^ n) / factorial;
    }
    return exp;
}

void Matrix::fill_with(double Number) {
    for(unsigned int idx = 0; idx < cols * rows; idx++){
        values[idx] = Number;
    }

}

bool Matrix::is_equal(const Matrix& X){
    bool equalness;
    if ((rows == X.rows)&&(cols == X.cols)){
        for (unsigned int idx = 0; idx < cols * rows; idx++){
            if(values[idx] == X.values[idx]){
                equalness = true;
            }
            else {
                equalness = false;
            }
        }
    }
    else{
        equalness = false;
    }
    return equalness;
}

int main() {

    // Создание матриц
    Matrix A(3,3);
    double arr_A[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    Matrix::data_input(&A,arr_A);
    Matrix B(3,3);
    double arr_B[] = {9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0};
    Matrix::data_input(&B,arr_B);
    // Блок вычислений
    Matrix Sum = A + B;
    Matrix Sub = A - B;
    Matrix Mult = A * B;
    Matrix exp = Matrix::exp(A);
    // Блок вывода
    Matrix::print_matrix(A);
    Matrix::print_matrix(B);
    Matrix::print_matrix(Sum,'+');
    Matrix::print_matrix(Sub,'-');
    Matrix::print_matrix(Mult,'*');
    Matrix::print_matrix(exp,'e');
    return 0;
}