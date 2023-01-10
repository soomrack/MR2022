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

  unsigned int get_rows_count() const;
  unsigned int get_cols_count() const;
  double get_value(unsigned int, unsigned int) const;
  void set_value(double, unsigned int, unsigned int);

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
  Matrix divide_by_scalar(double);
  Matrix operator/(double);
  void operator/=(double);
  bool operator==(const Matrix&) const;
  int get_triangle_matrix(Matrix& destinationMatrix);
  double get_determinant();
  Matrix get_transposed();
  double get_minor(unsigned int, unsigned int);
  Matrix get_cofactor();
  Matrix get_inverted();
  Matrix pow(unsigned int);
  Matrix get_identity_matrix(unsigned int size);
  Matrix get_matrix_exponent(double);


  class Row_proxy {
  public:
    Row_proxy(double*, size_t);
    double& operator[](size_t idx);
  private:
    double* values;
    size_t size;
  };
  Row_proxy operator[](size_t idx);
  Row_proxy operator[](size_t idx) const;

  friend std::ostream& operator<<(std::ostream&, Matrix&);
  friend std::ostream& operator<<(std::ostream&, Matrix&&);

private:
  unsigned int rows;
  unsigned int cols;
  double* values;

  void swap(Matrix&);
  void swap_rows(unsigned int, unsigned int);
  unsigned int get_index_max_col_value(unsigned int, unsigned int);
  double get_determinant_from_triangle_matrix(int swap_count);
  static bool is_equal_size(const Matrix&, const Matrix&);
  static bool check_accuracy(const Matrix&, const Matrix&, double);
  bool is_main_diagonal_has_zero();

};

#endif
