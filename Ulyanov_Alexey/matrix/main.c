#include <stdio.h>
#include "malloc.h"
#include <stdlib.h>


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



struct matrix addition(struct matrix x, struct matrix y){
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
        rez.values = 0;
    }
    return rez;
}

struct matrix A = {5, 5};
struct matrix B = {5,5};


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
            A.values[i][j] = rand() % 101;
        }
    }
    for (int i = 0; i < B.rows; i++){
        for (int j = 0; j < B.cols; j++){
            B.values[i][j] = rand() % 101;
        }
    }

    vivod(A);
    vivod(B);
    vivod(addition(A,B));
    return 0;
}
