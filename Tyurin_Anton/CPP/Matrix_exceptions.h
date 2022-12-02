#include <exception>
#include <string>

#ifndef MATRIX_EXСEPTIONS_H

#define MATRIX_EXСEPTIONS_H

class MatrixException: public std::exception {
private:
    std::string message;
    int error_code;
public:
    MatrixException(int input_code, std::string input_message);
    ~MatrixException() override = default;

    std::string get_message() const;
    int get_error_code() const;
};
#endif