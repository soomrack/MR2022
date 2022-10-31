#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

class Matrix
{


public:

	unsigned int rows;
	unsigned int cols;
	double& operator[](unsigned int idx) {return values[idx]; }
	Matrix(unsigned int, unsigned int, double value = 0.0);
	void generateMatrix();
	void output();
	friend double& determinant(Matrix, unsigned int);
	friend ostream& operator<<(ostream& out, Matrix m);
	Matrix copy();
	Matrix addiction(Matrix);
	Matrix subtraction(Matrix);
	Matrix multiply(Matrix);
	Matrix multiply(const double);
	Matrix create_one_matrix(const unsigned int);
	Matrix transpose();
	Matrix exponent();
	Matrix Minor(Matrix,const unsigned int, const unsigned int,const unsigned int);
	Matrix& operator+ (const Matrix&);
	Matrix& operator- (const Matrix&);
	Matrix& operator* (const Matrix&);
	Matrix& operator* (const double);
	Matrix& operator/ (const double);
	Matrix& operator+=(const Matrix&);
	Matrix& operator-=(const Matrix&);
	Matrix& operator*=(const Matrix&);
	Matrix& operator*=(const double);
	Matrix& operator/=(double);
	
	

private:
	double* values;
};


void Matrix::generateMatrix()
{
	for (unsigned int index = 0; index<cols*rows; index++) 
	{
		values[index] = double(rand() % 10);
	}
}


Matrix Matrix::copy() {
	Matrix res = Matrix(rows, cols);
	memcpy(res.values, values, rows * cols * sizeof(double));
	return res;
}


ostream& operator<<(ostream& out, Matrix m) {
	{
		for (unsigned int row = 0; row < m.rows; row++)
		{
			for (int col = 0; col < m.cols; col++)
			{
				out << m.values[row * m.rows + col] << "\t";
			}
			out << endl;
		}
		out << endl;
		return(out);
	}
}

Matrix Matrix::addiction(Matrix mat) {
	Matrix res = this->copy();
	for (unsigned int idx = 0; idx < rows * cols; idx++) {
		res.values[idx] += mat.values[idx];
	}
	return res;
}


Matrix Matrix::subtraction(Matrix mat) {
	Matrix res = this->copy();
	for (unsigned int idx = 0; idx < rows * cols; idx++) {
		res.values[idx] -= mat.values[idx];
	}
	return res;
}


Matrix Matrix::multiply(Matrix mat) {
	Matrix multiplication(rows, mat.cols);
	for (unsigned int row = 0; row < multiplication.rows; row++) {
		for (unsigned int col = 0; col < multiplication.cols; col++) {
			double sum = 0;
			for (unsigned int k = 0; k < mat.rows; k++) {
				sum += values[row * cols + k] * mat.values[k * mat.cols + col];
			}
			multiplication.values[row * multiplication.cols + col] = sum;
		}
	}
	return (multiplication);
}


Matrix Matrix::multiply(const double k) { // Умножение матрицы на число
	Matrix multiply(rows, cols);
	for (unsigned int idx = 0; idx < rows * cols; idx++) {
		this->values[idx] *= k;
	}
	return multiply = *this;
}


Matrix Matrix::Minor(Matrix matrix,const unsigned int size, const unsigned int row, const unsigned int col) {
	Matrix m1 (size - 1, size -1);
	unsigned int shiftRow = 0; //Смещение индекса строки в матрице
	unsigned int shiftCol; //Смещение индекса столбца в матрице
	for (int rows = 0; rows < size - 1; rows++) {
		//Пропустить row-ую строку
		if (rows == row) {
			shiftRow = 1; //Как только встретили строку, которую надо пропустить, делаем смещение для исходной матрицы
		}
		shiftCol = 0; //Обнулить смещение столбца
		for (int cols = 0; cols < size - 1; cols++) {
			if (cols == col) {
				shiftCol = 1;
			}
			m1[rows * (size - 1) + cols] = matrix[(rows + shiftRow) * size + (cols + shiftCol)];
		}
	}
	return m1;
}


Matrix::Matrix(unsigned int num_row, unsigned int num_col, double val)
{
	rows = num_row;
	cols = num_col;
	unsigned int index = rows * cols;
	values = new double [index];
	Matrix::generateMatrix();
}


void Matrix::output()
{
	for (unsigned int row  = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			std::cout << values[row*rows+col] << "\t";
		}
		std::cout << endl;
	}
}


Matrix Matrix::transpose() {
	Matrix trans(cols, rows);
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			trans.values[row * trans.cols + col] = values[col * trans.rows + row];
		}
	}
	return trans;
}


Matrix& Matrix::operator+(const Matrix& matrix) {
	Matrix add(matrix.rows, matrix.cols);
for (int index = 0; index < rows * cols; ++index) {
	this->values[index] += matrix.values[index];
												  }
return (add=*this);
}


Matrix& Matrix::operator-(const Matrix& matrix) {
	Matrix sub(matrix.rows, matrix.cols);
	for (int index = 0; index < rows * cols; ++index) {
		this->values[index] -= matrix.values[index];
	}
	return (sub = *this);
}


Matrix& Matrix::operator*(const double k) { // Умножение матрицы на число
	Matrix multiply(rows, cols);
	for (unsigned int idx = 0; idx < rows * cols; idx++) {
		this->values[idx] *= k;
	}
	return multiply=*this;
}


Matrix& Matrix::operator/(const double k) { // Деление матрицы на число
	Matrix multiply(rows, cols);
	for (unsigned int idx = 0; idx < rows * cols; idx++) {
		this->values[idx] /= k;
	}
	return multiply = *this;
}


Matrix& Matrix::operator*=(const Matrix& m2) { // Умножение матриц
	Matrix multiplication(rows, m2.cols);
	for (unsigned int row = 0; row < multiplication.rows; row++) {
		for (unsigned int col = 0; col < multiplication.cols; col++) {
			double sum = 0;
			for (unsigned int k = 0; k < m2.rows; k++) {
				sum += values[row * cols + k] * m2.values[k * m2.cols + col];
			}
			multiplication.values[row * multiplication.cols + col] = sum;
		}
	}
	return (multiplication);
}



Matrix& Matrix::operator+=(const Matrix& matrix)
{
	for (int index = 0; index < rows*cols; ++index) {
			this->values[index] += matrix.values[index];
			
		}
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& matrix)
{
	for (int index = 0; index < rows * cols; ++index) {
		this->values[index] -= matrix.values[index];
	}
	return *this;
}


Matrix& Matrix::operator*=(const double k) { // Умножение матрицы на число
	for (unsigned int idx = 0; idx < rows * cols; idx++) {
		this->values[idx] *= k;
	}
	return *this;
}


Matrix& Matrix::operator/=(const double k) { // Деление матрицы на число
	for (unsigned int idx = 0; idx < rows * cols; idx++) {
		this->values[idx] /= k;
	}
	return *this;
}


//double& determinant(Matrix m, unsigned int size) {
//	double det = 0;
//	if (size == 0)
//		return 0;
//	if (size == 1)
//		return m[0];
//	else if (size == 2) {
//		return (m[0] * m[3] - m[2] * m[1]);
//	}
//	for (unsigned int idx = 0; idx < size; idx++) {
//		Matrix temp(size - 1, size - 1);
//		det += (pow(-1, idx) * m[idx] * determinant(temp.Minor(m,size,0,idx), size - 1));
//	}
//	return det;
//}


int main()
{
	/*srand(time(NULL));*/
	setlocale(LC_ALL, "ru");
	Matrix A(2, 3);
	Matrix B = A.transpose();
	cout << A;
}