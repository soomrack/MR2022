#ifndef MATRIX_CPP_MATRIX_EXCEPTION_H
#define MATRIX_CPP_MATRIX_EXCEPTION_H

class Matrix_exception{
public:
    Matrix_exception();
    Matrix_exception(int code);
    void what() const;
private:
    int error_code;
};

#endif
