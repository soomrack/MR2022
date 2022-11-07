#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <math.h>

typedef struct Matrix{
    unsigned int rows;
    unsigned int columns;
    double  **cells;
} Matrix;

void matrix_make(unsigned int rows, unsigned int columns, Matrix *matrix){ //выделяет память под нулевую матрицу размера rows*columns
    free(matrix->cells);
    matrix->rows = rows;
    matrix->columns = columns;
    matrix->cells = (double **)malloc(sizeof(double *) * matrix->rows + sizeof(double) * matrix->rows * matrix->columns);
    double* start = (double*)((char*)matrix->cells + matrix->rows * sizeof(double*));
    for(rows = 0; rows < matrix->rows; rows++)
        matrix->cells[rows] = start + rows * matrix->columns;
    for(rows = 0; rows < matrix->rows; rows++)
        for (columns = 0; columns < matrix->columns; columns++)
            matrix->cells[rows][columns] = 0;
}

void matrix_fill_rnd(Matrix *matrix){
    for (int rows = 0; rows < matrix->rows; ++rows)
        for (int columns = 0; columns < matrix->columns ; ++columns)
            matrix->cells[rows][columns] = (double)(rand() - 32767 / 2);
        // matrix->cells[rows][columns] = 1.0;
}

void matrix_print(Matrix matrix) {
    for (int rows = 0; rows < matrix.rows; ++rows) {
        for (int columns = 0; columns < matrix.columns; ++columns) {
            printf("%lf \t", matrix.cells[rows][columns] );
        }
        printf("\n");
    }
}
void matrix_multiply_mat(Matrix matrix1,Matrix matrix2, Matrix *matrix3){
    matrix3->rows = matrix1.rows;
    matrix3->columns = matrix2.columns;
    if(matrix1.columns == matrix2.rows){
        for( int rows1 = 0;  rows1 < matrix1.rows; rows1++)
         for(int columns1 = 0; columns1 < matrix2.columns; columns1++)
             for(int columns2 = 0; columns2 < matrix1.columns; columns2++)
                matrix3->cells[rows1][columns1] += matrix1.cells[rows1][columns2] * matrix2.cells[columns2][rows1];
    }
    else printf("The count of columns of the first matrix doesn't equal to the count of the rows of the second matrix\n");
}

void matrix_addition(Matrix matrix1, Matrix matrix2, Matrix *matrix3){

    if(matrix1.rows == matrix2.rows && matrix1.columns == matrix2.columns){
        matrix_make(matrix1.rows, matrix1.columns, matrix3);
        for(int rows = 0; rows < matrix1.rows; rows++)
         for (int columns = 0; columns < matrix1.columns; columns++)
             matrix3->cells[rows][columns] = matrix2.cells[rows][columns] + matrix1.cells[rows][columns];
    }
    else printf("the sizes of the matrices are different\n");
}

void matrix_multiply_const(Matrix matrix1, double a, Matrix *matrix3){
    matrix_make(matrix1.rows, matrix1.columns, matrix3);
    for(int rows = 0; rows < matrix1.rows; rows++)
        for (int columns = 0; columns < matrix1.columns; columns++)
            matrix3->cells[rows][columns] = a * matrix1.cells[rows][columns];
}

void matrix_subtraction(){
}

void matrix_transposition(Matrix matrix1, Matrix *matrix3){
    matrix_make(matrix1.rows, matrix1.columns, matrix3);
    for(int rows = 0; rows < matrix1.rows; rows++)
        for(int columns = 0 ; columns < matrix1.columns; columns++)
            matrix3->cells[rows][columns] = matrix1.cells[columns][rows];
}

void matrix_exp(){
}

double matrix_determinant(Matrix matrix){ //возожна ошибка при вызове, можно обернуть в void  интрерфейс
if(matrix.rows == matrix.columns){
    if(matrix.rows > 2){
        for(int columns = 0; columns < matrix.columns; columns++){
            Matrix matrix3;
            matrix_make(matrix.rows--, matrix.columns--, &matrix3);
            unsigned int i = 0;
            unsigned int j = 0;
            for(int rows1 = 1 ; rows1 < matrix.rows; rows1++){
                for(int columns1 = 0; columns1 < matrix.columns; columns1++){
                    if(columns1 == columns) continue;
                    else {
                        matrix3.cells[i][j] = matrix.cells[rows1][columns1];
                        j++;
                    }
                }
                i++;
             }
            matrix.cells[0][columns] * pow(-1,columns) * matrix_determinant(matrix3);
        }
    }
    else{
    return matrix.cells[0][0] * matrix.cells[1][1] - matrix.cells[1][0] * matrix.cells[0][1];
    }
} else printf("The matrix isn't square\n");
}

int main(){
    srand (time(NULL));
    Matrix matrix1;
    matrix_make(2,2,&matrix1);
    matrix_fill_rnd(&matrix1);
    Matrix matrix2;
    matrix_make(2,2,&matrix2);
    matrix_fill_rnd(&matrix2);
    Matrix matrix3;
    matrix_print(matrix1);
    printf("\n");
    free(matrix1.cells);
    matrix_print(matrix2);
    free(matrix2.cells);

}
