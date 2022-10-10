#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Matrix {
	unsigned int cols;
	unsigned int rows;
	double* values;
}Matrix;

Matrix init_matrix(int cols, int rows) {
	Matrix matrix;
	matrix.cols = cols;
	matrix.rows = rows;
	int n_values = matrix.cols * matrix.rows;
	matrix.values = malloc(n_values * sizeof(double));
	return matrix;
}

void set_matrix_values(Matrix* matrix) {
	for (int index = 0; index < matrix -> cols * matrix -> rows; ++index) {
		matrix -> values[index] = (double)rand();
	}
}

void print_matrix(const Matrix matrix) {
	for (int row = 0; row < matrix.rows; ++row) {
		for (int col = 0; col < matrix.cols; ++col) {
			printf("%.2f ", matrix.values[row * matrix.cols + col]);
		}
		printf("\n");
	}
	printf("\n");
}

void free_matrix(Matrix* matrix) {
	free(matrix->values);
}

Matrix add(const Matrix matrix1, const Matrix matrix2) {
	if (matrix1.rows != matrix2.rows || matrix1.cols != matrix2.cols) {
		printf("Addition is impossible. Matrixes should have equal sizes\n");
		exit(1);
	}
	Matrix result = init_matrix(matrix1.cols, matrix1.rows);
	int n_values = result.cols * result.rows;
	result.values = malloc(n_values * sizeof(double));
	for (int index = 0; index < n_values; ++index) {
		result.values[index] = matrix1.values[index] + matrix2.values[index];
	}
	return result;
}

Matrix substruct(const Matrix matrix1, const Matrix matrix2) {
	if (matrix1.rows != matrix2.rows && matrix1.cols != matrix2.cols) {
		printf("Substruction is impossible. Matrixes should have equal sizes");
		exit(1);
	}
	else {
		Matrix result = init_matrix(matrix1.cols, matrix1.rows);
		int n_values = result.cols * result.rows;
		result.values = malloc(n_values * sizeof(double));
		for (int index = 0; index < n_values; ++index) {
			result.values[index] = matrix1.values[index] - matrix2.values[index];
		}
		return result;
	}
}

Matrix multiply_by_double(const Matrix matrix, double number) {
	Matrix result = init_matrix(matrix.cols, matrix.rows);
	int n_values = result.cols * result.rows;
	result.values = malloc(n_values * sizeof(double));
	for (int index = 0; index < n_values; ++index) {
		result.values[index] = matrix.values[index] * number;
	}
	return result;
}

Matrix multiply(const Matrix matrix1, const Matrix matrix2) {
	if (matrix1.cols != matrix2.rows) {
		printf("Multiplication is impossible. Matrixes should have certain sizes");
		exit(1);
	}
	int n_cols = matrix2.cols;
	int n_rows = matrix1.rows;
	Matrix result = init_matrix(n_cols, n_rows);
	for (int row = 0; row < n_rows; ++row) {
		for (int col = 0; col < n_cols; ++col) {
			float summa = 0.;
			for (int k = 0; k < matrix1.cols; ++k) {
				summa += 
					matrix1.values[row * matrix1.cols + k] * 
					matrix2.values[k * matrix2.cols + col];
			}
			result.values[row * n_cols + col] = summa;
		}
	}
}

double det(const Matrix matrix) {
	if (matrix.cols != matrix.rows) {
		printf("Operation is impossible. Matrix should be square");
		exit(1);
	}
	double result = 0;
	int n = matrix.cols; 
	if (n == 1) {
		result = matrix.values[0];
	}
	else {
		for (int row = 0; row < n; ++row) {
			int col = 0;
			Matrix submatrix = init_matrix(n - 1, n - 1);
			int row_offset = 0;
			int col_offset = 0;
			for (int sub_row = 0; sub_row < n - 1; ++sub_row) {
				for (int sub_col = 0; sub_col < n - 1; ++sub_col) {
					if (sub_row == row) { row_offset = 1; }
					if (sub_col == col) { col_offset = 1; }
					submatrix.values[sub_row * (n - 1) + sub_col] = matrix.values[(sub_row + row_offset) * n + (sub_col + col_offset)];
				}
			}
			result += pow(-1, row + col) * matrix.values[row * n + col] * det(submatrix);
		}
	}
	return result;
}



void main() {
	struct Matrix m1, m2, addition, substruction, multiplication1, multiplication2;
	double determinant;

	m1 = init_matrix(3, 3);
	set_matrix_values(&m1);
	print_matrix(m1);

	m2 = init_matrix(3, 3);
	set_matrix_values(&m2);
	print_matrix(m2);

	addition = add(m1, m2);
	print_matrix(addition);

	substruction = substruct(m1, m2);
	print_matrix(substruction);

	determinant = det(m1);
	printf("%f\n", determinant);

	determinant = det(m2);
	printf("%f\n", determinant);

	multiplication1 = multiply_by_double(m1, 5.);
	print_matrix(multiplication1);

	multiplication2 = multiply(m1, m2);
	print_matrix(multiplication2);

	free_matrix(&m1);
	free_matrix(&m2);
	free_matrix(&addition);
	free_matrix(&substruction);
	free_matrix(&multiplication1);
	free_matrix(&multiplication2);


}
