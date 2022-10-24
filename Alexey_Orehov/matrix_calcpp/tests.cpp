//
// Created by user on 24.10.2022.
//
#include "Matrix.h"

int main(){
    double val[9] = {1, 2, 3,
                     4, 5, 6,
                     7, 8, 9};
    Matrix mat = Matrix(3, 3).from_array(val);
    printm(mat);
    std::cout << mat[1][1] << std::endl;
}