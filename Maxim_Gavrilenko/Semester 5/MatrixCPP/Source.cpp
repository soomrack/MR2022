#include <iostream>
#include <ctime>
#include <windows.h>
#include <cmath>

const double EPS = 0.000001;

class Matrix_Exception : public std::exception
{
public:
	Matrix_Exception(const char* const &msg) : exception(msg)
	{}
};


Matrix_Exception NOTSQUARE("Error:the matrix must be square(should have nxn size)\n");
Matrix_Exception NOTEQUAL("Error: the matrix should have a same size\n");
Matrix_Exception MULTIPLYERROR("Error: first matrix cols not equal to second matrix row.\n");
Matrix_Exception ZERODIVISION("Error: divide by zero\n");
Matrix_Exception MEM_ERROR("Error: memory are not allocated\n");


class Matrix
{
private:
	unsigned int rows;
	unsigned int cols;
	double* values;

public:
	Matrix(unsigned int, unsigned int, double*);
	Matrix(unsigned int, unsigned int);
	Matrix();
	Matrix(const Matrix&);
	Matrix(Matrix&&) noexcept;
	~Matrix();
	
	
	void output();
	unsigned int getrow();
	unsigned int getcol();

	Matrix set_zero(); // ���������� �������� ������� ������
	Matrix fill_random(unsigned int);
	Matrix fill_from_array(double*);
	Matrix set_identity();		//�������������� ������� � ���������
	Matrix exponent(unsigned int);		//���������� ���������� �������
	Matrix set_transpose();				// ���������������� �������
	Matrix minor(const Matrix,const unsigned int, const unsigned int,const unsigned int);		//���������� ������ �������
	Matrix reverse(const Matrix, unsigned int);		//�������� �������
	double determinant(const Matrix, unsigned int);		//������������ ������� 

	Matrix& operator=(Matrix&&) noexcept;
	Matrix& operator=(const Matrix&);
	Matrix& operator+=(const Matrix&);
	Matrix& operator-=(const Matrix&);
	Matrix& operator*=(const Matrix&);
	Matrix& operator*=(const double);
	Matrix& operator/=(const double);

	Matrix operator+ (const Matrix&);
	Matrix operator- (const Matrix&);
	Matrix operator* (const Matrix&);
	Matrix operator* (const double);
	Matrix operator/ (const double);

	bool operator!=(const Matrix& mat);
	bool operator==(const Matrix& mat);
	friend std::ostream& operator<<(std::ostream& out, const Matrix m);

};


Matrix::Matrix() : rows(0), cols(0), values(nullptr) {}


Matrix::Matrix(const Matrix& mat) : rows(mat.rows), cols(mat.cols) 
{
	values = new double[rows * cols];
	if (!values) throw MEM_ERROR;
	memcpy(values, mat.values, rows * cols * sizeof(double));
}


Matrix::Matrix(unsigned int num_row, unsigned int num_col, double* value)
{
	rows = num_row;
	cols = num_col;
	for (unsigned int idx = 0; idx < rows*cols; idx++) {
		values[idx] = value[idx];
	}
}


Matrix::Matrix(unsigned int num_row, unsigned int num_col)
{
	rows = num_row;
	cols = num_col;
	values = new double[rows * cols];
	if (!values) throw MEM_ERROR;
}


Matrix::Matrix(Matrix&& mat) noexcept : values(mat.values), rows(mat.rows), cols(mat.cols) 
{
	mat.values = nullptr;
	mat.rows = 0;
	mat.cols = 0;
}


Matrix::~Matrix() 
{
	if (this->values != nullptr) {
		delete[] this->values;
	}
}
	

std::ostream& operator<<(std::ostream& out, const Matrix matrix) 
{
	{
		for (unsigned int row = 0; row < matrix.rows; row++)
		{
			for (unsigned int col = 0; col < matrix.cols; col++)
			{
				out << matrix.values[row * matrix.cols + col] << "\t";
			}
			out << std::endl;
		}
		out << std::endl;
		return(out);
	}
}


bool Matrix::operator==(const Matrix &A)
{
	if (this->cols != A.cols || this->rows != A.rows) return false;
	for (unsigned int idx = 0; idx < this->cols * this->rows; idx++) {
		if (abs(this->values[idx] - A.values[idx]) > EPS) return false;
	}
	return true;
}


bool Matrix::operator!=(const Matrix& mat) 
{
	return !(*this == mat);
}


Matrix Matrix::fill_random(unsigned int n = 10) 
{
	for (unsigned int index = 0; index < cols * rows; index++) {
		this->values[index] = double(rand() % n);
	}
	return (*this);
}


