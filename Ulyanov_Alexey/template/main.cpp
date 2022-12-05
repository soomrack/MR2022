#include <iostream>
#include <iomanip>


const double COMPARATION_CONST = 0.00001;
unsigned int MATRIX_MEMORY_QUANTITY = 0;


class Matrix_Exception : public std::domain_error
{
public:
    Matrix_Exception(const char* const msg) : std::domain_error(msg)
    {}
};


Matrix_Exception SIZE_UNMATCH("Error founded: Two datas have incompatible size");
Matrix_Exception NOT_SQUARE("Error founded: The number of rows must be equal to cols");
Matrix_Exception DIV_BY_ZERO("Error founded: Division by zero");


template <typename T>
class Matrix_T
{

    static_assert(
            std::is_same<float, T>::value ||
    std::is_same<double, T>::value ||
    std::is_same<long double, T>::value,
    "type of matrix must be floating point"
    );


protected:

    const T CMP_CONST = 0.0001;

    unsigned int rows;
    unsigned int cols;
    T* data;


public:

    Matrix_T();
    Matrix_T(const unsigned int n);
    Matrix_T(const unsigned int row, const unsigned int col);
    Matrix_T(const Matrix_T<T> &x);
    Matrix_T(Matrix_T<T> &&x);
    ~Matrix_T();

    Matrix_T<T>& operator=(const Matrix_T<T> &x);
    Matrix_T<T>& operator+=(const Matrix_T<T> &x);
    Matrix_T<T>& operator-=(const Matrix_T<T> &x);
    Matrix_T<T>& operator*=(const Matrix_T<T> &x);
    Matrix_T<T>& operator*=(const T k);
    Matrix_T<T>& operator/=(const Matrix_T<T> &x);
    bool operator==(const Matrix_T<T> &x);

    void zero();
    void one();
    void multy_k(const T k);
    void tran();
    Matrix_T<T> minor(const unsigned int cur_row, const unsigned int cur_col);
    void triangle();
    T det();
    void reverse();
    void pow(const unsigned int n);
    void exponent(const unsigned int p_degree = 3);

    void fill_random(const unsigned int max_range = 51);
    void fill_certain(const unsigned int len, const T* array);
    void output(bool f = false);

    Matrix_T<T> pow_mat(const unsigned int n = 2){
        Matrix_T<T> rez = Matrix_T<T>(rows, cols);
        if (rows != cols) throw NOT_SQUARE;

        rez.fill_certain(rows * cols, data);
        rez.pow(n);
        return rez;
    };
    Matrix_T<T> expo_mat(const unsigned int p_degree = 3){
        Matrix_T<T> rez = Matrix_T<T>(rows, cols);
        rez.fill_certain(rows * cols, data);

        rez.exponent(p_degree);
        return rez;
    };

};

template <typename T>
Matrix_T<T> undefinded();
template <typename T>
Matrix_T<T> zero(const unsigned int row, const unsigned int col);
template <typename T>
Matrix_T<T> one(const unsigned int row, const unsigned int col);

template <typename T>
Matrix_T<T> operator+(const Matrix_T<T> &x, const Matrix_T<T> &y);
template <typename T>
Matrix_T<T> operator-(const Matrix_T<T> &x, const Matrix_T<T> &y);
template <typename T>
Matrix_T<T> operator*(const Matrix_T<T> &x, const Matrix_T<T> &y);
template <typename T>
Matrix_T<T> operator*(const T k, const Matrix_T<T> &x);
template <typename T>
Matrix_T<T> operator*(const Matrix_T<T> &x, const T k);
template <typename T>
Matrix_T<T> operator/(const Matrix_T<T> &x, const Matrix_T<T> &y);


template <typename T>
Matrix_T<T>::Matrix_T(){
    rows = 0;
    cols = 0;
    data = nullptr;
}


template <typename T>
Matrix_T<T>::Matrix_T(const unsigned int n) {
    rows = n;
    cols = n;
    data = new T[n * n];
}


template <typename T>
Matrix_T<T>::Matrix_T(const unsigned int row, const unsigned int col) {
    rows = row;
    cols = col;

    data = new T[row * col];
}


