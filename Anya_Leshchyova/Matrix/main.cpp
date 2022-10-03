#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h> // под динамические масивы

typedef struct {  // структура задаёт размеры матрицы и саму матрицу
    unsigned int row; // число строк, целое положительное
    unsigned int col; // число столбцов, целое положительное
    int ** massive;
}matrix;

matrix A = {4, 4};
matrix B = {4, 4};




//row строка, col столбец
// функция возвращает память для матрицы
int **memory (unsigned int row,unsigned int col ){
    int **a;
    a = (int**)malloc(row * sizeof(int*)); //выделение памяти под указатели на строки
    for (int i = 0; i<row; i++)  // цикл по строкам
    {
        a[i] = (int *) malloc(col * sizeof(int));// Выделение памяти под хранение строк
    }
    return a;
}

// сумма матриц
matrix sum_matrix(const matrix A,const matrix B){
    if(A.row==B.row and A.col==B.col ) {
        matrix sum = {A.row, A.col};
        sum.massive = memory(sum.row, sum.col);
        for (int i = 0; i < sum.row; i++) {
            for (int j = 0; j < sum.col; j++) {
                sum.massive[i][j] = A.massive[i][j] + B.massive[i][j];

            }
        }
        return sum;
    }
    else {
        printf("Addition is Impossible\n");
        matrix no = {0, 0};
        no.massive = memory(no.row, no.col);


        return no;
    }
}


//вычитание матриц
matrix mun_matrix(const matrix A,const matrix B){
    if(A.row==B.row and A.col==B.col ) {
        matrix mun = {A.row, A.col};
        mun.massive = memory(mun.row, mun.col);
        for (int i = 0; i < mun.row; i++) {
            for (int j = 0; j < mun.col; j++) {
                mun.massive[i][j] = A.massive[i][j] - B.massive[i][j];

            }
        }
        return mun;
    }
    else {
        printf("Subtraction is impossible\n");
        matrix no = {0, 0};
        no.massive = memory(no.row, no.col);
        return no;
    }
}


// умножение матриц
matrix ymn_matrix(const matrix A,const matrix B) {
    //printf("Mun impossible\n");
    if (A.row == B.col) {
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
    else {
        printf("Multiplication is impossible\n");
        matrix no = {0, 0};
        no.massive = memory(no.row, no.col);
        return no;

    }
}

// функция вывода
void Itog(matrix A){
    for (int i = 0; i < A.row; i++){
        for (int j = 0; j < A.col; j++){
            printf("%d ", A.massive[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}




int main()
{
    A.massive = memory(A.row, A.col);
    B.massive = memory(B.row, B.col);
    for (int i = 0; i < A.row; i++){
        for (int j = 0; j < A.col; j++){
            A.massive[i][j] = rand() %1001; //матрицы создаются рандомом
        }
    }
    for (int i = 0; i < B.row; i++){
        for (int j = 0; j < B.col; j++){
            B.massive[i][j] = rand() %50;
        }
    }

    printf("          Matrix A=\n");
    Itog(A);
    printf("          Matrix B=\n");
    Itog(B);
    printf("          Result A+B=\n");
    Itog (sum_matrix (A,B));
    printf("          Result A-B=\n");
    Itog (mun_matrix (A,B));
    printf("          Result A*B=\n");
    Itog(ymn_matrix(A,B));

    return 0;
}