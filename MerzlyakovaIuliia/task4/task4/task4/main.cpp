
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>

class Matrix_Exception : public std::domain_error
{
public:
    Matrix_Exception(const char* const message) : std::domain_error(message)
    {}
};

Matrix_Exception NOTSQUARE("Make matrix square\n");
Matrix_Exception ERRORSIZE("Change matrix size\n");

template<typename T>
class Matrix{
protected:
    unsigned int cols;
    unsigned int rows;
    T *values;

public:
    Matrix();
    Matrix(unsigned int col, unsigned int row);
    Matrix(unsigned int col);
    Matrix(const Matrix& matrix);
    Matrix(Matrix&& matrix);
    ~Matrix();


    virtual void report();
    void set_values(const unsigned int);

    Matrix<T> operator+(const Matrix<T>&);
    Matrix<T> operator-(const Matrix<T>&);
    Matrix<T> operator*(const Matrix<T>&);
    Matrix<T> operator*(const T);
    Matrix<T> operator/(const T) const;
    Matrix<T> exponent(const Matrix<T>&, const unsigned int);
    Matrix<T> minor(Matrix<T>&, const unsigned int row, const unsigned int col);
    Matrix<T> transpose();
    double determinant(const Matrix<T>&);

    Matrix<T>& operator=(const Matrix<T>&);
    friend std::ostream& operator<<(std::ostream& out, Matrix<T> matrix)
    {
        {
            for(unsigned int row = 0; row < matrix.rows; row++)
            {
                for(unsigned int col = 0; col <matrix.cols; col++)
                {
                    out << matrix.values[row*matrix.cols +col] << "\t";
                }
                out << std::endl;
            }
            out << std::endl;
            return out;
        }
    }
};


template <typename T>
Matrix<T>::Matrix() {
    cols = 0;
    rows = 0;
    values = nullptr;
//    std:: cout << "matrix_f" << "\n";
}

template <typename T>
Matrix<T>:: ~Matrix()
{
    if (values != nullptr)
        delete [] values;
}

template <typename T>
Matrix<T>::Matrix(unsigned int col, unsigned int row) {
    cols = col;
    rows = row;
    unsigned int n_values = cols * rows;
    values = new T[cols*rows];
    for (unsigned int idx = 0; idx < n_values; ++idx) {
        values[idx] = 0.0;
    }
//    std:: cout << "matrix_2p" << "\n";
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& matrix) {
    cols = matrix.cols;
    rows = matrix.rows;
    values = new T[rows * cols];
    memcpy(values,matrix.values,rows * cols * sizeof(T));
//    std::cout << "matrix_copy ";
}


template <typename T>
Matrix<T>::Matrix(Matrix<T>&& matrix) {
    cols = matrix.cols;
    rows = matrix.rows;
    values = matrix.values;
    matrix.values = nullptr;
    matrix.rows = 0;
    matrix.cols = 0;
}

