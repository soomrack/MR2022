#include <stdio.h>
#include <stdlib.h>
#include "time.h"

typedef struct {
    unsigned int rows;
    unsigned int cols;
    double **values;
} Matrix;

Matrix A = {2, 2};
Matrix B = {2, 2};

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
        }
    }
}

void addition (Matrix A, Matrix B)
{
    Matrix addition_matrix = {2, 2};
    for (int i = 0; i < addition_matrix.rows; i++)
    {
        for (int j = 0; j < addition_matrix.cols; j++)
        {
            addition_matrix.values[i][j] = A.values[i][j] + B.values[i][j];
            printf("%lf ", addition_matrix.values[i][j]);
        }
        printf("\n");
    }
}

void start_output(Matrix *name)
{
    for (int i = 0; i < name -> rows; i++)
    {
        for(int j = 0; j < name -> cols; j++)
            printf("%lf ", name -> values[i][j]);
        printf("\n");
    }
    printf("\n");
}

void total_output()
{
    start_output(&A);
    start_output(&B);
    //addition_output();
    //subtraction_output();
    //multiplication_output();
}

void total()
{
    array_creation(&A);
    array_creation(&B);
    addition(A, B);
    //subtraction();
    //multiplication();
    total_output();

}

int main()
{
    srand(time(NULL));
    total();
}