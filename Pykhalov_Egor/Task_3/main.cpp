#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

const double COMPARATION_CONST = 0.0001;
unsigned int MATRIX_MEMORY_QUANTITY = 0;


class Matrix {
protected:

    unsigned int rows;
    unsigned int cols;

    double *data;

public:

    Matrix();  // конструктор создания пустых матриц
    Matrix(const unsigned int n);  // конструктор создания квадратных матриц
    Matrix(const unsigned int row, const unsigned int col);  //конструктор создания прямоугольных матриц
    Matrix(const Matrix& x);  // оператор копирования
    Matrix(Matrix&& x);  // оператор переноса
    ~Matrix();  // деструктор

    Matrix& operator=(const Matrix &x);
    Matrix& operator+=(const Matrix &x);
    Matrix& operator-=(const Matrix &x);
    Matrix& operator*=(const double k);
    Matrix& operator*=(const Matrix &x);

    void zero();
    void one();
    void multy_k(const double k);
    void tran();
    Matrix minor(const unsigned int cur_row, const unsigned int cur_col);
    void triangle();
    double det();
    void reverse();
    void pow(const unsigned int n);
    void exponent(const unsigned int p_degree = 3);

    void fill_random(const unsigned int max_range = 51);
    void fill_certain(const unsigned int len, const double* arrey);
    void output(bool f = false);

    friend Matrix pow(const Matrix x, const unsigned int n);
    friend Matrix exponent(const Matrix x, const unsigned int p_degree);

    friend bool operator==(const Matrix &x, const Matrix &y);

};


class Matrix_Exception : public std::domain_error
{
public:
    Matrix_Exception(const char* const msg) : std::domain_error(msg)
    {}
};


Matrix_Exception SIZE_UNMATCH("Error founded: Two datas have incompatible size");
Matrix_Exception NOT_SQUARE("Error founded: The number of rows must be equal to cols");
Matrix_Exception DIV_BY_ZERO("Error founded: Division by zero");


Matrix undefinded();
Matrix zero(const unsigned int row, const unsigned int col);
Matrix one(const unsigned int row, const unsigned int col);


Matrix operator+(const Matrix &x, const Matrix &y);
Matrix operator-(const Matrix &x, const Matrix &y);
Matrix operator*(const Matrix &x, const Matrix &y);
Matrix operator*(const double k, const Matrix &x);
Matrix operator*(const Matrix &x, const double k);


Matrix::Matrix() {
    rows = 0;
    cols = 0;
}


Matrix::Matrix(const unsigned int n) {
    rows = n;
    cols = n;

    data = new double[n * n];
}


Matrix::Matrix(const unsigned int row, const unsigned int col) {
    rows = row;
    cols = col;

    data = new double[row * col];
}


Matrix::Matrix(const Matrix &x) {
    rows = x.rows;
    cols = x.cols;

    //delete[] data;
    data = new double[rows * cols];

    for (unsigned int idx = 0; idx < rows * cols; idx++){
        data[idx] = x.data[idx];
    }
}


Matrix::Matrix(Matrix&& x){
    rows = x.rows;
    cols = x.cols;
    data = x.data;

    x.rows = 0;
    x.cols = 0;
    x.data = nullptr;
}


Matrix::~Matrix() {
    delete[] data;
}


Matrix& Matrix::operator=(const Matrix &x) {
    if (this != &x){
        if (!data)
            delete[] data;

        rows = x.rows;
        cols = x.cols;

        this->data = new double[rows * cols];
        for (unsigned int idx = 0; idx < rows * cols; idx++){
            data[idx] = x.data[idx];
        }
    }

    return *this;
}


Matrix& Matrix::operator+=(const Matrix &x) {
    if ((rows != x.rows) or (cols != x.cols)) throw SIZE_UNMATCH;

    for (unsigned int idx = 0; idx < rows * cols; idx++){
        data[idx] += x.data[idx];
    }

    return *this;
}


Matrix& Matrix::operator-=(const Matrix &x) {
    if ((rows != x.rows) or (cols != x.cols)) throw SIZE_UNMATCH;

    for (unsigned int idx = 0; idx < rows * cols; idx++){
        data[idx] -= x.data[idx];
    }

    return *this;
}


Matrix& Matrix::operator*=(const double k) {
    for (unsigned int idx = 0; idx < rows * cols; idx++){
        data[idx] *= k;
    }
}


