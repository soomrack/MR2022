#include "MatrixTest.h"
#include "EMatrix.h"


int main() {
    /*MatrixTest::using_unused();
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
    MatrixTest::exp_test();*/
    EMatrix a(2,4, 5);
    a.output();
    EMatrix::get_counter();
    return 0;
}