template <typename T>
Matrix_T<T>::Matrix_T(const Matrix_T<T> &x) {
    rows = x.rows;
    cols = x.cols;

    //delete[] data;
    data = new T[rows * cols];

    for (unsigned int idx = 0; idx < rows * cols; idx++){
        data[idx] = x.data[idx];
    }
}


template <typename T>
Matrix_T<T>::Matrix_T(Matrix_T<T> &&x) {
    rows = x.rows;
    cols = x.cols;
    data = x.data;

    x.rows = 0;
    x.cols = 0;
    x.data = nullptr;
}


template <typename T>
Matrix_T<T>::~Matrix_T() {
    delete[] data;
}


template <typename T>
Matrix_T<T>& Matrix_T<T>::operator=(const Matrix_T<T> &x){
    if (this != &x){
        if (!data)
            delete[] data;

        rows = x.rows;
        cols = x.cols;

        this->data = new T[rows * cols];
        for (unsigned int idx = 0; idx < rows * cols; idx++){
            data[idx] = x.data[idx];
        }
    }

    return *this;
}


template <typename T>
Matrix_T<T>& Matrix_T<T>::operator+=(const Matrix_T<T> &x){
    if ((rows != x.rows) or (cols != x.cols)) throw SIZE_UNMATCH;

    for (unsigned int idx = 0; idx < rows * cols; idx++){
        data[idx] += x.data[idx];
    }
    return *this;
}


template <typename T>
Matrix_T<T>& Matrix_T<T>::operator-=(const Matrix_T<T> &x){
    if ((rows != x.rows) or (cols != x.cols)) throw SIZE_UNMATCH;

    for (unsigned int idx = 0; idx < rows * cols; idx++){
        data[idx] -= x.data[idx];
    }
    return *this;
}


template <typename T>
Matrix_T<T>& Matrix_T<T>::operator*=(const Matrix_T<T> &x){
    if (cols != x.rows) throw SIZE_UNMATCH;

    Matrix_T<T> rez = Matrix_T(rows, x.cols);
    rez.zero();
    for (unsigned int row = 0; row < rez.rows; row++){
        for (unsigned int col = 0; col < rez.cols; col++){
            for (unsigned int idx = 0; idx < x.rows; idx++){
                rez.data[row * rez.cols + col] += data[row * cols + idx] * data[idx * x.cols + col];
            }
        }
    }

    *this = rez;
    return *this;
}


template <typename T>
Matrix_T<T>& Matrix_T<T>::operator*=(const T k) {
    for (unsigned int idx = 0; idx < rows * cols; idx++){
        data[idx] *= k;
    }
    return *this;
}


template <typename T>
Matrix_T<T>& Matrix_T<T>::operator/=(const Matrix_T<T> &x) {
    if (x.cols != x.rows) throw SIZE_UNMATCH;

    Matrix_T<T> temp = Matrix_T(x.rows, x.cols);
    temp.fill_certain(x.rows * x.cols, x.data);
    temp.reverse();

    this *= temp;
    return *this;
}


template <typename T>
void Matrix_T<T>::zero(){
    for (unsigned int idx = 0; idx < rows * cols; idx++){
        data[idx] = 0.0;
    }
}


template <typename T>
void Matrix_T<T>::one(){
    this->zero();
    for (unsigned int idx = 0; idx < rows; idx++){
        data[idx + cols * idx] = 1.0;
    }
}


template <typename T>
void Matrix_T<T>::multy_k(const T k){
    for (unsigned int idx = 0; idx < rows * cols; idx++){
        data[idx] *= k;
    }
}


template <typename T>
void Matrix_T<T>::tran(){
    unsigned int row = cols;
    unsigned int col = rows;
    T* temp_array = new T[rows * col];

    for (unsigned int row_idx = 0; row_idx < rows; row_idx++){
        for (unsigned int col_idx = 0; col_idx < cols; col_idx++){
            temp_array[col_idx * rows + row_idx] = data[row_idx * cols + col_idx];
        }
    }

    delete[] data;
    data = temp_array;
    rows = row;
    cols = col;
}