Matrix Matrix::fill_from_array(double* array)
{
	memcpy(values, array, rows * cols * sizeof(double));
	return *this;
}


Matrix Matrix::set_zero()
{
	for (unsigned int idx = 0; idx < this->rows * this->cols; idx++) {
		this->values[idx] = 0;
	}
	return *this;
}

Matrix Matrix::set_identity() 
{
	set_zero();
	for (unsigned int idx = 0; idx < this->cols * this->rows; idx += rows + 1) {
		this->values[idx] = 1.0;
	}
	return *this;
}


void Matrix::output()
{
	std::cout << *this << std::endl;
}


unsigned int Matrix::getrow()
{
	return (rows);
}


unsigned int Matrix::getcol()
{
	return (cols);
}


Matrix Matrix::minor(const Matrix matrix,const unsigned int size, const unsigned int row, const unsigned int col) 
{
	Matrix minor(size - 1, size - 1);
	unsigned int shiftrow = 0; //�������� ������� ������ � �������
	unsigned int shiftcol; //�������� ������� ������� � �������
	for (unsigned int rows = 0; rows < size - 1; rows++) {
		//���������� row-�� ������
		if (rows == row) {shiftrow = 1;} //��� ������ ��������� ������, 
		//������� ���� ����������, ������ �������� ��� �������� �������
		shiftcol = 0; //�������� �������� �������
		for (unsigned int cols = 0; cols < size - 1; cols++) {
			if (cols == col) {shiftcol = 1;}
			minor.values[rows * (size - 1) + cols] = matrix.values[(rows + shiftrow) 
				* size + (cols + shiftcol)];
		}
	}
	return minor;
}


Matrix Matrix::set_transpose() 
{
	Matrix trans(this->cols,this->rows);
	for (unsigned int row = 0; row < trans.rows; row++) {
		for (unsigned int col = 0; col < trans.cols; col++) { 
			trans.values[row * trans.cols + col] = this->values[col * trans.rows + row];
		}
	}
	*this = trans;
	return (*this);
}


Matrix Matrix::operator+(const Matrix& B) 
{
	Matrix add(*this);
	add += B;
return (add);
}


Matrix Matrix::operator-(const Matrix& B) 
{
	Matrix sub(*this);
	sub -= B;
	return (sub);
}


Matrix Matrix::operator*(const double k) // ��������� ������� �� �����
{ 
	Matrix multiply(*this);
	return (multiply*=k);
}


Matrix Matrix::operator*(const Matrix& B) 
{
	Matrix temp(*this);
	temp *= B;
	return (temp);
}


Matrix Matrix::operator/(const double k) // ������� ������� �� �����
{ 
	Matrix multiply(*this);
	multiply /= k;
	return multiply;
}


Matrix& Matrix::operator*=(const Matrix& matrix) // ��������� ������
{ 
	if (cols != matrix.rows) throw MULTIPLYERROR;
	Matrix multiplication(rows, matrix.cols);
	for (unsigned int row = 0; row < multiplication.rows; row++) {
		for (unsigned int col = 0; col < multiplication.cols; col++) {
			double sum = 0;
			for (unsigned int k = 0; k < matrix.rows; k++) {
				sum += values[row * cols + k] * matrix.values[k * matrix.cols + col];
				}
			multiplication.values[row * multiplication.cols + col] = sum;
		}
	}
	*this = multiplication;
	return (*this);
}


Matrix& Matrix::operator+=(const Matrix& matrix) 
{
	if (rows != matrix.rows || cols != matrix.cols) throw NOTEQUAL;
	for (unsigned int index = 0; index < rows * cols; ++index) {
		this->values[index] += matrix.values[index];
	}
	return *this;
}


Matrix& Matrix::operator-=(const Matrix& matrix) 
{
	if (rows != matrix.rows || cols != matrix.cols) throw NOTEQUAL;
	for (unsigned int index = 0; index < rows * cols; ++index) {
		this->values[index] -= matrix.values[index];
	}
	return *this;
}


Matrix& Matrix::operator*=(const double k) // ��������� ������� �� �����
{
	for (unsigned int idx = 0; idx < rows * cols; idx++) {
		this->values[idx] *= k;
	}
	return *this;
}


Matrix& Matrix::operator/=(const double k) // ������� ������� �� �����
{ 
	for (unsigned int idx = 0; idx < rows * cols; idx++) {
		this->values[idx] /= k;
	}
	return *this;
}


Matrix& Matrix::operator=(const Matrix& A) 
{
	if (this == &A) return *this;
	delete[] values;
	rows = A.rows;
	cols = A.cols;
	this->values = new double[rows * cols];
	if (!values) throw MEM_ERROR;
	memcpy(this->values, A.values, rows * cols * sizeof(double));
	return *this;
}


