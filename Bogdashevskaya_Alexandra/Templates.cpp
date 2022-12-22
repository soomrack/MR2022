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


template <typename T>
class Matrix {
protected:
	unsigned int cols{ 0 };
	unsigned int rows{ 0 };
	T* values{ nullptr };

public:
	Matrix() = default;
	Matrix(unsigned int cols, unsigned int rows, T value = 0.);
	Matrix(const Matrix& matrix);
	Matrix(Matrix&& matrix) noexcept;
	~Matrix();

	unsigned int get_cols();
	unsigned int get_rows();
	T* get_values();

	void set_value(int idx, T value);



	void print_matrix();
	void set_random_values();
	void set_values(T* given_values);
	bool is_null();
	Matrix add(const Matrix& matrix);
	Matrix substruct(const Matrix& matrix);
	Matrix multiply_by_double(double number);
	Matrix multiply(const Matrix& matrix);
	double det();
	Matrix transpose();
	Matrix invertible();
	Matrix expm(unsigned int accuracy = 10);

	Matrix& operator=(Matrix&& matrix) noexcept;
	Matrix& operator=(const Matrix& matrix);

	Matrix operator+ (const Matrix& matrix);
	Matrix operator- (const Matrix& matrix);
	Matrix operator* (const Matrix& matrix);
	Matrix operator* (const double number);

	void operator+=(const Matrix& matrix);
	void operator-=(const Matrix& matrix);
	void operator*=(const Matrix& matrix);
	void operator*=(const double number);
};

template <typename T>
Matrix<T> identity(unsigned int dimention) {
	Matrix<T> result(dimention, dimention);
	for (unsigned int n = 0; n < dimention; ++n) {
		result.set_value(n * dimention + n, 1.);
	}
	return result;
}

template <typename T>
Matrix<T>::~Matrix() {
	delete[] values;
}


template <typename T>
Matrix<T>::Matrix(unsigned int cols, unsigned int rows, T value) {
	this->cols = cols;
	this->rows = rows;
	unsigned int n_values = cols * rows;
	values = new T[n_values];
	for (unsigned int i = 0; i < n_values; ++i) {
		values[i] = value;
	}
}

template <typename T>
Matrix<T>::Matrix(const Matrix& matrix) {
	cols = matrix.cols;
	rows = matrix.rows;
	unsigned int n_values = cols * rows;
	values = new T[n_values];
	memcpy(values, matrix.values, n_values * sizeof(T));
}

template <typename T>
Matrix<T>::Matrix(Matrix&& matrix) noexcept {
	cols = matrix.cols;
	rows = matrix.rows;
	values = matrix.values;

	matrix.cols = 0;
	matrix.rows = 0;
	matrix.values = nullptr;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& matrix) {
	if (this == &matrix) {
		return *this;
	}
	delete[] values;

	rows = matrix.rows;
	cols = matrix.cols;

	values = new T[rows * cols];
	memcpy(values, matrix.values, rows * cols * sizeof(T));

	return *this;
}


template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix&& matrix) noexcept
{
	if (this == &matrix) return *this;
	rows = matrix.rows;
	cols = matrix.cols;
	values = matrix.values;
	matrix.values = nullptr;
	return *this;
}


template <typename T>
Matrix<T> Matrix<T>::operator+ (const Matrix& matrix) {
	return add(matrix);
}


template <typename T>
Matrix<T> Matrix<T>::operator- (const Matrix& matrix) {
	return substruct(matrix);
}


template <typename T>
Matrix<T> Matrix<T>::operator* (const Matrix& matrix) {
	return multiply(matrix);
}


template <typename T>
Matrix<T> Matrix<T>::operator* (const double number) {
	return multiply_by_double(number);
}

template <typename T>
void Matrix<T>::operator+=(const Matrix& matrix) {
	*this = add(matrix);
}

template <typename T>
void Matrix<T>::operator-=(const Matrix& matrix) {
	*this = substruct(matrix);
}

template <typename T>
void Matrix<T>::operator*=(const Matrix& matrix) {
	*this = multiply(matrix);
}

template <typename T>
void Matrix<T>::operator*=(const double number) {
	*this = multiply_by_double(number);
}

template <typename T>
unsigned int Matrix<T>::get_cols() {
	return cols;
}

template <typename T>
unsigned int Matrix<T>::get_rows() {
	return rows;
}

template <typename T>
T* Matrix<T>::get_values() {
	return values;
}

template <typename T>
void Matrix<T>::set_value(int idx, T value) {
	values[idx] = value;
}

