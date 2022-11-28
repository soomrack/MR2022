//
// Created by user on 28.11.22.
//

#include "EMatrix.h"


EMatrix::EMatrix(int input_rows, int input_cols, double number): Matrix(input_rows, input_cols, number) {
    counter++;
}


EMatrix::~EMatrix() {
    counter--;
}


void EMatrix::get_counter() {
    std::cout << EMatrix::counter << std::endl;
}
