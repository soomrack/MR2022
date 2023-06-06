#ifndef MATRIX_H
#define MATRIX_H

#include "matrixException.h"
#include <algorithm>
#include <iostream>
#include <exception>

template <typename T>
class Matrix {

protected:

    unsigned int rows;
    unsigned int cols;
    T* values;

    void swap(Matrix&);
    void swap_rows(unsigned int, unsigned int);
    T get_determinant_from_triangle_matrix(int swapCount);
    unsigned int get_index_max_col_value(unsigned int, unsigned int);
    bool is_main_diagonal_has_zero();
    static bool is_equal_size(const Matrix&, const Matrix&);
    static bool check_accuracy(const Matrix&, const Matrix&, T);

    const T EPS = 0.0001;

public:

    static_assert(std::is_same<T, float>::value ||
    std::is_same<T, double>::value ||
    std::is_same<T, long double>::value,
    "That data type can not be used in matrix calculations");

  Matrix();
  Matrix(const Matrix&);
  Matrix(Matrix&&) noexcept;
  Matrix(unsigned int, unsigned int);
  Matrix(unsigned int, unsigned int, const T*);
  Matrix& operator=(const Matrix&);
  Matrix& operator=(Matrix&&) noexcept;
  ~Matrix();

  unsigned int get_rows_count() const;
  unsigned int get_cols_count() const;
  T get_value(unsigned int, unsigned int) const;
  void set_value(T, unsigned int, unsigned int);

  Matrix add(const Matrix&);
  Matrix add(T);
  Matrix operator+(const Matrix&);
  Matrix operator+(T);
  void operator+=(const Matrix&);
  void operator+=(T);
  Matrix subtract(const Matrix&);
  Matrix subtract(T);
  Matrix operator-(const Matrix&);
  Matrix operator-(T);
  void operator-=(const Matrix&);
  void operator-=(T);
  Matrix multiply(const Matrix&);
  Matrix multiply(T);
  Matrix operator*(const Matrix&);
  Matrix operator*(T);
  void operator*=(const Matrix&);
  void operator*=(T);
  Matrix divide_by_scalar(T);
  Matrix operator/(T);
  void operator/=(T);
  bool operator==(const Matrix&) const;
  int get_triangle_matrix(Matrix& destinationMatrix);
  T get_determinant();
  Matrix get_transposed();
  T get_minor(unsigned int, unsigned int);
  Matrix get_cofactor();
  Matrix get_inverted();
  Matrix pow(unsigned int);
  Matrix get_identity_matrix(unsigned int size);
  Matrix get_matrix_exponent(T);

  class Row_proxy {
  public:
    Row_proxy(T*, size_t);
    T& operator[](size_t k);
  private:
    T* values;
    size_t size;
  };
  Row_proxy operator[](size_t idx);
  Row_proxy operator[](size_t idx) const;

  friend std::ostream& operator<<(std::ostream&, Matrix<T>&);
  friend std::ostream& operator<<(std::ostream&, Matrix<T>&&);

};

template <typename T>
Matrix<T>::Matrix():
    rows(0),
    cols(0),
    values(nullptr)
{}

template <typename T>
Matrix<T>::Matrix(const Matrix& other) {
  rows = other.rows;
  cols = other.cols;
  values = new T[rows * cols];
  for (size_t idx = 0; idx < rows * cols; idx++) {
    values[idx] = other.values[idx];
  }
}

template <typename T>
Matrix<T>::Matrix(Matrix&& other) noexcept {
  this->cols = 0;
  this->rows = 0;
  this->values = nullptr;
  swap(other);
}

template <typename T>
Matrix<T>::Matrix(unsigned int rows_count, unsigned int cols_count):
    rows(rows_count),
    cols(cols_count)
{
  values = new T[rows * cols];
  for (size_t idx = 0; idx < rows * cols; idx++) {
    values[idx] = 0;
  }
}

