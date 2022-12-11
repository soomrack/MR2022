#include "Matrix_test.h"
#include "Matrix.h"
#include "Matrix_exception.h"


void Matrix_test::summ_test() {
    try {
        Matrix A(3, 3);
        A.fill_with(2);
        Matrix B(3);
        Matrix C(3, 3);
        double arr_C[] = {3.0, 2.0, 2.0, 2.0, 3.0, 2.0, 2.0, 2.0, 3.0};
        Matrix::data_input(&C, arr_C);
        Matrix Sum = A + B;
        Sum.is_equal(C);
    }
    catch(MatrixException& exception){
        exception.print_message("Error",exception);
    }
}

void Matrix_test::sub_test() {
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

void Matrix_test::mult_test() {
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

void Matrix_test::exp_test() {
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
/*
void Matrix_test::expertise(int sum,int sub,int mult,int exp){
    if (sum == 0) {
        std::cout << "Summ is incorrect" << std::endl;
    }
    if (sub == 0) {
        std::cout << "Substruction is incorrect" << std::endl;
    }
    if (mult == 0) {
        std::cout << "Multiplication is incorrect" << std::endl;
    }
    if (exp == 0) {
        std::cout << "Exponent is incorrect" << std::endl;
    }
}
*/
void Matrix_test::test(){
    summ_test();
    sub_test();
    mult_test();
    exp_test();
/*    switch (sum + sub + mult + exp) {
        case 3:
            expertise(sum,sub,mult,exp);
        case 2:
            expertise(sum,sub,mult,exp);
        case 1:
            expertise(sum,sub,mult,exp);
        default:
            std::cout << "Functions work correctly" << std::endl;
    }*/
}