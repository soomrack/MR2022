#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <process.h>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
// Ввод начальных данных для вычисления матричной экспоненты
const double EPS = 0.001;
const unsigned int MIN_NUM_CYCLES = 100;

/* Функции для получения случайных значений количества столбцов и строк матриц
 и их элементов */
// Ввод граничных условий для генерации случайных значений
const double RAND_MAX_F = RAND_MAX;
const unsigned int MIN_NUMBER_COLS_ROWS = 2;
const unsigned int MAX_NUMBER_COLS_ROWS = 7;
const double MIN_ELEMENT_VALUE = 0;
const double MAX_ELEMENT_VALUE = 50;

double get_rand() {
    return (double) rand() / RAND_MAX_F;
}

double get_rand_range(const double min, const double max) {
    return get_rand() * (max - min) + min;
}

unsigned int get_rand_range_int(const unsigned int min,
                                 const unsigned int max) {
    return rand() % (max - min + 1) + min;
}

// Структура для образования матрицы
typedef struct Matrix {
    unsigned int cols;
    unsigned int rows;
    double *values;
} Matrix;

void create_random_size_matrix(Matrix *one, Matrix *two) {
    srand(getpid());
    unsigned int number =
            get_rand_range_int(MIN_NUMBER_COLS_ROWS, MAX_NUMBER_COLS_ROWS);
    one->cols = number;
    one->rows = number;
    two->cols = number;
    two->rows = number;
    one->values = (double* ) malloc(one->cols * one->rows
                                       * sizeof(double));
    two->values = (double* ) malloc(two->cols * two->rows
                                       * sizeof(double));
    for (unsigned int k = 0; k < one->cols * one->rows; k++) {
        one->values[k] = (round(get_rand_range
                (MIN_ELEMENT_VALUE, MAX_ELEMENT_VALUE) * 1000)) / 1000;
    }
    for (unsigned int k = 0; k < two->cols * two->rows; k++) {
        two->values[k] = (round(get_rand_range
                (MIN_ELEMENT_VALUE, MAX_ELEMENT_VALUE) * 1000)) / 1000;
    }
}

// Обнуление матрицы результатов при ошибке
Matrix* create_null_matrix(Matrix *res) {
    res->cols = 0;
    res->rows = 0;
    res->values = NULL;
    return res;
}

// Инициализация незаполненной матрицы
Matrix* create_zero_matrix(Matrix *res, const Matrix one, const Matrix two) {
    res->rows = one.rows;
    res->cols = two.cols;
    res->values = (double*) malloc(res->rows * res->cols * sizeof(double));
    for (unsigned int k = 0; k < res->rows * res->cols; k++) {
            res->values[k] = 0;
        }
    return res;
}

// Инициализация единичной матрицы
void create_identity_matrix(Matrix *ident, const Matrix one) {
    ident->cols = one.cols;
    ident->rows = one.cols;
    ident->values = (double* ) malloc(ident->rows * ident->cols * sizeof(double));
    for (unsigned int k = 0; k < ident->cols * ident->rows; k++) {
        ident->values[k] = 0;
    }
    for (unsigned int k = 0; k < ident->cols; k++) {
        ident->values[ident->cols * k + k] = 1;
    }
}

// Вывод матрицы
void print_matrix(const Matrix res) {
    for (unsigned int m = 0; m < res.rows; m++) {
        for (unsigned int n = 0; n < res.cols; n++) {
            printf("%f\t", res.values[n + m * res.cols]);
        }
        printf("\n");
    }
}

// Функция для освобождения памяти
void free_memory(const Matrix matrix) {
    free(matrix.values);
}

// Умножение матрицы на скаляр
Matrix mult_matrix_by_number(Matrix res, const Matrix one, const double a) {
    for (unsigned int k = 0; k < res.cols * res.rows; k++) {
        res.values[k] = one.values[k] * a;
    }
    return res;
}

// Деление матрицы на скаляр
Matrix div_matrix_by_number(Matrix res, const Matrix one, const double a) {
    for (unsigned int k = 0; k < res.cols * res.rows; k++) {
        res.values[k] = one.values[k] / a;
    }
    return res;
}

