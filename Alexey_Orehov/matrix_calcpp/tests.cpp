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

    Matrix mat1 = Matrix(3, 3).fill_from_array(val);
    Matrix mat2 = Matrix(3, 3).fill_from_array(val1);
    mat1.print();
    mat2.print();
    mat2.set(1, 1, 10);
    mat2.print();
    // Matrix mat2 = Matrix(3, 3);

    //    Matrix mat2 = Matrix(3, 3).fill_identity();
//    mat2.print();
    return 0;
}