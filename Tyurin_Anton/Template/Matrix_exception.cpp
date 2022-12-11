#include "Matrix_exception.h"

template<typename T3>
 std::string MatrixException <T3>::MatrixException::get_message() const {
    return message;
}
template<typename T3>
void MatrixException <T3>::MatrixException::print_message(const std::string &text, const MatrixException &Exception_object) {
    std::cout << text << ":" << std::endl << Exception_object.get_message() << std::endl << std::endl;
}
