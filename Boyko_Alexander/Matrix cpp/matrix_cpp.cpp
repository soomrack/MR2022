#include "matrix_cpp.h"

#include <iostream>


Matrix::Matrix() {
    //std::cout << "Constructor\n";
    cols = 1;
    rows = 1;
    values = (double*) malloc(sizeof(double));
    item = (double**) malloc(sizeof(double*));
    values[0] = NAN;
    item[0] = values;
}

Matrix::Matrix(const Matrix &orig) {
    //std::cout << "Copy constructor\n";

    rows = orig.rows;
    cols = orig.cols;
    values = (double*) malloc(rows * cols * sizeof(double));
    item = (double**) malloc(rows * sizeof(double*));
    for(int j = 0; j < rows; j++){
        item[j] = values + j * cols;
    }
    for(int k = 0; k < rows * cols; k++){
        values[k] = orig.values[k];
    }
}

Matrix::~Matrix() {
    //std::cout << "Deconstructor\n";
    free(values);
    free(item);
}

void Matrix::reset_mem(unsigned int set_rows, unsigned int set_cols) {
    free(values);
    free(item);
    rows = set_rows;
    cols = set_cols;
    values = (double*) malloc(rows * cols * sizeof(double));
    item = (double**) malloc(rows * sizeof(double*));
    for(int j = 0; j < rows; j++){
        item[j] = values + j * cols;
    }
}

Matrix &Matrix::operator=(const Matrix &orig) {
    reset_mem(orig.rows,orig.cols);
    for(int k = 0; k < rows * cols; k++){
        values[k] = orig.values[k];
    }
    return *this;
}

void Matrix::fill_sum(unsigned int set_rows, unsigned int set_cols) {
    reset_mem(set_rows, set_cols);
    for(int k = 0; k < rows * cols; k++){
        values[k] = k % cols + (unsigned int)(k / cols);
    }
}

void Matrix::fill_mult(unsigned int set_rows, unsigned int set_cols) {
    reset_mem(set_rows,set_cols);
    for(int k = 0; k < rows * cols; k++){
        values[k] = k % cols * (int)(k / cols);
    }
}

void Matrix::fill_val(unsigned int set_rows, unsigned int set_cols, const double *set_values) {
    reset_mem(set_rows, set_cols);
    for(int k = 0; k < rows * cols; k++){
        values[k] = set_values[k];
    }
}

void Matrix::make_one(unsigned int set_rows, unsigned int set_cols) {
    reset_mem(set_rows, set_cols);
    for(int k = 0; k < rows * cols; k++){
        if((int)(k / cols) == (k % cols)){
            values[k] = 1.0;
        }
        else{
            values[k] = 0.0;
        }
    }
}

void Matrix::make_zero(unsigned int set_rows, unsigned int set_cols) {
    reset_mem(set_rows, set_cols);
    for(int k = 0; k < rows * cols; k++){
        values[k] = 0.0;
    }
}

void Matrix::change_rows(const int fst_row, const int snd_row) const {
    double item_buff;
    for (int k = 0; k < cols; k++) {
        item_buff = item[snd_row][k];
        item[snd_row][k] = item[fst_row][k];
        item[fst_row][k] = item_buff;
    }
}

void Matrix::print_values() const {
    std::cout << "\n";
    for(int k = 0; k < rows; k++){
        std::cout << "(";
        for(int j = 0; j < cols; j++){
            std::cout << values[k * cols + j] << ", ";
        }
        std::cout <<")\n";
    }
}


Matrix operator+(Matrix fst_matx, Matrix snd_matx) {
    if (fst_matx.rows != snd_matx.rows || fst_matx.cols != snd_matx.cols){
        message(ADD);
        message(ERR);
        Matrix EMPTY;
        return EMPTY;
    }
    unsigned int cols = snd_matx.cols;
    unsigned int rows = fst_matx.rows;
    Matrix res_matx;
    res_matx.make_zero(rows,cols);
    for(int k = 0; k < rows * cols; k++){
        res_matx.values[k] = fst_matx.values[k] + snd_matx.values[k];
    }
    return res_matx;
}

