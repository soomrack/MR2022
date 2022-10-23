#include <stdio.h>
#include <malloc.h>


struct Matrix {
    unsigned int cols;
    unsigned int rows;
    double *values;
};

struct Matrix matrix_make (const unsigned int cols, const unsigned int rows){  // Инициализация матрицы
    struct Matrix matrix;
    matrix.cols = cols;
    matrix.rows = rows;
    matrix.values = malloc(cols * rows * sizeof(double));
    for (unsigned int idx = 0; idx < cols * rows; idx++){
        matrix.values[idx] = 0.0;
    }
    return matrix;
}

struct Matrix data_input(struct Matrix matrix, double arr[]){
    for (unsigned int idx = 0; idx < matrix.cols * matrix.rows; idx++){
        matrix.values[idx] = arr[idx];
    }
    return matrix;
}

struct Matrix zero(const unsigned int cols, const unsigned int rows){  // Инициализация нулевой матрицы
    struct Matrix Zero;
    Zero.cols = cols;
    Zero.rows = rows;
    Zero.values = malloc(cols * rows * sizeof(double));
    for (unsigned int idx = 0; idx < cols * rows; idx++){
        Zero.values[idx] = 0.0;
    }
    return Zero;
};

struct Matrix one(const unsigned int cols, const unsigned int rows){  // Инициализация единичной матрицы
    struct Matrix One;
    One.cols = cols;
    One.rows = rows;
    One.values = malloc(cols * rows * sizeof(double));
    for (unsigned int row = 0; row < One.rows; row++){
        for(unsigned int col = 0; col < One.cols; col++){
            if (row == col) {
            One.values[row * One.cols + col] = 1.0;}
            else {
            One.values[row * One.cols + col] = 0.0;}
        }
    }
    return One;
};


void print_matrix(const struct Matrix X){// Вывод матрицы на экран
    printf("Matrix \n");
    for (unsigned int row = 0; row < X.rows; row++){
        for(unsigned int col = 0; col < X.cols; col++){
            printf("%.1lf\t", X.values[row * X.cols + col]);
        }
        printf("\n");
    }
}


struct Matrix error(void){
    struct Matrix error;
    error.cols = 0;
    error.rows = 0;
    error.values = NULL;
    return error;
}


struct Matrix matrix_output(const struct Matrix A,char symbol) {
    printf("A %c B=\n", symbol);
    for (unsigned int row = 0; row < A.rows; row++) {
        for (unsigned int col = 0; col < A.cols; col++) {
            printf("%.1lf\t",A.values[row * A.cols + col]);
        }
        printf("\n");
    }
}


struct Matrix matrix_sum(const struct Matrix A,const struct Matrix B){
    struct Matrix C = matrix_make(A.cols,A.rows);
    if ((A.cols != B.cols)||(A.rows != B.rows)) return error();
    for (unsigned int row = 0; row < A.rows; row++) {
        for (unsigned int col = 0; col < A.cols; col++) {
            C.values[row * C.cols + col] = A.values[row * A.cols + col] + B.values[row * B.cols + col];

        }
    }
    return C;
}


struct Matrix matrix_sub(const struct Matrix A, const struct Matrix B) {
    if ((A.cols != B.cols)||(A.rows != B.rows)) return error();
    struct Matrix C = matrix_make(A.cols,A.rows);
    for (unsigned int row = 0; row < A.rows; row++) {
        for (unsigned int col = 0; col < A.cols; col++) {
            C.values[row * C.cols + col] = A.values[row * A.cols + col] - B.values[row * B.cols + col];
        }
    }
    return C;
}

struct Matrix matrix_output1(struct Matrix C) {
    printf("Exponent A =\n");
    for (unsigned int row = 0; row < C.rows; row++) {
        for (unsigned int col = 0; col < C.cols; col++) {
            printf("%.1lf\t", C.values[row * C.cols + col]);
        }
        printf("\n");
    }
}

struct Matrix matrix_mult(const struct Matrix A, const struct Matrix B) {
    if ((A.cols != B.rows)||(A.rows != B.cols)) return error();
    struct Matrix C = matrix_make(B.cols,A.rows);
    for (unsigned int row = 0; row < A.rows; row++) {
        for (unsigned int col = 0; col < B.cols; col++) {
            C.values[row * C.rows + col] = 0;
            for(unsigned int k = 0; k < A.cols; k++) {
                C.values[row * C.cols + col] += A.values[row * A.cols + k] * B.values[k * B.cols + col];
            }
        }
    }
    return C;
}


void test(){
    struct Matrix Zero = zero(2,2);
    struct Matrix One = one(2,2);

    struct Matrix sum = matrix_sum(One,Zero);
    int result_sum;
    for (unsigned int idx = 0; idx < sum.cols * sum.rows; idx++){

        if (sum.values[idx] == 1.0){result_sum = 1;}
    }
    if (result_sum == 1) {printf("Summ Correct\n");}
    else printf("Summ Incorrect\n");
    free(sum.values);

    struct Matrix sub = matrix_sub(Zero,One);
    int result_sub;
    for (unsigned int idx = 0; idx < sub.cols * sub.rows; idx++){

        if (sub.values[idx] == -1.0){result_sub = 1;}
    }
    if (result_sub == 1) {printf("Sub Correct\n");}
    else printf("Sub Incorrect\n");
    free(sub.values);

    struct Matrix mult = matrix_mult(One,Zero);
    int result_mult;
    for (unsigned int idx = 0; idx < mult.cols * mult.rows; idx++){

        if (mult.values[idx] == 0.0){result_mult = 1;}
    }
    if (result_mult == 1) {printf("Mult Correct\n");}
    else printf("Mult Incorrect\n");
    free(mult.values);
}


struct Matrix matrix_exp (const struct Matrix A) {
    struct Matrix exp1 = one(A.cols, A.rows);
    struct Matrix exp = matrix_sum(exp1,A);
    free(exp1.values);
    int factorial = 1;
    struct Matrix numerator = A;
    struct Matrix numerator1;
    for (int n = 2; n < 4; n++) {
        factorial *= n;
        numerator1 = matrix_mult(numerator,A);
        free(numerator.values);
        numerator = numerator1;
        for (unsigned int idx = 0; idx < numerator.cols * numerator.rows; idx++){
            numerator.values[idx] /= factorial;
        }
        exp = matrix_sum(exp,numerator);
        for (unsigned int idx = 0; idx < numerator.cols * numerator.rows; idx++){
            numerator.values[idx] *= factorial;
        }
    }
    return exp;
}

int main() {
// тест функций
    test();
// создание первой матрицы
    struct Matrix A = matrix_make(3,3);
    double arr_A[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    data_input(A, arr_A);
    print_matrix(A);
// создание второй матрицы
    struct Matrix B = matrix_make(3,3);
    double arr_B[] = {9.0,8.0,7.0,6.0, 5.0, 4.0, 3.0, 2.0, 1.0};
    data_input(B, arr_B);
    print_matrix(B);
// математические операции с матрицами
    struct Matrix sum = matrix_sum(A,B);  // сумма
    matrix_output(sum,'+');
    struct Matrix sub = matrix_sub(A,B);  // разность
    matrix_output(sub,'-');
    struct Matrix mult = matrix_mult(A,B);  // умножение
    matrix_output(mult,'*');
    struct Matrix exp = matrix_exp(A);  // матричная экспонента
    matrix_output1(exp);

    free(A.values);
    free(B.values);
    return 0;
}