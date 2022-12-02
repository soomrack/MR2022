#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <vector>
#include <iosfwd>


class Matrix
{
public:
  Matrix(size_t rows, size_t columns);
  Matrix(const Matrix &matrix) = default;
  Matrix(Matrix &&matrix) noexcept;
  Matrix& operator=(const Matrix &matrix) = default;
  Matrix& operator=(Matrix &&matrix) noexcept;
  ~Matrix()=default;

  static Matrix getMinor(const Matrix &matrix, size_t minorRow, size_t minor_Col);
  static double getDetMatrix(Matrix matrix);
  void fillMatrix();
  Matrix operator+(const Matrix &otherMatrix) const;
  Matrix operator-(const Matrix &otherMatrix) const;
  Matrix operator*(const Matrix &otherMatrix) const;
  Matrix operator*(double scalar) const;
  Matrix transpose() const;
  friend std::ostream &operator<<(std::ostream &out, const Matrix &matrix);

private:
  size_t columns_;
  size_t rows_;
  std::vector<double> values_;
};


#endif
