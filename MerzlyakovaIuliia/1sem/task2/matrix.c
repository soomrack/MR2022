#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define MATIX_ROWS 3
#define MATRIX_COLS 3
#define TOP_BORDER 1000

typedef struct Matrix 
{
	uint16_t cols;
	uint16_t rows;
	double* values;
}Matrix;

const Matrix EMPTY = { 0, 0, NULL };





Matrix matrixInitialization(const uint16_t cols, const uint16_t rows);
void startValues(Matrix* matrix);
void errorOfSize(char* operation_name, char* error);
int16_t isMatrixZero(const Matrix matrix);
void matrixPrint(const Matrix matrix);
void matrixRelease(Matrix* matrix);
Matrix quantum(const Matrix matrix1, const Matrix matrix2);
Matrix substruct(const Matrix matrix1, const Matrix matrix2);
Matrix numericMultiplication(const Matrix matrix, double number);
Matrix multiply(const Matrix matrix1, const Matrix matrix2);
double det(const Matrix matrix);
Matrix transpose(const Matrix matrix);
Matrix identity(uint16_t dimention);
Matrix invertible(const Matrix matrix);
Matrix copy(const Matrix matrix);
Matrix expo(const Matrix matrix, int16_t accuracy);






int main(void)
{
	Matrix m1, m2;

	m1 = matrixInitialization(MATIX_ROWS, MATRIX_COLS);
	startValues(&m1);
    printf("%s", "Начальная матрица 1:\n");
	matrixPrint(m1);

	m2 = matrixInitialization(3, 3);
	startValues(&m2);
    printf("%s", "Начальная матрица 2:\n");
	matrixPrint(m2);

	Matrix quant;
	quant = quantum(m1, m2);
    printf("%s", "Сумма двух матриц:\n");
	matrixPrint(quant);
	matrixRelease(&quant);

	Matrix substruction;
	substruction = substruct(m1, m2);
    printf("%s", "Произведение матриц:\n");
	matrixPrint(substruction);
	matrixRelease(&substruction);


	double determinant;
	determinant = det(m1);
    printf("%s", "Определитель матрицы 1:\n");
	printf("%.2f\n\n", determinant);

	determinant = det(m2);
    printf("%s", "Определитель матрицы 2:\n");
	printf("%.2f\n\n", determinant);

	Matrix multiplication1;
	multiplication1 = numericMultiplication(m1, 5.);
    printf("%s", "Умножение матрицы на число:\n");
	matrixPrint(multiplication1);
	matrixRelease(&multiplication1);


	Matrix multiplication2;
	multiplication2 = multiply(m1, m2);
    printf("%s", "Умножение матрицы на матрицу:\n");
	matrixPrint(multiplication2);
	matrixRelease(&multiplication2);


	Matrix trans;
	trans = transpose(m1);
    printf("%s", "Транспонированная матрица:\n");
	matrixPrint(trans);
	matrixRelease(&trans);

	Matrix invert;
	invert = invertible(m1);
    printf("%s", "Обратная матрица:\n");
	matrixPrint(invert);
	matrixRelease(&invert);

	Matrix exponenta;
	exponenta = expo(m1, 3);
    printf("%s","Матричная экспонента:\n");
	matrixPrint(exponenta);
	matrixRelease(&exponenta);

	matrixRelease(&m1);
	matrixRelease(&m2);
}





/////////////// создание новой матрицы с выделением памяти
Matrix matrixInitialization(const uint16_t cols, const uint16_t rows)
{ 
	Matrix matrix;
	matrix.cols = cols;
	matrix.rows = rows;
	uint16_t n_values = matrix.cols * matrix.rows;
	matrix.values = malloc(n_values * sizeof(double));
	return matrix;
}
/////////////


////////////// заполнение матрицы рандомными числами
void startValues(Matrix* matrix)
{
	for (uint16_t index = 0; index < matrix -> cols * matrix -> rows; ++index)
	{
		matrix -> values[index] = (double)(rand()%TOP_BORDER);
	}
}
/////////////


////////////// выведение заданной ошибки
void errorOfSize(char* operation_name, char* error)
{  
	printf("В %s случился косяяяк!. %s\n", operation_name, error);
}
/////////////


////////////// проверка: нулевая ли матрица
int16_t isMatrixZero(const Matrix matrix)
{ 
	return matrix.cols == 0 && matrix.rows == 0 ?  1 : 0;
}
/////////////


////////////// вывести матрицу в консоль
void matrixPrint(const Matrix matrix)
{ 
	if (isMatrixZero(matrix))
	{
		printf("Матрицы нет\n\n");
		return;
	}
	for (uint16_t row = 0; row < matrix.rows; ++row)
	{
		for (uint16_t col = 0; col < matrix.cols; ++col)
			printf("%.2f\t | \t", matrix.values[row * matrix.cols + col]);
		printf("\n");
	}
	printf("\n\n");
}
/////////////


////////////// отчистить память
void matrixRelease(Matrix* matrix)
{ 
	free(matrix->values);
}
/////////////


////////////// сумма матриц
Matrix quantum(const Matrix matrix1, const Matrix matrix2)
{ 
	if (matrix1.rows != matrix2.rows || matrix1.cols != matrix2.cols) 
	{
		errorOfSize("quantum", "Необходимо сделать матрицы одного размера");
		return EMPTY;
	}
	Matrix result = matrixInitialization(matrix1.cols, matrix1.rows);
	uint16_t n_values = result.cols * result.rows;
	for (uint16_t index = 0; index < n_values; ++index)
		result.values[index] = matrix1.values[index] + matrix2.values[index];

	return result;
}
/////////////


