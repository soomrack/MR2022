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
            rand_matrix->values[i] =(double) i+1;
    }
}


void print (Matrix Mprint) { // Вывод каждой матрицы
    printf("\n");
    for (int row = 0; row <Mprint.rows; row++) {
        for (int col = 0; col < Mprint.columns; col++) {
            printf("%.0lf ", Mprint.values[row * Mprint.columns+col]);
        }
        printf("\n");
    }
}


void cleaning(Matrix* Matr) {
    free(Matr->values);
}


Matrix sum (const Matrix M1,const Matrix M2) { // Сумма 2 матриц
    Matrix M0 = Mem(M1.rows, M1.columns);
    if ((M1.rows != M2.rows )||(M1.columns != M2.columns)) {
        printf("\nAddition is impossible");
        M0.rows = 0;
        M0.columns = 0;
    }
    else {
        for (int i = 0; i < (M0.rows) * (M0.columns); i++) {
            M0.values[i] = M1.values[i] + M2.values[i];
        }
        printf("\nMatrix A+B =");
    }
    return M0;
}


Matrix unsum (const Matrix M1,const Matrix M2) { // Разница 2 матриц
    Matrix M0 = Mem(M1.rows, M1.columns);
    if ((M1.rows != M2.rows )||(M1.columns != M2.columns)) {
        printf("\nSubtraction is impossible");
        M0.rows = 0;
        M0.columns = 0;
    }
    else {
        for (int i = 0; i < (M0.rows) * (M0.columns); i++) {
            M0.values[i] = M1.values[i] - M2.values[i] ;
        }
        printf("\nMatrix A-B =");
    }
    return M0;
}


Matrix multiplication_by_number (const Matrix M1, double x) { // Умножение матрицы 1 на число
    Matrix M0 = Mem(M1.rows, M1.columns);
    for (int i = 0; i < (M0.rows) * (M0.columns); i++) {
        M0.values[i] = M1.values[i] * x ;
    }
    printf("\nMatrix A*%.1lf =",x);
    return M0;
}


Matrix multiplication (const Matrix M1,const Matrix M2) { // Умножение матриц A*B
    Matrix M0 = Mem(M1.rows, M2.columns);
    if (M1.columns != M2.rows ) {
        printf("\nMultiplication is impossible");
        cleaning(&M0);
    }
    else {
        for (int row = 0; row <M0.rows; row++) {
            for (int col = 0; col < M0.columns; col++) {
                M0.values[row * M0.columns+col] = 0;
                for (int k = 0; k < M1.columns; k++) {
                    M0.values[row * M0.columns+col] += (M1.values[row * M0.columns+k] * M2.values[k * M0.columns+col]);
                }
            }
        }
    }
    return M0;
}


Matrix power (const Matrix M1, const int n) { // Возведение в степень
    Matrix Mwork = Mem(M1.rows, M1.columns);
    Matrix M0 = Mem(M1.rows, M1.columns);
    Mwork=M1;
    for (int count = 1; count < n; count++) {
        Mwork= multiplication(Mwork,M1);
    }
    return Mwork;
}


int factorial (int step) {
    if (step == 0) return 1;
    if (step == 1) return 1;
    return step * factorial ( step - 1);
}


Matrix exponent (const Matrix M1, int time) { // Экспонента матрицы
    Matrix Ms = Mem(M1.rows, M1.columns);
    Matrix M0 = Mem(M1.rows, M1.columns);
    M0 = M1;
    Ms = M1;
    for (int i = 2; i <= time; i++) {
        Ms = power (M1 , i);

        for (int row = 0; row <M1.rows; row++) {
            for (int col = 0; col < M1.columns; col++) {
                M0.values[row * M0.columns+col] += ( Ms.values[row * M0.columns+col]/
                        (double)factorial(i));
            }
        }

        print(Ms);
    }
    printf("\nMatrix exp(A) =");
    return M0;
}


int main() {
    Matrix A,B;

    A=Mem(3,3);
    B=Mem(3,3);

    feeling_matrix(&A);
    feeling_matrix(&B);

    printf("Matrix A =");
    print(A);
    printf("\nMatrix B =");
    print(B);

    Matrix summa;
    summa=sum(A,B);
    print(summa);
    cleaning(&summa);

    Matrix unsumma;
    unsumma=unsum(A,B);
    print(unsumma);
    cleaning(&unsumma);

    Matrix xn;
    int multiplier=2;
    xn=multiplication_by_number(A,multiplier);
    print(xn);
    cleaning(&xn);

    Matrix AxB;
    AxB=multiplication(A,B);
    printf("\nMatrix A*B =");
    print(AxB);
    cleaning(&AxB);

    Matrix Power;
    int n=3;
    Power=power(A,n);
    printf("\nMatrix A^n =");
    print(Power);
    cleaning(&Power);

    Matrix Exponent;
    Exponent=exponent(A,3);
    print(Exponent);
    cleaning(&Exponent);



    return 0;
}
