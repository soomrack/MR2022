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
    Matrix C(3,3);
    double arr_C[] = {3.0, 2.0, 2.0, 2.0, 3.0, 2.0, 2.0, 2.0, 3.0};
    Matrix::data_input(&C,arr_C);
    Matrix Sum = A + B;
    if (Sum.is_equal(C)){
        return 1;
    }
    return 0;
}

int Matrix_test::sub_test() {
    Matrix A(3,3);
    A.fill_with(2);
    Matrix B(3);
    Matrix C(3,3);
    double arr_C[] = {1.0, 2.0, 2.0, 2.0, 1.0, 2.0, 2.0, 2.0, 1.0};
    Matrix::data_input(&C,arr_C);
    Matrix Sub = A - B;
    if (Sub.is_equal(C)){
        return 1;
    }
    return 0;
}

int Matrix_test::mult_test() {
    Matrix A(3,3);
    A.fill_with(2);
    Matrix B(3,3);
    B.fill_with(3);
    Matrix C(3,3);
    C.fill_with(18);
    Matrix Mult = A * B;
    if (Mult.is_equal(C)){
        return 1;
    }
    return 0;
}

int Matrix_test::exp_test() {
    Matrix A(3,3);
    A.fill_with(2);
    Matrix real_exp(3,3);
    double arr_real_exp[] = {129.411, 128.411, 128.411, 128.411, 129.411, 128.411, 128.411, 128.411, 129.411};
    Matrix exponent = Matrix::exp(A);
    if (exponent.is_equal(real_exp)){
        return 1;
    }
    return 0;
}


