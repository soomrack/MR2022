#include <iostream>
#include <stdlib.h>
#include <malloc.h>

class Matrix_Exception : public std::exception
{
public:
	Matrix_Exception(const char* const& msg) : exception(msg)
	{}
};

Matrix_Exception NOTEQUAL("Matrixes should have equal sizes\n");
Matrix_Exception MULTIPLICATIONERR("Number of first matrix's columns should be equal to number of second matrix's rows\n");
Matrix_Exception NOTSQUARE("Matrix should be square\n");


class Matrix {
	unsigned int cols {0};
	unsigned int rows {0};
	double* values {NULL};

public:
	Matrix() = default;
	Matrix(unsigned int cols, unsigned int rows);
	Matrix(const Matrix& matrix);
	Matrix(Matrix&& matrix);
	~Matrix();

	unsigned int get_cols();
	unsigned int get_rows();
	double* get_values();

	void set_value(int idx, double value);



	void print_matrix();
	void set_random_values();
	void set_values(double* given_values);
	bool is_null();
	Matrix add(const Matrix& matrix);
	Matrix substruct(const Matrix& matrix);
	Matrix multiply_by_double(double number);
	Matrix multiply(const Matrix& matrix);
	double det();
	Matrix transpose();
	Matrix invertible();
	Matrix expo(int accuracy);

	Matrix& operator=(Matrix&&) noexcept;
	Matrix& operator=(const Matrix&);
};

Matrix identity(unsigned int dimention) {
	Matrix result(dimention, dimention);
	unsigned int cols = result.get_cols();
	unsigned int rows = result.get_rows();
	for (unsigned int row = 0; row < rows; ++row) {
		for (unsigned int col = 0; col < cols; ++col) {
			if (row == col) {
				result.set_value(row * result.get_cols() + col, 1.);
			}
			else {
				result.set_value(row * result.get_cols() + col, 0.);

			}
		}
	}
	return result;
}

int main() {
	Matrix A(2, 2);
	A.set_random_values();
	std::cout << "Matrix A:\n";
	A.print_matrix();

	Matrix B(2, 2);
	B.set_random_values();
	std::cout << "Matrix B:\n";
	B.print_matrix();

	try {
		std::cout << "A + B:\n";
		A.add(B).print_matrix();
	}
	catch (const Matrix_Exception& e) {
		std::cout << "Addition is impossible\n";
		std::cerr << e.what() << std::endl;
	}

	try {
		std::cout << "A - B:\n";
		A.substruct(B).print_matrix();
	}
	catch (const Matrix_Exception& e) {
		std::cout << "Substruction is impossible\n";
		std::cerr << e.what() << std::endl;
	}

	std::cout << "A * 2:\n";
	A.multiply_by_double(2.).print_matrix();

	try {
		std::cout << "A * B:\n";
		A.multiply(B).print_matrix();
	}
	catch (const Matrix_Exception& e) {
		std::cout << "Multiplication is impossible\n";
		std::cerr << e.what() << std::endl;
	}

	try {
		std::cout << "det(A):\n";
		std::cout << A.det() << "\n\n";
	}
	catch (const Matrix_Exception& e) {
		std::cout << "Getting determinant is impossible\n";
		std::cerr << e.what() << std::endl;
	}

	std::cout << "Transponent A:\n";
	A.transpose().print_matrix();

	try {
		std::cout << "Inverted A:\n";
		A.invertible().print_matrix();
	}
	catch (const Matrix_Exception& e) {
		std::cout << "Inverting is impossible\n";
		std::cerr << e.what() << std::endl;
	}
	/*
	try {
		std::cout << "Exp(A):\n";
		A.expo(3).print_matrix();
	}
	catch (const Matrix_Exception& e) {
		std::cout << "Inverting is impossible\n";
		std::cerr << e.what() << std::endl;
	}
	*/
	
	return 0;
}


Matrix::~Matrix() {
	free(values);
}

Matrix::Matrix(unsigned int cols, unsigned int rows) {
	this->cols = cols;
	this->rows = rows;
	unsigned int n_values = cols * rows;
	values = (double*)malloc(n_values * sizeof(double));
	for (unsigned int i = 0; i < n_values; ++i) {
		values[i] = 0.;
	}
}

Matrix::Matrix(const Matrix& matrix) {
	cols = matrix.cols;
	rows = matrix.rows;	
	unsigned int n_values = cols * rows;
	values = (double*)malloc(n_values * sizeof(double));
	for (unsigned int idx = 0; idx < n_values; ++idx) {
		values[idx] = matrix.values[idx];
	}
}

Matrix::Matrix(Matrix&& matrix) {
	cols = matrix.cols;
	rows = matrix.rows;
	values = matrix.values;

	matrix.cols = 0;
	matrix.rows = 0;
	matrix.values = nullptr;
}

Matrix& Matrix::operator=(const Matrix& matrix) {
	if (this != &matrix) {
		free(values);

		rows = matrix.rows;
		cols = matrix.cols;

		values = (double*)malloc(rows * cols * sizeof(double));
		for (unsigned int idx = 0; idx < rows * cols; idx++) {
			values[idx] = matrix.values[idx];
		}
	}

	return *this;
}


Matrix& Matrix::operator=(Matrix&& matrix) noexcept
{
	if (this == &matrix) return *this;
	free(matrix.values);
	rows = matrix.rows;
	cols = matrix.cols;
	values = matrix.values;
	matrix.values = nullptr;
	return *this;
}



