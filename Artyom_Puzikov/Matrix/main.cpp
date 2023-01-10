#include <iostream>
#include "matrix.h"

int main()
{
  try
  {
    Matrix_Memory<double> matrix1(3, 3);
    Matrix_Memory<double> matrix2(3, 3);
    matrix1.fill_matrix();
    matrix2.fill_matrix();

    std::cout << "Sum\n";
    Matrix<double> matrix3 = matrix1 + matrix2;
    matrix3.print_values();

    std::cout << "Sub\n";
    matrix3 = matrix1 - matrix2;
    matrix3.print_values();

    std::cout << "Mult\n";
    matrix3 = matrix1 * matrix2;
    matrix3.print_values();

    std::cout << "Mult on scalar\n";
    matrix3 = matrix1 * 5;
    matrix3.print_values();

    std::cout << "Transpose\n";
    matrix3 = matrix1.transpose();
    matrix3.print_values();

    std::cout << "Det of matrix\n";
    std::cout << Matrix<double>::det_matrix(matrix1) << "\n";

    std::cout << "Exp\n";
    Matrix<double>::exp_matrix(matrix1, 3).print_values();

    matrix1.report();
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
  }
  return 0;
}
