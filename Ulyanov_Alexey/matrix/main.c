#include <stdio.h>
#include "malloc.h"
#include <stdlib.h>
#include <math.h>

const int max_range = 51;

int ** array_initialization(unsigned int col, unsigned int row){
    int ** rez = (int **)malloc(row * sizeof(int *));
    for (int i = 0; i < row; i ++){
        rez[i] = (int *)malloc(col*sizeof(int *));
    }
    return rez;
}

struct matrix {
    unsigned int cols;
    unsigned int rows;

    int **values;
};

struct matrix minor(unsigned int i, unsigned int j, struct matrix x){
    struct matrix rez = {x.cols-1, x.rows-1};
    rez.values = array_initialization(rez.cols, rez.rows);
    for (int k = 0; k < i; k++){
        for (int l = 0; l < j; l++){
            rez.values[k][l] = x.values[k][l];
        }
    }
    for (int k = 0; k < i; k++){
        for (int l = j; l < rez.cols; l++){
            rez.values[k][l] = x.values[k][l+1];
        }
    }
    for (int k = i; k < rez.rows; k++){
        for (int l = 0; l < j; l++){
            rez.values[k][l] = x.values[k+1][l];
        }
    }
    for (int k = i; k < rez.rows; k++){
        for (int l = j; l < rez.cols; l++){
            rez.values[k][l] = x.values[k+1][l+1];
        }
    }
    return rez;
}

struct matrix addition(const struct matrix x, const struct matrix y){
    struct matrix rez = {0, 0};
    if ((x.cols == y.cols) && (x.rows == y.rows)){
        rez.cols = x.cols;
        rez.rows = y.rows;
        rez.values = array_initialization(rez.cols, rez.rows);
        for (int i = 0; i < rez.rows; i++){
            for (int j = 0; j < rez.cols; j++){
                rez.values[i][j] = x.values[i][j] + y.values[i][j];
            }
        }
    } else {
        rez.values = NULL;
    }
    return rez;
}

struct matrix subtraction(const struct matrix x, const struct matrix y){
    struct matrix rez = {0, 0};
    if ((x.cols == y.cols) && (x.rows == y.rows)){
        rez.cols = x.cols;
        rez.rows = y.rows;
        rez.values = array_initialization(rez.cols, rez.rows);
        for (int i = 0; i < rez.rows; i++){
            for (int j = 0; j < rez.cols; j++){
                rez.values[i][j] = x.values[i][j] - y.values[i][j];
            }
        }
    } else {
        rez.values = NULL;
    }
    return rez;
}

struct matrix multiplication(const struct matrix x, const struct matrix y){
    struct matrix rez = {0, 0};
    if ((x.cols == y.rows)){
        rez.rows = x.rows;
        rez.cols = y.cols;
        rez.values = array_initialization(rez.cols, rez.rows);
        for (int i = 0; i < rez.rows; i++){
            for (int j = 0; j < rez.cols; j++){
                rez.values[i][j] = 0;
                for (int k = 0; k < x.cols; k++){
                    rez.values[i][j] += x.values[i][k] * y.values[k][j];
                }
            }
        }

    } else {
        rez.values = NULL;
    }
    return rez;
}

struct matrix multy_k(struct matrix x, int k){
    struct matrix rez = {x.cols, x.rows};
    rez.values = array_initialization(rez.cols, rez.rows);
    for (int i = 0; i < rez.rows; i++){
        for (int j = 0; j < rez.cols; j++){
            rez.values[i][j] = x.values[i][j] * k;
        }
    }
    return rez;
}

long long  int det(struct matrix x){
    if (x.cols == x.rows){
        if (x.cols == 1){
            return x.values[0][0];

        } else {
            long int rez = 0;
            for (int i = 0; i < x.cols; i++) {
                rez += pow(-1, i) * x.values[0][i] * det(minor(0, i, x));
            }
            return rez;
        }
    } else {
        return NULL;
    }
}



struct matrix A = {5, 5};
struct matrix B = {5, 5};


void vivod(struct matrix x){

    for (int i = 0; i < x.rows; i++){
        for (int j = 0; j < x.cols; j++){
            printf("%d ", x.values[i][j]);
        }
        printf("\n");
    }
    printf("\n");

}

int main() {
    A.values = array_initialization(A.cols, A.rows);
    B.values = array_initialization(B.cols, B.rows);
    for (int i = 0; i < A.rows; i++){
        for (int j = 0; j < A.cols; j++){
            A.values[i][j] = rand() % max_range;
        }
    }
    for (int i = 0; i < B.rows; i++){
        for (int j = 0; j < B.cols; j++){
            B.values[i][j] = rand() % max_range;
        }
    }

    printf("This is matrix A\n");
    vivod(A);
    printf("This is matrix B\n");
    vivod(B);
    printf("This is matrix A + B\n");
    vivod(addition(A,B));
    printf("This is matrix A - B\n");
    vivod(subtraction(A,B));
    printf("This is matrix A * B\n");
    vivod(multiplication(A, B));
    printf("This is matrix A * 5\n");
    vivod(multy_k(A, 5));

    printf("This is det of matrix A\n");
    printf("%d", det(A));


    return 0;
}