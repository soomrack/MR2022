#include <iostream>
#include <windows.h>
#include <cmath>
#include<math.h>

const double EPS = 0.00000001;  // prisicion for stop 

class Matrix_Exception : public std::exception{
public:
	Matrix_Exception(const char* const& massage) : exception(massage)
	{}
};


Matrix_Exception MULTIPLYERROR("Error: first matrix cols is not equal with second matrix row\n");
Matrix_Exception NOTSQUARE("Error:the matrix is not square(should have nxn size)\n");
Matrix_Exception NOTEQUAL("Error: the matrix should have a same size\n");
Matrix_Exception ZERODIVISION("Error: divide by zero\n");
Matrix_Exception MEM_ERROR("Error: memory are not allocated\n");
Matrix_Exception DEGENERACY("Error: matrix is degeneracy\n");



class Matrix{
private:
	int rows;
	int cols;
	double* values;

public:
	Matrix();  // empty constructor matrix
	Matrix(int rows, int cols);
	Matrix(int rows, int cols, double* values);

	Matrix(const Matrix& other_matrix);
	Matrix(Matrix&& M) noexcept;

	void print_value(const std::string massage);
	int get_row() { return (rows); }
	int get_col() { return (rows); }


	Matrix& operator=(Matrix&& other) noexcept;
	Matrix& operator=(const Matrix& other);
	Matrix& operator+=(const Matrix& matrix);
	Matrix& operator-=(const Matrix& matrix);
	Matrix& operator*=(const Matrix& matrix);
	Matrix& operator*=(const double scalar);
	Matrix& operator/=(const double scalar);

	Matrix operator+ (const Matrix& matrix);
	Matrix operator- (const Matrix& matrix);
	Matrix operator* (const Matrix& matrix);
	Matrix operator* (const double scalar);
	Matrix operator/ (const double scalar);

	bool operator!=(const Matrix& other);
	bool operator==(const Matrix& other);

	Matrix fill_from_array(double* array);
	Matrix E();
	Matrix truncated(const int del_row, const int del_col, Matrix M); // retun Matrix without deleted row and col
	double determinant(const Matrix matrix);
	Matrix transpose();
	Matrix reverse(const Matrix);
	Matrix exponent(int);

	~Matrix();
};


Matrix::Matrix(): rows(0), cols(0), values(nullptr) {}


Matrix::Matrix(int rows, int cols, double* values){
	this->rows = rows;
	this->cols = cols;
	for (int idx = 0; idx < rows * cols; idx++) {
		this->values[idx] = values[idx];
	}
}


Matrix::Matrix(int rows, int cols){
	this->rows = rows;
	this->cols = cols;
	values = new double[rows * cols];
	if (!values) throw MEM_ERROR;
}


Matrix::Matrix(const Matrix& other_matrix):rows(other_matrix.rows), cols(other_matrix.cols) {
	values = new double[rows * cols];
	if (!values) throw MEM_ERROR;
	memcpy(values, other_matrix.values, rows * cols * sizeof(double));
}


Matrix::Matrix(Matrix&& other_matrix) noexcept : values(other_matrix.values), rows(other_matrix.rows), cols(other_matrix.cols){
	other_matrix.values = nullptr;
	other_matrix.rows = 0;
	other_matrix.cols = 0;
}


Matrix& Matrix::operator=(Matrix&& other) noexcept{
	if (this == &other) return *this;
	delete[] other.values;
	rows = other.rows;
	cols = other.cols;
	values = other.values;
	other.values = nullptr;
	return *this;
}


Matrix& Matrix::operator=(const Matrix& other){
	if (this == &other) return *this;
	delete[] values;
	rows = other.rows;
	cols = other.cols;
	this->values = new double[rows * cols];
	if (!values) throw MEM_ERROR;
	memcpy(this->values, other.values, rows * cols * sizeof(double));
	return *this;
}


Matrix& Matrix::operator+=(const Matrix& matrix){
	if (rows != matrix.rows || cols != matrix.cols) throw NOTEQUAL;

	for (int idx = 0; idx < rows * cols; idx++) {
		this->values[idx] += matrix.values[idx];
	}
	return *this;
}


Matrix& Matrix::operator-=(const Matrix& matrix){
	if (rows != matrix.rows || cols != matrix.cols) throw NOTEQUAL;

	for (int idx = 0; idx < rows * cols; ++idx) {
		this->values[idx] -= matrix.values[idx];
	}
	return *this;
}


