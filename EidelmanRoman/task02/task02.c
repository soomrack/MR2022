#include <stdio.h>
#include <stdlib.h>

int **MatrixA;

typedef struct matrix_size {
    unsigned int lines;
    unsigned int columns;
} matrix_size;

matrix_size size = {2, 2};

void array_creation_A {
    MatrixA = (int **)malloc(size.lines * sizeof(int *));
    for (int i = 0; i < lines; i++)
        MatrixA[i] = (int *)malloc(size.columns * sizeof(int));
    for (int i = 0; i < size.lines; i++)
    {
        for(int j = 0; j < size.columns)
        {
            MatrixA[i][j] = rand() % 9;
        }
    }
}



void total() {
    array_creation_A();
    addition();
    subtraction();
    multiplication();

}

int main() {
    total();
}