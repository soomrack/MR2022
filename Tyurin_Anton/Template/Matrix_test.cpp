#include "Matrix_test.h"
#include "Matrix.h"
#include "Matrix_exception.h"

template <typename T1, typename T2, typename T3>
void Matrix_test <T2>::Matrix_test <T2>::summ_test() {
    try {
        T1 A(3,3);
        A.fill_with(2);
        T1 B(3);
        T1 C(3, 3);
        double arr_C[] = {3.0, 2.0, 2.0, 2.0, 3.0, 2.0, 2.0, 2.0, 3.0};
        Matrix<T1>::Matrix::data_input(&C, arr_C);
        T1 Sum = A + B;
        Sum.is_equal(C);
    }
    catch(T3& exception){
        exception.print_message("Error",exception);
    }
}

template <typename T2>
void Matrix_test <T2>::Matrix_test::sub_test() {
    try {
        Matrix A(3, 3);
        A.fill_with(2);
        Matrix B(3);
        Matrix C(3, 3);
        double arr_C[] = {1.0, 2.0, 2.0, 2.0, 1.0, 2.0, 2.0, 2.0, 1.0};
        Matrix::data_input(&C, arr_C);
        Matrix Sub = A - B;
        Sub.is_equal(C);
    }
    catch(MatrixException& exception){
        exception.print_message("Error",exception);
    }
}

template <typename T2>
void Matrix_test <T2>::Matrix_test::mult_test() {
    try {
        Matrix A(3, 3);
        A.fill_with(2);
        Matrix B(3, 3);
        B.fill_with(3);
        Matrix C(3, 3);
        C.fill_with(18);
        Matrix Mult = A * B;
        Mult.is_equal(C);
    }
    catch(MatrixException& exception){
        exception.print_message("Error",exception);
    }
}

template <typename T2>
void Matrix_test <T2>::Matrix_test::exp_test() {
    try {
        Matrix A(3, 3);
        A.fill_with(2);
        Matrix real_exp(3, 3);
        double arr_real_exp[] = {129.411, 128.411, 128.411, 128.411, 129.411, 128.411, 128.411, 128.411, 129.411};
        Matrix::data_input(&real_exp, arr_real_exp);
        Matrix exponent = Matrix::exp(A);
        exponent.is_equal(real_exp);
    }
    catch(MatrixException& exception){
        exception.print_message("Error",exception);
    }
}

template <typename T2>
void Matrix_test <T2>::Matrix_test::test(){
    summ_test();
    sub_test();
    mult_test();
    exp_test();
}