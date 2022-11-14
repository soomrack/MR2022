#include "MatrixException.h"

std::string MatrixException::get_msg() {
    return msg;
}

int MatrixException::get_ex_number() {
    return ex_number;
}

void MatrixException::positive_parameters(int input_rows, int input_cols) {
    if (input_rows < 0 || input_cols < 0) {
        MatrixException::ex_number = 1;
        MatrixException::msg = "matrix parameters are less than zero";
        throw get_ex_number();
    }
}

void MatrixException::is_memory_null(double **values, double *start) {
    if (nullptr == values || nullptr == start) {
        MatrixException::ex_number = 2;
        MatrixException::msg = "memory is not allocated";
        delete values;
        delete start;
        throw get_ex_number();
    }
}

void MatrixException::addition_check(int rows1, int cols1, int rows2, int cols2) {
    if (rows1 != rows2 || cols1 != cols2) {
        MatrixException::ex_number = 4;
        MatrixException::msg = "wrong matrix sizes for addition";
        throw get_ex_number();
    }
}

void MatrixException::subtraction_check(int rows1, int cols1, int rows2, int cols2) {
    if (rows1 != rows2 || cols1 != cols2) {
        MatrixException::ex_number = 5;
        MatrixException::msg = "wrong matrix sizes for subtraction";
        throw get_ex_number();
    }
}

void MatrixException::is_number_nan(double number) {
    if (std::isnan(number)) {
        MatrixException::ex_number = 6;
        MatrixException::msg = "number is NAN";
        throw get_ex_number();
    }
}

void MatrixException::multiplication_check(int cols1, int rows2) {
    if (cols1 != rows2) {
        MatrixException::ex_number = 7;
        MatrixException::msg = "wrong matrix sizes for multiplication";
        throw get_ex_number();
    }
}

void MatrixException::division_by_zero(double number) {
    if (std::abs(number) < EPSILON) {
        MatrixException::ex_number = 8;
        MatrixException::msg = "division_by_zero";
        throw get_ex_number();
    }
}

void MatrixException::is_matrix_square(int rows, int cols) {
    if (rows != cols) {
        MatrixException::ex_number = 9;
        MatrixException::msg = "matrix is not square";
        throw get_ex_number();
    }
}
