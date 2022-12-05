#include <exception>
#include <string>
#include <cstdlib>

#ifndef MATRIX_EXCEPTION_H
#define MATRIX_EXCEPTION_H

class MatrixException: public domain_error {
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