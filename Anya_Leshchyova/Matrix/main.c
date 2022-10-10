#include <stdio.h>
#include "malloc.h"
#include <stdlib.h> // под динамические масивы
#include <valarray>


typedef struct {  // структура задаёт размеры матрицы и саму матрицу
    unsigned int row; // число строк, целое положительное
    unsigned int col; // число столбцов, целое положительное
    double ** massive;
}matrix;

matrix A = {3, 3};
matrix B = {4, 4};


//row строка, col столбец
// функция возвращает память для матрицы
double **memory (unsigned int row,unsigned int col ){
    double **a;
    a = ( double**)malloc(row * sizeof( double*)); //выделение памяти под указатели на строки
    for ( int i = 0; i<row; i++)  // цикл по строкам
    {
        a[i] = ( double *) malloc(col * sizeof( double));// Выделение памяти под хранение строк
    }
    return a;
}

// сумма матриц
matrix sum_matrix(const matrix A,const matrix B){
    if(!(A.row==B.row and A.col==B.col) ) {
        printf("Addition is Impossible\n");
        matrix no = {0, 0};
        return no;
    }
    matrix sum = {A.row, A.col};
    sum.massive = memory(sum.row, sum.col);
    for (int i = 0; i < sum.row; i++) {
        for (int j = 0; j < sum.col; j++) {
            sum.massive[i][j] = A.massive[i][j] + B.massive[i][j];
        }
    }
    return sum;
}


//вычитание матриц
matrix mun_matrix(const matrix A,const matrix B){
    if(!(A.row==B.row and A.col==B.col) ) {
        printf("Subtraction is impossible\n");
        matrix no = {0, 0};
        return no;
    }
    matrix mun = {A.row, A.col};
    mun.massive = memory(mun.row, mun.col);
    for (int i = 0; i < mun.row; i++) {
        for (int j = 0; j < mun.col; j++) {
            mun.massive[i][j] = A.massive[i][j] - B.massive[i][j];
        }
    }
    return mun;
}



// умножение матриц
matrix ymn_matrix(const matrix A,const matrix B) {
    //printf("Mun impossible\n");
    if (A.row != B.col) {
        printf("Multiplication is impossible\n");
        matrix no = {0, 0};
        return no;
    }
    matrix ymn = {A.row, B.col};
    ymn.massive = memory(ymn.row, ymn.col);
    for (int i = 0; i < ymn.row; i++) {
        for (int j = 0; j < ymn.col; j++) {
            ymn.massive[i][j] = 0;
            for (int h = 0; h < A.col; h++) {
                ymn.massive[i][j] = ymn.massive[i][j] + A.massive[i][h] * B.massive[h][j];
            }
        }

    }
    return ymn;
}



matrix minor (const matrix A, unsigned int x, unsigned int y)  {
    matrix det_min= {A.row-1, B.col-1};
    det_min.massive = memory(det_min.row, det_min.col);
    for (int i=0; i<x;i++){
        for (int j=0;j<y; j++){
            det_min.massive[i][j]=A.massive[i][j];
        }
    }
    for (int i = 0; i < x; i++){
        for (int j = y; j < det_min.col; j++){
            det_min.massive[i][j] = A.massive[i][j+1];
        }
    }
    for (int i = x; i < det_min.row; i++){
        for (int j = 0; j < y; j++){
            det_min.massive[i][j] = A.massive[i+1][j];
        }
    }
    for (int i = x; i <det_min.row; i++){
        for (int j = y; j < det_min.col; j++){
            det_min.massive[i][j] = A.massive[i+1][j+1];
        }
    }


    return det_min;
}

double det_matrix (const matrix A){
    double det=0.00;
    for (int i=0; i< A.row; i++){
        matrix minor_auxiliary = minor (A,i,0);
        det=det+pow(-1,i)*A.massive[i][0]* det_matrix(minor_auxiliary);
        free(minor_auxiliary.massive);
    }
    return det;
}


matrix mult_k(const matrix A, double k) {
    matrix result = {A.row, A.col};
    result.massive = memory(result.row, result.col);
    for (int i = 0; i < A.row; i++) {
        for (int j = 0; j < A.col; j++) {
            result.massive[i][j] = A.massive[i][j] * k;
        }
    }
    return result;
}


// функция вывода
void Itog(matrix A){
    for (int i = 0; i < A.row; i++){
        for (int j = 0; j < A.col; j++){
            printf("%f ", A.massive[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// break работает по-дурацки
void test (matrix A, char metod){
    double addition[3][3] ={{1.00,3.00,5.00},
                            {9.00,11.00,13.00},
                            {17.00,19.00,21.00}};
    double subtraction[3][3] ={{-1.00,-1.00,-1.00},
                               {-1.00,-1.00,-1.00},
                               {-1.00,-1.00,-1.00}};
    double multiplication[3][3] ={{23.00,26.00,29.00},
                                  {83.00,98.00,113.00},
                                  {143.00,170.00,197.00}};
    int n=0;
    for (int i = 0; i < A.row; i++) {
        for (int j = 0; j < A.col; j++) {
            if (metod == '+') {
                if (A.massive[i][j] != addition[i][j])  {
                    n=1;
                }
            }
            if (metod == '-') {
                if (A.massive[i][j] != subtraction[i][j]) {
                    n=1;
                }
            }
            if  (metod == '*') {
                if (A.massive[i][j] != multiplication[i][j]) {
                    n=1;
                }
            }
        }
        if (n!=0){
            printf("false\n");
            break;
        }
    }
    if (n==0) {
        printf("true\n");
    }
}


int main() {
    A.massive = memory(A.row, A.col);
    B.massive = memory(B.row, B.col);
    double n=-1.00,k=-1.00;
    for (int i = 0; i < A.row; i++){
        k=k+1.00;
        for (int j = 0; j < A.col; j++){
            n=n+1.00;
            A.massive[i][j] = k+n;
        }
    }
    n=-1.00;
    k=-1.00;
    for (int i = 0; i < B.row; i++){
        k=k+1.00;
        for (int j = 0; j < B.col; j++){
            n=n+1.00;
            B.massive[i][j] = k+n+1.00;
        }
    }

    printf("          Matrix A=\n");
    Itog(A);

    printf("          Matrix B=\n");
    Itog(B);

    printf("          Result A+B=\n");
    Itog (sum_matrix (A,B));
    test(sum_matrix (A,B),'+');

    printf("          Result A-B=\n");
    Itog (mun_matrix (A,B));
    test(mun_matrix (A,B),'-');

    printf("          Result A*B=\n");
    Itog(ymn_matrix(A,B));
    test(ymn_matrix (A,B),'*');

    printf("Determinant A = %f\n", det_matrix(A));
    printf("Determinant B = %f\n", det_matrix(B));

    printf("\n");
    printf("          Result A*5=\n");
    Itog (mult_k(A,5));

    return 0;
}