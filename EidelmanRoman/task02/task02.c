#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include <math.h>

typedef struct {
    unsigned int rows;
    unsigned int cols;
    double **values;
    double *data;
} Matrix;

void matrix_memory(Matrix *name)
{
    name->data = (double*)malloc(name->rows * name->cols * sizeof(double) + name->rows * sizeof(double*));
    name->values = name->data + name->rows * name->cols;
    for (int row = 0; row < name->rows; row++)
        name->values[row] = name->data + row * name->cols;
}

void freeing_memory(Matrix *name)
{
    free(name->data);
}

void null_array(Matrix *name)
{
    matrix_memory(name);

    for (int rows = 0; rows < name->rows; rows++)
    {
        for(int cols = 0; cols < name->cols; cols++)
        {
            name->values[rows][cols] = 0;
        }
    }
}

void random_array(Matrix *name)
{
    matrix_memory(name);

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

    Matrix addition_matrix = {2, 2, NULL, NULL};
    matrix_memory(&addition_matrix);

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

    Matrix subtraction_matrix = {2, 2, NULL, NULL};
    matrix_memory(&subtraction_matrix);

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

    freeing_memory(&subtraction_matrix);
}

void multiplication (Matrix A, Matrix B)
{
    printf("MULTIPLICATION:\n");

    Matrix multiplication_matrix = {2, 2, NULL, NULL};
    null_array(&multiplication_matrix);

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

    freeing_memory(&multiplication_matrix);
}

void transposition (Matrix A)
{
    printf("TRANSPOSITION:\n");

    Matrix copy_matrix = {2, 2, NULL, NULL};
    matrix_memory(&copy_matrix);

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

    freeing_memory(&copy_matrix);
}

void exponent (Matrix A)
{
    printf("EXPONENTIAL MATRIX:\n");

    Matrix exp_matrix = {2, 2, NULL, NULL};
    matrix_memory(&exp_matrix);
    for (int rows = 0; rows < exp_matrix.rows; rows++)
        for (int cols = 0; cols < exp_matrix.cols; cols++)
            exp_matrix.values[rows][cols] = 1 + A.values[rows][cols];

    Matrix temporarily_matrix = {2, 2, NULL, (double *) A.values};
    matrix_memory(&temporarily_matrix);

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
            }
        }
        k++;
        factorial *= k;
    }

    freeing_memory(&temporarily_matrix);

    for (int rows = 0; rows < exp_matrix.rows; rows++)
    {
        for (int cols = 0; cols < exp_matrix.cols; cols++)
        {
            printf("%lf ", exp_matrix.values[rows][cols]);
        }
        printf("\n");
    }

    freeing_memory(&exp_matrix);
}

void total()
{
    Matrix A = {2, 2, NULL, NULL};
    Matrix B = {2, 2, NULL, NULL};
    random_array(&A);
    random_array(&B);
    addition(A, B);
    subtraction(A, B);
    multiplication(A, B);
    transposition(A);
    exponent(A);
    freeing_memory(&A);
    freeing_memory(&B);
}

int main()
{
    srand(time(NULL));
    total();
}
