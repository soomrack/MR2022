#include <iostream>
#include <cmath>

#define EPSILON 0.0001

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

    //Matrix operator = (double i);
    Matrix &operator = (Matrix const &matrix);
    Matrix operator + (Matrix matrix) const;
    Matrix operator + (double number) const;
    Matrix operator - (Matrix matrix) const;
    Matrix operator - (double number) const;
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


/*Matrix Matrix::operator = (double i) {

}*/


Matrix &Matrix::operator = (Matrix const &matrix) {
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


Matrix Matrix::operator + (Matrix const matrix) const {
    Matrix sum_matrix(2,2);
    for (int cell = 0; cell < size; cell++)
        sum_matrix.start[cell] = start[cell] + matrix.start[cell];
    return sum_matrix;
}


Matrix Matrix::operator + (double number) const {
    Matrix sum_matrix(2,2);
    for (int cell = 0; cell < size; cell++)
        sum_matrix.start[cell] = start[cell] + number;
    return sum_matrix;
}


Matrix Matrix::operator - (Matrix const matrix) const {
    Matrix sum_matrix(2,2);
    for (int cell = 0; cell < size; cell++)
        sum_matrix.start[cell] = start[cell] - matrix.start[cell];
    return sum_matrix;
}


Matrix Matrix::operator - (double number) const {
    Matrix sum_matrix(2,2);
    for (int cell = 0; cell < size; cell++)
        sum_matrix.start[cell] = start[cell] - number;
    return sum_matrix;
}


void arrays_compare(double true_array[], Matrix matrix, std::string text) {
    int error_flag = 0;
    std::cout << text << " check:\n";
    for (int cell = 0; cell < matrix.size; cell++) {
        int cell_flag = 0;
        if (std::abs(true_array[cell] - matrix.start[cell]) > EPSILON) {
            cell_flag = 1;
            error_flag += 1;
        }
        std::cout << "true: " << true_array[cell] << " res: " << matrix.start[cell] << " | " << cell_flag << "\n";
    }
    std::cout << "Errors: " << error_flag << "\n";
    std::cout << "\n";
}


void test() {
    Matrix res_matrix(2, 2);
    res_matrix.filling(NAN);

    Matrix matrix1(2,2);
    matrix1.filling(2);

    Matrix matrix2(2,2);
    matrix2.filling(-2);

    //проверка перегрузки =
    res_matrix = matrix1;
    double eq_true_array[] = {2, 2, 2, 2};
    arrays_compare(eq_true_array, res_matrix, "= overload");


    //проверка перегрузки +
    res_matrix = matrix1 + matrix2;
}


int main() {
    test();
    return 0;
}