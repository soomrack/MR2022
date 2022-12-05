#include <iostream>
#include <algorithm>
#include <math.h>


const double EPS_CONST = pow(10, -5);


class Matrix {
private:
    unsigned int rows;
    unsigned int cols;
    double *value;

public:
    Matrix();  //
    Matrix(const Matrix& m);  // copy
    Matrix(const unsigned int n);  // square matrix
    Matrix(const unsigned int row, const unsigned int col);  // rectangle matrix
    ~Matrix();  // destructor
    Matrix(Matrix&& m);

    Matrix& operator= (const Matrix &m);
    Matrix& operator+= (const Matrix &m);
    Matrix& operator-= (const Matrix &m);
    Matrix& operator*= (const Matrix &m);
    Matrix& operator*= (const double num);

    void zero_matrix();  // нулевая матрица
    void unit_matrix();  // едничная матрица
    void mult_by_num(const double num);  // умножение на число
    void transposition();  // траспонирование
    double determinant(const Matrix, unsigned int);  // определитель
    void invert();  // обратная матрица
    void power(const unsigned int n);  // возведение матрицы в степень
    void exponent(const unsigned int e = 5);  // матричная экспонента
    Matrix minor(const Matrix, const unsigned int size, const unsigned int r, const unsigned int c);

    void set_values(const unsigned int l, const double* array);
    void set_random(const unsigned int range = 21);
    void output(bool f = false);

    friend Matrix exponent(const Matrix m, const unsigned int e);
    friend Matrix power(const Matrix m, const unsigned int n);
    friend bool operator==(const Matrix &m1, const Matrix &m2);
};


/*
добавить exceptions
*/


Matrix operator+ (const Matrix &m1, const Matrix &m2);
Matrix operator- (const Matrix &m1, const Matrix &m2);
Matrix operator* (const double num, const Matrix &m);
Matrix operator* (const Matrix &m1, const Matrix &m2);
Matrix operator* (const Matrix &m, const double num);


Matrix::Matrix() {
    rows = 0;
    cols = 0;
}


Matrix::Matrix(const unsigned int r, const unsigned int c) {
    rows = r;
    cols = c;
    value = new double [rows * cols];
}


Matrix::Matrix(const unsigned int n) {
    rows = n;
    cols = n;
    value = new double [pow(n, 2)];
}


Matrix::Matrix(const Matrix &m) {
    rows = m.rows;
    cols = m.cols;
    int total_num = rows * cols;
    value = new double [total_num];
    for (unsigned int number = 0; number < total_num; number++) {
        value[number] = m.value[number];
    }
}


Matrix::Matrix(Matrix&& m) {
    rows = m.rows;
    cols = m.cols;
    value = m.value;
    m.rows = 0;
    m.cols = 0;
    m.value = nullptr;
}


Matrix& Matrix::operator=(const Matrix &m) {
    rows = m.rows;
    cols = m.cols;
    int total_num = rows * cols;
    this->value = new double [total_num];
    for (unsigned int number = 0; number < total_num; number++) {
        value[number] = m.value[number];
    }
    return *this;
}


Matrix& Matrix::operator+=(const Matrix &m) {
    rows = m.rows;
    cols = m.cols;
    int total_num = rows * cols;
    for (unsigned int number = 0; number < total_num; number++) {
        value[number] = +m.value[number];
    }
    return *this;
}


Matrix& Matrix::operator-=(const Matrix &m) {
    rows = m.rows;
    cols = m.cols;
    int total_num = rows * cols;
    for (unsigned int number = 0; number < total_num; number++) {
        value[number] -= m.value[number];
    }
    return *this;
}


Matrix& Matrix::operator*=(const double num) {
    for (unsigned int number = 0; number < rows * cols; number++){
        value[number] *= num;
    }
}


Matrix& Matrix::operator*=(const Matrix &m) {
    Matrix itog = Matrix(rows, cols);
    itog.zero_matrix();
    for (unsigned int row = 0; row < itog.rows; row++) {
        for (unsigned int col = 0; col < itog.cols; col++) {
            for (unsigned int number = 0; number < m.rows; number++) {
                itog.value[row * itog.cols + col] += value[row * col + number] * m.value[number * m.cols + col];
            }
        }
    }
    *this = itog;
    return *this;
}