////////////// разность матриц
Matrix substruct(const Matrix matrix1, const Matrix matrix2) 
{ 
	if (matrix1.rows != matrix2.rows && matrix1.cols != matrix2.cols) 
	{
		errorOfSize("Substruct", "Необходимо сделать матрицы одного размера");
		return EMPTY;
	}
	Matrix result = matrixInitialization(matrix1.cols, matrix1.rows);
	uint16_t n_values = result.cols * result.rows;
	for (uint16_t index = 0; index < n_values; ++index)
		result.values[index] = matrix1.values[index] - matrix2.values[index];

	return result;
}
/////////////


////////////// умножение матрицы на число
Matrix numericMultiplication(const Matrix matrix, double number)
{ 
	Matrix result = matrixInitialization(matrix.cols, matrix.rows);
	uint16_t n_values = result.cols * result.rows;
	for (uint16_t index = 0; index < n_values; ++index)
		result.values[index] = matrix.values[index] * number;
	
	return result;
}
/////////////


////////////// умножение матрицы на матрицу
Matrix multiply(const Matrix matrix1, const Matrix matrix2) 
{ 
	if (matrix1.cols != matrix2.rows) 
	{
		errorOfSize("multiply", "Матрицы должны иметь определенные размеры");
		return EMPTY;
	}
	uint16_t n_cols = matrix2.cols;
	uint16_t n_rows = matrix1.rows;
	Matrix result = matrixInitialization(n_cols, n_rows);
	for (uint16_t row = 0; row < n_rows; ++row)
	{
		for (uint16_t col = 0; col < n_cols; ++col)
		{
			double summ = 0.0;
			for (uint16_t k = 0; k < matrix1.cols; ++k)
			{
				summ += matrix1.values[row * matrix1.cols + k] * matrix2.values[k * matrix2.cols + col];
			}
			result.values[row * n_cols + col] = summ;
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
		errorOfSize("det", "Операция применима к квадратным матрицам");
		return 0.;
	}
	double result = 0;
	uint16_t n = matrix.cols;
	if (n == 1) 
	{
		result = matrix.values[0];
		return result;
	}
	for (uint16_t row = 0; row < n; ++row)
	{
		uint16_t col = 0;
		Matrix submatrix = matrixInitialization(n - 1, n - 1);
		uint16_t row_offset = 0;
		uint16_t col_offset = 0;
		for (uint16_t sub_row = 0; sub_row < n - 1; ++sub_row)
		{
			for (uint16_t sub_col = 0; sub_col < n - 1; ++sub_col)
			{
				if (sub_row == row)  row_offset = 1; 
				if (sub_col == col)  col_offset = 1;
				submatrix.values[sub_row * (n - 1) + sub_col] = 
					matrix.values[(sub_row + row_offset) * n + (sub_col + col_offset)];
			}
		}
		result += pow(-1, row + col) * matrix.values[row * n + col] * det(submatrix);
		matrixRelease(&submatrix);
		}
	return result;
}
/////////////


////////////// транспонированная матрица
Matrix transpose(const Matrix matrix) 
{ 
	Matrix result = matrixInitialization(matrix.rows, matrix.cols);
	for (uint16_t row = 0; row < result.rows; ++row)
	{
		for (uint16_t col = 0; col < result.cols; ++col)
		{
			result.values[row * result.cols + col] = matrix.values[col * result.rows + row];
		}
	}
	return result;
}
/////////////


////////////// единичная матрица
Matrix identity(uint16_t dimention)
{ 
	Matrix result = matrixInitialization(dimention, dimention);
	for (uint16_t row = 0; row < result.rows; ++row)
	{
		for (uint16_t col = 0; col < result.cols; ++col)
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
		errorOfSize("invertibe", "Операция применима к квадратным матрицам");
		return EMPTY;
	}
	Matrix transponent = transpose(matrix);
	Matrix result = numericMultiplication(transponent, 1. / det(matrix));
	matrixRelease(&transponent);
	return result;
}
/////////////


////////////// копирование матрицы
Matrix copy(const Matrix matrix) 
{ 
	Matrix result = matrixInitialization(matrix.cols, matrix.rows);
	for (uint16_t index = 0; index < matrix.cols * matrix.rows; ++index)
	{
		result.values[index] = matrix.values[index];
	}
	return result;
}
/////////////


////////////// экпонента
Matrix expo(const Matrix matrix, int16_t accuracy)
{ 
	if (matrix.cols != matrix.rows) 
	{
		errorOfSize("Exp", "Операция применима к квадратным матрицам");
		return EMPTY;
	}
	Matrix new_result, new_powered, multiplied;
	Matrix result = identity(matrix.rows);
	Matrix powered = identity(matrix.rows);
	int16_t factorial = 1;
	for (int16_t acc = 1; acc <= accuracy; ++acc)
	{
		factorial *= acc;

		new_powered = multiply(powered, matrix);
		powered = copy(new_powered);
		matrixRelease(&new_powered);

		multiplied = numericMultiplication(powered, 1. / factorial);

		new_result = quantum(result, multiplied);
		result = copy(new_result);
		matrixRelease(&new_result);

		matrixRelease(&multiplied);
	}
	matrixRelease(&powered);
	return result;
}
/////////////
