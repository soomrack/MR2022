#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Matrix 
{
	uint16_t cols;
	uint16_t rows;
	double* values;
}Matrix;

const Matrix EMPTY = { 0, 0, NULL };





Matrix init_matrix(const unsigned int cols, const unsigned int rows);
void set_matrix_values(Matrix* matrix);
void error_size(char* operation_name, char* error);
int is_null(const Matrix matrix);
void print_matrix(const Matrix matrix);
void free_matrix(Matrix* matrix);
Matrix add(const Matrix matrix1, const Matrix matrix2);
Matrix substruct(const Matrix matrix1, const Matrix matrix2);
Matrix multiply_by_double(const Matrix matrix, double number);
Matrix multiply(const Matrix matrix1, const Matrix matrix2);
double det(const Matrix matrix);
Matrix transpose(const Matrix matrix);
Matrix identity(unsigned int dimention);
Matrix invertible(const Matrix matrix);
Matrix copy(const Matrix matrix);
Matrix expo(const Matrix matrix, int accuracy);






void main() 
{
	Matrix m1, m2;

	m1 = init_matrix(3, 3);
	set_matrix_values(&m1);
	print_matrix(m1);

	m2 = init_matrix(3, 3);
	set_matrix_values(&m2);
	print_matrix(m2);

	Matrix addition;
	addition = add(m1, m2);
	print_matrix(addition);
	free_matrix(&addition);

	Matrix substruction;
	substruction = substruct(m1, m2);
	print_matrix(substruction);
	free_matrix(&substruction);


	double determinant;
	determinant = det(m1);
	printf("%.2f\n\n", determinant);

	determinant = det(m2);
	printf("%.2f\n\n", determinant);

	Matrix multiplication1;
	multiplication1 = multiply_by_double(m1, 5.);
	print_matrix(multiplication1);
	free_matrix(&multiplication1);


	Matrix multiplication2;
	multiplication2 = multiply(m1, m2);
	print_matrix(multiplication2);
	free_matrix(&multiplication2);


	Matrix trans;
	trans = transpose(m1);
	print_matrix(trans);
	free_matrix(&trans);

	Matrix invert;
	invert = invertible(m1);
	print_matrix(invert);
	free_matrix(&invert);	

	Matrix exponenta;
	exponenta = expo(m1, 3);
	print_matrix(exponenta);
	free_matrix(&exponenta);

	free_matrix(&m1);
	free_matrix(&m2);


}





/////////////// создание новой матрицы с выделением памяти
Matrix init_matrix(const unsigned int cols, const unsigned int rows) 
{ 
	Matrix matrix;
	matrix.cols = cols;
	matrix.rows = rows;
	unsigned int n_values = matrix.cols * matrix.rows;
	matrix.values = malloc(n_values * sizeof(double));
	return matrix;
}
/////////////


////////////// заполнение матрицы рандомными числами
void set_matrix_values(Matrix* matrix) 
{  
	for (unsigned int index = 0; index < matrix -> cols * matrix -> rows; ++index) 
	{
		matrix -> values[index] = (double)rand();
	}
}
/////////////


////////////// выведение заданной ошибки
void error_size(char* operation_name, char* error) 
{  
	printf("%s is impossible. %s\n", operation_name, error);
}
/////////////


////////////// проверка: нулевая ли матрица
int is_null(const Matrix matrix) 
{ 
	return matrix.cols == 0 && matrix.rows == 0 ?  1 : 0;
}
/////////////


////////////// вывести матрицу в консоль
void print_matrix(const Matrix matrix) 
{ 
	if (is_null(matrix)) 
	{
		printf("The matrix doesn't exist\n\n");
		return;
	}
	for (unsigned int row = 0; row < matrix.rows; ++row) 
	{
		for (unsigned int col = 0; col < matrix.cols; ++col) 
			printf("%.2f ", matrix.values[row * matrix.cols + col]);
		printf("\n");
	}
	printf("\n");
}
/////////////


////////////// отчистить память
void free_matrix(Matrix* matrix) 
{ 
	free(matrix->values);
}
/////////////


////////////// сумма матриц
Matrix add(const Matrix matrix1, const Matrix matrix2) 
{ 
	if (matrix1.rows != matrix2.rows || matrix1.cols != matrix2.cols) 
	{
		error_size("Addition", "Matrixes should have equal sizes");
		return EMPTY;
	}
	Matrix result = init_matrix(matrix1.cols, matrix1.rows);
	unsigned int n_values = result.cols * result.rows;
	for (unsigned int index = 0; index < n_values; ++index) 
		result.values[index] = matrix1.values[index] + matrix2.values[index];

	return result;
}
/////////////


////////////// разность матриц
Matrix substruct(const Matrix matrix1, const Matrix matrix2) 
{ 
	if (matrix1.rows != matrix2.rows && matrix1.cols != matrix2.cols) 
	{
		error_size("Substruction", "Matrixes should have equal sizes");
		return EMPTY;
	}
	Matrix result = init_matrix(matrix1.cols, matrix1.rows);
	unsigned int n_values = result.cols * result.rows;
	for (unsigned int index = 0; index < n_values; ++index) 
		result.values[index] = matrix1.values[index] - matrix2.values[index];

	return result;
}
/////////////


