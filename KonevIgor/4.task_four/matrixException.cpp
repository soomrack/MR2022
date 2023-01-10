#include "matrixException.h"

Matrix_exception::Matrix_exception(const std::string& message):
  std::logic_error(message)
{}
