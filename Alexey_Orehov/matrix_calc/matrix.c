#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Matrix{
    unsigned int rows;
    unsigned int cols;
    double* values;
} Matrix;

void printm(struct Matrix matrix){
    printf("\n");
    for (int row = 0; row < matrix.rows; row++){
        for (int col = 0; col < matrix.cols; col++){
            printf(" %f", matrix.values[row * matrix.cols + col]);
        }
        printf("\n");
    }
}

bool same_size(const Matrix m1, const Matrix m2){ return (m1.cols == m2.cols && m1.rows == m2.rows);}

Matrix m_add(const Matrix m1, const Matrix m2){
    if (!same_size(m1, m2)){
        fprintf(stderr, "Matrices should have same size");
        exit(1);
    }
    Matrix ans = {m1.rows, m1.cols, (double*)malloc(sizeof(double) * m1.rows * m2.cols)};
    for (int index = 0; index < ans.rows * ans.cols; index++){
        ans.values[index] = m1.values[index] + m2.values[index];
    }
    return ans;
}

Matrix m_sub(const Matrix m1, const Matrix m2){
    if (!same_size(m1, m2)){
        fprintf(stderr, "Matrices should have same size");
        exit(1);
    }
    Matrix ans = {m1.rows, m1.cols, (double*)malloc(sizeof(double) * m1.rows * m2.cols)};
    for (int index = 0; index < ans.rows * ans.cols; index++){
        ans.values[index] = m1.values[index] - m2.values[index];
    }
    return ans;
}

Matrix m_mul(const Matrix m1, const Matrix m2){
    if (m1.cols != m2.rows){
        fprintf(stderr, "number of cols of matrix 1 should be equal to number of rows of second matrix");
        exit(1);
    }
    Matrix ans = {m1.rows, m2.cols, (double*)malloc(sizeof(double) * m1.rows * m2.cols)};
    for (int rows = 0; rows < ans.rows; rows++){
        for (int cols = 0; cols < ans.cols; cols++){
            double summa = 0.f;
            for (int k = 0; k < m1.cols; k++){
                summa += m1.values[rows * m1.cols + k] * m2.values[k * m2.cols + cols];
            }
            ans.values[ans.cols * rows + cols] = summa;
        }
    }
    return ans;
}

Matrix transpose(const Matrix mat){
    Matrix ans = {mat.cols, mat.rows,
                  (double*)malloc(sizeof(double) * mat.rows * mat.cols)};
    for (int row = 0; row < mat.rows; row++){
        for (int col = 0; col < mat.cols; col++){
            ans.values[col * ans.rows + row] = mat.values[row * ans.cols + col];
        }
    }
    return ans;
}

Matrix minor(const Matrix mat, const unsigned int i, const unsigned int j){
    Matrix minor = {mat.rows - 1, mat.cols - 1};
    minor.values = (double*) malloc(sizeof(double) * minor.cols * minor.rows);
    int minor_index = 0;
    for (int row = 0; row < mat.rows; row++){  // Формирование алгебраического дополнения для элементов первой строки
        for (int col = 0; col < mat.cols; col++) if (row != i && col != j){
                minor.values[minor_index++] = mat.values[row * mat.rows + col];
            }
    }
    return minor;
}

double m_det(const Matrix mat){
    if (mat.cols != mat.rows){
        fprintf(stderr, "number of cols should be equal to number of rows");
        exit(1);
    }
    double ans = 0;
    unsigned int dim = mat.rows;  // Размер матрицы

    if (dim == 2){  // Определитель матрицы порядка 2 считается по формуле
        ans = mat.values[0] * mat.values[3] - mat.values[1] * mat.values[2];
        return ans;
    }
    // Определители матриц больших порядков считаются разложением по первой строке
    for (int i = 0; i < dim; i++){
        ans += mat.values[i] * pow(-1, i) * m_det(minor(mat, 0, i));
    }
    return ans;
}

Matrix m_inv(Matrix mat){
    if (mat.cols != mat.rows){
        fprintf(stderr, "number of cols should be equal to number of rows");
        exit(1);
    }
    Matrix inv = {mat.rows, mat.cols, (double*) malloc(sizeof(double) * mat.rows * mat.cols)};
    double determinant = m_det(mat);
    for (int row = 0; row < mat.rows; row++){
        for (int col = 0; col < mat.cols; col++){
            inv.values[row * inv.cols + col] = pow(-1, row + col) *
                                               m_det(minor(mat, row, col)) / determinant;
        }
    }
    return transpose(inv);
}

unsigned int rank(Matrix mat){
    if (mat.cols == mat.rows && m_det(mat) != 0) return mat.cols;
    // TODO Вычисление ранга матрицы
    return 0;
}


int main(){
//    double values1[6] = {3, 2, 1,
//                         0, 1, 2};
//    double values2[6] = {1, 2,
//                         2, 0,
//                         3, 1};
//    Matrix matrix1 = {2, 3, values1};
//    Matrix matrix2 = {3, 2, values2};

    double values1[9] = {3, -1, 2,
                         4, 2, 0,
                         -5, 6, 1};
    double values2[9] = {0.026, 0.167, -0.051,
                         -0.051, 0.167, 0.103,
                         0.436, -0.167, 0.128};
    Matrix matrix1 = {3, 3, values1};
    Matrix matrix2 = {3, 3, values2};

    //printm(m_add(matrix1, matrix2));
    //printm(m_subs(matrix1, matrix2));
    //printm(m_mult(matrix1, matrix2));
    printm(matrix1);
    printm(m_mul(matrix1, m_inv(matrix1)));

    //printf("%f", m_det(matrix1));

}