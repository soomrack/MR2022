//
// Created by user on 08.11.22.
//

#ifndef HELLO_WORLD_TEST_H
#define HELLO_WORLD_TEST_H

#include <iostream>
#include <iomanip>
#include "Matrix.h"
#include "MatrixException.h"

class MatrixTest {
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
    static void user_test();
    static void memory_leak_test();
};

#endif //HELLO_WORLD_TEST_H
