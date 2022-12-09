#include <string>
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <exception>

#ifndef MATRIX_EXCEPTION_H
#define MATRIX_EXCEPTION_H


class MatrixException: public std::domain_error {
private:
    std::string message;
public:
    explicit MatrixException(const char* const msg) : std::domain_error(msg)
    {}
    [[nodiscard]] std::string get_message() const;
    void print_message(const std::string& text, const MatrixException& Exception_object);
};



#endif