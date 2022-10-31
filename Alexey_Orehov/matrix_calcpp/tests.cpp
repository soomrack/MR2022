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

    double data1[6] = {1, 2, 3,
                       4, 5, 6};
    double data2[9] = {8, -1, 1,
                       -2, 2, 4,
                       7, 3, 0};
    double ans_data[6] = {25, 12, 9,
                          64, 24, 24};

    Matrix mat1 = Matrix(2, 3).fill_from_array(data1);
    Matrix mat2 = Matrix(3, 3).fill_from_array(data2);
    Matrix mat3 = Matrix(2, 3).fill_from_array(ans_data);



    // Matrix mat2 = Matrix(3, 3);

    //    Matrix mat2 = Matrix(3, 3).fill_identity();
//    mat2.print();
    return 0;
}