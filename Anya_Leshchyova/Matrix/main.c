#include <stdio.h>
#include <malloc.h>
#include <stdlib.h> // под динамические масивы




typedef struct {  // структура задаёт размеры матрицы и саму матрицу
    unsigned int row; // число строк, целое положительное
    unsigned int col; // число столбцов, целое положительное
    double ** massive;
}matrix;

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
           result.massive[i][j]=0;
            if (i==j){
               result.massive[i][j]=1;
            }

        }
    }
    return result;
}

void mistake (){
    printf("This action is impossible\n");
}

matrix Zero_matrix(){
    matrix zero = {0, 0};
    return zero;
}
int comparison_matrix(matrix A, matrix B) {
    int n = 1;
    if (A.col!=B.col || A.col!=B.col) return 0;
    for (int i = 0; i < A.row; i++) {
        for (int j = 0; j < A.col; j++) {
            if (abs(A.massive[i][j] - B.massive[i][j])>0.00001 ) n = 0;
        }
    }
    return n;
}

// сумма матриц
matrix sum_matrix(const matrix A,const matrix B){
    if(!(A.row==B.row & A.col==B.col) ) {
        mistake();
        //matrix no = {0, 0};
        return Zero_matrix();
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
        //matrix no = {0, 0};
        return Zero_matrix();
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
        //matrix no = {0, 0};
        return Zero_matrix();
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
        return 0.00;
    }
    if (A.col == 1){
        return A.massive[0][0];
    }
    double det=0.00;
    for (int i=0; i< A.col; i++){
        matrix minor_auxiliary = minor (A,0,i);
        det=det+znak*A.massive[0][i]* det_matrix(minor_auxiliary);
        znak *= -1.00;

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
    //matrix no={0,0};
    if (det_A==0) {
        mistake();
        return Zero_matrix();
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


matrix change_matrix( double A[3][3]) {
    matrix result = {3, 3};
    result.massive = memory(result.row, result.col);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.massive[i][j] = A[i][j];
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
    double addition[3][3] ={{1.00,3.00,9.00},
                            {9.00,11.00,17.00},
                            {17.00,19.00,21.00}};
    double subtraction[3][3] ={{-1.00,-1.00,3.00},
                               {-1.00,-1.00,3.00},
                               {-1.00,-1.00,-1.00}};
    double multiplication[3][3] ={{59.00,66.00,73.00},
                                  {119.00,138.00,157.00},
                                  {143.00,170.00,197.00}};
    double inverce[3][3] ={{-2.50,2.75,-1.25},
                           {2.50,-3.00,1.50},
                           {-0.25,0.50,-0.25}};
    double stepen_3[3][3] ={{796.00,977.00,1602.00},
                            {1868.00,2261.00,3530.00},
                            {2476.00,2973.00,4506.00}};

    int n;
    if (metod == '+') {
        matrix sum=change_matrix(addition);
        n=comparison_matrix(A,sum);
    }
    if (metod == '-') {
        matrix min=change_matrix(subtraction);
        n=comparison_matrix(A,min);
    }

    if  (metod == '*') {
        matrix ymn=change_matrix(multiplication);
        n=comparison_matrix(A,ymn);
    }
    if  (metod == 'r') {
        matrix inv=change_matrix(inverce);
        n=comparison_matrix(A,inv);
    }
    if  (metod == '^') {
        matrix step=change_matrix(stepen_3);
        n=comparison_matrix(A,step);
    }
    if (n==0){
        printf("Made a mistake\n");
        printf("\n");
        }
    if (n==1) {
        printf("Operation performed correctly\n");
        printf("\n");
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
    printf("\n");


    printf("          Result A*5=\n");
    Itog (mult_k(A,5));
    printf("          Transpose matrix A =\n");
    Itog(trans(A));
    printf("          Transpose matrix B =\n");
    Itog(trans(B));



    printf("          Inverce matrix A=\n");
    Itog(inverce_matrix(A));
    test(inverce_matrix(A),'r');
    printf("          Inverce matrix B=\n");
    Itog(inverce_matrix(B));

    printf("          Result A^3=\n");

    Itog(stepen(A,3));
    test(stepen(A,3),'^');
    return 0;
}