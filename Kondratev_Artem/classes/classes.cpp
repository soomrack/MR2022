#include <iostream>


class Matrix {
private:
    int rows;
    int cols;
public:
    int size;
    double **values;
    double *start;

    Matrix(int input_rows, int input_cols);
    ~Matrix();
    Matrix(Matrix const &matrix);
    void output() const;
    void filling(double number) const;

    Matrix operator = (Matrix &matrix);
};


Matrix::Matrix(int input_rows, int input_cols) {
    rows = input_rows;
    cols = input_cols;
    size = rows * cols;
    values = new double *[rows];
    start = new double [size];
    for (int row = 0; row < rows; row++)
        values[row] = start + row * cols;
}


Matrix::~Matrix() {
    rows = 0;
    cols = 0;
    size = 0;
    delete values;
    delete start;
}


Matrix::Matrix(Matrix const &matrix) {
    rows = matrix.rows;
    cols = matrix.cols;
    size = rows * cols;
    values = new double *[rows];
    start = new double[size];
    for (int row = 0; row < rows; row++)
        values[row] = start + row * cols;
    for (int cell = 0; cell < size; cell++)
        start[cell] = matrix.start[cell];
}


void Matrix::output() const {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++)
            std::cout << values[row][col] << "  ";
        std::cout << "\n";
    }
    std::cout << "\n";
}


void Matrix::filling(double number) const {
    for (int cell = 0; cell < size; cell++)
        start[cell] = number;
}


Matrix ret(Matrix matrix) {
    return matrix;
}


int main() {

    Matrix A(2,2);
    A.filling(2);
    A.output();
    Matrix C = ret(A);
    C.output();
    A.filling(3);
    A.output();
    C.output();

    return 0;
}