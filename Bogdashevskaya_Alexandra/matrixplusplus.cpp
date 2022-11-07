#include <iostream>
#include <stdlib.h>
#include <malloc.h>

class Matrix {
	unsigned int cols {0};
	unsigned int rows {0};
	double* values {NULL};

public:
	Matrix() = default;
	Matrix(unsigned int c, unsigned int r);
	Matrix(const Matrix& matrix);
	Matrix(Matrix&& matrix);
	~Matrix();

	void print_matrix();
	void set_matrix_values();
};


int main() {
	Matrix A;
	Matrix B(2, 2);
	B.print_matrix();
	B.set_matrix_values();
	B.print_matrix();
	Matrix C = B;
	C.print_matrix();
	return 0;
}


Matrix::~Matrix() {
	free(values);
}

Matrix::Matrix(unsigned int c, unsigned int r) {
	cols = c;
	rows = r;
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
	unsigned int n_values = cols * rows;
	values = (double*)malloc(n_values * sizeof(double));
	for (unsigned int idx = 0; idx < n_values; ++idx) {
		values[idx] = matrix.values[idx];
	}
	matrix.~Matrix();
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


void Matrix::set_matrix_values() {
	for (unsigned int index = 0; index < rows * cols; ++index) {
		values[index] = (double)rand();
	}
}