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
int max_value = 10;
int coefficient = 4;
int n = 5;

Matrix empty(){
    Matrix Null_Matrix = {0,0, NULL};
    return Null_Matrix;
}


double ** array_initialization(const unsigned int col, const unsigned int row) {
    double **rez = (double **) malloc(row * sizeof(double *));
    for (int i = 0; i < row; i++) {
        rez[i] = (double *) malloc(col * sizeof(double *));
    }
    return rez;
}

Matrix minor (int r_row,  int r_col, const Matrix a)  {
    Matrix rez= {A.rows-1, A.cols-1};
    rez.values = array_initialization(rez.rows,rez.cols);

    for (int row=0; row<r_row;row++){
        for (int col=0;col<r_col; col++){
            rez.values[row][col]= a.values[row][col];
        }
    }
    for (int row = 0; row < r_row; row++){
        for (int col = r_col; col < rez.cols; col++){
            rez.values[row][col] = a.values[row][col+1];
        }
    }
    for (int row = r_row; row < rez.rows; row++){
        for (int col = 0; col < r_col; col++){
            rez.values[row][col] = a.values[row+1][col];
        }
    }
    for (int row = r_row ; row <rez.rows; row++){
        for (int col = r_col; col < rez.cols; col++){
            rez.values[row][col] = a.values[row+1][col+1];
        }
    }
    return rez;
}

Matrix addition(const Matrix a, const Matrix b) {// Сложение двух матриц
    Matrix rez = {0,0, NULL};
    if (a.rows!=b.rows || a.cols != b.cols) {
        return empty();
    }
        rez.rows = a.rows;
        rez.cols = a.cols;
        rez.values = array_initialization(rez.cols,rez.rows);
        for (int i = 0; i < rez.rows; i++){
            for (int j = 0; j < rez.cols; j++){
                rez.values[i][j] = a.values[i][j] + b.values[i][j];
            }
        }
    return rez;
}

Matrix substraction(const Matrix a, const Matrix b) {  // Вычитание двух матриц
    Matrix rez = {0,0, NULL};
    if (a.rows!=b.rows || a.cols != b.cols) {
        return empty();
    } else{
        rez.rows = a.rows;
        rez.cols = a.cols;
        rez.values = array_initialization(rez.cols,rez.rows);
        for (unsigned int i = 0; i < rez.rows; i++){
            for (unsigned int j = 0; j < rez.cols; j++){
                rez.values[i][j] = a.values[i][j] - b.values[i][j];
            }
        }
    }
    return rez;
}

Matrix multiplication(const Matrix A, const Matrix B) { //  Произведение двух матриц
    Matrix rez = empty();
    if (a.cols!=b.rows){ return empty();
    }
        rez.rows = A.rows;
        rez.cols = A.cols;
        rez.values = array_initialization(rez.cols,rez.rows);
        for (unsigned int row = 0; row < rez.rows; row++){
            for (unsigned int col = 0; col < rez.cols; col++){
                rez.values[row][col] = 0.00;
                for (int k = 0; k < A.cols; k++) {
                    rez.values[row][col] += A.values[row][k] * B.values[k][col];
                }

            }
        }
    return rez;
}

double det(const Matrix A) {  // Определитель матрицы
    if (A.cols != A.rows){ return 0.00;}
    if (n == 1 || n==0){return 0.00;}
    double rez = 0.00;
    int znak = 1;
    for(unsigned int row = 0; row < A.rows; row++){
        Matrix minor_a = minor(0,row,a);
        rez = rez + znak * A.values[0][row] * det(minor_a);
        znak *= -1.00;
    }
    return rez;
}


Matrix mult_d(const Matrix A, const double k ){
    Matrix rez = {0,0, NULL};
    rez.cols=A.cols;
    rez.rows=A.rows;
    rez.values = array_initialization(rez.cols,rez.rows);
    for (int row = 0; row < rez.rows; row++){
        for (int col = 0; col < rez.cols; col++){
            rez.values[row][col] = a.values[row][col] * k;
        }
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
            A.values[i][j] = rand() % max_value ;
        }
    }
    for (int i = 0; i < B.rows; i++){
        for (int j = 0; j < B.cols; j++){
            B.values[i][j] = rand() % max_value;
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
    printf("This is matrix.c A * k\n");
    print(mult_d(A,coefficient));
    printf("This is matrix.c A minor\n");
    print(minor(4,4,A));
    printf("This is matrix.c A det %f\n", det(A));
    return 0;

}

