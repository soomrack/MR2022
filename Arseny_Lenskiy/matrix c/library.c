#include "library.h"

// Создание матриц

Matrix create_zero_matrix(const unsigned int rows, const unsigned int cols) {
    Matrix zero;
    zero.cols = cols;
    zero.rows = rows;
    //values - значения в строчку; item - ссылки на начало строчек (двумерный массив)
    zero.values = malloc(rows * cols * sizeof(double)); // Выделение памяти под матрицу и возврат адреса этой области; rows и cols - размер области, а sizeof, то какие значения мы может туда записать
    zero.item = malloc(rows * sizeof(double*)); // Выделение памяти под область с ссылками на начало строчек массива
    for(int k = 0; k < rows * cols; k++){
        zero.values[k] = 0.0; // Заполнение 0 значениями
    }
    for(int j = 0; j < rows; j++){
        zero.item[j] = zero.values + j * cols; // Заполнения массива ссылок ссылкамми
    }
    return zero;
}

Matrix create_one_matrix(const unsigned int rows, const unsigned int cols) {
    Matrix one;
    one.cols = cols;
    one.rows = rows;
    one.values = malloc(rows * cols * sizeof(double));
    one.item = malloc(rows * sizeof(double*));
    for(int k = 0; k < rows * cols; k++){
        if((int)(k / cols) == (k % cols)){ //Для элементов находяшихся на главной диагонали
            one.values[k] = 1.0;
        }
        else{
            one.values[k] = 0.0;
        }
    }
    for(int j = 0; j < rows; j++){
        one.item[j] = one.values + j * cols;
    }
    return one;
}

void fill_mat_summ(Matrix *matrix) { //Matrix * - это указатель на матрицу, и работа непосредственно со значениями в исходной матрице
    for(int k = 0; k < matrix->rows * matrix->cols; k++){
        matrix->values[k] = k % matrix->cols + (unsigned int)(k / matrix->cols);
    }
}

void fill_mat_mult(Matrix *matrix) {
    for(int k = 0; k < matrix->rows * matrix->cols; k++){
        matrix->values[k] = k % matrix->cols * (int)(k / matrix->cols);
    }
}

void fill_matrix_val(Matrix *matrix, const double *value) {
    for(int k = 0; k < matrix->rows * matrix->cols; k++){
        matrix->values[k] = value[k];
    }
}

// Действия с матрицами

void free_mat(Matrix *matrix) { //Освобождение памяти
    free(matrix->item);
    free(matrix->values);
}

void message(int ind) {
    printf("%s", MESSAGES[ind]);
}

Matrix matrix_add(const Matrix fst_matx, const Matrix snd_matx) {
    if (fst_matx.rows != snd_matx.rows || fst_matx.cols != snd_matx.cols){
        message(ADD);
        message(ERR);
        return EMPTY;
    }
    unsigned int cols = fst_matx.cols; // Количество строк и столбцев берем из входной матрицы
    unsigned int rows = fst_matx.rows;
    Matrix res_matx = create_zero_matrix(rows,cols); // Созданная копированная матрица сначала нулевая
    for(int k = 0; k < rows * cols; k++){ // Количество элементов в матрице равно кол-во столбцев*строк
        res_matx.values[k] = fst_matx.values[k] + snd_matx.values[k]; // Считаем значения для конечной матрицы
    }
    return res_matx;
}

Matrix matrix_subt(const Matrix fst_matx, const Matrix snd_matx) {
    if (fst_matx.rows != snd_matx.rows || fst_matx.cols != snd_matx.cols){
        message(SUB);
        message(ERR);
        return EMPTY;
    }
    unsigned int cols = fst_matx.cols;
    unsigned int rows = fst_matx.rows;
    Matrix res_matx = create_zero_matrix(rows,cols);
    for(int k = 0; k < rows * cols; k++){
        res_matx.values[k] = fst_matx.values[k] - snd_matx.values[k];
    }
    return res_matx;
}

Matrix matrix_mult(const Matrix fst_matx, const Matrix snd_matx) {
    if (fst_matx.cols != snd_matx.rows){
        message(MULT);
        message(ERR);
        return EMPTY;
    }
    unsigned int cols = snd_matx.cols;
    unsigned int rows = fst_matx.rows;
    Matrix res_matx = create_zero_matrix(rows,cols);
    for(int k = 0; k < rows; k++) {
        for (int j = 0; j < cols; j++) {
            for (int n = 0; n < fst_matx.cols; n++) {
                res_matx.item[k][j] += fst_matx.item[k][n] * snd_matx.item[n][j];
            }
        }
    }
    return res_matx;
}

