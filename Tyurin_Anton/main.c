#include <stdio.h>
#include <math.h>
#include <malloc.h>


struct Matrix {
    unsigned int cols;
    unsigned int rows;
    double *values;
};


struct Matrix zero(const unsigned int cols, const unsigned int rows){// Инициализация матрицы A
    struct Matrix A;
    A.cols = cols;
    A.rows = rows;
    A.values = malloc(cols * rows * sizeof(double));
    for (unsigned int idx = 0; idx < cols * rows; idx++){
        A.values[idx] = 0.0;
    }
    return A;
};


struct Matrix one(const unsigned int cols, const unsigned int rows){// Инициализация матрицы B
    struct Matrix B;
    B.cols = cols;
    B.rows = rows;
    B.values = malloc(cols * rows * sizeof(double));
    for (unsigned int idx = 0; idx < cols * rows; idx++){
        B.values[idx] = 0.0;
    }
    return B;
};


void print_matrix(const struct Matrix X){// Вывод матрицы на экран
    printf("Matrix \n");
    for (unsigned int row = 0; row < X.rows; row++){
        for(unsigned int col = 0; col < X.cols; col++){
            scanf("%lf",&(X.values[row * X.cols + col]));
        }
    }
    for (unsigned int row = 0; row < X.rows; row++){
        for(unsigned int col = 0; col < X.cols; col++){
            printf("%.1lf\t", X.values[row * X.cols + col]);
        }
        printf("\n");
    }
}


void matrix_sum(struct Matrix A, struct Matrix B){
    switch ((A.cols == B.cols)*(A.rows == B.rows)) {
        case 1: for (unsigned int row = 0; row < A.rows; row++) {
                for (unsigned int col = 0; col < A.cols; col++) {
                A.values[row * A.cols + col] += B.values[row * B.cols + col];
                }
            }
            printf("A+B=\n");
            for (unsigned int row = 0; row < A.rows; row++){
                for(unsigned int col = 0; col < A.cols; col++){
                    printf("%.1lf\t", A.values[row * A.cols + col]);
                }
                printf("\n");
            }
            break;


        case 0: printf("Can't be solved!");break;
    }
}


void matrix_min(struct Matrix A, struct Matrix B){
    switch ((A.cols == B.cols)*(A.rows == B.rows)) {
        case 1: for (unsigned int row = 0; row < A.rows; row++) {
                for (unsigned int col = 0; col < A.cols; col++) {
                    A.values[row * A.cols + col] -= B.values[row * B.cols + col];
                }
            }
            printf("A-B=\n");
            for (unsigned int row = 0; row < A.rows; row++){
                for(unsigned int col = 0; col < A.cols; col++){
                    printf("%.1lf\t", A.values[row * A.cols + col]);
                }
                printf("\n");
            }
            break;


        case 0: printf("Can't be solved!");break;
    }
}


void matrix_mult(struct Matrix A, struct Matrix B) {

    struct Matrix C;
    C.cols = A.rows;
    C.rows = B.cols;
    C.values = malloc(C.cols * C.rows * sizeof(double));
    for (unsigned int idx = 0; idx < C.cols * C.rows; idx++) {
        C.values[idx] = 0.0;
    }
    for (unsigned int row = 0; row < A.rows; row++){
    for (unsigned int col = 0; col < B.cols; col++) {

            int sum = 0;
            int sum1 = 0;
            for(unsigned int k = 0; k < A.cols; k++) {
               sum1 += A.values[k * A.cols + row] * B.values[k * B.cols + col];
               C.values[col * C.cols + row] = sum1;

               sum += A.values[row * A.cols + k] * B.values[k * B.cols + col];
               C.values[col * C.rows + row] = sum;
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
}





int main() {

    struct Matrix A = zero(1,4);
    print_matrix(A);

    struct Matrix B = one(4,1);
    print_matrix(B);


    matrix_mult(A,B);

    free(A.values);
    free(B.values);
    return 0;
}
