#ifndef MATRIX_CPP_MATRIX_CPP_H
#define MATRIX_CPP_MATRIX_CPP_H
#include "cmath"
#include <string>
#include <iostream>
#include <array>


enum Message {ERR = 0, ADD = 1, SUB = 2, MUL = 3, DET = 4, EXP = 5};

char MESSAGES[6][30] = {"\nIncompatible matrix sizes!\n",
                        "\nAddition\n",
                        "\nSubtraction\n",
                        "\nMultiplication\n",
                        "\nDeterminant\n",
                        "\nExponent\n"};


void message(int ind) {
    std::cout << MESSAGES[ind];
}

typedef
class Matrix{
public:
    Matrix();
    Matrix(const Matrix& orig);
    ~Matrix();
    void reset_mem(unsigned int set_rows, unsigned int set_cols);
    Matrix& operator=(const Matrix &orig);

    unsigned int cols;
    unsigned int rows;
    double* values;
    double** item;

    void fill_sum(unsigned int set_rows,unsigned int set_cols);

    void fill_mult(unsigned int set_rows,unsigned int set_cols);

    void fill_val(unsigned int set_rows,unsigned int set_cols, const double *set_values);

    void make_one(unsigned int set_rows,unsigned int set_cols);

    void make_zero(unsigned int set_rows,unsigned int set_cols);

    void change_rows(int fst_row, int snd_row) const;

    void print_values() const;
} Matrix;

const double DETERMINANT_ACCURACY = 0.000001;
const double EXPONENT_ACCURACY = 0.001;
const int EXPONENT_STEPS = 100;
double EQUAL_ACCURACY = 0.001;

Matrix operator + (Matrix fst_matx, Matrix snd_matx);

Matrix operator - (Matrix fst_matx, Matrix snd_matx);

Matrix operator * (Matrix fst_matx, Matrix snd_matx);

Matrix operator * (Matrix matrix, double a);

bool operator == (Matrix A, Matrix B);

bool operator != (Matrix A, Matrix B);

double matx_det(Matrix matrix);

double check_max_dif(Matrix fst_mat, Matrix snd_mat);

Matrix matrix_exp(Matrix matrix);


#endif //MATRIX_CPP_MATRIX_CPP_H
