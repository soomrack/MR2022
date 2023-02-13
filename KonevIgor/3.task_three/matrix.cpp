#include "matrix.hpp"
#include "matrixException.hpp"
#include <algorithm>
#include <iostream>
#include <exception>
#include <cstdlib>

const double EPS = 0.0001;

Matrix::Matrix():
    rows(0),
    cols(0),
    values(nullptr)
{}

Matrix::Matrix(const Matrix& other) {
    rows = other.rows;
    cols = other.cols;
    values = new double[rows * cols];
    for (size_t idx = 0; idx < rows * cols; idx++) {
        values[idx] = other.values[idx];
  }
}

Matrix::Matrix(Matrix&& other) noexcept {
  this->cols = 0;
  this->rows = 0;
  this->values = nullptr;
  swap(other);
}

Matrix::Matrix(unsigned int rows_count, unsigned int cols_count):
    rows(rows_count),
    cols(cols_count)
{
    values = new double[rows * cols];
    for (size_t idx = 0; idx < rows * cols; idx++) {
        values[idx] = 0;
    }
}

Matrix::Matrix(unsigned int rows_count, unsigned int cols_count, const double* value):
    rows(rows_count),
    cols(cols_count)
{
    values = new double[rows * cols];
    for (size_t idx = 0; idx < rows_count * cols_count; idx++) {
        values[idx] = value[idx];
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
  delete[] this->values;
}

unsigned int Matrix::get_rows_count() const {
  return this->rows;
}

unsigned int Matrix::get_cols_count() const {
  return this->cols;
}


double Matrix::get_value(unsigned int row, unsigned int column) const {
    return (*this)[row][column];
}

void Matrix::set_value(double value, unsigned int row, unsigned int column) {
    (*this)[row][column] = value;
}

Matrix Matrix::add(const Matrix& other) {
  if (!is_equal_size(*this, other)) {
    throw Matrix_exception("The matrices do not match in size!");
  }
  Matrix result = Matrix(this->rows, this->cols);
  for (size_t idx = 0; idx < this->rows * this->cols; idx++) {
    result.values[idx] = this->values[idx] + other.values[idx];
  }
  return result;
}

Matrix Matrix::add(double value) {
  Matrix result = Matrix(this->rows, this->cols);
  for (size_t idx = 0; idx < this->rows * this->cols; idx++) {
    result.values[idx] = this->values[idx] + value;
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
  if (!is_equal_size(*this, other)) {
    throw Matrix_exception("The matrices do not match in size!");
  }
  Matrix result = Matrix(this->rows, this->cols);
  for (size_t idx = 0; idx < this->rows * this->cols; idx++) {
    result.values[idx] = this->values[idx] - other.values[idx];
  }
  return result;
}

Matrix Matrix::subtract(double value) {
  return this->add(-value);
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
  if (this->cols != other.rows) {
    throw Matrix_exception("The number of columns of the first matrix does not correspond"
                          "to the number of rows of the second matrix!");
  }
  Matrix result = Matrix(this->rows, other.cols);
  for (size_t m = 1; m <= result.rows; m++) {
    for (size_t n = 1; n <= result.cols; n++) {
      double sum = 0.0;
      for (size_t k = 1; k <= this->cols; k++) {
        sum += (*this)[m][k] * other[k][n];
      }
      result[m][n] = sum;
    }
  }
  return result;
}

Matrix Matrix::multiply(double value) {
  Matrix result = Matrix(this->rows, this->cols);
  for (size_t idx = 0; idx < this->rows * this->cols; idx++) {
    result.values[idx] = this->values[idx] * value;
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


Matrix Matrix::divide_by_scalar(double value) {
  if (std::abs(value) < EPS) {
    throw Matrix_exception("Division by zero");
  }
  return this->multiply(1.0 / value);
}

Matrix Matrix::operator/(double value) {
  if (std::abs(value) < EPS) {
    throw Matrix_exception("Division by zero");
  }
  return this->divide_by_scalar(value);
}

void Matrix::operator/=(double value) {
  if (std::abs(value) < EPS) {
    throw Matrix_exception("Division by zero");
  }
  *this = this->divide_by_scalar(value);
}

bool Matrix::operator==(const Matrix& other) const {
  if (this == &other) {
    return true;
  }
  if (this->rows != other.rows || this->cols != other.cols) {
    return false;
  }
  for (size_t idx
  = 0; idx < this->rows * this->cols; idx++) {
    if (std::abs(this->values[idx] - other.values[idx]) > EPS) {
      return false;
    }
  }
  return true;
}

//Получение треугольной матрицы
int Matrix::get_triangle_matrix(Matrix& destinationMatrix) {
  if (this->cols != this->rows) {
    throw Matrix_exception("The matrix must be square!");
  }
  if (is_main_diagonal_has_zero()) {
    throw Matrix_exception("The diagonal of the matrix contains zeros. Calculation is impossible!");
  }
  int result = 0;
  destinationMatrix = *this;
  for (size_t m = 1; m < destinationMatrix.rows; m++) {
    //Находим строку с максимальным значением и поднимаем наверх
    unsigned int rowMax = destinationMatrix.get_index_max_col_value(m, m);
    if (rowMax != 0) {
        destinationMatrix.swap_rows(m, rowMax);
      result++;
    }
    //Находим коэффициент и приводим все оставшиеся строки
    for (size_t n = m + 1; n <= destinationMatrix.rows; n++) {
      double ratio = (-1) * destinationMatrix[n][m] / destinationMatrix[m][m];
      for (size_t k = m; k <= destinationMatrix.cols; k++) {
        destinationMatrix[n][k] += destinationMatrix[m][k] * ratio;
      }
    }
  }
  return result;
}

double Matrix::get_determinant() {
  if (this->cols != this->rows) {
    throw Matrix_exception("The matrix must be square!");
  }
  Matrix matrix;
  int swapCount = this->get_triangle_matrix(matrix);
  return matrix.get_determinant_from_triangle_matrix(swapCount);
}

Matrix Matrix::get_transposed() {
  Matrix result = Matrix(this->cols, this->rows);
  for (size_t m = 1; m <= this->rows; m++) {
    for (size_t n = 1; n <= this->cols; n++) {
      result[n][m] = (*this)[m][n];
    }
  }
  return result;
}

double Matrix::get_minor(unsigned int row, unsigned int column) {
  if (row > this->rows || column > this->cols) {
    throw Matrix_exception("Going over the size of the matrix. You can't find a minor!");
  }
  if (this->cols != this->rows) {
    throw Matrix_exception("The matrix must be square!");
  }
  Matrix temp(this->rows - 1, this->cols - 1);
  for (size_t m = 1, k = m; m <= temp.rows; m++, k++) {
    for (size_t n = 1, s = n; n <= temp.cols; n++, s++) {
      k == row ? k++ : k;
        s == column ? s++ : s;
      temp[m][n] = (*this)[k][s];
    }
  }
  return temp.get_determinant();
}

Matrix Matrix::get_cofactor() {
  if (this->cols != this->rows) {
    throw Matrix_exception("The matrix must be square!");
  }
  Matrix result = Matrix(this->rows, this->cols);
  for (size_t m = 1; m <= result.rows; m++) {
    for (size_t n = 1; n <= result.cols; n++) {
      double minor = this->get_minor(m, n);
      if ((m + n) % 2 == 1) {
        minor *= -1;
      }
      result[m][n] = minor;
    }
  }
  return result;
}

Matrix Matrix::get_inverted() {
  Matrix resultMatrix = Matrix();
  double determinant = this->get_determinant();
  Matrix cofactorMatrix = this->get_cofactor();
  resultMatrix = cofactorMatrix.get_transposed();
  resultMatrix = resultMatrix.divide_by_scalar(determinant);
  return resultMatrix;
}

Matrix Matrix::pow(unsigned int degree) {
    if (degree > 100) {
        throw Matrix_exception("Degree value is too high!");
    }
    if (this->cols != this->rows) {
        throw Matrix_exception("The matrix must be square!");
    }
    Matrix result = get_identity_matrix(this->cols);
    for (size_t idx = 1; idx < (degree + 1); idx++) {
      result *= (*this);
    }
    return result;
}

Matrix Matrix::get_matrix_exponent(double precision) {
  if (this->cols != this->rows) {
    throw Matrix_exception("The matrix must be square!");
  }
  Matrix last;
  Matrix result = get_identity_matrix(this->rows);
  Matrix power = get_identity_matrix(this->rows);
  bool isAccurate = false;
  int k = 1;
  double factorial = 1;
  while ((!isAccurate) || (k < 50)) {
      last = result;
      power = power.multiply(*this);
      result += power.divide_by_scalar(factorial);
    k++;
    factorial *= k;
    isAccurate = check_accuracy(result, last, precision);
  }
  return result;
}

Matrix::Row_proxy Matrix::operator[](size_t idx) {
  if (((idx - 1) > this->rows) || (idx < 1)) {
     throw Matrix_exception("An attempt to access an element outside the matrix boundary!");
  }
  return Row_proxy(&values[(idx - 1) * cols], cols);
}

Matrix::Row_proxy Matrix::operator[](size_t idx) const {
  if (((idx - 1) > this->rows) || (idx < 1)) {
    throw Matrix_exception("An attempt to access an element outside the matrix boundary!");
  }
  return Row_proxy(&values[(idx - 1) * cols], cols);
}

std::ostream& operator<<(std::ostream& out, Matrix& matrix) {
  double* current = matrix.values;
  for (size_t idx = 0; idx < matrix.cols * matrix.rows; idx++)
  {
    out << *current << " ";
    current++;
    if ((idx + 1) % matrix.cols == 0) {
      out << "\n";
    }
  }
  return out;
}

std::ostream& operator<<(std::ostream& out, Matrix&& matrix) {
  double* current = matrix.values;
  for (size_t idx = 0; idx < matrix.cols * matrix.rows; idx++)
  {
    out << *current << " ";
    current++;
    if ((idx + 1) % matrix.cols == 0) {
      out << "\n";
    }
  }
  return out;
}

Matrix::Row_proxy::Row_proxy(double* data, size_t size):
        values(data),
        size(size)
{}

double& Matrix::Row_proxy::operator[](size_t idx) {
  if (((idx - 1) > size ) || (idx < 1)) {
    throw Matrix_exception("An attempt to access an element outside the matrix boundary!");
  }
  return this->values[idx - 1];
}

void Matrix::swap(Matrix& other) {
  std::swap(this->rows, other.rows);
  std::swap(this->cols, other.cols);
  std::swap(this->values, other.values);
}

double Matrix::get_determinant_from_triangle_matrix(int swap_count) {
  double result = 1;
  for (size_t idx = 1; idx <= this->cols; idx++) {
    result *= (*this)[idx][idx];
  }
  return (swap_count % 2) == 0 ? result : (-1) * result;
}

bool Matrix::is_equal_size(const Matrix& first, const Matrix& second) {
  if ((first.cols != second.cols) || (first.rows != second.rows)) {
    return false;
  }
  return true;
}

unsigned int Matrix::get_index_max_col_value(unsigned int index, unsigned int start_position)
{
  unsigned int result = 0;
  double temp = (*this)[start_position][index];
  for (size_t idx = start_position + 1; idx <= this->cols; idx++) {
    if (std::abs((*this)[idx][index]) > std::abs(temp)) {
      temp = (*this)[idx][index];
      result = idx;
    }
  }
  return result;
}

void Matrix::swap_rows(unsigned int first, unsigned int second)
{
  for (size_t idx = 1; idx <= this->cols; idx++) {
    double temp = (*this)[first][idx];
    (*this)[first][idx] = (*this)[second][idx];
    (*this)[second][idx] = temp;
  }
}

bool Matrix::is_main_diagonal_has_zero()
{
    bool result = false;
    for (size_t i = 1; i <= rows; i++) {
        if (std::abs((*this)[i][i]) < EPS) {
            result = true;
            break;
        }
    }
    return result;
}

bool Matrix::check_accuracy(const Matrix& first, const Matrix& second,
                            double precision) {
  for (size_t m = 1; m <= first.rows; m++) {
    for (size_t n = 1; n <= first.cols; n++) {
      if ((first[m][n] - second[m][n]) > precision) {
        return false;
      }  
    }
  }
  return true;
}

Matrix Matrix::get_identity_matrix(const unsigned int size) {
    Matrix result(size, size);
    for (size_t idx = 1; idx <= size; ++idx) {
        result[idx][idx] = 1;
    }
    return result;
}
