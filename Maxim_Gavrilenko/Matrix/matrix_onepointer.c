#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


struct Matrix {
    unsigned int row;
    unsigned int col;
    double *values;
};


// Инициализация памяти
struct Matrix initialization (const unsigned int row, const unsigned int col){ // инициализация памяти под массив
    struct Matrix mem = {row,col,NULL};
    mem.values = (double*)malloc(row*col*sizeof(double));
    return  mem;
}


// Блок вывода
void output(const char* function_name, struct Matrix A){
    printf("\n%s\n",function_name);
    for (unsigned int row = 0; row<A.row; row++)
    {
        for (unsigned int col = 0; col<A.col; col++)
        {

            printf("%lf ", A.values[row*A.col+col]);
        }
        printf("\n"); // перевод на новую строку
    }
}


void input_data(struct Matrix m) {// Введение значений в массив
    srand(time(NULL));
    for (unsigned int index = 0; index < m.col * m.row; index++) {
        m.values[index] = (double)(rand()%10);
    }
}


// Нулевая матрица в случае ошибочного ввода
struct Matrix Empty(){
    struct Matrix zero = initialization(0,0);
    return zero;
}


struct Matrix transposition (const struct Matrix trans){ // Транспонирование матрицы
    struct Matrix a = initialization(trans.col,trans.row);
    for (unsigned int row = 0; row < a.row; row++){
        for (unsigned int col = 0; col < a.col; col++){
            a.values[row * a.col + col] = trans.values[col*a.row+row];
        }
    }
    return  a;
}

struct Matrix multy_k(const struct Matrix matrix, const double k){ // Умножение матрицы на число
    struct Matrix multy = initialization(matrix.row,matrix.col);
    unsigned int n = multy.row * multy.col;
    for (unsigned int index = 0; index < n; index++){
        multy.values[index] = matrix.values[index] * k;
    }
    return multy;
}


//Минор
struct Matrix getMatrixhoutRowAndCol(const struct Matrix matrix, const unsigned int size, const unsigned int row, const unsigned int col) {
    struct Matrix m1 = initialization(matrix.row - 1,matrix.col - 1);
    unsigned int shiftRow = 0; //Смещение индекса строки в матрице
    unsigned int shiftCol; //Смещение индекса столбца в матрице
    for (int rows = 0; rows < size - 1; rows++) {
        //Пропустить row-ую строку
        if (rows == row) {
            shiftRow = 1; //Как только встретили строку, которую надо пропустить, делаем смещение для исходной матрицы
        }
        shiftCol = 0; //Обнулить смещение столбца
        for (int cols = 0; cols < size - 1; cols++) {
            if (cols == col) {
                shiftCol= 1;
            }
            m1.values[rows*(size-1)+cols] = matrix.values[(rows+shiftRow)*size+(cols+shiftCol)];
        }
    }
    return m1;
}

struct Matrix create_one_matrix(const unsigned int size){
    struct Matrix mat = initialization(size, size);
    for (unsigned int row = 0; row < size; row++){
        for(unsigned int col = 0; col < size; col++){
            if (col == row)
                mat.values[row*mat.col+col] = 1.0;
            else
                mat.values[row*mat.col+col] = 0.0;
        }
    }
    return mat;
}


struct Matrix addition(const struct Matrix m1, const struct Matrix m2) { // Сложение матриц
    if (m1.row != m2.row || m1.col != m2.col) {
        printf("For Addition Matrix should have same size");
        return Empty();
    }
        struct Matrix sum = initialization(m1.row, m1.col);
        for (unsigned int index = 0; index < sum.row * sum.col; index++) {
                sum.values[index] = m1.values[index]+ m2.values[index];
        }
        return sum;
}


struct Matrix subtraction(const struct Matrix m1, const struct Matrix m2){ // Вычитание матриц
    if (m1.row != m2.row || m1.col != m2.col) {
        printf("For Subtraction Matrix should have same size");
        return Empty();
    }
    struct Matrix sub = initialization(m1.row,m2.col);
        for (unsigned int index = 0; index < sub.row * sub.col; index++) {
                sub.values[index] = m1.values[index] - m2.values[index];
        }
        return sub;
    }


