#include <stdio.h>
#include "malloc.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <minmax.h>


const unsigned int Max_range = 51;
const double Comparison_const = 0.00001;


struct Matrix {
    unsigned int rows;
    unsigned int cols;

    double *data;
    double **value;
};


struct Matrix undefined(const unsigned int rows, const unsigned int cols){
    struct Matrix rez;
    rez.rows = rows;
    rez.cols = cols;
    rez.data = (double*)malloc(rows * cols * sizeof (double *));
    rez.value = (void**)malloc(rows * sizeof(void *));

    for (unsigned int row = 0; row < rows; row ++){
        rez.value[row] = rez.data + row * cols;
    }
    return rez;
}


void release(struct Matrix x){
    free(x.data);
    free(x.value);
}


struct Matrix empty(){
    struct Matrix rez = {0,0};
    return rez;
}


struct Matrix zero(const unsigned int rows, const unsigned int cols){

    struct Matrix rez = undefined(rows, cols);
    for (unsigned int idx = 0; idx < rows * cols; idx++){
        rez.data[idx] = 0.0;
    }
    return rez;

}


struct Matrix one(const unsigned int rows, const unsigned int cols){

    struct Matrix rez = zero(rows, cols);
    for (unsigned int idx = 0; idx < min(rows, cols); idx++){
        rez.value[idx][idx] = 1.0;
    }
    return rez;

}


struct Matrix tran(struct Matrix x){
    struct Matrix rez = undefined(x.cols, x.rows);
    for (unsigned int row = 0; row < rez.rows; row++){
        for (unsigned int col = 0; col < rez.cols; col++){
            rez.value[row][col] = x.value[col][row];
        }
    }
    return rez;
}


struct Matrix minor(const unsigned int cur_row, const unsigned int cur_col, const struct Matrix x){
    struct Matrix rez = undefined( x.rows - 1, x.cols - 1);
    unsigned int k = 0;
    for (unsigned int idx = 0; idx < x.rows * x.cols; idx++){
        if ((idx % x.cols != cur_col) && (idx / x.cols != cur_row)){
            rez.data[k++] = x.data[idx];
        }
    }
    return rez;
}


struct Matrix sum(const struct Matrix x, const struct Matrix y){
    if ((x.cols != y.cols) || (x.rows != y.rows)) return empty();

    struct Matrix rez = undefined(x.rows, x.cols);
    for (unsigned int idx = 0; idx < x.rows * x.cols; idx++){
        rez.data[idx] = x.data[idx] + y.data[idx];
    }
    return rez;

}


struct Matrix subtraction(const struct Matrix x, const struct Matrix y){
    if ((x.cols != y.cols) || (x.rows != y.rows)) return empty();

    struct Matrix rez = undefined(x.rows, x.cols);
    for (unsigned int idx = 0; idx < x.rows * x.cols; idx++){
        rez.data[idx] = x.data[idx] - y.data[idx];
    }
    return rez;

}


struct Matrix multiplication(const struct Matrix x, const struct Matrix y){
    if (x.cols != y.rows) return empty();

    struct Matrix rez = undefined(x.rows, y.cols);
    for (unsigned int row = 0; row < rez.rows; row++){
        for (unsigned int col = 0; col < rez.cols; col++){
            rez.value[row][col] = 0.0;
            for (unsigned int idx = 0; idx < x.cols; idx++){
                rez.value[row][col] += x.value[row][idx] * y.value[idx][col];
            }
        }
    }
    return rez;

}


struct Matrix multy_k(const struct Matrix x, const double k){

    struct Matrix rez = undefined(x.rows, x.cols);
    for (unsigned int idx = 0; idx < x.rows * x.cols; idx++){
        rez.data[idx] = x.data[idx] * k;
    }
    return rez;

}


double det(const struct Matrix x){
    if (x.cols != x.rows) return 0.0;

    if (x.cols == 1){
        return x.value[0][0];
    }
    double rez = 0.0;
    int ratio = 1;
    for (unsigned int idx = 0; idx < x.cols; idx++) {
        struct Matrix temp = minor(0, idx, x);
        rez += ratio * x.value[0][idx] * det(temp);
        ratio *= -1;
        release(temp);
    }
    return rez;

}


