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

    matrix.array = (double**)malloc(matrix.rows * sizeof(double*) + matrix.rows * matrix.cols * sizeof(double));

    double* start = (double*)((char*)matrix.array + matrix.rows * sizeof(double*));

    for(int row = 0; row <= matrix.rows - 1; row++) {
        matrix.array[row] = start + row * matrix.cols;
    }

    /*matrix.array = (double**)malloc(rows * sizeof(double*));

    for(int row = 0; row <= rows - 1; row++) {
     matrix.array[row] = (double*)malloc(cols * sizeof(double));
    }*/

    return matrix;

}


void matrix_output(Matrix *matrix, int filling_key) {

    if(filling_key == 0)
        printf("You get: \n");
    else
        printf("You entered:\n");

    for(int row = 0; row <= matrix->rows-1; row++) {

        for(int col = 0; col <= matrix->cols-1; col++)
            printf("%10.2lf", matrix->array[row][col]);

        printf("\n");
    }

}


void matrix_filling(Matrix *matrix) {

    printf("fill matrix:\n");

    for(int row = 0; row <= matrix->rows-1; row++)
        for(int col = 0; col <= matrix->cols-1; col++)
            scanf("%lf", &matrix->array[row][col]);

    matrix_output(matrix, 1);

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

    /*for(int row = 0; row <= matrix->rows - 1; row ++)
        free(matrix->array[row]);*/

    free(matrix->array);

}


int matrix_addition(int key) {

    Matrix matrix1 = new_matrix();

    Matrix matrix2 = matrix_init(matrix1.rows, matrix1.cols);

    if(matrix_size_comparer(0, &matrix1, &matrix2) == -1) {
        printf("Sizes of matrices are not equals\n");
        return -1;
    }

    matrix_filling(&matrix1);
    matrix_filling(&matrix2);

    Matrix sum_matrix = matrix_init(matrix1.rows, matrix1.rows);

    for(int row = 0; row <= matrix1.rows-1; row++)
        for(int col = 0; col <= matrix1.cols-1; col++)
            sum_matrix.array[row][col] = 1 * matrix1.array[row][col] + key * matrix2.array[row][col];

    matrix_output(&sum_matrix, 0);

    mem_clearing(&matrix1);
    mem_clearing(&matrix2);
    mem_clearing(&sum_matrix);

}


Matrix matrix_multiplication(Matrix *matrix1, Matrix *matrix2) {

    Matrix multiplied_matrix = matrix_init(matrix1->rows, matrix2->cols);

    int key = (int)matrix1->cols;

    for(int row = 0; row <= multiplied_matrix.rows - 1; row++)

        for(int col = 0; col <= multiplied_matrix.cols - 1; col++) {

            multiplied_matrix.array[row][col] = 0;

            for (int k = 0; k <= key - 1; k++)
                multiplied_matrix.array[row][col] += matrix1->array[row][k] * matrix2->array[k][col];
        }

    return multiplied_matrix;

}


void multiplication_output() {

    Matrix matrix1 = new_matrix();

    Matrix matrix2 = new_matrix();

    if(matrix_size_comparer(1, &matrix1, &matrix2) == -1) {
        printf("Sizes of matrices are not equals");
        return;
    }

    matrix_filling(&matrix1);
    matrix_filling(&matrix2);

    Matrix multiplied_matrix = matrix_multiplication(&matrix1, &matrix2);

    matrix_output(&multiplied_matrix, 0);

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
    matrix_filling(&matrix);

    double number;

    printf("Enter a number:\n");
    scanf("%lf", &number);

    Matrix operated_matrix = matrix_number_operation(&matrix, number, key);

    matrix_output(&operated_matrix, 0);

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

    matrix_filling(&matrix);

    double determinant = recursive_determinant_evaluation(&matrix);

    printf("You get: ");
    printf("determinant = %.3lf\n", determinant);

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
    matrix_filling(&matrix);

    Matrix transposed_matrix = matrix_transposition(&matrix);

    matrix_output(&transposed_matrix, 0);

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

    mem_clearing(&transposed_matrix);
    mem_clearing(&transformed_matrix);

    return inverse_matrix;

}


int zero_determinant(Matrix *matrix) {

    double determinant = recursive_determinant_evaluation(matrix);

    if((int)((determinant - (int)determinant) * 1000) == 0)
        return -1;
    else
        return 0;
}


void inverse_matrix_output() {

    Matrix matrix = new_matrix();

    if(matrix_square_checker(&matrix) == -1) {
        printf("You need to input square matrix\n");
        return;
    }

    matrix_filling(&matrix);

    if(zero_determinant(&matrix) == -1) {
        printf("Error: determinant = 0\n");
        return;
    }

    Matrix inverse_matrix = matrix_inversion(&matrix);

    matrix_output(&inverse_matrix, 0);

    mem_clearing(&matrix);
    mem_clearing(&inverse_matrix);

}


Matrix matrix_inverse_multiplication(Matrix *matrix1, Matrix *matrix2) {

    Matrix inverse_matrix = matrix_inversion(matrix2);printf("ok\n");
    matrix_output(&inverse_matrix, 0);printf("ok\n");

    Matrix inverse_multiplied_matrix = matrix_multiplication(matrix1, &inverse_matrix);printf("ok");
    mem_clearing(&inverse_matrix);printf("ok");

    return inverse_multiplied_matrix;

}


void inverse_multiplication_output() {

    Matrix matrix1 = new_matrix();

    Matrix matrix2 = new_matrix();

    if(matrix_square_checker(&matrix2) == -1) {
        printf("You need to input square matrix\n");
        return;
    }

    matrix_filling(&matrix1);
    matrix_filling(&matrix2);

    double determinant = recursive_determinant_evaluation(&matrix2);
    if((int)((determinant - (int)determinant) * 1000) == 0) {
        printf("Error: determinant2 = 0\n");
        return;
    }

    Matrix inverse_multiplied_matrix = matrix_inverse_multiplication(&matrix1, &matrix2);

    matrix_output(&inverse_multiplied_matrix, 0);

    mem_clearing(&matrix1);
    mem_clearing(&matrix2);
    mem_clearing(&inverse_multiplied_matrix);

}


void start_menu() {

    printf("Choose operation\n");
    printf("1: matrix addition; 2: matrix subtraction; 3: number addition; 4: number multiplication;\n");
    printf("5: matrix multiplication; 6: matrix determinant; 7: matrix transposition; 8: matrix inversion;\n");
    printf("9: matrix inverse multiplication;\n");

    int operation_key;
    scanf("%d", &operation_key);
    switch(operation_key)
    {
        case 1:
            matrix_addition(1); break;
        case 2:
            matrix_addition(-1); break;
        case 3:
            number_operation_output(0); break;
        case 4:
            number_operation_output(1); break;
        case 5:
            multiplication_output(); break;
        case 6:
            matrix_determinant_output(); break;
        case 7:
            transposition_output(); break;
        case 8:
            inverse_matrix_output(); break;
        case 9:
            inverse_multiplication_output(); break;
    }

}


int main() {

    start_menu();

    return 0;
}