//
// Created by user on 08.02.23.
//

#include "Exception.h"


Exception::Exception(std::string input_message) {
    message = std::move(input_message);
}


std::string Exception::getMessage() const {
    return message;
}

