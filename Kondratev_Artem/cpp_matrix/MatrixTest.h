//
// Created by user on 08.11.22.
//

#ifndef TEST_H
#define TEST_H


#include <iostream>
#include <iomanip>
#include <vector>
#include "Matrix.h"
#include "EMatrix.h"
#include "MatrixException.h"


template<typename T>
class MatrixTest {
private:
    inline static const T EPSILON = 0.000001;
    inline static std::vector<T> vector1 = {2, 8, 1, 3};
    inline static std::vector<T> vector2 = {4, 9, 21, 13};
    inline static std::vector<T> vector3 = {2, 2, 2, 2};
    inline static T power_array[] = {64, 216, 27, 91};
    inline static int power = 3;

public:
    static void usingUnused();
    static void calculationCheck(T true_array[], Matrix<T> *matrix, const std::string& text);
    static Matrix<T> createMatrix(const std::vector<T>& vector);
    static void outputTest();
    static void overloadTest();
    static void additionTest();
    static void numberAdditionTest();
    static void subtractionTest();
    static void multiplicationTest();
    static void numberMultiplicationTest();
    static void determinantTest();
    static void transpositionTest();
    static void inversionTest();
    static void inverseMultiplicationTest();
    static void numberDivisionTest();
    static void powerTest();
    static void expTest();
    static void equalTest();
    static void counterTest();
    static void matrixMemTest();
    static void genMemTest();
};


#endif //TEST_H
