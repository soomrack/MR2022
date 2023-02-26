#ifndef MATRIX_EXCEPTION_H
#define MATRIX_EXCEPTION_H

#include <stdexcept>
#include <string>

class Matrix_exception: public std::logic_error
{
public:
  Matrix_exception(const std::string& message);

};

#endif //MATRIX_EXCEPTION_H
