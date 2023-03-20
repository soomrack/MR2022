#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Matrix {
    unsigned int cols;
    unsigned int rows;
    double* values;
}Matrix;

const Matrix EMPTY = { 0, 0, NULL };

Matrix init_matrix(const unsigned int cols, const unsigned int rows) {  // создание новой матрицы с выделением памяти
    Matrix matrix;
    matrix.cols = cols;
    matrix.rows = rows;
    unsigned int n_values = matrix.cols * matrix.rows;
    matrix.values = malloc(n_values * sizeof(double));
    return matrix;
}

void set_matrix_values(Matrix* matrix) {  // заполнение матрицы рандомными числами
    for (unsigned int index = 0; index < matrix -> cols * matrix -> rows; ++index) {
        matrix -> values[index] = (double)rand();
    }
}

void error_size(char* operation_name, char* error) {  // выведение заданной ошибки
    printf("%s is impossible. %s\n", operation_name, error);
}

int is_null(const Matrix matrix) {  // проверка: нулевая ли матрица
    return matrix.cols == 0 && matrix.rows == 0 ?  1 : 0;
}

void print_matrix(const Matrix matrix) {  // вывести матрицу в консоль
    if (is_null(matrix)) {
        printf("The matrix doesn't exist\n\n");
        return;
    }
    for (unsigned int row = 0; row < matrix.rows; ++row) {
        for (unsigned int col = 0; col < matrix.cols; ++col) {
            printf("%.2f ", matrix.values[row * matrix.cols + col]);
        }
        printf("\n");
    }
    printf("\n");
}

void free_matrix(Matrix* matrix) {  // очистить память
    free(matrix->values);
}



Matrix add(const Matrix matrix1, const Matrix matrix2) {  // сумма матриц
    if (matrix1.rows != matrix2.rows || matrix1.cols != matrix2.cols) {
        error_size("Addition", "Matrixes should have equal sizes");
        return EMPTY;
    }
    Matrix result = init_matrix(matrix1.cols, matrix1.rows);
    unsigned int n_values = result.cols * result.rows;
    for (unsigned int index = 0; index < n_values; ++index) {
        result.values[index] = matrix1.values[index] + matrix2.values[index];
    }
    return result;
}

Matrix substruct(const Matrix matrix1, const Matrix matrix2) {  // разность матриц
    if (matrix1.rows != matrix2.rows && matrix1.cols != matrix2.cols) {
        error_size("Substruction", "Matrixes should have equal sizes");
        return EMPTY;
    }
    Matrix result = init_matrix(matrix1.cols, matrix1.rows);
    unsigned int n_values = result.cols * result.rows;
    for (unsigned int index = 0; index < n_values; ++index) {
        result.values[index] = matrix1.values[index] - matrix2.values[index];
    }
    return result;
}

Matrix multiply_by_double(const Matrix matrix, double number) {  // умножение матрицы на число
    Matrix result = init_matrix(matrix.cols, matrix.rows);
    unsigned int n_values = result.cols * result.rows;
    for (unsigned int index = 0; index < n_values; ++index) {
        result.values[index] = matrix.values[index] * number;
    }
    return result;
}

