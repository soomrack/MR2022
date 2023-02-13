#include "testFunctions.h"
#include <iostream>
#include "matrix.h"

int main(int argc, char const *argv[])
{

    std::cout << "Add test: " << (test_add() ? "Success\n" : "Fault\n");
    std::cout << "Subtract test: " << (test_subtract() ? "Success\n" :
   "Fault\n");
    std::cout << "Multiply test: " << (test_multiply() ? "Success\n" :
   "Fault\n");
    std::cout << "Divide by a scalar test: " << (test_divide_by_scalar() ?
   "Success\n" : "Fault\n");
    std::cout << "Triangle matrix test: " << (test_triangle_matrix() ?
   "Success\n" : "Fault\n");
    std::cout << "Transposed matrix test: " << (test_transposed() ?
   "Success\n" : "Fault\n");
    std::cout << "Determinant of matrix test: " << (test_determinant() ?
   "Success\n" : "Fault\n");
    std::cout << "Minor of matrix test: " << (test_minor() ? "Success\n" :
   "Fault\n");
    std::cout << "Cofactor matrix test: " << (test_cofactor() ? "Success\n" :
   "Fault\n");
    std::cout << "Inverted matrix test: " << (test_inverted() ? "Success\n" :
   "Fault\n");
    std::cout << "Pow matrix test: " << (test_pow() ? "Success\n" : "Fault\n");
    std::cout << "Matrix exponent test: " << (test_exponent() ? "Success\n\n" :
    "Fault\n\n");

    //Exception tests
    std::cout << "Exception add test: " << (test_exception_add() ? "Success\n"
    : "Fault\n");
    std::cout << "Exception division by zero test: " <<
    (test_exception_division_by_zero() ? "Success\n" : "Fault\n");
    std::cout << "Exception not square test: " <<
    (test_exception_not_square() ? "Success\n" : "Fault\n");
    std::cout << "Exception matrix boundary test: " <<
    (test_exception_matrix_boundary() ? "Success\n" : "Fault\n");
    std::cout << "Exception exponentiation degree test: " <<
    (test_exception_too_high_pow_degree() ? "Success\n" : "Fault\n");

    // Memory test
    double values[9] = {1, 2,3,
                        4, 5, 6,
                        7, 8, 9};
    Matrix_memory<double> matrix;
    matrix.print_mem();
    Matrix_memory<double> matrix1(3, 3);
    matrix.print_mem();
    Matrix_memory<double> matrix2(3, 3, values);
    matrix.print_mem();
    Matrix_memory<double> matrix3 = matrix2;
    matrix.print_mem();
    Matrix_memory<double> matrix4 = matrix1.add(matrix2);
    matrix.print_mem();
    matrix = matrix2;
    matrix.print_mem();
    matrix1 = matrix4.add(matrix2);
    matrix.print_mem();

  return 0;

}
