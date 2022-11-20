#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>


typedef struct Matrix {
    unsigned int cols;
    unsigned int rows;
    double* value;
} Matrix;


const Matrix ZERO = {0, 0, NULL};


Matrix initialization (const unsigned int cols, const unsigned int rows) {  // Инициализация матриц
    Matrix matrix;
    matrix.cols = cols;
    matrix.rows = rows;
    unsigned int total_num = matrix.cols * matrix.rows;
    matrix.value = malloc(total_num * sizeof(double ));
    return matrix;
}


void mistake (char* name_of_operation, char* error) {  // Есть ошибка в матрицах или они не удовлетворяют условиям
    printf("%s not possible. %s\n", name_of_operation, error);
}


void set (Matrix* matrix) {  // Рандомный ввод матриц
    for (int number = 0; number < (matrix->cols * matrix->rows); number++) {
        matrix->value[number] = rand()%10;  //
    }
}


/*void set (Matrix* matrix) {
    for (int number = 0; number < (matrix->cols * matrix->rows); number++) {
        scanf("%lf", &matrix->value[number]);
    }
}*/


int is_null (const Matrix matrix) {  // Матрицы нет
    if (matrix.cols == 0 && matrix.rows == 0) {
        return 1;
    }
    return 0;
}


Matrix clean_memory (Matrix matrix) {  // Очистка памяти после выполнения операции
    matrix.cols = 0;
    matrix.rows = 0;
    free (matrix.value);
    return matrix;
}


void matrix_output (const Matrix matrix) {  // Вывод матрицы результатов
    if (is_null(matrix)) {
        printf ("No matrix\n");
        return;
    }
    for (unsigned int row = 0; row < matrix.rows; row++){
        for (unsigned int col = 0; col < matrix.cols; col++){
            printf("%.2f ", matrix.value[row * matrix.cols + col]);
        }
        printf("\n");
    }
    printf("\n");
}


Matrix summation (const Matrix matrix1, const Matrix matrix2) {  // Суммирование матриц
    int col1 = matrix1.cols; int row1 = matrix1.rows;
    int col2 = matrix2.cols; int row2 = matrix2.rows;
    if (col1 != col2 || row1 != row2) {
        mistake("Summation", "Not equal matrix size");
        return ZERO;
    }
    Matrix itog = initialization(matrix1.cols, matrix1.rows);
    unsigned int total_num = itog.cols * itog.rows;
    for (unsigned int number = 0; number < total_num; number++) {
        itog.value[number] = matrix1.value[number] + matrix2.value[number];
    }
    return itog;
}


Matrix subtraction (const Matrix matrix1, const Matrix matrix2) {  // Вычитание
    if (matrix1.cols != matrix2.cols || matrix1.rows != matrix2.rows) {
        mistake("Subtraction", "Not equal matrix size");
        return ZERO;
    }
    Matrix itog = initialization(matrix1.cols, matrix1.rows);
    unsigned int total_num = itog.cols * itog.rows;
    for (unsigned int number = 0; number < total_num; number++) {
        itog.value[number] = matrix1.value[number] - matrix2.value[number];
    }
    return itog;
}


Matrix unit_matrix (const unsigned int cols, const unsigned int rows) {  // Задание единичной матрицы (identity_matrix)
    Matrix itog = initialization(cols, rows);
    for (unsigned int number = 0; number < cols * rows; number ++) {
        itog.value [number] = 0.0;
    }
    for ( unsigned int num = 0; num <= cols*rows; num += cols + 1) {
        itog.value[num] = 1.0;
    }
    return itog;
}


Matrix copy_matrix (const Matrix matrix) {  // Копирование значений одной матрицы в другую
    Matrix itog = initialization(matrix.cols, matrix.rows);
    for (unsigned int number = 0; number < matrix.cols * matrix.rows; number ++) {
        itog.value [number] = matrix.value [number];
    }
    return itog;
}


Matrix mult_m_by_num (const Matrix matrix, double num) {  // Умножение матрицы на число
    Matrix itog = initialization(matrix.cols, matrix.rows);
    unsigned int total_number = matrix.cols * matrix.rows;
    for (unsigned int number = 0; number < total_number; number++) {
        itog.value[number] = matrix.value[number] * num;
    }
    return itog;
}


Matrix multiply_m_by_m (const Matrix matrix1, const Matrix matrix2) {  // Умножение матрицы на матрицу
    if (matrix1.cols != matrix2.rows) {
        mistake("Multiply matrix on matrix", "Matrix 1 cols should be equal");
        printf("to matrix 2 rows\n");
        return ZERO;
    }
    unsigned int itog_cols = matrix2.cols;
    unsigned int itog_rows = matrix1.rows;
    Matrix itog = initialization(itog_cols, itog_rows);
    for (unsigned int row = 0;  row < itog_rows; row++) {
        for (unsigned int col = 0; col < itog_cols; col++) {
            double result = 0.0;
            for (unsigned int k = 0; k < matrix1.cols; k++) {
                result += matrix1.value[row * matrix1.cols + k] *
                        matrix2.value[k * matrix2.cols + col];
            }
            itog.value[row * itog_cols + col] = result;
        }
    }
    return itog;
}


