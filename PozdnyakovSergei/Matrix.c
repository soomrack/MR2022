#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
/*#include <time.h>*/


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
    //srand(time(NULL));
    for (int number = 0; number < (matrix->cols * matrix->rows); number++) {
        matrix->value[number] = rand()%100;  // НАДО ИСПРАВИТЬ РАНДОМАЙЗЕР, НЕ ФУРЫЧИТ
    }
}


int is_null (const Matrix matrix) {  // МАТРИЦЫ НЕТ
    if (matrix.cols == 0 && matrix.rows == 0) {
        return 1;
    }
    return 0;
}


void clean_memory (Matrix* matrix) {  // ОЧИСТКА ПАМЯТИ ПОСЛЕ ВЫПОЛНЕНИЯ ОПЕРАЦИИ
    free (matrix->value);
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


/*
Matrix determinant (const Matrix matrix) { // ОПРЕДЕЛИТЕЛЬ МАТРИЦЫ

    return itog;
}
*/

/*Matrix matrix_exponent (const Matrix matrix, unsigned int ) {

    return itog;
}*/


Matrix transponation (const Matrix matrix) {
    Matrix itog = initialization(matrix.rows, matrix.cols);
    for (unsigned int row = 0; row < itog.rows; row++) {
        for (unsigned int col = 0; col < itog.cols; col++) {
            itog.value[row * itog.cols + col] = matrix.value[col * itog.rows + row];
        }
    }
    return itog;
}


int main() {
    Matrix mat1, mat2, mat3;

    printf("\nFirst martix\n");
    mat1 = initialization(3, 3);
    matrix_input(&mat1);
    matrix_output(mat1);

    printf("Second matrix\n");
    mat2 = initialization(3, 4);
    matrix_input(&mat2);
    matrix_output(mat2);

    /*printf("Third matrix\n");
    mat3 = initialization(4, 3);
    matrix_input(&mat3);
    matrix_output(mat3);*/

    printf("Sum of matrices\n");
    Matrix summa;
    summa = summation(mat1, mat2);
    matrix_output(summa);
    clean_memory(&summa);

    printf("Sub of matrices\n");
    Matrix sub;
    sub = subtraction(mat1, mat2);
    matrix_output(sub);
    clean_memory(&sub);

    printf("Multiplying the first matrix by a number\n");
    Matrix mult_on_num1;
    mult_on_num1 = multiply_by_num(mat1, 3);
    matrix_output(mult_on_num1);
    clean_memory(&mult_on_num1);

    printf("Multiplying the second matrix by a number\n");
    Matrix mult_on_num2;
    mult_on_num2 = multiply_by_num(mat2, 5);
    matrix_output(mult_on_num2);
    clean_memory(&mult_on_num2);

    printf("Multiplying the first matrix by a second martix\n");
    Matrix multiply_M_by_M;
    multiply_M_by_M = multiply_matrix_by_matrix(mat1, mat2);
    matrix_output(multiply_M_by_M);
    clean_memory(&multiply_M_by_M);

    printf("Transponated first matrix");
    Matrix trans1;
    trans1 = transponation(mat1);
    matrix_output(trans1);
    clean_memory(&trans1);

    printf("Transponated second matrix");
    Matrix trans2;
    trans2 = transponation(mat2);
    matrix_output(trans2);
    clean_memory(&trans2);



    /*printf("Determinant of the first matrix");
    Matrix det1;
    det1 = determinant(mat1);
    matrix_output(det1);
    clean_memory(&det1);

    printf("Determinant of the second matrix");
    Matrix det2;
    det2 = determinant(mat2);
    matrix_output(det2);
    clean_memory(&det2);

    printf("Exponent of the first matrix");
    Matrix exp1;
    exp1 = matrix_exponent(mat1);
    matrix_output(exp1);
    clean_memory(&exp1);

    printf("Exponent of the second matrix");
    Matrix exp2;
    exp2 = matrix_exponent(exp2);
    matrix_output(exp2);
    clean_memory(&exp2);*/

    printf("\nI HOPE IT'S WORKs RIGHT\n");

    /* ЕСЛИ ИСПОЛЬЗОВАТЬ SRAND И БИБЛИОТЕКУ TIME, ТО ВВОДЯТСЯ "РАНДОМНО"
     * ДВЕ ОДИНАКОВЫЕ МАТРИЦЫ, ЕСЛИ ЗАКОММИТИТЬ ПРЕДЫДУЩИЕ И ИСПОЛЬЗОВАТЬ
     * MATRIX->VALUE[NUMBER] = RAND()%100, ТО ВВОДИТ 2 РАЗНЫЕ МАТРИЦЫ,
     * НО ПРИ КАЖДОМ ПРОГОНЕ ОДНИ И ТЕ ЖЕ*/

}
