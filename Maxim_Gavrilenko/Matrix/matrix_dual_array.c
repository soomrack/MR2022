#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Matrix {
    unsigned int rows;
    unsigned int cols;

    double *data;
    double **values;
}Matrix;


// Очистка памяти и зануление указателя
Matrix free_matrix (Matrix matrix) {
    free(matrix.data);
    free(matrix.values);
    matrix.rows = 0;
    matrix.cols = 0;
    return matrix;
}

// Инициализация памяти
Matrix mem_allocation(const unsigned int rows, const unsigned int cols) {
    Matrix mem;
    mem.rows = rows;
    mem.cols = cols;
    mem.data = (double*)malloc(rows * cols * sizeof (double *));
    mem.values = (void**)malloc(rows * sizeof(void *));

    for (unsigned int row = 0; row < rows; row ++){
        mem.values[row] = mem.data + row * cols;
    }
    return mem;
}


// Блок вывода
void output(const char* function_name, const Matrix A){
    printf("\n%s\n",function_name);
    for (unsigned int row = 0; row < A.rows; row++)
    {
        for (int col = 0; col < A.cols; col++)
        {

            printf("%lf ", A.values[row][col]);
        }
        printf("\n"); // перевод на новую строку
    }
}


// Введение случайных значений в массив
Matrix fill_random(Matrix A) {
    for(unsigned int idx = 0; idx < A.rows * A.cols; idx++){
        A.data[idx] = rand()%10;
    }
    return A;
}


Matrix EMPTY() { // Нулевая матрица в случае ошибочного ввода
    Matrix EMPTY = mem_allocation(0,0);
    EMPTY.values = NULL;
    return EMPTY;
}


Matrix create_zero(const unsigned int rows, const unsigned int cols){ //Создание матрицы из нолей
    Matrix matrix = mem_allocation(rows, cols);
    for (unsigned int row = 0; row < matrix.rows; row++) {
        for (unsigned int col = 0; col < matrix.cols; col++) {
            matrix.values[row][col] = 0;
        }
    }
    return matrix;
}


// Единичная матрица
 Matrix create_one_matrix(unsigned int size){
    Matrix mat = create_zero(size,size);
    for (unsigned int idx = 0; idx < size * size; idx += size + 1) mat.data[idx] = 1.0;
    return mat;
}


 Matrix transposition(const Matrix A){ // Транспонирование матрицы
    Matrix trans = mem_allocation(A.rows,A.cols);
    for (unsigned int row = 0; row < trans.rows; row++){
        for (unsigned int col = 0; col < trans.cols; col++){
            trans.values[row][col] = A.values [col][row];
        }
    }
    return trans;
}


 Matrix addition(const Matrix A, const Matrix B) { // Сложение матриц
    if (A.rows != B.rows || A.cols != B.cols) {
        printf("For Addition Matrix should have same size");
        return EMPTY();
    }
    Matrix add = mem_allocation(A.rows, A.cols);
    for (unsigned int idx = 0; idx < add.rows * add.cols; idx++) {
        add.data[idx] = A.data[idx] + B.data[idx];
    }
    return add;
}


Matrix subtraction(const Matrix A, const Matrix B) { // Сложение матриц
    if (A.rows != B.rows || A.cols != B.cols) {
        printf("For Addition Matrix should have same size");
        return EMPTY();
    }
    Matrix sub = mem_allocation(A.rows, A.cols);
    for (unsigned int idx = 0; idx < sub.rows * sub.cols; idx++) {
        sub.data[idx] = A.data[idx] + B.data[idx];
    }
    return sub;
}


Matrix multiplication(const  Matrix A, const  Matrix B) { // Умножение матриц
    if (A.cols != B.rows) {
        printf("For Multiplication First Matrix Cols should equal to Second Matrix Row");
        return EMPTY();
    }
    Matrix multiplication= mem_allocation(A.rows, B.cols);
    for (unsigned int row = 0; row < multiplication.rows; row++) {
        for (unsigned int col = 0; col < multiplication.cols; col++) {
            double sum = 0;
            for (unsigned int k = 0; k < A.cols; k++) {
                sum += A.values[row][k] * B.values[k][col];
            }
            multiplication.values[row][col] = sum;
        }
    }
    return multiplication;
}


 Matrix multy_k(const Matrix matrix, const double k){ // Умножение матрицы на число
    Matrix multy= mem_allocation(matrix.rows, matrix.cols);
    for (unsigned int index = 0; index < matrix.rows * matrix.cols; index++){
        multy.data[index] = matrix.data[index] * k;
    }
    return multy;
}


