#include <stdio.h>
#include <malloc.h>
#include <stdlib.h> // под динамические масивы




typedef struct {
    unsigned int row; // число строк, целое положительное
    unsigned int col; // число столбцов, целое положительное
    double ** massive;
}matrix;  // структура задаёт размеры матрицы и саму матрицу

matrix A = {3, 3};
matrix B = {3, 3};


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

matrix identity_matrix(unsigned int row,unsigned int col ){
    matrix result = {row, col};
    result.massive = memory(result.row, result.col);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j <col; j++) {
            result.massive[i][j]=1;
        }
    }
    return result;
}

void mistake (){
    printf("This action is impossible\n");
}

int comparison_matrix(matrix A, matrix B) {
    int n = 1;
    for (int i = 0; i < A.row; i++) {
        for (int j = 0; j < A.col; j++) {
            if (A.massive[i][j] != B.massive[i][j]) n = 0;
        }
    }
    return n;
}

// сумма матриц
matrix sum_matrix(const matrix A,const matrix B){
    if(!(A.row==B.row & A.col==B.col) ) {
        mistake();
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
    if(!(A.row==B.row & A.col==B.col) ) {
        mistake();
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
    int n_A;
    int n_B;
    if (A.row != B.col) {
        mistake();
        matrix no = {0, 0};
        return no;
    }
    n_A=comparison_matrix(identity_matrix(A.row,A.col),A);
    n_B=comparison_matrix(identity_matrix(B.row,B.col),B);
    if (n_A==1) return B;
    if (n_B==1) return A;
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



matrix minor (const matrix A,  int x,  int y)  {
    matrix det_min= {A.row-1, A.col-1};
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
    double znak = 1.00;
    if (A.col != A.row) {
        mistake();
        return 0.0;
    }
    if (A.col == 1){
        return A.massive[0][0];
    }
    double det=0.00;
    for (int i=0; i< A.col; i++){
        matrix minor_auxiliary = minor (A,0,i);
        det=det+znak*A.massive[0][i]* det_matrix(minor_auxiliary);
        znak *= -1.00;
        //printf("fdfdfdf %f\n", det);
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

matrix trans (const matrix A) {
    matrix result = {A.col, A.row};
    result.massive = memory(result.row, result.col);
    for (int i = 0; i < A.row; i++) {
        for (int j = 0; j < A.col; j++) {
            result.massive[i][j] = A.massive[j][i];
        }
    }
    return result;
}

double minor_k(matrix A, unsigned int x,unsigned int y) {
    double k;
    for (int i = 0; i < A.row; i++) {
        for (int j = 0; j < A.col; j++) {
            if (i==x & j==y & x==y==0){
                k=A.massive[1][1];
            }
            if (i==x & j==y & x==y==1){
                k=A.massive[0][0];
            }
            if (i==x & j==y & x!=y ){
                k=A.massive[j][i];
            }
        }
    }
    return k;
}

matrix inverce_matrix (matrix A){
    double det_A= det_matrix(A);
    double znak=1.00;
    matrix result = {A.row, A.col};
    result.massive = memory(result.row, result.col);
    matrix result_trans = {A.row, A.col};
    result_trans.massive = memory( result_trans.row,  result_trans.col);
    matrix no={0,0};
    if (det_A==0) {
        mistake();
        return no;
    }
    if (A.row==A.col==2) {
        for (int i = 0; i < A.row; i++) {
            for (int j = 0; j < A.col; j++) {
                result.massive[i][j] = znak* minor_k(A, i, j)/det_A;
                znak=-1*znak;
            }
        }
        result_trans=trans(result);
        return  result_trans;
    }

    for (int i = 0; i < A.row; i++) {
        for (int j = 0; j < A.col; j++) {
            matrix minor_auxiliary = minor(A, i, j);
            result.massive[i][j] = znak * det_matrix(minor_auxiliary) / det_A;
            znak=-1*znak;

        }
    }
    result_trans=trans(result);
    return  result_trans;

}


matrix stepen (const matrix A,int  n){
    matrix result=identity_matrix(A.row,A.col);
    int i=1;
    while (i<=n){
        result=ymn_matrix(result,A);
        i++;
    }
    return  result;
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
    matrix addition ={3,3};
    addition.massive =memory(3,3);
    addition.massive[0][0]=1.00;
    addition.massive[0][1]=3.00;
    addition.massive[0][2]=9.00;
    addition.massive[1][0]=9.00;
    addition.massive[1][1]=11.00;
    addition.massive[1][2]=17.00;
    addition.massive[2][0]=17.00;
    addition.massive[2][1]=19.00;
    addition.massive[2][2]=21.00;
    double subtraction[3][3] ={{-1.00,-1.00,3.00},
                               {-1.00,-1.00,3.00},
                               {-1.00,-1.00,-1.00}};
    double multiplication[3][3] ={{59.00,66.00,73.00},
                                  {119.00,138.00,157.00},
                                  {143.00,170.00,197.00}};
    int n=1;
    if (metod == '+') {
        n=comparison_matrix(A,addition);
    }

    for (int i = 0; i < A.row; i++) {
        for (int j = 0; j < A.col; j++) {

            if (metod == '-') {
                if (A.massive[i][j] != subtraction[i][j]) {
                    n=0;
                }
            }
            if  (metod == '*') {
                if (A.massive[i][j] != multiplication[i][j]) {
                    n=0;
                }
            }
        }
        if (n==0){
            printf("false\n");
            break;
        }
    }
    if (n==1) {
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
            A.massive[1][2] = 10;
            A.massive[0][2] = 6;
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

    // printf("\n");
    printf("          Result A*5=\n");
    Itog (mult_k(A,5));
    printf("          Transpose matrix A =\n");
    Itog(trans(A));
    printf("          Transpose matrix B =\n");
    Itog(trans(B));



    printf("          Inverce matrix A=\n");
    Itog(inverce_matrix(A));
    printf("          Inverce matrix B=\n");
    Itog(inverce_matrix(B));

    printf("          Result A^3=\n");

    Itog(stepen(A,3));
    return 0;
}