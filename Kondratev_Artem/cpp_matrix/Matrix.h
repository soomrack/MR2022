//
// Created by user on 08.11.22.
//


#ifndef HELLO_WORLD_MATRIX_H
#define HELLO_WORLD_MATRIX_H


class Matrix {
private:
    int rows{};
    int cols;
    int size;
public:
    double **values;
    double *start;

    Matrix(int input_rows, int input_cols);
    Matrix(int input_rows, int input_cols, double number);  //  number filled matrix
    explicit Matrix(int row_number);  //  identity matrix
    Matrix(int input_rows, int input_cols, double const array[]);  // filling from array
    ~Matrix();
    Matrix(Matrix const &matrix);
    //Matrix(Matrix const &&matrix) noexcept;

    Matrix &operator = (Matrix const &matrix);
    Matrix operator + (Matrix matrix) const;
    Matrix operator + (double number) const;
    Matrix operator - (Matrix matrix) const;
    Matrix operator * (Matrix matrix) const;
    Matrix operator * (double number) const;
    Matrix operator / (Matrix matrix) const;
    Matrix operator / (double number) const;

    unsigned int get_rows(int print_flag) const;
    unsigned int get_cols(int print_flag) const;
    unsigned int get_size(int print_flag) const;
    static Matrix error();
    void output() const;
    void filling(double number) const;
    void filling(double array[]) const;
    Matrix minor_init(int crossed_row, int crossed_col) const;
    double determinant() const;
    Matrix transposition() const;
    static Matrix minor_transformation(Matrix matrix);
    Matrix inversion() const;
    Matrix power(int power) const;
    static Matrix exp(Matrix matrix);
};


#endif //HELLO_WORLD_MATRIX_H
