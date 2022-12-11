#include <iostream>
#include <iomanip>


static unsigned int memory = 0;  // отслеживает выделенную память для ВСЕХ экземпляров Matrix_memory


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

    unsigned int getRows() { return rows; };
    unsigned int getCols() { return cols; };
    T * getData() { return data; };
    char * getName() { return "Matrix_T"; };

};


template <typename T, template <typename> class CLS>
CLS<T> undefinded();
template <typename T, template <typename> class CLS>
CLS<T> zero(const unsigned int row, const unsigned int col);
template <typename T, template <typename> class CLS>
CLS<T> one(const unsigned int row, const unsigned int col);


template <typename T, template <typename> class CLS>
CLS<T> operator+(const CLS<T> &x, const CLS<T> &y);
template <typename T, template <typename> class CLS>
CLS<T> operator-(const CLS<T> &x, const CLS<T> &y);
template <typename T, template <typename> class CLS>
CLS<T> operator*(const CLS<T> &x, const CLS<T> &y);
template <typename T, template <typename> class CLS>
CLS<T> operator*(const T k, const CLS<T> &x);
template <typename T, template <typename> class CLS>
CLS<T> operator*(const CLS<T> &x, const T k);
template <typename T, template <typename> class CLS>
CLS<T> operator/(const CLS<T> &x, const CLS<T> &y);


