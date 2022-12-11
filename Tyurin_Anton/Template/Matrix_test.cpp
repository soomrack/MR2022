#include "Matrix_test.h"
#include "Matrix.h"
#include "Matrix_exception.h"

template <typename T>
void Matrix_test <T>::Matrix_test::summ_test() {
    try {
        T A(3,3);
        A.fill_with(2);
        T B(3);
        T C(3, 3);
        double arr_C[] = {3.0, 2.0, 2.0, 2.0, 3.0, 2.0, 2.0, 2.0, 3.0};
        Matrix<T>::Matrix::data_input(&C, arr_C);
        T Sum = A + B;
        Sum.is_equal(C);
    }
    catch(T& exception){
        exception.print_message("Error",exception);
    }
}

template <typename T>
void Matrix_test <T>::Matrix_test::sub_test() {
    try {
        T A(3, 3);
        A.fill_with(2);
        T B(3);
        T C(3, 3);
        double arr_C[] = {1.0, 2.0, 2.0, 2.0, 1.0, 2.0, 2.0, 2.0, 1.0};
        Matrix<T>::data_input(&C, arr_C);
        T Sub = A - B;
        Sub.is_equal(C);
    }
    catch(T& exception){
        exception.print_message("Error",exception);
    }
}

template <typename T>
void Matrix_test <T>::Matrix_test::mult_test() {
    try {
        T A(3, 3);
        A.fill_with(2);
        T B(3, 3);
        B.fill_with(3);
        T C(3, 3);
        C.fill_with(18);
        T Mult = A * B;
        Mult.is_equal(C);
    }
    catch(T& exception){
        exception.print_message("Error",exception);
    }
}

template <typename T>
void Matrix_test <T>::Matrix_test::exp_test() {
    try {
        T A(3, 3);
        A.fill_with(2);
        T real_exp(3, 3);
        double arr_real_exp[] = {129.411, 128.411, 128.411, 128.411, 129.411, 128.411, 128.411, 128.411, 129.411};
        T::data_input(&real_exp, arr_real_exp);
        T exponent = Matrix<T>::exp(A);
        exponent.is_equal(real_exp);
    }
    catch(T& exception){
        exception.print_message("Error",exception);
    }
}

template <typename T>
void Matrix_test <T>::Matrix_test::test(){
    summ_test();
    sub_test();
    mult_test();
    exp_test();
}