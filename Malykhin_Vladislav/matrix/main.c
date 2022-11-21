#include <stdio.h>
#include <malloc.h>

typedef struct Matrix{
    unsigned int rows;
    unsigned int columns;
    double  **cells;
} Matrix;

void matrix_zero(Matrix *matrix){
    for(int rows = 0; rows < matrix->rows; rows++)
        for(int columns = 0; columns < matrix->columns; columns++)
            matrix->cells[rows][columns] = 0;
}

void matrix_make(unsigned int rows, unsigned int columns, Matrix *matrix){ //выделяет память под нулевую матрицу размера rows*columns
    matrix->rows = rows;
    matrix->columns = columns;
    matrix->cells = (double **)malloc(sizeof(double *) * matrix->rows + sizeof(double) * matrix->rows * matrix->columns);
    double* start = (double*)((char*)matrix->cells + matrix->rows * sizeof(double*));
    for(rows = 0; rows < matrix->rows; rows++)
        matrix->cells[rows] = start + rows * matrix->columns;
    matrix_zero(matrix);
}

void matrix_copy (Matrix matrix1, Matrix *matrix3){
    matrix3->rows = matrix1.rows;
    matrix3->columns = matrix1.columns;
    for(int rows = 0; rows < matrix3->rows; rows++)
        for(int columns = 0; columns < matrix3->columns; columns++)
            matrix3->cells[rows][columns] = matrix1.cells[rows][columns];
}

void matrix_fill_0123(Matrix *matrix){
    for(int rows = 0; rows < matrix->rows; rows++)
        for(int columns = 0; columns < matrix->columns; columns++)
            matrix->cells[rows][columns] = rows * matrix->columns + columns;
}

void matrix_print(Matrix matrix) {
    for (int rows = 0; rows < matrix.rows; ++rows) {
        for (int columns = 0; columns < matrix.columns; ++columns)
            printf("%lf\t", matrix.cells[rows][columns]);
        printf("\n");
    }
    printf("\n");
}

void matrix_multiply_matrix(Matrix matrix1, Matrix matrix2, Matrix *matrix3){
    for(int rows1 = 0;  rows1 < matrix1.rows; rows1++)
        for(int columns1 = 0; columns1 < matrix2.columns; columns1++)
            for(int columns2 = 0; columns2 < matrix1.columns; columns2++)
                matrix3->cells[rows1][columns1] += matrix1.cells[rows1][columns2] * matrix2.cells[columns2][rows1];
}

void matrix_multiply_number(Matrix matrix, double a, Matrix *matrix3){
    for(int rows = 0; rows < matrix.rows; rows++)
        for (int columns = 0; columns < matrix.columns; columns++)
            matrix3->cells[rows][columns] = a * matrix.cells[rows][columns];
}

void matrix_multiply_test(Matrix matrix1, Matrix matrix2, double a){
    Matrix matrix_multiplied;
    matrix_make(matrix1.rows, matrix1.columns, &matrix_multiplied);
    printf("Matrix multiplied by number\n");
    matrix_multiply_number(matrix1, a, &matrix_multiplied);
    matrix_print(matrix_multiplied);
    free(matrix_multiplied.cells);
    printf("Matrix multiplied by matrix\n");
    if(matrix1.columns == matrix2.rows) {
        matrix_make(matrix1.rows,matrix2.columns,&matrix_multiplied);
        matrix_multiply_matrix(matrix1, matrix2, &matrix_multiplied);
        matrix_print(matrix_multiplied);
        free(matrix_multiplied.cells);
    }
    else printf("Error: the count of columns of the first matrix doesn't equal to the count of the rows of the second matrix\n");
}

void matrix_addition(Matrix matrix1, Matrix matrix2, Matrix *matrix3){
        for(int rows = 0; rows < matrix1.rows; rows++)
         for (int columns = 0; columns < matrix1.columns; columns++)
             matrix3->cells[rows][columns] = matrix1.cells[rows][columns] + matrix2.cells[rows][columns];
}

void matrix_subtraction(Matrix matrix1, Matrix matrix2, Matrix *matrix3){
    for(int rows = 0; rows < matrix1.rows; rows++)
        for (int columns = 0; columns < matrix1.columns; columns++)
            matrix3->cells[rows][columns] = matrix1.cells[rows][columns] - matrix2.cells[rows][columns];
}

void matrix_addition_subtraction_test(Matrix matrix1, Matrix matrix2){
    Matrix matrix3;
    matrix_make(matrix1.rows,matrix1.columns,&matrix3);
    if(matrix1.rows == matrix2.rows && matrix1.columns == matrix2.columns){
        matrix_addition(matrix1, matrix2, &matrix3);
        printf("The result of addition\n");
        matrix_print(matrix3);
        matrix_subtraction(matrix1, matrix2, &matrix3);
        printf("The result of subtraction\n");
        matrix_print(matrix3);
        free(matrix3.cells);
    } else printf("Error: the sizes of the matrices are different\n");
}

void matrix_transposition(Matrix matrix, Matrix *matrix_out){
    for(int rows = 0; rows < matrix.rows; rows++)
        for(int columns = 0; columns < matrix.columns; columns++)
            matrix_out->cells[rows][columns] = matrix.cells[columns][rows];
}