template <typename T>
Matrix_T<T> Matrix_T<T>::minor(const unsigned int cur_row, const unsigned int cur_col) {
    int new_row = rows - 1, new_col = cols - 1;
    if (cur_row >= rows) new_row++;
    if (cur_col >= cols) new_col++;

    Matrix_T<T> rez = Matrix_T<T>(new_row, new_col);
    unsigned int k = 0;

    for (unsigned int idx = 0; idx < rows * cols; idx++){
        if ((idx % cols == cur_col) or (idx / cols == cur_row)) continue;
        rez.data[k++] = data[idx];
    }

    return rez;
}


template <typename T>
void Matrix_T<T>::triangle(){
    if (rows == 1) return;

    bool need_to_trans = false;
    if (rows > cols){
        need_to_trans = true;
        this->tran();
    }

    for (unsigned int step = 1; step < rows; step++) {
        for (unsigned int cur_row = step; cur_row < rows; cur_row++) {
            if (data[(step - 1) * (cols + 1)] < COMPARATION_CONST){
                throw DIV_BY_ZERO;
            }
            T ratio = data[cur_row * cols + step - 1] / data[(step - 1) * cols + step - 1];
            for (unsigned int col = step - 1; col < cols; col++) {
                data[cur_row * cols + col] -= ratio * data[(step - 1) * cols + col];
            }
        }
    }

    if (need_to_trans){
        this->tran();
    }
}


template <typename T>
T Matrix_T<T>::det(){
    if (rows != cols) throw NOT_SQUARE;

    Matrix_T<T> temp = Matrix_T<T>(rows, cols);
    temp.fill_certain(rows * cols, data);
    temp.triangle();

    T rez = 1.0;
    for (unsigned int idx = 0; idx < temp.rows; idx++){
        rez *= temp.data[idx * cols + idx];
    }
    return rez;
}


template <typename T>
void Matrix_T<T>::reverse() {
    T deter = this->det();
    if (rows != cols) throw NOT_SQUARE;

    Matrix_T<T> temp = Matrix_T<T>(rows, cols);
    int ratio = 1;
    for (unsigned int row = 0; row < rows; row++){
        for (unsigned int col = 0; col < cols; col++){
            temp.data[row * cols + col] = ratio * this->minor(row, col).det();
            ratio *= -1;
        }
    }

    temp.tran();
    if (abs(deter - 0.0) < COMPARATION_CONST)  throw DIV_BY_ZERO;
    temp.multy_k(1/deter);

    this->fill_certain(temp.rows * temp.cols, temp.data);
}


template <typename T>
void Matrix_T<T>::pow(const unsigned int n) {
    if (rows != cols) throw NOT_SQUARE;

    Matrix_T<T> rez = Matrix_T<T>(rows, cols);
    rez.one();
    for (unsigned int idx = 0; idx < n; idx++) {
        rez *= *this;
    }

    this->fill_certain(rows * cols, rez.data);
}


template <typename T>
void Matrix_T<T>::fill_random(const unsigned int max_range) {
    for (unsigned int idx = 0; idx < rows * cols; idx++){
        data[idx] = rand() % max_range;
    }
}


template <typename T>
void Matrix_T<T>::fill_certain(const unsigned int len, const T *array) {
    if (len != rows * cols) throw SIZE_UNMATCH;

    for (unsigned int idx = 0; idx < rows * cols; idx++){
        data[idx] = array[idx];
    }
}