struct Matrix reverse(const struct Matrix x){
    double deter = det(x);
    if ((x.cols != x.rows) || (deter == 0.0)) return empty();

    struct Matrix rez = undefined(x.rows, x.cols);
    int ratio = 1;
    for (unsigned int row = 0; row < rez.rows; row++){
        for (unsigned int col = 0; col < rez.cols; col++){
            struct Matrix temp = minor(row, col, x);
            rez.value[row][col] = ratio * det(temp);
            ratio *= -1;
            release(temp);
        }
    }
    struct Matrix ans = tran(rez);
    rez = multy_k(ans, 1/deter);
    release(ans);
    return rez;

}


struct Matrix pow_mat(const struct Matrix x, const unsigned int n){
    if (x.rows != x.cols) return empty();

    if (n == 0) return one(x.rows, x.cols);
    struct Matrix rez = undefined(x.rows, x.cols);
    rez.data = x.data;
    rez.value = x.value;
    for (unsigned int idx = 1; idx < n; idx++){
        struct Matrix temp = multiplication(x, rez);
        rez = temp;
        release(temp);
    }
    return rez;

}


struct Matrix exponent(const struct Matrix x, const unsigned int kol_slog){
    if (x.cols != x.rows) return empty();

    struct Matrix rez = zero(x.rows, x.cols);
    double ratio = 1;
    for (unsigned int idx = 0; idx < kol_slog; idx++){
        struct Matrix degree = pow_mat(x, idx);
        struct Matrix multiplier = multy_k(degree, ratio);
        rez = sum(rez, multiplier);
        ratio /= (idx + 1);

        release(degree);
        release(multiplier);
    }
    return rez;

}


void output(const struct Matrix x){

    for (unsigned int row = 0; row < x.rows; row++){
        for (unsigned int col = 0; col < x.cols; col++){
            printf("%.2lf ", x.value[row][col]);
        }
        printf("\n");
    }
    printf("\n");

}


struct Matrix certain(const unsigned int rows, const unsigned int cols,
        const double *arrey, const unsigned int arr_length){
    if (abs(rows * cols - arr_length) > Comparison_const) return empty();

    struct Matrix rez = undefined(rows, cols);
    for (unsigned int idx = 0; idx < rows * cols; idx++){
        rez.data[idx] = arrey[idx];
    }
    return rez;

}