Matrix division_k(const Matrix matrix, const double k){ // Деление матрицы на число
    Matrix division = mem_allocation(matrix.rows, matrix.cols);
    for (unsigned int index = 0; index < matrix.rows * matrix.cols; index++){
        division.data[index] = matrix.data[index] / k;
    }
    return division;
}

 Matrix minor(const Matrix matrix, const unsigned int size, const unsigned int row, const unsigned int col) {
    Matrix minor = mem_allocation(size - 1,size - 1);
    int shiftrow = 0; //Смещение индекса строки в матрице
    int shiftcol; //Смещение индекса столбца в матрице
    for (unsigned int rows = 0; rows < size - 1; rows++) {
        if (rows == row) {shiftrow = 1;}
        shiftcol = 0; //Обнулить смещение столбца
        for (unsigned int cols = 0; cols < size - 1; cols++) {
            if (cols == col) {shiftcol= 1;}
            minor.data[rows * (size - 1) + cols] = matrix.data[(rows + shiftrow)* size + (cols + shiftcol)];
        }
    }
    return minor;
}


double determinant(const Matrix matrix, const unsigned int size) { // Определитель с рекурсивным вызовом
    if (matrix.rows != matrix.cols) {
        printf("Matrix should be nxn");
        return 0;
    }
    double det = 0;
    int k = 1;
    if (size == 0) return 0;
    if (size == 1) return matrix.data[0];
    if (size == 2) return (matrix.data[0] * matrix.data[3] - matrix.data[2] * matrix.data[1]);
        for (unsigned int idx = 0; idx < size; idx++) {
            Matrix temp = minor(matrix,size,0,idx);
            det += k * matrix.data[idx] * determinant(temp, size - 1);
            k = -k;
            free_matrix(temp);
        }
    return det;
}


 Matrix reverse_matrix (const Matrix matrix,const unsigned int size) { // Функция нахождения обратной матрицы
    double det = determinant(matrix,size);
    if (matrix.rows != matrix.cols) {
        printf("Matrix should have size nxn");
        return EMPTY();
    }
    if (det == 0){
        printf("Matrix is degenerative, determinate = 0");
        return EMPTY();
    }
    int k = 1;
    Matrix reverse = mem_allocation(size, size);
    Matrix temp;
    for (unsigned int row = 0; row < reverse.rows; row++) {
        for (unsigned int col = 0; col < reverse.cols; col++) {
            temp = minor(matrix,size,row,col);
            reverse.values[row][col] = k * determinant(temp,size - 1);
            k = -k;
        }
    free_matrix(temp);
    }
    Matrix temp_transpose = transposition(reverse);
    free_matrix(reverse);
    Matrix temp_division = division_k(temp_transpose,det);
    free_matrix(temp_transpose);
    reverse = temp_division;
    return reverse;
}


 Matrix exponent_matrix (const Matrix exponent, const unsigned int size) { // Функция нахождения экспоненты матрицы
    if (exponent.rows != exponent.cols) {
        printf("Matrix should have size nxn");
        return EMPTY();
    }
    unsigned int n = 30;
    Matrix ex = create_one_matrix(exponent.rows);
    Matrix temp = create_one_matrix(exponent.rows);
    Matrix temp_multiply;
    Matrix temp_add;
    double fact = 1;
    for (unsigned int i = 1; i < n; i++) {
        fact *= i;
        temp_multiply = multiplication(temp, exponent);
        free_matrix(temp);
        temp = temp_multiply;
        temp_add = addition(ex, division_k(temp, fact));
        free_matrix(ex);
        ex = temp_add;
    }
    free_matrix(temp_multiply);
    return ex;
}


int main() {
    Matrix A = mem_allocation(3,3);
    A = fill_random(A);
    output("First Matrix", A);

   Matrix B = mem_allocation(3,3);
   B = fill_random(B);
   output("Second Matrix", B);

    Matrix add = addition(A,B);
    output("addiction", add);
    free_matrix(add);

    Matrix sub = subtraction(A,B);
    output("subtraction",sub);
    free_matrix(sub);

    Matrix multi = multiplication(A,B);
    output("multiplication", multi);
    free_matrix(multi);

    printf("\ndet %lf\n", determinant(A, A.rows));

    Matrix reverse = reverse_matrix(A,A.rows);
    output("reverse matrix", reverse);
    free_matrix(reverse);
    
    Matrix exponent = exponent_matrix(A,A.rows);
    output("exponent matrix",exponent);
    free_matrix(exponent);

    free_matrix(A);
    free_matrix(B);
    return 0;
}