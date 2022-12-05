#include "Matrix_exception.h"

/*
MatrixException::MatrixException(const char* const msg){
    message = std::move(msg);
}
*/
std::string MatrixException::get_message() const {
    return message;
}

void MatrixException::print_message(const std::string &text, const MatrixException &Exception_object) {
    std::cout << text << ":" << std::endl << Exception_object.get_message() << std::endl << std::endl;
}
