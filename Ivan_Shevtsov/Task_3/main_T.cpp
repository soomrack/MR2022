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


Matrix_Exception MULTIPLYERROR("ERROR: first matrix cols is not equal with second matrix row\n");
Matrix_Exception NOTSQUARE("ERROR:the matrix is not square(should have nxn size)\n");
Matrix_Exception NOTEQUAL("ERROR: the matrix should have a same size\n");
Matrix_Exception ZERODIVISION("ERROR: divide by zero\n");
Matrix_Exception MEM_ERROR("ERROR: memory are not allocated\n");
Matrix_Exception DEGENERACY("ERROR: matrix is degeneracy\n");


template<typename T>
class Matrix{
protected:
	int rows;
	int cols;
	T* values;

public:
	static_assert(
		std::is_same<double, T>::value ||
		std::is_same<float, T>::value ||
		std::is_same<long double, T>::value,
		"value must be double");
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
	Matrix exponent();

	~Matrix();
};

template <typename T>
Matrix<T>::Matrix(): rows(0), cols(0), values(nullptr) {}


template <typename T>
Matrix<T>::Matrix(int rows, int cols, double* values){
	this->rows = rows;
	this->cols = cols;
	for (int idx = 0; idx < rows * cols; idx++) {
		this->values[idx] = values[idx];
	}
}

template <typename T>
Matrix<T>::Matrix(int rows, int cols){
	this->rows = rows;
	this->cols = cols;
	values = new double[rows * cols];
	if (!values) throw MEM_ERROR;
}


template <typename T>
Matrix<T>::Matrix(const Matrix& other_matrix){
	cols = matrix.cols;
	rows = matrix.rows;
	values = new T[rows * cols];
	memcpy(values, matrix.values, rows * cols * sizeof(T));
}


template <typename T>
Matrix<T>::Matrix(Matrix<T>&& matrix) {
	cols = matrix.cols;
	rows = matrix.rows;
	values = matrix.values;
	matrix.values = nullptr;
}


template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix&& other) noexcept{
	if (this == &other) return *this;
	delete[] other.values;
	rows = other.rows;
	cols = other.cols;
	values = other.values;
	other.values = nullptr;
	return *this;
}


template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& other){
	if (this == &other) return *this;
	delete[] values;
	rows = other.rows;
	cols = other.cols;
	this->values = new double[rows * cols];
	if (!values) throw MEM_ERROR;
	memcpy(this->values, other.values, rows * cols * sizeof(double));
	return *this;
}

template <typename T>

Matrix<T>& Matrix<T>::operator+=(const Matrix& matrix){
	if (rows != matrix.rows || cols != matrix.cols) throw NOTEQUAL;

	for (int idx = 0; idx < rows * cols; idx++) {
		this->values[idx] += matrix.values[idx];
	}
	return *this;
}


template <typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix& matrix){
	if (rows != matrix.rows || cols != matrix.cols) throw NOTEQUAL;

	for (int idx = 0; idx < rows * cols; ++idx) {
		this->values[idx] -= matrix.values[idx];
	}
	return *this;
}


template <typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix& matrix) {
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


template <typename T>
Matrix<T>& Matrix<T>::operator*=(const double scalar) {
	for (int idx = 0; idx < rows * cols; idx++) {
		this->values[idx] *= scalar;
	}
	return *this;
}

	
template <typename T>
Matrix<T>& Matrix<T>::operator/=(const double scalar) {
	for (int idx = 0; idx < rows * cols; idx++) {
		this->values[idx] /= scalar;
	}
	return *this;
}


template <typename T>
Matrix<T> Matrix<T>::operator*(const double scalar){
	Matrix mul(*this);
	return (mul *= scalar);
}


template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix& matrix){
	Matrix mul(*this);
	mul *= matrix;
	return (mul);
}


template <typename T>
Matrix<T> Matrix<T>::operator/(const double scalar){
	Matrix dev(*this);
	dev /= scalar;
	return dev;
}


template <typename T>
bool Matrix<T>::operator==(const Matrix& other){
	if (cols != other.cols || rows != other.rows) return false;

	for (int idx = 0; idx < cols * rows; idx++) {
		if (abs(values[idx] - other.values[idx]) > EPS) return false;
	}
	return true;
}


