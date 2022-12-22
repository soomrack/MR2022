#include "Matrix_test.h"
#include "Matrix.h"
#include "Matrix_exception.h"

template <typename T>
void Matrix_test <T>::sum_test() {
    try {
        Matrix<T> A(3,3);
        A.fill_with(2);
        Matrix<T> B(3);
        Matrix<T> C(3, 3);
        T arr_C[] = {3.0, 2.0, 2.0, 2.0, 3.0, 2.0, 2.0, 2.0, 3.0};
        Matrix<T>::Matrix::data_input(&C, arr_C);
        Matrix<T> Sum = A + B;
        Sum.is_equal(C);
    }
    catch(MatrixException& exception){
        exception.print_message("Error",exception);
    }
}

template <typename T>
void Matrix_test <T>::sub_test() {
    try {
        Matrix<T> A(3, 3);
        A.fill_with(2);
        Matrix<T> B(3);
        Matrix<T> C(3, 3);
        T arr_C[] = {1.0, 2.0, 2.0, 2.0, 1.0, 2.0, 2.0, 2.0, 1.0};
        Matrix<T>::data_input(&C, arr_C);
        Matrix<T> Sub = A - B;
        Sub.is_equal(C);
    }
    catch(MatrixException& exception){
        exception.print_message("Error",exception);
    }
}

template <typename T>
void Matrix_test <T>::mult_test() {
    try {
        Matrix<T> A(3, 3);
        A.fill_with(2);
        Matrix<T> B(3, 3);
        B.fill_with(3);
        Matrix<T> C(3, 3);
        C.fill_with(18);
        Matrix<T> Mult = A * B;
        Mult.is_equal(C);
    }
    catch(MatrixException& exception){
        exception.print_message("Error",exception);
    }
}

template <typename T>
void Matrix_test <T>::exp_test() {
    try {
        Matrix<T> A(3, 3);
        A.fill_with(2);
        Matrix<T> real_exp(3, 3);
        T arr_real_exp[] = {129.411, 128.411, 128.411, 128.411, 129.411, 128.411, 128.411, 128.411, 129.411};
        Matrix<T>::data_input(&real_exp, arr_real_exp);
        Matrix<T> exponent = Matrix<T>::exp(A);
        exponent.is_equal(real_exp);
    }
    catch(MatrixException& exception){
        exception.print_message("Error",exception);
    }
}

template <typename T>
void Matrix_test<T>::test() {
    sum_test();
    sub_test();
    mult_test();
    exp_test();
}

template class Matrix_test<double>;
//template class Matrix_test<float>;
