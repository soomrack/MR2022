#include <stdio.h>
#include "matrix.h"

int main () {

    double data1[4] = {1,2,3,4};        // выделение массива на 4 элемента и его заполнение
    double data2[4] = {5,6,7,8};        // выделение массива на 4 элемента и его заполнение
    double data3[5] = {5,6,7,8,9};  // выделение массива на 5 элементов и его заполнение

    Matrix mat1 = {2,2,data1};        // создание матрицы с использованием массива
    Matrix mat2 = {2,2,data2};
    Matrix mat3 = {2,3,data3};

    printf("Primer 0 - matrix 1 = ");
    printm(mat1);
    printf("\n");

    printf("Primer 1 -\n");
    printm(add(mat1,mat2));                  // вывод матрицы результатом сложения

    printf("\n");
    printf("1st numb adress massive %d\n", data1);  // адрес первого элемента массива который выделяет ОС в оперативной памяти
    printf("1st elem matrix %f\n", *data1);         // первая ячейка матрицы (ее данные)
    printf("4 elem matrix %f\n", data1[3]);         // возвращает 3 элемент матрицы/массива

    printf("Primer 2 -\n");
    printm(add(copy(mat1),mat3));        // вывод матрицы рез сложения НО тут не совпадает размерность 4 на 5 и вывода нет

    printf("Primer 3 -\n");
    Matrix mat4 = create_zero(2,2);              // создание нулевой матрицы по функции create_zero
    printm(mat4);                                      // вывод нулевой матрицы

    printf("Primer 4 -\n");
    printm(s_mul(mat1,2));                   // умножение матрицы на скаляр
    printf("\n");

    printf("Primer 5 -\n");
    printm(s_div(mat1,2));                   // деление матрицы на скаляр
    printf("\n");
    return 0;
}