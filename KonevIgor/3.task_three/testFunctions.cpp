#include "matrix.hpp"
#include "matrixException.hpp"
#include <cstring>

const double EPS = 0.0001;

bool is_triangle(const Matrix& matrix) {
  if (matrix.get_rows_count() != matrix.get_cols_count()) {
    return false;
  }
  for (size_t i = 1; i <= matrix.get_rows_count(); i++) {
    for (size_t j = i; j <= matrix.get_cols_count(); j++) {
      if (std::abs(matrix[i][j]) < EPS) {
        return false;
      }
    }
  }

  for (size_t i = 1; i <= matrix.get_rows_count(); i++) {
    for (size_t j = 1; j < i; j++) {
      if (std::abs(matrix[i][j]) > EPS) {
        return false;
      }
    }
  }
  return true;
}

bool test_add() {
  double values_first[12] = {1, 2, 3, 4,
                             5, 6, 7, 8,
                             9, 10, 11, 12};

  double values_second[12] = {5, 9, 3, 4,
                              51, 48, 13, 0,
                              -2, 1, 111, 42};

  double values_result[12] = {6, 11, 6, 8,
                              56, 54, 20, 8,
                              7, 11, 122, 54};

  Matrix first_matrix = Matrix(3, 4, values_first);
  Matrix second_matrix = Matrix(3, 4, values_second);
  Matrix result_matrix = Matrix(3, 4, values_result);
  if (result_matrix == first_matrix + second_matrix) {
    return true;
  }
  return false;
}


bool test_subtract() {
  double values_first[12] = {1, 2, 3, 4,
                             5, 6, 7, 8,
                             9, 10, 11, 12};

  double values_second[12] = {12, 11, 121, 0,
                              -48, 3, 13, 5,
                              -1, 15, 111, 42};

  double values_result[12] = {-11, -9, -118, 4,
                              53, 3, -6, 3,
                              10, -5, -100, -30};

  Matrix first_matrix = Matrix(3, 4, values_first);
  Matrix second_matrix = Matrix(3, 4, values_second);
  Matrix result_matrix = Matrix(3, 4, values_result);
  if (result_matrix == first_matrix - second_matrix) {
    return true;
  }
  return false;
}

bool test_multiply() {
  double values_first[12] = {1, 2, 3, 4,
                             5, 6, 7, 8,
                             9, 10, 11, 12};

  double values_second[8] = {0, 10,
                             -4, 3,
                             46, 15,
                             1, 29};

  double values_result[6] = {134, 177,
                             306, 405,
                             478, 633};

  Matrix first_matrix = Matrix(3, 4, values_first);
  Matrix second_matrix = Matrix(4, 2, values_second);
  Matrix result_matrix = Matrix(3, 2, values_result);
  if (result_matrix == first_matrix * second_matrix) {
    return true;
  }
  return false;
}

bool test_divide_by_scalar() {
  double values_first[4] = {1, -100,
                            0, 200};

  double value_second = 5.0;

  double values_result[6] = {0.2, -20,
                             0, 40};
  Matrix first_matrix = Matrix(2, 2, values_first);
  Matrix result_matrix = Matrix(2, 2, values_result);
  if (result_matrix == first_matrix / value_second) {
    return true;
  }
  return false;
}

bool test_triangle_matrix() {
  double values[9] = {17, 24, 3,
                      51, -5, 7,
                      9, 10, 11};
  Matrix matrix = Matrix(3, 3, values);
  Matrix result_matrix;
    matrix.get_triangle_matrix(result_matrix);
  if (is_triangle(result_matrix)) {
    return true;
  }
  return false;
}

bool test_transposed() {
  double values[6] = {1, 2, 3,
                      4, 5, 6};

  double values_result[6] = {1, 4,
                             2, 5,
                             3, 6};
  Matrix matrix = Matrix(2, 3, values);
  Matrix resultMatrix = Matrix(3, 2, values_result);
  if (matrix.get_transposed() == resultMatrix) {
    return true;
  }
  return false;
}

bool test_determinant() {
  double values[9] = {4, 2, 3,
                      5, 5, 6,
                      7, 3, 9};

  Matrix matrix = Matrix(3, 3, values);
  double determinant = 42;
  if (std::abs(matrix.get_determinant() - determinant) < EPS) {
    return true;
  }
  return false;
}

bool test_minor() {
  double values[9] = {1, 2, 3,
                      4, 5, 6,
                      7, 8, 9};

  Matrix matrix = Matrix(3, 3, values);
  double determinant = 5 * 9 - 6 * 8;
  if (std::abs(matrix.get_minor(1, 1) - determinant) < EPS) {
    return true;
  }
  return false;
}

