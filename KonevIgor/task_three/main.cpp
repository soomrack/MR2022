#include "testFunctions.hpp"
#include <iostream>

int main(int argc, char const *argv[])
{
  std::cout << "Add test: " << (testAdd() ? "Success\n" : "Fault\n");
  std::cout << "Subtract test: " << (testSubtract() ? "Success\n" : "Fault\n");
  std::cout << "Multiply test: " << (testMultiply() ? "Success\n" : "Fault\n");
  std::cout << "Divide by a scalar test: " << (testDivideByScalar() ? "Success\n" : "Fault\n");
  std::cout << "Triangle matrix test: " << (testTriangleMatrix() ? "Success\n" : "Fault\n");
  std::cout << "Transposed matrix test: " << (testTransposed() ? "Success\n" : "Fault\n");
  std::cout << "Determinant of matrix test: " << (testDeterminant() ? "Success\n" : "Fault\n");
  std::cout << "Minor of matrix test: " << (testMinor() ? "Success\n" : "Fault\n");
  std::cout << "Cofactor matrix test: " << (testCofactor() ? "Success\n" : "Fault\n");
  std::cout << "Inverted matrix test: " << (testInverted() ? "Success\n" : "Fault\n");
  std::cout << "Pow matrix test: " << (testPow() ? "Success\n" : "Fault\n");

  //Exception tests
  std::cout << "Exception add test: " << (testExceptionAdd() ? "Success\n" : "Fault\n");
  std::cout << "Exception division by zero test: " << (testExceptionDivisionByZero() ? "Success\n" : "Fault\n");
  std::cout << "Exception not square test: " << (testExceptionNotSquare() ? "Success\n" : "Fault\n");
  std::cout << "Exception matrix boundary test: " << (testExceptionMatrixBoundary() ? "Success\n" : "Fault\n");

  return 0;
}
