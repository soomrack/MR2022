#include <string>
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <exception>

#ifndef MATRIX_EXCEPTION_H
#define MATRIX_EXCEPTION_H

template <typename T>
class MatrixException: public std::domain_error {
private:
    T message;
public:
    explicit MatrixException(const T) : std::domain_error(message)
    {}
    [[nodiscard]] std::string get_message() const;
    void print_message(const std::string& text, const MatrixException& Exception_object);
};

#endif