bool test_cofactor() {
  double values[9] = {4, 2, 3,
                      5, 5, 6,
                      7, 3, 9};

  double values_result[9] = {27, -3, -20,
                             -9, 15, 2,
                             -3, -9, 10};

  Matrix matrix = Matrix(3, 3, values);
  Matrix result_matrix = Matrix(3, 3, values_result);
  if (matrix.get_cofactor() == result_matrix) {
    return true;
  }
  return false;
}

bool test_inverted() {
  double values[9] = {4, 2, 3,
                      5, 5, 6,
                      7, 3, 9};

  double values_result[9] = {9.0 / 14.0, (-3.0) / 14.0, (-1.0) / 14.0,
                            (-1.0) / 14.0, 5.0 / 14.0, (-3.0) / 14.0,
                            (-10.0) / 21.0, 1.0 / 21.0, 5.0 / 21.0};

  Matrix matrix = Matrix(3, 3, values);
  Matrix result_matrix = Matrix(3, 3, values_result);
  if (matrix.get_inverted() == result_matrix) {
    return true;
  }
  return false;
}

bool test_pow() {
  double values[9] = {1, 2, 3,
                      4, 5, 6,
                      7, 8, 9};

  double values_result[9] = {468, 576, 684,
                             1062, 1305, 1548,
                             1656, 2034, 2412};

  Matrix matrix = Matrix(3, 3, values);
  Matrix result_matrix = Matrix(3, 3, values_result);
  if (matrix.pow(3) == result_matrix) {
    return true;
  }
  return false;
}

bool test_exponent () {
    double values[9] =
            {1, 2, 3,
             4, 5, 4,
             3, 2, 1};
    Matrix first_matrix(3, 3, values);
    Matrix second_matrix = first_matrix.multiply(-1);
    Matrix first_result_matrix = first_matrix.get_matrix_exponent(0.00001);
    Matrix second_result_matrix = second_matrix.get_matrix_exponent(0.00001);
    Matrix result;
    result = first_result_matrix.multiply(second_result_matrix);
    Matrix check;
    check = check.get_identity_matrix(3);
    return (result == check);
}

bool test_exception_add() {
  double values_first[9] = {1, 2, 3,
                            4, 5, 6,
                            7, 8, 9};

  double values_second[4] = {1, 2,
                             4, 5};

  Matrix first_matrix = Matrix(3, 3, values_first);
  Matrix second_matrix = Matrix(2, 2, values_second);
  try {
    Matrix result_matrix = first_matrix + second_matrix;
  } catch (Matrix_exception& e) {
    if (strcmp(e.what(), "The matrices do not match in size!") == 0) {
      return true;
    }
    return false;
  }
  return false;
}

bool test_exception_division_by_zero() {
  double values_first[9] = {1, 2, 3,
                            4, 5, 6,
                            7, 8, 9};

  Matrix matrix = Matrix(3, 3, values_first);
  try {
    Matrix result_matrix = matrix / 0.0;
  } catch (Matrix_exception& e) {
    if (strcmp(e.what(), "Division by zero") == 0) {
      return true;
    }
    return false;
  }
  return false;
}

bool test_exception_not_square() {
  double values_first[6] = {1, 2, 3,
                            4, 5, 6};

  Matrix matrix = Matrix(2, 3, values_first);
  try {
    double determinant = matrix.get_determinant();
  } catch (Matrix_exception& e) {
    if (strcmp(e.what(), "The matrix must be square!") == 0) {
      return true;
    }
    return false;
  }
  return false;
}

bool test_exception_matrix_boundary() {
  double values_first[6] = {1, 2, 3,
                            4, 5, 6};

  Matrix matrix = Matrix(2, 3, values_first);
  try {
    double value = matrix[4][1];
  } catch (Matrix_exception& e) {
    if (strcmp(e.what(), "An attempt to access an element outside the matrix boundary!") == 0) {
      return true;
    }
    return false;
  }
  return false;
}

bool test_exception_too_high_pow_degree() {
    double values[9] = {1, 2, 3,
                        4, 1, 2,
                        3, 4, 5};

    Matrix matrix = Matrix(3, 3, values);
    try {
        Matrix result = matrix.pow(101);
    } catch (Matrix_exception& e) {
        if (strcmp(e.what(), "Degree value is too high!") == 0) {
            return true;
        }
        return false;
    }
    return false;
}
