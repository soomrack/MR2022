#include <stdio.h>
#include "malloc.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>


typedef struct {
    unsigned int cols;
    unsigned int rows;
    double **values;
} Matrix;

Matrix A = {5,5};
Matrix B = {5,5};


double ** array_initialization(unsigned int col, unsigned int row) {
    double **rez = (double **) malloc(row * sizeof(double *));
    for (int i = 0; i < row; i++) {
        rez[i] = (double *) malloc(col * sizeof(double *));
    }
    return rez;
}

Matrix addition(const Matrix a, const Matrix b) { //  Сложение двух матриц
    Matrix rez = {0,0};
if (a.rows==b.rows && a.cols == b.cols){
    rez.rows = a.rows;
    rez.cols = a.cols;
    rez.values = array_initialization(rez.cols,rez.rows);
    for (int i = 0; i < rez.rows; i++){
        for (int j = 0; j < rez.cols; j++){
            rez.values[i][j] = a.values[i][j] + b.values[i][j];
        }
    }
} else {
    printf("Matrix sizes are different. Addition is impossible");
}
return rez;
}

Matrix substraction(const Matrix a, const Matrix b) { //  Вычитание двух матриц
    Matrix rez = {0,0};
    if (a.rows==a.rows && a.cols == a.cols){
        rez.rows = a.rows;
        rez.cols = a.cols;
        rez.values = array_initialization(rez.cols,rez.rows);
        for (int i = 0; i < rez.rows; i++){
            for (int j = 0; j < rez.cols; j++){
                rez.values[i][j] = a.values[i][j] - b.values[i][j];
            }
        }
    } else {
        printf("Matrix sizes are different. Substraction is impossible");
    }
    return rez;
}

Matrix multiplication(const Matrix a, const Matrix b) { //  Произведение двух матриц
    Matrix rez = {0,0};
    if (a.cols==b.rows){
        rez.rows = a.rows;
        rez.cols = b.cols;
        rez.values = array_initialization(rez.cols,rez.rows);
        for (int i = 0; i < rez.rows; i++){
            for (int j = 0; j < rez.cols; j++){
                rez.values[i][j] = 0.00;
                for (int k = 0; k < a.cols; k++) {
                    rez.values[i][j] += a.values[i][k] * b.values[k][j];
                }

            }
        }
    } else {
        printf("Matrices are incompatible. Multiplication is impossible");
    }
    return rez;
}


void print(Matrix a){

    for (int i = 0; i < a.rows; i++){
        for (int j = 0; j < a.cols; j++){
            printf("%.2lf ", a.values[i][j]);
        }
        printf("\n");
    }
    printf("\n");

}

int main() {
    srand(time(NULL));
    A.values = array_initialization(A.cols, A.rows);
    B.values = array_initialization(B.cols, B.rows);
    for (int i = 0; i < A.rows; i++){
        for (int j = 0; j < A.cols; j++){
            A.values[i][j] = rand() % 10 ;
        }
    }
    for (int i = 0; i < B.rows; i++){
        for (int j = 0; j < B.cols; j++){
            B.values[i][j] = rand() % 10 ;
        }
    }

    printf("This is matrix.c A\n");
    print(A);
    printf("This is matrix.c B\n");
    print(B);
    printf("This is matrix.c A + B\n");
    print(addition(A,B));
    printf("This is matrix.c A - B\n");
    print(substraction(A,B));
    printf("This is matrix.c A * B\n");
    print(multiplication(A, B));

    return 0;
}



