#ifndef MATRIX_CPP_MATRIX_CPP_H
#define MATRIX_CPP_MATRIX_CPP_H
#include "cmath"
#include <string>
#include <iostream>
#include <exception>

enum Message {ADD = 0, SUB = 1, MUL = 2, DET = 3, EXP = 4};

char MESSAGES[6][30] = {"\nAddition\n",
                        "\nSubtraction\n",
                        "\nMultiplication\n",
                        "\nDeterminant\n",
                        "\nExponent\n"};


void message(int ind) {
    std::cout << MESSAGES[ind];
}

class MatrixExceptions: public std::exception{
public:
	MatrixExceptions(const char* const& msg) : exception(msg){}
};

const MatrixExceptions NOT_SQUARE("Matrix must be square!\n");
const MatrixExceptions WRONG_SIZE("Incompatible matrix sizes!\n");
const MatrixExceptions DIV_BY_ZERO("Division by zero!\n");


class Matrix{
protected:
	unsigned int cols;
	unsigned int rows;
	double* values;
public:
    Matrix();
    Matrix(const Matrix& orig);
    Matrix(Matrix&& orig) noexcept;
    ~Matrix();
	virtual void reset_mem(unsigned int set_rows, unsigned int set_cols);

	unsigned int get_rows() const;

	unsigned int get_cols() const;

	double get_value(unsigned int ind);

	void set_value(unsigned int ind, double val);

	double* get_values();

	void set_values(double* val);

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

class MemMatrix : public Matrix {
private:
	static unsigned int FULL_MEM;
	static unsigned int OBJ_COUNT;
	unsigned int mat_mem;
public:
	MemMatrix();
	MemMatrix(const Matrix& orig);
	MemMatrix(Matrix&& orig);
	~MemMatrix();

	MemMatrix& operator=(Matrix&& orig) noexcept;

	void reset_mem(unsigned int set_rows, unsigned int set_cols) override;

	void print_mem() {
		std::cout << "Matrix memory " << mat_mem << " bits\n";
		std::cout << "Summary memory " << FULL_MEM << " bits\n";
		std::cout << "Monitoring matrix count " << OBJ_COUNT << " \n";
	}
};

unsigned int MemMatrix::FULL_MEM = 0;
unsigned int MemMatrix::OBJ_COUNT = 0;


const double DETERMINANT_ACCURACY = 0.000001;
const double EXPONENT_ACCURACY = 0.001;
const int EXPONENT_STEPS = 100;
double EQUAL_ACCURACY = 0.001;



double matx_det(Matrix matrix);

double check_max_dif(Matrix* fst_mat, Matrix* snd_mat);

Matrix matrix_exp(Matrix matrix);


#endif //MATRIX_CPP_MATRIX_CPP_H
