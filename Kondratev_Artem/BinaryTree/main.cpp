#include <iostream>
#include "BinaryTree.h"


typedef struct Matrix {
    char a;
    int b;
} Matrix;


int main() {

    BinaryTree A;

    Matrix matrix;
    matrix.a = 5;
    matrix.b = 8;

    Matrix matrix2;
    matrix2.a = 5;
    matrix2.b = -5;

    A.append(4, nullptr);
    A.append(5, nullptr);
    A.append(7, &matrix2);
    A.append(2, nullptr);
    A.append(1, nullptr);
    A.append(3, nullptr);
    A.append(6, &matrix);
    A.append(8,  nullptr);

    auto* new_matrix = static_cast<Matrix*> (A.find(6));
    std::cout << new_matrix->b << std::endl;

    auto* pop_matrix = static_cast<Matrix*> (A.pop(7));
    std::cout << pop_matrix->b << std::endl;

    std::cout << "height: " << A.get_height() << std::endl;

    return 0;
}