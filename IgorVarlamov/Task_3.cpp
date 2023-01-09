#include <iostream>



class Matrix_Exception : public std::domain_error
{
public:
	Matrix_Exception(const char* const message) : std::domain_error(message)
	{}
};


Matrix_Exception NotSquare("The matrix should be square\n");
Matrix_Exception WrongSize("The matrix should have another size\n");
Matrix_Exception MemoryError("Memory has not been allocated\n");
Matrix_Exception DivisionError("Can't divide by zero\n");


class Matrix
{
	friend Matrix subtraction(Matrix A, Matrix B);
	friend Matrix addition(Matrix A, Matrix B);
	friend Matrix multiplication(Matrix A, Matrix B);
	friend Matrix multiplication(Matrix A, Matrix B);
	friend Matrix transposition(Matrix A);
	friend Matrix invertible(Matrix A);

private:
	int cols{ 0 }, rows{ 0 };
	double* values{ nullptr };

public:

	Matrix(int C, int R, int number);
	Matrix() = default;
	Matrix(int cols, int rows);
	Matrix(const Matrix& matrix);
	Matrix(Matrix&& matrix) noexcept;
	~Matrix();

	void output();
	unsigned int get_cols();
	unsigned int get_rows();
	double* get_values();
	double determinant();
	Matrix multiplication_by_num(double num);
	Matrix division_by_num(double num);

	Matrix fill_from_array(double*);

	Matrix operator + (Matrix& second_matrix);
	Matrix operator - (Matrix second_matrix);
	Matrix operator * (Matrix second_matrix);
	Matrix operator / (Matrix second_matrix);

	void operator = (Matrix second_matrix);

	void operator += (Matrix second_matrix);
	void operator -= (Matrix second_matrix);
	void operator *= (Matrix second_matrix);

	Matrix operator ^ (unsigned int x);
};


Matrix::Matrix(int C, int R, int number)
{
	cols = C, rows = R;

	values = new double[rows * cols];

	for (int i = 0; i < cols; ++i)
	{
		for (int j = 0; j < rows; ++j)
		{
			*(values + i * rows + j) = number;
			//values[i] = number;
		}
	}
}

Matrix::Matrix(int cols, int rows)
{
	this->cols = cols;
	this->rows = rows;

	values = new double[cols * rows];
	for (unsigned int i = 0; i < cols * rows; ++i)
	{
		//*(values + i) = rand() % 9;
		values[i] = rand() % 9;
	}
}

Matrix::Matrix(const Matrix& matrix)
{
	cols = matrix.cols;
	rows = matrix.rows;

	values = new double[cols * rows];
	if (!values) throw MemoryError;
	memcpy(values, matrix.values, cols * rows * sizeof(double));
}

Matrix::Matrix(Matrix&& matrix) noexcept
{
	cols = matrix.cols;
	rows = matrix.rows;
	values = matrix.values;

	matrix.cols = 0;
	matrix.rows = 0;
	matrix.values = nullptr;
}

Matrix::~Matrix()
{
	delete[] values;
}



Matrix Matrix::fill_from_array(double* arr)
{
	memcpy(values, arr, rows * cols * sizeof(double));
	return *this;
}

unsigned int Matrix::get_cols()
{
	return cols;
}

unsigned int Matrix::get_rows()
{
	return rows;
}

double* Matrix::get_values() 
{
	return values;
}

