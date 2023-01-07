#ifndef MAT_CPP_TEMP_LIBRARY_H
#define MAT_CPP_TEMP_LIBRARY_H
#include "cmath"
#include <string>
#include <iostream>
#include <exception>

const double DETERMINANT_ACCURACY = 0.000001;
const double EXPONENT_ACCURACY = 0.001;
const int EXPONENT_STEPS = 100;
double EQUAL_ACCURACY = 0.001;

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

MatrixExceptions NOT_SQUARE("Matrix must be square!\n");
MatrixExceptions WRONG_SIZE("Incompatible matrix sizes!\n");
MatrixExceptions DIV_BY_ZERO("Division by zero!\n");

template <typename Type>
class Matrix{
private:
	unsigned int cols;
	unsigned int rows;
	Type* values;
public:
	Matrix() {
		//std::cout << "Constructor\n";
		cols = 1;
		rows = 1;
		values = new Type[cols * rows];
		values[0] = NAN;
	}

	Matrix(const Matrix& orig) {
		//std::cout << "Copy constructor\n";

		rows = orig.rows;
		cols = orig.cols;
		values = new Type[rows * cols];

		for (int k = 0; k < rows * cols; k++) {
			values[k] = orig.values[k];
		}
	}


	Matrix(Matrix&& orig) noexcept {
		//std::cout << "Move constructor\n";

		rows = orig.rows;
		cols = orig.cols;
		values = orig.values;
		orig.rows = 0;
		orig.cols = 0;
		orig.values = nullptr;
	}

	~Matrix() {
		//std::cout << "Deconstructor\n";
		delete[] values;
	}

	void reset_mem(unsigned int set_rows, unsigned int set_cols) {
		delete[] values;
		rows = set_rows;
		cols = set_cols;
		values = new Type[rows * cols];
	}

	void fill_sum(unsigned int set_rows, unsigned int set_cols) {
		reset_mem(set_rows, set_cols);
		for (int k = 0; k < rows * cols; k++) {
			values[k] = k % cols + (unsigned int)(k / cols);
		}
	}

	void fill_mult(unsigned int set_rows, unsigned int set_cols) {
		reset_mem(set_rows, set_cols);
		for (int k = 0; k < rows * cols; k++) {
			values[k] = k % cols * (int)(k / cols);
		}
	}

	void fill_val(unsigned int set_rows, unsigned int set_cols, const double* set_values) {
		reset_mem(set_rows, set_cols);
		for (int k = 0; k < rows * cols; k++) {
			values[k] = set_values[k];
		}
	}

	void make_one(unsigned int set_rows, unsigned int set_cols) {
		reset_mem(set_rows, set_cols);
		for (int k = 0; k < rows * cols; k++) {
			if ((int)(k / cols) == (k % cols)) {
				values[k] = 1.0;
			}
			else {
				values[k] = 0.0;
			}
		}
	}

	void make_zero(unsigned int set_rows, unsigned int set_cols) {
		reset_mem(set_rows, set_cols);
		for (int k = 0; k < rows * cols; k++) {
			values[k] = 0.0;
		}
	}

	void change_rows(const int fst_row, const int snd_row) const {
		double item_buff;
		for (int col = 0; col < cols; col++) {
			item_buff = values[snd_row * cols + col];
			values[snd_row * cols + col] = values[fst_row * cols + col];
			values[fst_row * cols + col] = item_buff;
		}
	}

	void print_values() const {
		std::cout << "\n";
		for (int k = 0; k < rows; k++) {
			std::cout << "(";
			for (int j = 0; j < cols; j++) {
				std::cout << values[k * cols + j] << ", ";
			}
			std::cout << ")\n";
		}
	}

	Matrix& operator=(const Matrix& orig) {
		//std::cout << "Equal operator copy\n";
		if (this == &orig) return *this;
		reset_mem(orig.rows, orig.cols);
		for (int k = 0; k < rows * cols; k++) {
			values[k] = orig.values[k];
		}
		return *this;
	}

	Matrix& operator=(Matrix&& orig) noexcept {
		//std::cout << "Equal operator move\n";
		if (this == &orig) return *this;
		delete[] values;
		cols = orig.cols;
		rows = orig.rows;
		values = orig.values;
		orig.cols = 0;
		orig.rows = 0;
		orig.values = nullptr;
		return *this;
	}

	Matrix operator+(Matrix const snd_matx) {
		if (rows != snd_matx.rows || cols != snd_matx.cols) {
			message(ADD);
			throw WRONG_SIZE;
		}
		Matrix res_matx;
		res_matx.make_zero(rows, cols);
		for (int k = 0; k < rows * cols; k++) {
			res_matx.values[k] = values[k] + snd_matx.values[k];
		}
		return res_matx;
	}

