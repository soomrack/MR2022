#include <stdio.h>
#include <malloc.h>

typedef struct Matrix{ // стилистика кода; на вход подавать const, columns переделать в cols
    unsigned int rows;
    unsigned int columns;
    double  **cells;
} Matrix;
void error_message(int error_code){
    switch(error_code) {
        case 1:
            printf("Error: size of matrix_out is wrong.\n");
            break;
        case 2 :
            printf("Error: number of columns of the first matrix isn't equal number of the rows of the second matrix.\n");
            break;
        case 3:
            printf("Error: the sizes of the matrices are different.\n\n");
            break;
        case 4 :
            printf("Error: the matrix isn't square.\n");
            break;
        case 5:
            printf("Error: determinant of the matrix equals zero.\n");
            break;
    }
}

void matrix_zero(Matrix *matrix){
    for(int rows = 0; rows < matrix->rows; rows++)
        for(int columns = 0; columns < matrix->columns; columns++)
            matrix->cells[rows][columns] = 0;
}

void error(Matrix *matrix){
    matrix->rows = 0;
    matrix->columns = 0;
}

void matrix_make(const unsigned int rows_in, const unsigned int columns_in, Matrix *matrix_in){ //выделяет память под нулевую матрицу размера rows*columns
    matrix_in->rows = rows_in;
    matrix_in->columns = columns_in;
    matrix_in->cells
    = (double **)malloc(sizeof(double *) * matrix_in->rows + sizeof(double) * matrix_in->rows * matrix_in->columns);
    double* start = (double*)((char*)matrix_in->cells + matrix_in->rows * sizeof(double*));
    for(int rows = 0; rows < matrix_in->rows; rows++)
        matrix_in->cells[rows] = start + rows * matrix_in->columns;
    matrix_zero(matrix_in);
}

void matrix_copy(const Matrix matrix_in, Matrix *matrix_out){
    matrix_out->rows = matrix_in.rows;
    matrix_out->columns = matrix_in.columns;
    for(int rows = 0; rows < matrix_out->rows; rows++)
        for(int columns = 0; columns < matrix_out->columns; columns++)
            matrix_out->cells[rows][columns] = matrix_in.cells[rows][columns];
}

void matrix_fill_0123(Matrix *matrix_in){
    for(int rows = 0; rows < matrix_in->rows; rows++)
        for(int columns = 0; columns < matrix_in->columns; columns++)
            matrix_in->cells[rows][columns] = rows * matrix_in->columns + columns;
}

void matrix_print(const Matrix matrix_in){
    if(matrix_in.cells == NULL || matrix_in.rows == 0 || matrix_in.columns == 0)  printf("Error occurred.\n\n");
    else {
        for (int rows = 0; rows < matrix_in.rows; ++rows) {
            for (int columns = 0; columns < matrix_in.columns; ++columns)
                printf("%lf\t", matrix_in.cells[rows][columns]);
            printf("\n");
        }
        printf("\n");
    }
}

void matrix_multiply_number(const Matrix matrix_in, const double coefficient, Matrix *matrix_out){
    for(int rows = 0; rows < matrix_in.rows; rows++)
        for (int columns = 0; columns < matrix_in.columns; columns++)
            matrix_out->cells[rows][columns] = coefficient * matrix_in.cells[rows][columns];
}

void matrix_multiply_matrix(const Matrix matrix_in1, const Matrix matrix_in2, Matrix *matrix_out){
    if(matrix_out->rows != matrix_in2.rows || matrix_in2.columns != matrix_in1.columns){
        error_message(1);
        error(matrix_out);
    }
    else
    if(matrix_in1.columns != matrix_in2.rows){
        error_message(2);
        error(matrix_out);
    }
    else{
        for(int rows = 0; rows < matrix_in1.rows; rows++)
            for(int columns = 0; columns < matrix_in2.columns; columns++)
                for(int counter = 0; counter < matrix_in1.columns; counter++)
                    matrix_out->cells[rows][columns] +=
                            matrix_in1.cells[rows][counter] * matrix_in2.cells[counter][columns];
    }
}