Matrix& Matrix::operator*=(const Matrix& matrix) {
	if (cols != matrix.rows) throw MULTIPLYERROR;

	Matrix mul(rows, matrix.cols);
	for (int row = 0; row < mul.rows; row++) {
		for (int col = 0; col < mul.cols; col++) {
			double sum = 0;
			for (int idx = 0; idx < matrix.rows; idx++) {
				sum += values[row * cols + idx] * matrix.values[idx * matrix.cols + col];
			}
			mul.values[row * mul.cols + col] = sum;
		}
	}
	*this = mul;
	return (*this);
}


Matrix& Matrix::operator*=(const double scalar) {
	for (int idx = 0; idx < rows * cols; idx++) {
		this->values[idx] *= scalar;
	}
	return *this;
}

	
Matrix& Matrix::operator/=(const double scalar) {
	for (int idx = 0; idx < rows * cols; idx++) {
		this->values[idx] /= scalar;
	}
	return *this;
}


Matrix Matrix::operator*(const double scalar){
	Matrix mul(*this);
	return (mul *= scalar);
}


Matrix Matrix::operator*(const Matrix& matrix){
	Matrix mul(*this);
	mul *= matrix;
	return (mul);
}


Matrix Matrix::operator/(const double scalar){
	Matrix dev(*this);
	dev /= scalar;
	return dev;
}


bool Matrix::operator==(const Matrix& other){
	if (cols != other.cols || rows != other.rows) return false;

	for (int idx = 0; idx < cols * rows; idx++) {
		if (abs(values[idx] - other.values[idx]) > EPS) return false;
	}
	return true;
}


bool Matrix::operator!=(const Matrix& other){
	if (cols != other.cols || rows != other.rows) return true;

	for (int idx = 0; idx < cols * rows; idx++) {
		if (abs(values[idx] - other.values[idx]) > EPS) return true;
	}
	return false;
}


Matrix Matrix::operator+(const Matrix& matrix){
	Matrix add(*this);
	add += matrix;
	return (add);
}


Matrix Matrix::operator-(const Matrix& matrix){
	Matrix sub(*this);
	sub -= matrix;
	return (sub);
}


Matrix Matrix::fill_from_array(double* array){
	memcpy(values, array, rows * cols * sizeof(double));
	return *this;
}


Matrix Matrix::E(){
	for (int idx = 0; idx < this->rows * this->cols; idx++) {
		this->values[idx] = 0;
	}
	for (int idx = 0; idx < this->cols * this->rows; idx += rows + 1) {
		this->values[idx] = 1.0;
	}
	return *this;
}


void Matrix::print_value(const std::string massage = "Output matrix:") {
	std::cout << massage << std::endl;
	for (int row = 0; row < rows; row++){
		for (int col = 0; col < cols; col++){
			std::cout << values[row * cols + col] << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}


Matrix Matrix::truncated(const int del_row, const int del_col, const Matrix matrix) {
	Matrix trun(matrix.rows - 1, matrix.cols - 1);
	int row_t = 0;  int col_t = 0;
	for (int row_M = 0; row_M < matrix.rows; row_M++) {
		if (row_M == del_row) continue;  // in cycle just skip deleted col and row
		for (int col_M = 0; col_M < matrix.cols; col_M++) {
			trun.values[row_t * trun.cols + col_t] =
				matrix.values[row_M * matrix.cols + col_M];
			col_t++;
		}
		row_t++;
		col_t = 0;
	}
	return trun;
}

double Matrix::determinant(Matrix matrix){
	if (matrix.rows != matrix.cols) throw NOTSQUARE;

	double det = 0;
	int sign = 1;
	if (matrix.cols == 1)  // first order determinant
		return matrix.values[0];
	if (matrix.cols == 2)  // second order determinant
		return (matrix.values[0] * matrix.values[3] - matrix.values[2] * matrix.values[1]);
	for (int col = 0; col < matrix.cols; col++) {
		Matrix trun = truncated(0, col, matrix);
		det += (matrix.values[col] * sign * determinant(trun));
		sign *= -1;
	}
	return det;
}


Matrix Matrix::transpose(){
	Matrix trans(this->cols, this->rows);
	for (int row = 0; row < trans.rows; row++) {
		for (int col = 0; col < trans.cols; col++) {
			trans.values[row * trans.cols + col] = this->values[col * trans.rows + row];
		}
	}
	*this = trans;
	return (*this);
}


Matrix Matrix::reverse(const Matrix A) {
	if (A.rows != A.cols) throw NOTSQUARE;

	Matrix inver(A.rows, A.cols);
	double det = determinant(A);
	if (det == 0) throw DEGENERACY; 

	for (int row = 0; row < A.rows; row++) {
		for (int col = 0; col < A.cols; col++) {
			Matrix trun = truncated(row, col, A);
			int idx = A.rows * col + row;
			inver.values[idx] = pow(-1, idx) * determinant(trun) / det;
		}
	}
	return inver;
}


Matrix Matrix::exponent(int iteration_count = 50){
	if (rows != cols) throw NOTSQUARE;
	Matrix ex(rows, cols);
	Matrix tmp(rows, cols);
	tmp.E();
	ex.E();
	double fact = 1.0;
	for (int idx = 1; idx < iteration_count; idx++) {
		fact *= idx;
		tmp *= (*this);
		ex += tmp / fact;
	}
	return ex;
}


Matrix::~Matrix() {
	delete[] this->values;
}





void test_add(){
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
		std::cerr << "Addition test failed\n";
	}
	else {

		std::cerr << "Addition test passed\n";
	}
}


void test_sub(){
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
		std::cerr << "Substraction test failed\n";
	}
	else {
		std::cerr << "Substruction test passed\n";
	}
}


