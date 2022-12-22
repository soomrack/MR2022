#ifndef TEMPLATE_MATRIX_CMATRIX_H
#define TEMPLATE_MATRIX_CMATRIX_H


#include "Matrix.h"


template<typename T>
class CMatrix: public Matrix<T>  {
private:
    static inline unsigned int counter = 0;
    static inline unsigned int general_size = 0;
    static unsigned int calcMemory(int c_rows, int c_cols);
private:
    unsigned int memory_size{};
public:
    CMatrix();

    [[maybe_unused]] CMatrix(int input_rows, int input_cols);
    CMatrix(int input_rows, int input_cols, T number);
    CMatrix(int input_rows, int input_cols, const std::vector<T>& v);
    //explicit CMatrix(int identity_size);
    CMatrix(const CMatrix<T> &other);
    CMatrix(CMatrix<T> &&other) noexcept;
    ~CMatrix();

    CMatrix<T>& operator=(const CMatrix& other);
    CMatrix<T>& operator=(CMatrix&& other) noexcept;

    static unsigned int get_counter();
    static unsigned int get_gen_size();
    unsigned int get_mem_size();
};


#endif //TEMPLATE_MATRIX_CMATRIX_H
