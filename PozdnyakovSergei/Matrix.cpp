#include <iostream>
#include <algorithm>
#include <math.h>
/*
#include <time.h>
*/


const double EPS_CONST = pow(10, -5);


class Matrix {
private:  // в чем отливие между private и protected?
    unsigned int rows;
    unsigned int cols;
    double *value;

public:
    Matrix();  //пустые матрицы
    Matrix(const Matrix& m);  // копирование
    Matrix(const unsigned int row, const unsigned int col);  // прямоугольные матрицы
    ~Matrix();  // деструктор
    Matrix(Matrix&& m); // перенос

    Matrix& operator= (const Matrix &m);
    Matrix& operator+= (const Matrix &m);
    Matrix& operator-= (const Matrix &m);
    Matrix& operator*= (const Matrix &m);
    Matrix& operator*= (const double num);

    void zero_matrix();  // нулевая матрица
    void unit_matrix();  // едничная матрица
    void mult_by_num(const double num);  // умножение на число
    Matrix transposition();  // траспонирование
    double determinant(const Matrix, unsigned int);  // определитель
    void invert();  // обратная матрица
    void power(const unsigned int n);  // возведение матрицы в степень
    void exponent(const unsigned int e = 3);  // матричная экспонента
    Matrix minor(const Matrix, const unsigned int size, const unsigned int r, const unsigned int c);  // минор марицы

    void set_values(const unsigned int l, const double* array);  // заполнение из массива
    void set_random(const unsigned int range = 21);  // заполнение рандомно
    void output(bool f = false);

    friend Matrix exponent(const Matrix m, const unsigned int e);
    friend Matrix power(const Matrix m, const unsigned int n);
    friend bool operator== (const Matrix &m1, const Matrix &m2);
};


/*
добавить exceptions
*/


class Matrix_exceptions : public std::domain_error {  // Класс исключений
public:
    Matrix_exceptions(const char* const error) : std::domain_error(error) {
    }
};


Matrix_exceptions Size_Error ("Error: unequal size of matrices");
Matrix_exceptions Not_Square ("Error: matrix not square");
Matrix_exceptions Div_by_zero ("Error: division by zero");



Matrix operator+ (const Matrix &m1, const Matrix &m2);
Matrix operator- (const Matrix &m1, const Matrix &m2);
Matrix operator* (const double num, const Matrix &m);
Matrix operator* (const Matrix &m1, const Matrix &m2);
Matrix operator* (const Matrix &m, const double num);


Matrix zero_matrix(const unsigned int row, const unsigned int col);
Matrix unit_matrix(const unsigned int row, const unsigned int col);


Matrix::Matrix() : rows(0), cols(0), value(nullptr) {}


Matrix::~Matrix() {
    delete[] value;
}


Matrix::Matrix(const unsigned int r, const unsigned int c) {
    rows = r;
    cols = c;
    value = new double [r * c];  // выделение памяти под элементы матрицы
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
   /* if (this != &m){
        if (!value)
            delete[] value;*/
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

    if ((cols *= m.cols) or (rows != m.rows)) {
        throw Size_Error;
    }

    rows = m.rows;
    cols = m.cols;
    int total_num = rows * cols;
    for (unsigned int number = 0; number < total_num; number++) {
        value[number] += m.value[number];
    }
    return *this;
}


Matrix& Matrix::operator-=(const Matrix &m) {

    if ((cols *= m.cols) or (rows != m.rows)) {
        throw Size_Error;
    }

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

    if (cols *= m.rows) {
        throw Size_Error;
    }

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
    this -> zero_matrix();
    for (unsigned int number = 0; number < cols * rows; number += cols + 1) {
        value[number] = 1.0;
    }
}


/*void Matrix::transposition() {
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
}*/


Matrix Matrix::transposition() {
    Matrix itog = {cols, rows};
    for (unsigned int row = 0; row < itog.rows; row++) {
        for (unsigned int col = 0; col < itog.cols; col++) {
            itog.value[row * itog.cols + col] = value[col * itog.cols + row];
        }
    }
    return itog;
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

    if (cols != rows) {
        throw Not_Square;
    }

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

    if (rows != cols) {
        throw Not_Square;
    }

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


void Matrix::set_values(const unsigned int l, const double *array) {
    for (unsigned int number = 0; number < rows * cols; number++) {
        value[number] = array[number];
    }
}


void Matrix::set_random(const unsigned int range) {
    for (unsigned int number = 0; number < rows * cols; number++) {
        value[number] = rand() % range;
    }
}


void Matrix::output(bool f) {  // Вывод
    if (f) std::cout << rows << " " << cols << " \n";
    for (unsigned int row = 0; row < rows; row++) {
        for (unsigned int col = 0; col < cols; col++) {
            std::cout << this -> value [row * cols + col] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
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


bool operator== (const Matrix &m1, const Matrix &m2) {
    bool fl = ((m1.rows == m2.rows) and (m1.cols == m2.cols));
    if (!fl) return fl;

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


/* При проверки корректности выдает такое: Condition is always false */

// Тест для вычитания
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

// Тест для перемножения
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

// Тест для умножения на число
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


/*void determinant_test() {
    Matrix m = Matrix(3, 3);
    double array_1[9] = {2.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    m.set_values(9, array_1);
    double itog = m.determinant(m, 3);
    double result = -3;
    bool res = (itog == result);
    if (res) {
        std::cout << ("Determinant was ound correctly\n");
    }
    else {
        std::cout << ("Determinant was found incorrectly\n");
    }
}*/


void exponent_test() {
    Matrix m1 = Matrix(3, 3);
    double array_1[9] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    m1.set_values(9, array_1);
    Matrix m2 = exponent(m1, 3);
    Matrix result = Matrix(3, 3);
    result = unit_matrix(3, 3) + m1 + 0.5 * power(m1, 2);
    m1.exponent();
    bool res = (m1 == result);
    if (res) {
        std::cout << ("Exponent is calculated correctly");
    }
    else {
        std::cout << ("Exponent is calculated incorrectly\n");
    }
}


void power_test() {
    Matrix m1 = Matrix(3, 3);
    double num = 5;
    double array_1[9] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    m1.set_values(9, array_1);
    Matrix itog = power(m1, num);
    Matrix result = Matrix(3, 3);
    double array_result[9] = {468.0, 576.0, 684.0, 1062.0, 1305.0, 1548.0, 1656.0, 2034.0, 2412.0};
    result.set_values(9, array_result);
    bool res = (itog == result);
    if (res) {
        std::cout << ("Matrix power is calculated correctly");
    }
    else {
        std::cout << ("Matrix power is calculates incorrectly\n");
    }
}


void test_part() {  // Блок для вызова тестов, потом его в main прописать
    summation_test();
    subtraction_test();
    mult_by_num_test();
    multiplication_test();
    /*determinant_test();*/
    power_test();
    exponent_test();
}


void output_part() {

    Matrix M1 = Matrix (3, 4);
    double array_m1[12] = {1, 2, 3, 4,
                           5, 6, 7, 8,
                           9, 0, 11, 12};
    M1.set_values(12, array_m1);
    M1.output();

    Matrix M2 = Matrix (3, 4);
    M2.set_random(21);
    M1.output();

    Matrix M3 = Matrix(3, 3);
    M3.zero_matrix();
    M3.output();

    Matrix M4 = Matrix(3, 3);
    M4.unit_matrix();
    M4.output();
}


int main() {

    test_part();  // Вызов блока тестов для прогона

    output_part();

    return 0;
}

// Спросить как кидать проверки