#include <stdio.h>
#include "matrix.h"

int main () {

    double data[9] = {23,2,4,5,6,7,5,7,8};
    Matrix mat = {3,3,data};
    printm(s_mul(mat,8));
    return 0;
}