template <typename T>
void Matrix<T>::report() {
    for (unsigned int row = 0; row < rows; ++row) {
        for (unsigned int col = 0; col < cols; ++col) {
            std::cout << values[row * cols + col] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

template <typename T>
void Matrix<T>::set_values(const unsigned int n) {
    for (unsigned int index = 0; index < rows * cols; ++index) {
        values[index] = rand() % n;
    }
}

template <typename T>
Matrix<T>::Matrix(unsigned int col) {
    cols = col;
    rows = col;
    values = new T[cols * rows];
    for (unsigned int row = 0; row < rows; row++) {
        for (unsigned int col = 0; col < cols; col++) {
            values[row * cols + col] = (row == col) ? 1 : 0;

        }
    }
}

template <typename T>
Matrix<T> Matrix<T>::operator+ (const Matrix<T>& matrix) {
    if (rows != matrix.rows) throw ERRORSIZE;
    Matrix result(matrix);
    for (unsigned int idx = 0; idx < matrix.cols * matrix.rows; idx++) {
        result.values[idx] += values[idx];
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator- (const Matrix<T>& matrix)  {
    if (rows != matrix.rows) throw ERRORSIZE;
    Matrix result(matrix);
    for (unsigned int idx = 0; idx < matrix.cols * matrix.rows; idx++) {
        result.values[idx] -= values[idx];
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator* (const Matrix<T>& matrix)  {
    if (rows != matrix.rows) throw ERRORSIZE;
    Matrix result(matrix);
    for (unsigned int row = 0; row < result.rows; row++) {
        for (unsigned int col = 0; col < result.cols; col++) {
            result.values[row* result.rows + col] = 0.00;
            for (unsigned int k = 0; k < result.cols; k++) {
                result.values[row * result.cols + col] += values[row * cols + k] * matrix.values[k * result.cols + col];
            }
        }
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator* (const T number) {
    Matrix result(cols, rows);
    for (unsigned int idx = 0; idx < rows * cols; idx++) {
        result.values[idx] = values[idx] * number;
    }
    return result;
}


template <typename T>
Matrix<T>& Matrix<T>::operator= (const Matrix<T>& matrix)  {
    if (this == &matrix) {
        return *this;
    }
    rows = matrix.rows;
    cols = matrix.cols;
    delete[]values;
    values = new T[cols * rows];
    memcpy(values, matrix.values, rows * cols * sizeof(T));
    return *this;
}



template <typename T>
Matrix<T> Matrix<T>::operator/(const T number) const {
    Matrix result(cols, rows);
    for(unsigned int idx = 0; idx < rows * cols; ++idx) {
        result.values[idx] = values[idx]/number;
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::exponent(const Matrix<T>& A, const unsigned int accuracy){
    if (A.rows != A.cols) throw NOTSQUARE;
    Matrix result(A.cols);
    Matrix temp(A.cols);
    double factorial = 1.0;
    for (int step = 1; step < accuracy; step++) {
        factorial *= step;
        temp = temp * A;
        result = result + temp / factorial;
    }
    return result;
}


template <typename T>
Matrix<T> Matrix<T>::minor(Matrix<T>& A, unsigned int row, unsigned int col) {
    int new_row = A.rows -1;
    int new_col = A.cols - 1;
    if (row >= A.rows) new_row++;
    if (col >= A.cols) new_col++;

    Matrix result = Matrix(new_row, new_col);
    unsigned int k = 0;

    for (unsigned int idx = 0; idx < rows * cols; idx++){
        if ((idx % cols == col) or (idx / cols == row)) continue;
        result.values[k++] = A.values[idx];
    }

    return result;
}
template <typename T>
Matrix<T> Matrix<T>::transpose() {
    Matrix result = {cols, rows};
    for (unsigned int row = 0; row < result.rows; row++) {
        for (unsigned int col = 0; col < result.cols; col++) {
            result.values[row * result.cols + col] = values[col * result.cols + row];
        }
    }
    return result;
}

template <typename T>
double Matrix<T>::determinant(const Matrix<T>& matrix)
{
    if(cols != rows) throw NOTSQUARE;
    double det = 0;
    int sign = 1;
    if (rows == 0 and cols == 0)
        return 0;
    if (rows == 1 and cols == 1)
        return matrix.values[0];
    if (rows == 2 and cols == 2) {
        return (matrix.values[0] * matrix.values[3] - matrix.values[2] * matrix.values[1]);
    }
    for (unsigned int idx = 0; idx < rows; idx++) {
        det += sign * matrix.values[idx] * determinant(Minor(matrix, 0, idx), rows - 1);
        sign = -sign;
    }
    return det;
}

template <typename T1>
class Matrix_Memory : public Matrix<T1> {
private:
    unsigned long memory_size;
    static unsigned long total_memory;
public:
    Matrix_Memory<T1>();
    Matrix_Memory<T1>(unsigned int row, unsigned int col);
    Matrix_Memory<T1>(const Matrix_Memory<T1>&);
    Matrix_Memory<T1>(Matrix_Memory<T1>&&) noexcept;
    ~Matrix_Memory();
    
    Matrix_Memory<T1>& operator=(const  Matrix_Memory<T1>& );
    Matrix_Memory<T1>& operator=(const  Matrix_Memory<T1>&& );
    void report() override;
};

template <typename T>
Matrix_Memory<T>&::Matrix_Memory<T>::operator=(const Matrix_Memory<T> &matrix) {
    if (this == &matrix)
    {
        return *this;
    }
    this->rows = matrix.rows;
    this->cols = matrix.cols;
    delete[] this->values;
    total_memory -= matrix.memory_size;
    this->values = new T[this->cols * this->rows];
    memcpy(this->values, matrix.values, this->rows * this->cols * sizeof(T));
    memory_size += matrix.memory_size;
    total_memory += memory_size;
    return *this;
}

template <typename T>
Matrix_Memory<T>&::Matrix_Memory<T>::operator=(const Matrix_Memory<T> &&matrix) {
    if (this == &matrix)
    {
        return *this;
    }
    this->rows = matrix.rows;
    this->cols = matrix.cols;
    delete[] this->values;
    total_memory -= matrix.memory_size;
    this -> values = matrix.values;
    matrix.values = nullptr;
    matrix.memory_size = 0;
    return *this;
}

template <typename T>
Matrix_Memory<T>::Matrix_Memory()
{
    this->memory_size += 0;
    this->total_memory += 0;
}


template <typename T>
Matrix_Memory<T>::Matrix_Memory(unsigned int row, unsigned int col) : Matrix<T>(row, col)
{
//    this->rows = row;
//    this->cols = col;
//    this->values = new T[this->rows * this->cols];
    memory_size = row * col * sizeof(T);
    total_memory += memory_size;
//    std::cout << "matrix_mem";
}


template <typename T>
Matrix_Memory<T>::~Matrix_Memory()
{
    total_memory -= memory_size;
}
template <typename T>
Matrix_Memory<T>::Matrix_Memory(const Matrix_Memory<T>& matrix) : Matrix<T>(matrix)
{
    memory_size = matrix.memory_size;
    total_memory += memory_size;
}


template <typename T>
Matrix_Memory<T>::Matrix_Memory(Matrix_Memory<T>&& matrix) noexcept
{
    this -> rows = matrix.rows;
    this -> cols = matrix.cols;
    this -> values = new T[this->rows * this->cols];
    memory_size = matrix.memory_size;
    total_memory += memory_size;
    matrix.rows = 0;
    matrix.cols = 0;
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
//template <typename T>
//unsigned long int Matrix_Memory<T>::memory_size = 0;

int main() {
    Matrix_Memory<double> mat1(3,3);
    //std:: cout << mat1;
    mat1.set_values(10);
    std:: cout << mat1;
    Matrix_Memory<double> mat2(3, 3);
    mat2.set_values(10);
    std:: cout << mat2;
    std::cout << mat1 + mat2;
    std::cout << mat1 - mat2;
    std::cout << mat1 * mat2;
    std::cout << mat1 * 3;
    std::cout << mat1 / 3;
    std::cout << mat1.exponent(mat1,30);
    mat1.report();
    return 0;
}
