#include "matrix.h"
#include <iostream>

void print_matrix(const Matrix &matrix){
    for (int item = 0; item < (matrix.get_row() * matrix.get_col()); item++){
        if ((item != 0) && ((item % matrix.get_col()) == 0)) {
            std::cout << std::endl;
        }
        std::cout << matrix.array[item] << " ";
    }
    std::cout << "\n" << std::endl;
}

int main(){
    double test3x3[3][3] = {1, 2, 3,
                            4, 5, 6,
                            7, 8, 1};

    double test3x2[3][2] = {-5, 2,
                            4, 0,
                            9, 1};
    double test4x4[4][4] = {1, 2, 2, 3,
                            5, 8, 13, 21,
                            34, 55, 89, 144,
                            89, 55, 34, 21};
    double test5x1[5][1] = {-1, 2, -3, 4, -5};
    double test1x1[1][1] = {5};
    double test2x2[2][2] = {2, 4,
                            6, 8};

    Matrix result;
    Matrix matrix1(3, 4, *test3x3);
    Matrix matrix2(4, 4, *test4x4);
    try {
        result.exponential_matrix(matrix1);
        print_matrix(result);
    } catch (Matrix_exception& exception) {
        exception.what();
    }
}
