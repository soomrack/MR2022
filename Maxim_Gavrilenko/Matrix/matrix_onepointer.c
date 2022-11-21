#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct Matrix {
    unsigned int rows;
    unsigned int cols;
    double *values;
} Matrix;


Matrix memory_allocation (const unsigned int rows, const unsigned int cols){ // Выделение памяти
    Matrix mem = {rows,cols,NULL};
    mem.values = (double*)malloc(rows * cols * sizeof(double));
    if (mem.values == NULL) printf("Memory are not allocated");
    return  mem;
}


Matrix free_matrix(Matrix A){ // Освобождение памяти
    A.rows = 0;
    A.cols = 0;
    free(A.values);
    return A;
}



void output(const char* function_name, Matrix A) { // Блок вывода
    printf("\n%s\n",function_name);
    for (unsigned int row = 0; row<A.rows; row++)
    {
        for (unsigned int col = 0; col<A.cols; col++) printf("%lf ", A.values[row * A.cols + col]);
    printf("\n"); // перевод на новую строку
    }
}


void fill_random(Matrix m) { // Введение случайных значений в массив
    for (unsigned int index = 0; index < m.cols * m.rows; index++) {
        m.values[index] = rand() % 10;
    }
}


Matrix EMPTY() { // Нулевая матрица в случае ошибочного ввода
    Matrix EMPTY = memory_allocation(0,0);
    EMPTY.values = NULL;
    return EMPTY;
}


Matrix create_zero(const unsigned int rows, const unsigned int cols){ //Создание матрицы из нолей
    Matrix matrix = memory_allocation(rows, cols);
    for (unsigned int idx = 0; idx < rows * cols; idx++) matrix.values[idx] = 0.0;
    return matrix;
}


Matrix transposition(const Matrix A){ // Транспонирование матрицы
    Matrix trans = memory_allocation(A.cols,A.rows);
    for (unsigned int row = 0; row < trans.rows; row++){
        for (unsigned int col = 0; col < trans.cols; col++){
            trans.values[row * trans.cols + col] = A.values[col * trans.rows + row];
        }
    }
    return  trans;
}


Matrix minor(const Matrix matrix, const unsigned int size, const unsigned int row, const unsigned int col) { // Минор
    Matrix minor = memory_allocation(matrix.rows - 1,matrix.cols - 1);
    unsigned int shiftrow = 0; //Смещение индекса строки в матрице
    unsigned int shiftcol; //Смещение индекса столбца в матрице
    for (unsigned int rows = 0; rows < size - 1; rows++) {
        //Пропустить rows-ую строку
        if (rows == row) shiftrow = 1;  //Как только встретили строку, которую надо пропустить,
        // делаем смещение для исходной матрицы
        shiftcol = 0; //Обнулить смещение столбца
        for (unsigned int cols = 0; cols < size - 1; cols++) {
            if (cols == col) shiftcol= 1;
            minor.values[rows * (size - 1) + cols] = matrix.values[(rows + shiftrow)* size + (cols + shiftcol)];
        }
    }
    return minor;
}


Matrix create_one_matrix(const unsigned int size){ // Создание единичной матрицы
    Matrix mat = create_zero(size,size);
    for (unsigned int idx = 0; idx < size * size; idx += size + 1) mat.values[idx] = 1.0;
    return mat;
}


Matrix addition(const Matrix A, const Matrix B) { // Сложение матриц
    if (A.rows != B.rows || A.cols != B.cols) {
        printf("For Addition Matrix should have same size");
        return EMPTY();
    }
        Matrix sum = memory_allocation(A.rows, B.cols);
        for (unsigned int index = 0; index < sum.rows * sum.cols; index++) {
                sum.values[index] = A.values[index]+ B.values[index];
        }
        return sum;
}


Matrix subtraction(const Matrix m1, const Matrix m2){ // Вычитание матриц
    if (m1.rows != m2.rows || m1.cols != m2.cols) {
        printf("For Subtraction Matrix should have same size");
        return EMPTY();
    }
    Matrix sub = memory_allocation(m1.rows,m1.cols);
    for (unsigned int index = 0; index < sub.rows * sub.cols; index++) {
            sub.values[index] = m1.values[index] - m2.values[index];
    }
    return sub;
}


