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

class Matrix{
private:
	unsigned int cols;
	unsigned int rows;
	double* values;
	double** item;
public:
    Matrix();
    Matrix(const Matrix& orig);
    Matrix(Matrix&& orig) noexcept;
    ~Matrix();
    void reset_mem(unsigned int set_rows, unsigned int set_cols);

	unsigned int get_rows() const;

	unsigned int get_cols() const;

	double get_values(unsigned int ind);

	void set_values(unsigned int ind, double val);

	double get_item(unsigned int row, unsigned int col);

	void set_item(unsigned int row, unsigned int col, double val);

    void fill_sum(unsigned int set_rows,unsigned int set_cols);

    void fill_mult(unsigned int set_rows,unsigned int set_cols);

    void fill_val(unsigned int set_rows,unsigned int set_cols, const double *set_values);

    void make_one(unsigned int set_rows,unsigned int set_cols);

    void make_zero(unsigned int set_rows,unsigned int set_cols);

    void change_rows(int fst_row, int snd_row) const;

    void print_values() const;

	Matrix& operator=(const Matrix& orig);

	Matrix& operator=(Matrix&& orig) noexcept;

	Matrix operator + (Matrix snd_matx);

	Matrix operator - (Matrix snd_matx);

	Matrix operator * (Matrix snd_matx);

	Matrix operator * (double a)  const;

	Matrix operator / (double a)  const;

	Matrix& operator += (Matrix& snd_matx);

	Matrix& operator -= (Matrix& snd_matx);

	bool operator == (Matrix B);

	bool operator != (Matrix B);

};

const double DETERMINANT_ACCURACY = 0.000001;
const double EXPONENT_ACCURACY = 0.001;
const int EXPONENT_STEPS = 100;
double EQUAL_ACCURACY = 0.001;



double matx_det(Matrix matrix);

double check_max_dif(Matrix* fst_mat, Matrix* snd_mat);

Matrix matrix_exp(Matrix matrix);


#endif //MATRIX_CPP_MATRIX_CPP_H
