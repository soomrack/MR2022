#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
//#define DEBUG
//#define MANUAL_INPUT

typedef struct Matrix {
    int rows;
    int cols;
    double *values;
}Matrix;

Matrix allocate_memory(const int row, const int col){
    Matrix empty = {row, col, NULL};
    empty.values = (double*) malloc(row * col * sizeof(double));
    return (empty);}

void output_Matrix(const char* massage, Matrix A){
    printf("%s\n", massage);
    for (int row = 0; row < A.rows; row++){
        for (int col = 0; col < A.cols; col++){
            printf("%lf ", A.values[row * A.cols + col]);}
        printf("\n");}
    printf("\n");
}

//errors codes in swich oprator
void error(int code){
    switch (code) {
        case 1:
            printf("Error: invalid size, please try another input\n");
            exit(1);
        case 2:
            printf("Error: invalid input, please try again\n");
            exit(2);
        case 3:
            printf("Error: determenant is zero. "
                   "There is no inverse matrix\n");
            exit(3);
    }
}

Matrix addition(Matrix A, Matrix B){
    if (A.rows != B.rows || A.cols != B.cols){
        error(1);}
    Matrix sum = allocate_memory(A.rows, A.cols);
    for (int idx = 0; idx < A.rows * A.cols; idx++){
            sum.values[idx] = A.values[idx] + B.values[idx];}
    return sum;
}

//retun Matrix without deleted row and col: in cycle skip deleted row&col
Matrix truncated(const int del_row, const int del_col,  Matrix M){
    Matrix trun = allocate_memory(M.rows - 1, M.cols - 1);
    int row_t = 0; int col_t = 0;
    for (int row_M = 0; row_M < M.rows; row_M++){
        if (row_M == del_row) continue;
        for (int col_M = 0; col_M < M.cols; col_M++){
            if (col_M == del_col) continue;
            trun.values [row_t * trun.cols + col_t] =
                    M.values[row_M * M.cols + col_M];
            col_t++;}
        row_t++; col_t = 0;}
    return trun;}

double determinant(Matrix A){
    double det = 0;
    if (A.rows != A.cols){
        error(1);
        return NAN;}
    if (A.rows == 1) // first order matrix determinant
        return A.values[0];
    else if (A.rows == 2)  // second order matrix determinant
        return (A.values[0] * A.values[3] - A.values[1] * A.values[2]);
    else {
        for (int col = 0; col < A.cols; col++){
            Matrix trun = truncated(0, col, A);
            det += (A.values[col] * pow(-1, col) * determinant(trun));
            free(trun.values);}
    }
    return det;}

double  trace (Matrix A){
    if (A.rows != A.cols){
        error(1);
        return NAN;}
    double tr = 0;
    for (int idx = 0; idx < A.cols; idx++){
        tr += A.values[idx * A.rows + idx];}
    return tr;
}

Matrix multiplication_scalar(const Matrix A, const double s) {
    Matrix mul = allocate_memory(A.rows, A.cols);
    for (int idx = 0; idx < A.rows * A.cols; idx++){
        mul.values[idx] = A.values[idx] * s;}
    return mul;}

Matrix subtraction(Matrix A, Matrix B){
    Matrix unB = multiplication_scalar(B, -1);
    return addition(A, unB);
}

Matrix multiplication(const Matrix A, const Matrix B) {
    if (A.cols != B.rows) {
        error(1);
    }
    Matrix mul = allocate_memory(A.rows,B.cols);
    for (int row = 0; row < mul.rows; row++) {
        for (int col = 0; col < mul.cols; col++) {
            double sum = 0.0;
            for (int idx = 0; idx < A.cols; idx++) {
                sum += A.values[row * A.cols + idx] * B.values[idx * B.cols + col];}
            mul.values[row * mul.cols + col] = sum;}
    }
    return mul;}

#ifdef MANUAL_INPUT;
void input_Matrix(Matrix A){
    for (int row = 0; row < A.rows; row++){
        for (int col = 0; col < A.cols; col++){
            printf("a[%d][%d] = ", row, col);
            scanf(" %lf", &A.values[row * A.cols + col]);}}}
#endif

//create identity matrix
Matrix E(int row){
    Matrix E = allocate_memory(row, row);
    int diag = 0;
    for (int idx = 0; idx < row * row; idx++){
        if (idx == diag) {
            E.values[idx] = 1;
            diag += row + 1;}
        else
            E.values[idx] = 0;}
    return E;}

