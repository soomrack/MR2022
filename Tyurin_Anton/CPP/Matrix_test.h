
#ifndef UNTITLED_MATRIX_TEST_H
#define UNTITLED_MATRIX_TEST_H

#include "Matrix.h"

class Matrix_test {
    static Matrix size_comparation(const Matrix& A, const Matrix& B);
    virtual Matrix multiply_size_comparation(const Matrix& A, const Matrix& B) = 0;
    int summ_test();
    int sub_test();
    int mult_test();
    int exp_test();
};


#endif //UNTITLED_MATRIX_TEST_H
