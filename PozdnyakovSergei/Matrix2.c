#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>


typedef struct  {
    unsigned int rows; //строка
    unsigned int cols; //столбец
    double ** matrix;
} Matrix;

Matrix A = {3, 3};
Matrix B = {3, 3};


int ** memory (unsigned int rows, unsigned int cols){ //выделение памяти
    long int **m;
    m = (int**) malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++){
        m[i] = (int*) malloc(cols *sizeof (int));
    }
    return m;
}


Matrix summation (const Matrix A, Matrix B){ //const тк эти матрицы в процессе вычислений не изменяются
    if (A.rows == B.rows) and (A.cols == B.cols){ //суммировать можно только матрицы с равным числом и строк и столбцов
        Matrix summation = {B.rows, B.cols};
        summation.matrix = memory(summation.rows; summation.cols);
        for (int i = 0; i < summation.rows; i++){
            for (int j = 0; j < summation.cols; j++){
                summation.matrix[i][j] = A.matrix[i][j] + B.matrix[i][j];
            }
        }
        return summation;
    }
    else{
        printf("Impossible\n");
        return 0;
    }
}


Matrix subtraction (const Matrix A, Matrix B){ //const тк эти матрицы в процессе вычислений не изменяются
    if (A.rows == B.rows and A.cols == B.cols){ //вычитать можно только матрицы с равным числом и строк и столбцов
        Matrix subtraction = {B.rows, B.cols};
        subtraction.matrix = memory(subtraction.rows ; subtraction.cols);
        for (int i = 0; i < subtraction.rows; i++){
            for (int j = 0; j < subtraction.cols; j++){
                subtraction.matrix[i][j] = A.matrix[i][j] - B.matrix[i][j];
            }
        }
        return subtraction;
    }
    else{
        printf("Impossible\n");
        return 0;
    }
}


Matrix multiplying(const Matrix A; const Matrix B){
    if (A.rows == B.cols){
        Matrix multiplying = {A.rows, B.cols};
        multiplying.matrix = memory(multiplying.rows, multiplying.cols);
        for (int i = 0; i < multiplying.rows; i++){
            for (int j = 0; j < multiplying.cols; j++){
                multiplying.matrix[i][j] = 0;
                for (int x = 0; x < A.cols; x++){
                    multiplying.matrix[i][j] = multiplying.matrix[i][j] + A.matrix[i][h]*B.matrix[h][j];
                }
            }
        }
        return multiplying;
    }
    else{
        printf("Impossible")
        return 0;
    }
}


void result(Matrix A){
    for (int i = 0; i < A.row; i++){
        for (int j = 0; j < A.col; j++){
            printf("%d ", A.matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


int main() {
    A.matrix = memory( A.rows; A.cols);
    B.matrix = memory( B.rows; B.cols);
    for (int i = 0; i < A.rows; i++){
        for (int j = 0; j < A.cols; j++){
            A.matrix[i][j] = rand() %100; //заполнение ячеек матрицы А рандомными числами от 0 до 100
        }
    }
    for (int i = 0; i < B.rows; i++){
        for (int j = 0; j < B.cols; j++){
            B.matrix[i][j] = rand() %100; //заполнение ячеек матрицы B рандомными числами от 0 до 100
        }
    }

    printf("Matrix A=\n");
    result (A);
    printf("Matrix B=\n");
    result (B);
    printf("result A+B\n");
    result (summation(A,B));
    printf("result A-B\n");
    result (subtraction(A,B));
    printf("result A*B\n");
    result (multiplying(A,B));

    return 0;
}