void test_mult(){
	double data1[9] = { 1, 7, 4,
						0, 9, 4,
						8, 8, 2 };
	double data2[9] = { 4, 5, 5,
						1, 7, 1,
						1, 5, 2 };
	double ans_d[9] = { 15, 74, 20,
						13, 83, 17,
						42, 106, 52 };
	Matrix matrix1 = Matrix(3, 3).fill_from_array(data1);
	Matrix matrix2 = Matrix(3, 3).fill_from_array(data2);
	Matrix test_add = Matrix(3, 3).fill_from_array(ans_d);
	if (test_add != matrix1 * matrix2) {
		std::cerr << "Multiplication test failed\n";
	}
	else {
		std::cerr << "Multiplication test passed\n";
	}
}


void test_mult_scalar(){
	double data1[3] = { 1, 7, 4 };
	double ans_d[3] = { 3, 21, 12 };
	Matrix matrix1 = Matrix(1, 3).fill_from_array(data1);
	Matrix test_add = Matrix(1, 3).fill_from_array(ans_d);
	if (test_add != matrix1 * 3) {
		std::cerr << "Multiplication test failed\n";
	}
	else {
		std::cerr << "Multiplication test passed\n";
	}
}


void test_det(){
	double data1[9] = { 1, 7, 4,
						0, 9, 4,
						8, 8, 2 };
	Matrix matrix1 = Matrix(3, 3).fill_from_array(data1);
	double determinant = matrix1.determinant(matrix1);
	if (determinant != -78) {
		std::cerr << "Determinant test failed\n";
	}
	else {
		std::cerr << "Determinant test passed\n";
	}
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
	Matrix rev = matrix1.reverse(matrix1);
	if (rev == test_rev) {
		std::cerr << "Reverse test passed\n";
	}
	else {
		std::cerr << "Reverse test failed\n";
	}
}


void test_transpose(){
	double data1[3] = { 1, 7, 4 };
	double ans[3] = { 1,7,4 };
	Matrix matrix1 = Matrix(3, 1).fill_from_array(data1);
	Matrix test_trans = Matrix(1, 3).fill_from_array(ans);
	if (matrix1.transpose() == test_trans) {
		std::cerr << "Trasposition test passed\n";
	}
	else {
		std::cerr << "Transposition test failed\n";
	}
}



void ALL_TESTS() {
	test_add();
	test_sub();
	test_mult_scalar();
	test_mult();
	test_det();
	test_rev();
	test_transpose();
}


int main(){
	double data1[4] = { 1,2,3,4};
	double data2[4] = { 5,6,7,7};
	Matrix A = Matrix(2, 2).fill_from_array(data1);
	Matrix B = Matrix(2, 2).fill_from_array(data2);
	A.print_value("First Matrix\n");
	B.print_value("Second Matrix\n");

	try {
		Matrix sum = A + B;
		sum.print_value("Addiction of the two matrix\n");
		Matrix sub = A - B;
		sub.print_value("Subtraction of the two matrix\n");
	}
	catch (const Matrix_Exception& e)
	{
		std::cerr << "Caught: " << e.what() << std::endl;
		std::cerr << "Type: " << typeid(e).name() << std::endl;
	}

	try {
		Matrix mul = A * B;
		mul.print_value("Multiplication of two matrix\n");
	}
	catch (const Matrix_Exception& e)
	{
		std::cerr << "Caught: " << e.what() << std::endl;
		std::cerr << "Type: " << typeid(e).name() << std::endl;
	}

	try {
		std::cout << "Determinant\n" << A.determinant(A) << std::endl;
		Matrix rev = A.reverse(A);
		rev.print_value("Reverse Matrix\n");
		Matrix exp = A.exponent();
		exp.print_value("Exponent Matrix\n");
	}
	catch (Matrix_Exception& e)
	{
		std::cerr << "Caught: " << e.what() << std::endl;
		std::cerr << "Type: " << typeid(e).name() << std::endl;
	}

	ALL_TESTS();
}