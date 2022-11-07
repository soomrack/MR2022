#include <iostream>
#include <malloc.h>

class Matrix {
private:
    unsigned int cols;
    unsigned int rows;
public:
    double *values;
    Matrix(const unsigned int cols_m, const unsigned int rows_m);
    Matrix(const Matrix &A);
    ~Matrix();
    Matrix data_input(Matrix matrix, double arr[]);
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


Matrix Matrix::data_input(Matrix matrix, double arr[]){
        for (unsigned int idx = 0; idx < cols * rows; idx++){
            values[idx] = arr[idx];
        }
        return matrix;
}


int main() {
    Matrix A(3,3);
    Matrix C(3,3);
    Matrix B(A);
    return 0;
}
