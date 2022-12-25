#include <iostream>
#include <windows.h>
#include <cmath>
#include<math.h>


const double EPS = 0.00000001;  // prisicion for stop 

class Matrix_Exception : public std::exception {
public:
	Matrix_Exception(const char* const& massage) : exception(massage)
	{
	
	}
};


Matrix_Exception MULTIPLYERROR("ERROR: first matrix cols must have equal with second matrix row\n");
Matrix_Exception NOTSQUARE("ERROR:the matrix should have nxn size\n");
Matrix_Exception NOTEQUAL("ERROR: the matrix should have the same size\n");
Matrix_Exception ZERODIVISION("ERROR: divide by zero\n");
Matrix_Exception MEM_ERROR("ERROR: memory are not allocated\n");
Matrix_Exception DEGENERACY("ERROR: matrix is degeneracy\n");


template<typename T>
class Matrix {
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
	Matrix truncated(const int del_row, const int del_col); // retun Matrix without deleted row and col
	double determinant();
	Matrix transpose();
	Matrix reverse();
	Matrix exponent();

	~Matrix();
};

template <typename T>
Matrix<T>::Matrix() : rows(0), cols(0), values(nullptr) {}


template <typename T>
Matrix<T>::Matrix(int rows, int cols, double* values) {
	this->rows = rows;
	this->cols = cols;
	this->values = new double[rows * cols];
	for (int idx = 0; idx < rows * cols; idx++) {
		this->values[idx] = values[idx];
	}
}

template <typename T>
Matrix<T>::Matrix(int rows, int cols) {
	this->rows = rows;
	this->cols = cols;
	values = new double[rows * cols];
}


template <typename T>
Matrix<T>::Matrix(const Matrix& other_matrix) {
	cols = other_matrix.cols;
	rows = other_matrix.rows;
	values = new T[rows * cols];

	memcpy(values, other_matrix.values, rows * cols * sizeof(T));
}


template <class T>
Matrix<T>::Matrix(Matrix<T>&& mat) noexcept {
	this->values = mat.values;
	this->rows = mat.rows;
	this->cols = mat.cols;
	mat.values = nullptr;
	mat.rows = 0;
	mat.cols = 0;
}


template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix&& other) noexcept {
	if (this == &other) return *this;
	rows = other.rows;
	cols = other.cols;
	values = other.values;
	other.values = nullptr;
	return *this;
}


template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& other) {
	if (this == &other) return *this;
	delete[] values;
	rows = other.rows;
	cols = other.cols;
	this->values = new double[rows * cols];

	memcpy(this->values, other.values, rows * cols * sizeof(double));
	return *this;
}

template <typename T>

Matrix<T>& Matrix<T>::operator+=(const Matrix& matrix) {
	if (rows != matrix.rows || cols != matrix.cols) throw NOTEQUAL;

	for (int idx = 0; idx < rows * cols; idx++) {
		this->values[idx] += matrix.values[idx];
	}
	return *this;
}


template <typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix& matrix) {
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
	if (scalar == 0) throw ZERODIVISION;

	for (int idx = 0; idx < rows * cols; idx++) {
		this->values[idx] /= scalar;
	}
	return *this;
}


template <typename T>
Matrix<T> Matrix<T>::operator*(const double scalar) {
	Matrix mul(*this);
	return (mul *= scalar);
}


template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix& matrix) {
	Matrix mul(*this);
	mul *= matrix;
	return (mul);
}


template <typename T>
Matrix<T> Matrix<T>::operator/(const double scalar) {
	if (scalar == 0) throw ZERODIVISION;

	Matrix dev(*this);
	dev /= scalar;
	return dev;
}


template <typename T>
bool Matrix<T>::operator==(const Matrix& other) {
	if (cols != other.cols || rows != other.rows) return false;

	for (int idx = 0; idx < cols * rows; idx++) {
		if (abs(values[idx] - other.values[idx]) > EPS) return false;
	}
	return true;
}


template <typename T>
bool Matrix<T>::operator!=(const Matrix& other) {
	if (cols != other.cols || rows != other.rows) return true;

	for (int idx = 0; idx < cols * rows; idx++) {
		if (abs(values[idx] - other.values[idx]) > EPS) return true;
	}
	return false;
}


template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix& matrix) {
	Matrix add(*this);
	add += matrix;
	return (add);
}


template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix& matrix) {
	Matrix sub(*this);
	sub -= matrix;
	return (sub);
}


template <typename T>
Matrix<T> Matrix<T>::fill_from_array(double* array) {
	memcpy(values, array, rows * cols * sizeof(double));
	return *this;
}