template <typename T>
Matrix<T>::Matrix(unsigned int rows_count, unsigned int cols_count, const T*
value):
    rows(rows_count),
    cols(cols_count)
{
  values = new T[rows * cols];
  for (size_t idx = 0; idx < rows_count * cols_count; idx++) {
    values[idx] = value[idx];
  }
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& other) {
  if (this == &other) {
    return *this;
  }
  Matrix temp(other);
  swap(temp);
  return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix&& other) noexcept {
  if (this == &other) {
    return *this;
  }
  swap(other);
  return *this;
}

template <typename T>
Matrix<T>::~Matrix() {
  delete[] this->values;
}

template <typename T>
unsigned int Matrix<T>::get_rows_count() const {
  return this->rows;
}

template <typename T>
unsigned int Matrix<T>::get_cols_count() const {
  return this->cols;
}

template <typename T>
T Matrix<T>::get_value(unsigned int row, unsigned int column) const {
  return (*this)[row][column];
}

template <typename T>
void Matrix<T>::set_value(T value, unsigned int row, unsigned int
column) {
  (*this)[row][column] = value;
}

template <typename T>
Matrix<T> Matrix<T>::add(const Matrix& other) {
  if (!is_equal_size(*this, other)) {
    throw Matrix_exception("The matrices do not match in size!");
  }
  Matrix result = Matrix(this->rows, this->cols);
  for (size_t idx = 0; idx < this->rows * this->cols; idx++) {
    result.values[idx] = this->values[idx] + other.values[idx];
  }
  return result;
}

template <typename T>
Matrix<T> Matrix<T>::add(T value) {
  Matrix result = Matrix(this->rows, this->cols);
  for (size_t idx = 0; idx < this->rows * this->cols; idx++) {
    result.values[idx] = this->values[idx] + value;
  }
  return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix& other) {
  return this->add(other);
}

template <typename T>
Matrix<T> Matrix<T>::operator+(T value) {
  return this->add(value);
}

template <typename T>
void Matrix<T>::operator+=(const Matrix& other) {
  *this = this->add(other);
}

template <typename T>
void Matrix<T>::operator+=(T value) {
  *this = this->add(value);
}

template <typename T>
Matrix<T> Matrix<T>::subtract(const Matrix& other) {
  if (!is_equal_size(*this, other)) {
    throw Matrix_exception("The matrices do not match in size!");
  }
  Matrix result = Matrix(this->rows, this->cols);
  for (size_t idx = 0; idx < this->rows * this->cols; idx++) {
    result.values[idx] = this->values[idx] - other.values[idx];
  }
  return result;
}

template <typename T>
Matrix<T> Matrix<T>::subtract(T value) {
  return this->add(-value);
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix& other) {
  return this->subtract(other);
}

template <typename T>
Matrix<T> Matrix<T>::operator-(T value) {
  return this->subtract(value);
}

template <typename T>
void Matrix<T>::operator-=(const Matrix& other) {
  *this = this->subtract(other);
}

template <typename T>
void Matrix<T>::operator-=(T value) {
  *this = this->subtract(value);
}

template <typename T>
Matrix<T> Matrix<T>::multiply(const Matrix& other) {
  if (this->cols != other.rows) {
    throw Matrix_exception("The number of columns of the first matrix does not correspond"
                           "to the number of rows of the second matrix!");
  }
  Matrix result = Matrix(this->rows, other.cols);
  for (size_t m = 1; m <= result.rows; m++) {
    for (size_t n = 1; n <= result.cols; n++) {
      T sum = 0.0;
      for (size_t k = 1; k <= this->cols; k++) {
        sum += (*this)[m][k] * other[k][n];
      }
      result[m][n] = sum;
    }
  }
  return result;
}

template <typename T>
Matrix<T> Matrix<T>::multiply(T value) {
  Matrix result = Matrix(this->rows, this->cols);
  for (size_t idx = 0; idx < this->rows * this->cols; idx++) {
    result.values[idx] = this->values[idx] * value;
  }
  return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix& other) {
  return this->multiply(other);
}

