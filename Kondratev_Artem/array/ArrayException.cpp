//
// Created by user on 08.02.23.
//

#include "ArrayException.h"


ArrayException::ArrayException(std::string input_message) {
    message = std::move(input_message);
}


std::string ArrayException::getMessage() const {
    return message;
}

