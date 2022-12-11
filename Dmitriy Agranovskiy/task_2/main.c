#include <stdio.h>
#include <malloc.h>
#include <math.h>


typedef struct Matrix {
    int rows;
    int cols;
    int size;
    double **values;
    double *start;

} Matrix;


Matrix matrix_init(int rows, int cols) {
    struct Matrix matrix;
    matrix.rows = rows;
    matrix.cols  = cols;
    matrix.size = matrix.rows * matrix.cols;
    matrix.values = (double**)malloc(matrix.rows * sizeof(double*) + matrix.rows * matrix.cols * sizeof(double));
    matrix.start = (double*)((char*)matrix.values + matrix.rows * sizeof(double*));
    for(int row = 0; row < matrix.rows; row++) {
        matrix.values[row] = matrix.start + row * matrix.cols;
    }
    return matrix;
}


void matrix_output(Matrix matrix) {
    for(int row = 0; row < matrix.rows; row++) {
        for(int col = 0; col < matrix.cols; col++)
            printf("%14.4lf", matrix.values[row][col]);
        printf("\n");
    }
    printf("\n");
}


void free_memory(Matrix *matrix) {
    free(matrix->values);
    matrix->size = 0;
    matrix->rows = 0;
    matrix->cols = 0;
}


Matrix error() {
    Matrix error_matrix = matrix_init(0, 0);
    return error_matrix;
}


Matrix matrix_copy(Matrix matrix) {
    Matrix copied_matrix = matrix_init(matrix.rows, matrix.cols);
    for(int cell = 0; cell < matrix.size; cell++)
        copied_matrix.start[cell] = matrix.start[cell];
    return copied_matrix;
}


Matrix identity_matrix(int rows) {
    int cols = rows;
    Matrix id_matrix = matrix_init(rows, rows);
    for(int row = 0; row < rows; row++)
        for(int col = 0; col < cols; col++)
            id_matrix.values[row][col] = (row == col) ? 1 : 0;
    return id_matrix;
}


Matrix matrix_number_filling(int rows, int cols, double number) {
    Matrix filled_matrix = matrix_init(rows, cols);
    for(int cell = 0; cell < rows; cell++)
            filled_matrix.start[cell] = number;
    return filled_matrix;
}


Matrix matrix_addition(Matrix matrix1, Matrix matrix2) {
    if(matrix1.rows != matrix2.rows || matrix1.cols != matrix2.cols) {
        return error();
    }
    Matrix sum_matrix = matrix_init(matrix1.rows, matrix1.rows);
    for(int cell = 0; cell < matrix1.size; cell++)
            sum_matrix.start[cell] = 1 * matrix1.start[cell] + matrix2.start[cell];
    return sum_matrix;
}


Matrix matrix_subtraction(Matrix matrix1, Matrix matrix2) {
    if(matrix1.rows != matrix2.rows || matrix1.cols != matrix2.cols) {
        return error();
    }
    Matrix sum_matrix = matrix_init(matrix1.rows, matrix1.rows);
    for(int cell = 0; cell < matrix1.size; cell++)
        sum_matrix.start[cell] = 1 * matrix1.start[cell] - matrix2.start[cell];
    return sum_matrix;
}


Matrix matrix_multiplication(Matrix matrix1, Matrix matrix2) {
    if(matrix1.cols != matrix2.rows) {
        return error();
    }
    Matrix multiplied_matrix = matrix_init(matrix1.rows, matrix2.cols);
    for(int row = 0; row < multiplied_matrix.rows; row++)
        for(int col = 0; col < multiplied_matrix.cols; col++) {
            multiplied_matrix.values[row][col] = 0;
            for (int k = 0; k < matrix1.cols; k++)
                multiplied_matrix.values[row][col] += matrix1.values[row][k] * matrix2.values[k][col];
        }
    return multiplied_matrix;
}


