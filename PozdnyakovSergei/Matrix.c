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


Matrix initialization (const unsigned int cols, const unsigned int rows) {  // ИНИЦИАЛИЗАЦИЯ МАТРИЦ
    Matrix matrix;
    matrix.cols = cols;
    matrix.rows = rows;
    unsigned int total_num = matrix.cols * matrix.rows;
    matrix.value = malloc(total_num * sizeof(double ));
    return matrix;
}


void mistake (char* name_of_operation, char* error) {  // ЕСТЬ ОШИБКА В МАТРИЦАХ ИЛИ ОНИ НЕ УДОВЛЕТВОРЯЮТ УСЛОВИЯМ
    printf("%s not possible. %s\n", name_of_operation, error);
}


void matrix_input (Matrix* matrix) {  // РАНДОМНЫЙ ВВОД МАТРИЦ
    for (int number = 0; number < (matrix->cols * matrix->rows); number++) {
        matrix->value[number] = rand()%10;  // НАДО ИСПРАВИТЬ РАНДОМАЙЗЕР, НЕ ФУРЫЧИТ
    }
}


/*void matrix_input (Matrix* matrix) {
    for (int number = 0; number < (matrix->cols * matrix->rows); number++) {
        scanf("%lf", &matrix->value[number]);
    }
}*/


int is_null (const Matrix matrix) {  // МАТРИЦЫ НЕТ
    if (matrix.cols == 0 && matrix.rows == 0) {
        return 1;
    }
    return 0;
}


void clean_memory (Matrix matrix) {  // ОЧИСТКА ПАМЯТИ ПОСЛЕ ВЫПОЛНЕНИЯ ОПЕРАЦИИ
    free (matrix.value);
}


