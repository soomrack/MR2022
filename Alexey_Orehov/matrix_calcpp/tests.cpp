//
// Created by user on 24.10.2022.
//
#include "Matrix.h"

int main(){
    double val[9] = {1, 2, 3,
                     4, 5, 6,
                     7, 8, 9};
    double val1[9] = {3, 2, 1,
                      3, 2, 1,
                      3, 2, 1};
//    Matrix mat1 = Matrix(3, 3).fill_from_array(val);
//    Matrix mat2 = Matrix(3, 3).fill_from_array(val1);
    Matrix mat1 = Matrix(3, 3).fill_random(-5, 5);
    Matrix mat2 = Matrix(3, 3).fill_random(-5, 5);
    printm(mat2 + mat1);
}