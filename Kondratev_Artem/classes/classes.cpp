#include <iostream>
#include <cstdint>

#define EPSILON 0.0001

class Matrix {
private:
    uint64_t rows = 0;
    uint64_t cols = 0;
public:
    double **values;
    uint64_t size = 0;

    Matrix(uint64_t init_rows, uint64_t init_cols) {
        if (init_rows > 0 and init_cols > 0) {
            rows = init_rows;
            cols = init_cols;
            size = rows * cols;
            values = new double *[rows];
            for (int row = 0; row < rows; row++)
                values[row] = new double[cols];
        }
    }

    ~Matrix() {
        for (int row = 0; row < rows; row++)
            delete values[row];
        delete values;
        rows = 0;
        cols = 0;
        size = 0;
    }

    Matrix(const Matrix &matrix) {
        values = new double *[rows];
        for (int row = 0; row < rows; row++)
            values[row] = new double[cols];
        for (int row = 0; row <= matrix.rows-1; row++)
            for (int col = 0; col <= matrix.cols-1; col++)
                values[row][col] = matrix.values[row][col];
    }

    void filling(double number) const {
        for (int row = 0; row < rows; row++)
            for (int col = 0; col < cols; col++)
                values[row][col] = number;
    }

    void filling(const double array[]) const {
        int array_index = 0;
        for (int row = 0; row < rows; row++)
            for (int col = 0; col < cols; col++) {
                values[row][col] = array[array_index];
                array_index += 1;
            }
    }

    void output() const {
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++)
                std::cout << values[row][col] << "  ";
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    [[nodiscard]] inline int is_len_zero() const {
        return (int) (rows + cols);
    }

    static Matrix addition(Matrix matrix1, Matrix matrix2) {
        /*if(matrix1.rows != matrix2.rows or matrix1.cols != matrix2.cols or
                matrix1.are_row_col_not_zero() == 0 or matrix2.is_len_zero() == 0) {
            Matrix error(0, 0);
            return error;
        }*/
        //Matrix sum_matrix(matrix1.rows, matrix1.cols);
        for (int row = 0; row < matrix1.rows; row++)
            for (int col = 0; col < matrix1.cols; col++)
                //sum_matrix.values[row][col] = matrix1.values[row][col] + matrix2.values[row][col];
                //return sum_matrix;
                int a;

    }

    static Matrix addition(Matrix matrix1, double number) {
        if (matrix1.is_len_zero() == 0) {
            Matrix error(0, 0);
            return error;
        }
        Matrix sum_matrix(matrix1.rows, matrix1.cols);
        for (int row = 0; row < sum_matrix.rows; row++)
            for (int col = 0; col < sum_matrix.cols; col++)
                sum_matrix.values[row][col] = matrix1.values[row][col] + number;
        return sum_matrix;
    }

    static Matrix subtraction(Matrix matrix1, Matrix matrix2) {
        if (matrix1.rows != matrix2.rows or matrix1.cols != matrix2.cols or matrix1.rows == 0 or matrix1.rows) {
            Matrix error(0, 0);
            return error;
        }
        Matrix sum_matrix(matrix1.rows, matrix1.cols);
        for (int row = 0; row < sum_matrix.rows; row++)
            for (int col = 0; col < sum_matrix.cols; col++)
                sum_matrix.values[row][col] = matrix1.values[row][col] - matrix2.values[row][col];
        return sum_matrix;
    }

    static Matrix multiplication(Matrix matrix1, Matrix matrix2) {
        if (matrix1.cols != matrix2.rows or matrix1.is_len_zero() == 0 or matrix2.is_len_zero() == 0) {
            Matrix error(0, 0);
            return error;
        }
        Matrix multiplied_matrix(matrix1.rows, matrix2.cols);
        for (int row = 0; row < multiplied_matrix.rows; row++)
            for (int col = 0; col < multiplied_matrix.cols; col++) {
                multiplied_matrix.values[row][col] = 0;
                for (int k = 0; k < matrix1.cols; k++)
                    multiplied_matrix.values[row][col] += matrix1.values[row][k] * matrix2.values[k][col];
            }
        return multiplied_matrix;
    }

    static Matrix multiplication(Matrix matrix1, double number) {
        if (matrix1.is_len_zero() == 0) {
            Matrix error(0, 0);
            return error;
        }
        Matrix sum_matrix(matrix1.rows, matrix1.cols);
        for (int row = 0; row < sum_matrix.rows; row++)
            for (int col = 0; col < sum_matrix.cols; col++)
                sum_matrix.values[row][col] = matrix1.values[row][col] * number;
        return sum_matrix;
    }

};

int main() {

    Matrix A(2, 2);
    A.filling(2);

    Matrix B(2, 2);
    B.filling(2);

    //Matrix C(2, 2);
    Matrix::addition(A, B);

    return 0;
}