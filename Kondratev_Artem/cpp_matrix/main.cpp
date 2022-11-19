#include "MatrixTest.h"

int main() {
    MatrixTest::using_unused();
    MatrixTest::output_test();
    MatrixTest::overload_test();
    MatrixTest::addition_test();
    MatrixTest::number_addition_test();
    MatrixTest::subtraction_test();
    MatrixTest::multiplication_test();
    MatrixTest::number_multiplication_test();
    MatrixTest::determinant_test();
    MatrixTest::transposition_test();
    MatrixTest::inversion_test();
    MatrixTest::inverse_multiplication_test();
    MatrixTest::number_division_test();
    MatrixTest::power_test();
    MatrixTest::exp_test();
    Matrix A(2,2,2.0);
    A.output();
    std::cout << A.get_value(0, 0);
    return 0;
}
