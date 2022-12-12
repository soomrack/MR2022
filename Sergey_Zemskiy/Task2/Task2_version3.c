#include <stdio.h>
#include <stdlib.h>


typedef struct Matrix {
    int rows;
    int columns;
    double* values;
} Matrix;


Matrix Mem(int rows, int columns) { //  Выделение памяти под матрицы
    Matrix M0 = {rows, columns, NULL};
    int size = rows * columns;
    M0.values = (double*) malloc(size*sizeof(double));
    if (M0.values == NULL) {
        printf("OS didn't gave memory. \nExit...");
        exit(13);
    }
    return M0;
}


void feeling_matrix (Matrix* rand_matrix) { // Заполнение матриц случайными числами
    for (int i = 0; i < (rand_matrix->rows * rand_matrix->columns); i++) {
            rand_matrix->values[i] = (double) i+1;
    }
}


void print (Matrix Mprint) { // Вывод каждой матрицы
    for (int row = 0; row <Mprint.rows; row++) {
        for (int col = 0; col < Mprint.columns; col++) {
            printf("%.1lf\t", Mprint.values[row * Mprint.columns+col]);
        }
        printf("\n");
    }
    printf("\n");
}


const Matrix zero = {0,0,NULL};


void cleaning(Matrix* Matrix0) {
    free(Matrix0->values);
}


void error (int n_error){ // Вывод описания ошибки пользователя
    if (n_error == 1) printf("Matrices must be the same size\n");
    if (n_error == 2) printf("Matrix1 column must be the same size as Matrix2 rows\n");
    if (n_error == 3) printf("Matrix must be square\n");
}


Matrix sum (const Matrix M1,const Matrix M2) { // Сумма 2 матриц
    Matrix M0 = Mem(M1.rows, M1.columns);
    if ((M1.rows != M2.rows )||(M1.columns != M2.columns)) {
        error(1);
        return zero;
    }
    else {
        for (int i = 0; i < (M0.rows) * (M0.columns); i++) {
            M0.values[i] = M1.values[i] + M2.values[i];
        }
        return M0;
    }
}


Matrix subtraction (const Matrix M1,const Matrix M2) { // Разница 2 матриц
    Matrix M0 = Mem(M1.rows, M1.columns);
    if ((M1.rows != M2.rows )||(M1.columns != M2.columns)) {
        error(1);
        return zero;
    }
    else {
        for (int i = 0; i < (M0.rows) * (M0.columns); i++) {
            M0.values[i] = M1.values[i] - M2.values[i] ;
        }
        return M0;
    }
}


Matrix multiplication_by_number (const Matrix M1, double x) { // Умножение матрицы 1 на число
    Matrix M0 = Mem(M1.rows, M1.columns);
    for (int i = 0; i < (M0.rows) * (M0.columns); i++) {
        M0.values[i] = M1.values[i] * x ;
    }
    return M0;
}


Matrix multiplication (const Matrix M1,const Matrix M2) { // Умножение матриц A*B
    Matrix M0 = Mem(M1.rows, M2.columns);
    if (M1.columns != M2.rows ) {
        error(1);
        return zero;
    }
    else {
        for (int row = 0; row < M0.rows; row++) {
            for (int col = 0; col < M0.columns; col++) {
                M0.values[row * M0.columns + col] = 0;
                for (int k = 0; k < M1.columns; k++) {
                    M0.values[row * M0.columns + col] += (M1.values[row * M0.columns + k] * M2.values[k * M0.columns + col]);
                }
            }
        }
        return M0;
    }
}


Matrix power (const Matrix M1, const int n) { // Возведение в степень
    if (M1.columns != M1.rows ) {
        error(3);
        return zero;
    }
    else {
        Matrix M0 = Mem(M1.rows, M1.columns);
        M0.values = M1.values;
        for (int count = 1; count < n; count++) {
            M0 = multiplication(M0, M1);
        }
        return M0;
    }
}


int factorial (unsigned int step) {
    if (step == 0) return 1; // факториал нуля = 1
    int f = 1;
    for (int i = 1; i <= step; i++) {
        f *= i ;
    }
    return f ;
}


Matrix single (unsigned int size) { //  Единичная матрица
    Matrix M0 = Mem(size, size);
    for ( int number = 0; number < (size * size); number++) {
        if ( number % (size + 1) == 0 ) {
            M0.values[number] = 1;
        }
        else M0.values[number] = 0;
    }
    return M0;
}


Matrix exponent (const Matrix M1, int time) { // Экспонента матрицы
    if (M1.columns != M1.rows ) {
        error(3);
        return zero;
    }
    else {
        Matrix Ms;
        Matrix M0 = single(M1.rows);
        for (int i = 1; i <= time; i++) {
            Ms = power(M1, i);
            Ms = multiplication_by_number(Ms, 1.0 / (double)factorial(i));
            M0 = sum(M0, Ms);
            cleaning(&Ms);
        }
        return M0;
    }
}


int main() {
    Matrix A,B;

    A=Mem(3,3);
    B=Mem(3,3);

    feeling_matrix(&A);
    feeling_matrix(&B);

    printf("Matrix A =\n");
    print(A);
    printf("Matrix B =\n");
    print(B);

    Matrix summa;
    summa = sum(A,B);
    printf("Matrix A+B =\n");
    print(summa);
    cleaning(&summa);

    Matrix subtractions;
    subtractions = subtraction(A,B);
    printf("Matrix A-B =\n");
    print(subtractions);
    cleaning(&subtractions);

    Matrix xn;
    double multiplier = 2;
    xn = multiplication_by_number(A,multiplier);
    printf("Matrix A * %.2lf =\n",multiplier);
    print(xn);
    cleaning(&xn);

    Matrix AxB;
    AxB = multiplication(A,B);
    printf("Matrix A * B =\n");
    print(multiplication(A,B));
    cleaning(&AxB);

    Matrix Power;
    int n = 3;
    Power = power(A,n);
    printf("Matrix A^n =\n");
    print(Power);
    cleaning(&Power);

    Matrix Single;
    int size = 3;
    Single = single(size);
    printf("Single matrix %d * %d =\n",size,size);
    print(Single);
    cleaning(&Single);

    Matrix Exponent;
    Exponent = exponent(A,3);
    printf("exp(A) =\n");
    print(Exponent);
    cleaning(&Exponent);


    return 0;
}
