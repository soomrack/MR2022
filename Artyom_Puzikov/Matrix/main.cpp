#include <iostream>
#include "matrix.h"

int main()
{
  try
  {
    Matrix matrix1(3, 3);
    Matrix matrix2(3, 3);
    matrix1.fillMatrix();
    matrix2.fillMatrix();

    std::cout << "Sum\n";
    Matrix matrix3 = matrix1 + matrix2;
    std::cout << matrix3 << '\n';

    std::cout << "Sub\n";
    matrix3 = matrix1 - matrix2;
    std::cout << matrix3 << '\n';

    std::cout << "Mult\n";
    matrix3 = matrix1 * matrix2;
    std::cout << matrix3 << '\n';

    std::cout << "Mult on scalar\n";
    matrix3 = matrix1 * 5;
    std::cout << matrix3 << '\n';

    std::cout << "Transpose\n";
    matrix3 = matrix1.transpose();
    std::cout << matrix3 << '\n';

    std::cout << "Det of matrix\n";
    std::cout << Matrix::getDetMatrix(matrix1) << ' ';
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
  }
  return 0;
}
