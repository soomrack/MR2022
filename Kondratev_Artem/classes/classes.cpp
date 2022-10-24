#include <iostream>
#include <cmath>
#include <cstdint>

#define EPSILON 0.001


class Matrix {

    uint64_t rows;
    uint64_t cols;
    double **values;

public:
    Matrix(uint64_t init_rows, uint64_t init_cols){
        if(init_rows > 0 and init_cols > 0) {
            rows = init_rows;
            cols = init_cols;
            values = (double **) malloc(rows * sizeof(double *) + rows * cols * sizeof(double));
            auto *start = (double *) ((char *) values + rows * sizeof(double *));
            for (uint64_t row = 0; row < rows; row++)
                values[row] = start + row * cols;
        }
    }

    void filling(double number) {
        for(int row = 0; row < rows; row++)
            for(int col = 0; col < cols; col++)
                values[row][col] = number;
    }

    void output() {
        for(int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++)
                std::cout << values[row][col] << "  ";
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    void free_memory() {
        free(values);
        rows = 0;
        cols = 0;
    }

    int are_row_col_zero() const {
        return (int)(rows + cols);
    }

    static Matrix addition(Matrix matrix1, Matrix matrix2) {
        if(matrix1.rows != matrix2.rows or matrix1.cols != matrix2.cols or
        matrix1.are_row_col_zero() == 0 or matrix2.are_row_col_zero() == 0) {
            Matrix error(0, 0);
            return error;
        }
        Matrix sum_matrix(matrix1.rows, matrix1.cols);
        for(int row = 0; row < sum_matrix.rows; row++)
            for(int col = 0; col < sum_matrix.cols; col++)
                sum_matrix.values[row][col] = matrix1.values[row][col] + matrix2.values[row][col];
        return sum_matrix;
    }

    static Matrix addition(Matrix matrix1, double number) {
        if(matrix1.are_row_col_zero() == 0) {
            Matrix error(0, 0);
            return error;
        }
        Matrix sum_matrix(matrix1.rows, matrix1.cols);
        for(int row = 0; row < sum_matrix.rows; row++)
            for(int col = 0; col < sum_matrix.cols; col++)
                sum_matrix.values[row][col] = matrix1.values[row][col] + number;
        return sum_matrix;
    }

    static Matrix subtraction(Matrix matrix1, Matrix matrix2) {
        if(matrix1.rows != matrix2.rows or matrix1.cols != matrix2.cols or matrix1.rows == 0 or matrix1.rows) {
            Matrix error(0, 0);
            return error;
        }
        Matrix sum_matrix(matrix1.rows, matrix1.cols);
        for(int row = 0; row < sum_matrix.rows; row++)
            for(int col = 0; col < sum_matrix.cols; col++)
                sum_matrix.values[row][col] = matrix1.values[row][col] - matrix2.values[row][col];
        return sum_matrix;
    }

    static Matrix multiplication(Matrix matrix1, Matrix matrix2) {
        if(matrix1.cols != matrix2.rows){
            Matrix error(0, 0);
            return error;
        }
        Matrix multiplied_matrix(matrix1.rows, matrix2.cols);
        for(int row = 0; row < multiplied_matrix.rows; row++)
            for(int col = 0; col < multiplied_matrix.cols; col++) {
                multiplied_matrix.values[row][col] = 0;
                for (int k = 0; k < matrix1.cols; k++)
                    multiplied_matrix.values[row][col] += matrix1.values[row][k] * matrix2.values[k][col];
            }
        return multiplied_matrix;
    }

    static Matrix multiplication(Matrix matrix1, double number) {
        if(matrix1.are_row_col_zero() == 0) {
            Matrix error(0, 0);
            return error;
        }
        Matrix sum_matrix(matrix1.rows, matrix1.cols);
        for(int row = 0; row < sum_matrix.rows; row++)
            for(int col = 0; col < sum_matrix.cols; col++)
                sum_matrix.values[row][col] = matrix1.values[row][col] * number;
        return sum_matrix;
    }

};




int main() {

    Matrix A(0, 2);
    //A.output();

    Matrix B(2, 2);
    B.filling(2);
    //B.output();

    Matrix C = Matrix::addition(A, B);
    C.output();

    /*C = Matrix::subtraction(A, B);
    C.output();

    C = Matrix::multiplication(A, B);
    C.output();*/

    return 0;

}