#include <stdio.h>
#include <stdint.h>
#include <malloc.h>


typedef struct Matrix {

    int rows;
    int cols;

    double **array;

} Matrix;


Matrix matrix_init(int rows, int cols) {

    struct Matrix matrix;

    matrix.rows = rows;
    matrix.cols  = cols;

    matrix.array = (double**)malloc(matrix.rows * sizeof(double*) + matrix.rows * matrix.cols * sizeof(double));

    double* start = (double*)((char*)matrix.array + matrix.rows * sizeof(double*));

    for(int row = 0; row <= matrix.rows - 1; row++) {
        matrix.array[row] = start + row * matrix.cols;
    }

    return matrix;

}


void matrix_output(Matrix matrix) {

    for(int row = 0; row <= matrix.rows-1; row++) {

        for(int col = 0; col <= matrix.cols-1; col++)
            printf("%14.4lf", matrix.array[row][col]);

        printf("\n");
    }

    printf("\n");

}


void mem_clearing(Matrix *matrix) {

    /*for(int row = 0; row <= matrix.c->rows - 1; row ++)
        free(matrix.c->array[row]);*/

    free(matrix->array);

}


Matrix matrix_addition(Matrix matrix1, Matrix matrix2, int plus_key) {

    Matrix sum_matrix = matrix_init(matrix1.rows, matrix1.rows);

    for(int row = 0; row <= matrix1.rows-1; row++)
        for(int col = 0; col <= matrix1.cols-1; col++)
            sum_matrix.array[row][col] = 1 * matrix1.array[row][col] + plus_key * matrix2.array[row][col];

    return sum_matrix;

}


int is_rows1_equal_rows2(Matrix matrix1, Matrix matrix2) {

    uint64_t delta = matrix1.cols - matrix2.rows;
    return (delta != 0) ? 1 : 0;

}


Matrix matrix_multiplication(Matrix matrix1, Matrix matrix2) {

    Matrix multiplied_matrix = matrix_init(matrix1.rows, matrix2.cols);

    for(int row = 0; row <= multiplied_matrix.rows - 1; row++)

        for(int col = 0; col <= multiplied_matrix.cols - 1; col++) {

            multiplied_matrix.array[row][col] = 0;

            for (int k = 0; k <= matrix1.cols - 1; k++)
                multiplied_matrix.array[row][col] += matrix1.array[row][k] * matrix2.array[k][col];
        }

    return multiplied_matrix;

}


Matrix matrix_number_operation(Matrix matrix, double number, int plus_key) {

    Matrix operated_matrix = matrix_init(matrix.rows, matrix.cols);

    for(int row = 0; row <= matrix.rows - 1; row++)
        for(int col = 0; col <= matrix.cols - 1; col++)
            if(plus_key == 1)
                operated_matrix.array[row][col] = matrix.array[row][col] + number;
            else
                operated_matrix.array[row][col] = matrix.array[row][col] * number;

    return operated_matrix;

}


Matrix minor_init(Matrix matrix, int crossed_row, int crossed_col, int det_key) {

    Matrix minor = matrix_init(matrix.rows-1, matrix.cols-1);

    int row_link = det_key;
    int col_link;

    for(int i = 0; i <= minor.rows - 1; i++) {

        if(crossed_row == i)
            row_link += 1;

        col_link = 0;

        for (int j = 0; j <= minor.cols - 1; j++) {
            if(j == crossed_col)
                col_link += 1;
            minor.array[i][j] = matrix.array[i + row_link][j + col_link];
        }

    }

    return minor;

}


double recursive_determinant(Matrix matrix) {

    double determinant;

    if(matrix.rows == 1) {
        determinant = matrix.array[0][0];
        return determinant;
    }

    for(int col = 0; col <= matrix.cols - 1; col++) {

        Matrix minor = minor_init(matrix, -1, col, 1);

        int k;
        k = (col % 2 != 0) ? -1 : 1;

        determinant += k * matrix.array[0][col] * recursive_determinant(minor);

        mem_clearing(&minor);

    }

    return determinant;

}


int is_square_matrix(Matrix matrix) {

    if(matrix.rows - matrix.cols != 0)
        return -1;

    return 0;

}


Matrix matrix_transposition(Matrix matrix) {

    int rows = matrix.cols;
    int cols = matrix.rows;

    Matrix transposed_matrix = matrix_init(rows, cols);

    for(int row = 0; row <= transposed_matrix.rows - 1; row++)
        for(int col = 0; col <= transposed_matrix.cols - 1; col++)
            transposed_matrix.array[row][col] = matrix.array[col][row];

    return transposed_matrix;

}