/*double determinant (const Matrix matrix) { // Определитель матрицы
    if (matrix.cols != matrix.rows) {
        mistake("Determinant", "Cols must be equal to rows");
        return 0.0;
    }
    double itog = 0.0;
    if (matrix.cols == 1) {
        itog = matrix.value [0];
    }
    else {
        for (unsigned int row = 0; row < matrix.cols; row++) {
                unsigned int col = 0;
                Matrix subm = initialization(matrix.cols - 1, matrix.cols - 1);
                unsigned int col_of = 0;
                unsigned int row_of = 0;
                for (unsigned int subm_row = 0; subm_row < matrix.cols - 1; subm_row++) {
                    for (unsigned int subm_col = 0; subm_col < matrix.cols - 1; subm_col++) {
                        if (subm_row == row) {
                            row_of = 1;
                        }
                        if (subm_col == col) {
                            col_of = 1;
                        }
                        subm.value [subm_row * (matrix.cols - 1) + subm_col] =
                                matrix.value [(subm_col + row_of) * matrix.cols + (subm_col + col_of)];
                    }
                }
                itog += pow(-1, row + col) * matrix.value[row * matrix.cols + col] * determinant(subm);
                clean_memory(&subm);
        }
    }
    return itog;
}*/


Matrix minor (const unsigned int cols, const unsigned int rows, const struct Matrix matrix) {  // Минор матрицы
    struct Matrix itog = initialization(matrix.cols - 1, matrix.rows - 1);
    unsigned int k=0;
    for (unsigned int number = 0; number < matrix.cols * matrix.rows; number ++) {
        if ((number % matrix.cols != cols) && (number / matrix.cols != rows)) {
            itog.value[k++] = matrix.value[number];
        }
    }
    return itog;
}


double determinant (const struct Matrix matrix) {  // Определитель матрицы
    if (matrix.cols != matrix.rows) {
        mistake("Determinant", "Cols must be equal to rows");
        return 0.0;
    }
    if (matrix.cols == 1) {
        return matrix.value [0];
    }
    double itog = 0.0;
    for (unsigned int number = 0; number < matrix.cols; number ++) {
        struct Matrix min = minor(number, 0, matrix);
        itog += pow((-1), number) * matrix.value [number] * determinant(min);
        clean_memory(min);
    }
    return itog;
}


Matrix transposition (const Matrix matrix) {  // Транспонирование матрицы
    Matrix itog = initialization(matrix.rows, matrix.cols);
    for (unsigned int row = 0; row < itog.rows; row++) {
        for (unsigned int col = 0; col < itog.cols; col++) {
            itog.value[row * itog.cols + col] = matrix.value[col * itog.rows + row];
        }
    }
    return itog;
}


Matrix matrix_power (const struct Matrix matrix, unsigned int num) {  // Возведение матрицы в стерень
    if (matrix.cols != matrix.rows) {
        mistake("Power", "Cols must be equal to rows");
        return ZERO;
    }
    if (num == 0) {
        return unit_matrix(matrix.cols, matrix.rows);
    }
    Matrix itog = copy_matrix(matrix);
    for (unsigned int number = 1; number < num; number ++) {
        Matrix new = multiply_m_by_m(matrix, itog);
        itog = new;
        if (number == num) {
        clean_memory(new); //почистить всегда
      }
    }
    return itog;
}


/*Matrix invert_matrix (const Matrix matrix, unsigned int size) {
    if (matrix.cols != matrix.rows || determinant(matrix) == 0) {
        mistake("Getting the inverse matrix", "Matrix must be square and with not zero determinant\n");
        return ZERO;
    }
    Matrix itog = initialization(matrix.cols, matrix.rows);
    for (int col = 0; col < matrix.cols; col++) {
        for (int row = 0; row < matrix.rows; row++) {
            matrix.value[col*size + row] = (pow(-1, col + row) * determinant(minor(matrix.cols, matrix.rows, matrix)));
        }
        itog = multiply_by_num(transposition(itog), 1.0 / determinant(matrix));
        return itog;
    }
}*/


Matrix inverse_matrix (const struct Matrix matrix) {  // Инвертирование матрицы
    double d = determinant(matrix);
    if (matrix.cols != matrix.rows) {
        mistake("Getting the inverse matrix", "Matrix must be square and with not zero determinant\n");
        return ZERO;
    }

    struct Matrix itog = initialization(matrix.cols, matrix.rows);
    for (unsigned int row = 0; row < matrix.rows; row++) {
        for (unsigned int col = 0; col < matrix.cols; col++) {
            itog.value [row*matrix.cols + col] = (pow(-1, col + row) * determinant(minor(col, row, matrix)));
        }
    }
    itog = mult_m_by_num(transposition(itog), (1/ d));
    return itog;

   /* Matrix transponent = transponation(matrix);
    Matrix itog = multiply_by_num(transponent, 1. / determinant(matrix));
    clean_memory(transponent);
    return itog;*/
}


