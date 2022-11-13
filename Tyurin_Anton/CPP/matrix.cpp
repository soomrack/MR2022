#include <iostream>

class Matrix {
private:
    unsigned int cols;
    unsigned int rows;
public:
    double *values;
    Matrix(unsigned int cols_m, unsigned int rows_m);
    Matrix(const Matrix &A);
    ~Matrix();
    static Matrix data_input(Matrix matrix, const double arr[]);
    static void print_matrix(Matrix matrix);
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

Matrix Matrix::data_input(Matrix matrix, const double arr[]){
        for (unsigned int idx = 0; idx < matrix.cols * matrix.rows; idx++){
            matrix.values[idx] = arr[idx];
        }
        return matrix;
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
int main() {
    Matrix A(3,3);
    double arr_A[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    Matrix::data_input(A,arr_A);
    Matrix::print_matrix(A);
    return 0;
}