Matrix matrix_mult_by_num(const double a, const Matrix matrix) {
    unsigned int cols = matrix.cols;
    unsigned int rows = matrix.rows;
    Matrix res_matx = create_zero_matrix(rows,cols);
    for(int k = 0; k < rows * cols; k++) {
        res_matx.values[k] = a * matrix.values[k];
    }
    return res_matx;
}

Matrix matrix_copy(Matrix matrix){
    unsigned int rows = matrix.rows;
    unsigned int cols = matrix.cols;
    Matrix copy = create_zero_matrix(rows,cols);
    for(int k = 0; k < rows * cols; k++){
        copy.values[k] = matrix.values[k];
    }
    return copy;
}

void change_rows(Matrix *matrix, const int fst_row, const int snd_row) {
    double item_buffer;
    for (int k = 0; k < matrix->cols; k++) {
        item_buffer = matrix->item[snd_row][k];
        matrix->item[snd_row][k] = matrix->item[fst_row][k];
        matrix->item[fst_row][k] = item_buffer;
    }
}

double matrix_det(const Matrix matrix) {
    if(matrix.rows != matrix.cols){
        message(DET);
        message(ERR);
        return NAN;
    }
    double det = 1;
    Matrix trian_mat = matrix_copy(matrix);
    for(int row_fix = 0; row_fix < trian_mat.rows - 1; row_fix++) { // Строчка которую будем отнимать
        for (int row = row_fix + 1; row < trian_mat.rows; row++) { // Начинаем со следующей строчки
            if (fabs(trian_mat.item[row_fix][row_fix]) < DETERMINANT_ACCURACY) { // Проверка на деление на ноль
                change_rows(&trian_mat, row_fix, row_fix + 1);
                det = -det;
            }
            double koef = trian_mat.item[row][row_fix] / trian_mat.item[row_fix][row_fix];
            for (int col = 0; col < trian_mat.cols; col++) {
                trian_mat.item[row][col] -= trian_mat.item[row_fix][col] * koef;
            }
        }
        det *= trian_mat.item[row_fix + 1][row_fix + 1];
    }
    free_mat(&trian_mat);
    return det;
}

double check_max_dif(const Matrix fst_mat, const Matrix snd_mat){
    double dif = 0.0;
    for(int k = 0; k < fst_mat.cols * fst_mat.rows; k++){
        if(fabs(fst_mat.values[k] - snd_mat.values[k]) > dif){
            dif = fst_mat.values[k] - snd_mat.values[k];
        }
    }
    return dif;
}

Matrix matrix_exp(const Matrix matrix){
    if(matrix.rows != matrix.cols){
        message(EX);
        message(ERR);
        return EMPTY;
    }
    Matrix res_mat = create_one_matrix(matrix.rows,matrix.cols);
    Matrix n_member = create_one_matrix(matrix.rows,matrix.cols);
    Matrix n1_member = create_zero_matrix(0,0);
    Matrix prev_mat = create_zero_matrix(0,0);
    Matrix mult_mat = create_zero_matrix(0,0);
    for(int m = 1; m <= EXPONENT_STEPS; m++){
        free_mat(&prev_mat);
        prev_mat = matrix_copy(res_mat);
        free_mat(&mult_mat);
        mult_mat = matrix_mult_by_num(1.0 / m, matrix);
        free_mat(&n1_member);
        n1_member = matrix_mult(n_member, mult_mat);
        free_mat(&res_mat);
        res_mat = matrix_add(prev_mat,n1_member);
        free_mat(&n_member);
        n_member = matrix_copy(n1_member);
        if(fabs(check_max_dif(res_mat,prev_mat)) < EXPONENT_ACCURACY){ // проверка на степень точности
            free_mat(&prev_mat);
            free_mat(&n_member);
            free_mat(&n1_member);
            free_mat(&mult_mat);
            return res_mat;
        }
    }
    free_mat(&prev_mat);
    free_mat(&n1_member);
    free_mat(&n_member);
    free_mat(&mult_mat);
    return res_mat;
}

