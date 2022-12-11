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
    MatrixException(int input_code, std::string input_message);
    ~MatrixException() override = default;

    std::string getMessage() const;
    int getErrorCode() const;
};


#endif //MATRIXEXCEPTION_H
