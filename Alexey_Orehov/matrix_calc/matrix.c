#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc50-cpp"
#pragma ide diagnostic ignored "cert-msc51-cpp"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Matrix{
    unsigned int rows;
    unsigned int cols;
    double* values;
} Matrix;

void printm(struct Matrix mat){
    // Вывод матрицы в консоль
    printf("\n");
    for (int row = 0; row < mat.rows; row++){
        for (int col = 0; col < mat.cols; col++){
            printf(" %f", mat.values[row * mat.cols + col]);
        }
        printf("\n");
    }
}

Matrix create_identity(const int size){
    // Создание единичной матрицы размера n*n
    Matrix mat = {size, size, (double*)malloc(sizeof(double) * size * size)};
    for (int idx = 0; idx < size * size; idx++) mat.values[idx] = idx % (size + 1) == 0 ? 1 : 0;
    return mat;
}

Matrix create_random(const int rows, const int cols, const double max_value){
    // Создание матрицы со случайными значениями от 0 до max_value
    srand(time(NULL));
    Matrix mat = {rows, cols, (double*) malloc(sizeof(double) * cols * rows)};
    for (int idx = 0; idx < rows * cols; idx++) mat.values[idx] = ((float)rand()/(float)(RAND_MAX)) * max_value;
    return mat;
}

Matrix m_add(const Matrix m1, const Matrix m2){
    // Сложение двух матриц
    if (m1.cols != m2.cols || m1.rows != m2.rows){
        fprintf(stderr, "Matrices should have same size");
        exit(1);
    }
    Matrix ans = {m1.rows, m1.cols, (double*)malloc(sizeof(double) * m1.rows * m2.cols)};
    for (int idx = 0; idx < ans.rows * ans.cols; idx++){
        ans.values[idx] = m1.values[idx] + m2.values[idx];
    }
    return ans;
}

Matrix m_sub(const Matrix m1, const Matrix m2){
    // Вычитание двух матриц
    if (m1.cols != m2.cols || m1.rows != m2.rows){
        fprintf(stderr, "Matrices should have same size");
        exit(1);
    }
    Matrix ans = {m1.rows, m1.cols, (double*)malloc(sizeof(double) * m1.rows * m2.cols)};
    for (int idx = 0; idx < ans.rows * ans.cols; idx++){
        ans.values[idx] = m1.values[idx] - m2.values[idx];
    }
    return ans;
}

Matrix m_mul(const Matrix m1, const Matrix m2){
    // Умножение двух матриц
    if (m1.cols != m2.rows){
        fprintf(stderr, "number of cols of matrix 1 should be equal to number of rows of second matrix");
        exit(1);
    }
    Matrix ans = {m1.rows, m2.cols, (double*)malloc(sizeof(double) * m1.rows * m2.cols)};
    for (int rows = 0; rows < ans.rows; rows++){
        for (int cols = 0; cols < ans.cols; cols++){
            double summa = 0.f;
            for (int idx = 0; idx < m1.cols; idx++){
                summa += m1.values[rows * m1.cols + idx] * m2.values[idx * m2.cols + cols];
            }
            ans.values[ans.cols * rows + cols] = summa;
        }
    }
    return ans;
}

Matrix s_mul(const Matrix mat, const double scal){
    // Умножение матрицы на скаляр
    Matrix ans = {mat.rows, mat.cols, (double*)malloc(sizeof(double) * mat.rows * mat.cols)};
    for (int idx = 0; idx < mat.rows * mat.cols; idx++) ans.values[idx] = mat.values[idx] * scal;
    return ans;
}

Matrix transpose(const Matrix mat){
    // Транспонирование матрицы
    Matrix ans = {mat.cols, mat.rows, (double*)malloc(sizeof(double) * mat.rows * mat.cols)};
    for (int row = 0; row < mat.rows; row++){
        for (int col = 0; col < mat.cols; col++){
            ans.values[col * ans.rows + row] = mat.values[row * ans.cols + col];
        }
    }
    return ans;
}

Matrix minor(const Matrix mat, const unsigned int minor_row, const unsigned int minor_col){
    // Минор матрицы по строке minor_row и столбцу minor_col
    Matrix ans = {mat.rows - 1, mat.cols - 1};
    ans.values = (double*) malloc(sizeof(double) * ans.cols * ans.rows);
    int minor_index = 0;
    for (int row = 0; row < mat.rows; row++){
        for (int col = 0; col < mat.cols; col++) if (row != minor_row && col != minor_col){
                ans.values[minor_index++] = mat.values[row * mat.rows + col];
            }
    }
    return ans;
}

double m_det(const Matrix mat){
    // Определитель матрицы
    if (mat.cols != mat.rows){
        fprintf(stderr, "number of cols should be equal to number of rows");
        exit(1);
    }
    double ans = 0;
    if (mat.rows == 2){
        ans = mat.values[0] * mat.values[3] - mat.values[1] * mat.values[2];
        return ans;
    }  // Определитель матрицы порядка 2 считается по формуле
    for (int idx = 0; idx < mat.rows; idx++){
        if (mat.values[idx] != 0) ans += mat.values[idx] * pow(-1, idx) * m_det(minor(mat, 0, idx));
    }  // Определители матриц больших порядков считаются разложением по первой строке
    return ans;
}

double m_tr(Matrix mat){
    // След (trace) матрицы
    if (mat.cols != mat.rows){
        fprintf(stderr, "number of cols should be equal to number of rows");
        exit(1);
    }
    unsigned int size = mat.cols;
    double trace = 0;
    for (int idx = 0; idx < size * size; idx++) if (idx % (size + 1) == 0) trace += mat.values[idx];
    return trace;
}

Matrix m_inv(Matrix mat){
    // Обратная матрица
    if (mat.cols != mat.rows){
        fprintf(stderr, "number of cols should be equal to number of rows");
        exit(1);
    }
    Matrix ans = {mat.rows, mat.cols, (double*) malloc(sizeof(double) * mat.rows * mat.cols)};
    double determinant = m_det(mat);
    for (int row = 0; row < mat.rows; row++){
        for (int col = 0; col < mat.cols; col++){
            ans.values[row * ans.cols + col] = pow(-1, row + col) *
                                               m_det(minor(mat, row, col)) / determinant;
        }
    }
    return transpose(ans);
}

Matrix m_exp(Matrix mat){
    // Матричная экспонента (На данный момент работает только для диагональных матриц)
    if (mat.cols != mat.rows){
        fprintf(stderr, "number of cols should be equal to number of rows");
        exit(1);
    }
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
    // Ранг матрицы (Пока считает только максимальное значение или 0)
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
    Matrix matrix3 = create_random(3, 3, 5);
    //printm(matrix3);

    //printm(m_add(matrix1, matrix2));
    //printm(m_subs(matrix1, matrix2));
    //printm(m_mult(matrix1, matrix2));
    //printm(m_exp(matrix2));
    printf("%f", m_det(matrix1));
    printm(minor(matrix2, 2, 2));
    //printm(matrix1);
    printm(m_mul(matrix1, m_inv(matrix1)));

    //printf("%f", m_det(matrix1));
}
#pragma clang diagnostic pop