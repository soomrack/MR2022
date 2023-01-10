
#ifndef MATRIX_CAL_MATRIX_H
#define MATRIX_CAL_MATRIX_H

#include <iostream>
#include <cmath>


const double EPS = 10e-6;  // Точность при сравнении величин с плавающей точкой


class MatrixException: public std::exception { // способ показать что произошло что-то не то // создание класса Исключения и наследование от стдЭксепшен
public:
    MatrixException(const char* msg): std::exception() {}  // создание метода (с вход значением const char* - указатель на строку данных :: - метод наследуется из стдЭксепшен
};



class Matrix {
protected:               // меняем private на protected чтобы произошло наследование 3 атрибутов ниже тк приватные бы не наследовались
    unsigned int rows;
    unsigned int cols;
    double* values; // указатель на массив


public:
    Matrix();                                          // Создание конструктора создающий нуль(ПУСТУЮ) матрицу
    Matrix(unsigned int rows, unsigned int cols);      // Создание конструктора создающий матрицу с выделением памяти
    Matrix(const Matrix &);                            // Создание конструктора копирования матрицы matrix A=B (& - ссылка)
    Matrix(Matrix &&mat) noexcept;                     // Создание конструктора перемещения матрицы matrix A=B+C (&& - Rvalue то что сохраняется справа от операции)

    Matrix set_value(double value);                   // Создание функции заполнения созданной матрицы одним числом
    Matrix set_random(int min_value, int max_value);  // Создание функции заполнения созданной матрицы случайно
    Matrix set_identity();                            // Создание функции преобразования матрицы в единичную
    Matrix fill_from_array(double* array);            // Создание функции заполнения матрицы значениями из массива

    double get(unsigned int row, unsigned int col);            // Создание функции получения произвольного элемента матрицы
    void set(unsigned int row, unsigned int col, double val);  // Создание функции изменения произвольного элемента матрицы

    Matrix& operator=(const Matrix& mat);      // Создание оператора копирующего присваивания A=B (нет matrix) существующая матрица А = сущ матрице Б, матрицы заранее введены
    Matrix& operator=(Matrix&& mat) noexcept;  // Создание оператора перемещающего присваивания A=B+C (нет matrix) существующая матрица А = сущ матрице Б и С, матрицы заранее введены

// && - Rvalue
// & - ссылка

    bool operator==(const Matrix& mat);                             // Создание логического оператора РАВНО ЛИ
    bool operator!=(const Matrix& mat) { return !(*this == mat); }  // Создание логического оператора НЕ РАВНО
    double* operator[](unsigned int row);                           // Создание оператора доступа к заданной строке матрицы через [номер строки]

    bool is_identity(); // Создание логической функции проверки на единичную матрицу
    bool is_diagonal(); // Создание логической функции проверки на диагональную матрицу

    Matrix operator+(const Matrix& mat) const;   // Создание оператора сложения матриц
    Matrix operator-(const Matrix& mat) const;   // Создание оператора вычитания матриц

    Matrix operator*(const Matrix& mat2) const;  // Создание оператора перемножение матриц

    Matrix operator*(double scalar) const;       // Создание оператора умножения на скаляр матриц
    Matrix operator/(double scalar) const;       // Создание оператора деления на скаляр матриц



    void operator+=(const Matrix& mat) { *this = *this + mat; }
    void operator-=(const Matrix& mat) { *this = *this - mat; }
    void operator*=(const Matrix& mat) { *this = *this * mat; }

    Matrix transpose(); // транспонирование
    void swap_rows(unsigned int row1, unsigned int row2); // свойства матрицы на замену 2 строк местами НУЖНО для нахождения определителя и верхней треугольной матрицы
    unsigned int upper_triangle(); // приводим матрицу к верхней треугольной чтобы ПОТОМ посчитать определитель как перемножение эл по диагонали
    double det(); // определить
    double trace(); // след матрицы

    Matrix minor(unsigned int minor_row, unsigned int minor_col); // минор
    Matrix inv(); // обратная
    Matrix exp(); // матричная экспонента

    friend std::ostream& operator<<(std::ostream &os, Matrix &mat);  // friend ключевое слово показывающее что оператор << определенный в библиотеке стд является дружественным и мы можем добавить к нему определение
    friend std::ostream& operator<<(std::ostream &os, Matrix &&mat);
    friend std::istream& operator>>(std::istream &is, Matrix &mat);

//    explicit operator bool() {   // оператор для проверки наличия данных в матрице если начнется логическая с ним операция типа If // explicit оператор явного приведения типов данных - из типа матрицы в тип бул (логический bool)
//        for (unsigned int idx = 0; idx < rows * cols; idx++) {
//            if (!(bool) values[idx]) return false;
//        }
//        return true;
//    }

