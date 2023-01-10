#include <iostream>
#include <cmath>

class MatrixException: public std::exception {
public:
    MatrixException(const char* msg): std::exception() {}
};

template<class T>
class Matrix {
private:
    unsigned int rows;
    unsigned int cols;
    T * values;

    const T EPS = 10e-6;  // Точность при сравнении величин с плавающей точкой

public:
    static_assert(
            std::is_same<double, T>::value ||
            std::is_same<float, T>::value ||
            std::is_same<long double, T>::value,
            "T must be int, double or float");

    Matrix();

    Matrix(unsigned int rows, unsigned int cols);

    Matrix(const Matrix &);
    Matrix(Matrix &&mat) noexcept;

    Matrix set_value(T value);  // Заполнение созданной матрицы одним числом
    Matrix set_random(int min_value, int max_value);  // Заполнение созданной матрицы случайно
    Matrix set_identity();  // Преобразование матрицы в единичную
    Matrix fill_from_array(T * array);  // Заполнение матрицы значениями из массива

    T get(unsigned int row, unsigned int col);  // Получение произвольного элемента матрицы
    void set(unsigned int row, unsigned int col, T val);  // Изменение произвольного элемента матрицы

    Matrix& operator=(const Matrix& mat);
    Matrix& operator=(Matrix&& mat) noexcept;
    bool operator==(const Matrix& mat);
    bool operator!=(const Matrix& mat) { return !(*this == mat); }
    T * operator[](unsigned int row);  // Доступ к заданной строке матрицы
    bool is_identity();
    bool is_diagonal();

    Matrix operator+(const Matrix& mat) const;
    Matrix operator-(const Matrix& mat) const;
    Matrix operator*(T scalar) const;
    Matrix operator*(const Matrix& mat2) const;
    Matrix operator/(T scalar) const;

    void operator+=(const Matrix& mat) { *this = *this + mat; }
    void operator-=(const Matrix& mat) { *this = *this - mat; }
    void operator*=(const Matrix& mat) { *this = *this * mat; }

    Matrix transpose();
    void swap_rows(unsigned int row1, unsigned int row2);
    unsigned int upper_triangle();
    T det();
    T trace();

    Matrix minor(unsigned int minor_row, unsigned int minor_col);
    Matrix inv();
    Matrix exp();

    explicit operator bool() {  //  Явное преобразование - приведение типов данных
        for (unsigned int idx = 0; idx < rows * cols; idx++) {
            if (!(bool) values[idx]) return false;
        }
        return true;
    }

    void print() { std::cout << *this << std::endl; }

    ~Matrix() { delete[] this->values; }
};

template <typename T>
Matrix<T>::Matrix() : rows(0), cols(0), values(nullptr) {}

template <typename T>
Matrix<T>::Matrix(unsigned int rows, unsigned int cols)
        : rows(rows), cols(cols) {
    values = new T[rows * cols];
    if (!values) throw MatrixException("Error: unable to allocate memory");
}

template <typename T>
Matrix<T>::Matrix(const Matrix& mat) {
    rows = mat.rows;
    cols = mat.cols;
    values = new T[rows * cols];
    if (!values) throw MatrixException("Error: unable to allocate memory");
    memcpy(values, mat.values, sizeof(T) * rows * cols);
}

template <typename T>
Matrix<T>::Matrix(Matrix&& mat) noexcept {
    values = mat.values;
    rows = mat.rows;
    cols = mat.cols;
    mat.values = nullptr;
    mat.rows = 0;
    mat.cols = 0;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& mat) {
    if (this == &mat) return *this;
    delete[] values;
    rows = mat.rows;
    cols = mat.cols;
    memcpy(values, mat.values, rows * cols * sizeof(T));
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix&& mat) noexcept {  // Оператор перемещающего присваивания
    if (this == &mat) return *this;
    delete[] values;
    rows = mat.rows;
    cols = mat.cols;
    values = mat.values;
    mat.values = nullptr;
    return *this;
}

