#include "MatrixException.h"


MatrixException::MatrixException(std::string input_message) {
    message = std::move(input_message);
}


std::string MatrixException::getMessage() const {
    return message;
}
