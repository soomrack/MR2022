#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <math.h>

struct Matrix{
    double *values;
    int rows;
    int cols;
};
typedef struct Matrix Matrix;
Matrix matrix_1, matrix_2, adde, subt, tran, subl;

void m_rows_cols(Matrix *matrix) {
    scanf("%d", &matrix->rows);
    scanf("%d", &matrix->cols);
}

Matrix m_setsize(int rows, int cols) {
    Matrix matrix;
    matrix.cols = cols;
    matrix.rows = rows;
    int n_values = matrix.cols * matrix.rows;
    matrix.values = malloc(sizeof(double) * n_values);
    return matrix;
}

void m_init(Matrix *matrix) {
    for (int i = 0; i < matrix -> cols * matrix -> rows; i++)
        matrix->values[i] = i;
}

void m_output(const Matrix matrix) {
    for (int i = 0; i < matrix.rows; i++) {
        printf("\n");
        for (int j = 0; j < matrix.cols; j++)
            printf("%f ", matrix.values[i * matrix.cols + j]);
    }
    printf("\n");
}

Matrix addition(Matrix matr1, Matrix matr2) {
    if ((matr1.cols == matr2.cols) && (matr1.rows == matr2.rows)) {
        Matrix resultmatrix = m_setsize(matr1.rows, matr2.cols);
        resultmatrix.values = malloc(sizeof(double) * matr1.cols * matr2.rows);
        for (int i = 0; i < matr1.cols * matr1.rows; i++) {
            resultmatrix.values[i] = matr1.values[i] + matr2.values[i];
        }
        return resultmatrix;
    } else {
        printf("imp");
        exit(EXIT_FAILURE);
    }
}

Matrix subtraction(Matrix matr1, Matrix matr2) {
    if ((matr1.cols == matr2.cols) && (matr1.rows == matr2.rows)) {
        Matrix resultmatrix = m_setsize(matr1.rows, matr2.cols);
        resultmatrix.values = malloc(sizeof(double) * matr1.cols * matr2.rows);
        for (int i = 0; i < matr1.cols * matr1.rows; i++) {
            resultmatrix.values[i] = matr1.values[i] - matr2.values[i];
        }
        return resultmatrix;
    } else {
        printf("imp");
        exit(EXIT_FAILURE);
    }
}

void transposition_out(Matrix matr) {
    Matrix resultmatrix = m_setsize(matr.rows, matr.cols);
    resultmatrix.values = malloc(sizeof(double) * matr.rows * matr.cols);
    for(int i = 0; i < matr.cols; i++) {
        printf("\n");
        for(int j =0; j < matr.rows; j++) {
            resultmatrix.values[i * matr.rows +j] = matr.values[j * matr.cols + i];
            printf("%f ", resultmatrix.values[i * matr.rows +j]);
        }
    }
}

Matrix transposition(Matrix matr) {
    Matrix resultmatrix = m_setsize(matr.rows, matr.cols);
    resultmatrix.values = malloc(sizeof(double) * matr.rows * matr.cols);
    for(int i = 0; i < matr.cols; i++) {
        for(int j =0; j < matr.rows; j++) {
            resultmatrix.values[i * matr.rows +j] = matr.values[j * matr.cols + i];
        }
    }
    return resultmatrix;
}

Matrix sublimation(Matrix matrix1, Matrix matrix2) {
    if (matrix1.cols == matrix2.rows) {
        Matrix resultmatrix = m_setsize(matrix1.rows, matrix2.cols);
        resultmatrix.values = malloc(sizeof(double) * matrix1.rows * matrix2.cols);
        for (int i = 0; i < matrix1.rows; i++) {
            for (int j = 0; j < matrix2.cols; j++) {
                double temp = 0.00;
                for (int k = 0; k < matrix1.cols; k++) {
                    temp += matrix1.values[i * matrix1.cols + k] * matrix2.values[k * matrix2.cols + j];
                }
                resultmatrix.values[i * matrix2.cols + j] = temp;
            }
        }
        return resultmatrix;
    }
    else {
        printf("imp");
        exit(EXIT_FAILURE);
    }
}

double det(const Matrix matrix) {
    if (matrix.cols != matrix.rows) {
        printf("Operation is impossible. Matrix should be square");
        exit(1);
    }
    double result = 0;
    int n = matrix.cols;
    if (n == 1) {
        result = matrix.values[0];
    }
    else {
        for (int row = 0; row < n; ++row) {
            int col = 0;
            Matrix submatrix = m_setsize(n - 1, n - 1);
            int row_offset = 0;
            int col_offset = 0;
            for (int sub_row = 0; sub_row < n - 1; ++sub_row) {
                for (int sub_col = 0; sub_col < n - 1; ++sub_col) {
                    if (sub_row == row) { row_offset = 1; }
                    if (sub_col == col) { col_offset = 1; }
                    submatrix.values[sub_row * (n - 1) + sub_col] = matrix.values[(sub_row + row_offset) * n + (sub_col + col_offset)];
                }
            }
            result += pow(-1, row + col) * matrix.values[row * n + col] * det(submatrix);
        }
    }
    return result;
}

int main() {
    m_rows_cols(&matrix_1);
    matrix_1 = m_setsize(matrix_1.rows, matrix_1.cols);
    m_init(&matrix_1);
    m_output(matrix_1);

    m_rows_cols(&matrix_2);
    matrix_2 = m_setsize(matrix_2.rows, matrix_2.cols);
    m_init(&matrix_2);
    m_output(matrix_2);

    subl = sublimation(matrix_1, matrix_2);
    m_output(subl);
    //adde = addition(matrix_1, matrix_2);
    //m_output(adde);

    //subt = subtraction(matrix_1, matrix_2);
    //m_output(subt);

    //transposition(matrix_1);
    double dete;
    dete = det(matrix_1);
    printf("%f", dete);
}