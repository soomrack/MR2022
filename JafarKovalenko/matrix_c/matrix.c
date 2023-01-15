#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct Matrix{
    int row;
    int col;
    double *array;
} Matrix;

void give_matrix_memory(Matrix *matrix){
    matrix->array = (double *) malloc(matrix->row * matrix->col * sizeof(double));
 }

void free_matrix_memory(Matrix *matrix){
    free(matrix->array);
}

void input_matrix(Matrix *matrix, int ROW, int COL, double input[][COL]){
    matrix->row = ROW;
    matrix->col = COL;

    give_matrix_memory(matrix);

    for (int row = 0; row < matrix->row; row++) {
        for (int col = 0; col < matrix->col; col++)
            matrix->array[row * matrix->col + col] = input[row][col];
    }
}

void  matrix_to_array(Matrix *matrix,  double array[matrix->row][matrix->col]){
    for (int row = 0; row < matrix->row; row++){
        for (int col = 0; col < matrix->col; col++){
           array[row][col] = matrix->array[row * matrix->col + col] ; 
        }
    }
}

void fill_zero(Matrix *matrix){
    for (int item = 0; item < (matrix->row * matrix->col); item++)
        matrix->array[item] = 0;
}

void print_matrix(const Matrix *matrix){
    if (matrix == NULL)
        return;

    for (int item = 0; item < (matrix->row * matrix->col); item++){
        if ((item != 0) && ((item % matrix->col) == 0)) {
            printf("\n");
        }
        printf("%6.2f ", matrix->array[item]);
    }
    printf("\n");
}

void exception(int error_code){
    switch (error_code) {
        case 1:
            printf("\nMatrices have different sizes. Addition not possible\n");
            break;
        case 2:
            printf("\nMatrices have different sizes. Subtraction not possible\n");
            break;
        case 3:
            printf("\nThe number of columns doesn't match the number of rows. Multiplication not possible\n");
            break;
        case 4:
            printf("\nThe matrix isn't square. The determinant can't be calculated\n");
            break;
        default:
            printf("ERROR");
    }
}

Matrix *addition_matrix(const Matrix *summand1, const Matrix *summand2){
    if ((summand1->row != summand2->row) || (summand1->col != summand2->col)) {
        exception(1);
        return NULL;
    }

    static Matrix addition_matrix;
    addition_matrix.row = summand1->row;
    addition_matrix.col = summand2->col;
    give_matrix_memory(&addition_matrix);
    fill_zero(&addition_matrix);

    for (int item = 0; item < (summand1->row * summand1->col); item++)
        addition_matrix.array[item] = summand1->array[item] + summand2->array[item];

    return &addition_matrix;
}

Matrix *subtraction_matrix(const Matrix *summand1, const Matrix *summand2){
    if ((summand1->row != summand2->row) || (summand1->col != summand2->col)) {
        exception(2);
        return NULL;
    }

    static Matrix subtraction_matrix;
    subtraction_matrix.row = summand1->row;
    subtraction_matrix.col = summand2->col;
    give_matrix_memory(&subtraction_matrix);
    fill_zero(&subtraction_matrix);

    for (int item = 0; item < (summand1->row * summand1->col); item++)
        subtraction_matrix.array[item] = summand1->array[item] - summand2->array[item];

    return &subtraction_matrix;
}

Matrix *multiplication_by_number_matrix(const Matrix *matrix, double number){
    static Matrix multiplied_matrix;
    multiplied_matrix.row = matrix->row;
    multiplied_matrix.col = matrix->col;
    give_matrix_memory(&multiplied_matrix);
    fill_zero(&multiplied_matrix);

    for (int item = 0; item < (matrix->row * matrix->col); item++)
        multiplied_matrix.array[item] = matrix->array[item] * number;

    return &multiplied_matrix;
}

