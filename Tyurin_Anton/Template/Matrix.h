#ifndef UNTITLED_MATRIX_H
#define UNTITLED_MATRIX_H


template<typename T>
class Matrix {
private:
    double PRECISION = 0.001;
protected:
    unsigned int rows;
    T *values;
    unsigned int cols;
public:
    Matrix(unsigned int cols_m, unsigned int rows_m);
    Matrix(const Matrix &A);
    Matrix(Matrix&& A) noexcept;
    explicit Matrix(unsigned int cols_m);
    ~Matrix();

    static Matrix data_input(Matrix<T> *matrix, const T arr[]);
    static void print_matrix(const Matrix<T>& matrix);
    static void print_matrix(const Matrix<T>& matrix, char symbol);
    static Matrix exp(const Matrix<T>& A);
    void fill_with(T Number);
    void is_equal(const Matrix<T> &X);

    Matrix operator+(const Matrix<T>& X) const;
    Matrix operator-(const Matrix<T>& X) const;
    Matrix operator*(const Matrix<T>& X) const;
    Matrix operator=(Matrix<T>& X);
    Matrix operator=(Matrix<T>&& X) noexcept;
    Matrix operator^(T X) const;
    Matrix operator/ (const Matrix<T>& X) const;
    Matrix operator/ (T X) const;
    };


#endif //UNTITLED_MATRIX_H
