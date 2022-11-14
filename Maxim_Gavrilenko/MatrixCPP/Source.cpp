#include <iostream>
#include <cmath>
#include <ctime>


class Matrix
{

public:

	unsigned int rows;
	unsigned int cols;

	Matrix(unsigned int, unsigned int, double*);
	Matrix(unsigned int, unsigned int);
	Matrix();
	Matrix(const Matrix&);
	Matrix(Matrix&&) noexcept;
	~Matrix();


	void fill_Matrix();
	void output();
	
	Matrix one();		//Преобразование матрицы в единичную
	Matrix exponent_matrix();		//Нахождение экспоненты матрицы
	Matrix transpose();				// Транспонирование матрицы
	Matrix Minor(Matrix,const unsigned int, const unsigned int,const unsigned int);		//Нахождение минора матрицы
	Matrix reverse_matrix(const Matrix, unsigned int);		//Обратная матрица
	double determinant(const Matrix, unsigned int);		//Определитель матрицы 

	Matrix& operator=(Matrix&&) noexcept;
	Matrix& operator=(const Matrix&);
	Matrix& operator+=(const Matrix&);
	Matrix& operator-=(const Matrix&);
	Matrix& operator*=(const Matrix&);
	Matrix& operator*=(const double);
	Matrix& operator/=(double);

	friend std::ostream& operator<<(std::ostream& out, Matrix m);
	/*double* operator[](unsigned int);*/


private:
	double* values;
};


Matrix empty();

Matrix operator+ (const Matrix&);
Matrix operator- (const Matrix&, const Matrix&);
Matrix operator* (const Matrix&,const Matrix&);
Matrix operator* (const Matrix&,const double);
Matrix operator/ (const Matrix&,const double);
Matrix& operator+=(const Matrix&,const Matrix&);
void output(Matrix&);

Matrix::Matrix() : rows(0), cols(0), values(nullptr) {}


Matrix::Matrix(const Matrix& mat) : rows(mat.rows), cols(mat.cols) {
	values = new double[rows * cols];
	memcpy(values, mat.values, rows * cols * sizeof(double));
}


Matrix::Matrix(unsigned int num_row, unsigned int num_col, double* value)
{
	rows = num_row;
	cols = num_col;
	unsigned int index = rows * cols;
	for (unsigned int idx = 0; idx < index; idx++) {
		values[index] = value[index];
	}
}


Matrix::Matrix(unsigned int num_row, unsigned int num_col)
{
	rows = num_row;
	cols = num_col;
	unsigned int index = rows * cols;
	values = new double[index];
	Matrix::fill_Matrix();
}


Matrix::Matrix(Matrix&& mat) noexcept : values(mat.values), rows(mat.rows), cols(mat.cols) {
	mat.values = nullptr;
	mat.rows = 0;
	mat.cols = 0;
}


Matrix::~Matrix() {
	/*std::cout << "destructor\n";*/
	delete[] this->values;
}
	

std::ostream& operator<<(std::ostream& out, Matrix m) {
	{
		for (unsigned int row = 0; row < m.rows; row++)
		{
			for (unsigned int col = 0; col < m.cols; col++)
			{
				out << m.values[row * m.cols + col] << "\t";
			}
			out << std::endl;
		}
		out << std::endl;
		return(out);
	}
}


//double* Matrix::operator[](unsigned int idx) {
//	if (idx > rows) {
//		return nullptr;
//	}
//	return values + idx * cols;
//}


void Matrix::fill_Matrix() {
	for (unsigned int index = 0; index < cols * rows; index++)
	{
		values[index] = double(rand() % 10);
	}
}


Matrix Matrix::one() {
	for (unsigned int index = 0; index < cols * rows; index++) {
		values[index] = 0;
		for (unsigned int num = 0; num <= index; num+=cols+1) {
			values[num] = 1.0;
		}
	}
	return *this;
}


void Matrix::output()
{
	std::cout << *this << std::endl;
}


void output(Matrix& m) {
		std::cout << m;
}


Matrix Matrix::Minor(Matrix matrix,const unsigned int size, const unsigned int row, const unsigned int col) {
	Matrix m1(size - 1, size -1);
	unsigned int shiftRow = 0; //Смещение индекса строки в матрице
	unsigned int shiftCol; //Смещение индекса столбца в матрице
	for (unsigned int rows = 0; rows < size - 1; rows++) {
		//Пропустить row-ую строку
		if (rows == row) {
			shiftRow = 1; //Как только встретили строку, которую надо пропустить, делаем смещение для исходной матрицы
		}
		shiftCol = 0; //Обнулить смещение столбца
		for (unsigned int cols = 0; cols < size - 1; cols++) {
			if (cols == col) {
				shiftCol = 1;
			}
			m1.values[rows * (size - 1) + cols] = matrix.values[(rows + shiftRow) * size + (cols + shiftCol)];
		}
	}
	return m1;
}


Matrix Matrix::transpose() {
	Matrix trans(cols,rows);
	for (unsigned int row = 0; row < rows; row++) {
		for (unsigned int col = 0; col < cols; col++) {
			trans.values[col * trans.rows + row] = values[row * trans.cols + col];
		}
	}
	*this = trans;
	return (*this);
}


