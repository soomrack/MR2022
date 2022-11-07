#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include <math.h>

typedef struct {
    unsigned int rows;
    unsigned int cols;
    double **values;
} Matrix;

void array_creation2(Matrix *name)
{
    name->values = (double*)malloc(name->rows * name->cols * sizeof(double));

    for (int rows = 0; rows < name->rows; rows++)
    {
        for(int cols = 0; cols < name->cols; cols++)
        {
            name->values[rows][cols] = rand() % 9;
            printf("%lf ", name -> values[rows][cols]);
        }
        printf("\n");
    }
    printf("\n");
}

void array_creation(Matrix *name)
{
    name->values = (double**)malloc(name->rows * sizeof(double*));
    for (int rows = 0; rows < name->rows; rows++)
        name->values[rows] = (double*)malloc(name->cols * sizeof(double));

    for (int rows = 0; rows < name->rows; rows++)
    {
        for(int cols = 0; cols < name->cols; cols++)
        {
            name->values[rows][cols] = rand() % 9;
            printf("%lf ", name -> values[rows][cols]);
        }
        printf("\n");
    }
    printf("\n");
}

void addition (Matrix A, Matrix B)
{
    printf("SUM:\n");

    Matrix addition_matrix = {2, 2, NULL};
    addition_matrix.values = (double**)malloc(addition_matrix.rows * sizeof(double*));
    for (int rows = 0; rows < addition_matrix.rows; rows++)
        addition_matrix.values[rows] = (double*)malloc(addition_matrix.cols * sizeof(double));

    for (int rows = 0; rows < addition_matrix.rows; rows++)
    {
        for (int cols = 0; cols < addition_matrix.cols; cols++)
        {
            addition_matrix.values[rows][cols] = A.values[rows][cols] + B.values[rows][cols];
            printf("%lf ", addition_matrix.values[rows][cols]);
        }
        printf("\n");
    }
    printf("\n");

}

void subtraction (Matrix A, Matrix B)
{
    printf("SUBTRACTION:\n");
    Matrix subtraction_matrix = {2, 2, NULL};
    subtraction_matrix.values = (double**)malloc(subtraction_matrix.rows * sizeof(double*));
    for (int rows = 0; rows < subtraction_matrix.rows; rows++)
        subtraction_matrix.values[rows] = (double*)malloc(subtraction_matrix.cols * sizeof(double));
    for (int rows = 0; rows < subtraction_matrix.rows; rows++)
    {
        for (int cols = 0; cols < subtraction_matrix.cols; cols++)
        {
            subtraction_matrix.values[rows][cols] = A.values[rows][cols] - B.values[rows][cols];
            printf("%lf ", subtraction_matrix.values[rows][cols]);
        }
        printf("\n");
    }
    printf("\n");
}

void multiplication (Matrix A, Matrix B)
{
    printf("MULTIPLICATION:\n");

    Matrix multiplication_matrix = {2, 2, NULL};
    multiplication_matrix.values = (double**)malloc(multiplication_matrix.rows * sizeof(double*));
    for (int rows = 0; rows < multiplication_matrix.rows; rows++)
        multiplication_matrix.values[rows] = (double*)malloc(multiplication_matrix.cols * sizeof(double));

    for (int rows = 0; rows < multiplication_matrix.rows; rows++)
    {
        for (int cols = 0; cols < multiplication_matrix.cols; cols++)
        {
            for (int k = 0; k < multiplication_matrix.rows; k++)
            {
                multiplication_matrix.values[rows][cols] += A.values[rows][k] * B.values[k][cols];
            }
            printf("%lf ", multiplication_matrix.values[rows][cols]);
        }
        printf("\n");
    }
    printf("\n");

}

void transposition (Matrix A)
{
    printf("TRANSPOSITION:\n");

    Matrix copy_matrix = {2, 2, NULL};
    copy_matrix.values = (double**)malloc(copy_matrix.rows * sizeof(double*));
    for (int rows = 0; rows < copy_matrix.rows; rows++)
        copy_matrix.values[rows] = (double*)malloc(copy_matrix.cols * sizeof(double));

    for (int rows = 0; rows < copy_matrix.rows; rows++)
    {
        for (int cols = 0; cols < copy_matrix.cols; cols++)
        {
            copy_matrix.values[rows][cols] = A.values[cols][rows];
            printf("%lf ", copy_matrix.values[rows][cols]);
        }
        printf("\n");
    }
    printf("\n");

}

void exponent (Matrix A)
{
    printf("EXPONENTIAL MATRIX:\n");
    Matrix exp_matrix = {2, 2, NULL};
    exp_matrix.values = (double**)malloc(exp_matrix.rows * sizeof(double*));
    for (int rows = 0; rows < exp_matrix.rows; rows++)
        exp_matrix.values[rows] = (double*)malloc(exp_matrix.cols * sizeof(double));
    for (int rows = 0; rows < exp_matrix.rows; rows++)
        for (int cols = 0; cols < exp_matrix.cols; cols++)
            exp_matrix.values[rows][cols] = 1 + A.values[rows][cols];

    Matrix temporarily_matrix = {2, 2, A.values};
    temporarily_matrix.values = (double**)malloc(temporarily_matrix.rows * sizeof(double*));
    for (int rows = 0; rows < exp_matrix.rows; rows++)
        temporarily_matrix.values[rows] = (double*)malloc(temporarily_matrix.cols * sizeof(double));

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
                    temporarily_matrix.values[rows][cols] = temporarily_matrix.values[rows][i] * A.values[i][cols];
                }
            }
        }
        for (int rows = 0; rows < exp_matrix.rows; rows++)
        {
            for (int cols = 0; cols < exp_matrix.cols; cols++)
            {
                exp_matrix.values[rows][cols] += temporarily_matrix.values[rows][cols] / factorial;
                printf("%lf ", exp_matrix.values[rows][cols]);
            }
            printf("\n");
        }
        k++;
        factorial *= k;
        printf("\n");
    }
}

void total()
{
    Matrix A = {2, 2, NULL};
    Matrix B = {2, 2, NULL};
    array_creation(&A);
    array_creation(&B);
    addition(A, B);
    subtraction(A, B);
    multiplication(A, B);
    transposition(A);
    exponent(A);
}

int main()
{
    srand(time(NULL));
    total();
}
