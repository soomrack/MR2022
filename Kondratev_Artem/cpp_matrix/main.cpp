#include "MatrixTest.h"


int main() {
    MatrixTest<float>::usingUnused();
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
    MatrixTest<float>::genMemTest();

    int a;
    EMatrix<double> A(2,2);
    std::cout << A.getMemSize() << std::endl;
    std::cout << EMatrix<double>::getGenSize() << std::endl;
    std::cout << EMatrix<double>::getCounter() << std::endl;
    EMatrix<double> B(2,2);
    std::cout << A.getMemSize() << std::endl;
    std::cout << A.getMemSize() << std::endl;
    std::cout << EMatrix<double>::getGenSize() << std::endl;
    std::cout << EMatrix<double>::getCounter() << std::endl;
    A.~EMatrix();
    std::cout << EMatrix<double>::getGenSize() << std::endl;
    std::cout << EMatrix<double>::getCounter() << std::endl;
    B.~EMatrix();
    std::cout << EMatrix<double>::getGenSize() << std::endl;
    std::cout << EMatrix<double>::getCounter() << std::endl;
    std::cin >> a;

    EMatrix<double> C(2,2,4);
    EMatrix<double> D(3,3,5);
    C = D;
    C.output();

    return 0;
}
