#include "MatrixTest.h"


int main() {
    MatrixTest<float>::using_unused();
    MatrixTest<float>::output_test();
    MatrixTest<double>::overload_test();
    MatrixTest<float>::addition_test();
    MatrixTest<float>::number_addition_test();
    MatrixTest<float>::subtraction_test();
    MatrixTest<double>::multiplication_test();
    MatrixTest<float>::number_multiplication_test();
    MatrixTest<float>::determinant_test();
    MatrixTest<float>::transposition_test();
    MatrixTest<float>::inversion_test();
    MatrixTest<float>::inverse_multiplication_test();
    MatrixTest<float>::number_division_test();
    MatrixTest<float>::power_test();
    MatrixTest<double>::exp_test();
    MatrixTest<float>::equal_test();
    MatrixTest<float>::counter_test();
    MatrixTest<double>::matrix_mem_test();
    MatrixTest<float>::matrix_mem_test();
    MatrixTest<double>::gen_mem_test();
    MatrixTest<float>::gen_mem_test();

    int a;
    EMatrix<double> A(2,2);
    std::cout << A.getMemSize() << std::endl;
    std::cout << EMatrix<double>::getGenSize() << std::endl;
    std::cout << EMatrix<double>::get_counter() << std::endl;
    EMatrix<double> B(2,2);
    std::cout << A.getMemSize() << std::endl;
    std::cout << A.getMemSize() << std::endl;
    std::cout << EMatrix<double>::getGenSize() << std::endl;
    std::cout << EMatrix<double>::get_counter() << std::endl;
    A.~EMatrix();
    std::cout << EMatrix<double>::getGenSize() << std::endl;
    std::cout << EMatrix<double>::get_counter() << std::endl;
    B.~EMatrix();
    std::cout << EMatrix<double>::getGenSize() << std::endl;
    std::cout << EMatrix<double>::get_counter() << std::endl;
    std::cin >> a;

    return 0;
}
