#include <iostream>

class Matrix {
private:
    unsigned int cols;
    unsigned int rows;
public:
    double *values;
    Matrix(unsigned int cols_m, unsigned int rows_m);
    Matrix(const Matrix &A);
    Matrix(unsigned int cols_m);
    ~Matrix();
    static Matrix data_input(Matrix *matrix, const double arr[]);
    static void print_matrix(Matrix matrix);
    static void print_matrix(Matrix matrix, char symbol);
    Matrix error();
    Matrix operator+(Matrix X);
    Matrix operator-(Matrix X);
    Matrix operator*(Matrix X);
};


Matrix::Matrix(const unsigned int cols_m, const unsigned int rows_m){  // Инициализация матриц
        cols = cols_m;
        rows = rows_m;
        values = new double[cols * rows];
        // delete[] matrix.values;
        for (unsigned int idx = 0; idx < cols * rows; idx++){
            values[idx] = 0.0;
        }
}

Matrix::Matrix(const Matrix &A) {
    rows = A.rows;
    cols = A.cols;
    values = new double[rows * cols];
    for (unsigned int idx = 0; idx < rows * cols; idx++) {
        values[idx] = A.values[idx];
    }
}

Matrix::~Matrix() {
    delete[] values;
}

Matrix Matrix::data_input(Matrix *matrix, const double arr[]){
        for (unsigned int idx = 0; idx < matrix->cols * matrix->rows; idx++){
            matrix->values[idx] = arr[idx];
        }
        return *matrix;
}

void Matrix::print_matrix(Matrix X) {  // Вывод матрицы на экран
    std::cout << "Matrix\n";
    for (unsigned int row = 0; row < X.rows; row++) {
        for (unsigned int col = 0; col < X.cols; col++) {
            std::cout << X.values[row * X.cols + col] << "\t";
        }
        std::cout << "\n";
    }
}

void Matrix::print_matrix(Matrix matrix, char symbol){
    std::cout << "Matrix";
    switch(symbol){
        case '+': std::cout << "\tsumm\n"; break;
        case '-': std::cout << "\tsubstruction\n"; break;
        case '*': std::cout << "\tmultiplication\n"; break;
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
    error.values = NULL;
    return error;
}

Matrix Matrix::operator+ (Matrix X) {
    Matrix sum(X.cols, X.rows);
    for (unsigned int idx = 0; idx < X.cols * X.rows; idx++) {
      sum.values[idx] = values[idx] + X.values[idx];
    }
    return sum;
}

Matrix Matrix::operator- (Matrix X) {
    Matrix sub(X.cols, X.rows);
    for (unsigned int idx = 0; idx < X.cols * X.rows; idx++) {
        sub.values[idx] = values[idx] - X.values[idx];
    }
    return sub;
}

Matrix Matrix::operator* (Matrix X) {
    Matrix mult(X.cols, X.rows);
    for (unsigned int row = 0; row < rows; row++) {
        for (unsigned int col = 0; col < X.cols; col++) {
            mult.values[row * mult.rows + col] = 0;
            for (unsigned int k = 0; k < cols; k++) {
                mult.values[row * mult.cols + col] += values[row * cols + k] * X.values[k * X.cols + col];
            }
            return mult;
        }
    }
}

int main() {
    Matrix A(3,3);
    double arr_A[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    Matrix::data_input(&A,arr_A);
    Matrix B(3);
    Matrix::print_matrix(A);
    Matrix::print_matrix(B);
    Matrix Sum = A + B;
    Matrix Sub = A - B;
    Matrix Mult = A * B;

    Matrix::print_matrix(Sum,'+');
    Matrix::print_matrix(Sub,'-');
    Matrix::print_matrix(Mult,'*');

    return 0;
}