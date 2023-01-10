#include <iostream>
#include <ctime>
#include <windows.h>
#include <cmath>
#include <type_traits>
#include <iostream>

using namespace std;

long int total_mem = 0;

class Matrix_Exception : public  domain_error
{
public:
    Matrix_Exception(const char* const msg) : domain_error(msg)
    {
    }
};

Matrix_Exception Not_Square("Error:the matrix must be square(should have nxn size)\n");
Matrix_Exception Not_Equal("Error: the matrix should have a same size\n");
Matrix_Exception Multiply_Error("Error: first matrix cols not equal to second matrix row.\n");
Matrix_Exception Zero_division("Error: divide by zero\n");
Matrix_Exception Mem_Error("Error: memory are not allocated\n");

template<typename T>
class Matrix
{
protected:

    unsigned int rows;
    unsigned int cols;
    T* values;

public:

    static_assert
        (is_same<double, T>::value || is_same<float, T>::value || is_same<long double, T>::value,
            "T must be int, double or float");

    const double EPS = 0.000001;

    Matrix(unsigned int, unsigned int, T*);
    Matrix(unsigned int, unsigned int);
    Matrix();
    Matrix(const Matrix&);                  // Конструктор копирования матрицы
    Matrix(Matrix&&) noexcept;              // Конструктор переноса матрицы
    ~Matrix();


    T* getvalues();
    unsigned int getrow();
    unsigned int getcol();
    virtual void output();
    Matrix<T> fill_random(unsigned int n);
    Matrix<T> set_zero();
    Matrix<T> set_identity();
    Matrix set_transpose();
    Matrix fill_from_array(T*);
    double determinant(const Matrix<T>, const unsigned int);
    Matrix reverse(const Matrix<T>, const unsigned int);
    Matrix minor(const Matrix<T>, const unsigned, const unsigned, const unsigned);
    Matrix exponent(unsigned int);


    bool operator!=(const Matrix<T>&);
    bool operator==(const Matrix<T>&);

    Matrix& operator=(const Matrix<T>&);
    Matrix& operator-=(const Matrix<T>&);
    Matrix& operator+=(const Matrix<T>&);
    Matrix& operator*=(const Matrix<T>&);
    Matrix& operator*=(const T);
    Matrix& operator/=(const T);

    Matrix<T> operator+ (const Matrix<T>&);
    Matrix<T> operator- (const Matrix<T>&);
    Matrix<T> operator* (const Matrix<T>&);
    Matrix<T> operator* (const T);
    Matrix<T> operator/ (const T);

    friend  ostream& operator<<(ostream& out, Matrix<T> matrix)
    {
        {
            for (unsigned int row = 0; row < matrix.rows; row++)
            {
                for (unsigned int col = 0; col < matrix.cols; col++)
                {
                    out << matrix.values[row * matrix.cols + col] << "\t";
                }
                out << endl;
            }
            out << endl;
            return(out);
        }
    }
};


template <typename T>
Matrix<T>::Matrix(unsigned int R, unsigned int C, T* value)
{
    rows = R;
    cols = C;
    values = new T[rows * cols];
    if (!values) throw Mem_Error;
    memcpy(values, value, sizeof(T) * rows * cols);
    total_mem = sizeof(T) * rows * cols;
}

template <typename T>
Matrix<T>::Matrix(unsigned int R, unsigned int C)
{
    rows = R;
    cols = C;
    values = new T[rows * cols];
    if (!values) throw Mem_Error;
    total_mem = sizeof(T) * rows * cols;
}

template <class T>
Matrix<T>::Matrix(Matrix&& mat) noexcept : values(mat.values), rows(mat.rows), cols(mat.cols)
{
    mat.values = nullptr;
    mat.rows = 0;
    mat.cols = 0;
}

template <class T>
Matrix<T>::Matrix() : rows(0), cols(0), values(nullptr)
{
}


template <class T>
Matrix<T>::Matrix(const Matrix& mat) : rows(mat.rows), cols(mat.cols)
{
    values = new T[rows * cols];
    if (!values) throw Mem_Error;
    memcpy(values, mat.values, rows * cols * sizeof(T));
}


template <typename T>
Matrix<T>::~Matrix()
{
    if (values != nullptr)
    {
        delete[] values;
    }
}


template <typename T>
unsigned int Matrix<T>::getrow()
{
    return (rows);
}


template <typename T>
unsigned int Matrix<T>::getcol()
{
    return (cols);
}


template <typename T>
T* Matrix<T>::getvalues()
{
    T* data = new T[rows * cols];
    memcpy(data, values, sizeof(T) * rows * cols);
}


