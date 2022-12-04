#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>
#include <minmax.h>

const unsigned int Max_range = 51;
const double Comparison_const = 0.00001;

struct Mat {
    unsigned int cols;
    unsigned int rows;

    double *data;
    double **value;
};

struct Mat undef_mat (const unsigned int rows, const unsigned int cols) {
    struct Mat rez;
    rez.rows = rows;
    rez.cols = cols;
    rez.data = (double *) malloc(rows * cols * sizeof(double *));
    rez.value = (void**) malloc(rows * sizeof(void *));

    for(unsigned int row = 0; row < rows; row ++){
        rez.value[row] = rez.data + row * cols;
    }
    return rez;
}

void release(struct Mat x){
    free(x.data);
    free(x.value);
}

struct Mat empty() {
    struct Mat rez = {0, 0};
    return rez;
}

struct Mat zero(const unsigned int rows, const unsigned int cols){
    struct Mat rez = undef_mat(rows, cols);
    for(unsigned int dx = 0; dx < rows * cols; dx++){
        rez.data[dx]=0.0;
    }
    return rez;
}

struct Mat one(const unsigned int rows, const unsigned int cols){
    struct Mat rez = zero(rows, cols);
    for (unsigned int dx = 0; dx < min(rows, cols); dx++){
        rez.value[dx][dx] = 1.0;
    }
    return rez;
}

struct Mat transponation(struct Mat x){
    struct Mat rez = undef_mat(x.cols, x.rows);
    for (unsigned int row = 0; row < rez.rows; row++){
        for (unsigned int col = 0; col < rez.cols; col++){
            rez.value[row][col] = x.value[col][row];
        }
    }
    return rez;
}

struct Mat minor(const unsigned int cur_row, const unsigned int cur_col, const struct Mat x) {
    struct Mat rez = undef_mat(x.rows - 1, x.cols - 1);
    unsigned int k = 0;
    for (unsigned int dx = 0; dx < x.rows * x.cols; dx++) {
        if ((dx % x.cols != cur_col) && (dx / x.cols != cur_row)) {
            rez.data[k++] = x.data[dx];
        }
    }
    return rez;
}

struct Mat sum(const struct Mat x, const struct Mat y){
    if ((x.cols != y.cols) || (x.rows != y.rows)) return empty();

    struct Mat rez = undef_mat(x.rows, x.cols);
    for (unsigned int dx = 0; dx < x.rows * x.cols; dx++){
        rez.data[dx] = x.data[dx] + y.data[dx];
    }
    return rez;

}

struct Mat subtraction(const struct Mat x, const struct Mat y){
    if ((x.cols != y.cols) || (x.rows != y.rows)) return empty();

    struct Mat rez = undef_mat(x.rows, x.cols);
    for (unsigned int dx = 0; dx < x.rows * x.cols; dx++){
        rez.data[dx] = x.data[dx] - y.data[dx];
    }
    return rez;

}

struct Mat multiplication(const struct Mat x, const struct Mat y){
    if (x.cols != y.rows) return empty();

    struct Mat rez = undef_mat(x.rows, y.cols);
    for (unsigned int row = 0; row < rez.rows; row++){
        for (unsigned int col = 0; col < rez.cols; col++){
            rez.value[row][col] = 0.0;
            for (unsigned int dx = 0; dx < x.cols; dx++){
                rez.value[row][col] += x.value[row][dx] * y.value[dx][col];
            }
        }
    }
    return rez;
}

struct Mat multiplication_k(const struct Mat x, const double k){

    struct Mat rez = undef_mat(x.rows, x.cols);
    for (unsigned int dx = 0; dx < x.rows * x.cols; dx++){
        rez.data[dx] = x.data[dx] * k;
    }
    return rez;
}

double det(const struct Mat x){
    if (x.cols != x.rows) return 0.0;

    if (x.cols == 1){
        return x.value[0][0];
    }
    double rez = 0.0;
    int ratio = 1;
    for (unsigned int dx = 0; dx < x.cols; dx++) {
        struct Mat temp = minor(0, dx, x);
        rez += ratio * x.value[0][dx] * det(temp);
        ratio *= -1;
        release(temp);
    }
    return rez;
}

struct Mat reverse(const struct Mat x){
    double deter = det(x);
    if ((x.cols != x.rows) || (deter == 0.0)) return empty();

    struct Mat rez = undef_mat(x.rows, x.cols);
    int ratio = 1;
    for (unsigned int row = 0; row < rez.rows; row++){
        for (unsigned int col = 0; col < rez.cols; col++){
            struct Mat temp = minor(row, col, x);
            rez.value[row][col] = ratio * det(temp);
            ratio *= -1;
            release(temp);
        }
    }
    struct Mat ans = transponation(rez);
    rez = multiplication_k(ans, 1/deter);
    release(ans);
    return rez;

}

struct Mat pow_m(const struct Mat x, const unsigned int n){
    if (x.rows != x.cols) return empty();

    if (n == 0) return one(x.rows, x.cols);
    struct Mat rez = undef_mat(x.rows, x.cols);
    rez.data = x.data;
    rez.value = x.value;
    for (unsigned int dx = 1; dx < n; dx++){
        struct Mat temp = multiplication(x, rez);
        rez = temp;
        release(temp);
    }
    return rez;
}

