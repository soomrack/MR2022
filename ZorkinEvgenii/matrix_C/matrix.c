#include <stdio.h>
#include "matrix.h"

int main () {

//    double data[9] = {23,2,4,5,6,74,5,9,8};
//    Matrix mat = {3,3,data};
//    printm(s_mul(mat,8));
//    printf("%d\n", data); // адрес первого элемента массива который выделяет ОС в оперативной памяти
//    printf("%f\n", *data); // первая ячейка матрицы (ее данные)
//    printf("%f\n", data[3]); // возвращает 3 элемент матрицы/массива

    double data1[4] = {1,2,3,4};
    double data2[4] = {5,6,7,8};
    double data3[5] = {5,6,7,8,9};

    Matrix mat1 = {2,2,data1};
    Matrix mat2 = {2,2,data2};
    Matrix mat3 = {2,3,data3};

    printm(add(mat1,mat2));
    printm(add(mat1,mat3));


    return 0;
}