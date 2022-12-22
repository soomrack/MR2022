#include "matrix.hpp"
#include "matrixException.hpp"
#include <algorithm>
#include <iostream>
#include <exception>

const double EPS = 0.0001;

Matrix::Matrix():
    rowsCount_(0),
    columnsCount_(0),
    values_(nullptr)
{}

Matrix::Matrix(const Matrix& other) {
  rowsCount_ = other.rowsCount_;
  columnsCount_ = other.columnsCount_;
  values_ = new double[rowsCount_ * columnsCount_];
  for (int i = 0; i < rowsCount_ * columnsCount_; i++) {
    values_[i] = other.values_[i];
  }
}

Matrix::Matrix(Matrix&& other) noexcept {
  this->columnsCount_ = 0;
  this->rowsCount_ = 0;
  this->values_ = nullptr;
  swap(other);
}

Matrix::Matrix(unsigned int rowsCount, unsigned int colsCount):
  rowsCount_(rowsCount),
  columnsCount_(colsCount)
{
  values_ = new double[rowsCount_ * columnsCount_];
  for (size_t i = 0; i < rowsCount_ * columnsCount_; i++) {
    values_[i] = 0;
  }
}

Matrix::Matrix(unsigned int rowsCount, unsigned int colsCount, const double* values):
  rowsCount_(rowsCount),
  columnsCount_(colsCount)
{
  values_ = new double[rowsCount_ * columnsCount_];
  for (size_t i = 0; i < rowsCount * colsCount; i++) {
    values_[i] = values[i];
  }
}

