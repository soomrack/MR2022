#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct Matrix {
    unsigned int cols;
    unsigned int rows;
    double* values;
}Matrix;
const Matrix ZERO = { 0, 0, NULL };

Matrix create_matrix(const unsigned int cols, const unsigned int rows) {
    Matrix matrix;
    matrix.cols = cols;
    matrix.rows = rows;
    unsigned int n_values = matrix.cols * matrix.rows;
    matrix.values = malloc(n_values * sizeof(double));
    return matrix;
}

void fill_matrix(Matrix* matrix) {
    for (unsigned int index = 0; index < matrix->cols * matrix->rows; ++index) {
        matrix->values[index] = (int)rand();
    }
}

void print_matrix(const Matrix matrix) {
       for (unsigned int row = 0; row < matrix.rows; ++row) {
        for (unsigned int col = 0; col < matrix.cols; ++col) {
            printf("%.2f ", matrix.values[row * matrix.cols + col]);
        }
        printf("\n");
    }
    printf("\n");
}
void errorofsize(char* operation_name, char* error) {
    printf("%s is impossible. %s\n", operation_name, error);
}
Matrix empty={0,0,NULL};

void free_matrix(Matrix* matrix) {
    free(matrix->values);
}

Matrix add_matrices(const Matrix matrix1, const Matrix matrix2) {
    if (matrix1.rows != matrix2.rows || matrix1.cols != matrix2.cols) {
        errorofsize("Addition", "Matrixes should have equal sizes");
        return empty;
    }
    Matrix result = create_matrix(matrix1.cols, matrix1.rows);
    unsigned int n_values = result.cols * result.rows;
    for (unsigned int index = 0; index < n_values; ++index) {
        result.values[index] = matrix1.values[index] + matrix2.values[index];
    }
    return result;
}

Matrix subtruct_matrices(const Matrix matrix1, const Matrix matrix2) {
    if (matrix1.rows != matrix2.rows && matrix1.cols != matrix2.cols) {
        errorofsize("Subtruction", "Matrixes should have equal sizes");
        return empty;
    }
    Matrix result = create_matrix(matrix1.cols, matrix1.rows);
    unsigned int n_values = result.cols * result.rows;
    for (unsigned int index = 0; index < n_values; ++index) {
        result.values[index] = matrix1.values[index] - matrix2.values[index];
    }
    return result;
}

Matrix multiply_on_number(const Matrix matrix, double number) {
    Matrix result = create_matrix(matrix.cols, matrix.rows);
    unsigned int n_values = result.cols * result.rows;
    for (unsigned int index = 0; index < n_values; ++index) {
        result.values[index] = matrix.values[index] * number;
    }
    return result;
}
Matrix multiply_matrices(const Matrix matrix1, const Matrix matrix2) {
    if (matrix1.cols != matrix2.rows) {
        errorofsize("Multiplication", "Matrixes should have certain sizes");
        return ZERO;
    }
    unsigned int n_cols = matrix2.cols;
    unsigned int n_rows = matrix1.rows;
    Matrix result = create_matrix(n_cols, n_rows);
    for (unsigned int row = 0; row < n_rows; ++row) {
        for (unsigned int col = 0; col < n_cols; ++col) {
            double summa = 0.0;
            for (unsigned int k = 0; k < matrix1.cols; ++k) {
                summa +=
                        matrix1.values[row * matrix1.cols + k] *
                        matrix2.values[k * matrix2.cols + col];
            }
            result.values[row * n_cols + col] = summa;
        }
    }
    return result;
}

double det_matrix(const Matrix matrix) {
    if (matrix.cols != matrix.rows) {
        errorofsize("Getting determinant", "Matrix should be square");
        return 0.;
    }
    double result = 0;
    unsigned int n = matrix.cols;
    if (n == 1) {
        result = matrix.values[0];
        return result;
    }
    for (unsigned int row = 0; row < n; ++row) {
        unsigned int col = 0;
        Matrix submatrix = create_matrix(n - 1, n - 1);
        unsigned int row_offset = 0;
        unsigned int col_offset = 0;
        for (unsigned int sub_row = 0; sub_row < n - 1; ++sub_row) {
            for (unsigned int sub_col = 0; sub_col < n - 1; ++sub_col) {
                if (sub_row == row) { row_offset = 1; }
                if (sub_col == col) { col_offset = 1; }
                submatrix.values[sub_row * (n - 1) + sub_col] =
                        matrix.values[(sub_row + row_offset) * n + (sub_col + col_offset)];
            }
        }
        result += pow(-1, row + col) * matrix.values[row * n + col] * det_matrix(submatrix);
        free_matrix(&submatrix);
    }
    return result;
}

