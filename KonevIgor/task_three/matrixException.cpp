#include "matrixException.hpp"

MatrixException::MatrixException(const std::string& message):
  std::logic_error(message)
{}
