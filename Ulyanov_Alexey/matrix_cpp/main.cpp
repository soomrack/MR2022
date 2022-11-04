#include <iostream>
#include <algorithm>
#include <iomanip>


const unsigned int Max_range = 51;
const double Comparation_const = 0.0001;


class Matrix {
public:

    unsigned int rows;
    unsigned int cols;

    double *data;


    Matrix();
    Matrix(const unsigned int row, const unsigned int col);
    Matrix(const Matrix &x);
    ~Matrix();
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

    void fill_random();
    void fill_certain(const unsigned int len, const double* arrey);
    void output(bool f = false);

};


Matrix undefinded();
Matrix zero(const unsigned int row, const unsigned int col);
Matrix one(const unsigned int row, const unsigned int col);
Matrix sum(const Matrix x, const Matrix y);
Matrix sub(const Matrix x, const Matrix y);
Matrix multiplication(const Matrix x, const Matrix y);
Matrix multy_k(const Matrix x, const double k);
Matrix pow(const Matrix x, const unsigned int n);


Matrix operator+(const Matrix &x, const Matrix &y);
Matrix operator-(const Matrix &x, const Matrix &y);
Matrix operator*(const Matrix &x, const Matrix &y);
Matrix operator*(const double k, const Matrix &x);
bool operator==(const Matrix &x, const Matrix &y);


Matrix::Matrix() {
    rows = 0;
    cols = 0;
}


Matrix::Matrix(const unsigned int row, const unsigned int col) {
    rows = row;
    cols = col;

    data = new double[row * col];
}