template <typename T>
void Matrix<T>::print_matrix() {
	for (unsigned int row = 0; row < rows; ++row) {
		for (unsigned int col = 0; col < cols; ++col) {
			std::cout << values[row * cols + col] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

template <typename T>
void Matrix<T>::set_random_values() {
	for (unsigned int index = 0; index < rows * cols; ++index) {
		values[index] = (T)rand();
	}
}


template <typename T>
bool Matrix<T>::is_null() {
	return cols == 0 && rows == 0 ? 1 : 0;
}


template <typename T>
Matrix<T> Matrix<T>::add(const Matrix& matrix) {
	if (this->rows != matrix.rows || this->cols != matrix.cols) throw NOTEQUAL;
	Matrix result(cols, rows);
	unsigned int n_values = result.cols * result.rows;
	for (unsigned int index = 0; index < n_values; ++index) {
		result.values[index] = matrix.values[index] + this->values[index];
	}
	return result;
}

template <typename T>
Matrix<T> Matrix<T>::substruct(const Matrix& matrix) {
	if (this->rows != matrix.rows || this->cols != matrix.cols) throw NOTEQUAL;
	Matrix result(cols, rows);
	unsigned int n_values = result.cols * result.rows;
	for (unsigned int index = 0; index < n_values; ++index) {
		result.values[index] = this->values[index] - matrix.values[index];
	}
	return result;
}

template <typename T>
Matrix<T> Matrix<T>::multiply_by_double(double number) {
	Matrix result(cols, rows);
	for (unsigned int index = 0; index < cols * rows; ++index) {
		result.values[index] = values[index] * number;
	}
	return result;
}

template <typename T>
Matrix<T> Matrix<T>::multiply(const Matrix& matrix) {
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

template <typename T>
double Matrix<T>::det() {
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

template <typename T>
Matrix<T> Matrix<T>::transpose() {
	Matrix result(rows, cols);
	for (unsigned int row = 0; row < result.rows; ++row) {
		for (unsigned int col = 0; col < result.cols; ++col) {
			result.values[row * result.cols + col] = values[col * result.rows + row];
		}
	}
	return result;
}

template <typename T>
Matrix<T> Matrix<T>::invertible() {
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

template <typename T>
Matrix<T> Matrix<T>::expm(unsigned int accuracy) {
	if (cols != rows) throw NOTSQUARE;
	Matrix<T> result = identity<T>(rows);
	Matrix<T> powered(*this);
	int factorial = 1;
	for (unsigned int acc = 1; acc <= accuracy; ++acc) {
		factorial *= acc;
		powered *= *this;
		powered *= (1. / factorial);
		result += powered;
	}
	return result;
}


template <typename T>
class Matrix_with_memory : public Matrix<T> {
protected:
	unsigned int memory_size{ 0 };
	static unsigned int total_memory;


public:
	Matrix_with_memory();
	Matrix_with_memory(unsigned int cols, unsigned int rows, T value = 0.);
	Matrix_with_memory(const Matrix_with_memory& matrix);
	Matrix_with_memory(Matrix_with_memory&& matrix) noexcept;
	~Matrix_with_memory();

	Matrix_with_memory& operator=(Matrix_with_memory&& matrix) noexcept;
	Matrix_with_memory& operator=(const Matrix_with_memory& matrix);

	void print_report();
};

template <typename T>
unsigned int Matrix_with_memory<T>::total_memory = 0;


template <typename T>
Matrix_with_memory<T>::Matrix_with_memory() : Matrix<T>() {
	this->memory_size = 0;
	this->total_memory += this->memory_size;
}


template <typename T>
Matrix_with_memory<T>::Matrix_with_memory(unsigned int cols, unsigned int rows, T value) : Matrix<T> (cols, rows, value) {
	this->memory_size = cols * rows * sizeof(T);
	this->total_memory += this->memory_size;
}


template <typename T>
Matrix_with_memory<T>::Matrix_with_memory(const Matrix_with_memory& matrix) : Matrix(matrix) {
	this->memory_size = matrix.memory_size;
	this->total_memory += this->memory_size;
}


template <typename T>
Matrix_with_memory<T>::Matrix_with_memory(Matrix_with_memory&& matrix) noexcept : Matrix(matrix) {
	this->memory_size = matrix.memory_size;

	matrix.memory_size = 0;

}


template <typename T>
Matrix_with_memory<T>::~Matrix_with_memory() {
	std::cout << "Matrix is destroyed\n";
	print_report();

	this->total_memory -= this->memory_size;
	this->memory_size = 0;


}

template <typename T>
Matrix_with_memory<T>& Matrix_with_memory<T>::operator=(Matrix_with_memory&& matrix) noexcept {
	if (this == &matrix) return *this;
	this->rows = matrix.rows;
	this->cols = matrix.cols;
	this->values = matrix.values;

	this->total_memory = - this->memory_size + matrix.memory_size;

	this->memory_size = matrix.memory_size;

	matrix.memory_size = 0;
	matrix.values = nullptr;
	return *this;

	if (this != &matrix) {
		this->memory_size = matrix.memory_size;

		matrix.memory_size = 0;
		
	}

}


template <typename T>
Matrix_with_memory<T>& Matrix_with_memory<T>::operator=(const Matrix_with_memory& matrix) {
	if (this == &matrix) {
		return *this;
	}
	delete[] this->values;

	this->rows = matrix.rows;
	this->cols = matrix.cols;

	this->values = new T[this->rows * this->cols];
	memcpy(this->values, matrix.values, this->rows * this->cols * sizeof(T));

	this->total_memory -= this->memory_size;
	this->memory_size = matrix.memory_size;

	return *this;
}


template <typename T>
void Matrix_with_memory<T>::print_report() {
	std::cout << "Memory size: " << this->memory_size << "\n";
	std::cout << "Total memory size: " << this->total_memory << "\n";
	std::cout << "\n";
}



int main() {
	std::cout << "Template performance:\n\n";

	Matrix<int> A(2, 2);
	A.set_random_values();
	std::cout << "Matrix A:\n";
	A.print_matrix();

	Matrix<int> B(2, 2);
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

	try {
		std::cout << "Exp(A):\n";
		A.expm().print_matrix();
	}
	catch (const Matrix_Exception& e) {
		std::cout << "Inverting is impossible\n";
		std::cerr << e.what() << std::endl;
	}

	std::cout << "-------------------------------\n";

	std::cout << "Using inheritance:\n\n";

	Matrix_with_memory<int> C(3, 3);
	C.set_random_values();
	C.print_matrix();

	Matrix_with_memory<int> D(3, 3);
	D.set_random_values();
	D.print_matrix();

	return 0;
}