	Matrix operator-(const Matrix snd_matx) {
		if (rows != snd_matx.rows || cols != snd_matx.cols) {
			message(SUB);
			throw WRONG_SIZE;
		}
		Matrix res_matx;
		res_matx.make_zero(rows, cols);
		for (int k = 0; k < rows * cols; k++) {
			res_matx.values[k] = values[k] - snd_matx.values[k];
		}
		return res_matx;
	}

	Matrix operator*(const Matrix snd_matx) {
		if (cols != snd_matx.rows) {
			message(MUL);
			throw WRONG_SIZE;
		}
		Matrix res_matx;
		res_matx.make_zero(rows, snd_matx.cols);
		for (int k = 0; k < rows; k++) {
			for (int j = 0; j < snd_matx.get_cols(); j++) {
				for (int n = 0; n < cols; n++) {
					res_matx.values[k * snd_matx.cols + j] += values[k * cols + n] * snd_matx.values[n * snd_matx.cols + j];
				}
			}
		}
		return res_matx;
	}

	Matrix operator*(double const a) const {
		Matrix res_matx;
		res_matx.make_zero(rows, cols);
		for (int k = 0; k < rows * cols; k++) {
			res_matx.values[k] = a * values[k];
		}
		return res_matx;
	}

	Matrix operator / (double a)  const {
		if (a == 0) throw DIV_BY_ZERO;
		Matrix res_matx;
		res_matx.make_zero(rows, cols);
		for (int k = 0; k < rows * cols; k++) {
			res_matx.values[k] = values[k] / a;
		}
		return res_matx;
	}

	bool operator==(const Matrix B) {
		if (cols != B.cols) {
			return false;
		}
		if (rows != B.rows) {
			return false;
		}
		for (int k = 0; k < cols * rows; k++) {
			if (fabs(values[k] - B.values[k]) > EQUAL_ACCURACY) {
				return false;
			}
		}
		return true;
	}

	bool operator!=(const Matrix B) {
		if (cols != B.cols) {
			return true;
		}
		if (rows != B.rows) {
			return true;
		}
		for (int k = 0; k < cols * rows; k++) {
			if (fabs(values[k] - B.values[k]) > EQUAL_ACCURACY) {
				return true;
			}
		}
		return false;
	}

	Matrix& operator += (Matrix& snd_matx) {
		*this = *this + snd_matx;
		return *this;
	}

	Matrix& operator -= (Matrix& snd_matx) {
		*this = *this - snd_matx;
		return *this;
	}

	unsigned int get_rows() const {
		return rows;
	}

	unsigned int get_cols() const {
		return cols;
	}

	double get_values(unsigned int ind) {
		return values[ind];
	}

	void set_values(unsigned int ind, double val) {
		values[ind] = val;
	}

	double get_item(unsigned int row, unsigned int col) {
		return values[row * cols + col];
	}

	void set_item(unsigned int row, unsigned int col, double val) {
		values[row * cols + col] = val;
	}

	double matx_det() {
		if (get_rows() != get_cols()) {
			message(DET);
			throw NOT_SQUARE;
		}
		double det = 1;
		Matrix trian_mat;
		trian_mat = *this;
		for (int row_fix = 1; row_fix < trian_mat.get_rows(); row_fix++) { // row that will be subtracted
			for (int row_c = row_fix; row_c < trian_mat.get_rows(); row_c++) { // start from the next row
				if (fabs(trian_mat.get_item(row_fix - 1, row_fix - 1)) < DETERMINANT_ACCURACY) { // division by zero check
					trian_mat.change_rows(row_fix - 1, row_fix);
					det = -det;
				}
				double koef = trian_mat.get_item(row_c, row_fix - 1) / trian_mat.get_item(row_fix - 1, row_fix - 1);
				for (int col_c = 0; col_c < trian_mat.get_cols(); col_c++) {
					double item_val = trian_mat.get_item(row_c, col_c) - trian_mat.get_item(row_fix - 1, col_c) * koef;
					trian_mat.set_item(row_c, col_c, item_val);
				}
			}
			det *= trian_mat.get_item(row_fix, row_fix);
		}
		return det;
	}

	double check_max_dif(Matrix* snd_mat) {
		double dif = 0.0;
		for (int k = 0; k < cols * rows; k++) {
			if (fabs(get_values(k) - snd_mat->get_values(k)) > dif) {
				dif = get_values(k) - snd_mat->get_values(k);
			}
		}
		return dif;
	}

	Matrix matrix_exp() {
		if (get_rows() != get_cols()) {
			message(EXP);
			throw NOT_SQUARE;
		}
		Matrix res_mat;
		res_mat.make_one(get_rows(), get_cols());
		Matrix member;
		member.make_one(get_rows(), get_cols());
		Matrix prev_mat;
		for (int m = 1; m <= EXPONENT_STEPS; m++) {
			member = member * *this / m;
			res_mat += member;
			if (fabs(res_mat.check_max_dif(&prev_mat)) < EXPONENT_ACCURACY) {
				return res_mat;
			}
		}
		return res_mat;
	}
};

#endif //MAT_CPP_TEMP_LIBRARY_H
