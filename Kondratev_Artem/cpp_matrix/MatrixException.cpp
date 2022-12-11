#include "MatrixException.h"


MatrixException::MatrixException(int input_code, std::string input_message) {
    error_code = input_code;
    message = std::move(input_message);
}


std::string MatrixException::getMessage() const {
    return message;
}


int MatrixException::getErrorCode() const {
    return error_code;
}