Matrix& Matrix::operator=(Matrix&& A) noexcept 
{
	if (this == &A) return *this;
	delete[] A.values;
	rows = A.rows;
	cols = A.cols;
	values = A.values;
	A.values = nullptr;
	return *this;
}


double Matrix::determinant(const Matrix matrix, unsigned int size) 
{
	if (matrix.rows != matrix.cols) throw NOTSQUARE;
	double det = 0;
	int k = 1;
	if (size == 0)
		return 0;
	if (size == 1)
		return matrix.values[0];
	if (size == 2) {
		return (matrix.values[0] * matrix.values[3] - matrix.values[2] * matrix.values[1]);
	}
	for (unsigned int idx = 0; idx < size; idx++) {
		det += k * matrix.values[idx] * determinant(minor(matrix, size, 0, idx), size - 1);
		k = -k;
	}
	return det;
}


Matrix Matrix::reverse(const Matrix matrix, const unsigned int size) // ������� ���������� �������� �������
{
	double d = determinant(matrix, size);
	if (matrix.rows != matrix.cols) throw NOTSQUARE;
	Matrix reverse(matrix.rows, matrix.cols);
	int k = 1;
	for (unsigned int row = 0; row < reverse.rows; row++) {
		for (unsigned int col = 0; col < reverse.cols; col++) {
			reverse.values[row * size + col] = k * determinant(minor(matrix, size, row, col), size - 1);
			k = -k;
		}
	}
	reverse.set_transpose();
	if (fabs(d) < EPS) throw ZERODIVISION;
	reverse /= d;
	return reverse;
}


Matrix Matrix::exponent(unsigned int n = 30) 
{
	if (rows != cols) throw NOTSQUARE;
	Matrix ex(rows,cols);
	Matrix temp(rows,cols);
	temp.set_identity();
	ex.set_identity();
	double fact = 1.0;
	for (unsigned int i = 1; i < n; i++) {
		fact *= i;
		temp *= (*this);
		ex += temp / fact;
	}
	return ex;
}


