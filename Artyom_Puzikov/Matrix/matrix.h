#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <cmath>
#include <iostream>
#include <stdexcept>


template<typename T>
class Matrix
{
public:
  Matrix();
  Matrix(size_t rows, size_t columns);
  Matrix(const Matrix &matrix);
  Matrix(Matrix &&matrix) noexcept;
  Matrix& operator=(const Matrix &matrix);
  Matrix& operator=(Matrix &&matrix) noexcept;
  ~Matrix();

  static Matrix getMinor(const Matrix &matrix, size_t minorRow, size_t minor_Col);
  static double getDetMatrix(Matrix matrix);
  static Matrix unit(unsigned int dimention);
  static Matrix copy(const struct Matrix<T> *matrix);
  static Matrix exp_matrix( Matrix<T> matrix, unsigned int accuracy);
  void fillMatrix();
  Matrix operator+(const Matrix &otherMatrix) const;
  Matrix operator-(const Matrix &otherMatrix) const;
  Matrix operator*(const Matrix &otherMatrix) const;
  Matrix operator*(double scalar) const;
  Matrix transpose() const;
  void printValues(std::ostream &out = std::cout) const;

protected:
  size_t columns;
  size_t rows;
  T* values;
};


class Matrix_Exception : public std::runtime_error
{
public:
  Matrix_Exception(const std::string &msg) : std::runtime_error(msg) {}
};


template<typename T>
Matrix<T>::Matrix(size_t rows, size_t columns) : rows(rows), columns(columns)
{
  values = new double[rows * columns];
  for (int i = 0; i < rows * columns; ++i)
  {
    values[i] = T();
  }
}


template<typename T>
Matrix<T>::Matrix(Matrix &&matrix) noexcept
{
  rows = matrix.rows;
  matrix.rows = 0;
  columns = matrix.columns;
  matrix.columns = 0;
  values = std::move(values);
}


template<typename T>
Matrix<T> &Matrix<T>::operator=(Matrix &&matrix) noexcept
{
  rows = matrix.rows;
  columns = matrix.columns;
  values = matrix.values;
  matrix.values = nullptr;
  return *this;
}


template<typename T>
Matrix<T> Matrix<T>::getMinor(const Matrix &matrix, size_t minorRow, size_t minorCol)
{
  Matrix answer(matrix.rows - 1, matrix.columns - 1);
  size_t minor_index = 0;
  for (int i = 0; i < matrix.rows; ++i)
  {
    for (int j = 0; j < matrix.columns; ++j)
    {
      if (i != minorRow && j != minorCol)
      {
        answer.values[minor_index++] = matrix.values[i * matrix.rows + j];
      }
    }
  }
  return answer;
}


template<typename T>
double Matrix<T>::getDetMatrix(Matrix matrix)
{
  if (matrix.rows != matrix.columns)
  {
    throw Matrix_Exception("Rows and columns are not equal\n");
  }
  double answer = 0;
  if (matrix.rows == 2)
  {
    answer = matrix.values[0] * matrix.values[3] - matrix.values[1] * matrix.values[2];
    return answer;
  }
  for (int i = 0; i < matrix.columns; ++i)
  {
    answer += std::pow(-1.0, i) * matrix.values[i] * getDetMatrix(getMinor(matrix, 0, i));
  }
  return answer;
}


template<typename T>
void Matrix<T>::fillMatrix()
{
  for (int i = 0; i < rows * columns; ++i)
  {
    values[i] = i + 1;
  }
}


template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix &otherMatrix) const
{
  if (!(rows == otherMatrix.rows && columns == otherMatrix.columns))
  {
    throw Matrix_Exception("Different size of matrices\n");
  }
  Matrix result(rows, columns);
  for (int i = 0; i < rows * columns; ++i)
  {
    result.values[i] = values[i] + otherMatrix.values[i];
  }
  return result;
}


