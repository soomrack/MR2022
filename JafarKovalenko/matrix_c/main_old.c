#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct Matrix{
    int row;
    int col;
    double **array;
} Matrix;

double** create_matrix(int rows, int cols){
    double **matrix = malloc(rows * sizeof(double));
    for(int row = 0; row < rows; row++)
        matrix[row] = (double *)malloc(cols * sizeof(double));
    return matrix;
}

void init_matrix(struct Matrix *matrix){
    matrix->array = create_matrix(matrix->row, matrix->col);
    double x = 1;
    for (int row = 0; row < matrix->row; row++) {
        for (int col = 0; col < matrix->col; col++) {
            matrix->array[row][col] = x;
            x += 1;
        }
    }
}

void init_zero_matrix(struct Matrix *matrix){
    matrix->array = create_matrix(matrix->row, matrix->col);
    for (int row = 0; row < matrix->row; row++){
        for (int col = 0; col < matrix->col; col++)
            matrix->array[row][col] = 0;
    }
}

void input_matrix(struct Matrix *matrix, double input[][matrix->col]){
    for (int row = 0; row < matrix->row; row++){
        for (int col = 0; col < matrix->col; col++){
            matrix->array[row][col] = input[row][col];
        }
    }
}

void print_matrix(struct Matrix *matrix) {
    for (int i = 0; i < matrix->row; i++) {
        for (int j = 0; j < matrix->col; j++)
            printf("%6.1f ", matrix->array[i][j]);
        printf("\n");
    }
}

void addition_matrix(struct Matrix *summand1, struct Matrix *summand2){
    if ((summand1->row != summand2->row) || (summand1->col != summand2->col)) {
        printf("Matrices have different sizes. Addition not possible");
        return;
    }

    Matrix addition_matrix;
    addition_matrix.row = summand1->row;
    addition_matrix.col = summand2->col;
    init_zero_matrix(&addition_matrix);

    for (int row = 0; row < summand1->row; row++) {
        for (int col = 0; col < summand1->col; col++) {
            addition_matrix.array[row][col] = summand1->array[row][col] + summand2->array[row][col];
        }
    }

    printf("The result of addition:\n");
    print_matrix(&addition_matrix);
}

void subtraction_matrix(struct Matrix *summand1, struct Matrix *summand2){
    if ((summand1->row != summand2->row) || (summand1->col != summand2->col)) {
        printf("Matrices have different sizes. Subtraction not possible");
        return;
    }

    Matrix subtraction_matrix;
    subtraction_matrix.row = summand1->row;
    subtraction_matrix.col = summand2->col;
    init_zero_matrix(&subtraction_matrix);

    for (int row = 0; row < summand1->row; row++) {
        for (int col = 0; col < summand1->col; col++) {
            subtraction_matrix.array[row][col] = summand1->array[row][col] - summand2->array[row][col];
        }
    }

    printf("The result of subtraction:\n");
    print_matrix(&subtraction_matrix);
}

void multiplication_by_number_matrix(struct Matrix *matrix, double number){

    Matrix multiplied_matrix;
    multiplied_matrix.row = matrix->row;
    multiplied_matrix.col = matrix->col;
    init_zero_matrix(&multiplied_matrix);

    for (int row = 0; row < matrix->row; row++) {
        for (int col = 0; col < matrix->col; col++) {
            multiplied_matrix.array[row][col] = matrix->array[row][col] * number;
        }
    }

    printf("The result of multiplication by number:\n");
    print_matrix(&multiplied_matrix);
}

void multiplication_matrix(struct Matrix *multiplier1, struct Matrix *multiplier2){
    if (multiplier1->col != multiplier2->row){
        printf("The number of columns doesn't match the number of rows. Multiplication not possible");
        return;
    }

    Matrix product;
    product.row = multiplier1->row;
    product.col = multiplier2->col;
    init_zero_matrix(&product);

    for (int row = 0; row < product.row; row++) {
        for (int col = 0; col < product.col; col++) {
            for (int k = 0; k < multiplier1->col; k++)
                product.array[row][col] += multiplier1->array[row][k] * multiplier2->array[k][col];
        }
    }

    printf("The result of multiplication:\n");
    print_matrix(&product);
}

void transpose_matrix(struct Matrix *matrix){
    Matrix transposed;
    transposed.row = matrix->col;
    transposed.col = matrix->row;
    init_matrix(&transposed);

    for (int row = 0; row < matrix->row; row++){
        for (int col = 0; col < matrix->col; col++)
            transposed.array[col][row] = matrix->array[row][col];
    }

    printf("The result of transposing:\n");
    print_matrix(&transposed);
}

struct Matrix *minor_matrix(struct Matrix *matrix, int minor_row, int minor_col){
    static Matrix minor;
    minor.row = matrix->row - 1;
    minor.col = matrix->col - 1;
    init_zero_matrix(&minor);

    int offset_row = 0; // смещение по строке, чтобы "перепрыгнуть" вычеркнутую строку

    for(int row = 0; row < minor.row; row++){
        if (row == minor_row)
            offset_row++;
        int offset_col = 0;

        for (int col = 0; col < minor.col; col++){
            if (col == minor_col)
                offset_col++;
            minor.array[row][col] = matrix->array[row + offset_row][col + offset_col];
        }
    }
    return &minor;
}

double determinant_2x2_matrix(struct Matrix *matrix){
    double det_2x2 = matrix->array[0][0] * matrix->array[1][1]
                    - matrix->array[0][1] * matrix->array[1][0];
    return det_2x2;
}

double determinant_matrix(struct Matrix *matrix) {
    if (matrix->row != matrix->col){
        printf("The number of columns doesn't match the number of rows. Calculation not possible");
        return 0;
    }

    if (matrix->row == 2)
        return determinant_2x2_matrix(matrix);

    double det = 0;
    for (int col = 0; col < matrix->col; col++){
        det += matrix->array[0][col] * pow(-1, col) * determinant_matrix(minor_matrix(matrix, 0, col));
    }
    return det;
}

void inverse_matrix(struct Matrix *matrix){

}

void test_3x3(char *operation){
    double test1[3][3] = {{1, 2, 3},
                         {4, 5, 6},
                         {7, 8, 9}};
    double test2[3][3] = {{5, -2, 4.5},
                          {0, 2, -3.2},
                          {-7, 0, 1}};

    struct Matrix matrix1;
    matrix1.row = 3;
    matrix1.col = 3;
    init_zero_matrix(&matrix1);
    input_matrix(&matrix1, test1);

    struct Matrix matrix2;
    matrix2.row = 3;
    matrix2.col = 3;
    init_zero_matrix(&matrix2);
    input_matrix(&matrix2, test2);

    print_matrix(&matrix1);
    printf("\n");
    print_matrix(&matrix2);

    if (strcmp(operation, "*") == 0){
        multiplication_matrix(&matrix1, &matrix2);
    }
    else if (strcmp(operation, "+") == 0){
        addition_matrix(&matrix1, &matrix2);
    }
    else if (strcmp(operation, "-") == 0){
        subtraction_matrix(&matrix1, &matrix2);
    }
    else if (strcmp(operation, "det") == 0){
        printf("Determinant is %2.2lf\n",determinant_matrix(&matrix1));
    }
    else if (strcmp(operation, "transpose") == 0){
        transpose_matrix(&matrix1);
    }
    else if (strcmp(operation, "inverse") == 0){
        addition_matrix(&matrix1, &matrix2);
    }

}

void check(){

    char *str = "transpose";
    test_3x3(str);

    //test_4x4(str);

    //test_2x3(str);
}

int main(){
    check();
}
