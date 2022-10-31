#include <iostream>
#include <malloc.h>

class Matrix {
private:
    unsigned int cols;
    unsigned int rows;
public:
    double *values;
    Matrix(const unsigned int cols_num, const unsigned int rows_num);
};


Matrix::Matrix(const unsigned int cols_num, const unsigned int rows_num){  // Инициализация матриц
        cols = cols_num;
        rows = rows_num;
        values = new double[cols * rows];  // malloc(cols * rows * sizeof(double));
        // delete[] matrix.values;
        for (unsigned int idx = 0; idx < cols * rows; idx++){
            values[idx] = 0.0;
        }
}



int main() {
    Matix A(5,5);
    return 0;
}
