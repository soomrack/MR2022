#include <iostream>

using namespace std;

class Matrix
{
	friend Matrix subtraction(Matrix A, Matrix B);
	friend Matrix addition(Matrix A, Matrix B);
	friend Matrix multiplication(Matrix A, Matrix B);
	friend Matrix multiplication(Matrix A, Matrix B);
	friend Matrix transposition(Matrix A);

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
	double determinant();

	Matrix fill_from_array(double*);

	Matrix operator + (Matrix second_matrix);
	Matrix operator - (Matrix second_matrix);
	Matrix operator * (Matrix second_matrix);
	Matrix operator ^ (unsigned int x);
	//Matrix operator / (Matrix second_matrix);
};


Matrix::Matrix(int C, int R, int number)
{
	cols = C, rows = R;

	values = new double[rows * cols];

	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			*(values + i * rows + j) = number;
		}
	}
}



Matrix::Matrix(int cols, int rows)
{
	this->cols = cols;
	this->rows = rows;

	values = new double[cols * rows];
	for (unsigned int i = 0; i < cols * rows; i++)
	{
		values[i] = rand() % 9;
	}
}

Matrix::Matrix(const Matrix& matrix)
{
	cols = matrix.cols;
	rows = matrix.rows;
	unsigned int n_values = cols * rows;
	values = new double[n_values];
	memcpy(values, matrix.values, n_values * sizeof(double));
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

void Matrix::output()
{
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			cout << "\t" << *(values + i * rows + j) << "\t";
		}
		cout << endl;
	}
	cout << endl;
}



Matrix addition(Matrix A, Matrix B)
{
	Matrix maxtix_tmp = Matrix(A.cols, A.rows, 0);

	cout << "\tResult of addition A from B:" << endl;

	for (int i = 0; i < A.cols; i++)
	{
		for (int j = 0; j < A.rows; j++)
		{
			*(maxtix_tmp.values + i * A.rows + j) = *(A.values + i * A.rows + j) + *(B.values + i * A.rows + j);
		}
	}
	maxtix_tmp.output();
	return maxtix_tmp;
}

Matrix subtraction(Matrix A, Matrix B)
{
	Matrix maxtix_tmp = Matrix(A.cols, A.rows, 0);

	cout << "\t  Result of subtraction A from B:" << endl;

	for (int i = 0; i < A.cols; i++)
	{
		for (int j = 0; j < A.rows; j++)
		{
			*(maxtix_tmp.values + i * A.rows + j) = *(A.values + i * A.rows + j) - *(B.values + i * A.rows + j);
		}
	}
	maxtix_tmp.output();
	return maxtix_tmp;
}

Matrix multiplication(Matrix A, Matrix B)
{
	Matrix maxtix_tmp = Matrix(A.cols, A.rows, 0);

	cout << "\t  Result of multiplication A from B:" << endl;

	for (int i = 0; i < A.cols; i++)
	{
		for (int j = 0; j < A.rows; j++)
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

	cout << "\t  Result of transposition A:" << endl;

	for (int i = 0; i < A.cols; i++)
	{
		for (int j = 0; j < A.rows; j++)
		{
			*(maxtix_tmp.values + i * maxtix_tmp.rows + j) = *(A.values + j * A.rows + i);
		}
	}
	maxtix_tmp.output();
	return maxtix_tmp;
}

double Matrix::determinant()
{
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



Matrix Matrix::operator + (Matrix second_matrix)
{
	Matrix maxtix_tmp = Matrix(cols, rows, 0);

	cout << "\tResult of addition A from B through operator \'+\'" << endl;

	for (int i = 0; i < maxtix_tmp.rows; i++)
	{
		for (int j = 0; j < maxtix_tmp.cols; j++)
		{
			*(maxtix_tmp.values + i * maxtix_tmp.rows + j) = *(values + i * rows + j) + *(second_matrix.values + i * second_matrix.rows + j);
		}
	}
	maxtix_tmp.output();
	return maxtix_tmp;
}

Matrix Matrix::operator - (Matrix second_matrix)
{
	Matrix maxtix_tmp = Matrix(cols, rows, 0);

	cout << "\t  Result of subtraction A from B through operator \'-\'" << endl;

	for (int i = 0; i < maxtix_tmp.rows; i++)
	{
		for (int j = 0; j < maxtix_tmp.cols; j++)
		{
			*(maxtix_tmp.values + i * maxtix_tmp.rows + j) = *(values + i * rows + j) - *(second_matrix.values + i * second_matrix.rows + j);
		}
	}
	maxtix_tmp.output();
	return maxtix_tmp;
}

Matrix Matrix::operator * (Matrix second_matrix)
{
	Matrix maxtix_tmp(cols, rows, 1);

	cout << "\t  Result of multiplication A to B through operator \'*\'" << endl;

	for (int i = 0; i < maxtix_tmp.rows; i++)
	{
		for (int j = 0; j < maxtix_tmp.cols; j++)
		{
			for (int k = 0; k < maxtix_tmp.rows; k++)
			{
				*(maxtix_tmp.values + i * maxtix_tmp.rows + j) += *(values + i * rows + k) * *(second_matrix.values + k * second_matrix.rows + j);
			}
		}
	}
	maxtix_tmp.output();
	return maxtix_tmp;
}

Matrix Matrix::operator ^ (unsigned int x)
{
	Matrix maxtix_tmp(cols, rows, 1);

	cout << "\t  Result of exponentiation Matrix A " << x << " through operator \'*\'" << endl;

	for (int degree = 0; degree < x; degree++)
	{
		for (int i = 0; i < maxtix_tmp.rows; i++)
		{
			for (int j = 0; j < maxtix_tmp.cols; j++)
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



int main()
{
	setlocale(LC_ALL, "");

	Matrix A = Matrix(3, 3);
	Matrix B = Matrix(3, 3);

	double arr [] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	Matrix C = Matrix(3, 3).fill_from_array(arr);
	
	cout << " " << endl << endl;

	cout << "\t\t    Matrix A:" << endl;
	A.output();
	cout << "\t\t    Matrix B: " << endl;
	B.output();
	cout << "\t\t    Matrix C: " << endl;
	C.output();

	addition(A, B);
	subtraction(A, B);
	multiplication(A, B);
	transposition(A);

	cout << "\t Determinant of Matrix A:" << endl;
	cout << "\t\t\t" << A.determinant() << "\n\n";

	A + B;
	A - B;
	A * B;
	A ^ 3;
}
