#include "Matrix_exception.h"

std::string Matrix_exception::get_msg() {
    return msg;
}

int Matrix_exception::get_ex_number() {
    return ex_number;
}

void Matrix_exception::positive_parameters(int input_rows, int input_cols) {
    if (input_rows < 0 || input_cols < 0) {
        Matrix_exception::ex_number = 1;
        Matrix_exception::msg = "matrix parameters are less than zero";
        throw get_ex_number();
    }
}

void Matrix_exception::is_memory_null(double **values, double *start) {
    if (nullptr == values || nullptr == start) {
        Matrix_exception::ex_number = 2;
        Matrix_exception::msg = "memory is not allocated";
        delete values;
        delete start;
        throw get_ex_number();
    }
}

void Matrix_exception::addition_check(int rows1, int cols1, int rows2, int cols2) {
    if (rows1 != rows2 || cols1 != cols2) {
        Matrix_exception::ex_number = 4;
        Matrix_exception::msg = "wrong matrix sizes for addition";
        throw get_ex_number();
    }
}

void Matrix_exception::subtraction_check(int rows1, int cols1, int rows2, int cols2) {
    if (rows1 != rows2 || cols1 != cols2) {
        Matrix_exception::ex_number = 5;
        Matrix_exception::msg = "wrong matrix sizes for subtraction";
        throw get_ex_number();
    }
}

void Matrix_exception::is_number_nan(double number) {
    if (std::isnan(number)) {
        Matrix_exception::ex_number = 6;
        Matrix_exception::msg = "number is NAN";
        throw get_ex_number();
    }
}

void Matrix_exception::multiplication_check(int cols1, int rows2) {
    if (cols1 != rows2) {
        Matrix_exception::ex_number = 7;
        Matrix_exception::msg = "wrong matrix sizes for multiplication";
        throw get_ex_number();
    }
}

void Matrix_exception::division_by_zero(double number) {
    if (std::abs(number) < EPSILON) {
        Matrix_exception::ex_number = 8;
        Matrix_exception::msg = "division_by_zero";
        throw get_ex_number();
    }
}

void Matrix_exception::is_matrix_square(int rows, int cols) {
    if (rows != cols) {
        Matrix_exception::ex_number = 9;
        Matrix_exception::msg = "matrix is not square";
        throw get_ex_number();
    }
}
