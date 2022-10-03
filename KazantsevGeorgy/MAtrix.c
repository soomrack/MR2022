#include <stdio.h>
#include "malloc.h"
#include <string.h>
#include <time.h>

struct Matrix{
    char *name;
    double **mas;
    int rows; //строка (i)
    int cols; //столбец (j)
};

typedef struct Matrix Matr;
Matr First_Matrix, Second_Matrix, Third_Matrix;

void Init_F(Matr *mas1){ //задание кол-ва рядов и стобцов матрицы
    mas1->name = malloc(16);
    mas1->name = "FirstMatrix";
    printf("Enter the number of rows of the %s \n", mas1->name);
    scanf("%d", &mas1->rows);
    printf("Enter the number of cols of the %s \n", mas1->name);
    scanf("%d", &mas1->cols);
    printf("number of rows of the first matrix:%d\n", mas1->rows);
    printf("number of cols of the first matrix:%d", mas1->cols);
}

void Init_S(Matr *mas2){ //задание кол-ва рядов и стобцов матрицы
    mas2->name = malloc(16);
    mas2->name = "SecondMatrix";
    printf("Enter the number of rows of the %s \n", mas2->name);
    scanf("%d", &mas2->rows);
    printf("Enter the number of cols of the %s \n", mas2->name);
    scanf("%d", &mas2->cols);
    printf("number of rows of the %s:%d\n", mas2->name, mas2->rows);
    printf("number of cols of the %s:%d", mas2->name, mas2->cols);
}

void Init_T(Matr *mas3){ //задание кол-ва рядов и стобцов матрицы
    mas3->name = malloc(16);
    mas3->name = "ThirdMatrix";
}

void arinitF(Matr *mas1) { // выделение памяти под первую матрицу
    mas1->mas = (double **) malloc(sizeof(double *) * mas1->rows);
    for (int i = 0; i < mas1->rows; i++) {
        mas1->mas[i] = (double *) malloc(sizeof(double *) * mas1->cols);
    }
}

void arinitS(Matr *mas2) { // выделение памяти под вторую матрицу
    mas2->mas = (double **) malloc(sizeof(double *) * mas2->rows);
    for (int i = 0; i < mas2->rows; i++) {
        mas2->mas[i] = (double *) malloc(sizeof(double *) * mas2->cols);
    }
}

//void arinitT(Matr *mas3) { // выделение памяти под третью матрицу
//    mas3->mas = (int **) malloc(sizeof(int *) * mas3->rows);
//    for (int i = 0; i < mas3->rows; i++) {
//        mas3->mas[i] = (int *) malloc(sizeof(int *) * mas3->cols);
//    }
//}

void MasZap_F(Matr *mas1) { //заполнение первой матрицы значениями
    printf("\n%s", mas1->name);
    for (int i = 0; i < mas1->rows; i++) {
        printf("\n");
        for (int j = 0; j < mas1->cols; j++) {
            mas1->mas[i][j] = 3.00;
            printf("%f ", mas1->mas[i][j]);
        }
    }
    printf("\n");
}

void MasZap_S(Matr *mas2) { //заполнение второй матрицы значениями
    printf("\n%s", mas2->name);
    for (int i = 0; i < mas2->rows; i++) {
        printf("\n");
        for (int j = 0; j < mas2->cols; j++) {
            mas2->mas[i][j] = rand() % 10;
            printf("%f ", mas2->mas[i][j]);
        }
    }
    printf("\n");
}


void Cleaning(Matr *mas3) {
    for(int i = 0; i < mas3->rows; i++) {
        free(mas3->mas[i]);
    }
    free(mas3->mas);
}

void sumofmatrices(Matr *mas1, Matr *mas2, Matr *mas3) {
    if ((mas1->rows == mas2->rows) && (mas1->cols == mas2->cols)) {
        int cols = mas1->cols;
        int rows = mas2->rows;
        mas3->mas = (double **) malloc(sizeof(double *) * rows);
        for (int i = 0; i < rows; i++) {
            mas3->mas[i] = (double *) malloc(sizeof(double *) * cols);
        }
        printf("%s", mas3->name);
        for (int i = 0; i < cols; i++) {
            printf("\n");
            for (int j = 0; j < rows; j++) {
                mas3->mas[i][j] = mas1->mas[i][j] + mas2->mas[i][j];
                printf("%f ", mas3->mas[i][j]);
            }
        }
    }
    else
        printf("Invalid matrix size summation is impossible\n");
}


void subtraction(Matr *mas1, Matr *mas2, Matr *mas3) {
    if ((mas1->rows == mas2->rows) && (mas1->cols == mas2->cols)) {
        int cols = mas1->cols;
        int rows = mas2->rows;
        mas3->mas = (double **) malloc(sizeof(double *) * rows);
        for (int i = 0; i < rows; i++) {
            mas3->mas[i] = (double *) malloc(sizeof(double *) * cols);
        }
        printf("\n%s - %s = %s", mas1->name, mas2->name, mas3->name);
        for (int i = 0; i < cols; i++) {
            printf("\n");
            for (int j = 0; j < rows; j++) {
                mas3->mas[i][j] = mas1->mas[i][j] - mas2->mas[i][j];
                printf("%f ", mas3->mas[i][j]);
            }
        }
    }
    else
        printf("Invalid matrix size. Subtraction is impossible\n");
}

void multiplication(Matr *mas1, Matr *mas2, Matr *mas3){
    if (mas1->cols == mas2->rows) {
        int cols = mas2->cols;
        int rows = mas1->rows;
        //mas1->cols == mas2->rows

        mas3->mas = (double **) malloc(sizeof(double *) * 2);
        for (int i = 0; i < rows; i++) {
            mas3->mas[i] = (double *) malloc(sizeof(double *) * cols);
        }

        printf("multiplication: %s", mas3->name);

        for (int i = 0; i < rows; i++){
            printf("\n");
            for (int j = 0; j < cols; j++) {
                mas3->mas[i][j] = 0.00;
                for (int k = 0; k < mas1->cols; k++) {
                    mas3->mas[i][j] += mas1->mas[i][k] * mas2->mas[k][j];
                    printf("%f ", mas3->mas[i][j]);
                }
            }
        }
    }
    else
        printf("Invalid matrix size. Multiplication is impossible\n");
}

int main() {
    srand(time(NULL));
    Init_F(&First_Matrix);
    arinitF(&First_Matrix);
    MasZap_F(&First_Matrix);

    Init_S(&Second_Matrix);
    arinitS(&Second_Matrix);
    MasZap_S(&Second_Matrix);

    Init_T(&Third_Matrix);
    //sumofmatrices(&First_Matrix, &Second_Matrix, &Third_Matrix);
    //Cleaning(&Third_Matrix);
    //subtraction(&First_Matrix, &Second_Matrix, &Third_Matrix);
    //Cleaning(&Third_Matrix);
    multiplication(&First_Matrix, &Second_Matrix, &Third_Matrix);
}

