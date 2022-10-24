#include "matrix_lib.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


const double EPS = 10e-6;


// Вывод матрицы в консоль
void printm(struct Matrix mat){
    printf("\n");
    for (unsigned int row = 0; row < mat.rows; row++){
        for (unsigned int col = 0; col < mat.cols; col++){
            printf(" %f", mat.values[row * mat.cols + col]);
        }
        printf("\n");
    }
}


Matrix create_null(){
    Matrix mat = {0, 0, NULL};
    return mat;
}


Matrix create_empty(const unsigned int rows, const unsigned int cols){
    double* data_ptr = malloc(sizeof(double) * rows * cols);
    if (data_ptr == NULL) return create_null();
    Matrix mat = {rows, cols, data_ptr};
    return mat;
}


Matrix create_zero(const unsigned int rows, const unsigned int cols){
    Matrix mat = create_empty(rows, cols);
    for (unsigned int idx = 0; idx < rows * cols; idx++) mat.values[idx] = 0.0;
    return mat;
}


// Создание единичной матрицы размера n*n
Matrix create_identity(const unsigned int size){
    Matrix mat = create_zero(size, size);
    for (unsigned int idx = 0; idx < size * size; idx += size + 1){
        mat.values[idx] = 1.0;
    }
    return mat;
}


// Создание матрицы со случайными значениями от 0 до max_value
Matrix create_random(const unsigned int rows, const unsigned int cols, const double max_value){
    Matrix mat = create_empty(rows, cols);
    for (unsigned int idx = 0; idx < rows * cols; idx++){
        mat.values[idx] = ((double)rand() / (double)(RAND_MAX)) * max_value;
    }
    return mat;
}


// Делает заданную матрицу единичной
void set_to_identity(const Matrix* mat){
    unsigned int size = mat->cols;
    for (unsigned int idx = 0; idx < size * size; idx++){
        mat->values[idx] = idx % (size + 1) == 0 ? 1.0 : 0.0;
    }
}


// Создает копию матрицы
Matrix copy(const Matrix mat){
    Matrix copy = create_empty(mat.rows, mat.cols);
    for (unsigned int idx = 0; idx < mat.rows * mat.cols; idx++) copy.values[idx] = mat.values[idx];
    return copy;
}


// Проверяет равны ли две матрицы
int is_equal(const Matrix mat1, const Matrix mat2){
    if (mat1.cols != mat2.cols || mat1.rows != mat2.rows) return 0;
    for (unsigned int idx = 0; idx < mat1.cols * mat1.rows; idx++){
        if (fabs(mat1.values[idx] - mat2.values[idx]) > EPS) return 0;
    }
    return 1;
}


int is_identity(const Matrix matrix){
    if (matrix.cols != matrix.rows) return 0;
    unsigned int size = matrix.rows;
    for (unsigned int idx = 0; idx < size * size; idx++){
        if (idx % (size + 1) == 0){
            if (fabs(matrix.values[idx] - 1) > EPS)  return 0;
        }
        else{
            if (fabs(matrix.values[idx]) > EPS) return 0;
        }
    }
    return 1;
}


// Сложение двух матриц
Matrix add(Matrix m1, const Matrix m2){
    if (m1.cols != m2.cols || m1.rows != m2.rows){
        return create_null();
    }
    for (unsigned int idx = 0; idx < m1.rows * m1.cols; idx++){
        m1.values[idx] = m1.values[idx] + m2.values[idx];
    }
    return m1;
}


// Вычитание двух матриц
Matrix sub(Matrix m1, const Matrix m2){
    if (m1.cols != m2.cols || m1.rows != m2.rows){
        return create_null();
    }
    for (unsigned int idx = 0; idx < m1.rows * m1.cols; idx++){
        m1.values[idx] = m1.values[idx] - m2.values[idx];
    }
    return m1;
}