    void print() { std::cout << *this << std::endl; } // чтобы не вводить так много БУКОВ а быстро выводить

    ~Matrix() { delete[] this->values; } // диструктор (очистка памяти от обьекта памяти выход из зоны видимости)
};



Matrix::Matrix() : rows(0), cols(0), values(nullptr) {} // nullptr - нулевой указатель и забит в саму система как NULL


Matrix::Matrix(unsigned int r_num, unsigned int c_num) {
    this->rows = r_num; // указатель на самого себя но можно и не писать
    cols = c_num;
    values = new double[rows * cols];  // new для выделения памяти для (кол-ва элементов)
    if (!values) throw MatrixException("Error: unable to allocate memory");
}


Matrix::Matrix(const Matrix& mat) {  // если создаем матрицу А=Б где Б была записана ранее
    rows = mat.rows;
    cols = mat.cols;
    values = new double[rows * cols];
    if (!values) throw MatrixException("Error: unable to allocate memory"); // невозможно выделить память
    memcpy(values, mat.values, sizeof(double) * rows * cols); // memcpy - копирование памяти (куда, откуда, размер - сколько), Нужно чтобы не было крит ошибки тк изначально идет обращение по указателю, а так мы создаем новую ячейку с памятью
}


Matrix::Matrix(Matrix&& mat) noexcept { // noexcept -  Указывает, может ли функция создавать исключения (показывает IDE)
    values = mat.values; // копируем все данные из временного обьекта из Rvalue при каких либо операциях (указатели, строки и столбцы)
    rows = mat.rows;
    cols = mat.cols;
    mat.values = nullptr; // зануляем указатель чтобы он потом никуда не ссылался на ост. данные
    mat.rows = 0;
    mat.cols = 0;
}


Matrix& Matrix::operator=(const Matrix& mat) {
    if (this == &mat) return *this;
    delete[] values;
    rows = mat.rows;
    cols = mat.cols;
    memcpy(values, mat.values, rows * cols * sizeof(double));
    return *this;
}


Matrix& Matrix::operator=(Matrix&& mat) noexcept {  // Оператор перемещающего присваивания
    if (this == &mat) return *this;
    delete[] values;
    rows = mat.rows;
    cols = mat.cols;
    values = mat.values;
    mat.values = nullptr;
    return *this;
}


double Matrix::get(unsigned int row, unsigned int col) {

    if (row > rows || col > cols) throw
                MatrixException("Index error: one of the indexes is bigger than matrix size");
    return values[col + row * cols];
}


void Matrix::set(unsigned int row, unsigned int col, double value) {
    if (row > rows || col > cols) return;
    values[col + row * cols] = value;
}


double* Matrix::operator[](unsigned int idx) {
    if (idx > rows) return nullptr; // проверка что указанное число строк не превышает всего строк
    return values + idx * cols;
}


bool Matrix::operator==(const Matrix& mat) {
    if (this->cols != mat.cols || this->rows != mat.rows) return false;
    for (unsigned int idx = 0; idx < this->cols * this->rows; idx++) {
        if (fabs(this->values[idx] - mat.values[idx]) > EPS) return false;
    }
    return true;
}


Matrix Matrix::set_value(double value) {
    for (unsigned int idx = 0; idx < rows * cols; idx++) values[idx] = value;
    return *this;
}


Matrix Matrix::set_random(int min_value, int max_value) {
    for (unsigned int idx = 0; idx < rows * cols; idx++) {
        values[idx] = min_value + (double) rand() / (double) RAND_MAX * (max_value - min_value); // нашел в инете
    }
    return *this;
}


Matrix Matrix::set_identity() {
    if (rows != cols) throw MatrixException("Error: Matrix must be square");
    this->set_value(0.0);
    for (unsigned int idx = 0; idx < rows * cols; idx += cols + 1) {
        this->values[idx] = 1.0;
    }
    return *this;
}


Matrix Matrix::fill_from_array(double* array) {
    memcpy(values, array, rows * cols * sizeof(double));
    return *this;
}


bool Matrix::is_identity() {
    if (cols != rows) return false;
    for (unsigned int idx = 0; idx < rows * cols; idx++) {
        if (idx % (rows + 1) == 0) {
            if (fabs(values[idx] - 1) > EPS) return false;
        } else {
            if (fabs(values[idx] - 0) > EPS) return false;
        }
    }
    return true;
}


