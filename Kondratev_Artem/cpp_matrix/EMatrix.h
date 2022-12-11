//
// Created by user on 28.11.22.
//

#ifndef EMATRIX_H
#define EMATRIX_H


#include "Matrix.h"


template<typename T>
class EMatrix: public Matrix<T> {
private:
    unsigned int memory_size;
    static inline unsigned int counter = 0;
    static inline unsigned int general_size = 0;
    static unsigned int calcMemory(int c_rows, int c_cols);
public:
    EMatrix();
    EMatrix(int input_rows, int input_cols);
    EMatrix(int input_rows, int input_cols, T number);
    EMatrix(int input_rows, int input_cols, const std::vector<T>& v);
    explicit EMatrix(int identity_size);
    EMatrix(const EMatrix<T> &other);
    EMatrix(EMatrix<T> &&other) noexcept;
    ~EMatrix();

    EMatrix<T>& operator=(const EMatrix& other);
    EMatrix<T>& operator=(EMatrix&& other) noexcept;

    static unsigned int getCounter();
    static unsigned int getGenSize();
    unsigned int getMemSize();

};


#endif //EMATRIX_H