Matrix *multiplication_matrix(const Matrix *multiplier1, const Matrix *multiplier2){
    if (multiplier1->col != multiplier2->row){
        exception(3);
        return NULL;
    }

    static Matrix product_matrix;
    product_matrix.row = multiplier1->row;
    product_matrix.col = multiplier2->col;
    give_matrix_memory(&product_matrix);
    fill_zero(&product_matrix);

    for (int row = 0; row < product_matrix.row; row++) {
        for (int col = 0; col < product_matrix.col; col++) {
            for (int k = 0; k < multiplier1->col; k++)
                product_matrix.array[row * product_matrix.col + col] +=
                        multiplier1->array[row * multiplier1->col + k] 
                        * multiplier2->array[col + multiplier2->col * k];
        }
    }

    return &product_matrix;
}

Matrix *transpose_matrix(const Matrix *matrix){
    static Matrix transposed_matrix;
    transposed_matrix.row = matrix->col;
    transposed_matrix.col = matrix->row;
    give_matrix_memory(&transposed_matrix);

    for (int row = 0; row < transposed_matrix.row; row++){
        for (int col = 0; col < transposed_matrix.col; col++)
            transposed_matrix.array[row * transposed_matrix.col + col] = matrix->array[col * matrix->col + row];
    }

    return &transposed_matrix;
}


Matrix *minor_matrix(Matrix *matrix, int minor_row, int minor_col){
    static Matrix minor;
    minor.row = matrix->row - 1;
    minor.col = matrix->col - 1;
    give_matrix_memory(&minor);
    print_matrix(matrix);

    int col_offset = 0; // смещение по строке, чтобы "перепрыгнуть" вычеркнутую строку
    int row_offset = 0; // смещение по столбцу, чтобы "перепрыгнуть" вычеркнутый столбец
    
    for (int row = 0; row < minor.row; ++row) {
        if (row == minor_row)
            row_offset = 1;
        for (int col = 0; col < minor.col; ++col) {
            if (col == minor_col)
                col_offset = 1;
            minor.array[row * minor.col + col] = matrix->array[(row + row_offset) * matrix->col + col + col_offset];
        }
        col_offset = 0;
    }
    return &minor;
}

double det_calc(int N, double array[N][N]){
    double det = 0;
    
    if (N == 2){
        return array[0][0]* array[1][1] -
            array[0][1] * array[1][0];
    }
    
    double minor[N - 1][N - 1];
    int offset = 0;

    for (int i = 0; i < N; i++){
        for (int row = 0; row < N - 1; row++){
            for (int col = 0; col < N; col++){
                if (col == i){
                    offset = 1;
                }
                minor[row][col] = array[row + 1][col + offset];
            }
            offset = 0;
        }
        
        det += pow(-1, i) * array[0][i] * det_calc(N - 1, minor);

    }


    return det;
}

Matrix *determinant_matrix(struct Matrix *matrix) {
    if (matrix->row != matrix->col){
        exception(4);
        return NULL;
    }

    double array[matrix->row][matrix->col]; 
    matrix_to_array(matrix, array); 
    
    static Matrix determinant;
    determinant.row = 1; determinant.col = 1;
    give_matrix_memory(&determinant);

    determinant.array[0] = det_calc(matrix->row, array);

    return &determinant;
}


void check(){
    Matrix matrix1;
    Matrix matrix2;

    double test3x3[3][3] = {{1, 2, 3},
                            {4, 5, 6},
                            {7, 8, 1}};

    double test3x2[3][2] = {{-5, 2},
                            {4, 0},
                            {9, 1}};
    double test4x4[4][4] = {{1, 2, 2, 3},
                            {5, 8, 13, 21},
                            {34, 55, 89, 144},
                            {89, 55, 34, 21}};
    double test5x1[5][1] = {{-1}, {2}, {-3}, {4}, {-5}};
    double test1x1[1][1] = {{5}};
    double test2x2[2][2] = {{2, 4},
                            {6, 8}};

    input_matrix(&matrix1, 2, 2, test2x2);
    input_matrix(&matrix2, 4, 4, test4x4);
    
    Matrix *result = multiplication_matrix(&matrix2, &matrix2);
    print_matrix(result);


    free_matrix_memory(&matrix1);
    free_matrix_memory(&matrix2);

    if (result != NULL)
        free_matrix_memory(result);
}

int main(){
    check();
}
