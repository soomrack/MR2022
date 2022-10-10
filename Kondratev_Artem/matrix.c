#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
//#include <iso646.h>


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

    /*matrix.c.array = (double**)malloc(rows * sizeof(double*));

    for(int row = 0; row <= rows - 1; row++) {
     matrix.c.array[row] = (double*)malloc(cols * sizeof(double));
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
            printf("%14.4lf", matrix->array[row][col]);

        printf("\n");
    }

}


void matrix_filling(Matrix *matrix) {

    printf("fill matrix.c:\n");

    for(int row = 0; row <= matrix->rows-1; row++)
        for(int col = 0; col <= matrix->cols-1; col++)
            scanf("%lf", &matrix->array[row][col]);

    matrix_output(matrix, 1);

}


Matrix new_matrix() {

    int  rows, cols;

    printf("input new matrix.c sizes:\n");
    scanf("%dx%d", &rows, &cols);
    printf("sizes: %dx%d\n", rows, cols);

    Matrix matrix = matrix_init(rows, cols);

    return matrix;

}


void mem_clearing(Matrix *matrix) {

    /*for(int row = 0; row <= matrix.c->rows - 1; row ++)
        free(matrix.c->array[row]);*/

    free(matrix->array);

}


Matrix matrix_addition(int sign, Matrix *matrix1, Matrix *matrix2) {

    Matrix sum_matrix = matrix_init(matrix1->rows, matrix1->rows);

    for(int row = 0; row <= matrix1->rows-1; row++)
        for(int col = 0; col <= matrix1->cols-1; col++)
            sum_matrix.array[row][col] = 1 * matrix1->array[row][col] + sign * matrix2->array[row][col];

    return sum_matrix;

}


void matrix_addition_output(int sign) {

    Matrix matrix1 = new_matrix();
    Matrix matrix2 = matrix_init(matrix1.rows, matrix1.cols);

    matrix_filling(&matrix1);
    matrix_filling(&matrix2);

    Matrix sum_matrix = matrix_addition(sign, &matrix1, &matrix2);

    matrix_output(&sum_matrix, 0);

    mem_clearing(&matrix1);
    mem_clearing(&matrix2);
    mem_clearing(&sum_matrix);

}


int matrix_size_comparer(Matrix *matrix1, Matrix *matrix2) {

        uint64_t delta = matrix1->cols - matrix2->rows;
        return (delta != 0) ? -1 : 0;

}


Matrix matrix_multiplication(Matrix *matrix1, Matrix *matrix2) {

    Matrix multiplied_matrix = matrix_init(matrix1->rows, matrix2->cols);

    for(int row = 0; row <= multiplied_matrix.rows - 1; row++)

        for(int col = 0; col <= multiplied_matrix.cols - 1; col++) {

            multiplied_matrix.array[row][col] = 0;

            for (int k = 0; k <= matrix1->cols - 1; k++)
                multiplied_matrix.array[row][col] += matrix1->array[row][k] * matrix2->array[k][col];
        }

    return multiplied_matrix;

}