template <typename T, template <typename> class CLS>
CLS<T> expo_mat(const CLS<T> &x, const unsigned int p_degree = 3);
template <typename T, template <typename> class CLS>
CLS<T> pow_mat(const CLS<T> &x, const unsigned int n = 2);


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
                rez.data[row * rez.cols + col] += data[row * cols + idx] * x.data[idx * x.cols + col];
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
            if (data[(step - 1) * (cols + 1)] < CMP_CONST){
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
    if (abs(deter - 0.0) < CMP_CONST)  throw DIV_BY_ZERO;
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


template <typename T, template <typename> class CLS>
CLS<T> undefinded(){
    CLS<T> rez = CLS<T>();
    return rez;
}


template <typename T, template <typename> class CLS>
CLS<T> zero(const unsigned int row, const unsigned int col){
    CLS<T> rez = CLS<T>(row, col);
    rez.zero();
    return rez;
}


template <typename T, template <typename> class CLS>
CLS<T> one(const unsigned int row, const unsigned int col){
    CLS<T> rez = CLS<T>(row, col);
    rez.one();
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
    if ((this->cols != x.cols) || (this->rows != x.rows)) return false;

    for (unsigned int idx = 0; idx < this->rows * this->cols; idx++) {
        if (abs(this->data[idx] - x.data[idx]) > CMP_CONST) return false;
    }
    return true;
}



template <typename T, template <typename> class CLS>
CLS<T> pow_mat(const CLS<T> &x, const unsigned int n){
    CLS<T> rez = CLS<T>(x.getRows(), x.getCols());
    if (rez.rows != rez.cols) throw NOT_SQUARE;

    rez.fill_certain(x.getRows() * x.getCols(), x.getData());
    rez.pow(n);
    return rez;
};


template <typename T, template <typename> class CLS>
CLS<T> expo_mat(const CLS<T> &x, const unsigned int p_degree){
    CLS<T> rez = CLS<T>(x.getRows(), x.getCols());
    rez.fill_certain(x.getRows() * x.getCols(), x.getData());

    rez.exponent(p_degree);
    return rez;
};


template <typename T, template <typename> class CLS>
CLS<T> operator+(const CLS<T> &x, const CLS<T> &y){
    CLS<T> rez = x;
    rez += y;
    return rez;
}


template <typename T, template <typename> class CLS>
CLS<T> operator-(const CLS<T> &x, const CLS<T> &y){
    CLS<T> rez = x;
    rez -= y;
    return rez;
}


template <typename T, template <typename> class CLS>
CLS<T> operator*(const CLS<T> &x, const CLS<T> &y){
    CLS<T> rez = x;
    rez *= y;
    return rez;
}


template <typename T, template <typename> class CLS>
CLS<T> operator*(const T k, const CLS<T> &x){
    CLS<T> rez = x;
    rez *= k;
    return rez;
}


template <typename T, template <typename> class CLS>
CLS<T> operator*(const CLS<T> &x, const T k){
    return k * x;
}


template <typename T, template <typename> class CLS>
CLS<T> operator/(const CLS<T> &x, const CLS<T> &y){
    CLS<T> rez = x;
    rez /= y;
    return rez;
}


template <typename T>
class Matrix_memory : public Matrix_T<T>
{

protected:
    unsigned int mem_size;
    static unsigned int quantity; // рудимент, отсчитывающий количество созданных экземпляров класса Matrix_memory

    static unsigned int total_memory;


public:
    Matrix_memory(){
        this->rows = 0;
        this->cols = 0;
        this->data = nullptr;
        mem_size = 0;
        quantity++;

        memory += mem_size;  total_memory += mem_size;
    }
    Matrix_memory(const unsigned int n){
        this->rows = n;
        this->cols = n;
        this->data = new T [n * n];
        mem_size = n * n * sizeof (T);
        quantity++;

        memory += mem_size;  total_memory += mem_size;
    }
    Matrix_memory(const unsigned int row, unsigned int col){
        this->rows = row;
        this->cols = col;
        this->data = new T [row * col];
        mem_size = row * col * sizeof (T);
        quantity++;

        memory += mem_size;  total_memory += mem_size;
    }
    Matrix_memory(const Matrix_memory<T> &x){
        this->rows = x.rows;
        this->cols = x.cols;
        this->data = new T [x.rows * x.cols];

        for (unsigned int idx = 0; idx < x.rows * x.cols; idx++){
            this->data[idx] = x.data[idx];
        }

        mem_size = x.mem_size;
        quantity++;
        memory += mem_size;  total_memory += mem_size;
    }
    Matrix_memory(Matrix_memory<T> &&x){
        memory -= mem_size;
        total_memory -= mem_size;

        this->rows = x.rows;
        this->cols = x.cols;
        this->data = x.data;
        mem_size = x.mem_size;

        memory += mem_size;  total_memory += x.mem_size;

        x.rows = 0;
        x.cols = 0;
        x.data = nullptr;
        x.mem_size = 0;
    }
    ~Matrix_memory() {
        quantity--;
        memory -= mem_size;  total_memory -= mem_size;
    };

    Matrix_memory<T>& operator=(const Matrix_memory<T> &x);
    Matrix_memory<T>& operator*=(const Matrix_memory<T> &x);

    void output(const bool mem_flg = true, const bool extra_flag = false);

    static int getQuantity() { return quantity; };
    static int getMemory() { return total_memory; };

    char * getName() { return "Matrix_memory"; };
};
template <typename T>
unsigned int Matrix_memory<T>::total_memory = 0;
template <typename T>
unsigned int Matrix_memory<T>::quantity = 0;


template <typename T>
Matrix_memory<T>& Matrix_memory<T>::operator=(const Matrix_memory<T> &x) {
    if (this != &x){
        if (!this->data)
            delete[] this->data;

        memory -= mem_size;  total_memory -= mem_size;

        this->rows = x.rows;
        this->cols = x.cols;
        mem_size = this->rows * this->cols * sizeof (T);

        this->data = new T[x.rows * x.cols];
        for (unsigned int idx = 0; idx < this->rows * this->cols; idx++){
            this->data[idx] = x.data[idx];
        }

        memory += mem_size;  total_memory += mem_size;
    }
    return *this;
}


template <typename T>
Matrix_memory<T>& Matrix_memory<T>::operator*=(const Matrix_memory<T> &x) {
    if (this->cols != x.rows) throw SIZE_UNMATCH;

    Matrix_memory<T> rez = Matrix_memory<T>(this->rows, x.cols);
    rez.zero();

    for (unsigned int row = 0; row < rez.rows; row++){
        for (unsigned int col = 0; col < rez.cols; col++){

            for (unsigned int idx = 0; idx < x.rows; idx++){
                rez.data[row * rez.cols + col] += this->data[row * this->cols + idx] * x.data[idx * x.cols + col];
            }
        }
    }

    total_memory -= mem_size;  memory -= mem_size;
    total_memory += rez.mem_size;  memory += rez.mem_size;

    *this = rez;
    return *this;
}


template <typename T>
void Matrix_memory<T>::output(const bool mem_flg, const bool extra_flag) {
    Matrix_T<T>::output(extra_flag);
    if (mem_flg) {
        std::cout << "This variable hold " << mem_size << " bytes in memory\n";
        std::cout << "There was defended " << getQuantity() << " variables of the Matrix_memory type\n";
        std::cout << "Total memory handed in all Matrix_memory are " << getMemory() << "/" << memory << " bytes\n\n\n";
    }
}


template <typename TPE, template <typename> class CLSS>
void test_sum(){
    CLSS<TPE> A = CLSS<TPE>(3, 3);
    CLSS<TPE> B = CLSS<TPE>(3, 3);

    TPE arrey_a[9] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    TPE arrey_b[9] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};

    A.fill_certain(9, arrey_a);
    B.fill_certain(9, arrey_b);

    CLSS<TPE> rez = zero<TPE, CLSS>(3,3);
    rez = A + B;

    CLSS<TPE> standard = CLSS<TPE>(3, 3);
    TPE arrey_s[9] = {2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0};
    standard.fill_certain(9, arrey_s);

    bool final = (rez == standard);
    std::cout << standard.getName() << " test of summation was ";
    if (final){
        std::cout << "successful\n";
    } else {
        std::cout << "failed\n";
    }
}