template <typename T>
Matrix<T> Matrix<T>::set_zero()
{
    for (unsigned int idx = 0; idx < this->rows * this->cols; idx++)
    {
        this->values[idx] = 0;
    }
    return (*this);
}


template <typename T>
Matrix<T> Matrix<T>::set_identity()
{
    set_zero();
    for (unsigned int idx = 0; idx < this->cols * this->rows; idx += rows + 1)
    {
        this->values[idx] = 1.0;
    }
    return (*this);
}


template <typename T>
Matrix<T> Matrix<T>::set_transpose()
{
    Matrix trans(this->cols, this->rows);
    for (unsigned int row = 0; row < trans.rows; row++)
    {
        for (unsigned int col = 0; col < trans.cols; col++)
        {
            trans.values[row * trans.cols + col] = this->values[col * trans.rows + row];
        }
    }
    *this = trans;
    return (*this);
}


template <typename T>
bool Matrix<T>::operator==(const Matrix<T>& A)
{
    if (this->cols != A.cols || this->rows != A.rows) return false;
    for (unsigned int idx = 0; idx < this->cols * this->rows; idx++)
    {
        if (abs(this->values[idx] - A.values[idx]) > EPS) return false;
    }
    return true;
}


template <typename T>
bool Matrix<T>::operator!=(const Matrix<T>& mat)
{
    return !(*this == mat);
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& A)
{
    if (this == &A) return *this;
    delete[] values;
    rows = A.rows;
    cols = A.cols;
    this->values = new T[rows * cols];
    if (!values) throw Mem_Error;
    memcpy(this->values, A.values, rows * cols * sizeof(T));
    return *this;
}


template <typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& matrix)
{
    if (rows != matrix.rows || cols != matrix.cols) throw Not_Equal;
    for (unsigned int index = 0; index < rows * cols; ++index)
    {
        this->values[index] += matrix.values[index];
    }
    return *this;
}


template <typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& matrix)
{
    if (rows != matrix.rows || cols != matrix.cols) throw Not_Equal;
    for (unsigned int index = 0; index < rows * cols; ++index)
    {
        this->values[index] -= matrix.values[index];
    }
    return *this;
}


template <typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& matrix)
{
    if (cols != matrix.rows) throw Multiply_Error;
    Matrix multiplication(rows, matrix.cols);
    for (unsigned int row = 0; row < multiplication.rows; row++)
    {
        for (unsigned int col = 0; col < multiplication.cols; col++)
        {
            double sum = 0;
            for (unsigned int k = 0; k < matrix.rows; k++)
            {
                sum += values[row * cols + k] * matrix.values[k * matrix.cols + col];
            }
            multiplication.values[row * multiplication.cols + col] = sum;
        }
    }
    *this = multiplication;
    return (*this);
}


template <typename T>
Matrix<T>& Matrix<T>::operator*=(const T k)
{
    for (unsigned int idx = 0; idx < rows * cols; idx++)
    {
        this->values[idx] *= k;
    }
    return *this;
}


template <typename T>
Matrix<T>& Matrix<T>::operator/=(const T k)
{
    for (unsigned int idx = 0; idx < rows * cols; idx++)
    {
        this->values[idx] /= k;
    }
    return *this;
}


template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& matrix)
{
    Matrix add(*this);
    add += matrix;
    return (add);
}


template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& matrix)
{
    Matrix sub(*this);
    sub -= matrix;
    return (sub);
}


template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& matrix)
{
    Matrix multiply(*this);
    multiply *= matrix;
    return (multiply);
}


template <typename T>
Matrix<T> Matrix<T>::operator*(const T value)
{
    Matrix multiply(*this);
    multiply *= value;
    return (multiply);
}


template <typename T>
Matrix<T> Matrix<T>::operator/(const T value)
{
    Matrix multiply(*this);
    multiply /= value;
    return (multiply);
}


template<typename T>
void Matrix<T>::output()
{
    for (unsigned int row = 0; row < rows; row++)
    {
        for (unsigned int col = 0; col < cols; col++)
        {
            cout << values[row * cols + col] << "\t";
        }
        cout << endl;
    }
}


template <typename T>
Matrix<T> Matrix<T>::fill_from_array(T* array)
{
    memcpy(values, array, rows * cols * sizeof(T));
    return (*this);
}


template<typename T>
Matrix<T> Matrix<T>::fill_random(unsigned int n)                       //Максимальное значение
{
    for (unsigned int index = 0; index < cols * rows; index++)
    {
        this->values[index] = T(rand() % n);
    }
    return (*this);
}


