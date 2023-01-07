#include "matrix.hpp"
#include "matrixException.hpp"
#include <cstring>

const double EPS = 0.0001;

bool isTriangle(const Matrix& matrix) {
  if (matrix.getRowsCount() != matrix.getColumnsCount()) {
    return false;
  }
  for (size_t i = 1; i <= matrix.getRowsCount(); i++) {
    for (size_t j = i; j <= matrix.getColumnsCount(); j++) {
      if (std::abs(matrix[i][j]) < EPS) {
        return false;
      }
    }
  }

  for (size_t i = 1; i <= matrix.getRowsCount(); i++) {
    for (size_t j = 1; j < i; j++) {
      if (std::abs(matrix[i][j]) > EPS) {
        return false;
      }
    }
  }
  return true;
}

bool testAdd() {
  double valuesFirst[12] = {1, 2, 3, 4,
                            5, 6, 7, 8,
                            9, 10, 11, 12};

  double valuesSecond[12] = {5, 9, 3, 4,
                            51, 48, 13, 0,
                            -2, 1, 111, 42};

  double valuesResult[12] = {6, 11, 6, 8,
                            56, 54, 20, 8,
                            7, 11, 122, 54};

  Matrix firstMatrix = Matrix(3, 4, valuesFirst);
  Matrix secondMatrix = Matrix(3, 4, valuesSecond);
  Matrix resultMatrix = Matrix(3, 4, valuesResult);
  if (resultMatrix == firstMatrix + secondMatrix) {
    return true;
  }
  return false;
}


bool testSubtract() {
  double valuesFirst[12] = {1, 2, 3, 4,
                            5, 6, 7, 8,
                            9, 10, 11, 12};

  double valuesSecond[12] = {12, 11, 121, 0,
                             -48, 3, 13, 5,
                             -1, 15, 111, 42};

  double valuesResult[12] = {-11, -9, -118, 4,
                             53, 3, -6, 3,
                             10, -5, -100, -30};

  Matrix firstMatrix = Matrix(3, 4, valuesFirst);
  Matrix secondMatrix = Matrix(3, 4, valuesSecond);
  Matrix resultMatrix = Matrix(3, 4, valuesResult);
  if (resultMatrix == firstMatrix - secondMatrix) {
    return true;
  }
  return false;
}

bool testMultiply() {
  double valuesFirst[12] = {1, 2, 3, 4,
                            5, 6, 7, 8,
                            9, 10, 11, 12};

  double valuesSecond[8] = {0, 10,
                            -4, 3,
                            46, 15,
                            1, 29};

  double valuesResult[6] = {134, 177,
                            306, 405,
                            478, 633};

  Matrix firstMatrix = Matrix(3, 4, valuesFirst);
  Matrix secondMatrix = Matrix(4, 2, valuesSecond);
  Matrix resultMatrix = Matrix(3, 2, valuesResult);
  if (resultMatrix == firstMatrix * secondMatrix) {
    return true;
  }
  return false;
}

bool testDivideByScalar() {
  double valuesFirst[4] = {1, -100,
                           0, 200};

  double valueSecond = 5.0;

  double valuesResult[6] = {0.2, -20,
                            0, 40};
  Matrix firstMatrix = Matrix(2, 2, valuesFirst);
  Matrix resultMatrix = Matrix(2, 2, valuesResult);
  if (resultMatrix == firstMatrix / valueSecond) {
    return true;
  }
  return false;
}

bool testTriangleMatrix() {
  double values[9] = {17, 24, 3,
                      51, -5, 7,
                      9, 10, 11};
  Matrix matrix = Matrix(3, 3, values);
  Matrix resultMatrix;
  matrix.getTriangleMatrix(resultMatrix);
  if (isTriangle(resultMatrix)) {
    return true;
  }
  return false;
}

bool testTransposed() {
  double values[6] = {1, 2, 3,
                      4, 5, 6};

  double valuesResult[6] = {1, 4,
                            2, 5,
                            3, 6};
  Matrix matrix = Matrix(2, 3, values);
  Matrix resultMatrix = Matrix(3, 2, valuesResult);
  if (matrix.getTransposed() == resultMatrix) {
    return true;
  }
  return false;
}

