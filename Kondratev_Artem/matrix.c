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


void output_matrix(Matrix *matrix, int key) {

    if(key != 0)
        printf("You get: \n");
    else
        printf("You entered:\n");

    for(int row = 0; row <= matrix->rows-1; row++) {

        for(int col = 0; col <= matrix->cols-1; col++)
            printf("%6.2lf", matrix->array[row][col]);

        printf("\n");
    }

}


void filling_matrix(Matrix *matrix) {

    printf("fill matrix:\n");

    for(int row = 0; row <= matrix->rows-1; row++)
        for(int col = 0; col <= matrix->cols-1; col++)
            scanf("%lf", &matrix->array[row][col]);

    output_matrix(matrix, 0);

}


Matrix new_matrix() {

    uint64_t  rows, cols;

    printf("input new matrix sizes:\n");
    scanf("%lux%lu", &rows, &cols);
    printf("sizes: %lux%lu\n", rows, cols);

    Matrix matrix = matrix_init(rows, cols);

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

        return (delta != 0) ? -1 : 0;

    }

}


void mem_clearing(Matrix *matrix) {

    for(int row = 0; row <= matrix->rows - 1; row ++)
        free(matrix->array[row]);

    free(matrix->array);

}


int matrix_addition() {

    Matrix matrix1 = new_matrix();

    Matrix matrix2 = new_matrix();

    if(matrix_size_comparer(0, &matrix1, &matrix2) == -1) {
        printf("Sizes of matrices are not equals");
        return -1;
    }

    filling_matrix(&matrix1);
    filling_matrix(&matrix2);

    Matrix sum_matrix = matrix_init(matrix1.rows, matrix1.rows);

    for(int row = 0; row <= matrix1.rows-1; row++)
        for(int col = 0; col <= matrix1.cols-1; col++)
            sum_matrix.array[row][col] = matrix1.array[row][col] + matrix2.array[row][col];

    output_matrix(&sum_matrix, 1);

    mem_clearing(&matrix1);
    mem_clearing(&matrix2);
    mem_clearing(&sum_matrix);

}


int matrix_subtraction() {

    Matrix matrix1 = new_matrix();

    Matrix matrix2 = new_matrix();


    if(matrix_size_comparer(0, &matrix1, &matrix2) == -1) {
        printf("Sizes of matrices are not equals");
        return -1;
    }

    filling_matrix(&matrix1);
    filling_matrix(&matrix2);

    Matrix sum_matrix = matrix_init(matrix1.rows, matrix1.rows);

    for(int row = 0; row <= matrix1.rows-1; row++)
        for(int col = 0; col <= matrix1.cols-1; col++)
            sum_matrix.array[row][col] = matrix1.array[row][col] - matrix2.array[row][col];

    output_matrix(&sum_matrix, 1);

    mem_clearing(&matrix1);
    mem_clearing(&matrix2);
    mem_clearing(&sum_matrix);

}


int matrix_multiplication() {

    Matrix matrix1 = new_matrix();

    Matrix matrix2 = new_matrix();

    if(matrix_size_comparer(1, &matrix1, &matrix2) == -1) {
        printf("Sizes of matrices are not equals");
        return -1;
    }

    filling_matrix(&matrix1);
    filling_matrix(&matrix2);

    Matrix multiplied_matrix = matrix_init(matrix1.rows, matrix2.cols);

    int key = (int)matrix1.cols;

    for(int row = 0; row <= multiplied_matrix.rows - 1; row++)

        for(int col = 0; col <= multiplied_matrix.cols - 1; col++) {

            multiplied_matrix.array[row][col] = 0;

            for (int k = 0; k <= key - 1; k++)
                multiplied_matrix.array[row][col] += matrix1.array[row][k] * matrix2.array[k][col];
        }

    output_matrix(&multiplied_matrix, 1);

    mem_clearing(&matrix1);
    mem_clearing(&matrix2);
    mem_clearing(&multiplied_matrix);

}


Matrix matrix_number_operation(Matrix *matrix, double number, int key) {

    Matrix operated_matrix = matrix_init(matrix->rows, matrix->cols);

    for(int row = 0; row <= matrix->rows - 1; row++)
        for(int col = 0; col <= matrix->cols - 1; col++)
            if(key == 0)
                operated_matrix.array[row][col] = matrix->array[row][col] + number;
            else
                operated_matrix.array[row][col] = matrix->array[row][col] * number;

    return operated_matrix;

}


void number_operation_output(int key) {

    Matrix matrix = new_matrix();
    filling_matrix(&matrix);

    double number;

    printf("Enter a number:\n");
    scanf("%lf", &number);

    Matrix operated_matrix = matrix_number_operation(&matrix, number, key);

    output_matrix(&operated_matrix, 1);

    mem_clearing(&matrix);
    mem_clearing(&operated_matrix);

}