void Matrix::output()
{
	for (int i = 0; i < cols; ++i)
	{
		for (int j = 0; j < rows; ++j)
		{
			std::cout << "\t" << *(values + i * rows + j) << "\t";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}



Matrix addition(Matrix A, Matrix B)
{
	if (A.rows != B.rows) throw WrongSize;
	Matrix maxtix_tmp (A.cols, A.rows, 0);

	std::cout << "\tResult of addition A from B:" << "\n";

	for (int i = 0; i < A.cols; ++i)
	{
		for (int j = 0; j < A.rows; ++j)
		{
			*(maxtix_tmp.values + i * A.rows + j) = *(A.values + i * A.rows + j) + *(B.values + i * A.rows + j);
		}
	}
	maxtix_tmp.output();
	return maxtix_tmp;
}

Matrix subtraction(Matrix A, Matrix B)
{
	if (A.rows != B.rows) throw WrongSize;
	Matrix maxtix_tmp = Matrix(A.cols, A.rows, 0);

	std::cout << "\t  Result of subtraction A from B:" << "\n";

	for (int i = 0; i < A.cols; ++i)
	{
		for (int j = 0; j < A.rows; ++j)
		{
			*(maxtix_tmp.values + i * A.rows + j) = *(A.values + i * A.rows + j) - *(B.values + i * A.rows + j);
		}
	}
	maxtix_tmp.output();
	return maxtix_tmp;
}

Matrix multiplication(Matrix A, Matrix B)
{
	if (A.rows != B.rows) throw WrongSize;
	Matrix maxtix_tmp = Matrix(A.cols, A.rows, 0);

	std::cout << "\t  Result of multiplication A from B:" << "\n";

	for (int i = 0; i < A.cols; ++i)
	{
		for (int j = 0; j < A.rows; ++j)
		{
			for (int k = 0; k < A.cols; k++)
			{
				*(maxtix_tmp.values + i * A.rows + j) += *(A.values + i * A.rows + k) * *(B.values + k * A.rows + j);
			}
		}
	}
	maxtix_tmp.output();
	return maxtix_tmp;
}

Matrix transposition(Matrix A)
{
	Matrix maxtix_tmp = Matrix(A.cols, A.rows, 0);

	std::cout << "\t  Result of transposition A:" << "\n";

	for (int i = 0; i < A.cols; ++i)
	{
		for (int j = 0; j < A.rows; ++j)
		{
			*(maxtix_tmp.values + i * maxtix_tmp.rows + j) = *(A.values + j * A.rows + i);
		}
	}
	maxtix_tmp.output();
	return maxtix_tmp;
}

Matrix Matrix::multiplication_by_num(double num)
{
	Matrix result(cols, rows);
	for (unsigned int index = 0; index < cols * rows; ++index) {
		result.values[index] = values[index] * num;
	}
	return result;
}

Matrix Matrix::division_by_num(double num)
{
	if (num == 0) throw DivisionError;
	Matrix result(cols, rows);
	for (unsigned int index = 0; index < cols * rows; ++index) {
		result.values[index] = values[index] / num;
	}
	return result;
}

double Matrix::determinant()
{
	if (rows != cols) throw NotSquare;
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
		result += pow(-1, row + col) * values[row * n + col] * submatrix.determinant();
	}
	return result;
}

Matrix invertible(Matrix A)
{
	if (A.rows != A.cols) throw NotSquare;
	Matrix transponent = transposition(A);
	Matrix result(A.cols, A.rows);
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
			result.values[row * A.cols + col] = pow(-1, row + col) * submatrix.determinant();
		}
	}
	std::cout << "\tResult of invertible Matrix A:" << "\n";
	result.multiplication_by_num(1 / result.determinant()).output();;
	return result.multiplication_by_num(1 / result.determinant());
}



Matrix Matrix::operator + (Matrix& second_matrix)
{
	if (rows != second_matrix.rows) throw WrongSize;
	Matrix maxtix_tmp (cols, rows, 0);

	std::cout << "\tResult of addition A from B through operator \'+\'" << "\n";

	for (int i = 0; i < maxtix_tmp.rows; ++i)
	{
		for (int j = 0; j < maxtix_tmp.cols; ++j)
		{
			*(maxtix_tmp.values + i * maxtix_tmp.rows + j) = *(values + i * rows + j) + *(second_matrix.values + i * second_matrix.rows + j);
		}
	}
	maxtix_tmp.output();
	return maxtix_tmp;
}

