#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H
#include "malloc.h"
#include <stdio.h>
#include "math.h"


typedef
struct Matrix{
    unsigned int cols;
    unsigned int rows;
    double* values;
    double** item;
}Matrix;

Matrix EMPTY = {0, 0, NULL, NULL};  // return if error

enum Message {ERR = 0, ADD = 1, SUB = 2, MULT = 3, DET = 4, EX = 5};

char *MESSAGES[6] = {"\nIncompatible matrix sizes!\n",
                      "\nAddition\n",
                      "\nSubtraction\n",
                      "\nMultiplication\n",
                      "\nDeterminant\n",
                      "\nExponent\n"};

Matrix create_zero_matrix(unsigned int rows, unsigned int cols);

void fill_matrix_summ(Matrix *matrix);

void fill_matrix_mult(Matrix *matrix);

void fill_matrix_val(Matrix *matrix, const double* value);

Matrix matrix_add(const Matrix *fst_matx, const Matrix *snd_matx);

Matrix matrix_subt(const Matrix *fst_matx, const Matrix *snd_matx);

Matrix matrix_mult(const Matrix *fst_matx, const Matrix *snd_matx);

Matrix matrix_mult_by_num(double a, const Matrix *matrix);

void matrix_change_rows(Matrix *matrix, int fst_row, int snd_row);

double matrix_det(Matrix matrix);

void free_mat(Matrix *matrix);

void print_matx(Matrix matrix);

void print_items(Matrix matrix);



void message(int ind);

#endif //MATRIX_MATRIX_H
