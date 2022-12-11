#include "matrix.h"

int main(){

    double values[9] = {1, 0, 0,
                        0, 2, 0,
                        0 ,0, 3};
    Matrix A = Matrix(3, 3).fill_from_array(values);
    A *= 5;
    A.print();
    return 0;
}
