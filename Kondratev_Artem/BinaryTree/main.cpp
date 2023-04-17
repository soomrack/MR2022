#include <iostream>
#include "BinaryTree.h"


typedef struct Matrix {
    int b;
} Matrix;


int main() {

    BinaryTree A;

    Matrix matrix;
    matrix.b = 8;

    Matrix matrix2;
    matrix2.b = 4;

    A.add(4, nullptr);
    A.add(2, nullptr);
    A.add(1, nullptr);
    A.add(3, nullptr);
    A.add(8, nullptr);
    A.add(6, &matrix);
    A.add(5, nullptr);
    A.add(7, &matrix2);
    A.add(16, nullptr);
    A.add(15, nullptr);
    A.add(13, nullptr);
    A.add(14, nullptr);
    A.add(11, nullptr);
    A.add(12, nullptr);
    A.add(22, nullptr);
    A.add(23, nullptr);
    A.add(20, nullptr);
    A.add(21, nullptr);
    A.add(18, nullptr);
    A.add(19, nullptr);
    A.add(17, nullptr);



    auto* new_matrix = static_cast<Matrix*> (A.find(6));
    std::cout << new_matrix->b << std::endl;

    auto* pop_matrix = static_cast<Matrix*> (A.del(7));
    std::cout << pop_matrix->b << std::endl;

    A.del(8);

    return 0;
}
