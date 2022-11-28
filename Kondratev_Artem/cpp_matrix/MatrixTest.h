//
// Created by user on 08.11.22.
//

#ifndef TEST_H
#define TEST_H


#include <iostream>
#include <iomanip>
#include <vector>
#include "Matrix.h"
#include "EMatrix.h"
#include "MatrixException.h"


class MatrixTest {
private:
    inline static const double EPSILON = 0.000001;
    inline static std::vector<double> vector1 = {2, 8, 1, 3};
    inline static std::vector<double> vector2 = {4, 9, 21, 13};
    inline static std::vector<double> vector3 = {2, 2, 2, 2};
    inline static double power_array[] = {64, 216, 27, 91};
    inline static int power = 3;

public:
    static void using_unused();
    static void calculation_check(double true_array[], Matrix *matrix, const std::string& text);
    static void output_test();
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
    static void counter_test();
};


#endif //TEST_H
