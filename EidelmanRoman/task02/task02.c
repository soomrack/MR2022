#include <stdio.h>
#include <stdlib.h>
#include "time.h"

typedef struct {
    unsigned int rows;
    unsigned int cols;
    double **values;
} Matrix;

Matrix A = {2, 2, NULL};
Matrix B = {2, 2, NULL};

void array_creation(Matrix *name)
{
    name->values = (double**)malloc(name->rows * sizeof(double*));
    for (int i = 0; i < name->rows; i++)
        name->values[i] = (double*)malloc(name->cols * sizeof(double));
    for (int i = 0; i < name->rows; i++)
    {
        for(int j = 0; j < name->cols; j++)
        {
            name->values[i][j] = rand() % 9;
            printf("%lf ", name -> values[i][j]);
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
    for (int i = 0; i < addition_matrix.rows; i++)
        addition_matrix.values[i] = (double*)malloc(addition_matrix.cols * sizeof(double));
    for (int i = 0; i < addition_matrix.rows; i++)
    {
        for (int j = 0; j < addition_matrix.cols; j++)
        {
            addition_matrix.values[i][j] = A.values[i][j] + B.values[i][j];
            printf("%lf ", addition_matrix.values[i][j]);
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
    for (int i = 0; i < subtraction_matrix.rows; i++)
        subtraction_matrix.values[i] = (double*)malloc(subtraction_matrix.cols * sizeof(double));
    for (int i = 0; i < subtraction_matrix.rows; i++)
    {
        for (int j = 0; j < subtraction_matrix.cols; j++)
        {
            subtraction_matrix.values[i][j] = A.values[i][j] - B.values[i][j];
            printf("%lf ", subtraction_matrix.values[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void total()
{
    array_creation(&A);
    array_creation(&B);
    addition(A, B);
    subtraction(A, B);
    //multiplication();

}

int main()
{
    srand(time(NULL));
    total();
}