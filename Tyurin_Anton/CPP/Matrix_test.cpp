#include "Matrix_test.h"
#include "Matrix.h"

Matrix Matrix_test::size_comparation(const Matrix& A, const Matrix& B) {
    if (!((A.rows == B.rows) && (A.cols == B.cols))) {
        Matrix::error();
    }
}

Matrix Matrix_test::multiply_size_comparation(const Matrix& A, const Matrix& B) {
    if (A.cols != B.rows) {
        Matrix::error();
    }
}

int Matrix_test::summ_test() {
    Matrix A(3,3);
    A.fill_with(2);
    Matrix B(3);
    Matrix Sum = A + B;
    if (Sum.is_equal(C)){

    }
    return 0;
}

int Matrix_test::sub_test() {
    return 0;
}

int Matrix_test::mult_test() {
    return 0;
}

int Matrix_test::exp_test() {
    return 0;
}