void test_add() 
{
	double data1[6] = { 3, 1, 2,
					   4, 5, 7 };
	double data2[6] = { 8, 2, 1,
					   -2, 2, 4 };
	double ans_d[6] = { 11, 3, 3,
					   2, 7, 11 };
	Matrix matrix1 = Matrix(2, 3).fill_from_array(data1);
	Matrix matrix2 = Matrix(2, 3).fill_from_array(data2);
	Matrix test_add = Matrix(2, 3).fill_from_array(ans_d);
	if (test_add != matrix1 + matrix2) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		std::cout<<"Addition test failed\n";
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		std::cout << "Addition test passed\n";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


void test_sub() 
{
	double data1[6] = { 3, 1, 2,
					   4, 5, 7 };
	double data2[6] = { 8, 2, 1,
					   -2, 2, 4 };
	double ans_d[6] = { -5, -1, 1,
					   6, 3, 3 };
	Matrix matrix1 = Matrix(2, 3).fill_from_array(data1);
	Matrix matrix2 = Matrix(2, 3).fill_from_array(data2);
	Matrix test_add = Matrix(2, 3).fill_from_array(ans_d);
	if (test_add != matrix1 - matrix2) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		std::cout << "Substraction test failed\n";
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		std::cout << "Substruction test passed\n";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


void test_mult() 
{
	double data1[9] = { 1, 7, 4,
					    0, 9, 4, 
						8, 8, 2 };
	double data2[9] = { 4, 5, 5,
					    1, 7, 1,
					    1, 5, 2};
	double ans_d[9] = { 15, 74, 20,
					    13, 83, 17,
					    42, 106, 52};
	Matrix matrix1 = Matrix(3, 3).fill_from_array(data1);
	Matrix matrix2 = Matrix(3, 3).fill_from_array(data2);
	Matrix test_add = Matrix(3, 3).fill_from_array(ans_d);
	if (test_add != matrix1 * matrix2) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		std::cout << "Multiplication test failed\n";
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		std::cout << "Multiplication test passed\n";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


void test_mult_k() 
{
	double data1[3] = { 1, 7, 4};
	double ans_d[3] = {3, 21, 12};
	Matrix matrix1 = Matrix(1, 3).fill_from_array(data1);
	Matrix test_add = Matrix(1, 3).fill_from_array(ans_d);
	if (test_add != matrix1 * 3) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		std::cout << "Multiplication test failed\n";
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		std::cout << "Multiplication test passed\n";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


void test_div_k() {
	double data1[3] = { 6, 21, 18 };
	double ans_d[3] = { 2, 7, 6 };
	Matrix matrix1 = Matrix(1,3).fill_from_array(data1);
	Matrix test_div = Matrix(1, 3).fill_from_array(ans_d);
	if (test_div != matrix1 / 3) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		std::cout << "Division test failed\n";
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		std::cout << "Division test passed\n";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


void test_det() 
{
	double data1[9] = { 1, 7, 4,
						0, 9, 4,
						8, 8, 2 };
	Matrix matrix1 = Matrix(3, 3).fill_from_array(data1);
	double determinant = matrix1.determinant(matrix1, matrix1.getrow());
	if (determinant != -78) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		std::cout << "Determinant test failed\n";
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		std::cout << "Determinant test passed\n";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


void test_rev() {
	double data1[9] = { 1, 7, 4,
						0, 9, 4,
						8, 8, 2 };
	double ans[9] = { 0.179487,  -0.230769, 0.102564,
					 -0.410256,	  0.384615, 0.0512821,
					 0.923077,   -0.615385, -0.115385 };
	Matrix matrix1 = Matrix(3, 3).fill_from_array(data1);
	Matrix test_rev = Matrix(3, 3).fill_from_array(ans);
	Matrix rev = matrix1.reverse(matrix1, matrix1.getrow());
	if (rev == test_rev) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		std::cout << "Reverse test passed\n";
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		std::cout << "Reverse test failed\n";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


void test_transpose()
{
	double data1[3] = { 1, 7, 4 };
	double ans[3] = {1,7,4};
	Matrix matrix1 = Matrix(3,1).fill_from_array(data1);
	Matrix test_trans = Matrix(1, 3).fill_from_array(ans);
	if (matrix1.set_transpose() == test_trans) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		std::cout << "Trasposition test passed\n";
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		std::cout << "Transposition test failed\n";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


void test_set_identity()
{
	double data1[9] = { 1, 7, 4,
						0, 9, 4,
						8, 8, 2 };
	double ans[9] = { 1,  0, 0,
					 0,	  1, 0,
					 0,   0, 1 };
	Matrix matrix1 = Matrix(3, 3).fill_from_array(data1);
	Matrix test_identity = Matrix(3, 3).fill_from_array(ans);
	if (matrix1.set_identity() == test_identity) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		std::cout << "SetIdentity test passed\n";
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		std::cout << "SetIdentity test failed\n";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


void test_set_zero()
{
	double data1[3] = { 1, 7, 4 };
	double ans[3] = { 0,0,0 };
	Matrix matrix1 = Matrix(3, 1).fill_from_array(data1);
	Matrix test_zero = Matrix(3, 1).fill_from_array(ans);
	if (matrix1.set_zero() == test_zero) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		std::cout << "SetZero test passed\n";
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		std::cout << "SetZero test failed\n";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


void test() {
	test_add();
	test_sub();
	test_div_k();
	test_mult_k();
	test_mult();
	test_det();
	test_rev();
	test_transpose();
	test_set_identity();
	test_set_zero();
}


int main()
{ 
	srand(time(NULL));
	setlocale(LC_ALL, "ru");

	double data[9] = { 1,7,4,0,9,4,8,8,2 };
	Matrix A = Matrix(3, 3).fill_from_array(data);
	Matrix B = Matrix(3, 3).fill_random();
	std::cout << "First Matrix\n" << A;
	std::cout << "Second Matrix\n" << B;
	
	try {
		std::cout << "Addiction of two matrix\n" << A + B;
		std::cout << "Subtraction of two matrix\n" << A - B;
	}
	catch (const Matrix_Exception& e)
	{
		std::cerr << "Caught: " << e.what() << std::endl;
		std::cerr << "Type: " << typeid(e).name() << std::endl;
	}

	try {
		std::cout << "Multiplication of two matrix\n" << A * B;
	}
	catch (const Matrix_Exception& e)
	{
		std::cerr << "Caught: " << e.what() << std::endl;
		std::cerr << "Type: " << typeid(e).name() << std::endl;
	}

	try {
		std::cout << "Determinant\n" << A.determinant(A, A.getrow()) << std::endl;
		std::cout << "Reverse Matrix\n" << A.reverse(A, A.getrow()) << std::endl;
		std::cout << "Exponent Matrix\n" << A.exponent();
	}
	catch (Matrix_Exception& e)
	{
		std::cerr << "Caught: " << e.what() << std::endl;
		std::cerr << "Type: " << typeid(e).name() << std::endl;
	}

	test();
}