// Функция для вычисления дополнительного минора матрицы
Matrix matrix_for_minor(const Matrix one, unsigned int rowNumber,
                       unsigned int colNumber) {
    Matrix min;
    rowNumber--;
    colNumber--;
    unsigned int f = 0;
    min.cols = one.cols - 1;
    min.rows = one.rows - 1;
    min.values = (double* ) malloc(min.rows * min.cols * sizeof(double));
    for (unsigned int k = 0; k < min.cols * min.rows; k++) {
        min.values[k] = 0;
    }
    for (unsigned int k = 0; k < one.cols * one.rows; k++) {
        if (((k / one.cols) == rowNumber)
                || (k % one.cols == colNumber)) {
            continue;
        }
        min.values[f] = one.values[k];
        f++;
    }
    free_memory(min);
    return min;
}

// Исправить на деление на число каждый раз
// Вычисление факториала числа
double factorial(const unsigned int b) {
    double fact = 1;
    for (unsigned int k = 1; k < b + 1; k++) {
        fact *= k;
    }
    return fact;
}

void change_rows(Matrix *res, unsigned int m, unsigned int n) {
    m--;
    n--;
    for (unsigned int k = 0; k < res->cols; k++) {
        double change = 0;
        change = res->values[n * res->cols + k];
        res->values[n * res->cols + k] = res->values[m * res->cols + k];
        res->values[m * res->cols + k] = change;
    }
}

// Вывод сообщения об ошибке (сложение, вычитание)
bool is_not_equal_size(const Matrix one, const Matrix two) {
    if ((one.cols != two.cols) || (one.rows != two.rows)) {
        if (one.cols != two.cols) {
            printf("The numbers of columns are different.\n");
        }
        if (one.rows != two.rows) {
            printf("The numbers of rows are different.\n");
        }
        return true;
    }
    return false;
}

// Функция сложения двух матриц
Matrix matrix_add(Matrix *res, const Matrix one, const Matrix two) {
    if (is_not_equal_size(one, two)) {
        res = create_null_matrix(res);
        return *res;
    }
    res = create_zero_matrix(res, one, two);
    for (unsigned int k = 0; k < res->rows * res->cols; k++) {
        res->values[k] = one.values[k] + two.values[k];
    }
    return *res;
}

// Функция для проверки корректности выполнения операции сложения.
bool is_ans_correct_add(const Matrix res, const Matrix one, const Matrix two) {
    printf("\n");
    for (unsigned int k = 0; k < res.cols * res.rows; k++) {
        if (fabs(res.values[k] - (one.values[k] + two.values[k])) < EPS) {
            continue;
        } else {
            return false;
        }
    }
    return true;
}

// Функция вычитания двух матриц
Matrix matrix_sub(Matrix *res, const Matrix one, const Matrix two) {
    if (is_not_equal_size(one, two)) {
        res = create_null_matrix(res);
        return *res;
    }
    res = create_zero_matrix(res, one, two);
    for (unsigned int k = 0; k < res->rows * res->cols; k++) {
        res->values[k] = one.values[k] - two.values[k];
    }
    return *res;
}

// Функция для проверки корректности выполнения операции вычитания
bool is_ans_correct_sub(const Matrix res, const Matrix one, const Matrix
two) {
    printf("\n");
    for (unsigned int k = 0; k < res.cols * res.rows; k++) {
        if (fabs(res.values[k] - (one.values[k] - two.values[k])) < EPS) {
            continue;
        } else {
            return false;
        }
    }
    return true;
}

// Вывод сообщения об ошибке (умножение)
bool is_not_numbers_match(const Matrix one, const Matrix two) {
    if (one.cols != two.rows) {
        printf("The number of columns of the first matrix and the number"
               " of rows of the second matrix don't match.\n");
        return true;
    } else {
        return false;
    }
}