template <typename T>
Matrix<T> Matrix<T>::minor(const Matrix matrix, const unsigned int size, const unsigned int row, const unsigned int col)
{
    Matrix minor(size - 1, size - 1);
    unsigned int shiftrow = 0;                                          //Смещение индекса строки в матрице
    unsigned int shiftcol;                                              //Смещение индекса столбца в матрице
    for (unsigned int rows = 0; rows < size - 1; rows++)
    {
                                                                        //Пропустить row-ую строку
        if (rows == row)
        {
            shiftrow = 1;
        }                                                               //Как только встретили строку,
                                                                        //которую надо пропустить, делаем смещение для исходной матрицы
        shiftcol = 0;                                                   //Обнулить смещение столбца
        for (unsigned int cols = 0; cols < size - 1; cols++)
        {
            if (cols == col)
            {
                shiftcol = 1;
            }
            minor.values[rows * (size - 1) + cols] = matrix.values[(rows + shiftrow)
                * size + (cols + shiftcol)];
        }
    }
    return minor;
}


template <typename T>
double Matrix<T>::determinant(const Matrix matrix, const unsigned int size)
{
    if (matrix.rows != matrix.cols) throw Not_Square;
    double det = 0;
    int k = 1;
    if (size == 0)
        return 0;
    if (size == 1)
        return matrix.values[0];
    if (size == 2)
    {
        return (matrix.values[0] * matrix.values[3] - matrix.values[2] * matrix.values[1]);
    }
    for (unsigned int idx = 0; idx < size; idx++) {
        det += k * matrix.values[idx] * determinant(minor(matrix, size, 0, idx), size - 1);
        k = -k;
    }
    return det;
}