int matrix_square_checker(Matrix *matrix) {

    if(matrix->rows - matrix->cols != 0)
        return -1;
    else
        return 0;

}


Matrix minor_init(Matrix *matrix, int crossed_row, int crossed_col, int det_key) {

    Matrix minor = matrix_init(matrix->rows-1, matrix->cols-1);

    int row_link = det_key;
    int col_link;

    for(int i = 0; i <= minor.rows - 1; i++) {

        if(crossed_row == i)
            row_link += 1;

        col_link = 0;

        for (int j = 0; j <= minor.cols - 1; j++) {
            if(j == crossed_col)
                col_link += 1;
            minor.array[i][j] = matrix->array[i + row_link][j + col_link];
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

        Matrix minor = minor_init(matrix, -1, col, 1);

        int k;
        k = (col % 2 != 0) ? -1 : 1;

        determinant += k * matrix->array[0][col] * recursive_determinant_evaluation(&minor);

        mem_clearing(&minor);

    }

    return determinant;

}


void matrix_determinant_output() {

    Matrix matrix = new_matrix();

    if(matrix_square_checker(&matrix) == -1) {
        printf("You need to input square matrix\n");
        return;
    }

    filling_matrix(&matrix);

    double determinant = recursive_determinant_evaluation(&matrix);

    printf("You get: ");
    printf("determinant = %.3lf", determinant);

    mem_clearing(&matrix);

}


Matrix matrix_transposition(Matrix *matrix) {

    Matrix transposed_matrix = matrix_init(matrix->cols, matrix->rows);

    for(int row = 0; row <= transposed_matrix.rows - 1; row++)
        for(int col = 0; col <= transposed_matrix.cols - 1; col++)
            transposed_matrix.array[row][col] = matrix->array[col][row];

    return transposed_matrix;

}


void transposition_output() {

    Matrix matrix = new_matrix();
    filling_matrix(&matrix);

    Matrix transposed_matrix = matrix_transposition(&matrix);

    output_matrix(&transposed_matrix, 1);

    mem_clearing(&matrix);
    mem_clearing(&transposed_matrix);

}


Matrix each_element_minor_transformation(Matrix *matrix) {

    Matrix inverse_added_matrix = matrix_init(matrix->rows, matrix->cols);

    if(matrix->rows == 1) {
        inverse_added_matrix = *matrix;
        return inverse_added_matrix;
    }

    for(int row = 0; row <= matrix->rows - 1; row++) {

        for(int col = 0; col <= matrix->cols - 1; col++) {

            Matrix minor = minor_init(matrix,row, col, 0);

            int k = ((row + col) % 2 == 0) ? 1 : -1;

            inverse_added_matrix.array[row][col] = k * recursive_determinant_evaluation(&minor);

            mem_clearing(&minor);

        }

    }

    return inverse_added_matrix;

}


Matrix matrix_inversion(Matrix *matrix) {

    double determinant = recursive_determinant_evaluation(matrix);
    double inverse_coef = 1 / determinant;

    Matrix transposed_matrix = matrix_transposition(matrix);

    Matrix transformed_matrix = each_element_minor_transformation(&transposed_matrix);

    Matrix inverse_matrix = matrix_number_operation(&transformed_matrix, inverse_coef, 1);

    mem_clearing(matrix);
    mem_clearing(&transposed_matrix);
    mem_clearing(&transformed_matrix);

    return inverse_matrix;

}


void inverse_matrix_output() {

    Matrix matrix = new_matrix();

    if(matrix_square_checker(&matrix) == -1) {
        printf("You need to input square matrix\n");
        return;
    }

    filling_matrix(&matrix);

    Matrix inverse_matrix = matrix_inversion(&matrix);

    output_matrix(&inverse_matrix, 1);

    mem_clearing(&matrix);
    mem_clearing(&inverse_matrix);

}


void start_menu() {

    printf("Choose operation\n");
    printf("1: matrix addition; 2: matrix subtraction; 3: number addition; 4: matrix multiplication\n");
    printf("5: matrix determinant; 6: matrix transposition; 7: invert matrix\n");

    int operation_key;
    scanf("%d", &operation_key);
    switch(operation_key)
    {
        case 1:
            matrix_addition(); break;
        case 2:
            matrix_subtraction(); break;
        case 3:
            number_operation_output(0); break;
        case 4:
            matrix_multiplication(); break;
        case 5:
            matrix_determinant_output(); break;
        case 6:
            transposition_output(); break;
        case 7:
            inverse_matrix_output(); break;
    }

}


int main() {

    start_menu();

    return 0;
}