#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct Matrix{
    unsigned int rows;
    unsigned int cols;
    double* values;
} Matrix;


/*
 TODO:
 Создавать нулевую матрицу, после чего добавлять ей значения
 починить везде unsigned int
 в случае ошибки по вводу выводить пустую матрицу
 В миноре пропускать целиком строки
 Минор в определителе и обратной матрице создавать не теряя память
 */

// Вывод матрицы в консоль
void printm(struct Matrix mat){
    printf("\n");
    for (int row = 0; row < mat.rows; row++){
        for (int col = 0; col < mat.cols; col++){
            printf(" %f", mat.values[row * mat.cols + col]);
        }
        printf("\n");
    }
}


Matrix zero_matrix(){
    Matrix mat = {0, 0, NULL};
    return mat;
}


// Создание единичной матрицы размера n*n
Matrix create_identity(const unsigned int size){
    Matrix mat = {size, size, (double*)malloc(sizeof(double) * size * size)};
    for (int idx = 0; idx < size * size; idx++){
        mat.values[idx] = idx % (size + 1) == 0 ? 1 : 0;
    }
    return mat;
}


// Делает заданную матрицу единичной
void set_to_identity(const Matrix* mat){
    unsigned int size = mat->cols;
    for (int idx = 0; idx < size * size; idx++){
        mat->values[idx] = idx % (size + 1) == 0 ? 1 : 0;
    }
}


// Создает копию матрицы
Matrix copy(const Matrix mat){
    Matrix copy = {mat.rows, mat.cols, (double*) malloc(sizeof(double) * mat.rows * mat.cols)};
    for(int idx = 0; idx < mat.rows * mat.cols; idx++) copy.values[idx] = mat.values[idx];
    return copy;
}


// Проверяет равны ли две матрицы
int equal(const Matrix mat1, const Matrix mat2){
    double eps = 10e-6;
    if (mat1.cols != mat2.cols || mat1.rows != mat2.rows) return 0;
    for (int idx = 0; idx < mat1.cols * mat1.rows; idx++){
        if (fabs(mat1.values[idx] - mat2.values[idx]) > eps) return 0;
    }
    return 1;
}


// Создание матрицы со случайными значениями от 0 до max_value
Matrix create_random(const unsigned int rows, const unsigned int cols, const double max_value){
    Matrix mat = {rows, cols, (double*) malloc(sizeof(double) * cols * rows)};
    for (int idx = 0; idx < rows * cols; idx++){
        mat.values[idx] = ((float)rand() / (float)(RAND_MAX)) * max_value;
    }
    return mat;
}


// Сложение двух матриц
Matrix add(const Matrix m1, const Matrix m2){
    if (m1.cols != m2.cols || m1.rows != m2.rows){
        return zero_matrix();
    }
    for (int idx = 0; idx < m1.rows * m1.cols; idx++){
        m1.values[idx] = m1.values[idx] + m2.values[idx];
    }
    return m1;
}


// Вычитание двух матриц
Matrix sub(const Matrix m1, const Matrix m2){
    if (m1.cols != m2.cols || m1.rows != m2.rows){
        return zero_matrix();
    }
    for (int idx = 0; idx < m1.rows * m1.cols; idx++){
        m1.values[idx] = m1.values[idx] - m2.values[idx];
    }
    return m1;
}


// Умножение двух матриц
Matrix mul(Matrix m1, const Matrix m2){
    if (m1.cols != m2.rows){
        return zero_matrix();
    }
    Matrix temp = {m1.rows, m2.cols, (double*)malloc(sizeof(double) * m1.rows * m2.cols)};
    for (int row = 0; row < temp.rows; row++){
        for (int col = 0; col < temp.cols; col++){
            double summa = 0.0;
            for (int idx = 0; idx < m1.cols; idx++){
                summa += m1.values[row * m1.cols + idx] * m2.values[idx * m2.cols + col];
            }
            temp.values[temp.cols * row + col] = summa;
        }
    }
    free(m1.values);
    m1.values = temp.values;
    return m1;
}


// Умножение матрицы на скаляр
Matrix s_mul(const Matrix mat, const double scal){
    for (int idx = 0; idx < mat.rows * mat.cols; idx++){
        mat.values[idx] = mat.values[idx] * scal;
    }
    return mat;
}


// Деление матрицы на скаляр
Matrix s_div(const Matrix mat, const double scal){
    for (int idx = 0; idx < mat.rows * mat.cols; idx++){
        mat.values[idx] = mat.values[idx] / scal;
    }
    return mat;
}