void Matrix::mult_by_num(const double num) {
    for (unsigned int number = 0; number < rows * cols; number++) {
        value[number] *= num;
    }
}


void Matrix::zero_matrix() {
    for (unsigned int number = 0; number < rows * cols; number++) {
        value[number] = 0;
    }
}

void Matrix::unit_matrix() {
    for (unsigned int number = 0; number < cols * rows; number += cols + 1) {
        value[number] = 1.0;
    }
}


void Matrix::transposition() {
    unsigned int row = rows;
    unsigned int col = cols;
    double* array = new double [rows * cols];
    for (unsigned int row_n = 0; row_n < rows; row_n++) {
        for (unsigned int col_n = 0; col_n < cols; col_n++) {
            array[row_n * cols + col_n] = value [col_n * rows + row_n];
        }
    }
    delete value;
    value = array;
    rows = row;
    cols = col;
}


/*Matrix Matrix::minor(const Matrix m, const unsigned int size, const unsigned int r, const unsigned int c) {
    int n_row = rows - 1;
    int n_col = cols - 1;

    Matrix itog = Matrix (n_row, n_col);
    unsigned int k = 0;
    for (unsigned int number = 0; number < rows * cols; number++) {
        if ((number % cols == c) or (number / cols == r)) {
            itog.value[k++] = value[number];
        }
    }
    return itog;
}*/


Matrix Matrix::minor(const Matrix matrix,const unsigned int size, const unsigned int row, const unsigned int col)
{
    Matrix minor(size - 1, size - 1);
    unsigned int shiftrow = 0;
    unsigned int shiftcol;
    for (unsigned int rows = 0; rows < size - 1; rows++) {
        if (rows == row) {shiftrow = 1;}
        shiftcol = 0;
        for (unsigned int cols = 0; cols < size - 1; cols++) {
            if (cols == col) {shiftcol = 1;}
            minor.value[rows * (size - 1) + cols] = matrix.value[(rows + shiftrow) * size + (cols + shiftcol)];
        }
    }
    return minor;
}


void Matrix::power(const unsigned int n) {
    Matrix itog = Matrix (rows, cols);
    itog.unit_matrix();
    for (unsigned int number = 0; number < n; number++) {
        itog *= *this;
    }
    this->set_values(rows * cols, itog.value);
}


void Matrix::exponent(const unsigned int e) {
    Matrix itog = Matrix (rows, cols);
    itog.unit_matrix();
    double fact = 1.0;
    Matrix temp = itog;
    for (unsigned int number = 1; number < e; number++) {
        temp *= *this;
        fact /= number;
        itog += (fact * temp);
    }
    *this = itog;
}


double Matrix::determinant(const Matrix m, unsigned int size) {
    Matrix temp = Matrix(rows, cols);
    temp.set_values(rows * cols, value);
    if (cols == 1) {
        return value[0];
    }
    double itog = 1.0;
    for (unsigned int number = 0; number < temp.rows; number++) {
        Matrix min = minor(m, size, 0, number);
        itog += pow(-1, number) * value[number] * determinant(min, size - 1);
    }
    return itog;
}


Matrix::~Matrix() {
    delete[] value;
}





Matrix operator+ (const Matrix &m1, const Matrix &m2) {
    Matrix itog = m1;
    itog += m2;
    return itog;
}


Matrix operator- (const Matrix &m1, const Matrix &m2) {
    Matrix itog = m1;
    itog -= m2;
    return itog;
}


Matrix operator* (const double num, const Matrix &m) {
    Matrix itog = m;
    itog *= num;
    return itog;
}


Matrix operator* (const Matrix &m1, const Matrix &m2) {
    Matrix itog = m1;
    itog *= m2;
    return itog;
}


Matrix operator* (const Matrix &m, const double num) {
    Matrix itog = m;
    itog *= num;
    return itog;
}


Matrix zero_matrix (const unsigned int rows, const unsigned int cols) {
    Matrix itog = Matrix (rows, cols);
    itog.zero_matrix();
    return itog;
}


Matrix unit_matrix (const unsigned int rows, const unsigned int cols) {
    Matrix itog = Matrix (rows, cols);
    itog.unit_matrix();
    return itog;
}