Matrix matrix_number_addition(Matrix matrix, double number) {
    Matrix operated_matrix = matrix_init(matrix.rows, matrix.cols);
    for(int cell = 0; cell < matrix.size; cell++)
                operated_matrix.start[cell] = matrix.start[cell] + number;
    return operated_matrix;
}


Matrix matrix_number_multiplication(Matrix matrix, double number) {
    Matrix operated_matrix = matrix_init(matrix.rows, matrix.cols);
    for(int cell = 0; cell < matrix.size; cell++)
        operated_matrix.start[cell] = matrix.start[cell] * number;
    return operated_matrix;
}


Matrix minor_init(Matrix matrix, int crossed_row, int crossed_col) {
    Matrix minor = matrix_init(matrix.rows-1, matrix.cols-1);
    int row_link = 0;
    for(int i = 0; i < minor.rows; i++) {
        if(crossed_row == i)
            row_link += 1;
        int col_link = 0;
        for (int j = 0; j < minor.cols; j++) {
            if(j == crossed_col)
                col_link += 1;
            minor.values[i][j] = matrix.values[i + row_link][j + col_link];
        }
    }
    return minor;
}


double recursive_determinant(Matrix matrix) {
    if(matrix.rows != matrix.cols) {
        return NAN;
    }
    double determinant = 0;
    if(matrix.rows == 1) {
        determinant = matrix.values[0][0];
        return determinant;
    }
    int k = 1;
    for(int col = 0; col < matrix.cols; col++) {
        Matrix minor = minor_init(matrix, 0, col);
        determinant += k * matrix.values[0][col] * recursive_determinant(minor);
        k = -k;
        free_memory(&minor);
    }
    return determinant;
}


Matrix matrix_transposition(Matrix matrix) {
    int rows = matrix.cols;
    int cols = matrix.rows;
    Matrix transposed_matrix = matrix_init(rows, cols);
    for(int row = 0; row < transposed_matrix.rows; row++)
        for(int col = 0; col < transposed_matrix.cols; col++)
            transposed_matrix.values[row][col] = matrix.values[col][row];
    return transposed_matrix;
}


Matrix minor_transformation(Matrix matrix) {
    if(matrix.rows != matrix.cols) {
        return error();
    }
    Matrix inverse_added_matrix = matrix_init(matrix.rows, matrix.cols);
    if(matrix.rows == 1) {
        inverse_added_matrix = matrix_copy(matrix);
        return inverse_added_matrix;
    }
    for(int row = 0; row < matrix.rows; row++) {
        for(int col = 0; col < matrix.cols; col++) {
            Matrix minor = minor_init(matrix,row, col);
            int k = ((row + col) % 2 == 0) ? 1 : -1;
            inverse_added_matrix.values[row][col] = k * recursive_determinant(minor);
            free_memory(&minor);
        }
    }
    return inverse_added_matrix;
}


Matrix matrix_inversion(Matrix matrix) {
    if(matrix.rows != matrix.cols) {
        return error();
    }
    double determinant = recursive_determinant(matrix);
    if(fabs(determinant) < 0.0001 || determinant == NAN) {
        return error();
    }
    double inv_det = 1 / determinant;
    Matrix transposed_matrix = matrix_transposition(matrix);
    Matrix transformed_matrix = minor_transformation(transposed_matrix);
    Matrix inverse_matrix = matrix_number_multiplication(transformed_matrix, inv_det);
    free_memory(&transposed_matrix);
    free_memory(&transformed_matrix);
    return inverse_matrix;
}


Matrix matrix_inverse_multiplication(Matrix matrix1, Matrix matrix2) {
    Matrix inverse_matrix = matrix_inversion(matrix2);
    Matrix inverse_multiplied_matrix = matrix_multiplication(matrix1, inverse_matrix);
    free_memory(&inverse_matrix);
    return inverse_multiplied_matrix;
}


