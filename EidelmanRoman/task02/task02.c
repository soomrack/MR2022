#include <stdio.h>
#include <stdlib.h>
#include "time.h"

typedef struct matrix_size {
    unsigned int rows;
    unsigned int cols;
    double **Matrix;
} matrix_size;

matrix_size A = {2, 2};
matrix_size B = {2, 2};
matrix_size addition_matrix = {2, 2};

void array_creation(matrix_size *name)
{
    srand(time(NULL));
    name->Matrix = (int**)malloc(name->rows * sizeof(int*));
    for (int i = 0; i < name->rows; i++)
        name->Matrix[i] = (int*)malloc(name->cols * sizeof(int));
    for (int i = 0; i < name->rows; i++)
    {
        for(int j = 0; j < name->cols; j++)
        {
            name->Matrix[i][j] = rand() % 9;
        }
    }
}

void addition()
{

}

void start_output(matrix_size *name)
{
    printf("Matrix %s \n", name);
    for (int i = 0; i < name -> rows; i++)
    {
        for(int j = 0; j < name -> cols; j++)
        {
            printf("%lf ", name -> Matrix[i][j]);
        }
        printf("\n");
    }
}

void total_output()
{
    start_output(&A);
    //addition_output();
    //subtraction_output();
    //multiplication_output();
}

void total()
{
    array_creation(&A);
    //addition();
    //subtraction();
    //multiplication();
    total_output();

}

int main()
{
    total();
}