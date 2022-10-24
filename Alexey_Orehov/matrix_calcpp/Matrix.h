#ifndef PROGRAMMING_MATRIX_H
#define PROGRAMMING_MATRIX_H

#include <cmath>
#include <malloc.h>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <malloc.h>


class Matrix{
private:
    double* values;

    Matrix(unsigned int, unsigned int, double*);

public:
    unsigned int rows;
    unsigned int cols;

    Matrix(unsigned int, unsigned int, double default_value = NAN);
    double* operator[](unsigned int idx);

    Matrix random(int min_value, int max_value);
    Matrix identity();
    Matrix from_array(double* array);
    void print();
};

void printm(Matrix mat);

#endif //PROGRAMMING_MATRIX_H
