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
        rows = init_rows;
        cols = init_cols;
        values = (double**)malloc(rows * sizeof(double*) + rows * cols * sizeof(double));
        auto* start = (double*)((char*)values + rows * sizeof(double*));
        for(uint64_t row_cells = 0; row_cells < rows; row_cells++)
            values[row_cells] = start + row_cells*cols;
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

    static Matrix addition(Matrix matrix1, Matrix matrix2) {
        if(matrix1.rows != matrix2.rows or matrix1.cols != matrix2.cols) {
            Matrix sum_matrix(0, 0);
            return sum_matrix;
        }

        Matrix sum_matrix(matrix1.rows, matrix1.cols);
        for(int row = 0; row < sum_matrix.rows; row++)
            for(int col = 0; col < sum_matrix.cols; col++)
                sum_matrix.values[row][col] = matrix1.values[row][col] + matrix2.values[row][col];
        return sum_matrix;
    }



};




int main() {

    Matrix A(2, 2);
    A.filling(2);
    A.output();

    Matrix B(2, 2);
    B.filling(2);
    B.output();

    Matrix C = Matrix::addition(A, B);
    C.output();


    return 0;

}