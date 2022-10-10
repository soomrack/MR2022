#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
struct Matrix {
    unsigned int row;
    unsigned int col;
    double **values;
};


// Очистка памяти
double ** free_memory (double ** values, unsigned int size){
    for (int i = 0; i < size; i++){
        free(values[i]);
    }
    free(values);
    values = NULL;
    return values;
}

// Инициализация памяти
double ** dual_array_initialization(const unsigned int row, const unsigned int col){ // инициализация памяти под массив
    double ** rez = (double **)malloc(row * sizeof(double *));
    for (int i = 0; i < row; i ++){
        rez[i] = (double *)malloc(col*sizeof(double *));
    }
    return rez;
}


// Блок вывода
void output(const char* function_name, struct Matrix A){
    printf("\n%s\n",function_name);
    for (int i = 0; i<A.row; i++)  // цикл по строкам
    {
        for (int j = 0; j<A.col; j++) // цикл по столбцам
        {

            printf("%lf ", A.values[i][j]);
        }
        printf("\n"); // перевод на новую строку
    }
}

// Введение значений
double** input_values(struct Matrix A) {
    A.values = dual_array_initialization(A.row, A.col);
    for (int i = 0; i<A.row; i++)  // цикл по строкам
    {
        for (int j = 0; j<A.col; j++) // цикл по столбцам
        {
            printf("a[%d][%d] = ", i, j);
            scanf("%lf", &A.values[i][j]);
        }
    }
    return A.values;
}


struct Matrix zero(unsigned int size){
    struct Matrix s = {size,size};
    s.values = dual_array_initialization(s.row,s.col);
    for(int i =0 ; i < size; i++){
        for(int j = 0; j < size; j++){
                s.values[i][j] = 0;
        }
    }
    return s;
}


struct Matrix single(unsigned int size){
    struct Matrix s = {size,size};
    s.values = dual_array_initialization(s.row,s.col);
    for(int i =0 ; i < size; i++){
        for(int j = 0; j < size; j++){
            if (i==j)
                s.values[i][j] = 1;
            else
                s.values[i][j] = 0;
        }
    }
    return s;
}


struct Matrix transposition (const struct Matrix trans){ // Транспонирование матрицы
    struct Matrix a = {trans.row,trans.col};
    a.values  = dual_array_initialization(a.row,a.col);
    for (int i = 0; i < a.row; i++){
        for (int j = 0; j < a.col; j++){
            a.values[i][j] = trans.values [j][i];
        }
    }
    return  a;
}


struct Matrix addition(const struct Matrix m1, const struct Matrix m2) { // Сложение матриц
    struct Matrix sum = {0, 0};
    if (m1.row != m2.row || m1.col != m2.col) {
        printf("For Addition Matrix should have same size");
        return sum;
    } else {
        sum.row = m1.row;
        sum.col = m2.col;
        sum.values = dual_array_initialization(sum.row, sum.col);
        for (int i = 0; i < sum.row; i++) {
            for (int j = 0; j < sum.col; j++) {
                sum.values[i][j] = m1.values[i][j] + m2.values[i][j];
            }
        }
        return sum;
    }

}


struct Matrix subtraction(const struct Matrix m1, const struct Matrix m2){ // Вычитание матриц
    struct Matrix sub = {0,0};
    if (m1.row != m2.row || m1.col != m2.col) {
        printf("For Subtraction Matrix should have same size");
        return sub;
    }
    else {
        sub.row = m1.row;
        sub.col = m2.col;
        sub.values = dual_array_initialization(sub.row,sub.col);
        for (int i = 0; i < sub.row; i++) {
            for (int j = 0; j < sub.col; j++) {
                sub.values[i][j] = m1.values[i][j] - m2.values[i][j];
            }
        }
        return sub;
    }

}


struct Matrix multiplication(const struct Matrix m1, const struct Matrix m2) { // Умножение матриц
    struct Matrix multiplication = {0, 0};
    if (m1.col != m2.row) {
        printf("For Multiplication First Matrix Cols should equal to Second Matrix Row");
        return multiplication;
    } else {
        multiplication.row = m1.row;
        multiplication.col = m2.col;
        multiplication.values = dual_array_initialization(multiplication.row, multiplication.col);
        double sum = 0;
        for (int i = 0; i < multiplication.row; i++) {
            for (int j = 0; j < multiplication.col; j++) {
                for (int k = 0; k < m1.col; k++) {
                    sum += m1.values[i][k] * m2.values[k][j];
                }
                multiplication.values[i][j] = sum;
                sum = 0;
            }
        }
        return multiplication;
    }
}


//Возвращает матрицу matrix.c без row-ой строки и col-того столбца
struct Matrix getMatrixhoutRowAndCol(const struct Matrix matrix, const unsigned int size, const unsigned int row, const unsigned int col) {
    struct Matrix m1 = {size - 1,size - 1};
    m1.values = dual_array_initialization(size - 1,size-1);
    int offsetRow = 0; //Смещение индекса строки в матрице
    int offsetCol; //Смещение индекса столбца в матрице
    for (int i = 0; i < size - 1; i++) {
        //Пропустить row-ую строку
        if (i == row) {
            offsetRow = 1; //Как только встретили строку, которую надо пропустить, делаем смещение для исходной матрицы
        }
        offsetCol = 0; //Обнулить смещение столбца
        for (int j = 0; j < size - 1; j++) {
            if (j == col) {
                offsetCol = 1;
            }
            m1.values[i][j] = matrix.values[i + offsetRow][j + offsetCol];
        }
    }
    return m1;
}