/*Matrix matrix_exponent (const Matrix matrix) {
    if (matrix.cols != matrix.rows) {
        mistake("Exponent", "Matrix must be square");
        return ZERO;
    }
    unsigned int n = 20;
    Matrix itog;
    Matrix temp;
    temp = identity_matrix(matrix.cols, matrix.rows);
    double r_factorial = 1.0;
    itog = identity_matrix(matrix.cols, matrix.rows);
    for (unsigned int num = 0; num < n; num++) {
        r_factorial /= num;
        temp = multiply_matrix_by_matrix(temp, matrix);
        itog = summation(itog, multiply_by_num(temp, r_factorial));
    }
    clean_memory(temp);
    return itog;
}*/


Matrix matrix_exponent (const Matrix matrix, int accuracy) { // Экспонента матрицы
    if (matrix.cols != matrix.rows) {
        mistake("Exp", "Matrix should be square");
        return ZERO;
    }
    Matrix new_result , new_powered, multiplied;
    Matrix exponent = unit_matrix(matrix.cols, matrix.rows);
    Matrix powered = exponent;
    new_result = unit_matrix(matrix.cols, matrix.rows);
    int factorial = 1;
    for (int acc = 1; acc <= accuracy; ++acc) {
        factorial *= acc;
        new_powered = multiply_m_by_m(powered, matrix);
        powered = copy_matrix(new_powered);
        clean_memory(new_powered);
        multiplied = mult_m_by_num(powered, 1. / factorial);
        new_result = summation(exponent, multiplied);

        clean_memory(multiplied);

        exponent = copy_matrix(new_result);

        clean_memory(new_result);
/*
        clean_memory(powered);
*/
    }
    clean_memory(powered);
    return exponent;
}


int main() {

    Matrix mat1, mat2;

    srand(time(NULL));

    printf("\nFirst martix\n");
    mat1 = initialization(2, 2);
    set(&mat1);
    matrix_output(mat1);

    printf("Second matrix\n");
    mat2 = initialization(2, 2);
    set(&mat2);
    matrix_output(mat2);

    printf("Sum of matrices\n");
    Matrix summa;
    summa = summation(mat1, mat2);
    matrix_output(summa);
    clean_memory(summa);

    printf("Sub of matrices\n");
    Matrix sub;
    sub = subtraction(mat1, mat2);
    matrix_output(sub);
    clean_memory(sub);

    printf("Multiplying the first matrix by a number\n");
    Matrix mult_on_num;
    mult_on_num = mult_m_by_num(mat1, 3);
    matrix_output(mult_on_num);
    clean_memory(mult_on_num);

    printf("Multiplying the second matrix by a number\n");
    mult_on_num = mult_m_by_num(mat2, 5);
    matrix_output(mult_on_num);
    clean_memory(mult_on_num);

    printf("Multiplying the first matrix by a second martix\n");
    Matrix multiply_M_by_M;
    multiply_M_by_M = multiply_m_by_m(mat1, mat2);
    matrix_output(multiply_M_by_M);
    clean_memory(multiply_M_by_M);

    printf("Transponated first matrix\n");
    Matrix trans;
    trans = transposition(mat1);
    matrix_output(trans);
    clean_memory(trans);

    printf("Transponated second matrix\n");
    trans = transposition(mat2);
    matrix_output(trans);
    clean_memory(trans);

    printf("Determinant of the first matrix\n");
    double det;
    det = determinant(mat1);
    printf("%.2f\n", det);


    printf("Determinant of the second matrix\n");
    det = determinant(mat2);
    printf("%.2f\n", det);

    printf("First inverse matrix \n");
    Matrix inv;
    inv = inverse_matrix(mat1);
    matrix_output(inv);
    clean_memory(inv);

    printf("Second inverse matrix \n");
    inv = inverse_matrix(mat2);
    matrix_output(inv);
    clean_memory(inv);

    printf("First matrix power\n");
    Matrix pow;
    pow = matrix_power(mat1, 5);
    matrix_output(pow);
    clean_memory(pow);

    printf("Second matrix power\n");
    pow = matrix_power(mat2, 2);
    matrix_output(pow);
    clean_memory(pow);

    printf("Exponent of the first matrix\n");
    Matrix exp;
    exp = matrix_exponent(mat1, 5);
    matrix_output(exp);
    clean_memory(exp);

    printf("Exponent of the second matrix\n");
    exp = matrix_exponent(mat2, 5);
    matrix_output(exp);
    clean_memory(exp);

    printf("identity\n");
    Matrix one;
    one = unit_matrix(3, 3);
    matrix_output(one);
    clean_memory(one);

   /* printf("Unit matrix\n");
    Matrix ed;
    ed = one_matrix(3, 3);
    matrix_output(ed);
    clean_memory(ed);*/
}