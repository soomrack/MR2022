#include "MatrixTest.h"


int main() {
    /*MatrixTest<float>::usingUnused();
    MatrixTest<float>::outputTest();
    MatrixTest<double>::overloadTest();
    MatrixTest<float>::additionTest();
    MatrixTest<float>::numberAdditionTest();
    MatrixTest<float>::subtractionTest();
    MatrixTest<double>::multiplicationTest();
    MatrixTest<float>::numberMultiplicationTest();
    MatrixTest<float>::determinantTest();
    MatrixTest<float>::transpositionTest();
    MatrixTest<float>::inversionTest();
    MatrixTest<float>::inverseMultiplicationTest();
    MatrixTest<float>::numberDivisionTest();
    MatrixTest<float>::powerTest();
    MatrixTest<double>::expTest();
    MatrixTest<float>::equalTest();
    MatrixTest<float>::counterTest();
    MatrixTest<double>::matrixMemTest();
    MatrixTest<float>::matrixMemTest();
    MatrixTest<double>::genMemTest();
    MatrixTest<float>::genMemTest();*/

    std::vector v = {1, 0, 2, 4};
    Matrix<double> A(2, 2, {1, 0, 2, 4});
    A.output();
    Matrix<double> B = Matrix<double>::exp(A, 200);
    B.output();
    return 0;
}