// Функция умножения двух матриц
Matrix matrix_mult(Matrix *res, const Matrix one, const Matrix two) {
    if (is_not_numbers_match(one, two)) {
        res = create_null_matrix(res);
        return *res;
    }
    res = create_zero_matrix(res, one, two);
    for (unsigned int row = 0; row < res->rows; row++) {
        for (unsigned int col = 0; col < res->cols; col++) {
            for (unsigned int k = 0; k < one.cols; k++) {
                res->values[row * res->cols + col] +=
                        one.values[row * one.cols + k] *
                        two.values[col + k * res->cols];
                }
            }
        }
    return *res;
}

/* Функция для проверки корректности выполнения операции умножения путем
умножения полученной матрицы на единичную, в результате чего должна быть
получена идентичная результирующей матрице матрица. */
bool is_ans_correct_mult(const Matrix res, const Matrix one, const Matrix two) {
    printf("\n");
    Matrix ident;
    Matrix check;
    create_identity_matrix(&ident, two);
    create_zero_matrix(&check, one, two);
    check = matrix_mult(&check, res, ident);
    for (unsigned int k = 0; k < res.cols * res.rows; k++) {
        if (fabs(res.values[k] - check.values[k]) < EPS) {
            continue;
        } else {
            return false;
        }
    }
    free_memory(ident);
    free_memory(check);
    return true;
}

// Проверка матрицы на равенство количества строк и столбцов
bool matrix_is_not_square(const Matrix one) {
    if (one.cols != one.rows) {
        printf("The number of columns and the number of rows are different.\n");
        return true;
    } else {
        return false;
    }
}

double alter_matrix(Matrix one, double det) {
    bool flag_one = false;
    bool flag_two = false;
    unsigned int elem = 0;
    unsigned int row = 1;
    for (unsigned int k = 0; k < one.cols * one.rows; k += (one.cols + 1)) {
        if (one.values[k] == 0) {
            flag_one = true;
            elem = k;
            break;
        }
        row++;
    }
    for (unsigned int k = 0; k < one.rows + 1; k++) {
        if ((flag_one)
        && (one.values[(elem - (row - 1) * one.cols) + one.cols * k] != 0)) {
                change_rows(&one, row, (k + 1));
            printf("Altered matrix:\n");
            print_matrix(one);
            printf("\n");
            det *= -1;
            break;
        }  else det = 1;
    }
    return det;
}

/* Функция вычисления определителя матрицы с использованием модификации
метода Гаусса */
double matrix_det_gauss(Matrix *res, const Matrix  one) {
    double det = 1;
    if (matrix_is_not_square(one)) {
        res = create_null_matrix(res);
        det = 0;
        return det;
    }
    det = alter_matrix(one, det);
    create_zero_matrix(res, one, one);
    for (unsigned int k = 0; k < one.cols * one.rows; k++) {
        res->values[k] = one.values[k];
    }
    double *m = malloc(sizeof(double) * one.rows);
    for (unsigned int it = 0; it < (one.cols - 1); it++) {
        m[it] = 0;
        for (unsigned int k = (it + 1); k < one.rows; k++) {
            m[k] = res->values[k * one.cols + it]
                    / res->values[it * one.cols + it];
        }
        for (unsigned int k = (it * one.cols + it); k < one.cols * one.rows;
                                                                        k++) {
            res->values[k] -= m[k / one.cols]
                    * res->values[k % one.cols + it * one.cols];
            if ((k + 1) % one.cols == 0) k += it;
        }
    }
    for (unsigned int k = 0; k < one.rows; k++) {
        det *= res->values[k + k * one.cols];
    }
    free(m);
    return det;
}

// Вывод сообщения об ошибке (обратная матрица)
bool error_inv(const Matrix one) {
    Matrix res;
    create_zero_matrix(&res, one, one);
    if (one.cols != one.rows) {
        printf("The number of columns and the number of rows are different.\n");
        return true;
    } else {
        if (fabs(matrix_det_gauss(&res, one)) == 0) {
            printf("The determinant of the introduced matrix is zero.\n");
            return true;
        } else {
            if ((one.rows * one.cols) == 1) {
                printf("%f\n", (1 / one.values[0]));
                return true;
            } else return false;
        }
    }
}