struct Mat exponent(const struct Mat x, const unsigned int kol_slog){
    if (x.cols != x.rows) return empty();

    struct Mat rez = zero(x.rows, x.cols);
    double ratio = 1;
    for (unsigned int dx = 0; dx < kol_slog; dx++){
        struct Mat degree = pow_m(x, dx);
        struct Mat multiplier = multiplication_k(degree, ratio);
        rez = sum(rez, multiplier);
        ratio /= (dx + 1);

        release(degree);
        release(multiplier);
    }
    return rez;

}

void output(const struct Mat x){
    for (unsigned int row = 0; row < x.rows; row++){
        for (unsigned int col = 0; col < x.cols; col++){
            printf("%.2lf ", x.value[row][col]);
        }
        printf("\n");
    }
    printf("\n");
}

struct Mat certain(const unsigned int rows, const unsigned int cols,
                      const double *arrey, const unsigned int arr_length){
    if (abs(rows * cols - arr_length) > Comparison_const) return empty();

    struct Mat rez = undef_mat(rows, cols);
    for (unsigned int dx = 0; dx < rows * cols; dx++){
        rez.data[dx] = arrey[dx];
    }
    return rez;

}


void test_of_add(){
    double arr_first[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    struct Mat first = certain(2, 3, arr_first, sizeof(arr_first) / sizeof(double));

    double arr_second[6] = {6.0, 5.0, 4.0, 3.0, 2.0, 1.0};
    struct Mat second = certain(2,3, arr_second, sizeof(arr_second) / sizeof(double));

    struct Mat rez_add = sum(first, second);

    int flag = (sum(zero(2,2), first).rows == empty().rows);
    for (unsigned int dx = 0; dx < rez_add.rows * rez_add.cols; dx++){
        flag *= (abs(rez_add.data[dx] - 7.0) < Comparison_const);
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
    struct Mat first = certain(2, 3, arr_first, sizeof(arr_first) / sizeof(double));

    double arr_second[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    struct Mat second = certain(2, 3, arr_second, sizeof(arr_second) / sizeof(double));

    struct Mat rez_sub = subtraction(first, second);

    int flag = (subtraction(zero(2,2), one(3, 3)).rows == empty().rows);
    for (unsigned int dx = 0; dx < rez_sub.rows * rez_sub.cols; dx++){
        flag *= (abs(rez_sub.data[dx] - 0.0) < Comparison_const);
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
    struct Mat first = certain(2, 3, arr_first, sizeof (arr_first) / sizeof (double));

    double arr_second[3] = {1.0, 0.0, 1.0};
    struct Mat second = certain(3, 1, arr_second, sizeof (arr_second) / sizeof (double));

    struct Mat rez_mul = multiplication(first, second);

    int flag = (multiplication(zero(2,3), one(2, 2)).rows == empty().rows);
    for (unsigned int dx = 0; dx < rez_mul.rows * rez_mul.cols; dx++){
        flag *= (abs(rez_mul.data[dx] - 7.0) < Comparison_const);
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
    struct Mat obj = undef_mat(n, n);
    for (unsigned int dx = 0; dx < obj.rows * obj.cols; dx++){
        obj.data[dx] = rand() % Max_range;
    }

    struct Mat rez = multiplication(obj, reverse(obj));
    struct Mat one_3 = one(n, n);

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
    struct Mat base = undef_mat(3, 3);
    for (unsigned int dx = 0; dx < base.rows * base.cols; dx++){
        base.data[dx] = rand() % Max_range;
    }

    struct Mat option_1 = exponent(base, 3);
    struct Mat option_2 = sum(one(3, 3), sum(base, multiplication_k(multiplication(base, base), 0.5)));

    int flag = (option_1.rows == option_2.rows);
    for (unsigned int dx = 0; dx < option_1.rows * option_1.cols; dx++){
        flag *= (abs(option_1.data[dx] - option_2.data[dx]) < Comparison_const);
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
    struct Mat A = undef_mat(5, 5);
    struct Mat B = undef_mat(5, 5);

    for (unsigned int dx = 0; dx < A.rows * A.cols; dx++){
        A.data[dx] = rand() % Max_range;
    }
    for (unsigned int dx = 0; dx < B.rows * B.cols; dx++){
        B.data[dx] = rand() % Max_range;
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
    output(transponation(A));

    printf("This is matrix A + B\n");
    output(sum(A,B));
    printf("This is matrix A - B\n");
    output(subtraction(A,B));
    printf("This is matrix A * B\n");
    output(multiplication(A, B));
    printf("This is matrix A * 0.33\n");
    output(multiplication_k(A, 0.33));

    printf("This is det of matrix A\n");
    printf("%.2lf\n\n", det(A));

    printf("This is reverse of matrix A\n");
    output(reverse(A));
    printf("This is matrix A in degree 3\n");
    output(pow_m(A, 3));

    printf("This is exp of Matrix A\n");
    output(exponent(A, 3));
}

int main() {

    block_tests();
    block_output();

    return 0;
}
