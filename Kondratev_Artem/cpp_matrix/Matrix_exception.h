//
// Created by user on 08.11.22.
//

#include <iostream>

#ifndef HELLO_WORLD_MATRIX_EXCEPTION_H
#define HELLO_WORLD_MATRIX_EXCEPTION_H

class Matrix_exception: public std::exception {
private:
    inline static std::string msg;
    inline static int ex_number;
public:
    Matrix_exception() = default;
    ~Matrix_exception() override = default;
    static std::string get_msg() { return msg;};
    static int get_ex_number() {return ex_number;};
    static void positive_parameters(int input_rows, int input_cols);
    static void is_values_null(double **values);
    static void addition_check(int rows1, int cols1, int rows2, int cols2);
    static void is_number_nan(double number);
    static void multiplication_check(int cols1, int rows2);
    static void division_by_zero(double number);
    static void is_matrix_square(int rows, int cols);
};

#endif //HELLO_WORLD_MATRIX_EXCEPTION_H
