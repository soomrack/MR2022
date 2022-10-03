#include <stdio.h>
#include <math.h>
#include <malloc.h>


struct Matrix {
    unsigned int cols;
    unsigned int rows;
    double *values;
};

struct Matrix matrix_make (const unsigned int cols, const unsigned int rows, struct Matrix matrix){  // Инициализация матрицы
    matrix.cols = cols;
    matrix.rows = rows;
    matrix.values = malloc(cols * rows * sizeof(double));
    for (unsigned int idx = 0; idx < cols * rows; idx++){
        matrix.values[idx] = 0.0;
    }
return matrix;
};

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
    for (unsigned int idx = 0; idx < cols * rows; idx++){
        One.values[idx] = 1.0;
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
    error.cols = 2;
    error.rows = 2;
    error.values = malloc(error.cols * error.rows * sizeof(double));
    for (unsigned int idx = 0; idx < error.cols * error.rows; idx++){
        error.values[idx] = 0.0;
    }

    return error;
}

struct Matrix matrix_sum(const struct Matrix A,const struct Matrix B){
    if ((A.cols != B.cols)*(A.rows != B.rows)) return error();
        for (unsigned int row = 0; row < A.rows; row++) {
            for (unsigned int col = 0; col < A.cols; col++) {
                A.values[row * A.cols + col] += B.values[row * B.cols + col];
            }
        }
    return A;
}

struct Matrix matrix_sub(const struct Matrix A, const struct Matrix B){
    if ((A.cols != B.cols)*(A.rows != B.rows)) return error();
    for (unsigned int row = 0; row < A.rows; row++) {
        for (unsigned int col = 0; col < A.cols; col++) {
            A.values[row * A.cols + col] -= B.values[row * B.cols + col];
        }
    }
    return A;
}

struct Matrix matrix_mult(const struct Matrix A, const struct Matrix B) {

    struct Matrix C;
    C.cols = A.rows;
    C.rows = B.cols;
    C.values = malloc(C.cols * C.rows * sizeof(double));

    for (unsigned int row = 0; row < A.rows; row++){
        for (unsigned int col = 0; col < B.cols; col++) {
        C.values[col * C.rows + row] = 0;
            for(unsigned int k = 0; k < A.cols; k++) {
                C.values[col * C.rows + row] += A.values[row * A.cols + k] * B.values[k * B.cols + col];
            }
        }
    }

        printf("A*B=\n");
        for (unsigned int row = 0; row < C.rows; row++) {
            for (unsigned int col = 0; col < C.cols; col++) {
                printf("%.1lf\t", C.values[col * C.cols + row]);
            }
            printf("\n");
    }
    return C;
}





int main() {

    struct Matrix A = matrix_make(3,2,A);
    double arr_A[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    data_input(A, arr_A);
    print_matrix(A);

    struct Matrix B = matrix_make(2,3,B);
    double arr_B[] = {6.0, 5.0, 4.0, 3.0, 2.0, 1.0};
    data_input(B, arr_B);
    print_matrix(B);

    matrix_sum(A,B);
    matrix_sub(A,B);
    matrix_mult(A,B);

    free(A.values);
    free(B.values);
    return 0;
}