template <typename T>
bool Matrix<T>::operator!=(const Matrix& other){
	if (cols != other.cols || rows != other.rows) return true;

	for (int idx = 0; idx < cols * rows; idx++) {
		if (abs(values[idx] - other.values[idx]) > EPS) return true;
	}
	return false;
}


template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix& matrix){
	Matrix add(*this);
	add += matrix;
	return (add);
}


template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix& matrix){
	Matrix sub(*this);
	sub -= matrix;
	return (sub);
}


template <typename T>
Matrix<T> Matrix<T>::fill_from_array(double* array){
	memcpy(values, array, rows * cols * sizeof(double));
	return *this;
}


template <typename T>
Matrix<T> Matrix<T>::E(){
	for (int idx = 0; idx < this->rows * this->cols; idx++) {
		this->values[idx] = 0;
	}
	for (int idx = 0; idx < this->cols * this->rows; idx += rows + 1) {
		this->values[idx] = 1.0;
	}
	return *this;
}


template <typename T>
void Matrix<T>::print_value(const std::string massage) {
	std::cout << massage << std::endl;
	for (int row = 0; row < rows; row++){
		for (int col = 0; col < cols; col++){
			std::cout << values[row * cols + col] << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}


template <typename T>
Matrix<T> Matrix<T>::truncated(const int del_row, const int del_col, const Matrix matrix) {
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


template <typename T>
double Matrix<T>::determinant(Matrix matrix){
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


template <typename T>
Matrix<T> Matrix<T>::transpose(){
	Matrix trans(this->cols, this->rows);
	for (int row = 0; row < trans.rows; row++) {
		for (int col = 0; col < trans.cols; col++) {
			trans.values[row * trans.cols + col] = this->values[col * trans.rows + row];
		}
	}
	*this = trans;
	return (*this);
}


template <typename T>
Matrix<T> Matrix<T>::reverse(const Matrix A) {
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


template <typename T>
Matrix<T> Matrix<T>::exponent(){
	if (rows != cols) throw NOTSQUARE;

	int iteration_count = 50;
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


template <typename T>
Matrix<T>::~Matrix() {
	delete[] this->values;
}





void test_add(){
	double test_matrix1[9] = { 1, 2, 3,
							   4, 5, 6,
						       7, 8, 9};
	double test_matrix2[9] = { 10, 11, 12,
							   13, 14, 15,
							   11, 3, 3};
	double answer[9] = { 11, 13, 15,
						 17, 19, 21,
						 18, 11, 12};
	Matrix<double> matrix1 = Matrix<double>(3, 3).fill_from_array(test_matrix1);
	Matrix<double> matrix2 = Matrix<double>(3, 3).fill_from_array(test_matrix2);
	Matrix<double> test_add = Matrix<double>(3, 3).fill_from_array(answer);
	if (test_add != matrix1 + matrix2) {
		std::cerr << "Addition test failed\n";
	}
	else {
		std::cerr << "Addition test PASSED\n";
	}
}


void test_sub(){
	double test_matrix1[8] = { 4, 7, 8, 12, 27, 3, 22,13 };
	double test_matrix2[8] = { 1, 3, 1, 3, 20, 3, 15,12 };
	double answer[8] = { 3, 4, 7, 9, 7, 0, 7,1 };
	Matrix<double> matrix1 = Matrix<double>(1, 8).fill_from_array(test_matrix1);
	Matrix<double> matrix2 = Matrix<double>(1, 8).fill_from_array(test_matrix2);
	Matrix<double> test_add = Matrix<double>(1, 8).fill_from_array(answer);
	if (test_add != matrix1 - matrix2) {
		std::cerr << "Substraction test failed\n";
	}
	else {
		std::cerr << "Substruction test PASSED\n";
	}
}


void test_mult(){
	double test_matrix1[6] = { 1, 2,3,4,5,6 };
	double test_matrix2[6] = { 7,8,9,1,2,3 };
	double answer[4] = { 31,19,85,55 };
	Matrix<double> matrix1 = Matrix<double>(3, 3).fill_from_array(test_matrix1);
	Matrix<double> matrix2 = Matrix<double>(3, 3).fill_from_array(test_matrix2);
	Matrix<double> test_add = Matrix<double>(3, 3).fill_from_array(answer);
	if (test_add != matrix1 * matrix2) {
		std::cerr << "Multiplication test failed\n";
	}
	else {
		std::cerr << "Multiplication test PASSED\n";
	}
}


void test_mult_scalar(){
	double test_matrix1[3] = { 1, 2, 3 };
	double answer[3] = { 3, 6, 9 };
	Matrix<double> matrix1 = Matrix<double>(1, 3).fill_from_array(test_matrix1);
	Matrix<double> test_add = Matrix<double>(1, 3).fill_from_array(answer);
	if (test_add != matrix1 * 3) {
		std::cerr << "Multiplication test failed\n";
	}
	else {
		std::cerr << "Multiplication test PASSED\n";
	}
}


void test_det(){
	double test_matrix1[9] = { 1, 7, 4,
						0, 9, 4,
						8, 8, 2 };
	Matrix<double> matrix1 = Matrix<double>(3, 3).fill_from_array(test_matrix1);
	double determinant = matrix1.determinant(matrix1);
	if (determinant != -78) {
		std::cerr << "Determinant test failed\n";
	}
	else {
		std::cerr << "Determinant test PASSED\n";
	}
}


void test_rev() {
	double test_matrix1[9] = { 1, 7, 4,
						0, 9, 4,
						8, 8, 2 };
	double ans[9] = { 0.179487,  -0.230769, 0.102564,
					 -0.410256,	  0.384615, 0.0512821,
					 0.923077,   -0.615385, -0.115385 };
	Matrix<double> matrix1 = Matrix<double>(3, 3).fill_from_array(test_matrix1);
	Matrix<double> test_rev = Matrix<double>(3, 3).fill_from_array(ans);
	Matrix<double> rev = matrix1.reverse(matrix1);
	if (rev == test_rev) {
		std::cerr << "Reverse test PASSED\n";
	}
	else {
		std::cerr << "Reverse test failed\n";
	}
}


void test_transpose(){
	double test_matrix1[6] = { 1,2,3,4,5,6 };
	double ans[6] = { 1,4,2,5,4,6 };
	Matrix<double> matrix1 = Matrix<double>(2, 3).fill_from_array(test_matrix1);
	Matrix<double> test_trans = Matrix<double>(3, 2).fill_from_array(ans);
	if (matrix1.transpose() == test_trans) {
		std::cerr << "Trasposition test PASSED\n";
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
	double test_matrix1[4] = { 1,2,3,4};
	double test_matrix2[4] = { 5,6,7,7};
	Matrix<double> A = Matrix<double>(2, 2).fill_from_array(test_matrix1);
	Matrix<double> B = Matrix<double>(2, 2).fill_from_array(test_matrix2);
	A.print_value("First Matrix\n");
	B.print_value("Second Matrix\n");

	try {
		Matrix<double> sum = A + B;
		sum.print_value("Addiction of the two matrix\n");
		Matrix<double> sub = A - B;
		sub.print_value("Subtraction of the two matrix\n");
	}
	catch (const Matrix_Exception& e)
	{
		std::cerr << "Caught: " << e.what() << std::endl;
		std::cerr << "Type: " << typeid(e).name() << std::endl;
	}

	try {
		Matrix<double> mul = A * B;
		mul.print_value("Multiplication of two matrix\n");
	}
	catch (const Matrix_Exception& e)
	{
		std::cerr << "Caught: " << e.what() << std::endl;
		std::cerr << "Type: " << typeid(e).name() << std::endl;
	}

	try {
		std::cout << "Determinant\n" << A.determinant(A) << std::endl;
		Matrix<double> rev = A.reverse(A);
		rev.print_value("Reverse Matrix\n");
		Matrix<double> exp = A.exponent();
		exp.print_value("Exponent Matrix\n");
	}
	catch (Matrix_Exception& e)
	{
		std::cerr << "Caught: " << e.what() << std::endl;
		std::cerr << "Type: " << typeid(e).name() << std::endl;
	}

	ALL_TESTS();
}