Matrix matrix_power(Matrix matrix, int power) {
    Matrix powered_matrix = matrix_copy(matrix);
    Matrix buffer;
    if(power == 1)
        return powered_matrix;
    for (int k = 1; k < power; k++) {
        buffer = matrix_multiplication(powered_matrix, matrix);
        free_memory(&powered_matrix);
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
    double k;
    for(int s = 1; s < 17; s++) {
        factorial *= s;
        k = 1.0 / factorial;
        powered_matrix = matrix_power(matrix, s);
        multiplied_matrix = matrix_number_multiplication(powered_matrix, k);
        free_memory(&powered_matrix);
        sum_matrix = matrix_addition(exp_matrix, multiplied_matrix);
        free_memory(&exp_matrix);
        free_memory(&multiplied_matrix);
        exp_matrix = sum_matrix;
    }
    return exp_matrix;
}


void test_matrix_filling(Matrix *matrix, const double array[]) {
    // получает на вход матрицу и массив, заполняет матрицу элементами массива
    int array_index = 0;
    for(int row = 0; row < matrix->rows; row++)
        for(int col = 0; col < matrix->cols; col++) {
            matrix->values[row][col] = array[array_index];
            array_index += 1;
        }
}


int test_check_array(const double true_array[], Matrix res_matrix) {
    /*Получает на вход массив достоверных результатов и результирующую матрицу. Создает массив значений ячеек матрицы.
    Поэлементно находит разность значений массива достоверных значений и массива матричных значений.
     Возвращает количество ошибок.*/
    int len = res_matrix.rows * res_matrix.cols;
    double result_array[len];
    int array_index = 0;
    for(int row = 0; row < res_matrix.rows; row++)
        for(int col = 0; col < res_matrix.cols; col++) {
            result_array[array_index] = res_matrix.values[row][col];
            array_index += 1;
        }
    double delta;
    int error_flag = 0;
    for(array_index = 0; array_index < len; array_index++) {
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
    free_memory(&res_matrix);
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
    Matrix sum_matrix  = matrix_addition(matrix1, matrix2);
    test_matrix_operation(add_true_array, sum_matrix, "Addition");

    //  subtraction test
    double sub_true_array[] = {-2, -1, -20, -10};
    Matrix sub_matrix  = matrix_subtraction(matrix1, matrix2);
    test_matrix_operation(sub_true_array, sub_matrix, "Subtraction");

    //  multiplication test
    double multi_true_array[] = {176, 122, 67, 48};
    Matrix multiplied_matrix = matrix_multiplication(matrix1, matrix2);
    test_matrix_operation(multi_true_array, multiplied_matrix, "Multiplication");

    //  number addition test
    double add_number = 2;
    double number_add_true_array[] = {4, 10, 3, 5};
    Matrix number_sum_matrix = matrix_number_addition(matrix1, add_number);
    test_matrix_operation(number_add_true_array, number_sum_matrix, "Number addition");

    //  number multiplication test
    double multi_number = 2;
    double number_multi_true_array[] = {4, 16, 2, 6};
    Matrix number_multi_matrix = matrix_number_multiplication(matrix1, multi_number);
    test_matrix_operation(number_multi_true_array, number_multi_matrix, "Number multiplication");

    //  determinant test
    double determinant_true_array[] = {-2};
    double determinant = recursive_determinant(matrix1);
    Matrix det_matrix = matrix_init(1, 1);
    det_matrix.values[0][0] = determinant;
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
    Matrix inverse_multipl_matrix = matrix_inverse_multiplication(matrix1, matrix2);
    test_matrix_operation(inverse_multipl_true_array, inverse_multipl_matrix,
                          "Matrix inverse multiplication");

    //  exp test
    Matrix matrix3 = matrix_init(2, 2);
    double array3[] = {2, 2, 2, 2};
    test_matrix_filling(&matrix3, array3);
    double exp_true_array[] = {29.2533, 28.2533, 28.2533, 29.2533};
    Matrix exp_matrix = matrix_exp(matrix3);
    test_matrix_operation(exp_true_array, exp_matrix, "Matrix exp");

    free_memory(&matrix1);
    free_memory(&matrix2);
    free_memory(&matrix3);
}


int main() {
    test();
    return 0;
}
