#ifndef UNTITLED_MATRIX_H
#define UNTITLED_MATRIX_H

#endif //UNTITLED_MATRIX_H
class Matrix {
    friend class Matrix_test;
private:
    unsigned int cols;
    unsigned int rows;
    double *values;
public:
    Matrix(unsigned int cols_m, unsigned int rows_m);
    Matrix(const Matrix &A);
    Matrix(Matrix&& A);
    explicit Matrix(unsigned int cols_m);
    ~Matrix();
    static Matrix data_input(Matrix *matrix, const double arr[]);
    static void print_matrix(const Matrix& matrix);
    static void print_matrix(const Matrix& matrix, char symbol);
    static Matrix error();
    Matrix operator+(const Matrix& X) const;
    Matrix operator-(const Matrix& X) const;
    Matrix operator*(const Matrix& X) const;
    Matrix operator=(const Matrix& X) const;
    Matrix operator^(double X) const;
    Matrix operator/ (const Matrix& X) const;
    Matrix operator/ (const double X) const;
    static Matrix exp(const Matrix& A);
    void fill_with(double Number);
};