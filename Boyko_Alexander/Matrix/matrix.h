#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H
#include "malloc.h"
#include <stdio.h>

struct Matrix{
    unsigned int cols;
    unsigned int rows;
    double* values;
    double** item;
};

struct Matrix ZERO;


struct Matrix create_zero_matrix(const unsigned int rows, const unsigned int cols){
    struct Matrix zero;
    zero.cols = cols;
    zero.rows = rows;
    zero.values = malloc(rows * cols * sizeof (double));
    zero.item = malloc(rows * sizeof (double*));
    for(int k = 0; k < rows * cols; k++){
        zero.values[k] = 0.0;
    }
    for(int j = 0; j < rows; j++){
        zero.item[j] = zero.values + j * cols;
    }
    return zero;
}

void fill_matrix_summ(struct Matrix *matrix){
    int k;
    for(k = 0; k < matrix->rows * matrix->cols; k++){
        matrix->values[k] = k % matrix->cols + (unsigned int)(k / matrix->cols);
    }
}

void fill_matrix_mult(struct Matrix *matrix){
    int k;
    for(k = 0; k < matrix->rows * matrix->cols; k++){
        matrix->values[k] = k % matrix->cols * (int)(k / matrix->cols);
    }
}

struct Matrix matrix_add(const struct Matrix *fst_matx, const struct Matrix *snd_matx){
    if (fst_matx->rows != snd_matx->rows || fst_matx->cols != snd_matx->cols){
        printf("Incompatible matrix sizes!\n");
        return ZERO;
    }
    unsigned int cols = snd_matx->cols;
    unsigned int rows = fst_matx->rows;
    struct Matrix res_matx = create_zero_matrix(rows,cols);
    printf("Addition\n");
    for(int k = 0; k < rows * cols; k++){
        res_matx.values[k] = fst_matx->values[k] + snd_matx->values[k];
    }
    return res_matx;
}

struct Matrix matrix_subt(const struct Matrix *fst_matx, const struct Matrix *snd_matx){
    if (fst_matx->rows != snd_matx->rows || fst_matx->cols != snd_matx->cols){
        printf("Incompatible matrix sizes!\n");
        return ZERO;
    }
    unsigned int cols = snd_matx->cols;
    unsigned int rows = fst_matx->rows;
    struct Matrix res_matx = create_zero_matrix(rows,cols);
    printf("Subtraction\n");
    for(int k = 0; k < rows * cols; k++){
        res_matx.values[k] = fst_matx->values[k] - snd_matx->values[k];
    }
    return res_matx;
}

struct Matrix matrix_mult(const struct Matrix *fst_matx, const struct Matrix *snd_matx){
    if (fst_matx->cols != snd_matx->rows){
        printf("Incompatible matrix sizes!\n");
        return ZERO;
    }
    unsigned int cols = snd_matx->cols;
    unsigned int rows = fst_matx->rows;
    struct Matrix res_matx = create_zero_matrix(rows,cols);
    printf("Multiplication\n");
    for(int k = 0; k < rows; k++) {
        for (int j = 0; j < cols; j++) {
            for (int n = 0; n < fst_matx->cols; n++) {
                res_matx.item[k][j] += fst_matx->item[k][n] * snd_matx->item[n][j];
            }
        }
    }
    return res_matx;
}

void print_matx(struct Matrix matrix){
    printf("\n");
    for(int k = 0; k < matrix.rows; k++){
        printf("(");
        int j;
        for(j = 0; j < matrix.cols; j++){
            printf("%f; ",matrix.values[k * matrix.cols + j]);
        }
        printf(")\n");
    }
}

void print_items(struct Matrix matrix){
    printf("\n");
    for(int k = 0; k < matrix.rows; k++){
        printf("(");
        int j;
        for(j = 0; j < matrix.cols; j++){
            printf("%f; ",matrix.item[k][j]);
        }
        printf(")\n");
    }
}

