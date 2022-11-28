
#ifndef UNTITLED_MATRIX_TEST_H
#define UNTITLED_MATRIX_TEST_H

#include "Matrix.h"

class Matrix_test {
    static Matrix size_comparation(const Matrix& A, const Matrix& B);
    virtual Matrix multiply_size_comparation(const Matrix& A, const Matrix& B) = 0;
    static int summ_test();
    static int sub_test();
    static int mult_test();

public:
    static int exp_test();
};


#endif //UNTITLED_MATRIX_TEST_H
