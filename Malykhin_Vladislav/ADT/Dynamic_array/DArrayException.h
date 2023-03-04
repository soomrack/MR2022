#ifndef P_T_MATRIX_DARRAYEXCEPTION_H
#define P_T_MATRIX_DARRAYEXCEPTION_H

#include <iostream>

class DArrayException : public std::exception {
private:
    std::string message;
public:
    explicit DArrayException(std::string input_message);
    DArrayException(const DArrayException &other) = default;
    DArrayException(DArrayException &&other) = default;
    ~DArrayException() override = default;

    std::string get_message() const;

};


#endif //P_T_MATRIX_DARRAYEXCEPTION_H