// Транспонирование матрицы
Matrix transpose(Matrix mat){
    Matrix temp = {mat.cols, mat.rows, (double*)malloc(sizeof(double) * mat.rows * mat.cols)};
    for (int row = 0; row < mat.rows; row++){
        for (int col = 0; col < mat.cols; col++){
            temp.values[col * temp.rows + row] = mat.values[row * temp.cols + col];
        }
    }
    free(mat.values);
    mat = temp;
    return mat;
}


// Минор матрицы по строке minor_row и столбцу minor_col
Matrix minor(Matrix mat, const unsigned int minor_row, const unsigned int minor_col){
    Matrix temp = {mat.rows - 1, mat.cols - 1};
    temp.values = (double*) malloc(sizeof(double) * temp.cols * temp.rows);
    int minor_index = 0;
    for (int row = 0; row < mat.rows; row++){
        for (int col = 0; col < mat.cols; col++) if (row != minor_row && col != minor_col){
                temp.values[minor_index++] = mat.values[row * mat.rows + col];
            }
    }
    free(mat.values);
    mat = temp;
    return mat;
}


// Определитель матрицы
double m_det(const Matrix mat){
    if (mat.cols != mat.rows){
        return 0;
    }
    double ans = 0.0;
    if (mat.rows == 2){
        ans = mat.values[0] * mat.values[3] - mat.values[1] * mat.values[2];
        return ans;
    }  // Определитель матрицы порядка 2 считается по формуле
    for (int idx = 0; idx < mat.rows; idx++){
        if (mat.values[idx] != 0){
            Matrix temp = minor(copy(mat), 0, idx);
            ans += mat.values[idx] * pow(-1, idx) * m_det(temp);
            free(temp.values);
        }
    }  // Определители матриц больших порядков считаются разложением по первой строке
    return ans;
}


// Превращает матрицу в верхнюю треугольную
Matrix upper_triangle(Matrix mat){

    return mat;
}

// След (trace) матрицы
double m_tr(Matrix mat){
    if (mat.cols != mat.rows){
        return 0;
    }
    unsigned int size = mat.cols;
    double trace = 0.0;
    for (int idx = 0; idx < size * size; idx++){
        if (idx % (size + 1) == 0) trace += mat.values[idx];
    }
    return trace;
}


// Обратная матрица
Matrix m_inv(Matrix mat){
    if (mat.cols != mat.rows){
        return zero_matrix();
    }
    Matrix ans = {mat.rows, mat.cols, (double*) malloc(sizeof(double) * mat.rows * mat.cols)};
    double determinant = m_det(mat);
    Matrix temp;
    for (int row = 0; row < mat.rows; row++){
        for (int col = 0; col < mat.cols; col++){
            temp = minor(copy(mat), row, col);
            ans.values[row * ans.cols + col] = pow(-1, row + col) *
                                               m_det(temp) / determinant;
        }
    }

    free(mat.values);
    free(temp.values);
    mat = ans;
    return mat;
}


void iterate_exp(const Matrix* ans, const Matrix mat){
    double accuracy = 0.001;
    double trace_old = m_tr(*ans);
    Matrix power = mat;
    unsigned long long int factorial = 1;
    Matrix temp = create_identity(ans->rows);
    int counter = 1;
    while (fabs(m_tr(temp) - trace_old) / trace_old > accuracy){
        trace_old = m_tr(temp);
        temp = add(temp, s_div(power, (double) factorial));
        factorial *= ++counter;
        power = mul(power, mat);
    }
    for (int idx = 0; idx < ans->rows * ans->cols; idx++) ans->values[idx] = temp.values[idx];
    free(temp.values);
}


// Экспонентная матрицы
Matrix m_exp(Matrix mat){
    if (mat.cols != mat.rows){
        return zero_matrix();
    }
    Matrix ans = {mat.rows, mat.cols, (double*) malloc(sizeof(double) * mat.rows * mat.cols)};
    for (int row = 0; row < mat.rows; row++){
        for (int col = 0; col < mat.cols; col++){
            if (row != col){
                if (mat.values[row * mat.cols + col] != 0){
                    iterate_exp(&ans, mat);
                    return ans;
                }
                else ans.values[row * mat.cols + col] = 0;
            }
            else ans.values[row * mat.cols + col] = exp(mat.values[row * mat.cols + col]);
        }
    }
    return ans;
}