Matrix operator-(Matrix fst_matx, Matrix snd_matx) {
    if (fst_matx.rows != snd_matx.rows || fst_matx.cols != snd_matx.cols){
        message(SUB);
        message(ERR);
        Matrix EMPTY;
        return EMPTY;
    }
    unsigned int cols = snd_matx.cols;
    unsigned int rows = fst_matx.rows;
    Matrix res_matx;
    res_matx.make_zero(rows,cols);
    for(int k = 0; k < rows * cols; k++){
        res_matx.values[k] = fst_matx.values[k] - snd_matx.values[k];
    }
    return res_matx;
}

Matrix operator*(Matrix fst_matx, Matrix snd_matx) {
    if (fst_matx.cols != snd_matx.rows){
        message(MUL);
        message(ERR);
        Matrix EMPTY;
        return EMPTY;
    }
    unsigned int cols = snd_matx.cols;
    unsigned int rows = fst_matx.rows;
    Matrix res_matx;
    res_matx.make_zero(rows, cols);
    for(int k = 0; k < rows; k++) {
        for (int j = 0; j < cols; j++) {
            for (int n = 0; n < fst_matx.cols; n++) {
                res_matx.item[k][j] += fst_matx.item[k][n] * snd_matx.item[n][j];
            }
        }
    }
    return res_matx;
}

Matrix operator*(Matrix matrix, double a) {
    unsigned int cols = matrix.cols;
    unsigned int rows = matrix.rows;
    Matrix res_matx;
    res_matx.make_zero(rows,cols);
    for(int k = 0; k < rows * cols; k++) {
        res_matx.values[k] = a * matrix.values[k];
    }
    return res_matx;
}

bool operator==(Matrix A, Matrix B) {
    if(A.cols != B.cols){
        return false;
    }
    if(A.rows != B.rows){
        return false;
    }
    for(int k = 0; k < A.cols * A.rows; k++){
        if (fabs(A.values[k] - B.values[k]) > EQUAL_ACCURACY) {
            return false;
        }
    }
    return true;
}

bool operator!=(Matrix A, Matrix B) {
    if(A.cols != B.cols){
        return true;
    }
    if(A.rows != B.rows){
        return true;
    }
    for(int k = 0; k < A.cols * A.rows; k++){
        if (fabs(A.values[k] - B.values[k]) > EQUAL_ACCURACY) {
            return true;
        }
    }
    return false;
}

double matx_det(const Matrix matrix) {
    if(matrix.rows != matrix.cols){
        message(DET);
        message(ERR);
        return NAN;
    }
    double det = 1;
    Matrix trian_mat;
    trian_mat = matrix;
    for(int row_fix = 1; row_fix < trian_mat.rows; row_fix++) { // row that will be subtracted
        for (int row = row_fix; row < trian_mat.rows; row++) { // start from the next row
            if (fabs(trian_mat.item[row_fix - 1][row_fix - 1]) < DETERMINANT_ACCURACY) { // division by zero check
                trian_mat.change_rows(row_fix - 1, row_fix);
                det = -det;
            }
            double koef = trian_mat.item[row][row_fix - 1] / trian_mat.item[row_fix - 1][row_fix - 1];
            for (int col = 0; col < trian_mat.cols; col++) {
                trian_mat.item[row][col] -= trian_mat.item[row_fix - 1][col] * koef;
            }
        }
        det *= trian_mat.item[row_fix][row_fix];
    }
    return det;
}

double check_max_dif(const Matrix fst_mat, const Matrix snd_mat) {
    double dif = 0.0;
    for(int k = 0; k < fst_mat.cols * fst_mat.rows; k++){
        if(fabs(fst_mat.values[k] - snd_mat.values[k]) > dif){
            dif = fst_mat.values[k] - snd_mat.values[k];
        }
    }
    return dif;
}

Matrix matrix_exp(const Matrix matrix) {
    if(matrix.rows != matrix.cols){
        message(EXP);
        message(ERR);
        Matrix EMPTY;
        return EMPTY;
    }
    Matrix res_mat;
    res_mat.make_one(matrix.rows,matrix.cols);
    Matrix n_member;
    n_member.make_one(matrix.rows,matrix.cols);
    Matrix n1_member;
    Matrix prev_mat;
    Matrix mem_mat;
    for(int m = 1; m <= EXPONENT_STEPS; m++){
        prev_mat = res_mat;
        n1_member = n_member * (matrix * (1.0 / m));
        mem_mat = res_mat;
        res_mat = mem_mat + n1_member;
        n_member = n1_member;
        if(fabs(check_max_dif(res_mat,prev_mat)) < EXPONENT_ACCURACY){
            return res_mat;
        }
    }
    return res_mat;
}
