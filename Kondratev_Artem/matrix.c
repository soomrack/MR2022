#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include<iso646.h>


typedef struct Matrix {

    uint64_t rows;
    uint64_t cols;

    long double **array;

} Matrix;


Matrix matrix_init(uint64_t rows, uint64_t cols) {

    struct Matrix matrix;

    matrix.rows = rows;
    matrix.cols  = cols;

    uint64_t array_of_pointers_mem = rows * sizeof(long double *);
    matrix.array = (long double **)malloc(array_of_pointers_mem);

    uint64_t column_array_mem = (cols + 1) * sizeof(long double *);
    for(int row = 0; row <= rows-1; row++)
        matrix.array[row] = (long double *)malloc(column_array_mem);

    free(malloc(array_of_pointers_mem));
    free(malloc(column_array_mem));

    return matrix;

}


void filling_matrix(Matrix *matrix) {

    printf("fill matrix:\n");

    for(int row = 0; row <= matrix->rows-1; row++)
        for(int col = 0; col <= matrix->cols-1; col++)
            scanf("%Lf", &matrix->array[row][col]);

}


void output_matrix(Matrix *matrix) {

    for(int row = 0; row <= matrix->rows-1; row++) {

        for(int col = 0; col <= matrix->cols-1; col++)
            printf("%6.2Lf", matrix->array[row][col]);

        printf("\n");
    }

}


Matrix new_matrix() {

    uint64_t  rows, cols;

    printf("input new matrix parameters:\n");
    scanf("%lux%lu", &rows, &cols);
    printf("%lux%lu\n", rows, cols);

    Matrix matrix = matrix_init(rows, cols);
    filling_matrix(&matrix);

    printf("You entered:\n");
    output_matrix(&matrix);

    return matrix;

}





int matrix_size_comparer(Matrix *matrix1, Matrix *matrix2) {

    uint64_t delta_rows = matrix1->rows - matrix2->rows;
    uint64_t delta_cols = matrix1->cols - matrix2->cols;

    if(delta_rows != 0 or delta_cols != 0)
        return -1;
    else
        return 0;

}


int matrix_addition() {

    Matrix matrix1 = new_matrix();

    Matrix matrix2 = new_matrix();


    if(matrix_size_comparer(&matrix1, &matrix2) == -1) {
        printf("Sizes of matrices are not equals");
        return -1;
    }

    printf("You get:\n");
    Matrix sum_matrix = matrix_init(matrix1.rows, matrix1.rows);

    for(int row = 0; row <= matrix1.rows-1; row++)
        for(int col = 0; col <= matrix1.cols-1; col++)
            sum_matrix.array[row][col] = matrix1.array[row][col] + matrix2.array[row][col];

    output_matrix(&sum_matrix);
}


void matrix_multiplication() {



}


int main() {

    matrix_addition();

    return 0;
}
