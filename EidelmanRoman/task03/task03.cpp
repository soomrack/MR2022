#include <iostream>
#include <cstring>

class Matrix {
private:
    unsigned int rows = 0;
    unsigned int cols = 0;
    unsigned int matrix_size = rows * cols;
    unsigned int memory_size = matrix_size + rows;
    double** values = nullptr;
    double* data = nullptr;

public:
    Matrix() = default;
    Matrix(unsigned int input_rows, unsigned int input_cols);
    Matrix(const Matrix& X); //copy
    Matrix(unsigned int input_rows, unsigned int input_cols, double x);
    ~Matrix();

    Matrix operator+(Matrix second_matrix);
    Matrix operator-(Matrix second_matrix);
    Matrix operator*(Matrix second_matrix);
    Matrix operator^(unsigned x);
    Matrix operator/(double x);

    Matrix T();
    void print();
};

Matrix::Matrix(unsigned int input_rows, unsigned int input_cols) {
    rows = input_rows;
    cols = input_cols;
    data = new double[memory_size];
    for (int row = 0; row < rows; ++row)
        values[row] = data + row * cols;
}

Matrix::Matrix(const Matrix& X) {
    matrix_size = X.matrix_size;
    data = new double[memory_size];
    memcpy(data, X.data, memory_size * sizeof(double));
}

Matrix::Matrix(unsigned int input_rows, unsigned int input_cols, double x): Matrix(input_rows, input_cols) {
    for (int i = 0; i < matrix_size; ++i) {
        data[i] = x;
    }
}

Matrix::~Matrix() {
    delete[] data;
}

Matrix Matrix::operator+(Matrix second_matrix) {
    Matrix addition_matrix(rows, cols);

    for (int row = 0; row < addition_matrix.rows; row++) {
        for (int col = 0; col < addition_matrix.cols; col++) {
            addition_matrix.values[row][col] = values[row][col] + second_matrix.values[row][col];
        }
    }

    return addition_matrix;  // одним циклом
}

Matrix Matrix::operator-(Matrix second_matrix) {
    Matrix subtraction_matrix(rows, cols);

    for (int row = 0; row < subtraction_matrix.rows; row++) {
        for (int col = 0; col < subtraction_matrix.cols; col++) {
            subtraction_matrix.values[row][col] = values[row][col] - second_matrix.values[row][col];
        }
    }

    return subtraction_matrix;
}

Matrix Matrix::operator*(Matrix second_matrix) {
    Matrix multiplication_matrix(rows, cols);

    for (int row = 0; row < multiplication_matrix.rows; row++) {
        for (int col = 0; col < multiplication_matrix.cols; col++) {
            for (int k = 0; k < multiplication_matrix.rows; k++) {
                multiplication_matrix.values[rows][cols] += values[rows][k] * second_matrix.values[k][cols];
            }
        }
    }

    return multiplication_matrix; // заполнить нулями
}

Matrix Matrix::operator^(unsigned int x) {
    Matrix result_matrix(rows, cols);
    Matrix const_matrix(rows, cols);
    const_matrix.values = values;// конструктор копий

    for (int i = 1; i < x; x++) {
        result_matrix = result_matrix * const_matrix; // единичная матрица
    }

    return result_matrix;
}

Matrix Matrix::operator/(double x) {

//    if (x == 0)
//        throw "Error founded: Division by zero";

    Matrix result_matrix(rows, cols);

    for (int row = 0; row < result_matrix.rows; row++) {
        for (int col = 0; col < result_matrix.cols; col++) {
            result_matrix.values[row][col] = values[row][col] / x;
        }
    }

    return result_matrix; // один цикл
}

Matrix Matrix::T() {

    Matrix copy_matrix(rows, cols);

    for (int rows = 0; rows < copy_matrix.rows; rows++) {
        for (int cols = 0; cols < copy_matrix.cols; cols++) {
            copy_matrix.values[rows][cols] = values[cols][rows];
        }
    }

    return copy_matrix;
}

void Matrix::print() {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++)
            std::cout << values[row][col] << " ";
        std::cout << "\n";
    }
    std::cout << "\n";
}

int main() {
    short n = 2;
    short m = 2;
    Matrix A(n, m);

    A.print();
//    try {
//        A / 0;
//    } catch (std::string) {
//        std::cout << "Error!";
//    }

    return 0;
}