#include <string>
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <exception>

#ifndef MATRIX_EXCEPTION_H
#define MATRIX_EXCEPTION_H

class MatrixException: public std::domain_error {
private:
    std::string message;
    int error_code;
public:
    MatrixException(int input_code, std::string input_message);
//    ~MatrixException() override = default;

    std::string get_message() const;
    int get_error_code() const;
};
#endif