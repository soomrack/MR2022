#include "Matrix_exception.h"


 std::string MatrixException::MatrixException::get_message() const {
    return message;
}


void MatrixException::MatrixException::print_message(const std::string &text, const MatrixException &Exception_object) {
    std::cout << text << ":" << std::endl << Exception_object.get_message() << std::endl << std::endl;
}