template <typename T>
Matrix<T> Matrix<T>::reverse(const Matrix matrix, const unsigned int size)
{
    double d = determinant(matrix, size);
    if (matrix.rows != matrix.cols) throw Not_Square;
    Matrix reverse(matrix.rows, matrix.cols);
    int k = 1;
    for (unsigned int row = 0; row < reverse.rows; row++)
    {
        for (unsigned int col = 0; col < reverse.cols; col++)
        {
            reverse.values[row * size + col] = k * determinant(minor(matrix, size, row, col), size - 1);
            k = -k;
        }
    }
    reverse.set_transpose();
    if (fabs(d) < EPS) throw Zero_division;
    reverse /= d;
    return reverse;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
Matrix<T> Matrix<T>::exponent(unsigned int n) //Количество членов разложения
{
    if (rows != cols) throw Not_Square;
    Matrix ex(rows, cols);
    Matrix temp(rows, cols);
    temp.set_identity();
    ex.set_identity();
    double fact = 1.0;
    for (unsigned int i = 1; i < n; i++)
    {
        fact *= i;
        temp *= (*this);
        ex += temp / fact;
    }
    return ex;
}


template <typename T1>
class Matrix_Memory : public Matrix<T1> {
private:
    unsigned int memory = 0;
public:
    Matrix_Memory<T1>() :Matrix<T1>()
    {
        memory += total_mem;
    }

    Matrix_Memory<T1>(const Matrix_Memory& mat) : Matrix<T1>(mat) {
        memory = mat.memory;
        total_mem += memory;
    }

    Matrix_Memory<T1>(Matrix_Memory&& mat) : Matrix<T1>(mat)
    {
        memory = mat.memory;
        total_mem += memory;
        total_mem -= mat.memory;
        mat.memory = 0;

    }
    void output() override
    {
        cout << "Memory allocated for class Matrix - " << memory << " byte" << endl;
    }

    Matrix_Memory<T1>(unsigned int row, unsigned int col) :Matrix<T1>(row, col)
    {
        memory = row * col * sizeof(T1);
        total_mem += memory;
    }

    Matrix_Memory<T1>() : Matrix<T1>()
    {
        memory = 0;
        total_mem += memory;
    }

    ~Matrix_Memory()
    {
        total_mem -= memory;
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void test_add()
{
    double data1[6] = { 3, 1, 2, 4, 5, 7 };
    double data2[6] = { 8, 2, 1, -2, 2, 4 };
    double ans_d[6] = { 11, 3, 3, 2, 7, 11 };

    Matrix<double> matrix1 = Matrix<double>(2, 3).fill_from_array(data1);
    Matrix<double> matrix2 = Matrix<double>(2, 3).fill_from_array(data2);
    Matrix<double> test_add = Matrix<double>(2, 3).fill_from_array(ans_d);

    if (test_add != matrix1 + matrix2)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << "Addition test failed\n";
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
        cout << "Addition test passed\n";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


void test_sub()
{
    double data1[6] = { 3, 1, 2, 4, 5, 7 };
    double data2[6] = { 8, 2, 1, -2, 2, 4 };
    double ans_d[6] = { -5, -1, 1, 6, 3, 3 };

    Matrix<double> matrix1 = Matrix<double>(2, 3).fill_from_array(data1);
    Matrix<double> matrix2 = Matrix<double>(2, 3).fill_from_array(data2);
    Matrix<double> test_add = Matrix<double>(2, 3).fill_from_array(ans_d);

    if (test_add != matrix1 - matrix2) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << "Substraction test failed\n";
    }
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
        cout << "Substruction test passed\n";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


void test_mult()
{
    double data1[9] = { 1, 7, 4, 0, 9, 4, 8, 8, 2 };
    double data2[9] = { 4, 5, 5, 1, 7, 1, 1, 5, 2 };
    double ans_d[9] = { 15, 74, 20, 13, 83, 17, 42, 106, 52 };

    Matrix<double> matrix1 = Matrix<double>(3, 3).fill_from_array(data1);
    Matrix<double> matrix2 = Matrix<double>(3, 3).fill_from_array(data2);
    Matrix<double> test_add = Matrix<double>(3, 3).fill_from_array(ans_d);

    if (test_add != matrix1 * matrix2) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << "Multiplication test failed\n";
    }
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
        cout << "Multiplication test passed\n";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


void test_mult_k()
{
    double data1[3] = { 1, 7, 4 };
    double ans_d[3] = { 3, 21, 12 };

    Matrix<double> matrix1 = Matrix<double>(1, 3).fill_from_array(data1);
    Matrix<double> test_add = Matrix<double>(1, 3).fill_from_array(ans_d);

    if (test_add != matrix1 * 3) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << "Multiplication test failed\n";
    }
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
        cout << "Multiplication test passed\n";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


void test_div_k()
{
    double data1[3] = { 6, 21, 18 };
    double ans_d[3] = { 2, 7, 6 };

    Matrix<double> matrix1 = Matrix<double>(1, 3).fill_from_array(data1);
    Matrix<double> test_div = Matrix<double>(1, 3).fill_from_array(ans_d);

    if (test_div != matrix1 / 3)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << "Division test failed\n";
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
        cout << "Division test passed\n";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


void test_det()
{
    double data1[9] = { 1, 7, 4, 0, 9, 4, 8, 8, 2 };

    Matrix<double> matrix1 = Matrix<double>(3, 3).fill_from_array(data1);

    double determinant = matrix1.determinant(matrix1, matrix1.getrow());
    if (determinant != -78.0)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << "Determinant test failed\n";
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
        cout << "Determinant test passed\n";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


void test_rev()
{
    double data1[9] = { 1, 7, 4, 0, 9, 4, 8, 8, 2 };
    double ans[9] = { 0.179487,  -0.230769, 0.102564, -0.410256,  0.384615, 0.0512821, 0.923077,   -0.615385, -0.115385 };

    Matrix<double> matrix1 = Matrix<double>(3, 3).fill_from_array(data1);
    Matrix<double> test_rev = Matrix<double>(3, 3).fill_from_array(ans);
    Matrix<double> reverse = matrix1.reverse(matrix1, matrix1.getrow());

    if (reverse == test_rev)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
        cout << "Reverse test passed\n";
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << "Reverse test failed\n";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


void test_transpose()
{
    double data1[3] = { 1, 7, 4 };
    double ans[3] = { 1,7,4 };

    Matrix<double> matrix1 = Matrix<double>(3, 1).fill_from_array(data1);
    Matrix<double> test_trans = Matrix<double>(1, 3).fill_from_array(ans);

    if (matrix1.set_transpose() == test_trans)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
        cout << "Trasposition test passed\n";
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << "Transposition test failed\n";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


void test_set_identity()
{
    double data1[9] = { 1, 7, 4, 0, 9, 4, 8, 8, 2 };
    double ans[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };

    Matrix<double> matrix1 = Matrix<double>(3, 3).fill_from_array(data1);
    Matrix<double> test_identity = Matrix<double>(3, 3).fill_from_array(ans);

    if (matrix1.set_identity() == test_identity)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
        cout << "SetIdentity test passed\n";
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << "SetIdentity test failed\n";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void test_set_zero()
{
    double data1[3] = { 1, 7, 4 };
    double ans[3] = { 0,0,0 };

    Matrix<double> matrix1 = Matrix<double>(3, 1).fill_from_array(data1);
    Matrix<double> test_zero = Matrix<double>(3, 1).fill_from_array(ans);

    if (matrix1.set_zero() == test_zero)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
        cout << "SetZero test passed\n";
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << "SetZero test failed\n";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void test()
{
    test_add();
    test_sub();
    test_div_k();
    test_mult_k();
    test_mult();
    test_det();
    test_rev();
    test_transpose();
    test_set_identity();
    test_set_zero();
}


int main()
{
    Matrix_Memory<double> A(3, 3);
    Matrix_Memory<double> B(A);

}