template <typename T>
Matrix<T> Matrix<T>::E() {
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
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			std::cout << values[row * cols + col] << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

template <typename T>
Matrix<T>::~Matrix() {
	delete[] this->values;
}


template <typename T>
class Memory : public Matrix<T> {
private:
	int memory_size;
	int id;
public:
	static int count;
	static int total_memory;  // common memory var

	Memory();
	Memory(int cols, int rows);
	Memory(const Memory& matrix);
	Memory(Memory&& matrix) noexcept;

	Memory& operator=(Memory&& matrix) noexcept;
	Memory& operator=(const Memory& matrix);

	void print_memory();
	int getid() { return id; }

	~Memory();
};

template <typename T>
int Memory<T>::total_memory = 0;  // static var inicialization

template <typename T>
int Memory<T>::count = 0;  // static var inicialization

template <typename T>
Memory<T>::Memory() : Matrix<T>() {
	this->memory_size = 0;
	count++;
	id = count;
}


template <typename T>
Memory<T>::Memory(int cols, int rows) : Matrix<T>(cols, rows) {
	this->memory_size = cols * rows * sizeof(T);
	this->total_memory += this->memory_size;
	count++;
	id = count;
}


template <typename T>
Memory<T>::Memory(const Memory& matrix) : Matrix<T>(matrix) {
	this->memory_size = matrix.memory_size;
	this->total_memory += this->memory_size;
	count++;
	id = count;
}


template <typename T>
Memory<T>::Memory(Memory&& matrix) noexcept : Matrix<T>(matrix) {
	this->memory_size = matrix.memory_size;
	matrix.memory_size = 0;
	count++;
	id = count;
}


template <typename T>
Memory<T>::~Memory() {
	print_memory();
}

template <typename T>
Memory<T>& Memory<T>::operator=(Memory&& other) noexcept {
	if (this == &other) return *this;
	
	this->rows = other.rows;
	this->cols = other.cols;
	this->values = other.values;

	this->total_memory = -this->memory_size + other.memory_size;  // new operator's memory block
	this->memory_size = other.memory_size;
	other.memory_size = 0;

	other.values = nullptr;
	return *this;
}


template <typename T>
Memory<T>& Memory<T>::operator=(const Memory& matrix) {
	if (this == &matrix) {
		return *this;
	}
	delete[] this->values;
	this->rows = matrix.rows;
	this->cols = matrix.cols;
	this->values = new T[this->rows * this->cols];
	memcpy(this->values, matrix.values, this->rows * this->cols * sizeof(T));


	this->total_memory -= this->memory_size;  // new operator's memory block
	this->memory_size = matrix.memory_size;
	this->total_memory += matrix.memory_size;

	return *this;

}


template <typename T>
void Memory<T>::print_memory() {
	std::cerr << id << " matrix deconstucted" << std::endl;
	std::cerr << "Memory size(bytes): " << this->memory_size << std::endl;
	std::cerr << "Total memory(bytes): " << Memory::total_memory << std::endl;
}


void test_add() {
	double test_matrix1[9] = { 1, 2, 3,
							   4, 5, 6,
							   7, 8, 9 };
	double test_matrix2[9] = { 10, 11, 12,
							   13, 14, 15,
							   11, 3, 3 };
	double answer[9] = { 11, 13, 15,
						 17, 19, 21,
						 18, 11, 12 };
	Matrix<double> matrix1 = Matrix<double>(3, 3).fill_from_array(test_matrix1);
	Matrix<double> matrix2 = Matrix<double>(3, 3).fill_from_array(test_matrix2);
	Matrix<double> test_add = Matrix<double>(3, 3).fill_from_array(answer);
	if (test_add != matrix1 + matrix2) {
		std::cerr << "Addition test FAILED\n";
	}
	else {
		std::cerr << "Addition test PASSED\n";
	}
}


void test_sub() {
	double test_matrix1[8] = { 4, 7, 8, 12, 27, 3, 22,13 };
	double test_matrix2[8] = { 1, 3, 1, 3, 20, 3, 15,12 };
	double answer[8] = { 3, 4, 7, 9, 7, 0, 7,1 };
	Matrix<double> matrix1 = Matrix<double>(1, 8).fill_from_array(test_matrix1);
	Matrix<double> matrix2 = Matrix<double>(1, 8).fill_from_array(test_matrix2);
	Matrix<double> test_add = Matrix<double>(1, 8).fill_from_array(answer);
	if (test_add != matrix1 - matrix2) {
		std::cerr << "Substraction test FAILED\n";
	}
	else {
		std::cerr << "Substruction test PASSED\n";
	}
}


void test_mult() {
	double test_matrix1[6] = { 1, 2,3,4,5,6 };
	double test_matrix2[6] = { 7,8,9,1,2,3 };
	double answer[4] = { 31,19,85,55 };
	Matrix<double> matrix1 = Matrix<double>(3, 3).fill_from_array(test_matrix1);
	Matrix<double> matrix2 = Matrix<double>(3, 3).fill_from_array(test_matrix2);
	Matrix<double> test_add = Matrix<double>(3, 3).fill_from_array(answer);
	if (test_add != matrix1 * matrix2) {
		std::cerr << "Multiplication test FAILED\n";
	}
	else {
		std::cerr << "Multiplication test PASSED\n";
	}
}


void test_mult_scalar() {
	double test_matrix1[3] = { 1, 2, 3 };
	double answer[3] = { 3, 6, 9 };
	Matrix<double> matrix1 = Matrix<double>(1, 3).fill_from_array(test_matrix1);
	Matrix<double> test_add = Matrix<double>(1, 3).fill_from_array(answer);
	if (test_add != matrix1 * 3) {
		std::cerr << "Multiplication test FAILED\n";
	}
	else {
		std::cerr << "Multiplication test PASSED\n";
	}
}


void test_det() {
	double test_matrix1[9] = { 1, 7, 4,
						0, 9, 4,
						8, 8, 2 };
	Matrix<double> matrix1 = Matrix<double>(3, 3).fill_from_array(test_matrix1);
	double determinant = matrix1.determinant();
	if (determinant != -78) {
		std::cerr << "Determinant test FAILED\n";
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
	Matrix<double> rev = matrix1.reverse();
	if (rev == test_rev) {
		std::cerr << "Reverse test PASSED\n";
	}
	else {
		std::cerr << "Reverse test FAILED\n";
	}
}


void test_transpose() {
	double test_matrix1[6] = { 1,2,3,4,5,6 };
	double ans[6] = { 1,4,2,5,4,6 };
	Matrix<double> matrix1 = Matrix<double>(2, 3).fill_from_array(test_matrix1);
	Matrix<double> test_trans = Matrix<double>(3, 2).fill_from_array(ans);
	if (matrix1.transpose() == test_trans) {
		std::cerr << "Trasposition test PASSED\n";
	}
	else {
		std::cerr << "Transposition test FAILED\n";
	}
}



void ALL_TESTS() {
	test_add();
	test_sub();
	test_mult_scalar();
	test_mult();
//	test_det();
//	test_rev();
//	test_transpose();
}



void test_memory() {
	double test_matrix1[5] = { 1,2,3,4 ,5};
	Memory<double> A = Memory<double>(1, 5);
	A.fill_from_array(test_matrix1);

	double test_matrix2[10] = { 1,2,3,4,5,5,4,4,4,4};
	Memory<double> B = Memory<double>(2, 5);
	B.fill_from_array(test_matrix2);

	Memory<double> C = Memory<double>(2, 5);
	C.fill_from_array(test_matrix2);

	double test_matrix4[5] = { 1,2,3,4 };
	Memory<double> D = Memory<double>(2, 2);
	D.fill_from_array(test_matrix4);


}



int main() {
	//double test_matrix1[4] = { 1,2,3,4 };
	//double test_matrix2[4] = { 5,6,7,7 };
	//Matrix<double> A = Matrix<double>(2, 2).fill_from_array(test_matrix1);
	//Matrix<double> B = Matrix<double>(2, 2).fill_from_array(test_matrix2);

	//A.print_value("First Matrix\n");
	//B.print_value("Second Matrix\n");

	//try {
	//	Matrix<double> sum = A + B;
	//	sum.print_value("Addiction of the two matrix\n");
	//	Matrix<double> sub = A - B;
	//	sub.print_value("Subtraction of the two matrix\n");
	//}
	//catch (const Matrix_Exception& e)
	//{
	//	std::cerr << "Caught: " << e.what() << std::endl;
	//	std::cerr << "Type: " << typeid(e).name() << std::endl;
	//}

	//try {
	//	Matrix<double> mul = A * B;
	//	mul.print_value("Multiplication of two matrix\n");
	//}
	//catch (const Matrix_Exception& e)
	//{
	//	std::cerr << "Caught: " << e.what() << std::endl;
	//	std::cerr << "Type: " << typeid(e).name() << std::endl;
	//}

	//try {
	//	//std::cout << "Determinant\n" << A.determinant(A) << std::endl;
	//	//Matrix<double> rev = A.truncated(0, 1);
	//	//rev.print_value("trun\n");
	//	//Matrix<double> rev = A.reverse(A);
	//	//rev.print_value("Reverse Matrix\n");
	//	//Matrix<double> exp = A.exponent();
	//	//exp.print_value("Exponent Matrix\n");
	//}
	//catch (Matrix_Exception& e)
	//{
	//	std::cerr << "Caught: " << e.what() << std::endl;
	//	std::cerr << "Type: " << typeid(e).name() << std::endl;
	//}

	test_memory();
	//ALL_TESTS();
}