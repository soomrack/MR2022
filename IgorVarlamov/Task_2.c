#include <stdio.h>
#include <stdlib.h>
#include "time.h"


typedef struct Matrix                                           // Объявленик структуры Matrix
{
    unsigned int rows;
    unsigned int cols;
    double** values;
    double* numeric;
} Matrix;


void memory(Matrix* hlp)                                        // Функция выделения памяти под объект структуры
{
    hlp->numeric = (double*)malloc(hlp->rows * hlp->cols * sizeof(double*) + hlp->rows * sizeof(double*));
    hlp->values = hlp->numeric + hlp->rows * hlp->cols;
    for (int row = 0; row < hlp->rows; row++)
        hlp->values[row] = hlp->numeric + row * hlp->cols;
}

    
void free_mem(Matrix* hlp)                                      // Функция освобождения памяти
{
    free(hlp->numeric);
}


void output(Matrix* hlp)                                        // Функция вывода Матрицы типа объекта структуры
{
    for (int rows = 0; rows < hlp->rows; rows++)
    {
        for (int cols = 0; cols < hlp->cols; cols++)
        {
            printf("\t%lf\t", hlp->values[rows][cols]);
        }
        printf("\n");
    }
    printf("\n");
}


void null_array(Matrix* hlp)                                    // Функция заполнения матрицы нулями
{
    memory(hlp);

    for (int rows = 0; rows < hlp->rows; rows++)
    {
        for (int cols = 0; cols < hlp->cols; cols++)
        {
            hlp->values[rows][cols] = 0;
        }
    }
}


void random_array(Matrix* hlp)                                  // Функция заполнения матрицы случайными значениями
{
    memory(hlp);

    for (int rows = 0; rows < hlp->rows; rows++)
    {
        for (int cols = 0; cols < hlp->cols; cols++)
        {
            hlp->values[rows][cols] = rand() % 10;
        }
    }

}


void addition(Matrix A, Matrix B)                               // Функция сложения
{

    printf("  Summation A and B:\n");

    Matrix addition_matrix = { 3, 3, NULL, NULL };
    memory(&addition_matrix);

    for (int rows = 0; rows < addition_matrix.rows; rows++)
    {
        for (int cols = 0; cols < addition_matrix.cols; cols++)
        {
            addition_matrix.values[rows][cols] = A.values[rows][cols] + B.values[rows][cols];
        }
    }


    output(&addition_matrix);
    free_mem(&addition_matrix);
}


void subtraction(Matrix A, Matrix B)                            // Функция вычитания
{
    printf("  Subtraction B from A:\n");

    Matrix subtraction_matrix = { 3, 3, NULL, NULL };
    memory(&subtraction_matrix);

    for (int rows = 0; rows < subtraction_matrix.rows; rows++)
    {
        for (int cols = 0; cols < subtraction_matrix.cols; cols++)
        {
            subtraction_matrix.values[rows][cols] = A.values[rows][cols] - B.values[rows][cols];
        }
    }
    output(&subtraction_matrix);
    free_mem(&subtraction_matrix);
}


void multiplication(Matrix A, Matrix B)                         // Функция умножения
{
    printf("  Multiplication A by B:\n");

    Matrix multiplication_matrix = { 3, 3, NULL, NULL };
    null_array(&multiplication_matrix);

    for (int rows = 0; rows < multiplication_matrix.rows; rows++)
    {
        for (int cols = 0; cols < multiplication_matrix.cols; cols++)
        {
            for (int k = 0; k < multiplication_matrix.rows; k++)
            {
                multiplication_matrix.values[rows][cols] += A.values[rows][k] * B.values[k][cols];
            }
        }
    }
    output(&multiplication_matrix);
    free_mem(&multiplication_matrix);
}


void transposition(Matrix A)                                    // Функция транспонирования
{
    printf("  Transposition A:\n");

    Matrix Tr_matrix = { 3, 3, NULL, NULL };
    memory(&Tr_matrix);

    for (int rows = 0; rows < Tr_matrix.rows; rows++)
    {
        for (int cols = 0; cols < Tr_matrix.cols; cols++)
        {
            Tr_matrix.values[rows][cols] = A.values[cols][rows];
        }
    }
    output(&Tr_matrix);
    free_mem(&Tr_matrix);
}


void exponent(Matrix A)                                         // Функция нахождения экспоненты для матриц 3х3
{
    printf("  Exponent A:\n");

    Matrix exp_matrix = { 2, 2, NULL, NULL };
    memory(&exp_matrix);

    for (int rows = 0; rows < exp_matrix.rows; rows++)
        for (int cols = 0; cols < exp_matrix.cols; cols++)
            exp_matrix.values[rows][cols] = 1 + C.values[rows][cols];

    Matrix temporarily_matrix = { 2, 2, NULL, (double*)C.values };
    memory(&temporarily_matrix);

    long int k = 2;
    long long int factorial = k;
    while (k < 10)
    {
        for (int rows = 0; rows < exp_matrix.rows; rows++)
        {
            for (int cols = 0; cols < exp_matrix.cols; cols++)
            {
                for (int i = 0; i < exp_matrix.rows; i++)
                {
                    temporarily_matrix.values[rows][cols] = temporarily_matrix.values[rows][i] * C.values[i][cols];
                }
            }
        }
        for (int rows = 0; rows < exp_matrix.rows; rows++)
        {
            for (int cols = 0; cols < exp_matrix.cols; cols++)
            {
                exp_matrix.values[rows][cols] += temporarily_matrix.values[rows][cols] / factorial;
            }
        }
        k++;
        factorial *= k;
    }

    free_mem(&temporarily_matrix);
    output(&exp_matrix);
    free_mem(&exp_matrix);
}


int main()
{
    printf("\n\n");

    Matrix A = { 3, 3, NULL, NULL };
    Matrix B = { 3, 3, NULL, NULL };
    Matrix C = { 2, 2, NULL, NULL };

    random_array(&A);
    random_array(&B);
    random_array(&C);

    printf("  Matrix A:\n");
    output(&A);
    printf("  Matrix B:\n");
    output(&B);
    printf("  Matrix C:\n");
    output(&C);

    addition(A, B);
    subtraction(A, B);
    multiplication(A, B);
    transposition(A);
    exponent(A);

    free_mem(&A);
    free_mem(&B);
    free_mem(&C);

    return 0;
}
