
#ifndef UNTITLED_MATRIX_TEST_H
#define UNTITLED_MATRIX_TEST_H

#include "Matrix.h"
#include "Matrix_exception.h"

MatrixException SIZE_ERROR(1,"Размеры матрицы некорректны");
MatrixException WRONG_SIZES(2,"Размеры некорректны для вычисления");
MatrixException MEMORY_DIDNOT_ALLOCATED(3,"Память не выделилась");


class Matrix_test {
public:
    static Matrix size_comparation(const Matrix& A, const Matrix& B);
    virtual Matrix multiply_size_comparation(const Matrix& A, const Matrix& B) = 0;
    static int summ_test();
    static int sub_test();
    static int mult_test();
    static int exp_test();
    static void test();
    static void expertise(int sum,int sub,int mult,int exp);
};


#endif //UNTITLED_MATRIX_TEST_H