Matrix transpose(const Matrix matrix) {
    Matrix result = create_matrix(matrix.rows, matrix.cols);
    for (unsigned int row = 0; row < result.rows; ++row) {
        for (unsigned int col = 0; col < result.cols; ++col) {
            result.values[row * result.cols + col] = matrix.values[col * result.rows + row];
        }
    }
    return result;
}
Matrix unit(unsigned int dimention) {
    Matrix result = create_matrix(dimention, dimention);
    for (unsigned int row = 0; row < result.rows; ++row) {
        for (unsigned int col = 0; col < result.cols; ++col) {
            result.values[row * result.cols + col] = (row == col) ? 1. : 0.;
        }
    }
    return result;
}
Matrix copy(const Matrix matrix) {
    Matrix result = create_matrix(matrix.cols, matrix.rows);
    for (unsigned int index = 0; index < matrix.cols * matrix.rows; ++index) {
        result.values[index] = matrix.values[index];
    }
    return result;
}
Matrix expo(const Matrix matrix, int accuracy) {
    if (matrix.cols != matrix.rows) {
        errorofsize("Exp", "Matrix should be square");
        return ZERO;
    }
    Matrix result_, pow_, multiplied;
    Matrix result = unit(matrix.rows);
    Matrix pow = unit(matrix.rows);
    int factorial = 1;
    for (int acc = 1; acc <= accuracy; ++acc) {
        factorial *= acc;
        pow_ = multiply_matrices(pow, matrix);
        pow = copy(pow_);
        free_matrix(&pow_);
        multiplied = multiply_on_number(pow, 1. / factorial);
        result_ = add_matrices(result, multiplied);
        result = copy(result_);
        free_matrix(&result_);
        free_matrix(&multiplied);
    }
    free_matrix(&pow);
    return result;
}

int main() {
    Matrix mat1, mat2;

    printf("\nFirst martix\n");
    mat1 = create_matrix(3, 3);
    fill_matrix(&mat1);
    print_matrix(mat1);

    printf("Second matrix\n");
    mat2 = create_matrix(3, 3);
    fill_matrix(&mat2);
    print_matrix(mat2);

    printf("Sum of matrices\n");
    Matrix addition;
    addition = add_matrices(mat1, mat2);
    print_matrix(addition);
    free_matrix(&addition);

    printf("Sub of matrices\n");
    Matrix subtruction;
    subtruction = subtruct_matrices(mat1, mat2);
    print_matrix(subtruction);
    free_matrix(&subtruction);

    printf("Multiplying the first matrix by a number\n");
    Matrix multiplication1;
    multiplication1 = multiply_on_number(mat1, 5.);
    print_matrix(multiplication1);
    free_matrix(&multiplication1);

    printf("Multiplying the second matrix by a number\n");
    Matrix multiplication2;
    multiplication2 = multiply_on_number(mat2, 5.);
    print_matrix(multiplication2);
    free_matrix(&multiplication2);

    printf("Multiplying the first matrix by a second martix\n");
    Matrix multiplication_matrices;
    multiplication_matrices = multiply_matrices(mat1, mat2);
    print_matrix(multiplication_matrices);
    free_matrix(&multiplication_matrices);

    double determinant;
    printf("Determinant of the first matrix\n");
    determinant = det_matrix(mat1);
    printf("%.2f\n\n", determinant);

    printf("Determinant of the second matrix\n");
    determinant = det_matrix(mat2);
    printf("%.2f\n\n", determinant);

    printf("Transponated first matrix\n");
    Matrix transpose1;
    transpose1 = transpose(mat1);
    print_matrix(transpose1);
    free_matrix(&transpose1);

    printf("Transponated second matrix\n");
    Matrix transpose2;
    transpose2 = transpose(mat2);
    print_matrix(transpose2);
    free_matrix(&transpose2);

    printf("Exponent of the first matrix\n");
    Matrix exponenta;
    exponenta = expo(mat1, 3);
    print_matrix(exponenta);
    free_matrix(&exponenta);
    free_matrix(&mat1);
    free_matrix(&mat2);

}