void matrix_multiply_test(const Matrix matrix_in1, const Matrix matrix_in2, const double coefficient){
    Matrix matrix_multiplied;
    matrix_make(matrix_in1.rows, matrix_in1.columns, &matrix_multiplied);
    printf("Matrix multiplied by number %lf:\n", coefficient);
    matrix_multiply_number(matrix_in1, coefficient, &matrix_multiplied);
    matrix_print(matrix_multiplied);
    free(matrix_multiplied.cells);
    printf("Matrix multiplied by matrix:\n");
    matrix_make(matrix_in1.rows, matrix_in2.columns, &matrix_multiplied);
    matrix_multiply_matrix(matrix_in1, matrix_in2, &matrix_multiplied);
    matrix_print(matrix_multiplied);
    free(matrix_multiplied.cells);
}

void matrix_addition(const Matrix matrix_in1, const Matrix matrix_in2, Matrix *matrix_out){
        for(int rows = 0; rows < matrix_in1.rows; rows++)
         for (int columns = 0; columns < matrix_in1.columns; columns++)
             matrix_out->cells[rows][columns] = matrix_in1.cells[rows][columns] + matrix_in2.cells[rows][columns];
}

void matrix_subtraction(const Matrix matrix_in1, const Matrix matrix_in2, Matrix *matrix_out){
    for(int rows = 0; rows < matrix_in1.rows; rows++)
        for (int columns = 0; columns < matrix_in1.columns; columns++)
            matrix_out->cells[rows][columns] = matrix_in1.cells[rows][columns] - matrix_in2.cells[rows][columns];
}

void matrix_addition_subtraction_test(const Matrix matrix_in1, const Matrix matrix_in2){
    Matrix matrix3;
    matrix_make(matrix_in1.rows, matrix_in1.columns, &matrix3);
    printf("Addition and subtraction test:\n");
    if(matrix_in1.rows == matrix_in2.rows && matrix_in1.columns == matrix_in2.columns){
        matrix_addition(matrix_in1, matrix_in2, &matrix3);
        printf("The result of addition:\n");
        matrix_print(matrix3);
        matrix_subtraction(matrix_in1, matrix_in2, &matrix3);
        printf("The result of subtraction:\n");
        matrix_print(matrix3);
    } else error_message(3);
    free(matrix3.cells);
}

void matrix_transposition(const Matrix matrix_in, Matrix *matrix_out) {
    for(int rows = 0; rows < matrix_in.rows; rows++)
        for(int columns = 0; columns < matrix_in.columns; columns++)
            matrix_out->cells[rows][columns] = matrix_in.cells[columns][rows];
}

void transposition_test(const Matrix matrix_in){
    Matrix matrix_test;
    matrix_make(matrix_in.rows, matrix_in.columns, &matrix_test);
    matrix_transposition(matrix_in, &matrix_test);
    printf("The result of transposition:\n");
    matrix_print(matrix_test);
    free(matrix_test.cells);
}

Matrix matrix_of_minor(const Matrix matrix_in,const unsigned int row,const unsigned int column){
    Matrix matrix_out;
    matrix_make(matrix_in.rows - 1, matrix_in.columns - 1, &matrix_out);
    unsigned int i = 0; // индексы элементов новой матрицы размера (n-1)*(n-1)
    unsigned int j = 0;
    for(int rows = 0; rows < matrix_in.rows; rows++){
        for(int columns = 0; columns < matrix_in.columns; columns++){
            if(columns != column && rows != row){
                matrix_out.cells[i][j] = matrix_in.cells[rows][columns];
                j++;
            }
        }
        if(rows != row) i++;
        j = 0;
    }
    return matrix_out;
}

double matrix_determinant(const Matrix matrix_in){
    if(matrix_in.rows > 2){ // если матрица по размеру больше, чем > 2*2, то находим миноры и алгебраические дополнения
        double determinant = 0;
        int k = 1;
        for(int columns = 0; columns < matrix_in.columns; columns++){
            Matrix matrix_minor;
            matrix_minor = matrix_of_minor(matrix_in, 0, columns); // создаём матрицу размера (n-1)*(n-1) для нахождения минора
            determinant += matrix_in.cells[0][columns] * k * matrix_determinant(matrix_minor);
            k = -k;
            free(matrix_minor.cells);
        }
        return determinant;
    } else
        if(matrix_in.rows == 2)
            return matrix_in.cells[0][0] * matrix_in.cells[1][1] - matrix_in.cells[1][0] * matrix_in.cells[0][1];
        else
            if(matrix_in.rows == 1)
                return matrix_in.cells[0][0];
}

