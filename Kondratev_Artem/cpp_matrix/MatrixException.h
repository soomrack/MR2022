//
// Created by user on 08.11.22.
//

#ifndef MATRIXEXCEPTION_H
#define MATRIXEXCEPTION_H


#include <iostream>


class MatrixException: public std::exception {
private:
    std::string message;
    int error_code;
public:
    MatrixException(const std::string &arg, int input_code, std::string input_message);
    ~MatrixException() override = default;

    std::string get_message() const;
    int get_error_code() const;
};


#endif //MATRIXEXCEPTION_H
