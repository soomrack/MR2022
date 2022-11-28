#include "MatrixException.h"

MatrixException::MatrixException(int input_code, std::string input_message) {
    error_code = input_code;
    message = input_message;
}

std::string MatrixException::get_message() const {
    return message;
}
int MatrixException::get_error_code() const {
    return error_code;
}