template <typename T>
T Matrix<T>::get(unsigned int row, unsigned int col) {
    if (row > rows || col > cols) throw
                MatrixException("Index error: one of the indexes is bigger than matrix size");
    return values[col + row * cols];
}

template <typename T>
void Matrix<T>::set(unsigned int row, unsigned int col, T value) {
    if (row > rows || col > cols) return;
    values[col + row * cols] = value;
}

template <typename T>
T* Matrix<T>::operator[](unsigned int idx) {
    if (idx > rows) return nullptr;
    return values + idx * cols;
}

template <typename T>
bool Matrix<T>::operator==(const Matrix& mat) {
    if (this->cols != mat.cols || this->rows != mat.rows) return false;
    for (unsigned int idx = 0; idx < this->cols * this->rows; idx++) {
        if (fabs(this->values[idx] - mat.values[idx]) > EPS) return false;
    }
    return true;
}

template <typename T>
Matrix<T> Matrix<T>::set_value(T value) {
    for (unsigned int idx = 0; idx < rows * cols; idx++) values[idx] = value;
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::set_random(int min_value, int max_value) {
    for (unsigned int idx = 0; idx < rows * cols; idx++) {
        values[idx] = min_value + (T) rand() / (T) RAND_MAX * (max_value - min_value);
    }
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::set_identity() {
    if (rows != cols) throw MatrixException("Error: Matrix must be square");
    this->set_value(0.0);
    for (unsigned int idx = 0; idx < rows * cols; idx += cols + 1) {
        this->values[idx] = 1.0;
    }
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::fill_from_array(T* array) {
    memcpy(values, array, rows * cols * sizeof(T));
    return *this;
}

template <typename T>
bool Matrix<T>::is_identity() {
    if (cols != rows) return false;
    for (unsigned int idx = 0; idx < rows * cols; idx++) {
        if (idx % (rows + 1) == 0) {
            if (fabs(values[idx] - 1) > EPS) return false;
        } else {
            if (fabs(values[idx]) > EPS) return false;
        }
    }
    return true;
}

template <typename T>
bool Matrix<T>::is_diagonal() {
    if (cols != rows) return false;
    for (unsigned int idx = 0; idx < rows * cols; idx++) {
        if (idx % (rows + 1) != 0 && fabs(values[idx]) > EPS) return false;
    }
    return true;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix& mat) const {
    if (this->rows != mat.rows || this->cols != mat.cols) throw
                MatrixException("Matrices must be the same size");
    Matrix res = {rows, cols};
    for (unsigned int idx = 0; idx < rows * cols; idx++) {
        res.values[idx] = this->values[idx] + mat.values[idx];
    }
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix& mat2) const {
    if (this->rows != mat2.rows || this->cols != mat2.cols) throw
                MatrixException("Matrices must be the same size");
    Matrix res = {rows, cols};
    for (unsigned int idx = 0; idx < rows * cols; idx++) {
        res.values[idx] = this->values[idx] - mat2.values[idx];
    }
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const T scalar) const {
    Matrix res = *this;
    for (unsigned int idx = 0; idx < rows * cols; idx++) res.values[idx] *= scalar;
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator/(const T scalar) const {
    Matrix res = *this;
    for (unsigned int idx = 0; idx < rows * cols; idx++) res.values[idx] /= scalar;
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix& mat2) const {
    if (this->cols != mat2.rows)
        throw MatrixException("Error: First matrix cals must be equal to second matrix rows");
    Matrix res = {this->rows, this->cols};
    for (unsigned int row = 0; row < res.rows; row++) {
        for (unsigned int col = 0; col < res.cols; col++) {
            T summa = 0.0;
            for (unsigned int idx = 0; idx < this->cols; idx++) {
                summa += this->values[row * this->cols + idx] * mat2.values[idx * mat2.cols + col];
            }
            res.values[res.cols * row + col] = summa;
        }
    }
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::transpose() {  //  Проверка на квадратную форму в класс исключений
    if (this->cols != this->rows)
        throw MatrixException("Error: Matrix must be square");
    Matrix res = {this->cols, this->rows};
    for (unsigned int row = 0; row < res.rows; row++) {
        for (unsigned int col = 0; col < res.cols; col++) {
            res.values[row * res.cols + col] = this->values[col * res.rows + row];
        }
    }
    return res;
}

template <typename T>
void Matrix<T>::swap_rows(unsigned int row1, unsigned int row2){
    auto temp = new T[cols];
    memcpy(temp, this->operator[](row1), cols * sizeof(T));
    memcpy(this->operator[](row1), this->operator[](row2), cols * sizeof(T));
    memcpy(this->operator[](row2), temp, cols * sizeof(T));
}

template <typename T>
unsigned int Matrix<T>::upper_triangle() {  //  Возврат матрицы с верхним треугольников 
    if (rows != cols) throw MatrixException("Error: Matrix must be square");
    unsigned int swap_num = 0;
    for (unsigned int step = 0; step < this->cols; step++) {
        unsigned int non_zero_row = step;  // Переход к следующему столбцу, все элементы столбца нулевые
        while (this->values[non_zero_row * this->cols + step] == 0 && non_zero_row != this->rows - 1) non_zero_row++;
        if (non_zero_row == step) continue;
        this->swap_rows(non_zero_row, step);
        swap_num += 1;
    }
    for (unsigned int col = 0; col < this->cols - 1; col++) {
        if (this->values[col + this->cols * col] == 0) continue;
        for (unsigned int row = col + 1; row < this->rows; row++) {
            T factor = this->values[col + this->cols * row] / this->values[col + this->cols * col];
            for (unsigned int idx = col; idx < this->cols; idx++) {
                this->values[idx + this->cols * row] -= this->values[idx + this->cols * col] * factor;
            }
        }
    }
    return swap_num;
}

template <typename T>
T Matrix<T>::det() {  //  Определитель
    if (rows != cols) throw MatrixException("Error: Matrix must be square");
    Matrix temp = *this;
    unsigned int swap_num = temp.upper_triangle();
    T res = 1;
    for (unsigned int idx = 0; idx < temp.rows * temp.cols; idx += temp.cols + 1) {
        res *= temp.values[idx];
    }
    return res * (1 - 2 * (swap_num % 2 == 1));
}

template <typename T>
T Matrix<T>::trace() {
    if (rows != cols) throw MatrixException("Error: Matrix must be square");
    T res = 0.0;
    for (unsigned int idx = 0; idx < this->rows * this->cols; idx += this->cols + 1) res += this->values[idx];
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::minor(const unsigned int minor_row, const unsigned int minor_col){  // Минор матрицы по строке minor_row и столбцу minor_col

    Matrix mat = *this;
    Matrix temp = Matrix(mat.rows - 1, mat.cols - 1);
    int minor_index = 0;
    for (unsigned int row = 0; row < mat.rows; row++){
        for (unsigned int col = 0; col < mat.cols; col++) {
            if (row == minor_row || col == minor_col) continue;
            temp.values[minor_index++] = mat.values[row * mat.rows + col];
        }
    }
    return temp;
}

template <typename T>
Matrix<T> Matrix<T>::inv() {  //  Инверсия матрицы
    if (rows != cols) throw MatrixException("Error: Matrix must be square");
    Matrix mat = *this;
    Matrix ans = {mat.rows, mat.cols};
    T determinant = mat.det();
    for (unsigned int row = 0; row < mat.rows; row++){
        for (unsigned int col = 0; col < mat.cols; col++){
            ans.values[col * ans.rows + row] = pow(-1, row + col) *
                                               mat.minor(row, col).det() / determinant;
        }
    }
    return ans;
}

template <typename T>
Matrix<T> Matrix<T>::exp() {  //  Матричная экспонента 
    if (rows != cols) throw MatrixException("Error: Matrix must be square");
    Matrix ans = *this;
    if (this->is_diagonal()) {
        for (unsigned int idx = 0; idx < rows * cols; idx++) {
            if (idx % (rows + 1) == 0 ) ans.values[idx] = ::exp(ans.values[idx]);
            else ans.values[idx] = 0;
        }
        return ans;
    }
    
    int max_iter = 20;  // Если матрица не диагональная, то вычисляем через степенной ряд
    Matrix pow = Matrix(this->rows, this->cols).set_identity();
    ans.set_identity();
    unsigned long long int factorial = 1;
    for(int iter = 1; iter < max_iter; iter++) {
        pow *= *this;
        factorial *= iter;
        ans += pow / factorial;
    }
    return ans;
}


  //  Создание класса наследования для памяти и количества
  
  
template <typename T>
class matrix_with_memory : public matrix<T> {
private:
	unsigned int mem_size{ 0 };
	static unsigned int total_mem;

public:
	matrix_with_memory();
	matrix_with_memory(unsigned int cols, unsigned int rows, T value = 0.);
	matrix_with_memory(const matrix_with_memory& matrix);
	matrix_with_memory(matrix_with_memory&& matrix) noexcept;
	~matrix_with_memory();

	matrix_with_memory& operator=(matrix_with_memory&& matrix) noexcept;
	matrix_with_memory& operator=(const Matrix_with_memory& matrix);

	void print_report();
};

template <typename T>
unsigned int matrix_with_memory<T>::total_mem = 0;


template <typename T>
matrix_with_memory<T>::matrix_with_memory() : Matrix<T>() {
	this->mem_size = 0;
	this->total_mem += this->mem_size;
}


template <typename T>
matrix_with_memory<T>::matrix_with_memory(unsigned int cols, unsigned int rows, T value): 
matrix<T> (cols, rows, value) {
	this->mem_size = cols * rows * sizeof(T);
	this->total_mem += this->mem_size;
}


template <typename T>
matrix_with_memory<T>::matrix_with_memory(const matrix_with_memory& matrix) : matrix(matrix) {
	this->mem_size = matrix.mem_size;
	this->total_mem += this->mem_size;
}


template <typename T>
matrix_with_memory<T>::matrix_with_memory(matrix_with_memory&& matrix) noexcept : matrix(matrix) {
	this->mem_size = matrix.mem_size;

	matrix.mem_size = 0;

}


template <typename T>
matrix_with_memory<T>::~matrix_with_memory() {
	std::cout << "matrix is destroyed\n";
	print_report();

	this->total_mem -= this->mem_size;
	this->mem_size = 0;


}

template <typename T>
matrix_with_memory<T>& matrix_with_memory<T>::operator=(matrix_with_memory&& matrix) noexcept {
	if (this == &matrix) return *this;
	this->rows = matrix.rows;
	this->cols = matrix.cols;
	this->values = matrix.values;

	this->total_mem = - this->mem_size + matrix.mem_size;

	this->mem_size = matrix.mem_size;

	matrix.mem_size = 0;
	matrix.values = nullptr;
	return *this;

	if (this != &matrix) {
		this->memory_size = matrix.mem_size;

		matrix.mem_size = 0;
		
	}

}


template <typename T>
matrix_with_memory<T>& matrix_with_memory<T>::operator=(const matrix_with_memory& matrix) {
	if (this == &matrix) {
		return *this;
	}
	delete[] this->values;

	this->rows = matrix.rows;
	this->cols = matrix.cols;

	this->values = new T[this->rows * this->cols];
	memcpy(this->values, matrix.values, this->rows * this->cols * sizeof(T));

	this->total_mem -= this->mem_size;
	this->mem_size = matrix.mem_size;

	return *this;
}

template <typename T>
void matrix_with_mem<T>::print_report() {
	std::cout << "memory size: " << this->mem_size << "\n";
	std::cout << "total memory size: " << this->total_mem << "\n";
	std::cout << "\n";
}

template <typename T>
class matrix_quantity: public matrix<T> {
private:
    static unsigned int quantity = 0;
public:
    matrix_quantity<T>() {
        quantity ++;
    }

  
    ~matrix_quantity()
    {
        quantity --;
    }
};