Matrix Matrix::operator - (Matrix second_matrix)
{
	if (rows != second_matrix.rows) throw WrongSize;
	Matrix maxtix_tmp (cols, rows, 0);

	std::cout << "\t  Result of subtraction A from B through operator \'-\'" << "\n";

	for (int i = 0; i < maxtix_tmp.rows; ++i)
	{
		for (int j = 0; j < maxtix_tmp.cols; ++j)
		{
			*(maxtix_tmp.values + i * maxtix_tmp.rows + j) = *(values + i * rows + j) - *(second_matrix.values + i * second_matrix.rows + j);
		}
	}
	maxtix_tmp.output();
	return maxtix_tmp;
}

Matrix Matrix::operator * (Matrix second_matrix)
{
	if (rows != second_matrix.rows) throw WrongSize;
	Matrix maxtix_tmp(cols, rows, 0);

	std::cout << "\t  Result of multiplication A to B through operator \'*\'" << "\n";

	for (int i = 0; i < maxtix_tmp.rows; ++i)
	{
		for (int j = 0; j < maxtix_tmp.cols; ++j)
		{
			for (int k = 0; k < maxtix_tmp.rows; k++)
			{
				*(maxtix_tmp.values + i * rows + j) += *(values + i * rows + k) * *(second_matrix.values + k * rows + j);
			}
		}
	}
	maxtix_tmp.output();
	return maxtix_tmp;

}

Matrix Matrix::operator ^ (unsigned int x)
{
	if (rows != cols) throw NotSquare;
	Matrix maxtix_tmp(cols, rows, 1);

	std::cout << "\t  Result of exponentiation Matrix A " << x << " through operator \'^\'" << "\n";

	for (int degree = 0; degree < x; degree++)
	{
		for (int i = 0; i < maxtix_tmp.rows; ++i)
		{
			for (int j = 0; j < maxtix_tmp.cols; ++j)
			{
				for (int k = 0; k < maxtix_tmp.rows; k++)
				{
					*(maxtix_tmp.values + i * maxtix_tmp.rows + j) += *(values + i * rows + k) * *(values + k * rows + j);
				}
			}
		}
	}
	maxtix_tmp.output();
	return maxtix_tmp;
	
}

Matrix Matrix::operator / (Matrix second_matrix)
{

	std::cout << "Result of division A to B through operator \'/\':" << "\n";
	second_matrix = invertible(second_matrix);

	Matrix result(cols, rows, 0);
	Matrix temp(cols, rows);
	
	for (unsigned int i = 0; i < cols * rows; ++i)
	{
		temp.values[i] = values[i]; 
	}
	result = temp * second_matrix;
	return result;
}

void Matrix::operator = (Matrix second_matrix)
{
	for (unsigned int i = 0; i < cols * rows; ++i)
	{
		values[i] = second_matrix.values[i];
	}
}

void Matrix::operator += (Matrix second_matrix)
{
	for (unsigned int i = 0; i < cols * rows; ++i)
	{
		values[i] += second_matrix.values[i];
	}
}

void Matrix::operator -= (Matrix second_matrix)
{
	for (unsigned int i = 0; i < cols * rows; ++i)
	{
		values[i] -= second_matrix.values[i];
	}
}

void Matrix::operator *= (Matrix second_matrix)
{
	for (unsigned int i = 0; i < cols * rows; ++i)
	{
		values[i] *= second_matrix.values[i];
	}
}


int main()
{
	setlocale(LC_ALL, "");

	Matrix A = Matrix(3, 3);
	Matrix B = Matrix(3, 3);

	double arr [] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	Matrix C = Matrix(3, 3).fill_from_array(arr);
	
	std::cout << " " << "\n" << "\n";

	std::cout << "\t\t    Matrix A:" << "\n";
	A.output();
	std::cout << "\t\t    Matrix B: " << "\n";
	B.output();
	std::cout << "\t\t    Matrix C: " << "\n";
	C.output();

	addition(A, B);
	subtraction(A, B);
	multiplication(A, B);
	transposition(A);

	std::cout << "\t Determinant of Matrix A:" << "\n";
	std::cout << "\t\t\t" << A.determinant() << "\n\n";

	invertible(A);

	A + B;
	A - B;
	A * B;
	A ^ 3;
	A / B;
	A += B;
	A -= B;
	A *= B;
}