#endif //MATRIX_MATRIX_H
/*
void create_empty_matrix(struct Matrix *matrix, unsigned int mat_cols, unsigned int mat_rows, char name[]){
    matrix->name = malloc(sizeof *name);
    matrix->name = name;
    matrix->cols = mat_cols;
    matrix->rows = mat_rows;
    matrix->values = malloc(matrix->rows * sizeof *matrix->values);
    matrix->ZERO = malloc(matrix->rows * sizeof *matrix->values);
    int k;
    for(k = 0; k < mat_rows; k++){
        matrix->values[k] = malloc(matrix->cols * sizeof *matrix->values);
        matrix->ZERO[k] = malloc(matrix->cols * sizeof *matrix->values);
        int j;
        for(j = 0; j < mat_cols; j++){
            matrix->values[k][j] = 0;
            matrix->ZERO[k][j] = 0;
        }
    }
}

void fill_matrix_summ(struct Matrix *matrix){
    int k;
    for(k = 0; k < matrix->rows; k++){
        int j;
        for(j = 0; j < matrix->cols; j++){
            matrix->values[k][j] = k+j;
        }
    }
}

void fill_matrix_mult(struct Matrix *matrix){
    int k;
    for(k = 0; k < matrix->rows; k++){
        int j;
        for(j = 0; j < matrix->cols; j++){
            matrix->values[k][j] = k*j;
        }
    }
}

struct Matrix matrix_add(const struct Matrix *fst_matx, const struct Matrix *snd_matx){
    struct Matrix res_matx;
    unsigned int cols = snd_matx->cols;
    unsigned int rows = fst_matx->rows;
    create_empty_matrix(&res_matx,cols,rows,"Res_Add");
    if (fst_matx->rows != snd_matx->rows || fst_matx->cols != snd_matx->cols){
        printf("Incompatible matrix sizes!\n");
        return res_matx;
    }
    res_matx.values = malloc(rows * sizeof *res_matx.values);
    int k;
    for(k = 0; k < rows; k++){
        res_matx.values[k] = malloc(cols * sizeof *res_matx.values);
        int j;
        for(j = 0; j < cols; j++){
            res_matx.values[k][j] = fst_matx->values[k][j] + snd_matx->values[k][j];
        }
    }
    return res_matx;
}

struct Matrix matrix_subt(const struct Matrix *fst_matx, const struct Matrix *snd_matx){
    struct Matrix res_matx;
    unsigned int cols = snd_matx->cols;
    unsigned int rows = fst_matx->rows;
    create_empty_matrix(&res_matx,cols,rows,"Res_Subt");
    if (fst_matx->rows != snd_matx->rows || fst_matx->cols != snd_matx->cols){
        printf("Incompatible matrix sizes!\n");
        return res_matx;
    }
    res_matx.values = malloc(rows * sizeof *res_matx.values);
    int k;
    for(k = 0; k < rows; k++){
        res_matx.values[k] = malloc(cols * sizeof *res_matx.values);
        int j;
        for(j = 0; j < cols; j++){
            res_matx.values[k][j] = fst_matx->values[k][j] - snd_matx->values[k][j];
        }
    }
    return res_matx;
}

struct Matrix matrix_mult(const struct Matrix *fst_matx, const struct Matrix *snd_matx){
    struct Matrix res_matx;
    unsigned int cols = snd_matx->cols;
    unsigned int rows = fst_matx->rows;
    create_empty_matrix(&res_matx,cols,rows,"Res_Mult");
    if (fst_matx->cols != snd_matx->rows){
        printf("Incompatible matrix sizes!\n");
        return res_matx;
    }
    res_matx.values = malloc(rows * sizeof *res_matx.values);
    int k;
    for(k = 0; k < rows; k++){
        res_matx.values[k] = malloc(cols * sizeof *res_matx.values);
        int j;
        for(j = 0; j < cols; j++){
            res_matx.values[k][j] = 0;
            int n;
            for(n = 0; n < fst_matx->cols; n++) {
                res_matx.values[k][j] += fst_matx->values[k][n] * snd_matx->values[n][j];
            }
        }
    }
    return res_matx;
}

void print_matx(struct Matrix matrix){
    printf("%s \n", matrix.name);
    int k;
    for(k = 0; k < matrix.rows; k++){
        printf("(");
        int j;
        for(j = 0; j < matrix.cols; j++){
            printf("%f; ",matrix.values[k][j]);
        }
        printf(")\n");
    }
}
*/

