#include <iostream>
#include "matrix.h"

int main()
{
  try
  {
    Matrix<double> matrix1(3, 3);
    Matrix<double> matrix2(3, 3);
    matrix1.fillMatrix();
    matrix2.fillMatrix();

    std::cout << "Sum\n";
    Matrix<double> matrix3 = matrix1 + matrix2;
    matrix3.printValues();

    std::cout << "Sub\n";
    matrix3 = matrix1 - matrix2;
    matrix3.printValues();

    std::cout << "Mult\n";
    matrix3 = matrix1 * matrix2;
    matrix3.printValues();

    std::cout << "Mult on scalar\n";
    matrix3 = matrix1 * 5;
    matrix3.printValues();

    std::cout << "Transpose\n";
    matrix3 = matrix1.transpose();
    matrix3.printValues();

    std::cout << "Det of matrix\n";
    std::cout << Matrix<double>::getDetMatrix(matrix1) << ' ';

    std::cout << "Exp\n";
    Matrix<double>::exp_matrix(matrix1, 3).printValues();
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
  }
  return 0;
}