Matrix minor_transformation(Matrix matrix) {

    Matrix inverse_added_matrix = matrix_init(matrix.rows, matrix.cols);

    if(matrix.rows == 1) {
        inverse_added_matrix = matrix;
        return inverse_added_matrix;
    }

    for(int row = 0; row <= matrix.rows - 1; row++) {

        for(int col = 0; col <= matrix.cols - 1; col++) {

            Matrix minor = minor_init(matrix,row, col, 0);

            int k = ((row + col) % 2 == 0) ? 1 : -1;

            inverse_added_matrix.array[row][col] = k * recursive_determinant(minor);

            mem_clearing(&minor);

        }

    }

    return inverse_added_matrix;

}


Matrix matrix_inversion(Matrix matrix) {

    double determinant = recursive_determinant(matrix);

    double inverse_coef = 1 / determinant;

    Matrix transposed_matrix = matrix_transposition(matrix);

    Matrix transformed_matrix = minor_transformation(transposed_matrix);

    Matrix inverse_matrix = matrix_number_operation(transformed_matrix, inverse_coef, 0);

    mem_clearing(&transposed_matrix);
    mem_clearing(&transformed_matrix);

    return inverse_matrix;

}


int is_zero_determinant(Matrix matrix) {

    double determinant = recursive_determinant(matrix);

    if((int)((determinant - (int)determinant) * 1000) == 0)
        return -1;
    else
        return 0;

}


Matrix matrix_inverse_multiplication(Matrix *matrix1, Matrix *matrix2) {

    Matrix inverse_matrix = matrix_inversion(*matrix2);

    Matrix inverse_multiplied_matrix = matrix_multiplication(*matrix1, inverse_matrix);
    mem_clearing(&inverse_matrix);

    return inverse_multiplied_matrix;

}


Matrix identity_matrix(int rows) {

    int cols = rows;
    Matrix id_matrix = matrix_init(rows, rows);

    for(int row = 0; row <= rows - 1; row++)
        for(int col = 0; col <= cols - 1; col++)
            id_matrix.array[row][col] = (row == col) ? 1 : 0;

    return id_matrix;

}


Matrix matrix_number_filling(int rows, int cols, double number) {

    Matrix filled_matrix = matrix_init(rows, cols);

    for(int row = 0; row <= rows - 1; row++)
        for(int col = 0; col <= cols - 1; col++)
            filled_matrix.array[row][col] = number;

    return filled_matrix;

}


Matrix matrix_power(Matrix matrix, int pow) {

    Matrix powered_matrix = matrix_init(matrix.rows, matrix.cols);
    for(int row = 0; row <= matrix.rows - 1; row++)
        for(int col = 0; col <= matrix.cols - 1; col++)
            powered_matrix.array[row][col] = matrix.array[row][col];

    Matrix buffer;

    if(pow == 1)
        return powered_matrix;

    for (int k = 1; k < pow; k++) {
        buffer = matrix_multiplication(powered_matrix, matrix);
        mem_clearing(&powered_matrix);
        powered_matrix = buffer;
    }

    return powered_matrix;

}


Matrix matrix_exp(Matrix matrix) {

    Matrix exp_matrix = identity_matrix(matrix.rows);

    Matrix powered_matrix;
    Matrix multiplied_matrix;
    Matrix sum_matrix;

    int factorial = 1;
    int clk = 1;
    double k;

    while(clk < 17) {

        factorial *= clk;
        k = 1.0 / factorial;
        //printf("clk=%d   k = %lf\n", clk, k);

        powered_matrix = matrix_power(matrix, clk);

        multiplied_matrix = matrix_number_operation(powered_matrix, k, 0);
        mem_clearing(&powered_matrix);

        sum_matrix = matrix_addition(exp_matrix, multiplied_matrix, 1);
        mem_clearing(&exp_matrix);
        mem_clearing(&multiplied_matrix);

        exp_matrix = sum_matrix;

        clk += 1;

    }

    return exp_matrix;

}


int test_matrix_filling(Matrix *matrix, const double array[]) {

    int array_index = 0;
    for(int row = 0; row <= matrix->rows-1; row++)
        for(int col = 0; col <= matrix->cols-1; col++) {
            matrix->array[row][col] = array[array_index];
            array_index += 1;
        }

}


