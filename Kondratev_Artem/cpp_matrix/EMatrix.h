//
// Created by user on 28.11.22.
//

#ifndef EMATRIX_H
#define EMATRIX_H


#include "Matrix.h"


class EMatrix: public Matrix {
private:
    inline static unsigned int counter = 0;
public:
    EMatrix();
    EMatrix(int input_rows, int input_cols, double number=0);
    ~EMatrix();

    static unsigned int get_counter();
};


#endif //EMATRIX_H
