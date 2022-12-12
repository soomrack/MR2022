//
// Created by User on 05.12.2022.
//

#include "MatrixException.h"


MatrixException::MatrixException(std::string input_message) {
    message = std::move(input_message);
}


std::string MatrixException::get_message() const {
    return message;
}