template <typename TPE, template <typename> class CLSS>
void test_sub(){
    CLSS<TPE> A = CLSS<TPE>(3, 3);
    CLSS<TPE> B = CLSS<TPE>(3, 3);

    TPE array_a[9] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    TPE array_b[9] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};

    A.fill_certain(9, array_a);
    B.fill_certain(9, array_b);

    CLSS<TPE> rez = zero<TPE, CLSS>(3, 3);
    rez = A - B;

    CLSS<TPE> standard = CLSS<TPE>(3, 3);
    TPE array_s[9] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    standard.fill_certain(9, array_s);

    bool final = (rez == standard);
    std::cout << standard.getName() << " test of subtraction was ";
    if (final){
        std::cout << "successful\n";
    } else {
        std::cout << "failed\n";
    }
}


template <typename TPE, template <typename> class CLSS>
void test_mul(){
    CLSS<TPE> A = CLSS<TPE>(3, 3);
    CLSS<TPE> B = CLSS<TPE>(3, 3);

    TPE array_a[9] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    TPE array_b[9] = {9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0};

    A.fill_certain(9, array_a);
    B.fill_certain(9, array_b);

    CLSS<TPE> rez = zero<TPE, CLSS>(3, 3);
    rez = A * B;

    CLSS<TPE> standard = CLSS<TPE>(3, 3);
    TPE array_s[9] = {30.0, 24.0, 18.0, 84.0, 69.0, 54.0, 138.0, 114.0, 90.0};
    standard.fill_certain(9, array_s);

    bool final = (rez == standard);
    std::cout << standard.getName() << " test of multiplication was ";
    if (final){
        std::cout << "successful\n";
    } else {
        std::cout << "failed\n";
    }
}


template <typename TPE, template <typename> class CLSS>
void test_reverse(){
    const unsigned int n = 3;
    CLSS<TPE> A = CLSS<TPE>(n, n);
    A.fill_random();

    CLSS<TPE> B = A;
    B.reverse();

    CLSS<TPE> standard = one<TPE, CLSS>(n, n);

    bool final = (standard == A * B);
    std::cout << standard.getName() << " test of reverse was ";
    if (final){
        std::cout << "successful\n";
    } else {
        std::cout << "failed\n";
    }
}


template <typename TPE, template <typename> class CLSS>
void test_exp(){
    CLSS<TPE> A = CLSS<TPE>(3, 3);
    A.fill_random();

    CLSS<TPE> B = A; B.exponent();
    CLSS<TPE> temp = zero<TPE, CLSS>(3, 3);
    temp = A; temp.pow(2);

    CLSS<TPE> standard = CLSS<TPE>(3, 3);
    standard = one<TPE, CLSS>(3,3) + (TPE) 1.0 * A + temp * (TPE) 0.5;

    A.exponent();

    bool final = ((A == standard) and (B == standard));
    std::cout << A.getName() << " test of exponent was ";
    if (final){
        std::cout << "successful\n";
    } else {
        std::cout << "failed\n";
    }
}


void block_tests(){
    test_sum<double, Matrix_T>();
    test_sub<float, Matrix_T>();
    test_mul<long double, Matrix_T>();
    test_reverse<double, Matrix_T>();
    test_exp<float, Matrix_T>();

    std::cout << "\n";

    test_sum<float, Matrix_memory>();
    test_sub<double, Matrix_memory>();
    test_mul<double, Matrix_memory>();
    test_reverse<long double, Matrix_memory>();
    test_exp<long double, Matrix_memory>();

    std::cout << "\n";
}


void block_output(){
    std::cout << std::fixed << std::setprecision(2);

    Matrix_T<double> X = Matrix_T<double>(3, 5);
    Matrix_T<float> Y = Matrix_T<float> (6);

    Matrix_memory<double> A = Matrix_memory<double>();
    Matrix_memory<double> B = Matrix_memory<double>(3);
    Matrix_memory<double> C = Matrix_memory<double>(3, 5);

    C.output();

    Matrix_memory<float> D= Matrix_memory<float>(4);
    D.output();

}


int main() {
    block_tests();
    block_output();
    return 0;
}