void matrix_output (const Matrix matrix) {  // ВЫВОД МАТРИЦЫ РЕЗУЛЬТАТОВ
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


Matrix summation (const Matrix matrix1, const Matrix matrix2) {  // СУММИРОВАНИЕ
    if (matrix1.cols != matrix2.cols || matrix1.rows != matrix2.rows) {
        mistake("Summation", "Not equal matrix size");
        return ZERO;
        printf("\n");
    }
    Matrix itog = initialization(matrix1.cols, matrix1.rows);
    unsigned int total_num = itog.cols * itog.rows;
    for (unsigned int number = 0; number < total_num; number++) {
        itog.value[number] = matrix1.value[number] + matrix2.value[number];
    }
    return itog;
}


Matrix subtraction (const Matrix matrix1, const Matrix matrix2) {  // ВЫЧИТАНИЕ
    if (matrix1.cols != matrix2.cols || matrix1.rows != matrix2.rows) {
        mistake("Subtraction", "Not equal matrix size");
        return ZERO;
        printf("\n");
    }
    Matrix itog = initialization(matrix1.cols, matrix1.rows);
    unsigned int total_num = itog.cols * itog.rows;
    for (unsigned int number = 0; number < total_num; number++) {
        itog.value[number] = matrix1.value[number] - matrix2.value[number];
    }
    return itog;
}


Matrix one_matrix (const unsigned int cols, const unsigned int rows) {
    Matrix itog = initialization(cols, rows);
    for (unsigned int number = 0; number < cols * rows; number ++) {
        itog.value [number] = 0.0;
        for ( unsigned int num = 0; num <= number; num = num + cols + 1) {
            itog.value[num] = 1.0;
        }
    }
}


Matrix copy_matrix (const Matrix matrix) {
    Matrix itog = initialization(matrix.cols, matrix.rows);
    for (unsigned int number = 0; number < matrix.cols * matrix.rows; number ++) {
        itog.value [number] = matrix.value [number];
    }
    return itog;
}


Matrix multiply_by_num (const Matrix matrix, double num) {  // УМНОЖЕНИЕ МАТРИЦЫ НА ЧИСЛО
    Matrix itog = initialization(matrix.cols, matrix.rows);
    unsigned int total_number = matrix.cols * matrix.rows;
    for (unsigned int number = 0; number < total_number; number++) {
        itog.value[number] = matrix.value[number] * num;
    }
    return itog;
}


Matrix multiply_matrix_by_matrix (const Matrix matrix1, const Matrix matrix2) {  // УМНОЖЕНИЕ МАТРИЦЫ НА МАТРИЦУ
    if (matrix1.cols != matrix2.rows) {
        mistake("Multiply matrix on matrix", "Matrix 1 cols should be equal");
        printf("to matrix 2 rows\n");
        return ZERO;
        printf("\n");
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


/*double determinant (const Matrix matrix) { // ОПРЕДЕЛИТЕЛЬ МАТРИЦЫ
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


Matrix minor (const unsigned int cols, const unsigned int rows, const struct Matrix matrix) {
    struct Matrix itog = initialization(matrix.cols - 1, matrix.rows - 1);
    unsigned int k=0;
    for (unsigned int number = 0; number < matrix.cols * matrix.rows; number ++) {
        if ((number % matrix.cols != cols) && (number / matrix.cols != rows)) {
            itog.value[k++] = matrix.value[number];
        }
    }
    return itog;
}


double determinant (const struct Matrix matrix) {
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


Matrix transponation (const Matrix matrix) {
    Matrix itog = initialization(matrix.rows, matrix.cols);
    for (unsigned int row = 0; row < itog.rows; row++) {
        for (unsigned int col = 0; col < itog.cols; col++) {
            itog.value[row * itog.cols + col] = matrix.value[col * itog.rows + row];
        }
    }
    return itog;
}


Matrix matrix_power (const struct Matrix matrix, unsigned int num) {
    if (matrix.cols != matrix.rows) {
        mistake("Power", "Cols must be equal to rows");
        return ZERO;
    }
    if (num == 0) {
        return one_matrix(matrix.cols, matrix.rows);
    }
    Matrix itog = copy_matrix(matrix);
    for (unsigned int number = 1; number < num; number ++) {
        Matrix new = multiply_matrix_by_matrix(matrix, itog);
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
        itog = multiply_by_num(transponation(itog), 1.0 / determinant(matrix));
        return itog;
    }
}*/


Matrix invert_matrix (const Matrix matrix) {
    if (matrix.cols != matrix.rows) {
        mistake("Getting the inverse matrix", "Matrix must be square and with not zero determinant\n");
        return ZERO;
    }
    Matrix transponent = transponation(matrix);
    Matrix itog = multiply_by_num(transponent, 1. / determinant(matrix));
    clean_memory(transponent);
    return itog;
}


/*Matrix matrix_exponent (const Matrix matrix) {
    if (matrix.cols != matrix.rows) {
        mistake("Exponent", "Matrix must be square");
        return ZERO;
    }
    unsigned int n = 20;
    Matrix itog;
    Matrix temp;
    temp = one_matrix(matrix.cols, matrix.rows);
    double r_factorial = 1.0;
    itog = one_matrix(matrix.cols, matrix.rows);
    for (unsigned int num = 0; num < n; num++) {
        r_factorial /= num;
        temp = multiply_matrix_by_matrix(temp, matrix);
        itog = summation(itog, multiply_by_num(temp, r_factorial));
    }
    clean_memory(temp);
    return itog;
}*/


Matrix matrix_exponent (const Matrix matrix, int accuracy) { // экпонента
    if (matrix.cols != matrix.rows) {
        mistake("Exp", "Matrix should be square");
        return ZERO;
    }
    Matrix new_result , new_powered, multiplied;
    Matrix result = one_matrix(matrix.cols, matrix.rows);
    Matrix powered = matrix;
    new_result = one_matrix(matrix.cols, matrix.rows);
    int factorial = 1;
    for (int acc = 1; acc <= accuracy; ++acc) {
        factorial *= acc;
        new_powered = multiply_matrix_by_matrix(powered, matrix);
        powered = copy_matrix(new_powered);
        clean_memory(new_powered);
        multiplied = multiply_by_num(powered, 1. / factorial);
        new_result = summation(result, multiplied);
        result = copy_matrix(new_result);
        clean_memory(new_result);
        clean_memory(multiplied);
        clean_memory(powered);
    }
/*
    clean_memory(powered);
*/
    return result;
}


int main() {

    Matrix mat1, mat2;

    srand(time(NULL));

    printf("\nFirst martix\n");
    mat1 = initialization(2, 2);
    matrix_input(&mat1);
    matrix_output(mat1);

    printf("Second matrix\n");
    mat2 = initialization(2, 2);
    matrix_input(&mat2);
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
    mult_on_num = multiply_by_num(mat1, 3);
    matrix_output(mult_on_num);
    clean_memory(mult_on_num);

    printf("Multiplying the second matrix by a number\n");
    mult_on_num = multiply_by_num(mat2, 5);
    matrix_output(mult_on_num);
    clean_memory(mult_on_num);

    printf("Multiplying the first matrix by a second martix\n");
    Matrix multiply_M_by_M;
    multiply_M_by_M = multiply_matrix_by_matrix(mat1, mat2);
    matrix_output(multiply_M_by_M);
    clean_memory(multiply_M_by_M);

    printf("Transponated first matrix\n");
    Matrix trans;
    trans = transponation(mat1);
    matrix_output(trans);
    clean_memory(trans);

    printf("Transponated second matrix\n");
    trans = transponation(mat2);
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
    inv = invert_matrix(mat1);
    matrix_output(inv);
    clean_memory(inv);

    printf("Second inverse matrix \n");
    inv = invert_matrix(mat2);
    matrix_output(inv);
    clean_memory(inv);

    printf("First matrix power\n");
    Matrix pow;
    pow = matrix_power(mat1, 2);
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

   /* printf("Unit matrix\n");
    Matrix ed;
    ed = one_matrix(3, 3);
    matrix_output(ed);
    clean_memory(ed);*/
}