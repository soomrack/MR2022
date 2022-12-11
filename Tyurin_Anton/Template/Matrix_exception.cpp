#include "Matrix_exception.h"

template<typename T>
 std::string MatrixException <T>::MatrixException::get_message() const {
    return message;
}
template<typename T>
void MatrixException <T>::MatrixException::print_message(const std::string &text, const MatrixException &Exception_object) {
    std::cout << text << ":" << std::endl << Exception_object.get_message() << std::endl << std::endl;
}
