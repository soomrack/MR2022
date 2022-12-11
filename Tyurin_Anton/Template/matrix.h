#ifndef UNTITLED_MATRIX_H
#define UNTITLED_MATRIX_H

template<typename T>
class Matrix {
private:
    double PRECISION = 0.001;
    unsigned int cols;
    unsigned int rows;
    T *values;
public:
    Matrix(unsigned int cols_m, unsigned int rows_m);
    Matrix(const Matrix &A);
    Matrix(Matrix&& A) noexcept;
    explicit Matrix(unsigned int cols_m);
    ~Matrix();

    static Matrix data_input(Matrix *matrix, const double arr[]);
    static void print_matrix(const Matrix& matrix);
    static void print_matrix(const Matrix& matrix, char symbol);
    static Matrix exp(const Matrix& A);
    void fill_with(double Number);
    void is_equal(const Matrix &X);

    Matrix operator+(const Matrix& X) const;
    Matrix operator-(const Matrix& X) const;
    Matrix operator*(const Matrix& X) const;
    Matrix operator=(Matrix& X);
    Matrix operator=(Matrix&& X) noexcept;
    Matrix operator^(double X) const;
    Matrix operator/ (const Matrix& X) const;
    Matrix operator/ (double X) const;
    };
#endif //UNTITLED_MATRIX_H