////////////// умножение матрицы на число
Matrix multiply_by_double(const Matrix matrix, double number) 
{ 
	Matrix result = init_matrix(matrix.cols, matrix.rows);
	unsigned int n_values = result.cols * result.rows;
	for (unsigned int index = 0; index < n_values; ++index) 
		result.values[index] = matrix.values[index] * number;
	
	return result;
}
/////////////


////////////// умножение матрицы на матрицу
Matrix multiply(const Matrix matrix1, const Matrix matrix2) 
{ 
	if (matrix1.cols != matrix2.rows) 
	{
		error_size("Multiplication", "Matrixes should have certain sizes");
		return EMPTY;
	}
	unsigned int n_cols = matrix2.cols;
	unsigned int n_rows = matrix1.rows;
	Matrix result = init_matrix(n_cols, n_rows);
	for (unsigned int row = 0; row < n_rows; ++row) 
	{
		for (unsigned int col = 0; col < n_cols; ++col) 
		{
			double summa = 0.0;
			for (unsigned int k = 0; k < matrix1.cols; ++k) 
			{
				summa +=
					matrix1.values[row * matrix1.cols + k] * 
					matrix2.values[k * matrix2.cols + col];
			}
			result.values[row * n_cols + col] = summa;
		}
	}
	return result;
}
/////////////


////////////// определитель матрицы
double det(const Matrix matrix) 
{ 
	if (matrix.cols != matrix.rows) 
	{
		error_size("Getting determinant", "Matrix should be square");
		return 0.;
	}
	double result = 0;
	unsigned int n = matrix.cols;
	if (n == 1) 
	{
		result = matrix.values[0];
		return result;
	}
	for (unsigned int row = 0; row < n; ++row) 
	{
		unsigned int col = 0;
		Matrix submatrix = init_matrix(n - 1, n - 1);
		unsigned int row_offset = 0;
		unsigned int col_offset = 0;
		for (unsigned int sub_row = 0; sub_row < n - 1; ++sub_row) 
		{
			for (unsigned int sub_col = 0; sub_col < n - 1; ++sub_col) 
			{
				if (sub_row == row)  row_offset = 1; 
				if (sub_col == col)  col_offset = 1;
				submatrix.values[sub_row * (n - 1) + sub_col] = 
					matrix.values[(sub_row + row_offset) * n + (sub_col + col_offset)];
			}
		}
		result += pow(-1, row + col) * matrix.values[row * n + col] * det(submatrix);
		free_matrix(&submatrix);
		}
	return result;
}
/////////////


////////////// транспонированная матрица
Matrix transpose(const Matrix matrix) 
{ 
	Matrix result = init_matrix(matrix.rows, matrix.cols);
	for (unsigned int row = 0; row < result.rows; ++row) 
	{
		for (unsigned int col = 0; col < result.cols; ++col) 
		{
			result.values[row * result.cols + col] = matrix.values[col * result.rows + row];
		}
	}
	return result;
}
/////////////


////////////// единичная матрица
Matrix identity(unsigned int dimention) 
{ 
	Matrix result = init_matrix(dimention, dimention);
	for (unsigned int row = 0; row < result.rows; ++row) 
	{
		for (unsigned int col = 0; col < result.cols; ++col) 
		{
			result.values[row * result.cols + col] = (row == col) ? 1. : 0.;
		}
	}
	return result;
}
/////////////


////////////// обратная матрица
Matrix invertible(const Matrix matrix) 
{ 
	if (matrix.cols != matrix.rows) 
	{
		error_size("Getting invertible matrix", "Matrix should be square");
		return EMPTY;
	}
	Matrix transponent = transpose(matrix);
	Matrix result = multiply_by_double(transponent, 1. / det(matrix));
	free_matrix(&transponent);
	return result;
}
/////////////


////////////// копирование матрицы
Matrix copy(const Matrix matrix) 
{ 
	Matrix result = init_matrix(matrix.cols, matrix.rows);
	for (unsigned int index = 0; index < matrix.cols * matrix.rows; ++index) 
	{
		result.values[index] = matrix.values[index];
	}
	return result;
}
/////////////


////////////// экпонента
Matrix expo(const Matrix matrix, int accuracy) 
{ 
	if (matrix.cols != matrix.rows) 
	{
		error_size("Exp", "Matrix should be square");
		return EMPTY;
	}
	Matrix new_result, new_powered, multiplied;
	Matrix result = identity(matrix.rows);
	Matrix powered = identity(matrix.rows);
	int factorial = 1;
	for (int acc = 1; acc <= accuracy; ++acc) 
	{
		factorial *= acc;

		new_powered = multiply(powered, matrix);
		powered = copy(new_powered);
		free_matrix(&new_powered);

		multiplied = multiply_by_double(powered, 1. / factorial);

		new_result = add(result, multiplied);
		result = copy(new_result);
		free_matrix(&new_result);

		free_matrix(&multiplied);
	}
	free_matrix(&powered);
	return result;
}
/////////////