void matrix_determinant_test(const Matrix matrix_in){
    if(matrix_in.rows == matrix_in.columns) printf("Matrix determinant = %lf\n\n", matrix_determinant(matrix_in));
    else error_message(4);
}

void invert_matrix(const Matrix matrix_in, Matrix *matrix_out){
    if(matrix_in.rows != matrix_in.columns){
        error_message(4);
        error(matrix_out);
    }
    else{
    int k = 1;
    double det = matrix_determinant(matrix_in);
    Matrix matrix_buffer;
    matrix_make(matrix_out->rows, matrix_out->columns, &matrix_buffer);
    if (det < 0.0001 && det > -0.0001)//вынести в константы
    {
        error_message(5);
        error(matrix_out);
    }
    else {
        for (int rows = 0; rows < matrix_in.rows; ++rows)
            for (int columns = 0; columns < matrix_in.columns; ++columns) {
                Matrix matrix_minor = matrix_of_minor(matrix_in, rows, columns);
                matrix_out->cells[rows][columns] = matrix_determinant(matrix_minor) * k / det;
                k = -k;
                free(matrix_minor.cells);
            }
            matrix_transposition(*matrix_out, &matrix_buffer);
            matrix_copy(matrix_buffer, matrix_out);
    }
    free(matrix_buffer.cells);
    }
}

void invert_test(const Matrix matrix_in){
    Matrix matrix_out;
    matrix_make(matrix_in.rows, matrix_in.columns, &matrix_out);
    printf("Invertible matrix:\n");
    invert_matrix(matrix_in, &matrix_out);
    matrix_print(matrix_out);
    free(matrix_out.cells);
}

void matrix_power(const Matrix matrix_in,int power, Matrix *matrix_out){
    switch (power) {
        case 0:
            for (int rows = 0; rows < matrix_in.rows; rows++)
                for(int columns = 0; columns < matrix_in.columns; columns++)
                    matrix_out->cells[rows][rows] = (columns == rows) ? 1 : 0;
            break;
        case 1:
            matrix_copy(matrix_in, matrix_out);
            break;
        default:
            matrix_copy(matrix_in, matrix_out);
            if(power > 0)
            for (int count = 1; count < power; count++)
                matrix_multiply_matrix(*matrix_out, matrix_in, matrix_out);
            else{
                power = -power;
                invert_matrix(matrix_in, matrix_out);
                Matrix matrix_buff;
                matrix_make(matrix_out->rows, matrix_out->columns, &matrix_buff);
                matrix_copy(*matrix_out, &matrix_buff);
                matrix_power(matrix_buff, power, matrix_out);
                free(matrix_buff.cells);
            }
            break;
    }
}

void matrix_exp(const Matrix matrix_in, Matrix *matrix_out) {
    if (matrix_in.rows != matrix_in.columns) {
        error_message(4);
        error(matrix_out);
    }
    else {
        Matrix matrix_buffer;
        matrix_make(matrix_in.rows, matrix_in.columns, &matrix_buffer);
        matrix_copy(matrix_in, &matrix_buffer);
        int factorial = 1;
        double k;
        for (int count = 0; count < 17; count++) {
            if (count > 1) factorial *= count;
            k = 1.0 / factorial;
            matrix_power(matrix_buffer, count, &matrix_buffer);
            matrix_multiply_number(matrix_buffer, k, &matrix_buffer);
            matrix_addition(*matrix_out, matrix_in, matrix_out);
        }
        free(matrix_buffer.cells);
    }
}

void exp_test(const Matrix matrix_in){
    printf("Matrix exponential test:\n");
    Matrix exp_matrix;
    matrix_make(matrix_in.rows, matrix_in.columns, &exp_matrix);
    matrix_exp(matrix_in, &exp_matrix);
    printf("The result of matrix exponential:\n");
    matrix_print(exp_matrix);
    free(exp_matrix.cells);
}

void test(){
    Matrix matrix1;
    matrix_make(3,3,&matrix1);
    matrix_fill_0123(&matrix1);
    matrix1.cells[0][0] = 16; // для теста
    Matrix matrix2;
    matrix_make(3,3,&matrix2);
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
   test();
}