Matrix& Matrix::operator*=(const Matrix &x) {
    if (cols != x.rows) throw SIZE_UNMATCH;

    Matrix rez = Matrix(rows, x.cols);
    rez.zero();
    for (unsigned int row = 0; row < rez.rows; row++){
        for (unsigned int col = 0; col < rez.cols; col++){

            for (unsigned int idx = 0; idx < x.rows; idx++){
                rez.data[row * rez.cols + col] += data[row * cols + idx] * x.data[idx * x.cols + col];
            }
        }
    }

    *this = rez;
    return *this;
}


void Matrix::zero(){
    for (unsigned int idx = 0; idx < rows * cols; idx++){
        data[idx] = 0.0;
    }
}


void Matrix::one(){
    this->zero();
    for (unsigned int idx = 0; idx < rows; idx++){
        data[idx + cols * idx] = 1.0;
    }
}


void Matrix::multy_k(const double k){
    for (unsigned int idx = 0; idx < rows * cols; idx++){
        data[idx] *= k;
    }
}


void Matrix::tran(){
    unsigned int row = cols;
    unsigned int col = rows;

    double* temp_arrey = new double [rows * cols];

    for (unsigned int row_idx = 0; row_idx < rows; row_idx++){
        for (unsigned int col_idx = 0; col_idx < cols; col_idx++){
            temp_arrey[col_idx * rows + row_idx] = data[row_idx * cols + col_idx];
        }
    }

    delete[] data;
    data = temp_arrey;
    rows = row;
    cols = col;
}


Matrix Matrix::minor(const unsigned int cur_row, const unsigned int cur_col){
    int new_row = rows - 1, new_col = cols - 1;
    if (cur_row >= rows) new_row++;
    if (cur_col >= cols) new_col++;

    Matrix rez = Matrix(new_row, new_col);
    unsigned int k = 0;

    for (unsigned int idx = 0; idx < rows * cols; idx++){
        if ((idx % cols == cur_col) or (idx / cols == cur_row)) continue;
        rez.data[k++] = data[idx];
    }

    return rez;
}


void Matrix::triangle() {
    if (rows == 1) return;

    bool need_to_trans = false;
    if (rows > cols){
        need_to_trans = true;
        this->tran();
    }

    for (unsigned int step = 1; step < rows; step++) {
        for (unsigned int cur_row = step; cur_row < rows; cur_row++) {
            if (data[(step - 1) * (cols + 1)] < COMPARATION_CONST){
                throw DIV_BY_ZERO;
            }
            double ratio = data[cur_row * cols + step - 1] / data[(step - 1) * cols + step - 1];
            for (unsigned int col = step - 1; col < cols; col++) {
                data[cur_row * cols + col] -= ratio * data[(step - 1) * cols + col];
            }
        }
    }

    if (need_to_trans){
        this->tran();
    }
}


double Matrix::det(){
    if (rows != cols) throw NOT_SQUARE;

    Matrix temp = Matrix(rows, cols);
    temp.fill_certain(rows * cols, data);
    temp.triangle();

    double rez = 1.0;
    for (unsigned int idx = 0; idx < temp.rows; idx++){
        rez *= temp.data[idx * cols + idx];
    }

    return rez;
}


void Matrix::reverse() {
    double deter = this->det();
    if (rows != cols) throw NOT_SQUARE;

    Matrix temp = Matrix(rows, cols);
    int ratio = 1;
    for (unsigned int row = 0; row < rows; row++){
        for (unsigned int col = 0; col < cols; col++){
            temp.data[row * cols + col] = ratio * this->minor(row, col).det();
            ratio *= -1;
        }
    }

    temp.tran();
    if (abs(deter - 0.0) < COMPARATION_CONST)  throw DIV_BY_ZERO;
    temp.multy_k(1/deter);

    this->fill_certain(temp.rows * temp.cols, temp.data);
}


void Matrix::pow(const unsigned int n) {
    if (rows != cols) throw NOT_SQUARE;

    Matrix rez = Matrix(rows, cols);
    rez.one();

    for (unsigned int idx = 0; idx < n; idx++) {
        rez *= *this;
    }

    this->fill_certain(rows * cols, rez.data);
}


void Matrix::fill_random(const unsigned int max_range) {
    for (unsigned int idx = 0; idx < rows * cols; idx++){
        data[idx] = rand() % max_range;
    }
}


void Matrix::fill_certain(const unsigned int len, const double* arrey) {
    if (len != rows * cols) throw SIZE_UNMATCH;

    for (unsigned int idx = 0; idx < rows * cols; idx++){
        data[idx] = arrey[idx];
    }
}