Matrix& Matrix::operator=(const Matrix& other) {
  if (this == &other) {
    return *this;
  }
  Matrix temp(other);
  swap(temp);
  return *this;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept {
  if (this == &other) {
    return *this;
  }
  swap(other);
  return *this;
}

Matrix::~Matrix() {
  delete[] this->values_;
}

unsigned int Matrix::getRowsCount() const {
  return this->rowsCount_;
}

unsigned int Matrix::getColumnsCount() const {
  return this->columnsCount_;
}

double Matrix::getValue(unsigned int row, unsigned int column) const {
  try {
    return (*this)[row][column];
  }
  catch (...) {
    throw;
  }
}

void Matrix::setValue(double value, unsigned int row, unsigned int column) {
  try {
    (*this)[row][column] = value;
  }
  catch (...) {
    throw;
  }
}

Matrix Matrix::add(const Matrix& other) {
  if (!isEqualSize(*this, other)) {
    throw MatrixException("The matrices do not match in size!");
  }
  Matrix result = Matrix(this->rowsCount_, this->columnsCount_);
  for (size_t i = 0; i < this->rowsCount_ * this->columnsCount_; i++) {
    result.values_[i] = this->values_[i] + other.values_[i];
  }
  return result;
}

Matrix Matrix::add(double value) {
  Matrix result = Matrix(this->rowsCount_, this->columnsCount_);
  for (size_t i = 0; i < this->rowsCount_ * this->columnsCount_; i++) {
    result.values_[i] = this->values_[i] + value;
  }
  return result;
}

Matrix Matrix::operator+(const Matrix& other) {
  return this->add(other);
}

Matrix Matrix::operator+(double value) {
  return this->add(value);
}

void Matrix::operator+=(const Matrix& other) {
  *this = this->add(other);
}

void Matrix::operator+=(double value) {
  *this = this->add(value);
}

Matrix Matrix::subtract(const Matrix& other) {
  if (!isEqualSize(*this, other)) {
    throw MatrixException("The matrices do not match in size!");
  }
  Matrix result = Matrix(this->rowsCount_, this->columnsCount_);
  for (size_t i = 0; i < this->rowsCount_ * this->columnsCount_; i++) {
    result.values_[i] = this->values_[i] - other.values_[i];
  }
  return result;
}

Matrix Matrix::subtract(double value) {
  return this->add((-1) * value);
}

Matrix Matrix::operator-(const Matrix& other) {
  return this->subtract(other);
}

Matrix Matrix::operator-(double value) {
  return this->subtract(value);
}

void Matrix::operator-=(const Matrix& other) {
  *this = this->subtract(other);
}

void Matrix::operator-=(double value) {
  *this = this->subtract(value);
}

Matrix Matrix::multiply(const Matrix& other) {
  if (this->columnsCount_ != other.rowsCount_) {
    throw MatrixException("The number of columns of the first matrix does not correspond"
                          "to the number of rows of the second matrix!");
  }
  Matrix result = Matrix(this->rowsCount_, other.columnsCount_);
  for (size_t i = 1; i <= result.rowsCount_; i++) {
    for (size_t j = 1; j <= result.columnsCount_; j++) {
      double sum = 0.0;
      for (size_t k = 1; k <= this->columnsCount_; k++) {
        sum += (*this)[i][k] * other[k][j];
      }
      result[i][j] = sum;
    }
  }
  return result;
}

Matrix Matrix::multiply(double value) {
  Matrix result = Matrix(this->rowsCount_, this->columnsCount_);
  for (size_t i = 0; i < this->rowsCount_ * this->columnsCount_; i++) {
    result.values_[i] = this->values_[i] * value;
  }
  return result;
}

Matrix Matrix::operator*(const Matrix& other) {
  return this->multiply(other);
}

Matrix Matrix::operator*(double value) {
  return this->multiply(value);
}

void Matrix::operator*=(const Matrix& other) {
  *this = this->multiply(other);
}

void Matrix::operator*=(double value) {
  *this = this->multiply(value);
}


Matrix Matrix::divideByScalar(double value) {
  if (std::abs(value) < EPS) {
    throw MatrixException("Division by zero");
  }
  return this->multiply(1.0 / value);
}

Matrix Matrix::operator/(double value) {
  if (std::abs(value) < EPS) {
    throw MatrixException("Division by zero");
  }
  return this->divideByScalar(value);
}

void Matrix::operator/=(double value) {
  if (std::abs(value) < EPS) {
    throw MatrixException("Division by zero");
  }
  *this = this->divideByScalar(value);
}

bool Matrix::operator==(const Matrix& other) const {
  if (this == &other) {
    return true;
  }
  if (this->rowsCount_ != other.rowsCount_ || this->columnsCount_ != other.columnsCount_) {
    return false;
  }
  for (size_t i = 0; i < this->rowsCount_ * this->columnsCount_; i++) {
    if (std::abs(this->values_[i] - other.values_[i]) > EPS) {
      return false;
    }
  }
  return true;
}

//Получение треугольной матрицы
int Matrix::getTriangleMatrix(Matrix& destinationMatrix) {
  if (this->columnsCount_ != this->rowsCount_) {
    throw MatrixException("The matrix must be square!");
  }
  if (isMatrixDiagonalHasZero()) {
    throw MatrixException("The diagonal of the matrix contains zeros. Calculation is impossible!");
  }
  int result = 0;
  destinationMatrix = *this;
  for (size_t i = 1; i < destinationMatrix.rowsCount_; i++) {
    //Находим строку с максимальным значением и поднимаем наверх
    unsigned int rowMax = destinationMatrix.getIndexMaxColValue(i, i);
    if (rowMax != 0) {
      destinationMatrix.swapRow(i, rowMax);
      result++;
    }
    //Находим коэффициент и приводим все оставшиеся строки
    for (size_t j = i + 1; j <= destinationMatrix.rowsCount_; j++) {
      double ratio = (-1) * destinationMatrix[j][i] / destinationMatrix[i][i];
      for (size_t k = i; k <= destinationMatrix.columnsCount_; k++) {
        destinationMatrix[j][k] += destinationMatrix[i][k] * ratio;
      }
    }
  }
  return result;
}

double Matrix::getDeterminant() {
  if (this->columnsCount_ != this->rowsCount_) {
    throw MatrixException("The matrix must be square!");
  }
  Matrix matrix;
  int swapCount = this->getTriangleMatrix(matrix);
  return matrix.getDeterminantFromTriangleMatrix(swapCount);
}

Matrix Matrix::getTransposed() {
  Matrix result = Matrix(this->columnsCount_, this->rowsCount_);
  for (size_t i = 1; i <= this->rowsCount_; i++) {
    for (size_t j = 1; j <= this->columnsCount_; j++) {
      result[j][i] = (*this)[i][j];
    }
  }
  return result;
}

double Matrix::getMinor(unsigned int row, unsigned int column) {
  if (row > this->rowsCount_ || column > this->columnsCount_) {
    throw MatrixException("Going over the size of the matrix. You can't find a minor!");
  }
  if (this->columnsCount_ != this->rowsCount_) {
    throw MatrixException("The matrix must be square!");
  }
  Matrix temp(this->rowsCount_ - 1, this->columnsCount_ - 1);
  for (size_t i = 1, k = i; i <= temp.rowsCount_; i++, k++) {
    for (size_t j = 1, l = j; j <= temp.columnsCount_; j++, l++) {
      k == row ? k++ : k;
      l == column ? l++ : l;
      temp[i][j] = (*this)[k][l];
    }
  }
  return temp.getDeterminant();
}

Matrix Matrix::getCofactor() {
  if (this->columnsCount_ != this->rowsCount_) {
    throw MatrixException("The matrix must be square!");
  }
  Matrix result = Matrix(this->rowsCount_, this->columnsCount_);
  for (size_t i = 1; i <= result.rowsCount_; i++) {
    for (size_t j = 1; j<= result.columnsCount_; j++) {
      double minor = this->getMinor(i, j);
      if ((i + j) % 2 == 1) {
        minor *= -1;
      }
      result[i][j] = minor;
    }
  }
  return result;
}

Matrix Matrix::getInverted() {
  Matrix resultMatrix = Matrix();
  try {
    double determinant = this->getDeterminant();
    Matrix cofactorMatrix = this->getCofactor();
    resultMatrix = cofactorMatrix.getTransposed();
    resultMatrix = resultMatrix.divideByScalar(determinant);
  } catch (...) {
    throw;
  }
  return resultMatrix;
}

Matrix Matrix::pow(unsigned int degree) {
  Matrix result = Matrix(*this);
  for (size_t i = 1; i < degree; i++) {
    result *= (*this);
  }
  return result;
}

Matrix Matrix::getMatrixExponent(double precision) {
  if (this->columnsCount_ != this->rowsCount_) {
    throw MatrixException("The matrix must be square!");
  }
  unsigned int degree = 2;
  Matrix last;
  Matrix current(*this);
  bool isAccurate = false;
  while(!isAccurate) {
    last = current;
    current = *this;
    Matrix sum = Matrix(*this);
    for (size_t i = 2; i <= degree; i++) {
      Matrix temp = current.pow(i);
      temp /= calculateFactorial(i);
      sum += temp;
    }
    degree++;
    current = sum;
    isAccurate = checkAccuracy(current, last, precision);
  }
  return current;
}

Matrix::RowProxy Matrix::operator[](size_t i) {
  if (((i - 1) > this->rowsCount_) || (i < 1)) {
     throw MatrixException("An attempt to access an element outside the matrix boundary!");
  }
  return RowProxy(&values_[(i - 1) * columnsCount_], columnsCount_);
}

Matrix::RowProxy Matrix::operator[](size_t i) const {
  if (((i - 1) > this->rowsCount_) || (i < 1)) {
    throw MatrixException("An attempt to access an element outside the matrix boundary!");
  }
  return RowProxy(&values_[(i - 1) * columnsCount_], columnsCount_);
}

std::ostream& operator<<(std::ostream& out, Matrix& matrix) {
  double* current = matrix.values_;
  for (size_t i = 0; i < matrix.columnsCount_ * matrix.rowsCount_; i++)
  {
    out << *current << " ";
    current++;
    if ((i + 1) % matrix.columnsCount_ == 0) {
      out << "\n";
    }
  }
  return out;
}

std::ostream& operator<<(std::ostream& out, Matrix&& matrix) {
  double* current = matrix.values_;
  for (size_t i = 0; i < matrix.columnsCount_ * matrix.rowsCount_; i++)
  {
    out << *current << " ";
    current++;
    if ((i + 1) % matrix.columnsCount_ == 0) {
      out << "\n";
    }
  }
  return out;
}

Matrix::RowProxy::RowProxy(double* data, size_t size):
    values_(data),
    size_(size)
{}

double& Matrix::RowProxy::operator[](size_t j) {
  if (((j - 1) > size_ ) || (j < 1)) {
    throw MatrixException("An attempt to access an element outside the matrix boundary!");
  }
  return this->values_[j - 1];
}

void Matrix::swap(Matrix& other) {
  std::swap(this->rowsCount_, other.rowsCount_);
  std::swap(this->columnsCount_, other.columnsCount_);
  std::swap(this->values_, other.values_);
}

double Matrix::getDeterminantFromTriangleMatrix(int swapCount) {
  double result = 1;
  for (size_t i = 1; i <= this->columnsCount_; i++) {
    result *= (*this)[i][i];
  }
  return (swapCount % 2) == 0 ? result : (-1) * result;
}

bool Matrix::isEqualSize(const Matrix& first, const Matrix& second) {
  if ((first.columnsCount_ != second.columnsCount_) || (first.rowsCount_ != second.rowsCount_)) {
    return false;
  }
  return true;
}

unsigned int Matrix::getIndexMaxColValue(unsigned int index, unsigned int startPosition)
{
  unsigned int result = 0;
  double temp = (*this)[startPosition][index];
  for (size_t i = startPosition + 1; i <= this->columnsCount_; i++) {
    if (std::abs((*this)[i][index]) > std::abs(temp)) {
      temp = (*this)[i][index];
      result = i;
    }
  }
  return result;
}

void Matrix::swapRow(unsigned int first, unsigned int second)
{
  for (size_t i = 1; i <= this->columnsCount_; i++) {
    double temp = (*this)[first][i];
    (*this)[first][i] = (*this)[second][i];
    (*this)[second][i] = temp;
  }
}

bool Matrix::isMatrixDiagonalHasZero()
{
  bool result = false;
  for (size_t i = 1; i <= rowsCount_; i++) {
    if (std::abs((*this)[i][i]) < EPS) {
      result = true;
      break;
    }
  }
  return result;
}

unsigned int Matrix::calculateFactorial(unsigned int degree)
{
  unsigned int result = 1;
  for (size_t i = 2; i <= degree; i++) {
    result *= i;
  }
  return result;
}

bool Matrix::checkAccuracy(const Matrix& first, const Matrix& second, double precision) {
  for (size_t i = 1; i <= first.rowsCount_; i++) {
    for (size_t j = 1; j <= first.columnsCount_; j++) {
      if ((first[i][j] - second[i][j]) > precision) {
        return false;
      }
    }
  }
  return true;
}