template <typename T>
Matrix<T> Matrix<T>::operator*(T value) {
  return this->multiply(value);
}

template <typename T>
void Matrix<T>::operator*=(const Matrix& other) {
  *this = this->multiply(other);
}

template <typename T>
void Matrix<T>::operator*=(T value) {
  *this = this->multiply(value);
}

template <typename T>
Matrix<T> Matrix<T>::divide_by_scalar(T value) {
  if (std::abs(value) < EPS) {
    throw Matrix_exception("Division by zero");
  }
  return this->multiply(1.0 / value);
}

template <typename T>
Matrix<T> Matrix<T>::operator/(T value) {
  if (std::abs(value) < EPS) {
    throw Matrix_exception("Division by zero");
  }
  return this->divide_by_scalar(value);
}

template <typename T>
void Matrix<T>::operator/=(T value) {
  if (std::abs(value) < EPS) {
    throw Matrix_exception("Division by zero");
  }
  *this = this->divide_by_scalar(value);
}

template <typename T>
bool Matrix<T>::operator==(const Matrix& other) const {
  if (this == &other) {
    return true;
  }
  if (this->rows != other.rows || this->cols != other.cols) {
    return false;
  }
  for (size_t idx = 0; idx < this->rows * this->cols; idx++) {
    if (std::abs(this->values[idx] - other.values[idx]) > EPS) {
      return false;
    }
  }
  return true;
}

//Получение треугольной матрицы
template <typename T>
int Matrix<T>::get_triangle_matrix(Matrix& destinationMatrix) {
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
      T ratio = (-1) * destinationMatrix[n][m] / destinationMatrix[m][m];
      for (size_t k = m; k <= destinationMatrix.cols; k++) {
        destinationMatrix[n][k] += destinationMatrix[m][k] * ratio;
      }
    }
  }
  return result;
}

template <typename T>
T Matrix<T>::get_determinant() {
  if (this->cols != this->rows) {
    throw Matrix_exception("The matrix must be square!");
  }
  Matrix matrix;
  int swapCount = this->get_triangle_matrix(matrix);
  return matrix.get_determinant_from_triangle_matrix(swapCount);
}

template <typename T>
Matrix<T> Matrix<T>::get_transposed() {
  Matrix result = Matrix(this->cols, this->rows);
  for (size_t m = 1; m <= this->rows; m++) {
    for (size_t n = 1; n <= this->cols; n++) {
      result[n][m] = (*this)[m][n];
    }
  }
  return result;
}

