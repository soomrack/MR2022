#include <stdio.h>
#include <stdint.h>
#include <malloc.h>


typedef struct Matrix {

    uint64_t rows;
    uint64_t cols;

    long double **array;

} Matrix;


Matrix matrix_init() {

    uint64_t rows;
    uint64_t cols;

    scanf("%lux%lu", &rows, &cols);
    printf("%lux%lu\n", rows, cols);

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


void input_matrix(Matrix *matrix) {

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


int main() {

    Matrix matrix = matrix_init();
    input_matrix(&matrix);
    output_matrix(&matrix);

    return 0;
}