void multiplication_output() {

    Matrix matrix1 = new_matrix();

    Matrix matrix2 = new_matrix();

    if(matrix_size_comparer(&matrix1, &matrix2) == -1) {
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


Matrix matrix_number_operation(Matrix *matrix, double number, int plus_key) {

    Matrix operated_matrix = matrix_init(matrix->rows, matrix->cols);

    for(int row = 0; row <= matrix->rows - 1; row++)
        for(int col = 0; col <= matrix->cols - 1; col++)
            if(plus_key == 1)
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


int matrix_square_checker(Matrix *matrix) {

    if(matrix->rows - matrix->cols != 0)
        return -1;

    return 0;

}


void matrix_determinant_output() {

    Matrix matrix = new_matrix();

    if(matrix_square_checker(&matrix) == -1) {
        printf("You need to input square matrix.c\n");
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

    Matrix inverse_matrix = matrix_number_operation(&transformed_matrix, inverse_coef, 0);

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
        printf("You need to input square matrix.c\n");
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
        printf("You need to input square matrix2\n");
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


int test_filling(Matrix *matrix, const double array[]) {

    int array_index = 0;
    for(int row = 0; row <= matrix->rows-1; row++)
        for(int col = 0; col <= matrix->cols-1; col++) {
            matrix->array[row][col] = array[array_index];
            array_index += 1;
        }

}


/*int test_check_array(const double true_array[], int len, Matrix *res_matrix) {

    double res_array[len];
    int array_index = 0;

    double delta;
    int error_flag = 0;

    for(int row = 0; row <= res_matrix->rows-1; row++)
        for(int col = 0; col <= res_matrix->cols-1; col++) {
            res_array[array_index] = res_matrix->array[row][col];
            array_index += 1;
        }

    for(array_index = 0; array_index <= len - 1; array_index++) {

        if(res_array[array_index] > true_array[array_index]) {
            delta = res_array[array_index] - true_array[array_index];
            printf("res bigger ");
        }
        else {
            delta = true_array[array_index] - res_array[array_index];
            printf("true bigger ");
        }
        printf("res: %lf // ", res_array[array_index]);
        printf("true: %lf // ", true_array[array_index]);
        printf("delta: %lf // ", delta);

        delta = (delta < 0) ? -delta : delta;
        printf("delta2: %lf // ", delta);
        printf("delta3: %lf // ", delta * 10000);
        if(delta * 10000 >= 10) {
            error_flag += 1;
            printf("error_flag: +1 //");
            printf("yes\n");
        }
        else
            printf("error_flag: +0 //\n");

    }

    return error_flag;

}


int test_matrix_addition(Matrix matrix1, Matrix matrix2, const double sum_true_array[]) {

    Matrix sum_matrix  = matrix_addition(1, &matrix1, &matrix2);

    int sum_len = matrix1.rows * matrix1.cols;

    int error_flag = test_check_array(sum_true_array, sum_len, &sum_matrix);

    return error_flag;

}


int test_matrix_multiplication(Matrix matrix1, Matrix matrix2, const double multi_true_array[]) {

    Matrix multiplied_matrix = matrix_multiplication(&matrix1, &matrix2);

    int multi_len = matrix1.rows * matrix1.cols;

    int error_flag = test_check_array(multi_true_array, multi_len, &multiplied_matrix);

    return error_flag;

}*/


void test() {

    Matrix matrix1 = matrix_init(2, 2);
    double array1[] = {3.1, 8, 1, 2.659};
    test_filling(&matrix1, array1);


    Matrix matrix2 = matrix_init(2, 2);
    double array2[] = {13.314, 9, 21, 46.928};
    test_filling(&matrix2, array2);


    /*int error_flag;

    double sum_true_array[] = {16.415, 16.999, 22, 49.587};
    error_flag = test_matrix_addition(matrix1, matrix2, sum_true_array);
    printf("Addition. Errors: %d\n", error_flag);

    double multi_true_array[] = {209.273, 403.324, 69.153, 133.782};
    error_flag = test_matrix_multiplication(matrix1, matrix2, multi_true_array);
    printf("Multiplication. Errors: %d\n", error_flag);*/

    Matrix result = matrix_addition(1, &matrix1, &matrix2);
    matrix_output(&result, 0);
}


void start_menu() {

    printf("Choose operation\n");
    printf("1: matrix.c addition; 2: matrix.c subtraction; 3: number addition; 4: number multiplication;\n");
    printf("5: matrix.c multiplication; 6: matrix.c determinant; 7: matrix.c transposition; 8: matrix.c inversion;\n");
    printf("9: matrix.c inverse multiplication;\n");

    int operation_key;
    scanf("%d", &operation_key);
    switch(operation_key)
    {
        case 0:
            test(); break;
        case 1:
            matrix_addition_output(1); break;
        case 2:
            matrix_addition_output(-1); break;
        case 3:
            number_operation_output(1); break;
        case 4:
            number_operation_output(0); break;
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
    //test();

    return 0;
}