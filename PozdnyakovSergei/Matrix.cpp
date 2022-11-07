#include <iostream>
#include <malloc.h>


class Matrix {
private:
    unsigned long int cols;
    unsigned long int rows;
public:
    double *values;
    Matrix (const unsigned long int colsm, const unsigned long int rowsm);
    Matrix (const Matrix &A);
    ~Matrix();
    Matrix data_input (Matrix matrix, double arr[]);
};


Matrix::Matrix(const unsigned long int colsm, const unsigned long int rowsm) {
    cols = colsm;
    rows = rowsm;
    values = new double [cols * rows];
    for (unsigned long int number = 0; number < cols * rows; number++) {
        values[number] = 0.0;
    }
}


Matrix::Matrix(const Matrix &A) {
    cols = A.cols;
    rows = A.rows;
    values = new double [cols * rows];
    for (int number = 0; number < cols * rows; number++) {
        values[number] = A.values[number];
    }
}


Matrix::~Matrix() {
    delete[] values;
}


Matrix Matrix::data_input(Matrix matrix, double arr[]) {
    for (unsigned int number = 0; number < cols * rows; number++) {
        values[number] = arr[number];
    }
    return matrix;
}


int main() {
    Matrix A(3,3);
    Matrix B(3, 3);

    return 0;
}
