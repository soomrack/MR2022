#include <stdio.h>
#include <stdlib.h>
/*#include <math.h>
#include <stdbool.h>*/
#include <time.h>


typedef struct Matrix{
    unsigned long int cols;
    unsigned long int rows;
    double* values;
} Matrix;


double* initialization(unsigned int cols, unsigned int rows){
    Matrix matrix;
    matrix.cols;
    matrix.rows;
    unsigned int total_size = matrix.cols * matrix.rows;
    matrix.values = malloc(total_size * sizeof(double ));
    return matrix.values;
}


double* enter_values(Matrix matrix){
    srand(time(NULL));
    matrix.values = initialization(matrix.cols,matrix.rows);
    for (int number = 0; number < matrix.cols * matrix.rows ; number++){
        matrix.values[number] = rand()%100;  // Рандомный ввод элементов матрицы
    }
    return matrix.values;
}


void matrix_print (const Matrix matrix){
    for (int row = 0; row < matrix.rows; row++){
        for (int col = 0; col < matrix.cols; col++){
            printf("%.2f ", matrix.values[row * matrix.cols + col]);
        }
        printf("\n");
    }
    printf("\n");
}


void clean_memory (Matrix* matrix){  // очистка памяти
    free (matrix->values);
}


Matrix summation (const Matrix matr1, const Matrix matr2){
    if (matr1.cols != matr2.cols || matr1.rows != matr2.rows){
        printf("Matrices must be of the same size");
        exit(1);
    }
    else{
        Matrix itog;
        itog.values = initialization(matr1.cols, matr1.rows);
        unsigned int total_size = itog.cols * itog.rows;
        itog.values = malloc(total_size * sizeof (double ));
        for (int number = 0; number < total_size; ++number){
            itog.values[number] = matr1.values[number] + matr2.values[number];
        }
        return itog;
    }
}


Matrix subtraction (const Matrix matr1, const Matrix matr2){
    if (matr1.cols != matr2.cols || matr1.rows != matr2.rows){
        printf("Matrices must be of the same size");
        exit(1);
    }
    else{
        Matrix itog;
        itog.values = initialization(matr1.cols, matr1.rows);
        unsigned int total_size = itog.cols * itog.rows;
        itog.values = malloc(total_size * sizeof (double ));
        for (int number = 0; number < total_size; ++number){
            itog.values[number] = matr1.values[number] - matr2.values[number];
        }
        return itog;
    }
}


Matrix multiptication_on_num (const Matrix matr, double num){
    Matrix itog;
    itog.values = initialization(matr.cols, matr.rows);
    unsigned int total_size = itog.cols * itog.rows;
    itog.values = malloc(total_size * sizeof(double));
    for (int number = 0; number < total_size; ++number){
        itog.values[number] = matr.values[number] * num;
    }
    return itog;
}


Matrix multiplication (const Matrix matr1, const Matrix matr2){
    if (matr1.cols != matr2.rows){
        printf("The number of rows of the first matrix must be equal\n"
               "to the number of columns of the second matrix");
        exit (1);
    }
    unsigned int itog_cols = matr2.cols;
    unsigned int itog_rows = matr1.rows;
    Matrix itog;
    itog.values = initialization (itog_cols, itog_rows);
    for (int row = 0; row < itog_rows; ++row){
        for (int col = 0; col < itog_cols; ++col){
            float sum = 0;
            for (int k = 0; k < matr1.cols; ++k){
                sum += matr1.values[row * matr1.cols + k] * matr2.values[k * matr2.cols + col];
            }
            itog.values[row * itog_cols + col] = sum;
        }
    }
    return itog;
}


int main() {

    struct Matrix mat1 = {2,2};
    printf("Matrix 1\n");
    mat1.values = enter_values(mat1);
    matrix_print(mat1);

    struct Matrix mat2 = {2, 2};
    printf("Matrix 2\n");
    mat2.values = enter_values(mat2);
    matrix_print(mat2);

    struct Matrix summat;
    printf("Summa\n");
    summat = summation(mat1, mat2);
    matrix_print(summat);
    clean_memory(&summat);

    struct Matrix subtract;
    printf("Subtraction\n");
    subtract = subtraction (mat1, mat2);
    matrix_print(subtract);
    clean_memory(&subtract);

    struct Matrix mult_on_num;
    printf("Multiplication on num 1\n");
    mult_on_num = multiptication_on_num (mat1, 3);
    matrix_print(mult_on_num);
    clean_memory(&mult_on_num);

    printf("Multiplication on num 2\n");
    mult_on_num = multiptication_on_num (mat2, 6);
    matrix_print(mult_on_num);
    clean_memory(&mult_on_num);
    clean_memory(&mult_on_num);


    struct Matrix multiply;
    printf("Multiplication\n");
    multiply = multiplication(mat1, mat2);
    matrix_print(multiply);
    clean_memory(&multiply);

    clean_memory(&mat1);
    clean_memory(&mat2);

    //return 0;
}