Matrix multiplication(const Matrix A, const Matrix B) { // Умножение матриц
    if (A.cols != B.rows) {
        printf("For Multiplication First Matrix cols should equal to Second Matrix rows");
        return EMPTY() ;
    }
        Matrix multiplication = memory_allocation(A.rows,B.cols);
        for (unsigned int row = 0; row < multiplication.rows; row++) {
            for (unsigned int col = 0; col < multiplication.cols; col++) {
                double sum = 0;
                for (unsigned int k = 0; k < A.cols; k++) {
                    sum += A.values[row * A.cols + k] * B.values[k * B.cols + col];
                }
                multiplication.values[row * multiplication.cols + col] = sum;
            }
        }
        return multiplication;
    }


Matrix multy_k(const Matrix matrix, const double k){ // Умножение матрицы на число
    Matrix multy = memory_allocation(matrix.rows,matrix.cols);
    for (unsigned int index = 0; index < matrix.rows * matrix.cols; index++){
        multy.values[index] = matrix.values[index] * k;
    }
    return multy;
}


Matrix division_k(const Matrix matrix, const double k){ // Деление матрицы на число
    Matrix division = memory_allocation(matrix.rows, matrix.cols);
    for (unsigned int index = 0; index < matrix.rows * matrix.cols; index++){
        division.values[index] = matrix.values[index] / k;
    }
    return division;
}


double determinant(const Matrix matrix, const unsigned int size) { // Определитель с рекурсивным вызовом
    if (matrix.rows != matrix.cols) {
        printf("Matrix should be nxn");
        return 0;
    }
    double det = 0;
    int k = 1;
    if (size == 0) return 0;
    if (size == 1) return matrix.values[0];
    if (size == 2) return (matrix.values[0] * matrix.values[3] - matrix.values[2] * matrix.values[1]);
    for (unsigned int idx = 0; idx < size; idx++) {
        Matrix temp = minor(matrix,size,0,idx);
        det += k * matrix.values[idx] * determinant(temp, size - 1);
        k = -k;
        free_matrix(temp);
    }
    return det;
}


Matrix reverse_matrix (const Matrix A,const unsigned int size) { // Функция нахождения обратной матрицы
    double det = determinant(A,size);
    if (A.rows != A.cols) {
        printf("Matrix should have size nxn");
        return EMPTY();
    }
    if (det == 0){
        printf("Matrix is degenerative, determinate is not determined");
        return EMPTY();
    }
    Matrix reverse = memory_allocation(size, size);
    Matrix temp;
    int k = 1;
    for (unsigned int i = 0; i < reverse.rows; i++) {
        for (unsigned int j = 0; j < reverse.cols; j++) {
            temp = minor(A, size,i,j);
            reverse.values[i * size + j] = k * determinant(temp,size -1);
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


Matrix exponent_matrix (const Matrix exponent) { // Функция нахождения экспоненты матрицы
    if (exponent.rows != exponent.cols) {
        printf("Matrix should have size nxn");
        return EMPTY();
    }
    unsigned int n = 30; // Количество членов ряда
    Matrix ex = create_one_matrix(exponent.rows);
    Matrix temp = create_one_matrix(exponent.rows);
    Matrix temp_multiply;
    Matrix temp_add;
    double fact = 1.0;
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


int main()
{
    /*double data1[9] = {1,7,4,
                       0,9,4,
                       8,8,2};*/
    Matrix A;
    A = memory_allocation(3,3);
    fill_random(A);
    output("First Matrix",A);
    Matrix B;
    B = memory_allocation(3,3);
    fill_random(B);
    output("Second Matrix",B);
    Matrix add = addition(A,B);
    output("Addiction", add);
    Matrix sub = subtraction(A,B);
    output("Subtraction", sub);
    Matrix multy = multiplication(A,B);
    output("Multiplication",multy);
    printf("det %lf", determinant(A,A.rows));
    Matrix reverse = reverse_matrix(A,A.rows);
    output("Reverse Matrix", reverse);
    Matrix exp = exponent_matrix(A);
    output("Exponent Matrix", exp);

    free_matrix(A);
    free_matrix(B);
    free_matrix(add);
    free_matrix(sub);
    free_matrix(multy);
    free_matrix(exp);
    return 0;
}
