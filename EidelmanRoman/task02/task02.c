#include <stdio.h>
#include <stdlib.h>

typedef struct matrix_size {
    unsigned int rows;
    unsigned int cols;
    double **Matrix;
} matrix_size;

matrix_size A = {2, 2};

void array_creation(matrix_size *name)
{
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

void output()
{
    for (int i = 0; i < A.rows; i++)
    {
        for(int j = 0; j < A.cols; j++)
        {
            printf("%lf ", A.Matrix[i][j]);
        }
        printf("\n");
    }
}


void total() {
    array_creation(&A);
    //addition();
    //subtraction();
    //multiplication();
    output();

}

int main() {
    total();
}