void test_of_add(){

    double arr_first[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    struct Matrix first = certain(2, 3, arr_first, sizeof(arr_first) / sizeof(double));

    double arr_second[6] = {6.0, 5.0, 4.0, 3.0, 2.0, 1.0};
    struct Matrix second = certain(2,3, arr_second, sizeof(arr_second) / sizeof(double));

    struct Matrix rez_add = sum(first, second);

    int flag = (sum(zero(2,2), first).rows == empty().rows);
    for (unsigned int idx = 0; idx < rez_add.rows * rez_add.cols; idx++){
        flag *= (abs(rez_add.data[idx] - 7.0) < Comparison_const);
    }

    if (flag){
        printf("Test of sum was successful\n");
    } else {
        printf("Test of sum was failed\n");
    }

    release(first);
    release(second);
    release(rez_add);
}


void test_of_sub(){

    double arr_first[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    struct Matrix first = certain(2, 3, arr_first, sizeof(arr_first) / sizeof(double));

    double arr_second[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    struct Matrix second = certain(2, 3, arr_second, sizeof(arr_second) / sizeof(double));

    struct Matrix rez_sub = subtraction(first, second);

    int flag = (subtraction(zero(2,2), one(3, 3)).rows == empty().rows);
    for (unsigned int idx = 0; idx < rez_sub.rows * rez_sub.cols; idx++){
        flag *= (abs(rez_sub.data[idx] - 0.0) < Comparison_const);
    }

    if (flag){
        printf("Test of subtraction was successful\n");
    } else {
        printf("Test of subtraction was failed\n");
    }

    release(first);
    release(second);
    release(rez_sub);
}


void test_of_multy(){
    double arr_first[6] = {1.0, 5.0, 6.0, 3.0, 9.0, 4.0};
    struct Matrix first = certain(2, 3, arr_first, sizeof (arr_first) / sizeof (double));

    double arr_second[3] = {1.0, 0.0, 1.0};
    struct Matrix second = certain(3, 1, arr_second, sizeof (arr_second) / sizeof (double));

    struct Matrix rez_mul = multiplication(first, second);

    int flag = (multiplication(zero(2,3), one(2, 2)).rows == empty().rows);
    for (unsigned int idx = 0; idx < rez_mul.rows * rez_mul.cols; idx++){
        flag *= (abs(rez_mul.data[idx] - 7.0) < Comparison_const);
    }

    if (flag){
        printf("Test of multiplication was successful\n");
    } else {
        printf("Test of multiplication was failed\n");
    }

    release(first);
    release(second);
    release(rez_mul);
}


void test_of_reverse(){
    unsigned int n = 3;
    struct Matrix obj = undefined(n, n);
    for (unsigned int idx = 0; idx < obj.rows * obj.cols; idx++){
        obj.data[idx] = rand() % Max_range;
    }

    struct Matrix rez = multiplication(obj, reverse(obj));
    struct Matrix one_3 = one(n, n);

    int flag = (rez.rows != empty().rows);
    for (unsigned int idx = 0; idx < rez.rows * rez.cols; idx++){
        flag *= (abs(rez.data[idx] - one_3.data[idx]) < Comparison_const);
    }

    if (flag){
        printf("Test of reverse matrix was successful\n");
    } else {
        printf("Test of reverse matrix was failed\n");
    }

    release(obj);
    release(rez);
    release(one_3);
}


void test_of_exponent(){
    struct Matrix base = undefined(3, 3);
    for (unsigned int idx = 0; idx < base.rows * base.cols; idx++){
        base.data[idx] = rand() % Max_range;
    }

    struct Matrix option_1 = exponent(base, 3);
    struct Matrix option_2 = sum(one(3, 3), sum(base, multy_k(multiplication(base, base), 0.5)));

    int flag = (option_1.rows == option_2.rows);
    for (unsigned int idx = 0; idx < option_1.rows * option_1.cols; idx++){
        flag *= (abs(option_1.data[idx] - option_2.data[idx]) < Comparison_const);
    }

    if (flag){
        printf("Test of exponent was successful\n");
    } else {
        printf("Test of exponent was failed\n");
    }

    release(base);
    release(option_1);
    release(option_2);
}


void block_tests(){
    test_of_add();
    test_of_sub();
    test_of_multy();
    test_of_reverse();
    test_of_exponent();
    printf("\n");
}


void block_output(){
    struct Matrix A = undefined(5, 5);
    struct Matrix B = undefined(5, 5);

    for (unsigned int idx = 0; idx < A.rows * A.cols; idx++){
        A.data[idx] = rand() % Max_range;
    }
    for (unsigned int idx = 0; idx < B.rows * B.cols; idx++){
        B.data[idx] = rand() % Max_range;
    }

    printf("This is empty Matrix\n");
    output(empty());
    printf("This is zero matrix\n");
    output(zero(5,5));
    printf("This is one matrix\n");
    output(one(5, 5));

    printf("This is matrix A\n");
    output(A);
    printf("This is matrix B\n");
    output(B);

    printf("This is transporation of matrix A\n");
    output(tran(A));

    printf("This is matrix A + B\n");
    output(sum(A,B));
    printf("This is matrix A - B\n");
    output(subtraction(A,B));
    printf("This is matrix A * B\n");
    output(multiplication(A, B));
    printf("This is matrix A * 0.33\n");
    output(multy_k(A, 0.33));

    printf("This is det of matrix A\n");
    printf("%.2lf\n\n", det(A));

    printf("This is reverse of matrix A\n");
    output(reverse(A));
    printf("This is matrix A in degree 3\n");
    output(pow_mat(A, 3));

    printf("This is exp of Matrix A\n");
    output(exponent(A, 3));
}


int main() {
    //srand(time(NULL));

    block_tests();
    block_output();

    return 0;
}
