#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <iso646.h>


typedef struct Matrix {

    uint64_t rows;
    uint64_t cols;

    double **array;

} Matrix;


Matrix matrix_init(uint64_t rows, uint64_t cols) {

    struct Matrix matrix;

    matrix.rows = rows;
    matrix.cols  = cols;

    matrix.array = (double**)malloc(rows * sizeof(double*));

    for(int row = 0; row <= rows - 1; row++) {
        matrix.array[row] = (double*)malloc(cols * sizeof(double));
    }

    return matrix;

}


void filling_matrix(Matrix *matrix) {

    printf("fill matrix:\n");

    for(int row = 0; row <= matrix->rows-1; row++)
        for(int col = 0; col <= matrix->cols-1; col++)
            scanf("%lf", &matrix->array[row][col]);

}


void output_matrix(Matrix *matrix) {

    for(int row = 0; row <= matrix->rows-1; row++) {

        for(int col = 0; col <= matrix->cols-1; col++)
            printf("%6.2lf", matrix->array[row][col]);

        printf("\n");
    }

}


Matrix new_matrix() {

    uint64_t  rows, cols;

    printf("input new matrix sizes:\n");
    scanf("%lux%lu", &rows, &cols);
    printf("sizes: %lux%lu\n", rows, cols);

    Matrix matrix = matrix_init(rows, cols);

    filling_matrix(&matrix);

    printf("You entered:\n");
    output_matrix(&matrix);

    return matrix;

}


int matrix_size_comparer(int key, Matrix *matrix1, Matrix *matrix2) {

    if(key == 0){

        uint64_t delta_rows = matrix1->rows - matrix2->rows;
        uint64_t delta_cols = matrix1->cols - matrix2->cols;

        if(delta_rows != 0 or delta_cols != 0)
            return -1;
        else
            return 0;

    }

    if(key == 1) {

        uint64_t delta = matrix1->cols - matrix2->rows;

        if(delta != 0)
            return -1;
        else
            return 0;

    }

}


int matrix_addition() {

    Matrix matrix1 = new_matrix();

    Matrix matrix2 = new_matrix();


    if(matrix_size_comparer(0, &matrix1, &matrix2) == -1) {
        printf("Sizes of matrices are not equals");
        return -1;
    }

    Matrix sum_matrix = matrix_init(matrix1.rows, matrix1.rows);

    for(int row = 0; row <= matrix1.rows-1; row++)
        for(int col = 0; col <= matrix1.cols-1; col++)
            sum_matrix.array[row][col] = matrix1.array[row][col] + matrix2.array[row][col];

    printf("You get:\n");
    output_matrix(&sum_matrix);
}


int matrix_subtraction() {

    Matrix matrix1 = new_matrix();

    Matrix matrix2 = new_matrix();


    if(matrix_size_comparer(0, &matrix1, &matrix2) == -1) {
        printf("Sizes of matrices are not equals");
        return -1;
    }

    Matrix sum_matrix = matrix_init(matrix1.rows, matrix1.rows);

    for(int row = 0; row <= matrix1.rows-1; row++)
        for(int col = 0; col <= matrix1.cols-1; col++)
            sum_matrix.array[row][col] = matrix1.array[row][col] - matrix2.array[row][col];

    printf("You get:\n");
    output_matrix(&sum_matrix);
}


int matrix_multiplication() {

    Matrix matrix1 = new_matrix();

    Matrix matrix2 = new_matrix();

    if(matrix_size_comparer(1, &matrix1, &matrix2) == -1) {
        printf("Sizes of matrices are not equals");
        return -1;
    }

    Matrix multiplied_matrix = matrix_init(matrix1.rows, matrix2.cols);

    int key = (int)matrix1.cols;

    for(int row = 0; row <= multiplied_matrix.rows - 1; row++)

        for(int col = 0; col <= multiplied_matrix.cols - 1; col++) {

            multiplied_matrix.array[row][col] = 0;

            for (int k = 0; k <= key - 1; k++)
                multiplied_matrix.array[row][col] += matrix1.array[row][k] * matrix2.array[k][col];
        }

    printf("You get:\n");
    output_matrix(&multiplied_matrix);

}


void number_addition() {

    Matrix matrix = new_matrix();

    double number;

    printf("Enter a number:\n");
    scanf("%lf", &number);

    Matrix sum_matrix = matrix_init(matrix.rows, matrix.cols);

    for(int row = 0; row <= matrix.rows - 1; row++)
        for(int col = 0; col <= matrix.cols - 1; col++)
            sum_matrix.array[row][col] = matrix.array[row][col] + number;

    printf("You get:\n");
    output_matrix(&sum_matrix);

}


int matrix_square_checker(Matrix *matrix) {

    if(matrix->rows - matrix->cols != 0)
        return -1;
    else
        return 0;

}


Matrix minor_function(Matrix *matrix, int crossed_col) {

    Matrix minor = matrix_init(matrix->rows-1, matrix->cols-1);

    int link;

    for(int i = 0; i <= minor.rows - 1; i++) {

        link = 0;

        for (int j = 0; j <= minor.cols - 1; j++) {

            if (j != crossed_col)
                minor.array[i][j] = matrix->array[i + 1][j + link];
            else {
                link += 1;
                minor.array[i][j] = matrix->array[i + 1][j + link];
            }
        }
    }

    return minor;

}


double recursive_determinant_evaluation(Matrix *matrix) {

    double determinant;

    if(matrix->rows == 1) {
        determinant = matrix->array[0][0];
        return determinant;
    }

    for(int col = 0; col <= matrix->cols - 1; col++) {

        Matrix minor = minor_function(matrix, col);

        int k;
        k = (col % 2 != 0) ? -1 : 1;

        determinant += k * matrix->array[0][col] * recursive_determinant_evaluation(&minor);

    }

    return determinant;

}


void matrix_determinant_output(int key) {

    Matrix matrix = new_matrix();

    if(matrix_square_checker(&matrix) == -1)
        return;

    double determinant = recursive_determinant_evaluation(&matrix);

    if(key == 1) {
        printf("You get: ");
        printf("determinant = %.3lf", determinant);
    }

}


void start_menu() {

    printf("Choose operation\n");
    printf("1: matrix addition; 2: matrix subtraction; 3: number addition; 4: matrix multiplication\n");
    printf("5: matrix determinant\n");

    int operation_key;
    scanf("%d", &operation_key);
    switch(operation_key)
    {
        case 1:
            matrix_addition(); break;
        case 2:
            matrix_subtraction(); break;
        case 3:
            number_addition(); break;
        case 4:
            matrix_multiplication(); break;
        case 5:
            matrix_determinant_output(1); break;
    }

}


int main() {

    start_menu();

    return 0;
}