bool Matrix::is_diagonal() {
    if (cols != rows) return false;
    for (unsigned int idx = 0; idx < rows * cols; idx++) {
        if (idx % (rows + 1) != 0 && fabs(values[idx]) > EPS) return false;
    }
    return true;
}


Matrix Matrix::operator+(const Matrix& mat) const { // 1) тип данных 2) класс Матрица :: - обращение к пространству имен в классе // оператор+ 3) аргументы Matrix& тип данных - ссылка на матрицу | mat - свое имя для переменной
    if (this->rows != mat.rows || this->cols != mat.cols) throw
                MatrixException("Matrices must be the same size");
    Matrix res = {rows, cols}; // иначе вызываем конструктор и создаем матрицу res с выделением памяти (3 матрица с результатом 1 + 2)
    for (unsigned int idx = 0; idx < rows * cols; idx++) {
        res.values[idx] = this->values[idx] + mat.values[idx]; // res = 3 а this 1 + mat 2
    }
    return res; // вывести результат
}


Matrix Matrix::operator-(const Matrix& mat2) const {
    if (this->rows != mat2.rows || this->cols != mat2.cols) throw
                MatrixException("Matrices must be the same size");
    Matrix res = {rows, cols};
    for (unsigned int idx = 0; idx < rows * cols; idx++) {
        res.values[idx] = this->values[idx] - mat2.values[idx];
    }
    return res;
}


Matrix Matrix::operator*(const double scalar) const {
    Matrix res = *this; // конструктор копирования матрицы для создания нашей res матрицы
    for (unsigned int idx = 0; idx < rows * cols; idx++) res.values[idx] *= scalar;
    return res;
}


Matrix Matrix::operator/(const double scalar) const {
    Matrix res = *this;
    for (unsigned int idx = 0; idx < rows * cols; idx++) res.values[idx] /= scalar;
    return res;
}

Matrix Matrix::operator*(const Matrix& mat2) const {
    if (this->cols != mat2.rows) throw
                MatrixException("Error: First matrix cals must be equal to second matrix rows");
    Matrix res = {this->rows, this->cols};
    for (unsigned int row = 0; row < res.rows; row++) {
        for (unsigned int col = 0; col < res.cols; col++) {
            double summa = 0.0;
            for (unsigned int idx = 0; idx < this->cols; idx++) {
                summa += this->values[row * this->cols + idx] * mat2.values[idx * mat2.cols + col];
            }
            res.values[res.cols * row + col] = summa;
        }
    }
    return res;
}


Matrix Matrix::transpose() {
    Matrix res = {this->cols, this->rows};
    for (unsigned int row = 0; row < res.rows; row++) {
        for (unsigned int col = 0; col < res.cols; col++) {
            res.values[row * res.cols + col] = this->values[col * res.rows + row];
        }
    }
    return res;
}


void Matrix::swap_rows(unsigned int row1, unsigned int row2){
    auto temp = new double[cols];
    memcpy(temp, this->operator[](row1), cols * sizeof(double));
    memcpy(this->operator[](row1), this->operator[](row2), cols * sizeof(double));
    memcpy(this->operator[](row2), temp, cols * sizeof(double));
}


unsigned int Matrix::upper_triangle() {
    if (rows != cols) throw MatrixException("Error: Matrix must be square");
    unsigned int swap_num = 0;
    for (unsigned int step = 0; step < this->cols; step++) {
        unsigned int non_zero_row = step;
        // Переход к следующему столбцу, все элементы столбца нулевые
        while (this->values[non_zero_row * this->cols + step] == 0 && non_zero_row != this->rows - 1) non_zero_row++;
        if (non_zero_row == step) continue;
        this->swap_rows(non_zero_row, step);
        swap_num += 1;
    }
    for (unsigned int col = 0; col < this->cols - 1; col++) {
        if (this->values[col + this->cols * col] == 0) continue;
        for (unsigned int row = col + 1; row < this->rows; row++) {
            double factor = this->values[col + this->cols * row] / this->values[col + this->cols * col];
            for (unsigned int idx = col; idx < this->cols; idx++) {
                this->values[idx + this->cols * row] -= this->values[idx + this->cols * col] * factor;
            }
        }
    }
    return swap_num;
}


