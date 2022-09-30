#include <stdio.h>
#include <stdint.h>
#include <malloc.h>


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

    return matrix;

}


Matrix new_matrix() {

    uint64_t  rows, cols;

    scanf("%lux%lu", &rows, &cols);
    printf("%lux%lu\n", rows, cols);

    return matrix_init(rows, cols);
}


void filling_matrix(Matrix *matrix) {

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


void plus() {

    Matrix matrix1 = new_matrix();
    filling_matrix(&matrix1);

    Matrix matrix2 = new_matrix();
    filling_matrix(&matrix2);

    Matrix sum_matrix = matrix_init(matrix1.rows, matrix1.rows);

    /*if (plus_check == False)
        return;*/

    for(int row = 0; row <= matrix1.rows-1; row++)
        for(int col = 0; col <= matrix1.cols-1; col++)
            sum_matrix.array[row][col] = matrix1.array[row][col] + matrix2.array[row][col];

    output_matrix(&sum_matrix);
}


int main() {

    plus();

    return 0;
}