template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix &otherMatrix) const
{
  if (!(rows == otherMatrix.rows && columns == otherMatrix.columns))
  {
    throw Matrix_Exception("Different size of matrices\n");
  }
  Matrix result(rows, columns);
  for (int i = 0; i < rows * columns; ++i)
  {
    result.values[i] = values[i] - otherMatrix.values[i];
  }
  return result;
}


template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix &otherMatrix) const
{
  if (columns != otherMatrix.rows)
  {
    throw Matrix_Exception("First matrix cols not equal to second matrix rows\n");
  }
  Matrix result(rows, otherMatrix.columns);
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < otherMatrix.columns; ++j)
    {
      for (int k = 0; k < columns; ++k)
      {
        result.values[i * result.columns + j] +=
          values[i * columns + k] * otherMatrix.values[k * otherMatrix.columns + j];
      }
    }
  }
  return result;
}


template<typename T>
Matrix<T> Matrix<T>::operator*(double scalar) const
{
  struct Matrix result(rows, columns);
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < columns; ++j)
    {
      result.values[i * result.columns + j] = values[i * columns + j] * scalar;
    }
  }
  return result;
}


template<typename T>
Matrix<T> Matrix<T>::transpose() const
{
  Matrix result(rows, columns);
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < columns; ++j)
    {
      result.values[i * columns + j] = values[j * rows + i];
    }
  }
  return result;
}

template<typename T>
Matrix<T>::Matrix(const Matrix &matrix)
{
  columns = matrix.columns;
  rows = matrix.rows;
  values = new double[rows * columns];
  for (int i = 0; i < rows * columns; ++i)
  {
    values[i] = matrix.values[i];
  }
}


template<typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix &matrix)
{
  if (&matrix == this)
  {
    return *this;
  }
  columns = matrix.columns;
  rows = matrix.rows;
  for (int i = 0; i < rows * columns; ++i)
  {
    values[i] = matrix.values[i];
  }
  return *this;
}


template<typename T>
Matrix<T>::~Matrix()
{
  delete[] values;
}

template<typename T>
Matrix<T> Matrix<T>::unit(unsigned int dimention)
{
  Matrix<T> result(dimention, dimention);
  for (unsigned int row = 0; row < result.rows; ++row)
  {
    for (unsigned int col = 0; col < result.columns; ++col)
    {
      result.values[row * result.columns + col] = (row == col) ? 1. : 0.;
    }
  }
  return result;
}


template<typename T>
Matrix<T> Matrix<T>::copy(const Matrix<T> *matrix)
{
  Matrix<T> result(matrix->columns ,matrix->rows);
  for (unsigned int index = 0; index < matrix->columns * matrix->rows; ++index)
  {
    result.values[index] = matrix->values[index];
  }
  return result;
}


template<typename T>
Matrix<T> Matrix<T>::exp_matrix(const Matrix<T> matrix, unsigned int accuracy)
{
  if (matrix.columns != matrix.rows)
  {
    throw Matrix_Exception("Matrix is not square");
  }
  Matrix<T> result_, pow_, multiplied;
  Matrix<T> result = unit(matrix.rows);
  Matrix<T> pow = unit(matrix.rows);
  int factorial = 1;
  for (int acc = 1; acc <= accuracy; ++acc)
  {
    factorial *= acc;
    pow_ = pow * matrix;
    pow = copy(&pow_);
    //free(pow_.values);
    multiplied = pow * (1. / factorial);
    result_ = result + multiplied;
    result = copy(&result_);
    //free(result_.values);
    //free(multiplied.values);
  }
  //free(pow.values);
  return result;
}

template<typename T>
void Matrix<T>::printValues(std::ostream &out) const
{
  out.setf(std::ios::fixed);
  out.setf(std::ios::showpoint);
  out.precision(2);
  for (int i = 0; i < this->rows; ++i)
  {
    for (int j = 0; j < this->columns; ++j)
    {
      out << this->values[i * this->columns + j] << ' ';
    }
    out << '\n';
  }
}

template<typename T>
Matrix<T>::Matrix()
{
  rows = T();
  columns = T();
  values = nullptr;
}