double Matrix::det() {
    if (rows != cols) throw MatrixException("Error: Matrix must be square");
    Matrix temp = *this;
    unsigned int swap_num = temp.upper_triangle();
    double res = 1;
    for (unsigned int idx = 0; idx < temp.rows * temp.cols; idx += temp.cols + 1) {
        res *= temp.values[idx];
    }
    return res * (1 - 2 * (swap_num % 2 == 1));
}


double Matrix::trace() {
    if (rows != cols) throw MatrixException("Error: Matrix must be square");
    double res = 0.0;
    for (unsigned int idx = 0; idx < this->rows * this->cols; idx += this->cols + 1) res += this->values[idx];
    return res;
}


// Минор матрицы по строке minor_row и столбцу minor_col
Matrix Matrix::minor(const unsigned int minor_row, const unsigned int minor_col){
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


Matrix Matrix::inv() {
    if (rows != cols) throw MatrixException("Error: Matrix must be square");
    Matrix mat = *this;
    Matrix ans = {mat.rows, mat.cols};
    double determinant = mat.det();
    for (unsigned int row = 0; row < mat.rows; row++){
        for (unsigned int col = 0; col < mat.cols; col++){
            ans.values[col * ans.rows + row] = pow(-1, row + col) *
                                               mat.minor(row, col).det() / determinant;
        }
    }
    return ans;
}


Matrix Matrix::exp() {
    if (rows != cols) throw MatrixException("Error: Matrix must be square");
    Matrix ans = *this;
    if (this->is_diagonal()) {
        for (unsigned int idx = 0; idx < rows * cols; idx++) {
            if (idx % (rows + 1) == 0 ) ans.values[idx] = ::exp(ans.values[idx]);
            else ans.values[idx] = 0;
        }
        return ans;
    }
    // Если матрица не диагональная, то вычисляем через степенной ряд
    int max_iter = 20;
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


std::ostream& operator<<(std::ostream& os, Matrix& mat) { // вывод матрицы
    os << "\n";
    for (unsigned int row = 0; row < mat.rows; row++) {
        for (unsigned int col = 0; col < mat.cols; col++) {
            os << mat.values[col + row * mat.cols] << " ";
        }
        if (row != mat.rows - 1) os << "\n";
    }
    return os;
}


std::ostream& operator<<(std::ostream& os, Matrix&& mat) {  // вывод временной Rvalue матрицы
    os << "\n";
    for (unsigned int row = 0; row < mat.rows; row++) {
        for (unsigned int col = 0; col < mat.cols; col++) {
            os << mat.values[col + row * mat.cols] << " ";
        }
        if (row != mat.rows - 1) os << "\n";
    }
    return os;
}


std::istream &operator>>(std::istream &is, Matrix &mat) { // ввод матрицы
    for (int idx = 0; idx < mat.rows * mat.cols; idx++) {
        is >> mat.values[idx];
    }
    return is;
}

// наследуется все кроме атрибутов и методов в приватных полях + конструкторы и деструкторы

class MatrixMemory : public Matrix {  // создание нового класса Матрих Мемори с наследованием его от ранее созданного класса Матрих // с индикатором доступа - (: public) что означает что все поля родителя класса копируются с теми же индикаторами доступа
private:  // ниже 2 атрибута приватных от нового класса Матрих Мемори
    unsigned long int memory_size = 0;  // размер памяти который занимает Матрица (строки*столбец)
    static unsigned long int total_memory;  // общий размер памяти который занимают все объекты класса Матрих Мемори

// так как конструкторы и деструкторы НЕ наследуются от родителя (класс Матрих) нам нужно создавать новые конструкторы

public:
    MatrixMemory() { memory_size = 0; }  //
    MatrixMemory(unsigned int rows, unsigned int cols) {
        memory_size = rows * cols * sizeof(double);
        total_memory += memory_size;
    }

    MatrixMemory(const MatrixMemory& mat)  : Matrix(mat) {
        memory_size = mat.memory_size;
        total_memory += memory_size;
    }

    MatrixMemory(MatrixMemory&& mat) noexcept {
        memory_size = mat.memory_size;
    }

    MatrixMemory& operator=(const MatrixMemory& mat) noexcept {
        memory_size = mat.memory_size;
        total_memory += memory_size;
        return *this;
    }

    MatrixMemory& operator=(MatrixMemory&& mat) noexcept {
        memory_size = mat.memory_size;
        return *this;
    }

    unsigned long int get_total_memory() { return total_memory; }

    ~MatrixMemory() { total_memory -= memory_size; };
};

#endif //MATRIX_CAL_MATRIX_H