Matrix::~Matrix() {
    delete[] data;
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


Matrix& Matrix::operator=(const Matrix &x) {
    rows = x.rows;
    cols = x.cols;

    if (!data) // проверка data на пустоту
        delete[] data;
    data = new double[rows * cols];

    for (unsigned int idx = 0; idx < rows * cols; idx++){
        data[idx] = x.data[idx];
    }
}


Matrix& Matrix::operator+=(const Matrix &x) {
    if ((rows != x.rows) or (cols != x.cols)) return *this;

    for (unsigned int idx = 0; idx < rows * cols; idx++){
        data[idx] += x.data[idx];
    }

    return *this;
}


Matrix& Matrix::operator-=(const Matrix &x) {
    if ((rows != x.rows) or (cols != x.cols)) return *this;

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
    if (cols != x.rows) return *this;

    Matrix rez = Matrix(rows, x.cols);
    rez.zero();
    for (unsigned int row = 0; row < rez.rows; row++){
        for (unsigned int col = 0; col < rez.cols; col++){
            //double sum = 0;
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
    for (unsigned int idx = 0; idx < rows * cols; idx++){
        temp_arrey[idx] = data[idx];
    }

    for (unsigned int row_idx = 0; row_idx < rows; row_idx++){
        for (unsigned int col_idx = 0; col_idx < cols; col_idx++){
            data[col_idx * rows + row_idx] = temp_arrey[row_idx * cols + col_idx];
        }
    }

    rows = row;
    cols = col;
    delete[] temp_arrey;
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

    bool f = false;
    if (rows > cols){
        f = true;
        this->tran();
    }

    for (unsigned int step = 1; step < rows; step++) {
        for (unsigned int cur_row = step; cur_row < rows; cur_row++) {
            double ratio = data[cur_row * cols + step - 1] / data[(step - 1) * cols + step - 1];
            for (unsigned int col = step - 1; col < cols; col++) {
                data[cur_row * cols + col] -= ratio * data[(step - 1) * cols + col];
            }
        }
    }

    if (f){
        this->tran();
    }
}


double Matrix::det(){
    if (rows != cols) return 0.0;

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
    if ((rows != cols) or (deter == 0)) return;

    Matrix temp = Matrix(rows, cols);
    int ratio = 1;
    for (unsigned int row = 0; row < rows; row++){
        for (unsigned int col = 0; col < cols; col++){
            temp.data[row * cols + col] = ratio * this->minor(row, col).det();
            ratio *= -1;
        }
    }

    temp.tran();
    temp.multy_k(1/deter);

    this->fill_certain(temp.rows * temp.cols, temp.data);
}


void Matrix::pow(const unsigned int n){
    if (rows != cols) return;

    Matrix rez = Matrix(rows, cols);
    rez.one();

    for (unsigned int idx = 0; idx < n; idx++){
        rez *= *this;
    }

    this->fill_certain(rows * cols, rez.data);
}


void Matrix::exponent(const unsigned int p_degree) {
    if (rows != cols) return;

    struct Matrix rez = Matrix(rows, cols);
    rez.one();
    double ratio = 1;
    struct Matrix temp = rez;
    for (unsigned int idx = 1; idx <= p_degree; idx++){
        temp *= *this;
        ratio /= (idx);
        rez += ::multy_k(temp, ratio);
    }

    this->fill_certain(rez.rows * rez.cols, rez.data);
}


void Matrix::fill_random() {
    for (unsigned int idx = 0; idx < rows * cols; idx++){
        data[idx] = rand() % Max_range;
    }
}


void Matrix::fill_certain(const unsigned int len, const double* arrey) {
    if (len != rows * cols) return;

    for (unsigned int idx = 0; idx < rows * cols; idx++){
        data[idx] = arrey[idx];
    }
}


void Matrix::output(bool f){
    if (f) std::cout << rows << " " << cols << "\n";

    /*
    for (unsigned int idx = 0; idx < rows * cols; idx++){
        std::cout << data[idx] << "  ";
    }
    std::cout << "\n";
    */

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


Matrix sum(const Matrix x, const Matrix y){
    if ((x.rows != y.rows) or (x.cols != y.cols)) return undefinded();

    Matrix rez = Matrix();
    rez = Matrix(x.rows, x.cols);
    for (unsigned int idx = 0; idx < rez.rows * rez.cols; idx++){
        rez.data[idx] = x.data[idx] + y.data[idx];
    }

    return rez;
}


Matrix sub(const Matrix x, const Matrix y){
    if ((x.rows != y.rows) or (x.cols != y.cols)) return undefinded();

    Matrix rez = Matrix();
    rez = Matrix(x.rows, x.cols);
    for (unsigned int idx = 0; idx < rez.rows * rez.cols; idx++){
        rez.data[idx] = x.data[idx] - y.data[idx];
    }

    return rez;
}


Matrix multiplication(const Matrix x, const Matrix y){
    if (x.cols != y.rows) return undefinded();

    Matrix rez = Matrix();
    rez = Matrix(x.rows, y.cols);
    for (unsigned int row = 0; row < rez.rows; row++){
        for (unsigned int col = 0; col < rez.cols; col++){
            rez.data[row * rez.cols + col] = 0.0;
            for (unsigned int idx = 0; idx < x.cols; idx++){
                rez.data[row * rez.cols + col] += x.data[row * x.cols + idx] * y.data[idx * y.cols + col];
            }
        }
    }
    return rez;
}


Matrix multy_k(const Matrix x, const double k){
    Matrix rez = x;
    rez.multy_k(k);
    return rez;
}


Matrix pow(const Matrix x, const unsigned int n){
    Matrix rez = Matrix();
    if (x.rows != x.cols) return rez;

    rez = x;
    rez.pow(n);

    return rez;
}


Matrix operator+(const Matrix &x, const Matrix &y){
    if ((x.rows != y.rows) or (x.cols != y.cols)) return undefinded();

    Matrix rez = Matrix(x.rows, x.cols);
    for (unsigned int idx = 0; idx < rez.rows * rez.cols; idx++){
        rez.data[idx] = x.data[idx] + y.data[idx];
    }
    return rez;
}


Matrix operator-(const Matrix &x, const Matrix &y){
    if ((x.rows != y.rows) or (x.cols != y.cols)) return undefinded();

    Matrix rez = Matrix(x.rows, x.cols);
    for (unsigned int idx = 0; idx < rez.rows * rez.cols; idx++){
        rez.data[idx] = x.data[idx] - y.data[idx];
    }
    return rez;
}


Matrix operator*(const Matrix &x, const Matrix &y){
    return multiplication(x, y);
}


Matrix operator*(const double k, const Matrix &x){
    return multy_k(x, k);
}


bool operator==(const Matrix &x, const Matrix &y){
    bool flag = ((x.rows == y.rows) and (x.cols == y.cols));
    if (!flag) return flag;

    for (unsigned int idx = 0; idx < x.rows * x.cols; idx++){
        flag *= (abs(x.data[idx] - y.data[idx]) < Comparation_const);
    }
    return flag;
}


void block_output(){
    std::cout << std::fixed << std::setprecision(2);

    Matrix A = Matrix(3, 3);
    A.fill_random();
    A.output(true);

    Matrix B = Matrix(A.rows, A.cols);
    B.one();
    B.output(true);

    Matrix C = 2 * A + A * B - B;
    C.output(true);

    double arrey_a[9] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    double arrey_b[9] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.9};

    A.fill_certain(9, arrey_a);
    B.fill_certain(9, arrey_b);

    bool f = A == B;
    std::cout << f << std::endl;

}


int main() {

    block_output();

    return 0;
}