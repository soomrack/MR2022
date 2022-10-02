#include <math.h>
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

Matrix create_identity(const int size){
    Matrix mat = {size, size, (double*)malloc(sizeof(double) * size * size)};
    for (int idx = 0; idx < size * size; idx++){
        mat.values[idx] = idx % (size + 1) == 0 ? 1 : 0;
    }
    return mat;
}

Matrix m_add(const Matrix m1, const Matrix m2){
    if (m1.cols != m2.cols || m1.rows != m2.rows){
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
    if (m1.cols != m2.cols || m1.rows != m2.rows){
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
    Matrix ans = {mat.cols, mat.rows, (double*)malloc(sizeof(double) * mat.rows * mat.cols)};
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
    for (int row = 0; row < mat.rows; row++){
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
    if (mat.rows == 2){  // Определитель матрицы порядка 2 считается по формуле
        ans = mat.values[0] * mat.values[3] - mat.values[1] * mat.values[2];
        return ans;
    }
    for (int i = 0; i < mat.rows; i++){  // Определители матриц больших порядков считаются разложением по первой строке
        if (mat.values[i] != 0) ans += mat.values[i] * pow(-1, i) * m_det(minor(mat, 0, i));
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

Matrix m_exp(Matrix mat){
    if (mat.cols != mat.rows){
        fprintf(stderr, "number of cols should be equal to number of rows");
        exit(1);
    }  // TODO: вычисление экспоненты не только для диагональных матриц
    Matrix ans = {mat.rows, mat.cols, (double*) malloc(sizeof(double) * mat.rows * mat.cols)};
    for (int row = 0; row < mat.rows; row++){
        for (int col = 0; col < mat.cols; col++){
            if (row != col){
                if (mat.values[row * mat.cols + col] != 0){
                    fprintf(stderr, "for now, this function only works for diagonal matrices");
                    exit(1);
                }
                else ans.values[row * mat.cols + col] = 0;
            }
            else ans.values[row * mat.cols + col] = exp(mat.values[row * mat.cols + col]);
        }
    }
    return ans;
}

unsigned int rank(Matrix mat){
    if (mat.cols == mat.rows && m_det(mat) != 0) return mat.cols;
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
    double values2[16] = {1, 0, 2, 3,
                         0, 2, 0, 4,
                         0, 0, 3, 5,
                         1, 5, 2, 8,};
    Matrix matrix1 = {3, 3, values1};
    Matrix matrix2 = {4, 4, values2};
    Matrix matrix3 = create_identity(4);
    printm(matrix3);

    //printm(m_add(matrix1, matrix2));
    //printm(m_subs(matrix1, matrix2));
    //printm(m_mult(matrix1, matrix2));
    //printm(m_exp(matrix2));
    //printm(minor(matrix2, 2, 2));
    //printm(matrix1);
    printm(m_mul(matrix1, m_inv(matrix1)));

    //printf("%f", m_det(matrix1));
}