Matrix mult_by_num (const Matrix m, const double num) {
    Matrix itog = m;
    itog.mult_by_num(num);
    return itog;
}


Matrix power (const Matrix m, const unsigned int n) {
    Matrix itog = Matrix (m.rows, m.cols);
    itog.set_values(m.rows * m.cols, m.value);
    itog.power(n);
    return itog;
}


Matrix exponent (const Matrix m, const unsigned int e = 5) {
    Matrix itog = Matrix (m.rows, m.cols);
    itog.set_values(m.rows * m.cols, m.value);
    itog.exponent(e);
    return itog;
}


/*Тесты для проверки работоспособности программы*/

// Тест для суммирование

void summation_test() {
    Matrix m1 = Matrix(3, 3);  // Инициализация матриц для теста
    Matrix m2 = Matrix(3, 3);
    double array_1[9] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};  // Задание исходных данных
    double array_2[9] = {9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0};
    m1.set_values(9, array_1);
    m2.set_values(9, array_2);
    Matrix itog = m1 + m2;  // Итог вычисления программой.
    Matrix result = Matrix (3, 3);
    double array_result[9] = {10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0};  // Результирующие данные для сравнения
    result.set_values(9, array_result);
    bool res = (itog == result);
    if (res) {  // Если результаты совпали
        std::cout << "Summation is correct\n";  // Суммирование верно
    }
    else {
        std::cout << "Summation is incorrect\n";
    }
}


void subtraction_test() {
    Matrix m1 = Matrix(3, 3);  // Инициализация матриц для теста
    Matrix m2 = Matrix(3, 3);
    double array_1[9] = {10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0};  // Задание исходных данных
    double array_2[9] = {9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0};
    m1.set_values(9, array_1);
    m2.set_values(9, array_2);
    Matrix itog = m1 - m2;  // Итог вычисления программой.
    Matrix result = Matrix (3, 3);
    double array_result[9] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};  // Результирующие данные для сравнения
    result.set_values(9, array_result);
    bool res = (itog == result);
    if (res) {  // Если результаты совпали
        std::cout << "Subtraction is correct\n";  // Вычитание верно
    }
    else {
        std::cout << "Subtraction is incorrect\n";
    }
}


void multiplication_test () {
    Matrix m1 = Matrix(3, 3);
    Matrix m2 = Matrix(3, 3);
    double array_1[9] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};  // Задание исходных данных
    double array_2[9] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    m1.set_values(9, array_1);
    m2.set_values(9, array_2);
    Matrix itog = m1 * m2;
    Matrix result = Matrix (3, 3);
    double array_result[9] = {30.0, 36.0, 42.0, 66.0, 81.0, 96.0, 102.0, 126.0, 150.0};
    result.set_values(9, array_result);
    bool res = (itog == result);
    if (res) {
        std::cout << ("Multiplication is correct\n");
    }
    else {
        std::cout << ("Multiplication is incorrect\n");
    }
}


void mult_by_num_test() {
    Matrix m1 = Matrix(3, 3);
    double num = 5;
    double array_1[9] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    m1.set_values(9, array_1);
    Matrix itog = m1 * num;
    Matrix result = Matrix(3, 3);
    double array_result[9] = {5.0, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40.0, 45.0};
    result.set_values(9, array_result);
    bool res = (itog == result);
    if (res) {
        std::cout << ("Multiplication matrix by number is correct\n");
    }
    else {
        std::cout << ("Multiplication matrix by number is incorrect\n");
    }
}


void determinant_test() {
    Matrix m1 = Matrix(3, 3);
    double array_1[9] = {2.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    m1.set_values(9, array_1);
    double itog = m1.determinant(m1, 3);
    double result = -3;
    bool res = (itog == result);
    if (res) {
        std::cout << ("Determinant was ound correctly\n");
    }
    else {
        std::cout << ("Determinant was found incorrectly\n");
    }
}


void all_tests() {  // Блок для вызова тестов, потом его в main прописать
    summation_test();
    subtraction_test();
    mult_by_num_test();
    multiplication_test();
    determinant_test();
}


int main() {

    all_tests();  // Вызов блока тестов для прогона

    return 0;
}

// Спросить как кидать проверки