Matrix empty() {
	Matrix zero(0, 0,NULL);
	return zero;
}


Matrix operator+(const Matrix& A, const Matrix& B) {
	Matrix add(A);
	add += B;
return (add);
}


Matrix operator-(const Matrix& A, const Matrix& B) {
	Matrix sub(A);
	sub -= B;
	return (sub);
}


Matrix operator*(const Matrix& A, const double k) { // Умножение матрицы на число
	Matrix multiply(A);
	return (multiply*=k);
}


Matrix operator*(const Matrix& A, const Matrix& B) {
	Matrix temp(A);
	temp *= B;
	return (temp);
}


Matrix operator/(const Matrix& A,const double k) { // Деление матрицы на число
	Matrix multiply(A);
	multiply /= k;
	return multiply;
}


Matrix& Matrix::operator*=(const Matrix& m2) { // Умножение матриц
	if (cols != m2.rows) {
		throw std::domain_error("Error: first matrix cols not equal to second matrix row.");
	}
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
		return (*this = multiplication);
}


Matrix& Matrix::operator+=(const Matrix& matrix) {
	if (rows != matrix.rows || cols != matrix.cols) {
		throw std::domain_error("Error: matrix should have a same size.");
	}
	for (unsigned int index = 0; index < rows * cols; ++index) {
		this->values[index] += matrix.values[index];
	}
	return *this;
}


Matrix& Matrix::operator-=(const Matrix& matrix) {
	if (rows != matrix.rows || cols != matrix.cols) {
		throw std::domain_error("Error: matrix should have a same size.");
	}
	for (unsigned int index = 0; index < rows * cols; ++index) {
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


Matrix& Matrix::operator=(const Matrix& A) {
	if (this != &A) {
		delete[] values;
		rows = A.rows;
		cols = A.cols;
		this->values = new double[rows * cols];
		memcpy(this->values, A.values, rows * cols * sizeof(double));
	}
	return *this;
}


Matrix& Matrix::operator=(Matrix&& A) noexcept {
	if (this != &A) {
		delete[] A.values;
		rows = A.rows;
		cols = A.cols;
		values = A.values;
		A.values = nullptr;
	}
	return *this;
}


double Matrix::determinant(const Matrix m, unsigned int size) {
	if (m.rows != m.cols) {
		throw std::domain_error("Error: matrix should have nxn.");
	}
	double det = 0;
	if (size == 0)
		return 0;
	if (size == 1)
		return m.values[0];
	if (size == 2) {
		return (m.values[0] * m.values[3] - m.values[2] * m.values[1]);
	}
	for (unsigned int idx = 0; idx < size; idx++) {
		det += (pow(-1, idx) * m.values[idx] * determinant(Minor(m,size,0,idx), size - 1));
	}
	return det;
}


Matrix Matrix::reverse_matrix(const Matrix rev, const unsigned int size) { // Функция нахождения обратной матрицы
	double d = determinant(rev, size);
	if (rev.rows != rev.cols) {
		throw std::domain_error("Error: matrix should have nxn.");
	}
	if (d == 0) {
		throw std::domain_error("Error: matrix is degenative.");
	}
	Matrix A(rev.rows, rev.cols);
	for (unsigned int row = 0; row < A.rows; row++) {
		for (unsigned int col = 0; col < A.cols; col++) {
			A.values[row * size + col] = (pow(-1, row + col) * determinant(Minor(rev, size, row, col), size - 1));
		}
	}
	A.transpose();
	A /= d;
	return A;
}


Matrix Matrix::exponent_matrix() {
	if (rows != cols) {
			throw std::domain_error("Error: matrix should be nxn\n.");
	}
	unsigned int n = 30; // Количество членов ряда
	Matrix ex(rows,cols);
	Matrix temp(rows,cols);
	temp.one();
	ex.one();
	double fact = 1.0;
	for (unsigned int i = 1; i < n; i++) {
		fact *= i;
		temp *= (*this);
		ex += temp / fact;
	}
	return ex;
}


int main()
{ 
	/*srand(time(NULL));*/
	setlocale(LC_ALL, "ru");
	Matrix A(5, 5);
	Matrix B(5, 5);
	std::cout << "First Matrix\n" << A;
	std::cout << "Second Matrix\n" << B;
	
	
	try {
		std::cout << "Addiction of two matrix\n" << A + B;
		std::cout << "Subtraction of two matrix\n" << A - B;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Caught: " << e.what() << std::endl;
		std::cerr << "Type: " << typeid(e).name() << std::endl;
	}

	try {
		std::cout << "Multiplication of two matrix\n" << A * B;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Caught: " << e.what() << std::endl;
		std::cerr << "Type: " << typeid(e).name() << std::endl;
	}


	try {
		std::cout << "Determinant\n" << A.determinant(A, A.rows) << std::endl;
		std::cout << "Reverse Matrix\n" << A.reverse_matrix(A, A.rows) << std::endl;
		std::cout << "Exponent Matrix\n" << A.exponent_matrix();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Caught: " << e.what() << std::endl;
		std::cerr << "Type: " << typeid(e).name() << std::endl;
	}

}