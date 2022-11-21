#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <process.h>

// Ввод начальных данных для вычисления матричной экспоненты
const double EPS = 0.001;
const unsigned int MIN_NUM_CYCLES = 100;

/* Функции для получения случайных значений количества столбцов и строк матриц
 и их элементов */
// Ввод граничных условий для генерации случайных значений
const double RAND_MAX_F = RAND_MAX;
const unsigned int MIN_NUMBER_COLS_ROWS = 1;
const unsigned int MAX_NUMBER_COLS_ROWS = 7;
const double MIN_ELEMENT_VALUE = 0;
const double MAX_ELEMENT_VALUE = 20;

double get_rand() {
    return (double) rand() / RAND_MAX_F;
}

double get_rand_range (const double min, const double max) {
    return get_rand() * (max - min) + min;
}

unsigned int get_rand_range_int (const unsigned int min,
                                 const unsigned int max) {
    return rand() % (max - min + 1) + min;
}

// Структура для образования матрицы
typedef struct Matrix {
    unsigned int cols;
    unsigned int rows;
    double *values;
} Matrix;

void create_random_matrix (Matrix *one, Matrix *two) {
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
// Ввод размеров и значений для обеих матриц
//void init_matrix (Matrix *matrix, const double values[1]) {
//}

// Обнуление матрицы результатов при ошибке
Matrix* create_null_matrix (Matrix *res) {
    res->cols = 0;
    res->rows = 0;
    res->values = NULL;
    return res;
}

// Инициализация пустой матрицы
Matrix* create_empty_matrix (Matrix *res, const Matrix one, const Matrix two) {
    res->rows = one.rows;
    res->cols = two.cols;
    res->values = (double* ) malloc(res->rows * res->cols * sizeof(double));
    for (unsigned int row = 0; row < res->rows; row++) {
        for (unsigned int col = 0; col < res->cols; col++) {
            res->values[row * res->cols + col] = 0;
        }
    }
    return res;
}

// Инициализация единичной матрицы
void create_identity_matrix (Matrix *ident, const Matrix one) {
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
void print_matrix (const Matrix res) {
    for (unsigned int m = 0; m < res.rows; m++) {
        for (unsigned int n = 0; n < res.cols; n++) {
            printf("%f\t", res.values[n + m * res.cols]);
        }
        printf("\n");
    }
}

// Деление матрицы на скаляр
Matrix mult_matrix_by_number (Matrix res, const Matrix one, const double a) {
    for (unsigned int k = 0; k < res.cols * res.rows; k++) {
        res.values[k] = one.values[k] * a;
    }
    return res;
}

// Деление матрицы на скаляр
Matrix div_matrix_by_number (Matrix res, const Matrix one, const double a) {
    for (unsigned int k = 0; k < res.cols * res.rows; k++) {
        res.values[k] = one.values[k] / a;
    }
    return res;
}

// Функция для вычисления дополнительного минора матрицы
Matrix matrix_for_minor (const Matrix one, unsigned int rowNumber,
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
    return min;
}

// Вычисление факториала числа
double factorial (const unsigned int b) {
    double fact = 1;
    for (unsigned int k = 1; k < b + 1; k++) {
        fact *= k;
    }
    return fact;
}

// Вывод сообщения об ошибке (сложение, вычитание)
bool error_add_sub (const Matrix one, const Matrix two) {
    if ((one.cols != two.cols) || (one.rows != two.rows)) {
        if (one.cols != two.cols) {
            printf("The numbers of columns are different.\n");
        }
        if (one.rows != two.rows) {
            printf("The numbers of rows are different.\n");
        }
        return true;
    } else {
        return false;
    }
}

// Функция сложения двух матриц
Matrix matrix_add (Matrix *res, const Matrix one, const Matrix two) {
    if (error_add_sub(one, two)) {
        res = create_null_matrix(res);
    } else {
        res = create_empty_matrix(res, one, two);
        for (unsigned int k = 0; k < res->rows * res->cols; k++) {
            res->values[k] = one.values[k] + two.values[k];
        }
    }
    return *res;
}

// Функция для проверки корректности выполнения операции сложения
void is_ans_correct_add (const Matrix res, const Matrix one, const Matrix two) {
    printf("\n");
    bool flag = true;
    for (unsigned int k = 0; k < res.cols * res.rows; k++) {
        if ((flag == true) &&
            (res.values[k] == one.values[k] + two.values[k])) {
            flag = true;
        } else flag = false;
    }
    if (flag == true) {
        printf("The answer is correct.\n");
    } else {
        printf("The answer is incorrect.\n");
    }
}

// Функция вычитания двух матриц
Matrix matrix_sub (Matrix *res, const Matrix one, const Matrix two) {
    if (error_add_sub(one, two)) {
        res = create_null_matrix(res);
    } else {
        res = create_empty_matrix(res, one, two);
        for (unsigned int k = 0; k < res->rows * res->cols; k++) {
            res->values[k] = one.values[k] - two.values[k];
        }
    }
    return *res;
}

// Функция для проверки корректности выполнения операции вычитания
void is_ans_correct_sub (const Matrix res, const Matrix one, const Matrix two) {
    printf("\n");
    bool flag = true;
    for (unsigned int k = 0; k < res.cols * res.rows; k++) {
        if ((flag == true) &&
            (res.values[k] == one.values[k] - two.values[k])) {
            flag = true;
        } else flag = false;
    }
    if (flag == true) {
        printf("The answer is correct.\n");
    } else {
        printf("The answer is incorrect.\n");
    }
}

// Вывод сообщения об ошибке (умножение)
bool error_mult (const Matrix one, const Matrix two) {
    if (one.cols != two.rows) {
        printf("The number of columns of the first matrix and the number"
               " of rows of the second matrix don't match.\n");
        return true;
    } else {
        return false;
    }
}

// Функция умножения двух матриц
Matrix matrix_mult (Matrix *res, const Matrix one, const Matrix two) {
    if (error_mult(one, two)) {
        res = create_null_matrix(res);
    } else {
        res = create_empty_matrix(res, one, two);
        for (unsigned int row = 0; row < res->rows; row++) {
            for (unsigned int col = 0; col < res->cols; col++) {
                for (unsigned int k = 0; k < one.cols; k++) {
                    res->values[row * res->cols + col] +=
                            one.values[row * one.cols + k] *
                            two.values[col + k * res->cols];
                }
            }
        }
    }
    return *res;
}

/* Функция для проверки корректности выполнения операции умножения путем
умножения полученной матрицы на единичную, в результате чего должна быть
получена идентичная результирующей матрице матрица. */
void is_ans_correct_mult (const Matrix res,
                          const Matrix one, const Matrix two) {
    printf("\n");
    bool flag = true;
    Matrix ident;
    Matrix check;
    create_identity_matrix(&ident, two);
    create_empty_matrix(&check, one, two);
    check = matrix_mult(&check, res, ident);
    for (unsigned int k = 0; k < res.cols * res.rows; k++) {
        if ((flag == true) &&
            (res.values[k] == check.values[k])) {
            flag = true;
        } else flag = false;
    }
    if (flag == true) {
        printf("The answer is correct.\n");
    } else {
        printf("The answer is incorrect.\n");
    }
}

// Вывод сообщения об ошибке (вычисление определителя методом Гаусса)
bool error_det_gauss (const Matrix one) {
    bool flag = false;
    /* Из-за особенностей метода нахождения определителя для матриц с нулевым
    элементом на главной диагонали невозможно */
    for (unsigned int k = 0; k < one.cols * one.rows; k++) {
        if ((!flag) && (one.values[k] == 0)) {
            flag = true;
        }
    }
    if (flag) {
        printf("The main diagonal has zero elements.\n");
        return true;
    } else {
        if (one.cols != one.rows) {
            printf("The number of columns and the number of rows are different.\n");
            return true;
        } else {
            return false;
        }
    }
}

/* Функция вычисления определителя матрицы с использованием модификации
метода Гаусса */
double matrix_det_gauss (Matrix *res, const Matrix  one) {
    double det = 1;
    if (error_det_gauss(one)) {
        res = create_null_matrix(res);
        det = 0;
    } else {
        create_empty_matrix(res, one, one);
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
            for (unsigned int k = (it * one.cols + it);
            k < one.cols * one.rows; k++) {
                res->values[k] -= m[k / one.cols]
                                  * res->values[k % one.cols + it * one.cols];
                if ((k + 1) % one.cols == 0) k += it;
            }
        }
        for (unsigned int k = 0; k < one.rows; k++) {
            det *= res->values[k + k * one.cols];
        }
    }
    return det;
}

/*
// Вывод сообщения об ошибке (вычисление определителя с помощью доп. миноров)
// (Заготовка)
bool error_det_minor (const Matrix one) {
    if (one.cols != one.rows) {
        printf("The number of columns and the number of rows are different.\n");
        return true;
    } else {
        return false;
    }
}

// Функция нахождения определителя обеих матриц через дополнительные миноры
// (Заготовка)
double det_matrix_minor (Matrix *min, const Matrix one) {
    double det = 0;
    return det;
}

// Проверка корректности вычисления определителя матрицы путем сравнения
// результата двух способов (через дополнительные миноры и метод Гаусса).
// (Заготовка)
void is_ans_correct_det (const double det, const Matrix one, unsigned int
method) {
    printf("\n");
    bool flag = true;
    Matrix res;
    create_empty_matrix(&res, one, one);
    if (method == 4) {
            if (det != det_matrix_minor(&res, one)) flag = false;
        } else {
        if (method == 5) {
            if (det != matrix_det_gauss(&res, one)) flag = false;
        }
    }
    if (flag == true) {
        printf("The answer is correct.");
    } else {
        printf("The answer is incorrect.");
    }
} */

// Вывод сообщения об ошибке (обратная матрица)
bool error_inv (const Matrix one) {
    Matrix res;
    create_empty_matrix(&res, one, one);
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
Matrix matrix_inv (Matrix *res, const Matrix one) {
    if (error_inv(one)) {
        res = create_null_matrix(res);
    } else {
        Matrix adj;
        Matrix det;
        Matrix mult;
        create_empty_matrix(&adj, one, one);
        create_empty_matrix(res, one, one);
        det.cols = one.cols - 1;
        det.rows = one.rows - 1;
        det.values = (double *) malloc(det.rows * det.cols * sizeof(double));
        for (unsigned int k = 0; k < det.cols * det.rows; k++) {
            det.values[k] = 0;
        }
        create_empty_matrix(&mult, det, det);
        for (unsigned int k = 0; k < one.cols * one.rows; k++) {
            adj.values[k] =
                    matrix_det_gauss(&det,
                                     matrix_for_minor(one,
                                                      (k % one.cols) + 1,
                                                      (k / one.cols) + 1)) *
                                                      pow((-1), k + 2);
        }
        div_matrix_by_number(*res, adj, matrix_det_gauss(res, one));
    }
    return *res;
}

/* Проверка корректности вычисления обратной матрицы путем умножения ее на
входную матрицу. Результатом должна быть единичная матрица. */
void is_ans_correct_inv (const Matrix res, const Matrix one) {
    printf("\n");
    bool flag = true;
    Matrix ident;
    Matrix check;
    create_identity_matrix(&ident, one);
    create_empty_matrix(&check, one, one);
    matrix_mult(&check, res, one);
    for (unsigned int k = 0; k < res.cols * res.rows; k++) {
        if ((flag == true) && ((fabs(check.values[k])) - ident.values[k]) <
                              EPS) {
            flag = true;
        } else flag = false;
    }
    if (flag == true) {
        printf("The answer is correct.\n");
    } else {
        printf("The answer is incorrect.\n");
    }
}

// Вывод сообщения об ошибке (вычисление матричной экспоненты)
bool error_exp (const Matrix one) {
    if (one.cols != one.rows) {
        printf("The number of columns and the number of rows are different.\n");
        return true;
    } else {
        return false;
    }
}

// Вычисление разности значений матрицы между предыдущей и последующей
// итерациями
bool accuracy_exp (const Matrix res, const Matrix last) {
    bool flag = true;
    for (unsigned int k = 0; k < res.cols * res.rows; k++) {
        if ((flag == true) && (fabs(res.values[k] - last.values[k])) > EPS) {
            flag = true;
        } else flag = false;
    }
    return flag;
}

// Функция для вычисления матричной экспоненты
Matrix matrix_exp (Matrix *res, const Matrix one) {
    if (error_exp(one)) {
        res = create_null_matrix(res);
    } else {
        Matrix power;
        Matrix last;
        create_identity_matrix(res, one);
        create_identity_matrix(&power, one);
        create_empty_matrix(&last, one, one);
        unsigned int k = 1;
        while ((accuracy_exp(*res, last)) || (k < MIN_NUM_CYCLES)) {
            Matrix division;
            create_empty_matrix(&division, one, one);
            last = *res;
            matrix_mult(&power, power, one);
            matrix_add(res, *res,
                       div_matrix_by_number(division, power,
                                            factorial(k)));
            k++;
        }
    }
    return *res;
}

/* Проверка корректности выполнения операции взятия матричной экспоненты
путем умножения матричной экспоненты от матрицы с инвертированными элементами
на полученную в результате выполнения программы. Результатом должна быть
единичная матрица. Выполняется с заданной точностью. */
void is_ans_correct_exp (const Matrix res, const Matrix one) {
    printf("\n");
    bool flag = true;
    Matrix ident;
    Matrix check;
    create_identity_matrix(&ident, one);
    create_empty_matrix(&check, one, one);
    matrix_mult(&check, res,
                matrix_exp(&check, mult_matrix_by_number(check, one, -1)));
    for (unsigned int k = 0; k < res.cols * res.rows; k++) {
        if ((flag == true) &&
            (fabs(check.values[k] - ident.values[k]))
                                        < EPS * 2) {
            flag = true;
        } else flag = false;
    }
    if (flag == true) {
        printf("The answer is correct.\n");
    } else {
        printf("The answer is incorrect.\n");
    }
}

// Функция для освобождения памяти
void free_memory (const Matrix matrix) {
    free(matrix.values);
}

int main() {
    unsigned int operation_choice = 6;
    // Выбор арифметической операции, производимой с матрицами, где
        // 1 - Операция сложения матриц
        // 2 - Операция вычитания матриц
        // 3 - Операция умножения матриц
        // 4 - Операция вычисления определителя матрицы методом Гаусса
        // 5 - Операция вычисления определителя с помощью миноров
        // 6 - Операция вычисления обратной матрицы
        // 7 - Операция взятия матричной экспоненты
    Matrix first;
    Matrix second;
    Matrix result;
    create_random_matrix(&first, &second);
    printf("Matrix A:\n");
    print_matrix(first);
    printf("\nMatrix B:\n");
    print_matrix(second);
    switch (operation_choice) {
        case 1: {
            printf("\nA + B:\n");
            print_matrix(matrix_add(&result, first, second));
            is_ans_correct_add(result, first, second);
            break;
            }
        case 2: {
            printf("\nA - B:\n");
            print_matrix(matrix_sub(&result, first, second));
            is_ans_correct_sub(result, first, second);
            break;
        }
        case 3: {
            printf("\nA * B:\n");
            print_matrix(matrix_mult(&result, first, second));
            is_ans_correct_mult(result, first, second);
            break;
        }
        case 4: {
            printf("\n|A| = %f\n", matrix_det_gauss(&result, first));
            printf("\n|B| = %f\n", matrix_det_gauss(&result, second));
            break;
        }
        case 6: {
            printf("\nA^(-1):\n");
            print_matrix(matrix_inv(&result, first));
            is_ans_correct_inv(result, first);
            printf("\nB^(-1):\n");
            print_matrix(matrix_inv(&result, second));
            is_ans_correct_inv(result, second);
            break;
        }
        case 7: {
            printf("\nexp(A)\n");
            print_matrix(matrix_exp(&result, first));
            is_ans_correct_exp(result, first);
            printf("\nexp(B)\n");
            print_matrix(matrix_exp(&result, second));
            is_ans_correct_exp(result, second);
            break;
        }
        default: {
            printf("Chosen number of operation does not allowed\n");
            print_matrix(*create_null_matrix(&result));
            break;
        }
    }
    free_memory(first);
    free_memory(second);
    free_memory(result);
    return 0;
}