template <typename T>
T Matrix<T>::get_minor(unsigned int row, unsigned int column) {
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

template <typename T>
Matrix<T> Matrix<T>::get_cofactor() {
  if (this->cols != this->rows) {
    throw Matrix_exception("The matrix must be square!");
  }
  Matrix result = Matrix(this->rows, this->cols);
  for (size_t m = 1; m <= result.rows; m++) {
    for (size_t n = 1; n <= result.cols; n++) {
      T minor = this->get_minor(m, n);
      if ((m + n) % 2 == 1) {
        minor *= -1;
      }
      result[m][n] = minor;
    }
  }
  return result;
}

template <typename T>
Matrix<T> Matrix<T>::get_inverted() {
  Matrix resultMatrix = Matrix();
  T determinant = this->get_determinant();
  Matrix cofactorMatrix = this->get_cofactor();
  resultMatrix = cofactorMatrix.get_transposed();
  resultMatrix = resultMatrix.divide_by_scalar(determinant);
  return resultMatrix;
}

template <typename T>
Matrix<T> Matrix<T>::pow(unsigned int degree) {
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

template <typename T>
Matrix<T> Matrix<T>::get_matrix_exponent(T precision) {
  if (this->cols != this->rows) {
    throw Matrix_exception("The matrix must be square!");
  }
  Matrix last;
  Matrix result = get_identity_matrix(this->rows);
  Matrix power = get_identity_matrix(this->rows);
  bool is_accurate = false;
  int k = 1;
  T factorial = 1;
  while ((!is_accurate) || (k < 150)) {
    last = result;
    power = power.multiply(*this);
    result += power.divide_by_scalar(factorial);
    k++;
    factorial *= k;
    is_accurate = check_accuracy(result, last, precision);
  }
  return result;
}

template <typename T>
typename Matrix<T>::Row_proxy Matrix<T>::operator[](size_t idx) {
  if (((idx - 1) > this->rows) || (idx < 1)) {
    throw Matrix_exception("An attempt to access an element outside the matrix boundary!");
  }
  return Row_proxy(&values[(idx - 1) * cols], cols);
}

template <typename T>
typename Matrix<T>::Row_proxy Matrix<T>::operator[](size_t idx) const {
  if (((idx - 1) > this->rows) || (idx < 1)) {
    throw Matrix_exception("An attempt to access an element outside the matrix boundary!");
  }
  return Row_proxy(&values[(idx - 1) * cols], cols);
}

template <typename T>
std::ostream& operator<<(std::ostream& out, Matrix<T>& matrix) {
  T* current = matrix.values;
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

template <typename T>
std::ostream& operator<<(std::ostream& out, Matrix<T>&& matrix) {
  T* current = matrix.values;
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

template <typename T>
Matrix<T>::Row_proxy::Row_proxy(T* data, size_t size):
    values(data),
    size(size)
{}

template <typename T>
T& Matrix<T>::Row_proxy::operator[](size_t k) {
  if (((k - 1) > size ) || (k < 1)) {
    throw Matrix_exception("An attempt to access an element outside the matrix boundary!");
  }
  return this->values[k - 1];
}

template <typename T>
void Matrix<T>::swap(Matrix& other) {
  std::swap(this->rows, other.rows);
  std::swap(this->cols, other.cols);
  std::swap(this->values, other.values);
}

template <typename T>
T Matrix<T>::get_determinant_from_triangle_matrix(int swapCount) {
  T result = 1;
  for (size_t idx = 1; idx <= this->cols; idx++) {
    result *= (*this)[idx][idx];
  }
  return (swapCount % 2) == 0 ? result : (-1) * result;
}

template <typename T>
bool Matrix<T>::is_equal_size(const Matrix& first, const Matrix& second) {
  if ((first.cols != second.cols) || (first.rows != second.rows)) {
    return false;
  }
  return true;
}

template <typename T>
unsigned int Matrix<T>::get_index_max_col_value(unsigned int index, unsigned int startPosition)
{
  unsigned int result = 0;
  T temp = (*this)[startPosition][index];
  for (size_t idx = startPosition + 1; idx <= this->cols; idx++) {
    if (std::abs((*this)[idx][index]) > std::abs(temp)) {
      temp = (*this)[idx][index];
      result = idx;
    }
  }
  return result;
}

template <typename T>
void Matrix<T>::swap_rows(unsigned int first, unsigned int second)
{
  for (size_t idx = 1; idx <= this->cols; idx++) {
    T temp = (*this)[first][idx];
    (*this)[first][idx] = (*this)[second][idx];
    (*this)[second][idx] = temp;
  }
}

template <typename T>
bool Matrix<T>::is_main_diagonal_has_zero()
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

template <typename T>
bool Matrix<T>::check_accuracy(const Matrix& first, const Matrix& second,
                               T precision) {
  for (size_t m = 1; m <= first.rows; m++) {
    for (size_t n = 1; n <= first.cols; n++) {
      if ((first[m][n] - second[m][n]) > precision) {
        return false;
      }
    }
  }
  return true;
}

template <typename T>
Matrix<T> Matrix<T>::get_identity_matrix(const unsigned int size) {
  Matrix result(size, size);
  for (size_t idx = 1; idx <= size; ++idx) {
    result[idx][idx] = 1;
  }
  return result;
}

template <typename T>
class Matrix_memory : public Matrix<T> {
private:
    unsigned long int memory_allocated;
    static int total_memory;
    static int quantity;
public:
    Matrix_memory<T>();
    Matrix_memory<T>(unsigned int, unsigned int);
    Matrix_memory<T>(unsigned int, unsigned int, T*);
    Matrix_memory<T>(const Matrix_memory&);
    Matrix_memory<T>(Matrix_memory&&) noexcept;
    bool is_equal_size(const Matrix_memory&, const Matrix_memory&);
    Matrix_memory<T> add(const Matrix_memory&);
    ~Matrix_memory();
    Matrix_memory<T>&  operator= (const Matrix_memory&);
    Matrix_memory<T>&  operator= (Matrix_memory&& ) noexcept ;
    void print_mem();

};

template <typename T>
int Matrix_memory<T>::total_memory = 0;

template <typename T>
int Matrix_memory<T>::quantity = 0;

template <typename T>
Matrix_memory<T>::Matrix_memory() : Matrix<T>() {
    memory_allocated = 0;
    quantity++;
}

template <typename T>
Matrix_memory<T>::Matrix_memory(unsigned int rows, unsigned int cols) :
Matrix<T>(rows, cols) {
    memory_allocated = sizeof(T) * rows * cols;
    total_memory += memory_allocated;
    quantity++;
}

template <typename T>
Matrix_memory<T>::Matrix_memory(unsigned int rows, unsigned int cols, T* value):
Matrix<T>(rows, cols, value) {
    memory_allocated = sizeof(T) * rows * cols;
    total_memory += memory_allocated;
    quantity++;
}

template <typename T>
Matrix_memory<T>::~Matrix_memory() {
    total_memory -= memory_allocated;
    memory_allocated = 0;
    quantity--;
}

template <typename T>
Matrix_memory<T>& Matrix_memory<T>::operator=(const Matrix_memory& other) {
    // Добавить синтаксис родительского оператора
    total_memory -= memory_allocated;
    memory_allocated = other.memory_allocated;
    total_memory += memory_allocated;
}

template <typename T>
Matrix_memory<T>& Matrix_memory<T>::operator=(Matrix_memory&& other) noexcept {
    // Добавить синтаксис родительского оператора
    total_memory -= memory_allocated;
    memory_allocated = other.memory_allocated;
    other.memory_allocated = 0;
}

template <typename T>
Matrix_memory<T>::Matrix_memory(const Matrix_memory<T>& other):
    Matrix<T>(other){
    memory_allocated = other.memory_allocated;
    total_memory += memory_allocated;
    quantity++;
}

template <typename T>
Matrix_memory<T>::Matrix_memory(Matrix_memory<T>&& other) noexcept:
    Matrix<T>(other){
    memory_allocated = other.memory_allocated;
    other.memory_allocated = 0;
    quantity++;
}

template <typename T>
bool Matrix_memory<T>::is_equal_size(const Matrix_memory& first,
                                     const Matrix_memory& second) {
    if ((first.cols != second.cols) || (first.rows != second.rows)) {
        return false;
    }
    return true;
}

template <typename T>
Matrix_memory<T> Matrix_memory<T>::add(const Matrix_memory& other) {
    if (!is_equal_size(*this, other)) {
        throw Matrix_exception("The matrices do not match in size!");
    }
    Matrix_memory<T> result(this->rows, this->cols);
    for (size_t idx = 0; idx < this->rows * this->cols; idx++) {
        result.values[idx] = this->values[idx] + other.values[idx];
    }
    result.memory_allocated = sizeof(T) * result.cols * result.rows;
    return result;
}

template <typename T>
void Matrix_memory<T>::print_mem() {
    std::cout << "Allocated " << this->total_memory << " bytes" << std::endl;
    std::cout << "Create " << this->quantity << " matrices\n" << std::endl;
}

#endif
