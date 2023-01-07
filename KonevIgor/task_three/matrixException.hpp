#ifndef MATRIX_EXCEPTION_H
#define MATRIX_EXCEPTION_H

#include <stdexcept>
#include <string>

class MatrixException: public std::logic_error
{
public:
  MatrixException(const std::string& message);

};

#endif //MATRIX_EXCEPTION_H
