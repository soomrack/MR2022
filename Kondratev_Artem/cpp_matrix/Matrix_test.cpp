//
// Created by user on 08.11.22.
//

#include <iostream>
#include <iomanip>
#include "Matrix.h"
#include "Matrix_exception.h"

#define EPSILON 0.000001

class Matrix_test {
private:
    inline static double array1[] = {2, 8, 1, 3};
    inline static double array2[] = {4, 9, 21, 13};
    inline static double array3[] = {2, 2, 2, 2};
    inline static double power_array[] = {64, 216, 27, 91};
    inline static int power = 3;

public:
    static void calculation_check(double true_array[], Matrix matrix, std::string text);
    static void overload_test();
    static void addition_test();
    static void number_addition_test();
    static void subtraction_test();
    static void multiplication_test();
    static void number_multiplication_test();
    static void determinant_test();
    static void transposition_test();
    static void inversion_test();
    static void inverse_multiplication_test();
    static void number_division_test();
    static void power_test();
    static void exp_test();
};

void Matrix_test::calculation_check(double true_array[], Matrix matrix, std::string text) {
    int error_flag = 0;
    std::cout << text << " test:\n";
    for (int cell = 0; cell < matrix.get_size(0); cell++) {
        int cell_flag = 0;
        if (std::abs(true_array[cell] - matrix.start[cell]) > EPSILON) {
            cell_flag = 1;
            error_flag += 1;
        }
        std::cout << "true: " << std::scientific << std::setw(13) << true_array[cell];
        std::cout << " res: " << std::scientific << std::setw(13) << matrix.start[cell] << " | " << cell_flag << "\n";
    }
    std::cout << "Errors: " << error_flag << "\n";
    std::cout << "\n";
}

void Matrix_test::overload_test() {
    try {
        Matrix matrix1(2, 2, array1);
        Matrix res_matrix = matrix1;
        double eq_true_array[] = {2, 8, 1, 3};
        calculation_check(eq_true_array, res_matrix, "= overload");
    }
    catch(int ex_number) {
        std::cout << Matrix_exception::get_msg() << std::endl;
    }
}

void Matrix_test::addition_test() {
    try {
        Matrix matrix1(2, 2, array1);
        Matrix matrix2(2, 2, array2);
        Matrix res_matrix = matrix1 + matrix2;
        double sum_true_array[] = {6, 17, 22, 16};
        calculation_check(sum_true_array, res_matrix, "addition (matrix)");
    }
    catch(int ex_number) {
        std::cout << Matrix_exception::get_msg() << std::endl;
    }
}

void Matrix_test::number_addition_test() {
    try {
        Matrix matrix1(2, 2, array1);
        Matrix res_matrix = matrix1 + 2;
        double snum_true_array[] = {4, 10, 3, 5};
        calculation_check(snum_true_array, res_matrix, "addition (number)");
    }
    catch(int ex_number) {
        std::cout << Matrix_exception::get_msg() << std::endl;
    }
}

void Matrix_test::subtraction_test() {
    try {
        Matrix matrix1(2, 2, array1);
        Matrix matrix2(2, 2, array2);
        Matrix res_matrix = matrix1 - matrix2;
        double sub_true_array[] = {-2, -1, -20, -10};
        calculation_check(sub_true_array, res_matrix, "subtraction");
    }
    catch(int ex_number) {
        std::cout << Matrix_exception::get_msg() << std::endl;
    }
}

void Matrix_test::multiplication_test() {
    try {
        Matrix matrix1(2, 2, array1);
        Matrix matrix2(2, 2, array2);
        Matrix res_matrix = matrix1 * matrix2;
        double multi_true_array[] = {176, 122, 67, 48};
        calculation_check(multi_true_array, res_matrix, "multiplication (matrix)");
    }
    catch(int ex_number) {
        std::cout << Matrix_exception::get_msg() << std::endl;
    }
}

void Matrix_test::number_multiplication_test() {
    try {
        Matrix matrix1(2, 2, array1);
        Matrix res_matrix = matrix1 * 2;
        double mnum_true_array[] = {4, 16, 2, 6};
        calculation_check(mnum_true_array, res_matrix, "multiplication (number)");
    }
    catch(int ex_number) {
        std::cout << Matrix_exception::get_msg() << std::endl;
    }
}

void Matrix_test::determinant_test() {
    try {
        Matrix matrix1(2, 2, array1);
        double determinant_true_array[] = {-2};
        Matrix det_matrix(1, 1, matrix1.determinant());
        calculation_check(determinant_true_array, det_matrix, "determinant");
    }
    catch(int ex_number) {
        std::cout << Matrix_exception::get_msg() << std::endl;
    }
}

void Matrix_test::transposition_test() {
    try {
        Matrix matrix1(2, 2, array1);
        double transp_true_array[] = {2, 1, 8, 3};
        Matrix res_matrix = matrix1.transposition();
        calculation_check(transp_true_array, res_matrix, "transposition");
    }
    catch(int ex_number) {
        std::cout << Matrix_exception::get_msg() << std::endl;
    }
}

void Matrix_test::inversion_test() {
    try {
        Matrix matrix1(2, 2, array1);
        double inv_true_array[] = {-1.5, 4, 0.5, -1};
        Matrix res_matrix = matrix1.inversion();
        calculation_check(inv_true_array, res_matrix, "inversion");
    }
    catch(int ex_number) {
        std::cout << Matrix_exception::get_msg() << std::endl;
    }
}

void Matrix_test::inverse_multiplication_test() {
    try {
        Matrix matrix1(2, 2, array1);
        Matrix matrix2(2, 2, array2);
        double inv_multi_true_array[] = {1.036496, -0.102189, 0.364963, -0.021897};
        Matrix res_matrix = matrix1 / matrix2;
        calculation_check(inv_multi_true_array, res_matrix, "inverse multiplication");
    }
    catch(int ex_number) {
        std::cout << Matrix_exception::get_msg() << std::endl;
    }
}

void Matrix_test::number_division_test() {
    try {
        Matrix matrix1(2, 2, array1);
        Matrix res_matrix = matrix1 / 2;
        double snum_true_array[] = {1, 4, 0.5, 1.5};
        calculation_check(snum_true_array, res_matrix, "division (number)");
    }
    catch(int ex_number) {
        std::cout << Matrix_exception::get_msg() << std::endl;
    }
}

void Matrix_test::power_test() {
    try {
        Matrix matrix1(2, 2, array1);
        Matrix res_matrix = matrix1.power(power);
        calculation_check(power_array, res_matrix, "power");
    }
    catch(int ex_number) {
        std::cout << Matrix_exception::get_msg() << std::endl;
    }
}

void Matrix_test::exp_test() {
    try {
        Matrix matrix3(2, 2, array3);
        double exp_true_array[] = {27.799075, 26.799075, 26.799075, 27.799075};
        Matrix res_matrix = Matrix::exp(matrix3);
        calculation_check(exp_true_array, res_matrix, "Matrix exp");
    }
    catch(int ex_number) {
        std::cout << Matrix_exception::get_msg() << std::endl;
    }
}
