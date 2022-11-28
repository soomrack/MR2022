//
// Created by user on 28.11.22.
//

#ifndef EMATRIX_H
#define EMATRIX_H


#include "Matrix.h"


class EMatrix: public Matrix {
private:
    unsigned int memory_size;
    inline static unsigned int counter = 0;
    inline static unsigned int general_size = 0;
    static unsigned int calc_memory(int rows, int cols);
public:
    EMatrix();
    EMatrix(int input_rows, int input_cols);
    EMatrix(int input_rows, int input_cols, double number);
    EMatrix(int input_rows, int input_cols, const std::vector<double>& v);
    EMatrix(int identity_size);
    ~EMatrix();

    static unsigned int get_counter();
};


#endif //EMATRIX_H