// Функция вычисления обратной матрицы
Matrix matrix_inv(Matrix *res, const Matrix one) {
    if (error_inv(one)) {
        res = create_null_matrix(res);
        return *res;
    }
    Matrix adj;
    Matrix det;
    Matrix mult;
    create_zero_matrix(&adj, one, one);
    create_zero_matrix(res, one, one);
    det.cols = one.cols - 1;
    det.rows = one.rows - 1;
    det.values = (double *) malloc(det.rows * det.cols * sizeof(double));
    for (unsigned int k = 0; k < det.cols * det.rows; k++) {
        det.values[k] = 0;
    }
    create_zero_matrix(&mult, det, det);
    for (unsigned int k = 0; k < one.cols * one.rows; k++) {
        adj.values[k] = matrix_det_gauss(&det, matrix_for_minor(one,
                                                      (k % one.cols) + 1,
                                                      (k / one.cols) + 1)) *
                                                      pow((-1), k + 2);
    }
    div_matrix_by_number(*res, adj, matrix_det_gauss(res, one));
    free_memory(adj);
    free_memory(det);
    free_memory(mult);
    return *res;
}

/* Проверка корректности вычисления обратной матрицы путем умножения ее на
входную матрицу. Результатом должна быть единичная матрица. */
bool is_ans_correct_inv(const Matrix res, const Matrix one) {
    printf("\n");
    Matrix ident;
    Matrix check;
    create_identity_matrix(&ident, one);
    create_zero_matrix(&check, one, one);
    matrix_mult(&check, res, one);
    for (unsigned int k = 0; k < res.cols * res.rows; k++) {
        if (((fabs(check.values[k])) - ident.values[k]) < EPS) {
            continue;
        } else {
            return false;
        }
    }
    free_memory(ident);
    free_memory(check);
    return true;
}

// Вычисление разности значений матрицы между предыдущей и последующей
// итерациями
bool accuracy_exp(const Matrix res, const Matrix last) {
    bool flag = true;
    for (unsigned int k = 0; k < res.cols * res.rows; k++) {
        if ((flag == true) && (fabs(res.values[k] - last.values[k])) > EPS) {
            flag = true;
        } else flag = false;
    }
    return flag;
}

// Функция для вычисления матричной экспоненты.
Matrix matrix_exp(Matrix *res, const Matrix one) {
    if (matrix_is_not_square(one)) {
        res = create_null_matrix(res);
        return *res;
    }
    Matrix power;
    Matrix last;
    create_identity_matrix(res, one);
    create_identity_matrix(&power, one);
    create_zero_matrix(&last, one, one);
    unsigned int k = 1;
    while ((accuracy_exp(*res, last)) || (k < MIN_NUM_CYCLES)) {
        Matrix division;
        create_zero_matrix(&division, one, one);
        last = *res;
        matrix_mult(&power, power, one);
        matrix_add(res, *res, div_matrix_by_number(division, power,
                                                   factorial(k)));
        k++;
        free_memory(division);
    }
    free_memory(power);
    free_memory(last);
    return *res;
}

/* Проверка корректности выполнения операции взятия матричной экспоненты
путем умножения матричной экспоненты от матрицы с инвертированными элементами
на полученную в результате выполнения программы. Результатом должна быть
единичная матрица. Выполняется с заданной точностью. */
bool is_ans_correct_exp(const Matrix res, const Matrix one) {
    printf("\n");
    Matrix ident;
    Matrix check;
    create_identity_matrix(&ident, one);
    create_zero_matrix(&check, one, one);
    matrix_mult(&check, res,
                matrix_exp(&check, mult_matrix_by_number(check, one, -1)));
    for (unsigned int k = 0; k < res.cols * res.rows; k++) {
        if ((fabs(check.values[k] - ident.values[k])) < EPS * 2) {
            continue;
        } else {
            return false;
        }
    }
    free_memory(ident);
    free_memory(check);
    return true;
}

#pragma clang diagnostic pop