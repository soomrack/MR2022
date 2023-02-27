#include "DArrayException.h"


DArrayException::DArrayException(std::string input_message) {
    message = std::move(input_message);
}


std::string DArrayException::get_message() const {
    return message;
}