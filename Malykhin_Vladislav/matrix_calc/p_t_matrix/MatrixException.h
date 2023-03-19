#ifndef MR2022_MATRIXEXCEPTION_H
#define MR2022_MATRIXEXCEPTION_H

#include <iostream>


class MatrixException: public std::exception {
private:
    std::string message;
public:
    explicit MatrixException(std::string input_message);
    MatrixException(const MatrixException &other) = default;
    MatrixException(MatrixException &&other) = default;
    ~MatrixException() override = default;

    std::string get_message() const;
};
#endif //MR2022_MATRIXEXCEPTION_H