template <typename T>
class Matrix_Mem : public Matrix<T> {
protected:
  unsigned int mem_size;
  static unsigned int quantity;
  static unsigned int total_memory;

public:
  Matrix_Mem();
  //Matrix_Mem(const unsigned int n);
  Matrix_Mem(const unsigned int row, unsigned int col);
  Matrix_Mem(const Matrix_Mem<T> &x);
  Matrix_Mem(Matrix_Mem<T> &&x);
  ~Matrix_Mem();

  Matrix_Mem<T>& operator=(const Matrix_Mem<T> &other);
  Matrix_Mem<T>& operator=(Matrix_Mem<T> &&other);
  Matrix_Mem<T>& operator*=(const Matrix_Mem<T> &other);

  void report();

  static int get_quantity() { return quantity; }
  static int get_mem() { return total_memory; }

  Matrix_Mem(Matrix<double> matrix);
};

template <typename T>
unsigned int Matrix_Mem<T>::total_memory = 0;
template <typename T>
unsigned int Matrix_Mem<T>::quantity = 0;

template <typename T>
Matrix_Mem<T>::Matrix_Mem():Matrix<T>(){
  mem_size = 0;
  quantity++;
  total_memory += mem_size;
}

/*template <typename T>
Matrix_Mem<T>::Matrix_Mem(const unsigned int n):Matrix<T>(n){
  mem_size = n * n * sizeof (T);
  quantity++;
  total_memory += mem_size;
}*/

template <typename T>
Matrix_Mem<T>::Matrix_Mem(const unsigned int row, unsigned int col):Matrix<T>(row, col){
  mem_size = row * col * sizeof (T);
  quantity++;
  total_memory += mem_size;
}

template <typename T>
Matrix_Mem<T>::Matrix_Mem(const Matrix_Mem<T> &other):Matrix<T>(other){
  mem_size = other.mem_size;
  quantity++;
  total_memory += mem_size;
}

template <typename T>
Matrix_Mem<T>::Matrix_Mem(Matrix_Mem<T> &&other):Matrix<T>(other){
  total_memory -= mem_size;
  mem_size = other.mem_size;
  other.mem_size = 0;
  total_memory += mem_size;
}

template <typename T>
Matrix_Mem<T>::~Matrix_Mem(){
  quantity--;
  total_memory -= mem_size;;
}

template<typename T>
Matrix_Mem<T>& Matrix_Mem<T>::operator=(const Matrix_Mem<T> &other) {
  if (other == *this) return other;
  this->rows = other.rows;
  this->columns = other.columns;
  delete[] this->values;
  this->values = new double[other.rows * other.columns];
  memcpy(this->values, other.values, this->rows * this->columns * sizeof(T));
  return *this;
}

template<typename T>
Matrix_Mem<T>& Matrix_Mem<T>::operator=(Matrix_Mem<T> &&other) {
  if (this == &other) {return *this;}
  this->rows = other.rows;
  this->columns = other.columns;
  this->values = other.values;
  other.values = nullptr;
  mem_size = other.mem_size;
  total_memory += mem_size;
  return *this;
}

template <typename T>
Matrix_Mem<T>& Matrix_Mem<T>::operator*=(const Matrix_Mem<T> &other) {
  if (this->columns != this->M1.rows)  {
    throw Matrix_Exception("Err");
  }
  Matrix_Mem M0(this->rows);
  for (unsigned int row = 0; row < M0.rows; row++) {
    for (unsigned int col = 0; col < M0.columns; col++) {
      double sum = 0;
      for (unsigned int k = 0; k < M0.rows; k++) {
        sum += this->values[row * this->columns + k] * other.values[k * other.columns + col];
      }
      M0.values[row * M0.columns + col] = sum;
    }
  }
  *this = M0;
  return (*this);
}

template <typename T>
void Matrix_Mem<T>::report() {
  std::cout << "variable weight is " << mem_size << std::endl ;
  std::cout << "Number of variables " << get_quantity() << std::endl;
  std::cout << "Total memory used " << get_mem() << std::endl;
}


#endif
