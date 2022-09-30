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










int main() {

    struct Matrix A = zero(2,3);
    print_matrix(A);

    struct Matrix B = one(2,3);
    print_matrix(B);

    matrix_sum(A,B);

    free(A.values);
    free(B.values);
    return 0;
}
