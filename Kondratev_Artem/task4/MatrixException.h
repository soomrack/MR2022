//
// Created by user on 08.11.22.
//

#ifndef MATRIXEXCEPTION_H
#define MATRIXEXCEPTION_H


#include <iostream>


class MatrixException: public std::exception {
private:
    std::string message;
public:
    explicit MatrixException(std::string input_message);
    MatrixException(const MatrixException &other) = default;
    MatrixException(MatrixException &&other) = default;
    ~MatrixException() override = default;

    std::string getMessage() const;
};


#endif //MATRIXEXCEPTION_H
