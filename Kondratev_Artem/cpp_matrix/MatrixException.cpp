#include "MatrixException.h"
#include "../../Tyurin_Anton/CPP/Matrix_exception.h"

#include <utility>


MatrixException::MatrixException(const std::string &arg, int input_code, std::string input_message) {
    error_code = input_code;
    message = std::move(input_message);
}


std::string MatrixException::get_message() const {
    return message;
}


int MatrixException::get_error_code() const {
    return error_code;
}

MatrixException MatrixException::WRONG_SIZES() {
    return MatrixException(__cxx11::basic_string(), 0, __cxx11::basic_string());
}