template <typename T>
void Matrix_T<T>::output(bool f){
    if (f) {
        std::cout << rows << " " << cols << "\n";
    }

    for (unsigned int row = 0; row < rows; row++){
        for (unsigned int col = 0; col < cols; col++){
            std::cout << data[row * cols + col] << "  ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";

}


template <typename T>
Matrix_T<T> undefinded(){
    Matrix_T<T> rez = Matrix_T<T>();
    return rez;
}


template <typename T>
Matrix_T<T> zero(const unsigned int row, const unsigned int col){
    Matrix_T<T> rez = Matrix_T<T>(row, col);
    rez.zero();
    return rez;
}


template <typename T>
Matrix_T<T> one(const unsigned int row, const unsigned int col){
    Matrix_T<T> rez = Matrix_T<T>(row, col);
    rez.one();
    return rez;
}


template <typename T>
Matrix_T<T> multy_k(const Matrix_T<T> x, const double k){
    Matrix_T<T> rez = x;
    rez.multy_k(k);
    return rez;
}




template <typename T>
void Matrix_T<T>::exponent(const unsigned int p_degree) {
    if (rows != cols) throw NOT_SQUARE;

    Matrix_T<T> rez = Matrix_T<T>(rows, cols);
    rez.one();
    T ratio = 1;
    Matrix_T<T> temp = rez;
    for (unsigned int idx = 1; idx < p_degree; idx++){
        temp *= *this;
        ratio /= (idx);
        rez += (temp * ratio);
    }

    *this = rez;
}


template <typename T>
bool Matrix_T<T>::operator==(const Matrix_T<T> &x) {
    if (this->cols != x.cols || this->rows != x.rows) return false;
    for (unsigned int idx = 0; idx < this->cols * this->rows; idx++) {
        if (abs(this->data[idx] - x.data[idx]) > x.CMP_CONST) return false;
    }
    return true;
}


template <typename T>
Matrix_T<T> operator+(const Matrix_T<T> &x, const Matrix_T<T> &y){
    Matrix_T<T> rez = x;
    rez += y;
    return rez;
}


template <typename T>
Matrix_T<T> operator-(const Matrix_T<T> &x, const Matrix_T<T> &y){
    Matrix_T<T> rez = x;
    rez -= y;
    return rez;
}


template <typename T>
Matrix_T<T> operator*(const Matrix_T<T> &x, const Matrix_T<T> &y){
    Matrix_T<T> rez = x;
    rez *= y;
    return rez;
}


template <typename T>
Matrix_T<T> operator*(const T k, const Matrix_T<T> &x){
    Matrix_T<T> rez = x;
    rez *= k;
    return rez;
}


template <typename T>
Matrix_T<T> operator*(const Matrix_T<T> &x, const T k){
    return k * x;
}


template <typename T>
Matrix_T<T> operator/(const Matrix_T<T> &x, const Matrix_T<T> &y){
    Matrix_T<T> rez = x;
    rez /= y;
    return rez;
}


template <typename T>
class Matrix_memory : public Matrix_T<T>
{

protected:
    unsigned int mem_size;
    unsigned int quantity;

public:
    Matrix_memory(){
        this->rows = 0;
        this->cols = 0;
        this->data = nullptr;
        this->mem_size = 0;
        this->quantity = ++MATRIX_MEMORY_QUANTITY;
    }
    Matrix_memory(const unsigned int n){
        this->rows = n;
        this->cols = n;
        this->data = new T [n * n];
        this->mem_size = n * n * sizeof (T);
        this->quantity = ++MATRIX_MEMORY_QUANTITY;
    }
    Matrix_memory(const unsigned int row, unsigned int col){
        this->rows = row;
        this->cols = col;
        this->data = new T [row * col];
        this->mem_size = row * col * sizeof (T);
        this->quantity = ++MATRIX_MEMORY_QUANTITY;
    }
    Matrix_memory(const Matrix_memory<T> &x){
        this->rows = x.rows;
        this->cols = x.cols;
        this->data = new T [x.rows * x.cols];

        for (unsigned int idx = 0; idx < x.rows * x.cols; idx++){
            this->data[idx] = x.data[idx];
        }

        this->mem_size = x.mem_size;
        this->quantity = x.quantity;
    }
    Matrix_memory(Matrix_memory<T> &&x){
        this->rows = x.rows;
        this->cols = x.cols;
        this->data = x.data;
        this->mem_size = x.mem_size;
        this->quantity = x.quantity;

        x.rows = 0;
        x.cols = 0;
        x.data = nullptr;
        x.mem_size = 0;
        x.quantity = 0;
    }
    ~Matrix_memory() {
        MATRIX_MEMORY_QUANTITY--;
    };

    void output(bool f = false);
};


template <typename T>
void Matrix_memory<T>::output(bool f){
    Matrix_T<T>::output(f);
    std::cout << "This variable hold " << mem_size << " bytes in memory\n";
    std::cout << "There was defended " << MATRIX_MEMORY_QUANTITY << " variables of the Matrix_memory type\n\n";
}


void test_sum(){
    Matrix_T<double> A = Matrix_T<double>(3, 3);
    Matrix_T<double> B = Matrix_T<double>(3, 3);

    double arrey_a[9] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    double arrey_b[9] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};

    A.fill_certain(9, arrey_a);
    B.fill_certain(9, arrey_b);

    Matrix_T<double> rez = A + B;

    Matrix_T<double> standard = Matrix_T<double>(3, 3);
    double arrey_s[9] = {2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0};
    standard.fill_certain(9, arrey_s);

    bool final = (rez == standard);
    if (final){
        std::cout << "Test of summation was successful\n";
    } else {
        std::cout << "Test of summation was failed\n";
    }
}



void test_sub(){
    Matrix_T<float> A = Matrix_T<float>(3, 3);
    Matrix_T<float> B = Matrix_T<float>(3, 3);

    float array_a[9] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    float array_b[9] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};

    A.fill_certain(9, array_a);
    B.fill_certain(9, array_b);

    Matrix_T<float> rez = A - B;

    Matrix_T<float> standard = Matrix_T<float>(3, 3);
    float array_s[9] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    standard.fill_certain(9, array_s);

    bool final = (rez == standard);
    if (final){
        std::cout << "Test of subtraction was successful\n";
    } else {
        std::cout << "Test of subtraction was failed\n";
    }
}