void Matrix::output(bool f){
    if (f) std::cout << rows << " " << cols << "\n";

    for (unsigned int row = 0; row < rows; row++){
        for (unsigned int col = 0; col < cols; col++){
            std::cout << this->data[row * cols + col] << "  ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}


Matrix undefinded(){
    Matrix rez = Matrix();
    return rez;
}


Matrix zero(const unsigned int row, const unsigned int col){
    Matrix rez = Matrix(row, col);
    rez.zero();
    return rez;
}


Matrix one(const unsigned int row, const unsigned int col){
    Matrix rez = Matrix(row, col);
    rez.one();
    return rez;
}


Matrix multy_k(const Matrix x, const double k){
    Matrix rez = x;
    rez.multy_k(k);
    return rez;
}


Matrix pow(const Matrix x, const unsigned int n){
    Matrix rez = Matrix(x.rows, x.cols);
    if (x.rows != x.cols) {
        throw NOT_SQUARE;
        return rez;
    }

    rez.fill_certain(x.rows * x.cols, x.data);
    rez.pow(n);

    return rez;
}


void Matrix::exponent(const unsigned int p_degree) {
    if (rows != cols) throw NOT_SQUARE;

    Matrix rez = Matrix(rows, cols);
    rez.one();

    double ratio = 1;
    Matrix temp = rez;
    for (unsigned int idx = 1; idx < p_degree; idx++){
        temp *= *this;
        ratio /= (idx);
        rez += (temp * ratio);
    }

    *this = rez;
}


Matrix exponent(const Matrix x, const unsigned int p_degree = 3){
    Matrix rez = Matrix(x.rows, x.cols);
    rez.fill_certain(x.rows * x.cols, x.data);

    rez.exponent(p_degree);
    return rez;
}


Matrix operator+(const Matrix &x, const Matrix &y){
    Matrix rez = x;
    rez += y;
    return rez;
}


Matrix operator-(const Matrix &x, const Matrix &y){
    Matrix rez = x;
    rez -= y;
    return rez;
}


Matrix operator*(const Matrix &x, const Matrix &y){
    Matrix rez = x;
    rez *= y;
    return rez;
}


Matrix operator*(const double k, const Matrix &x){
    Matrix rez = x;
    rez *= k;
    return rez;
}


Matrix operator*(const Matrix &x, const double k){
    return k * x;
}


bool operator==(const Matrix &x, const Matrix &y){
    bool flag = ((x.rows == y.rows) and (x.cols == y.cols));
    if (!flag) return flag;

    for (unsigned int idx = 0; idx < x.rows * x.cols; idx++){
        flag *= (abs(x.data[idx] - y.data[idx]) < COMPARATION_CONST);
    }
    return flag;
}


class Matrix_memory : public Matrix
{
protected:

    unsigned int mem_size;
    unsigned int quantity;

public:

    Matrix_memory();
    Matrix_memory(const unsigned int n);
    Matrix_memory(const unsigned int row, const unsigned int col);
    Matrix_memory(const Matrix_memory &x);
    Matrix_memory(Matrix_memory &&x);
    ~Matrix_memory();

    Matrix_memory& operator=(const Matrix_memory &x);

    void output(bool f = false);
};



Matrix_memory::Matrix_memory() {
    rows = 0;
    cols = 0;
    data = nullptr;
    mem_size = 0;
    quantity = ++MATRIX_MEMORY_QUANTITY;
}


Matrix_memory::Matrix_memory(const unsigned int n) {
    rows = n;
    cols = n;
    mem_size = n * n;
    data = new double[mem_size];
    quantity = ++MATRIX_MEMORY_QUANTITY;
}


Matrix_memory::Matrix_memory(const unsigned int row, const unsigned int col) {
    rows = row;
    cols = col;
    mem_size = row * col;
    data = new double[mem_size];

    quantity = ++MATRIX_MEMORY_QUANTITY;
}


Matrix_memory::Matrix_memory(const Matrix_memory &x) {
    rows = x.rows;
    cols = x.cols;
    mem_size = x.mem_size;
    quantity = x.quantity;
    //delete[] data;
    data = new double[mem_size];

    for (unsigned int idx = 0; idx < rows * cols; idx++){
        data[idx] = x.data[idx];
    }
}


Matrix_memory::Matrix_memory(Matrix_memory&& x){
    rows = x.rows;
    cols = x.cols;
    data = x.data;
    mem_size = x.mem_size;
    quantity = x.quantity;

    x.rows = 0;
    x.cols = 0;
    x.mem_size = 0;
    x.quantity = 0;
    x.data = nullptr;
}


Matrix_memory::~Matrix_memory() {
    //delete[] data;
    MATRIX_MEMORY_QUANTITY--;
}


Matrix_memory& Matrix_memory::operator=(const Matrix_memory &x) {
    if (this != &x){
        if (!data)
            delete[] data;

        rows = x.rows;
        cols = x.cols;
        mem_size = x.mem_size;
        quantity = x.quantity;

        this->data = new double[rows * cols];
        for (unsigned int idx = 0; idx < rows * cols; idx++){
            data[idx] = x.data[idx];
        }
    }

    return *this;
}


void Matrix_memory::output(bool f) {
    Matrix::output(f);
    std::cout << "This variable hold " << mem_size * sizeof(double) << " bytes in memory\n";
    std::cout << "There was defended " << MATRIX_MEMORY_QUANTITY << " variables of the Matrix_memory type\n\n";
}


void test_sum(){
    Matrix A = Matrix(3, 3);
    Matrix B = Matrix(3, 3);

    double arrey_a[9] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    double arrey_b[9] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};

    A.fill_certain(9, arrey_a);
    B.fill_certain(9, arrey_b);

    Matrix rez = A + B;

    Matrix standard = Matrix(3, 3);
    double arrey_s[9] = {2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0};
    standard.fill_certain(9, arrey_s);

    bool final = (rez == standard);
    if (final){
        std::cout << "Test of summation was successful\n";
    } else {
        std::cout << "Test of summation was failed\n";
    }
}


void test_sub(){
    Matrix A = Matrix(3, 3);
    Matrix B = Matrix(3, 3);

    double arrey_a[9] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    double arrey_b[9] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};

    A.fill_certain(9, arrey_a);
    B.fill_certain(9, arrey_b);

    Matrix rez = A - B;

    Matrix standard = Matrix(3, 3);
    double arrey_s[9] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    standard.fill_certain(9, arrey_s);

    bool final = (rez == standard);
    if (final){
        std::cout << "Test of subtraction was successful\n";
    } else {
        std::cout << "Test of subtraction was failed\n";
    }
}


void test_mul(){
    Matrix A = Matrix(3, 3);
    Matrix B = Matrix(3, 3);

    double arrey_a[9] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    double arrey_b[9] = {9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0};

    A.fill_certain(9, arrey_a);
    B.fill_certain(9, arrey_b);

    Matrix rez = A * B;

    Matrix standard = Matrix(3, 3);
    double arrey_s[9] = {30.0, 24.0, 18.0, 84.0, 69.0, 54.0, 138.0, 114.0, 90.0};
    standard.fill_certain(9, arrey_s);

    bool final = (rez == standard);
    if (final){
        std::cout << "Test of multiplication was successful\n";
    } else {
        std::cout << "Test of multiplication was failed\n";
    }
}


void test_reverse(){
    const unsigned int n = 3;
    Matrix A = Matrix(n, n);
    A.fill_random();

    Matrix B = A;
    B.reverse();

    Matrix standard = one(n, n);

    bool final = (standard == A * B);
    if (final){
        std::cout << "Test of reverse was successful\n";
    } else {
        std::cout << "Test of reverse was failed\n";
    }
}


void test_exp(){
    Matrix A = Matrix(3, 3);
    A.fill_random();

    Matrix B = exponent(A);

    Matrix standard = Matrix(3, 3);
    standard = one(3,3) + 1 * A + 0.5 * pow(A, 2);

    A.exponent();

    bool final = ((A == standard) and (B == standard));
    if (final){
        std::cout << "Test of exponent was successful\n";
    } else {
        std::cout << "Test of exponent was failed\n";
    }
}


void block_output(){
    std::cout << std::fixed << std::setprecision(2);

    Matrix A = Matrix(3, 5);

    double arrey_a[15] = {5, 4, 3, 2, 1,
                          5, 4, 8, 4, 10,
                          11, 43, 29, 16, 9};
    A.fill_certain(15, arrey_a);
    A.output();

    Matrix_memory X = Matrix_memory();
    Matrix_memory Y = Matrix_memory(5);
    Matrix_memory Z = Matrix_memory(5, 5);

    X = Y;
    X.fill_random(101);
    Y.fill_random(101);
    Z.one();
    Z += X;

    Z.output();

}


void block_tests(){
    test_sum();
    test_sub();
    test_mul();
    test_reverse();
    test_exp();

    std::cout << "\n";
}


int main() {

    block_tests();
    block_output();

    return 0;
}