Matrix multiply(const Matrix matrix1, const Matrix matrix2) {  // умножение матрицы на матрицу
    if (matrix1.cols != matrix2.rows) {
        error_size("Multiplication", "Matrixes should have certain sizes");
        return EMPTY;
    }
    unsigned int n_cols = matrix2.cols;
    unsigned int n_rows = matrix1.rows;
    Matrix result = init_matrix(n_cols, n_rows);
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

double det(const Matrix matrix) {  // определитель матрицы
    if (matrix.cols != matrix.rows) {
        error_size("Getting determinant", "Matrix should be square");
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
        Matrix submatrix = init_matrix(n - 1, n - 1);
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
        result += pow(-1, row + col) * matrix.values[row * n + col] * det(submatrix);
        free_matrix(&submatrix);
    }
    return result;
}

Matrix transpose(const Matrix matrix) {  // транспонированная матрица
    Matrix result = init_matrix(matrix.rows, matrix.cols);
    for (unsigned int row = 0; row < result.rows; ++row) {
        for (unsigned int col = 0; col < result.cols; ++col) {
            result.values[row * result.cols + col] = matrix.values[col * result.rows + row];
        }
    }
    return result;
}

Matrix identity(unsigned int dimention) {  // единичная матрица
    Matrix result = init_matrix(dimention, dimention);
    for (unsigned int row = 0; row < result.rows; ++row) {
        for (unsigned int col = 0; col < result.cols; ++col) {
            result.values[row * result.cols + col] = (row == col) ? 1. : 0.;
        }
    }
    return result;
}

Matrix invertible(const Matrix matrix) {  // обратная матрица
    if (matrix.cols != matrix.rows) {
        error_size("Getting invertible matrix", "Matrix should be square");
        return EMPTY;
    }
    Matrix transponent = transpose(matrix);
    Matrix result = init_matrix(matrix.cols, matrix.rows);
    for (unsigned int row = 0; row < transponent.rows; ++row) {
        for (unsigned int col = 0; col < transponent.cols; ++col) {
            Matrix submatrix = init_matrix(transponent.cols - 1, transponent.rows - 1);
            unsigned int row_offset = 0;
            unsigned int col_offset = 0;
            for (unsigned int sub_row = 0; sub_row < submatrix.rows; ++sub_row) {
                if (row == sub_row) { row_offset = 1; }
                for (unsigned int sub_col = 0; sub_col < submatrix.cols; ++sub_col) {
                    if (col == sub_col) { col_offset = 1; }
                    submatrix.values[sub_row * (transponent.cols - 1) + sub_col] =
                            transponent.values[(sub_row + row_offset) * transponent.cols + (sub_col + col_offset)];
                }
            }
            result.values[row * matrix.cols + col] = pow(-1, row + col) * det(submatrix);
            free(submatrix.values);
        }
    }
    free(transponent.values);
    Matrix multiplied_result = multiply_by_double(result, 1 / det(result));
    free(result.values);
    return multiplied_result;
}

Matrix copy(const Matrix matrix) {  // копирование матрицы
    Matrix result = init_matrix(matrix.cols, matrix.rows);
    for (unsigned int index = 0; index < matrix.cols * matrix.rows; ++index) {
        result.values[index] = matrix.values[index];
    }
    return result;
}

Matrix expo(const Matrix matrix, int accuracy) {  // экпонента
    if (matrix.cols != matrix.rows) {
        error_size("Exp", "Matrix should be square");
        return EMPTY;
    }
    Matrix new_result, new_powered, multiplied;
    Matrix result = identity(matrix.rows);
    Matrix powered = matrix;
    int factorial = 1;
    for (int acc = 1; acc <= accuracy; ++acc) {
        factorial *= acc;

        new_powered = multiply(powered, matrix);
        powered = copy(new_powered);
        free_matrix(&new_powered);

        multiplied = multiply_by_double(powered, 1. / factorial);

        new_result = add(result, multiplied);
        result = copy(new_result);
        free_matrix(&new_result);

        free_matrix(&multiplied);
    }
    free_matrix(&powered);
    return result;
}

int main() {
    Matrix m1, m2;

    m1 = init_matrix(3, 3);
    set_matrix_values(&m1);
    printf("\nMatrix 1\n");
    print_matrix(m1);

    m2 = init_matrix(3, 3);
    set_matrix_values(&m2);
    printf("Matrix 2\n");
    print_matrix(m2);

    Matrix addition;
    addition = add(m1, m2);
    printf("\nMatrix addition\n");
    print_matrix(addition);
    free_matrix(&addition);

    Matrix substruction;
    substruction = substruct(m1, m2);
    printf("Matrix substruction\n");
    print_matrix(substruction);
    free_matrix(&substruction);

    double determinant;
    determinant = det(m1);
    printf("Matrix 1 determinant\n");
    printf("%.2f\n\n", determinant);
    determinant = det(m2);
    printf("Matrix 2 determinant\n");
    printf("%.2f\n\n", determinant);

    Matrix multiplication1;
    multiplication1 = multiply_by_double(m1, 5.);
    printf("Matrix 1 multiplication\n");
    print_matrix(multiplication1);
    free_matrix(&multiplication1);

    Matrix multiplication2;
    multiplication2 = multiply(m1, m2);
    printf("Matrix 1 and 2 multiplication\n");
    print_matrix(multiplication2);
    free_matrix(&multiplication2);

    Matrix trans;
    trans = transpose(m1);
    printf("Matrix 1 transposed\n");
    print_matrix(trans);
    free_matrix(&trans);

    Matrix invert;
    invert = invertible(m1);
    printf("Matrix 1 inverted\n");
    print_matrix(invert);
    free_matrix(&invert);

    Matrix exponenta;
    exponenta = expo(m1, 3);
    printf("Matrix 1 exponential\n");
    print_matrix(exponenta);
    free_matrix(&exponenta);

    free_matrix(&m1);
    free_matrix(&m2);
}