void exp_test() {

    Matrix matrix = matrix_init(2,2);
    double array[] = {2,2,2,2};
    test_matrix_filling(&matrix, array);

    Matrix res = matrix_exp(matrix);
    mem_clearing(&matrix);

    matrix_output(res);
    mem_clearing(&res);

}


int test_check_array(const double true_array[], Matrix res_matrix) {

    int len = res_matrix.rows * res_matrix.cols;

    double result_array[len];
    int array_index = 0;

    double delta;
    int error_flag = 0;

    for(int row = 0; row <= res_matrix.rows-1; row++)
        for(int col = 0; col <= res_matrix.cols-1; col++) {
            result_array[array_index] = res_matrix.array[row][col];
            array_index += 1;
        }

    for(array_index = 0; array_index <= len - 1; array_index++) {

        delta = result_array[array_index] - true_array[array_index];

        printf("res: %lf // ", result_array[array_index]);
        printf("true: %lf // ", true_array[array_index]);
        printf("delta: %lf //\n", delta);

        delta = (delta < 0) ? -delta : delta;

        if(delta * 1000 >= 1.0)
            error_flag += 1;

    }

    return error_flag;

}


void test_matrix_operation(double true_array[], Matrix res_matrix, char text[]) {

    int error_flag = test_check_array(true_array, res_matrix);

    mem_clearing(&res_matrix);

    printf("%s. Errors: %d\n", text, error_flag);

}


void test() {

    Matrix matrix1 = matrix_init(2, 2);
    double array1[] = {2, 8, 1, 3};
    test_matrix_filling(&matrix1, array1);

    Matrix matrix2 = matrix_init(2, 2);
    double array2[] = {4, 9, 21, 13};
    test_matrix_filling(&matrix2, array2);

    //  addition test
    double add_true_array[] = {6, 17, 22, 16};
    Matrix sum_matrix  = matrix_addition(matrix1, matrix2, 1);
    test_matrix_operation(add_true_array, sum_matrix, "Addition");

    //  multiplication test
    double multi_true_array[] = {176, 122, 67, 48};
    Matrix multiplied_matrix = matrix_multiplication(matrix1, matrix2);
    test_matrix_operation(multi_true_array, multiplied_matrix, "Multiplication");

    //  number addition test
    double add_number = 2;
    double number_add_true_array[] = {4, 10, 3, 5};
    Matrix number_sum_matrix = matrix_number_operation(matrix1, add_number, 1);
    test_matrix_operation(number_add_true_array, number_sum_matrix, "Number addition");

    //  number multiplication test
    double multi_number = 2;
    double number_multi_true_array[] = {4, 16, 2, 6};
    Matrix number_multi_matrix = matrix_number_operation(matrix1, multi_number, 0);
    test_matrix_operation(number_multi_true_array, number_multi_matrix, "Number multiplication");

    //  determinant test
    double determinant_true_array[] = {-2};
    double determinant = recursive_determinant(matrix1);
    Matrix det_matrix = matrix_init(1, 1);
    det_matrix.array[0][0] = determinant;
    test_matrix_operation(determinant_true_array, det_matrix, "Matrix determinant");

    //  transposition test
    double transposition_true_array[] = {2, 1, 8, 3};
    Matrix transposed_matrix = matrix_transposition(matrix1);
    test_matrix_operation(transposition_true_array, transposed_matrix, "Matrix transposition");

    //  inversion test
    double inversion_true_array[] = {-1.5, 4, 0.5, -1};
    Matrix inverse_matrix = matrix_inversion(matrix1);
    test_matrix_operation(inversion_true_array, inverse_matrix, "Matrix inversion");

    //  inverse multiplication test
    double inverse_multipl_true_array[] = {1.0365, -0.1022, 0.3650, -0.0219};
    Matrix inverse_multipl_matrix = matrix_inverse_multiplication(&matrix1, &matrix2);
    test_matrix_operation(inverse_multipl_true_array, inverse_multipl_matrix,
                          "Matrix inverse multiplication");

    //  exp test
    Matrix matrix3 = matrix_init(2, 2);
    double array3[] = {2, 2, 2, 2};
    test_matrix_filling(&matrix3, array3);
    double exp_true_array[] = {29.2533, 28.2533, 28.2533, 29.2533};
    Matrix exp_matrix = matrix_exp(matrix3);
    test_matrix_operation(exp_true_array, exp_matrix, "Matrix exp");

    mem_clearing(&matrix1);
    mem_clearing(&matrix2);
    mem_clearing(&matrix3);

}


int main() {

    test();

    return 0;

}