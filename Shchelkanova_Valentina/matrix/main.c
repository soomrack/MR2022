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

int MAX_VALUE = 10;
int COEFFICIENT = 4;
int n = 5;
const Matrix EMPTY = { 0, 0, NULL };
void free_matrix(Matrix *matrix){
    free(matrix->values);
}

double** matrix_initialization(const unsigned int col, const unsigned int row) {
    double **rez = (double **) malloc(row * sizeof(double *));
    for (unsigned int i = 0; i < row; i++) {
        rez[i] = (double *) malloc(col * sizeof(double *));
    }
    return rez;
}

Matrix init(Matrix A){
    Matrix rez = EMPTY;
    rez.cols = A.cols;
    rez.rows = A.rows;
    rez.values = matrix_initialization(rez.cols,rez.rows);
    return rez;
}

Matrix minor (unsigned int r_row, unsigned int r_col, const Matrix A)  {
    Matrix rez= {A.rows-1, A.cols-1};
    rez.values = matrix_initialization(rez.rows,rez.cols);

    for (unsigned int row=0; row<r_row;row++){
        for (unsigned int col=0;col<r_col; col++){
            rez.values[row][col]= A.values[row][col];
        }
    }
    for (unsigned int row = 0; row < r_row; row++){
        for (unsigned int col = r_col; col < rez.cols; col++){
            rez.values[row][col] = A.values[row][col+1];
        }
    }
    for (unsigned int row = r_row; row < rez.rows; row++){
        for (unsigned int col = 0; col < r_col; col++){
            rez.values[row][col] = A.values[row+1][col];
        }
    }
    for (unsigned int row = r_row ; row <rez.rows; row++){
        for (unsigned int col = r_col; col < rez.cols; col++){
            rez.values[row][col] = A.values[row+1][col+1];
        }
    }
    return rez;
}

Matrix addition(const Matrix A, const Matrix B) {// Сложение двух матриц
    if (A.rows!=B.rows || A.cols != B.cols) {
        return EMPTY;
    }
    Matrix rez = init(A);
    for (unsigned int row = 0; row < rez.rows; row++){
        for (unsigned int col = 0; col < rez.cols; col++){
            rez.values[row][col] = A.values[row][col] + B.values[row][col];
        }
    }
    return rez;
}

Matrix substraction(const Matrix A, const Matrix B) {  // Вычитание двух матриц
    if (A.rows!=B.rows || A.cols != B.cols) {
        return EMPTY;
    }
    Matrix rez = init(A);
    for (unsigned int row = 0; row < rez.rows; row++){
        for (unsigned int col = 0; col < rez.cols; col++){
            rez.values[row][col] = A.values[row][col] - B.values[row][col];
        }
    }
    return rez;
}

Matrix multiplication(const Matrix A, const Matrix B) { //  Произведение двух матриц
    if (A.cols!=B.rows){ return EMPTY;
    }
    Matrix rez = init(A);
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

double determinant( Matrix A) {  // Определитель матрицы
    if (A.cols != A.rows){ return 0.00;}
    if (n == 1 || n==0){return 0.00;}
    double det = 0.00;
    int sign = -1;
    for(unsigned int row = 0; row < A.rows; row++){
        Matrix minor_A = minor(0,row,A);
        det += pow(sign,row) * A.values[0][row] * determinant(minor_A);
        free_matrix(&minor_A);
    }
    return det;
}


Matrix mult_d(const Matrix A, const double k ){
    Matrix rez = init(A);
    for (unsigned int row = 0; row < rez.rows; row++){
        for (unsigned int col = 0; col < rez.cols; col++){
            rez.values[row][col] = A.values[row][col] * k;
        }
    }
    return rez;
}
Matrix copy(const Matrix A) { // копирование матрицы
    Matrix rez = init(A);
    for (unsigned int row = 0; row < rez.rows; row++){
        for (unsigned int col = 0; col < rez.cols; col++){
            rez.values[row][col] = A.values[row][col];
        }
    }
    return rez;
}

Matrix Exp(const Matrix A, int accuracy) { // экпонента
    if (A.cols != A.rows) {
        return EMPTY;
    }
    Matrix new_rez, new_powered, multiplied;
    Matrix rez = init(A);
    Matrix powered = A;
    int factorial = 1;
    for (int acc = 1.0; acc <= accuracy; ++acc) {
        factorial *= acc;

        new_powered = multiplication(powered, A);
        powered = copy(new_powered);
        free_matrix(&new_powered);

        multiplied = mult_d(powered, 1. / factorial);

        new_rez = addition(rez, multiplied);
        rez = copy(new_rez);
        free_matrix(&new_rez);
        free_matrix(&multiplied);
    }
    free_matrix(&powered);
    return rez;
}

void print(Matrix A){

    for (unsigned int row = 0; row < A.rows; row++){
        for (unsigned int col = 0; col < A.cols; col++){
            printf("%.2lf ", A.values[row][col]);
        }
        printf("\n");
    }
    printf("\n");
}

int test(){
    Matrix One = {5,5};
    Matrix Two = {5,5};
    Matrix Add = {5,5};
    Matrix Sub = {5,5};
    Matrix Mu = {5,5};
    Matrix Mud = {5,5};
    One.values = matrix_initialization(One.cols,One.rows );
    Two.values = matrix_initialization(Two.cols, Two.rows);
    Add.values = matrix_initialization(Add.cols, Add.rows);
    Sub.values = matrix_initialization(Sub.cols, Sub.rows);
    Mu.values = matrix_initialization(Mu.cols, Mu.rows);
    Mud.values = matrix_initialization(Mud.cols, Mud.rows);
    int s = 0;
    for (unsigned int row = 0; row < One.rows; row++) {
        for (unsigned int col = 0; col < One.cols; col++) {
            One.values[row][col] = 1.00;
            Two.values[row][col] = 1.00;
            Add.values[row][col] = 2.00;
            Sub.values[row][col] = 0.00;
            Mu.values[row][col] = 5.00;
            Mud.values[row][col] = 1.00 * COEFFICIENT;
            if (abs((addition(One, Two).values[row][col]) == abs(Add.values[row][col]))) { s += 1; }
            if (abs((substraction(One,Two).values[row][col]) == abs(Sub.values[row][col]))){s+=1;}
            if (abs((addition(One,Two).values[row][col]) == abs(Add.values[row][col]))){s+=1;}
            if (abs((multiplication(One,Two).values[row][col]) == abs(Mu.values[row][col]))){s+=1;}
            if (abs((mult_d(One,COEFFICIENT).values[row][col]) == abs(Mud.values[row][col]))) {s+=1;}
        }
    }
    return s;
}

int main() {
    Matrix A = {5,5};
    Matrix B = {5,5};
    srand(time(NULL));
    A.values = matrix_initialization(A.cols, A.rows);
    B.values = matrix_initialization(B.cols, B.rows);
    for (unsigned int row = 0; row < A.rows; row++){
        for (unsigned int col = 0; col < A.cols; col++){
            A.values[row][col] = rand() % MAX_VALUE ;
        }
    }
    for (unsigned int row = 0; row < B.rows; row++){
        for (unsigned int col = 0; col < B.cols; col++){
            B.values[row][col] = rand() % MAX_VALUE;
        }
    }
    printf("%d\n", test());
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
    print(mult_d(A,COEFFICIENT));
    printf("This is matrix.c A minor\n");
    print(minor(4,4,A));
    printf("This is matrix.c A det %f\n", determinant(A));
    printf("This is matrix. A exp\n");
    print(Exp(A,3));
    return 0;
}