// Умножение двух матриц
Matrix mul(Matrix m1, const Matrix m2){
    if (m1.cols != m2.rows){
        return create_null();
    }
    Matrix temp = create_empty(m1.rows, m1.cols);
    for (unsigned int row = 0; row < temp.rows; row++){
        for (unsigned int col = 0; col < temp.cols; col++){
            double summa = 0.0;
            for (unsigned int idx = 0; idx < m1.cols; idx++){
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
    for (unsigned int idx = 0; idx < mat.rows * mat.cols; idx++){
        mat.values[idx] = mat.values[idx] * scal;
    }
    return mat;
}


// Деление матрицы на скаляр
Matrix s_div(const Matrix mat, const double scal){
    for (unsigned int idx = 0; idx < mat.rows * mat.cols; idx++){
        mat.values[idx] = mat.values[idx] / scal;
    }
    return mat;
}


// Транспонирование матрицы
Matrix transpose(Matrix mat){
    Matrix temp = create_empty(mat.cols, mat.rows);
    for (unsigned int row = 0; row < mat.rows; row++){
        for (unsigned int col = 0; col < mat.cols; col++){
            temp.values[col * temp.rows + row] = mat.values[row * temp.cols + col];
        }
    }
    free(mat.values);
    mat = temp;
    return mat;
}


// Минор матрицы по строке minor_row и столбцу minor_col
Matrix minor(Matrix mat, const unsigned int minor_row, const unsigned int minor_col){
    Matrix temp = create_empty(mat.rows - 1, mat.cols - 1);
    int minor_index = 0;
    for (unsigned int row = 0; row < mat.rows; row++){
        for (unsigned int col = 0; col < mat.cols; col++) {
            if (row != minor_row && col != minor_col) {
                temp.values[minor_index++] = mat.values[row * mat.rows + col];
            }
        }
    }
    free(mat.values);
    mat = temp;
    return mat;
}


// Превращает матрицу в верхнюю треугольную
Matrix upper_triangle(Matrix mat){
    // TODO: Обработка случаев когда есть нулевые элементы
    for (unsigned int col = 0; col < mat.cols - 1; col++){
        for (unsigned int row = col + 1; row < mat.rows; row++){
            double factor = mat.values[row * mat.rows + col] / mat.values[col * mat.rows + col];
            for (unsigned int idx = col; idx < mat.cols; idx++){
                mat.values[row * mat.cols + idx] -= mat.values[col * mat.rows + idx] * factor;
            }
        }
    }
    return mat;
}


double m_det(const Matrix mat){
    if (mat.cols != mat.rows){
        return NAN;
    }
    double ans = 1;
    Matrix temp = upper_triangle(copy(mat));
    for (unsigned int idx = 0; idx < temp.rows * temp.cols; idx += temp.cols + 1) ans *= temp.values[idx];
    free(temp.values);
    return ans;
}


// Рекурсивная функция определителя матрицы
double recursive_det(const Matrix mat){
    if (mat.cols != mat.rows){
        return NAN;
    }
    double ans = 0.0;
    if (mat.rows == 2){
        ans = mat.values[0] * mat.values[3] - mat.values[1] * mat.values[2];
        return ans;
    }  // Определитель матрицы порядка 2 считается по формуле
    for (unsigned int idx = 0; idx < mat.rows; idx++){
        if (mat.values[idx] != 0){
            Matrix temp = minor(copy(mat), 0, idx);
            ans += mat.values[idx] * pow(-1, idx) * recursive_det(temp);
            free(temp.values);
        }
    }  // Определители матриц больших порядков считаются разложением по первой строке
    return ans;
}


// След (trace) матрицы
double m_tr(Matrix mat){
    if (mat.cols != mat.rows){
        return NAN;
    }
    unsigned int size = mat.cols;
    double trace = 0.0;
    for (unsigned int idx = 0; idx < size * size; idx += size + 1) trace += mat.values[idx];
    return trace;
}


// Обратная матрица
Matrix m_inv(Matrix mat){
    if (mat.cols != mat.rows){
        return create_null();
    }
    Matrix ans = create_empty(mat.rows, mat.cols);
    double determinant = m_det(mat);
    Matrix temp;
    for (unsigned int row = 0; row < mat.rows; row++){
        for (unsigned int col = 0; col < mat.cols; col++){
            temp = minor(copy(mat), row, col);
            ans.values[col * ans.rows + row] = pow(-1, row + col) *
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
    unsigned int max_cycles = 100;
    double trace_old = m_tr(*ans);
    Matrix power = mat;
    unsigned long long int factorial = 1;
    Matrix temp = create_identity(ans->rows);
    int counter = 1;
    while (fabs(m_tr(temp) - trace_old) / trace_old > accuracy && counter < max_cycles){
        trace_old = m_tr(temp);
        temp = add(temp, s_div(power, (double) factorial));
        factorial *= ++counter;
        power = mul(power, mat);
    }
    for (unsigned int idx = 0; idx < ans->rows * ans->cols; idx++) ans->values[idx] = temp.values[idx];
    free(temp.values);
}


// Экспонентная матрицы
Matrix m_exp(Matrix mat){
    if (mat.cols != mat.rows) return create_null();
    Matrix ans = create_empty(mat.rows, mat.cols);
    for (unsigned int row = 0; row < mat.rows; row++){
        for (unsigned int col = 0; col < mat.cols; col++){
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