void transposition_test(Matrix matrix){
    Matrix matrix3;
    matrix_make(matrix.rows, matrix.columns,&matrix3);
    matrix_transposition(matrix, &matrix3);
    printf("The result of transposition\n");
    matrix_print(matrix3);
    free(matrix3.cells);
}

Matrix matrix_minor(Matrix matrix, int row, int column){
    Matrix matrix_out;
    matrix_make(--matrix.rows, --matrix.columns, &matrix_out);
    unsigned int i = 0; // индексы элементов новой матрицы размера (n-1)*(n-1)
    unsigned int j = 0;
    for(int rows = 0; rows < matrix.rows; rows++){
        for(int columns = 0; columns < matrix.columns; columns++){
            if(columns == column && rows == row) continue;
            else {
                matrix_out.cells[i][j] = matrix.cells[rows][columns];
                j++;
            }
        }
        i++;
    }
    return matrix_out;
}

double matrix_determinant(Matrix matrix){
    if(matrix.rows > 2){ // если матрица о размеру больше, чем > 2*2, то находим миноры и алгебраические дополения
        double determinant = 0;
        int k = 1;
        for(int columns = 0; columns < matrix.columns; columns++){
           Matrix matrix3;
           matrix3 = matrix_minor(matrix, 0,columns); // создаём матрицу размера (n-1)*(n-1) для нохождения минора
            determinant = matrix.cells[0][columns] * k * matrix_determinant(matrix3);
            k = -k;
            free(matrix3.cells);
        }
        return determinant;
    }    else
        switch (matrix.rows) {
            case 2:
                return matrix.cells[0][0] * matrix.cells[1][1] - matrix.cells[1][0] * matrix.cells[0][1];
            case 1:
                return matrix.cells[0][0];
        }
}

void matrix_determinant_test(Matrix matrix){
    if(matrix.rows == matrix.columns) printf("Matrix determinant = %lf\n\n", matrix_determinant(matrix));
    else printf("The matrix isn't square\n");
}

void invert_matrix(Matrix matrix, Matrix *matrix3){
    int k = 1;
    double det = matrix_determinant(matrix);
    if (det < 0.0001 && det > -0.0001) printf("Determinant of the matrix equals zero\n");
    else
        for (int rows = 0; rows < matrix.rows; ++rows)
            for (int columns = 0; columns < matrix.columns; ++columns) {
                matrix3->cells[rows][columns] = matrix_determinant(matrix_minor(matrix, rows, columns)) * k / det;
                k = -k;
            }
}

void invert_test(Matrix matrix){
    Matrix matrix3;
    matrix_make(matrix.rows, matrix.columns, &matrix3);
    printf("Invertible matrix: \n");
    invert_matrix(matrix,&matrix3);
    matrix_print(matrix3);
    free(matrix3.cells);
}


void matrix_power(Matrix matrix, int power, Matrix *matrix3){
    switch (power) {
        case 0:
            for (int rows = 0; rows < matrix.rows; rows++)
                for(int columns = 0; columns < matrix.columns; columns++)
                    matrix3->cells[rows][rows] = (columns == rows) ? 1 : 0;
            break;
        case 1:
            matrix_copy(matrix, matrix3);
            break;
        default:
            matrix_copy(matrix, matrix3);
            if(power > 0)
            for (int count = 1; count < power; count++)
                matrix_multiply_matrix(*matrix3, matrix, matrix3);
            else{
                power = -power;
                invert_matrix(matrix, matrix3);
                Matrix matrix4;
                matrix_make(matrix3->rows, matrix3->columns, &matrix4);
                matrix_copy(*matrix3, &matrix4);
                matrix_power(matrix4, power, matrix3);
                free(matrix4.cells);
            }
            break;
    }
}

void matrix_exp(Matrix matrix, Matrix *exp_matrix) {
    Matrix matrix1;
    matrix_make(matrix.rows, matrix.columns, &matrix1);
    matrix_copy(matrix, &matrix1);
    int factorial = 1;
    double k;
    for(int count = 0; count < 17; count++){
        if(count > 1) factorial *= count;
        k = 1.0 / factorial;
        matrix_power( matrix1, count, &matrix1);
        matrix_multiply_number( matrix1, k, &matrix1);
        matrix_addition(*exp_matrix, matrix, exp_matrix);
    }
}

void exp_test(Matrix matrix){
    Matrix exp_matrix;
    matrix_make(matrix.rows, matrix.columns, &exp_matrix);
    matrix_exp(matrix, &exp_matrix);
    printf("The result of matrix exponential\n");
    matrix_print(exp_matrix);
    free(exp_matrix.cells);
}

void test(){
    Matrix matrix1;
    matrix_make(2,2,&matrix1);
    matrix_fill_0123(&matrix1);
    Matrix matrix2;
    matrix_make(2,2,&matrix2);
    matrix_fill_0123(&matrix2);
    printf("Matrix1:\n");
    matrix_print(matrix1);
    printf("Matrix2:\n");
    matrix_print(matrix2);
    matrix_addition_subtraction_test(matrix1, matrix2);
    matrix_multiply_test(matrix1, matrix2, 3);
    transposition_test(matrix1);
    matrix_determinant_test(matrix1);
    invert_test(matrix1);
    exp_test(matrix1);
    printf("Matrix1:\n");
    matrix_print(matrix1);
    free(matrix1.cells);//очистка памяти
    free(matrix2.cells);
}

int main(){
   // for (int i = 0; i < 10000; ++i)
   test();
}