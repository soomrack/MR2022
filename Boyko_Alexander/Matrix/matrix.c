#include "matrix.h"

void message(int ind) {
    printf("%s", MESSAGES[ind]);
}

Matrix copy_mat(Matrix matrix){
    unsigned int rows = matrix.rows;
    unsigned int cols = matrix.cols;
    Matrix copy = create_zero_matrix(rows,cols);
    for(int k = 0; k < rows * cols; k++){
        copy.values[k] = matrix.values[k];
    }
    return copy;
}

Matrix create_zero_matrix(const unsigned int rows, const unsigned int cols) {
    Matrix zero;
    zero.cols = cols;
    zero.rows = rows;
    zero.values = malloc(rows * cols * sizeof(double));
    zero.item = malloc(rows * sizeof(double*));
    for(int k = 0; k < rows * cols; k++){
        zero.values[k] = 0.0;
    }
    for(int j = 0; j < rows; j++){
        zero.item[j] = zero.values + j * cols;
    }
    return zero;
}

void fill_matrix_summ(Matrix *matrix) {
    for(int k = 0; k < matrix->rows * matrix->cols; k++){
        matrix->values[k] = k % matrix->cols + (unsigned int)(k / matrix->cols);
    }
}

void fill_matrix_mult(Matrix *matrix) {
    for(int k = 0; k < matrix->rows * matrix->cols; k++){
        matrix->values[k] = k % matrix->cols * (int)(k / matrix->cols);
    }
}

void fill_matrix_val(Matrix *matrix, const double *value) {
    for(int k = 0; k < matrix->rows * matrix->cols; k++){
        matrix->values[k] = value[k];
    }
}

Matrix matrix_add(const Matrix *fst_matx, const Matrix *snd_matx) {
    if (fst_matx->rows != snd_matx->rows || fst_matx->cols != snd_matx->cols){
        message(ERR);
        return EMPTY;
    }
    unsigned int cols = snd_matx->cols;
    unsigned int rows = fst_matx->rows;
    Matrix res_matx = create_zero_matrix(rows,cols);
    message(ADD);
    for(int k = 0; k < rows * cols; k++){
        res_matx.values[k] = fst_matx->values[k] + snd_matx->values[k];
    }
    return res_matx;
}

Matrix matrix_subt(const Matrix *fst_matx, const Matrix *snd_matx) {
    if (fst_matx->rows != snd_matx->rows || fst_matx->cols != snd_matx->cols){
        message(ERR);
        return EMPTY;
    }
    unsigned int cols = snd_matx->cols;
    unsigned int rows = fst_matx->rows;
    Matrix res_matx = create_zero_matrix(rows,cols);
    message(SUB);
    for(int k = 0; k < rows * cols; k++){
        res_matx.values[k] = fst_matx->values[k] - snd_matx->values[k];
    }
    return res_matx;
}

Matrix matrix_mult(const Matrix *fst_matx, const Matrix *snd_matx) {
    if (fst_matx->cols != snd_matx->rows){
        message(ERR);
        return EMPTY;
    }
    unsigned int cols = snd_matx->cols;
    unsigned int rows = fst_matx->rows;
    Matrix res_matx = create_zero_matrix(rows,cols);
    message(MULT);
    for(int k = 0; k < rows; k++) {
        for (int j = 0; j < cols; j++) {
            for (int n = 0; n < fst_matx->cols; n++) {
                res_matx.item[k][j] += fst_matx->item[k][n] * snd_matx->item[n][j];
            }
        }
    }
    return res_matx;
}

Matrix matrix_mult_by_num(const double a, const Matrix *matrix) {
    unsigned int cols = matrix->cols;
    unsigned int rows = matrix->rows;
    Matrix res_matx = create_zero_matrix(rows,cols);
    message(MULT);
    for(int k = 0; k < rows * cols; k++) {
        res_matx.values[k] = a * matrix->values[k];
    }
    return res_matx;
}

void matrix_change_rows(Matrix *matrix, const int fst_row, const int snd_row) {
    double item_buff;
    for (int k = 0; k < matrix->cols; k++) {
        item_buff = matrix->item[snd_row][k];
        matrix->item[snd_row][k] = matrix->item[fst_row][k];
        matrix->item[fst_row][k] = item_buff;
    }
}

double matrix_det(const Matrix matrix) {
    if(matrix.rows != matrix.cols){
        message(ERR);
        return NAN;
    }
    message(DET);
    double det = 1;
    Matrix trian_mat = copy_mat(matrix);
    for(int row_ = 1; row_ < trian_mat.rows; row_++) {
        for (int row = row_; row < trian_mat.rows; row++) {
            if (trian_mat.item[row_ - 1][row_ - 1] == 0) {
                matrix_change_rows(&trian_mat, row_ - 1, row_);
                det *= -1;
            }
            double koef = trian_mat.item[row][row_-1] / trian_mat.item[row_ - 1][row_ - 1];
            for (int col = 0; col < trian_mat.cols; col++) {
                trian_mat.item[row][col] -= trian_mat.item[row_ - 1][col] * koef;
            }
        }
        det *= trian_mat.item[row_][row_];
    }
    free_mat(&trian_mat);
    return det;
}

void free_mat(Matrix *matrix) {
    free(matrix->item);
    free(matrix->values);
}

void print_matx(Matrix matrix) {
    printf("\n");
    for(int k = 0; k < matrix.rows; k++){
        printf("(");
        for(int j = 0; j < matrix.cols; j++){
            printf("%f; ",matrix.values[k * matrix.cols + j]);
        }
        printf(")\n");
    }
}

void print_items(Matrix matrix) {
    printf("\n");
    for(int k = 0; k < matrix.rows; k++){
        printf("(");
        for(int j = 0; j < matrix.cols; j++){
            printf("%f; ",matrix.item[k][j]);
        }
        printf(")\n");
    }
}


