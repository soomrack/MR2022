#ifndef MR2022_MATRIX_H
#define MR2022_MATRIX_H

#include <stdbool.h>

// Структура для образования матрицы
typedef struct Matrix {
    unsigned int cols;
    unsigned int rows;
    double *values;
} Matrix;

void create_random_size_matrix(Matrix *one, Matrix *two);
Matrix* create_null_matrix(Matrix *res);
Matrix* create_zero_matrix(Matrix *res, Matrix one, Matrix two);
void create_identity_matrix(Matrix *ident, Matrix one);
void print_matrix(Matrix res);
void free_memory(Matrix matrix);
Matrix mult_matrix_by_number(Matrix res, const Matrix one, const double a);
Matrix div_matrix_by_number(Matrix res, const Matrix one, const double a);
Matrix matrix_for_minor(const Matrix one, unsigned int rowNumber,
                        unsigned int colNumber);
double factorial(const unsigned int b);
bool is_not_equal_size(const Matrix one, const Matrix two);
Matrix matrix_add(Matrix *res, const Matrix one, const Matrix two);
void is_ans_correct_add(const Matrix res, const Matrix one, const Matrix two);
Matrix matrix_sub(Matrix *res, const Matrix one, const Matrix two);
void is_ans_correct_sub(const Matrix res, const Matrix one, const Matrix two);
bool is_not_numbers_match(const Matrix one, const Matrix two);
Matrix matrix_mult(Matrix *res, const Matrix one, const Matrix two);
void is_ans_correct_mult(const Matrix res, const Matrix one, const Matrix two);
bool error_det_gauss(const Matrix one);
double matrix_det_gauss(Matrix *res, const Matrix  one);
bool error_inv(const Matrix one);
Matrix matrix_inv(Matrix *res, const Matrix one);
void is_ans_correct_inv(const Matrix res, const Matrix one);
bool error_exp(const Matrix one);
bool accuracy_exp(const Matrix res, const Matrix last);
Matrix matrix_exp(Matrix *res, const Matrix one);
void is_ans_correct_exp(const Matrix res, const Matrix one);

#endif
