#include "matrix.h"
#include <cmath>
#include <iostream>
#include <stdexcept>

Matrix::Matrix(size_t rows, size_t columns) : rows_(rows), columns_(columns)
{
  values_.resize(columns_ * rows_);
}

Matrix::Matrix(Matrix &&matrix) noexcept
{
  rows_ = matrix.rows_;
  matrix.rows_ = 0;
  columns_ = matrix.columns_;
  matrix.columns_ = 0;
  values_ = std::move(matrix.values_);
}

Matrix &Matrix::operator=(Matrix &&matrix) noexcept
{
  rows_ = matrix.rows_;
  matrix.rows_ = 0;
  columns_ = matrix.columns_;
  matrix.columns_ = 0;
  values_ = std::move(matrix.values_);
  return *this;
}

Matrix Matrix::getMinor(const Matrix &matrix, size_t minorRow, size_t minorCol)
{
  Matrix answer(matrix.rows_ - 1, matrix.columns_ - 1);
  size_t minor_index = 0;
  for (int i = 0; i < matrix.rows_; ++i)
  {
    for (int j = 0; j < matrix.columns_; ++j)
    {
      if (i != minorRow && j != minorCol)
      {
        answer.values_[minor_index++] = matrix.values_[i * matrix.rows_ + j];
      }
    }
  }
  return answer;
}

double Matrix::getDetMatrix(Matrix matrix)
{
  if (matrix.rows_ != matrix.columns_)
  {
    throw std::logic_error("Rows and columns are not equal\n");
  }
  double answer = 0;
  if (matrix.rows_ == 2)
  {
    answer = matrix.values_[0] * matrix.values_[3] - matrix.values_[1] * matrix.values_[2];
    return answer;
  }
  for (int i = 0; i < matrix.columns_; ++i)
  {
    answer += std::pow(-1.0, i) * matrix.values_[i] * getDetMatrix(getMinor(matrix, 0, i));
  }
  return answer;
}

void Matrix::fillMatrix()
{
  for (int i = 0; i < rows_ * columns_; ++i)
  {
    values_[i] = i + 1;
  }
}

Matrix Matrix::operator+(const Matrix &otherMatrix) const
{
  if (!(rows_ == otherMatrix.rows_ && columns_ == otherMatrix.columns_))
  {
    throw std::invalid_argument("Error\n");
  }
  Matrix result(rows_, columns_);
  for (int i = 0; i < rows_ * columns_; ++i)
  {
    result.values_[i] = values_[i] + otherMatrix.values_[i];
  }
  return result;
}

Matrix Matrix::operator-(const Matrix &otherMatrix) const
{
  if (!(rows_ == otherMatrix.rows_ && columns_ == otherMatrix.columns_))
  {
    throw std::invalid_argument("Error\n");
  }
  Matrix result(rows_, columns_);
  for (int i = 0; i < rows_ * columns_; ++i)
  {
    result.values_[i] = values_[i] - otherMatrix.values_[i];
  }
  return result;
}

Matrix Matrix::operator*(const Matrix &otherMatrix) const
{
  if (columns_ != otherMatrix.rows_)
  {
    throw std::invalid_argument("Error\n");
  }
  Matrix result(rows_, otherMatrix.columns_);
  for (int i = 0; i < rows_; ++i)
  {
    for (int j = 0; j < otherMatrix.columns_; ++j)
    {
      for (int k = 0; k < columns_; ++k)
      {
        result.values_[i * result.columns_ + j] +=
          values_[i * columns_ + k] * otherMatrix.values_[k * otherMatrix.columns_ + j];
      }
    }
  }
  return result;
}

Matrix Matrix::operator*(double scalar) const
{
  struct Matrix result(rows_, columns_);
  for (int i = 0; i < rows_; ++i)
  {
    for (int j = 0; j < columns_; ++j)
    {
      result.values_[i * result.columns_ + j] = values_[i * columns_ + j] * scalar;
    }
  }
  return result;
}

Matrix Matrix::transpose() const
{
  Matrix result(rows_, columns_);
  for (int i = 0; i < rows_; ++i)
  {
    for (int j = 0; j < columns_; ++j)
    {
      result.values_[i * columns_ + j] = values_[j * rows_ + i];
    }
  }
  return result;
}

std::ostream &operator<<(std::ostream &out, const Matrix &matrix)
{
out.setf(std::ios::fixed);
out.setf(std::ios::showpoint);
out.precision(2);
for (int i = 0; i < matrix.rows_; ++i)
{
for (int j = 0; j < matrix.columns_; ++j)
{
out << matrix.values_[i * matrix.columns_ + j] << ' ';
}
out << '\n';
}
return out;
}