unsigned int Matrix::get_cols() {
	return cols;
}

unsigned int Matrix::get_rows() {
	return rows;
}

double* Matrix::get_values() {
	return values;
}

void Matrix::set_value(int idx, double value) {
	values[idx] = value;
}

void Matrix::print_matrix() {
	for (unsigned int row = 0; row < rows; ++row) {
		for (unsigned int col = 0; col < cols; ++col) {
			std::cout << values[row * cols + col] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}


void Matrix::set_random_values() {
	for (unsigned int index = 0; index < rows * cols; ++index) {
		values[index] = (double)rand();
	}
}



bool Matrix::is_null() {
	return cols == 0 && rows == 0 ? 1 : 0;
}


Matrix Matrix::add(const Matrix& matrix) { 
	if (this->rows != matrix.rows || this->cols != matrix.cols) throw NOTEQUAL;
	Matrix result(matrix.cols, matrix.rows);
	unsigned int n_values = result.cols * result.rows;
	for (unsigned int index = 0; index < n_values; ++index) {
		result.values[index] = matrix.values[index] + this->values[index];
	}
	return result;
}

Matrix Matrix::substruct(const Matrix& matrix) {
	if (this->rows != matrix.rows || this->cols != matrix.cols) throw NOTEQUAL;
	Matrix result(matrix.cols, matrix.rows);
	unsigned int n_values = result.cols * result.rows;
	for (unsigned int index = 0; index < n_values; ++index) {
		result.values[index] = this->values[index] - matrix.values[index];
	}
	return result;
}

Matrix Matrix::multiply_by_double(double number) {
	Matrix result(cols, rows);
	for (unsigned int index = 0; index < cols * rows; ++index) {
		result.values[index] = values[index] * number;
	}
	return result;
}

Matrix Matrix::multiply(const Matrix& matrix) { 
	if (this->cols != matrix.rows) throw MULTIPLICATIONERR;
	unsigned int n_cols = matrix.cols;
	unsigned int n_rows = this->rows;
	Matrix result(n_cols, n_rows);
	for (unsigned int row = 0; row < n_rows; ++row) {
		for (unsigned int col = 0; col < n_cols; ++col) {
			double summa = 0.0;
			for (unsigned int k = 0; k < this->cols; ++k) {
				summa +=
					this->values[row * this->cols + k] *
					matrix.values[k * matrix.cols + col];
			}
			result.values[row * n_cols + col] = summa;
		}
	}
	return result;
}

double Matrix::det() { 
	if (cols != rows) throw NOTSQUARE;
	double result = 0;
	unsigned int n = cols;
	if (n == 1) {
		result = values[0];
		return result;
	}
	for (unsigned int row = 0; row < n; ++row) {
		unsigned int col = 0;
		Matrix submatrix(n - 1, n - 1);
		unsigned int row_offset = 0;
		unsigned int col_offset = 0;
		for (unsigned int sub_row = 0; sub_row < n - 1; ++sub_row) {
			for (unsigned int sub_col = 0; sub_col < n - 1; ++sub_col) {
				if (sub_row == row) { row_offset = 1; }
				if (sub_col == col) { col_offset = 1; }
				submatrix.values[sub_row * (n - 1) + sub_col] =
					values[(sub_row + row_offset) * n + (sub_col + col_offset)];
			}
		}
		result += pow(-1, row + col) * values[row * n + col] * submatrix.det();
	}
	return result;
}

Matrix Matrix::transpose() {
	Matrix result(rows, cols);
	for (unsigned int row = 0; row < result.rows; ++row) {
		for (unsigned int col = 0; col < result.cols; ++col) {
			result.values[row * result.cols + col] = values[col * result.rows + row];
		}
	}
	return result;
}


Matrix Matrix::invertible() {
	if (cols != rows) throw NOTSQUARE;
	Matrix transponent = transpose();
	Matrix result(cols, rows);
	for (unsigned int row = 0; row < transponent.rows; ++row) {
		for (unsigned int col = 0; col < transponent.cols; ++col) {
			Matrix submatrix(transponent.cols - 1, transponent.rows - 1);
			unsigned int row_offset = 0;
			unsigned int col_offset = 0;
			for (unsigned int sub_row = 0; sub_row < submatrix.get_rows(); ++sub_row) {
				if (row == sub_row) { row_offset = 1; }
				for (unsigned int sub_col = 0; sub_col < submatrix.get_cols(); ++sub_col) {
					if (col == sub_col) { col_offset = 1; }
					submatrix.values[sub_row * (transponent.cols - 1) + sub_col] =
						transponent.values[(sub_row + row_offset) * transponent.cols + (sub_col + col_offset)];
				}
			}
			result.values[row * cols + col] = pow(-1, row + col) * submatrix.det();
		}
	}

	return result.multiply_by_double(1 / result.det());
}

Matrix Matrix::expo(int accuracy) { 
	if (cols != rows) throw NOTSQUARE;
	Matrix result = identity(rows);
	Matrix powered = *this;
	int factorial = 1;
	for (int acc = 1; acc <= accuracy; ++acc) {
		factorial *= acc;
		powered = powered.multiply(*this);
		powered = powered.multiply_by_double(1. / factorial);
		result = result.add(powered);
	}
	return result;
}

