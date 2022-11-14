//
// Created by user on 08.11.22.
//

#ifndef HELLO_WORLD_MATRIXEXCEPTION_H
#define HELLO_WORLD_MATRIXEXCEPTION_H

#include <iostream>
#include <cmath>

class MatrixException: public std::exception {
    friend class MatrixTest;
private:
    inline static const double EPSILON = 0.000001;
    inline static std::string msg;
    inline static int ex_number;
public:
    MatrixException() = default;
    ~MatrixException() override = default;

    static std::string get_msg();
    static int get_ex_number();
    static void positive_parameters(int input_rows, int input_cols);
    static void is_memory_null(double **values, double *start);
    static void addition_check(int rows1, int cols1, int rows2, int cols2);
    static void subtraction_check(int rows1, int cols1, int rows2, int cols2);
    static void is_number_nan(double number);
    static void multiplication_check(int cols1, int rows2);
    static void division_by_zero(double number);
    static void is_matrix_square(int rows, int cols);
};

#endif //HELLO_WORLD_MATRIXEXCEPTION_H
