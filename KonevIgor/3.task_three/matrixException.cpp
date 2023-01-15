#include "matrixException.hpp"

Matrix_exception::Matrix_exception(const std::string& message):
  std::logic_error(message)
{}
