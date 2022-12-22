#ifndef MATRIX_H
#define MATRIX_H

#include <iosfwd>

class Matrix {
public:
  Matrix();
  Matrix(const Matrix&);
  Matrix(Matrix&&) noexcept;
  Matrix(unsigned int, unsigned int);
  Matrix(unsigned int, unsigned int, const double*);
  Matrix& operator=(const Matrix&);
  Matrix& operator=(Matrix&&) noexcept;
  ~Matrix();

  unsigned int getRowsCount() const;
  unsigned int getColumnsCount() const;
  double getValue(unsigned int, unsigned int) const;
  void setValue(double, unsigned int, unsigned int);

  Matrix add(const Matrix&);
  Matrix add(double);
  Matrix operator+(const Matrix&);
  Matrix operator+(double);
  void operator+=(const Matrix&);
  void operator+=(double);
  Matrix subtract(const Matrix&);
  Matrix subtract(double);
  Matrix operator-(const Matrix&);
  Matrix operator-(double);
  void operator-=(const Matrix&);
  void operator-=(double);
  Matrix multiply(const Matrix&);
  Matrix multiply(double);
  Matrix operator*(const Matrix&);
  Matrix operator*(double);
  void operator*=(const Matrix&);
  void operator*=(double);
  Matrix divideByScalar(double);
  Matrix operator/(double);
  void operator/=(double);
  bool operator==(const Matrix&) const;
  int getTriangleMatrix(Matrix& destinationMatrix);
  double getDeterminant();
  Matrix getTransposed();
  double getMinor(unsigned int, unsigned int);
  Matrix getCofactor();
  Matrix getInverted();
  Matrix pow(unsigned int);
  Matrix getMatrixExponent(double);

  class RowProxy {
  public:
    RowProxy(double*, size_t);
    double& operator[](size_t j);
  private:
    double* values_;
    size_t size_;
  };
  RowProxy operator[](size_t i);
  RowProxy operator[](size_t i) const;

  friend std::ostream& operator<<(std::ostream&, Matrix&);
  friend std::ostream& operator<<(std::ostream&, Matrix&&);

private:
  unsigned int rowsCount_;
  unsigned int columnsCount_;
  double* values_;

  void swap(Matrix&);
  double getDeterminantFromTriangleMatrix(int swapCount);
  static bool isEqualSize(const Matrix&, const Matrix&);
  unsigned int getIndexMaxColValue(unsigned int, unsigned int);
  void swapRow(unsigned int, unsigned int);
  bool isMatrixDiagonalHasZero();
  unsigned int calculateFactorial(unsigned int);
  static bool checkAccuracy(const Matrix&, const Matrix&, double);

};

#endif