Matrix exponent(Matrix A){
    if (A.cols != A.rows) {
        error(1);}
    Matrix expon = allocate_memory(A.rows, A.cols);
    Matrix temp = allocate_memory(A.rows, A.cols);
    Matrix temp_mult;
    Matrix temp_sum;
    long double unfactorial = 1;
    double accuracy = 100;  //iteration count
    for (int acc = 0; acc < accuracy; acc++) {
        unfactorial /= acc;
        temp_mult = multiplication(temp, A);
        free(temp.values);
        temp = temp_mult;
        temp_sum = addition(expon, multiplication_scalar(temp, unfactorial));
        free(expon.values);
        expon = temp_sum;
    }
    free(temp_mult.values);
    return expon;
}



Matrix transposition(Matrix A){
    Matrix tr = allocate_memory(A.rows,  A.cols);
    for (int row = 0; row < A.rows; row++) {
        for (int col = 0; col < A.cols; col++) {
            tr.values[col * tr.rows + row] = A.values[row * tr.cols + col];}
    }
    return tr;}

Matrix inverse(const Matrix A){
    if (A.rows != A.cols){
        error(1);}
    Matrix inver = allocate_memory(A.rows, A.cols);
    double det = determinant(A);
    if (det == 0){  // degeneracy check
        error(3);
        return inver;}

    for (int row = 0; row < A.rows; row++) {
        for (int col = 0; col < A.cols; col++) {
            Matrix trun = truncated(row, col, A);
            int idx = A.rows * col + row;
            inver.values[idx] = pow(-1, idx) * determinant(trun) / det;
            free(trun.values);
        }}
    return inver;
}

void menu(Matrix A,  Matrix B){
    Matrix addiction;
    Matrix sub;
    Matrix multi;
    bool select_flag = true;
    bool single_flag = false;
    bool duo_flag= false;
    int num;
    while (select_flag) {
        printf("Select mode:\n"
               "1. Single matrix operations\n"
               "2. Operations with two matrices\n");
        select_flag = false;
        scanf("%d", &num);
        if (num == 1){single_flag = true; select_flag = false;} else{
            if (num == 2) {duo_flag = true; select_flag = false;} else{
                error(2);
                select_flag = true;}}}
    if (duo_flag) {
        printf("Select function in list:\n"
               "1. Addiction of two Matrix\n"
               "2. Subtraction of two Matrix\n"
               "3. Multiplication of two Matrix\n");
        duo_flag = false;
        scanf("%d", &num);
        switch (num) {
            case 1:
                addiction = addition(A,B);
                output_Matrix("addiction", addiction);
                free(addiction.values); break;
            case 2:
                sub = subtraction(A,B);
                output_Matrix("subtraction",sub);
                free(sub.values); break;
            case 3:
                multi = multiplication(A,B);
                output_Matrix("multiplication", multi);
                free(multi.values); break;
            default:
                error(2);
                duo_flag = true;}}
    if (single_flag) {
        printf("Select function in list:\n"
               "1. Find det of matrix\n"
               "2. Multiplication of a matrix by a scalar\n"
               "3. Find exponent matrix\n"
               "4. Division of a matrix by a scalar\n"
               "5. Matrix trace\n"
               "6. Inverse matrix \n");
        single_flag = false;
        scanf("%d", &num);
        switch (num) {
            case 1:
                printf("\ndet %lf\n", determinant(A)); break;
            case 2:
                printf("print scalar: \n");
                double scl;
                scanf("%lf", &scl);
                Matrix mul = multiplication_scalar(A, scl);
                output_Matrix("resolut: \n",mul);
                free(mul.values); break;
            case 3:
                mul = exponent(A);
                output_Matrix("exponent", mul);
                free(mul.values); break;
            case 4:
                printf("print scalar: \n");
                double div;
                scanf("%lf", &div);
                Matrix di = multiplication_scalar(A, 1 / div);
                output_Matrix("resolut: \n",di);
                free(di.values); break;
            case 5:
                printf("resolut: %lf\n",trace(A)); break;
            case 6:
                sub = inverse(A);
                output_Matrix("resolut: ",sub);
                free(sub.values); break;
            default:
                error(2);}}}

int main() {
#ifndef MANUAL_INPUT
    double  values1[9] = {2.0, 2.0, 5.0,
                           5.0, 2.0, 52.0,
                           50, 89, 9};
    double  values2[9] = {7.0, 55.0, 88, 32,
                          5.0, 5.0, 77, 8, 6};
    double values3[9] = {87.0, 5.0, 2, 32,
                         59.0, 5.0, 57, 8, 6};

    Matrix A = {3, 3,  values1};
    Matrix B = {3, 3, values2};
#endif
#ifdef MANUAL_INPUT
    Matrix A = allocate_memory(3, 3);
    Matrix B = allocate_memory(3, 3);
    input_Matrix(A);
    input_Matrix(B);
#endif
    output_Matrix("First Matrix", A);
    output_Matrix("Second Matrix", B);

    menu(A, B);

#ifdef MANUAL_INPUT
    free(A.values);
    free(B.values);
#endif
    return 0;
}
