#include <string>
#include <iostream>
#include <cstdlib>
#include <exception>

#ifndef MATRIX_EXCEPTION_H
#define MATRIX_EXCEPTION_H


class MatrixException: public std::domain_error {
private:
    std::string message;
public:
    explicit MatrixException(const std::string&) : std::domain_error(message)
    {}
    [[nodiscard]] std::string get_message() const;
    void print_message(const std::string& text, const MatrixException& Exception_object);
};

#endif