#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Структура для образования матрицы
typedef struct Matrix {
    unsigned int cols;
    unsigned int rows;
    double *values;
} Matrix;

// Вывод матрицы
void print_matrix (const Matrix res) {
    for (int m = 0; m < res.rows; m++) {
        for (int n = 0; n < res.cols; n++) {
            printf("%f\t", res.values[n + m * res.cols]);
        }
        printf("\n");
    }
}

// Выход из программы при ошибке
void exit_matrix (Matrix res) {
    res.cols = 0;
    res.rows = 0;
    res.values = NULL;
    exit(1);
}

// Функция сложения двух матриц
void add_matrix (Matrix *res, const Matrix one, const Matrix two) {
    if ((one.cols != two.cols) || (one.rows != two.rows)) {
        if (one.cols != two.cols) {
            printf("The numbers of columns are different\n");
        }
        if (one.rows != two.rows) {
            printf("The numbers of rows are different\n");
        }
        exit_matrix(*res);
    }
    res->cols = one.cols;
    res->rows = one.rows;
    res->values = (double* ) malloc(res->rows * res->cols * sizeof(double));
    for (int k = 0; k < res->rows * res->cols; k++) {
        res->values[k] = one.values[k] + two.values[k];
    }
    print_matrix(*res);
}

// Функция вычитания двух матриц
void sub_matrix (Matrix *res, const Matrix one, const Matrix two) {
    if ((one.cols != two.cols) || (one.rows != two.rows)) {
        if (one.cols != two.cols) {
            printf("The numbers of columns are different\n");
        }
        if (one.rows != two.rows) {
            printf("The numbers of rows are different\n");
        }
        exit_matrix(*res);
    }
    res->cols = one.cols;
    res->rows = one.rows;
    res->values = (double* ) malloc(res->rows * res->cols * sizeof(double));
    for (int k = 0; k < res->rows * res->cols; k++) {
        res->values[k] = one.values[k] - two.values[k];
    }
    print_matrix(*res);
}

// Функция умножения двух матриц
void mult_matrix(Matrix *res, const Matrix one, const Matrix two) {
    if (one.cols != two.rows) {
        printf("The number of columns of the first matrix and the number"
               " of rows of the second matrix don't match\n");
        exit_matrix(*res);
    }
    res->cols = two.cols;
    res->rows = one.rows;
    res->values = (double* ) malloc(res->rows * res->cols * sizeof(double));
    for (int k = 0; k < one.rows; k++) {
        for (int m = 0; m < res->rows; m++) {
            for (int n = 0; n < one.cols; n++) {
                res->values[k * res->rows + m] +=
                        one.values[k * one.cols + n] *
                        two.values[m + n * res->cols];
            }
        }
    }
    print_matrix(*res);
}

// Ввод размеров и значений для обеих матриц
void init_matrix_one (Matrix *matrix, const double values_one[1]) {
    matrix->cols = 2;
    matrix->rows = 2;
    matrix->values = (double* ) malloc(matrix->cols * matrix->rows
                                       * sizeof(double));
    for (int k = 0; k < matrix->cols * matrix->rows; k++) {
        matrix->values[k] = values_one[k];
    }
}

void init_matrix_two (Matrix *matrix, const double values_two[1]) {
    matrix->cols = 2;
    matrix->rows = 2;
    matrix->values = (double* ) malloc(matrix->cols * matrix->rows
            * sizeof(double));
    for (int k = 0; k < matrix->cols * matrix->rows; k++) {
        matrix->values[k] = values_two[k];
    }
}

int main() {
    unsigned int operation_choice = 1;
    // Выбор арифметической операции, производимой с матрицами, где
        // 1 - Операция сложения матриц
        // 2 - Операция вычитания матриц
        // 3 - Операция умножения матриц
        // 4 -
    double values_one[4] = {5, 6,
                            7, 8};
    double values_two[4] = {9, 10,
                            11, 12};
    Matrix first;
    Matrix second;
    init_matrix_one(&first, values_one);
    init_matrix_two(&second, values_two);
    Matrix result;
// Уточнить вывод ошибки при вводе нулевых матриц
    switch (operation_choice) {
        case 1: {
            add_matrix(&result, first, second);
            break;
            }
        case 2: {
            sub_matrix(&result, first, second);
            break;
        }
        case 3: {
            mult_matrix(&result, first, second);
            break;
        }
//        case 4: {
//            matrix_minor(first, 2, 3);
//            det_matrix_minor(&result, first);
//            break;
//        }
        default: {
            printf("Chosen number of operation does not allowed");
            exit_matrix(result);
        }
    }
    free(first.values);
    free(second.values);
    free(result.values);
    return 0;
}