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

  static Matrix minor(const Matrix &matrix, size_t minor_row, size_t minor_col);
  static double det_matrix(Matrix matrix);
  static Matrix unit(unsigned int dimention);
  static Matrix exp_matrix( Matrix<T> matrix, unsigned int accuracy);
  void fill_matrix();
  Matrix operator+(const Matrix &otherMatrix) const;
  Matrix operator-(const Matrix &otherMatrix) const;
  Matrix operator*(const Matrix &otherMatrix) const;
  Matrix operator*(double scalar) const;
  Matrix transpose() const;
  void print_values(std::ostream &out = std::cout) const;

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
Matrix<T> Matrix<T>::minor(const Matrix &matrix, size_t minor_row, size_t minor_col)
{
  Matrix answer(matrix.rows - 1, matrix.columns - 1);
  size_t minor_index = 0;
  for (int i = 0; i < matrix.rows; ++i)
  {
    for (int j = 0; j < matrix.columns; ++j)
    {
      if (i != minor_row && j != minor_col)
      {
        answer.values[minor_index++] = matrix.values[i * matrix.rows + j];
      }
    }
  }
  return answer;
}


template<typename T>
double Matrix<T>::det_matrix(Matrix matrix)
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
    answer += std::pow(-1.0, i) * matrix.values[i] * det_matrix(minor(matrix, 0, i));
  }
  return answer;
}


template<typename T>
void Matrix<T>::fill_matrix()
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
    pow = pow_;
    multiplied = pow * (1. / factorial);
    result_ = result + multiplied;
    result = result_;
  }
  return result;
}

template<typename T>
void Matrix<T>::print_values(std::ostream &out) const
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


template <typename T1>
class Matrix_Memory : public Matrix<T1> {
private:
  static unsigned long memory_size;
  static unsigned long total_memory;
public:
  Matrix_Memory<T1>();
  Matrix_Memory<T1>(unsigned int, unsigned int);
  Matrix_Memory<T1>(const Matrix_Memory<T1>&);
  Matrix_Memory<T1>(Matrix_Memory<T1>&&) noexcept;
  ~Matrix_Memory();
  Matrix_Memory<T1>&  operator= (const  Matrix_Memory<T1>& );
  void report();
};

template <typename T>
Matrix_Memory<T>&::Matrix_Memory<T>::operator=(const Matrix_Memory<T> &matrix) {
  if (this == &matrix)
  {
    return *this;
  }
  this->rows = matrix.rows;
  this->columns = matrix.columns;
  delete[] this->values;
  this->values = new T[this->columns * this->rows];
  memcpy(this->values, matrix.values, this->rows * this->columns * sizeof(T));
  memory_size += matrix.memory_size;
  total_memory += memory_size;
  return *this;
}

template <typename T>
Matrix_Memory<T>::Matrix_Memory()
{
  this->memory_size += 0;
  this->total_memory += 0;
}


template <typename T>
Matrix_Memory<T>::Matrix_Memory(unsigned int row, unsigned int col)
{
  this->rows = row;
  this->columns = col;
  this->values = new T[this->rows * this->columns];
  memory_size = row * col * sizeof(T);
  total_memory += memory_size;
}


template <typename T>
Matrix_Memory<T>::~Matrix_Memory()
{
  total_memory -= memory_size;
}
template <typename T>
Matrix_Memory<T>::Matrix_Memory(const Matrix_Memory<T>& matrix)
{
  this->values = new T[this->rows * this->cols];
  memcpy(this->values, matrix.values, sizeof(T) * this->rows * this->columns);
  memory_size = matrix.memory_size;
  total_memory += memory_size;
}


template <typename T>
Matrix_Memory<T>::Matrix_Memory(Matrix_Memory<T>&& matrix) noexcept
{

  memory_size = matrix.memory_size;

  matrix.rows = 0;
  matrix.columns = 0;
  matrix.values = nullptr;
  matrix.memory_size = 0;
}


template <typename T>
void Matrix_Memory<T>::report()
{
  std::cout << "Total memory " << this->total_memory << " byte" << std::endl;
}

template <typename T>
unsigned long int Matrix_Memory<T>::total_memory = 0;
template <typename T>
unsigned long int Matrix_Memory<T>::memory_size = 0;

#endif