struct Matrix multiplication(const struct Matrix m1, const struct Matrix m2) { // Умножение матриц
    if (m1.col != m2.row) {
        printf("For Multiplication First Matrix Cols should equal to Second Matrix Row");
        return Empty() ;
    }
        struct Matrix multiplication = initialization(m1.row,m2.col);
        for (unsigned int row = 0; row < multiplication.row; row++) {
            for (unsigned int col = 0; col < multiplication.col; col++) {
                double sum = 0;
                for (unsigned int k = 0; k < m1.col; k++) {
                    sum += m1.values[row * m1.col + k] * m2.values[k * m2.col + col];
                }
                multiplication.values[row * multiplication.col + col] = sum;
            }
        }
        return multiplication;
    }


double matrixDet(const struct Matrix m, const unsigned int size) { // Определитель с рекурсивным вызовом
    if (m.row != m.col) {
        printf("Matrix should be nxn");
        return 0;
    }
        double det = 0;
        if (size == 0)
            return 0;
        if (size == 1)
            return m.values[0];
        else if (size == 2) {
            return (m.values[0] * m.values[3] - m.values[2] * m.values[1]);
        }
            for (unsigned int idx = 0; idx < size; idx++) {
                struct Matrix temp = getMatrixhoutRowAndCol(m,size,0,idx);
                det += (pow(-1, idx) * m.values[idx] * matrixDet(temp, size - 1));
                free(temp.values);
            }
        return det;
    }


struct Matrix reverse_matrix (const struct  Matrix rev,const unsigned int size) { // Функция нахождения обратной матрицы

    double d = matrixDet(rev,size);
    if (rev.row != rev.col) {
        printf("Matrix should have size nxn");
        return Empty();
    }
    else if (d == 0){
        printf("Matrix is degenerative, determinate is not determined");
        return Empty();
    }
        struct Matrix a = initialization(rev.row,rev.col);
        for (unsigned int i = 0; i < a.row; i++) {
            for (unsigned int j = 0; j < a.col; j++) {
                a.values[i*size+j] = (pow(-1, i+j) * matrixDet(getMatrixhoutRowAndCol(rev,size,i,j),size -1));
            }
        }
        a = multy_k(transposition(a), (1 / d));
        return a;
    }


struct Matrix exponent_matrix (const struct Matrix expon) { // Функция нахождения экспоненты матрицы
    if (expon.row != expon.col) {
        printf("Matrix should have size nxn");
        return Empty();
    }
        unsigned int n = 30; // Количество членов ряда
        struct Matrix ex;
        struct Matrix temp;
        temp = create_one_matrix(expon.row);
        double reverse_fact = 1.0;
        ex = create_one_matrix((expon.row));
        for (unsigned int i = 1; i < n; i++) {
            reverse_fact /= i;
            temp = multiplication(temp, expon);
            ex = addition(ex, multy_k(temp, reverse_fact));
        }
        free(temp.values);
        return ex;
}


int main()
{
    struct Matrix A;
    A=initialization(3,3);
    input_data(A);
    output("First Matrix",A);
    struct Matrix B;
    B = initialization(3,3);
    input_data(B);
    output("Second Matrix",B);
    struct Matrix add = addition(A,B);
    output("Addiction", add);
    struct Matrix sub = subtraction(A,B);
    output("Subtraction", sub);
    struct Matrix multy = multiplication(A,B);
    output("Multiplication",multy);
    printf("det %lf", matrixDet(A,A.row));
    struct Matrix reverse = reverse_matrix(A,A.row);
    output("Reverse Matrix", reverse);
    struct Matrix exp = exponent_matrix(A);
    output("Exponent Matrix", exp);
    free(A.values);
    free(B.values);
    free(add.values);
    free(sub.values);
    free(multy.values);
    free(reverse.values);
    free(exp.values);
    return 0;
}