double matrixDet(const struct Matrix m, const unsigned int size) {
    if (m.row != m.col) {
        printf("Matrix should be nxn");
        return 0;
    } else {
        double det = 0;
        if (size == 1)
            return m.values[0][0];
        else if (size == 2) {
            return (m.values[0][0] * m.values[1][1] - m.values[0][1] * m.values[1][0]);
        } else {
            for (int j = 0; j < size; j++) {
                det += (pow(-1, j) * m.values[0][j] * matrixDet(getMatrixhoutRowAndCol(m, size, 0, j), size - 1));
            }
        }
        for (int i = 0; i < size; i++){
            free(m.values[i]);
        }
        free(m.values);
        return det;
    }
}


struct Matrix multy(const struct Matrix x, const double k){
    struct Matrix rez = {x.row, x.col};
    rez.values = dual_array_initialization(rez.row, rez.col);
    for (int i = 0; i < rez.row; i++){
        for (int j = 0; j < rez.col; j++){
            rez.values[i][j] = x.values[i][j] * k;
        }
    }
    return rez;
}


struct Matrix reverse_matrix (const struct  Matrix rev,const unsigned int size) {
    struct Matrix a = {rev.row, rev.col};
    double d = matrixDet(rev,size);
    if (rev.row != rev.col) {
        printf("Matrix should have size nxn");
        return zero(size);
    }
    else if (d == 0){
        printf("Matrix is degenerative, determinate = 0");
        return zero(size);
    }
    else {
        a.values = dual_array_initialization(a.row, a.col);
        for (int i = 0; i < a.row; i++) {
            for (int j = 0; j < a.col; j++) {
                a.values[i][j] = (pow(-1, i+j) * matrixDet(getMatrixhoutRowAndCol(rev,size,i,j),size -1));
            }
        }
        a = multy(transposition(a), (1 / d));
        return a;
    }
}


struct Matrix exponent_matrix (const struct Matrix expon, const unsigned int size) {
    if (expon.row != expon.col) {
        printf("Matrix should have size nxn");
        return zero(size);
    }
    else
    {
        int n = 30;
        struct Matrix ex = {expon.row, expon.col};
        ex.values = dual_array_initialization(ex.row, ex.col);
        struct Matrix temp = {ex.row, ex.col};
        temp.values = dual_array_initialization(temp.row, temp.col);
        temp = single(size);
        double reverse_fact = 1;
        ex = single((size));
        for (int i = 1; i < n; i++) {
            reverse_fact /= i;
            temp = multiplication(temp, expon);
            ex = addition(ex, multy(temp, reverse_fact));
        }
        for (int i = 0; i < temp.row; i++){
            free(temp.values[i]);
        }
        free(temp.values);
        temp.values = NULL;
        return ex;
    }
}


void menu(struct Matrix A, struct  Matrix B){
    struct Matrix addiction;
    struct Matrix sub;
    struct Matrix multi;
    struct Matrix reverse;
    struct Matrix exponent;
    bool run = true;
    int num;
    while (run) {
        run = false;
        scanf("%d", &num);
        switch (num) {
            case 1:
                addiction = addition(A,B);
                output("addiction", addiction);
                addiction.values = free_memory(addiction.values,addiction.row);
                break;
            case 2:
                sub = subtraction(A,B);
                output("subtraction",sub);
                sub.values = free_memory(sub.values,sub.row);
                break;
            case 3:
                multi = multiplication(A,B);
                output("multiplication", multi);
                multi.values = free_memory(multi.values,multi.row);
                break;
            case 4:
                printf("\ndet %lf\n", matrixDet(A, A.row));
                break;
            case 5:
                reverse = reverse_matrix(A,A.row);
                output("reverse matrix.c", reverse);
                reverse.values = free_memory(reverse.values,reverse.row);
                break;
            case 6:
                exponent = exponent_matrix(A,A.row);
                output("exponent matrix.c",exponent);
                exponent.values = free_memory(exponent.values,exponent.row);
                break;
            default:
                printf("Incorrect input\nInput new number");
                run = true;
        }
    }
}


int main() {
/*    struct Matrix addiction;
    struct Matrix sub;
    struct Matrix multi;
    struct Matrix reverse;
    struct Matrix exponent;*/

   struct Matrix A = {3, 3};
    A.values = input_values(A);
    output("First Matrix", A);

    struct Matrix B = {1, 1};
    B.values=input_values(B);
    output("Second Matrix", B);

    printf("Select function in menu\n"
           "1. Addiction of two Matrix\n"
           "2. Subtraction of two Matrix\n"
           "3. Multiplication of two Matrix\n"
           "4. Find det of matrix.c\n"
           "5. Find reverse matrix.c\n"
           "6. Find exponent matrix.c\n");
    menu(A,B);
    A.values = free_memory(A.values,A.row); // Указатель обнулен уже в функции;
    B.values = free_memory(B.values,B.row);
/*
    addiction = addition(A,B);
    output("addiction", addiction);
    addiction.values = free_memory(addiction.values,addiction.row);


    sub = subtraction(A,B);
    output("subtraction",sub);
    sub.values = free_memory(sub.values,sub.row);


    multi = multiplication(A,B);
    output("multiplication", multi);
    multi.values = free_memory(multi.values,multi.row);


    printf("\ndet %lf\n", matrixDet(A, A.row));


    reverse = reverse_matrix(A,A.row);
    output("reverse matrix.c", reverse);
    reverse.values = free_memory(reverse.values,reverse.row);


    exponent = exponent_matrix(A,A.row);
    output("exponent matrix.c",exponent);
    exponent.values = free_memory(exponent.values,exponent.row);

    A.values = free_memory(A.values,A.row);
    B.values = free_memory(B.values,B.row);*/
    return 0;
}