bool testDeterminant() {
  double values[9] = {4, 2, 3,
                      5, 5, 6,
                      7, 3, 9};

  Matrix matrix = Matrix(3, 3, values);
  double determinant = 42;
  if (std::abs(matrix.getDeterminant() - determinant) < EPS) {
    return true;
  }
  return false;
}

bool testMinor() {
  double values[9] = {1, 2, 3,
                      4, 5, 6,
                      7, 8, 9};

  Matrix matrix = Matrix(3, 3, values);
  double determinant = 5 * 9 - 6 * 8;
  if (std::abs(matrix.getMinor(1, 1) - determinant) < EPS) {
    return true;
  }
  return false;
}

bool testCofactor() {
  double values[9] = {4, 2, 3,
                      5, 5, 6,
                      7, 3, 9};

  double valuesResult[9] = {27, -3, -20,
                            -9, 15, 2,
                            -3, -9, 10};

  Matrix matrix = Matrix(3, 3, values);
  Matrix resultMatrix = Matrix(3, 3, valuesResult);
  if (matrix.getCofactor() == resultMatrix) {
    return true;
  }
  return false;
}

bool testInverted() {
  double values[9] = {4, 2, 3,
                      5, 5, 6,
                      7, 3, 9};

  double valuesResult[9] = {9.0 / 14.0, (-3.0) / 14.0, (-1.0) / 14.0,
                            (-1.0) / 14.0, 5.0 / 14.0, (-3.0) / 14.0,
                            (-10.0) / 21.0, 1.0 / 21.0, 5.0 / 21.0};

  Matrix matrix = Matrix(3, 3, values);
  Matrix resultMatrix = Matrix(3, 3, valuesResult);
  if (matrix.getInverted() == resultMatrix) {
    return true;
  }
  return false;
}

bool testPow() {
  double values[9] = {1, 2, 3,
                      4, 5, 6,
                      7, 8, 9};

  double valuesResult[9] = {468, 576, 684,
                            1062, 1305, 1548,
                            1656, 2034, 2412};

  Matrix matrix = Matrix(3, 3, values);
  Matrix resultMatrix = Matrix(3, 3, valuesResult);
  if (matrix.pow(3) == resultMatrix) {
    return true;
  }
  return false;
}

bool testExceptionAdd() {
  double valuesFirst[9] = {1, 2, 3,
                          4, 5, 6,
                          7, 8, 9};

  double valuesSecond[4] = {1, 2,
                            4, 5};

  Matrix firstMatrix = Matrix(3, 3, valuesFirst);
  Matrix secondMatrix = Matrix(2, 2, valuesSecond);
  try {
    Matrix resultMatrix = firstMatrix + secondMatrix;
  } catch (MatrixException& e) {
    if (strcmp(e.what(), "The matrices do not match in size!") == 0) {
      return true;
    }
    return false;
  }
  return false;
}

bool testExceptionDivisionByZero() {
  double valuesFirst[9] = {1, 2, 3,
                           4, 5, 6,
                           7, 8, 9};

  Matrix matrix = Matrix(3, 3, valuesFirst);
  try {
    Matrix resultMatrix = matrix / 0.0;
  } catch (MatrixException& e) {
    if (strcmp(e.what(), "Division by zero") == 0) {
      return true;
    }
    return false;
  }
  return false;
}

bool testExceptionNotSquare() {
  double valuesFirst[6] = {1, 2, 3,
                           4, 5, 6};

  Matrix matrix = Matrix(2, 3, valuesFirst);
  try {
    double determinant = matrix.getDeterminant();
  } catch (MatrixException& e) {
    if (strcmp(e.what(), "The matrix must be square!") == 0) {
      return true;
    }
    return false;
  }
  return false;
}

bool testExceptionMatrixBoundary() {
  double valuesFirst[6] = {1, 2, 3,
                           4, 5, 6};

  Matrix matrix = Matrix(2, 3, valuesFirst);
  try {
    double value = matrix[4][1];
  } catch (MatrixException& e) {
    if (strcmp(e.what(), "An attempt to access an element outside the matrix boundary!") == 0) {
      return true;
    }
    return false;
  }
  return false;
}
