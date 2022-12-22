#ifndef TEST_FUNCTIONS_H
#define TEST_FUNCTIONS_H

bool testAdd();
bool testSubtract();
bool testMultiply();
bool testDivideByScalar();
bool testTriangleMatrix();
bool testTransposed();
bool testDeterminant();
bool testMinor();
bool testCofactor();
bool testInverted();
bool testPow();

//Exception tests
bool testExceptionAdd();
bool testExceptionDivisionByZero();
bool testExceptionNotSquare();
bool testExceptionMatrixBoundary();

#endif //TEST_FUNCTIONS_H