void test_mul(){
    Matrix_T<long double> A = Matrix_T<long double>(3, 3);
    Matrix_T<long double> B = Matrix_T<long double>(3, 3);

    long double array_a[9] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    long double array_b[9] = {9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0};

    A.fill_certain(9, array_a);
    B.fill_certain(9, array_b);

    Matrix_T<long double> rez = A * B;

    Matrix_T<long double> standard = Matrix_T<long double>(3, 3);
    long double array_s[9] = {30.0, 24.0, 18.0, 84.0, 69.0, 54.0, 138.0, 114.0, 90.0};
    standard.fill_certain(9, array_s);

    bool final = (rez == standard);
    if (final){
        std::cout << "Test of multiplication was successful\n";
    } else {
        std::cout << "Test of multiplication was failed\n";
    }
}


void test_reverse(){
    const unsigned int n = 3;
    Matrix_T<double> A = Matrix_T<double>(n, n);
    A.fill_random();

    Matrix_T<double> B = A;
    B.reverse();

    Matrix_T<double> standard = one<double>(n, n);

    bool final = (standard == A * B);
    if (final){
        std::cout << "Test of reverse was successful\n";
    } else {
        std::cout << "Test of reverse was failed\n";
    }
}


void test_exp(){
    Matrix_T<double> A = Matrix_T<double>(3, 3);
    A.fill_random();

    Matrix_T<double> B = A.expo_mat();

    Matrix_T<double> standard = Matrix_T<double>(3, 3);
    standard = one<double>(3,3) + 1.0 * A + A.pow_mat(2) * 0.5;

    A.exponent();

    bool final = ((A == standard) and (B == standard));
    if (final){
        std::cout << "Test of exponent was successful\n";
    } else {
        std::cout << "Test of exponent was failed\n";
    }
}

void block_tests(){
    test_sum();
    test_sub();
    test_mul();
    test_reverse();
    test_exp();
    std::cout << "\n";
}


void block_output(){
    std::cout << std::fixed << std::setprecision(2);

    Matrix_T<double> A = Matrix_T<double>(3, 5);
    Matrix_T<float> B = Matrix_T<float> (6);

    Matrix_memory<double> X = Matrix_memory<double>();
    Matrix_memory<float> Y = Matrix_memory<float>(5);
    Y.fill_random(101);
    Y.output();

}


int main() {
    block_tests();
    block_output();
    return 0;
}
