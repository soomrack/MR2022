
typedef struct Matrix{
    unsigned int rows;
    unsigned int cols;
    double* values;
} Matrix;


// Вывод матрицы в консоль
void printm(struct Matrix mat);


Matrix create_null();

// Создание единичной матрицы размера n*n
Matrix create_identity(unsigned int size);


// Делает заданную матрицу единичной
void set_to_identity(const Matrix* mat);


// Создает копию матрицы
Matrix copy(Matrix mat);


// Проверяет равны ли две матрицы
int is_equal(Matrix mat1, Matrix mat2);

int is_identity(Matrix matrix);


// Создание матрицы со случайными значениями от 0 до max_value
Matrix create_random(unsigned int rows, unsigned int cols, double max_value);


// Сложение двух матриц
Matrix add(Matrix m1, Matrix m2);


// Вычитание двух матриц
Matrix sub(Matrix m1, Matrix m2);


// Умножение двух матриц
Matrix mul(Matrix m1, Matrix m2);


// Умножение матрицы на скаляр
Matrix s_mul(Matrix mat, double scal);


// Деление матрицы на скаляр
Matrix s_div(Matrix mat, double scal);


// Транспонирование матрицы
Matrix transpose(Matrix mat);


// Минор матрицы по строке minor_row и столбцу minor_col
Matrix minor(Matrix mat, unsigned int minor_row, unsigned int minor_col);


// Превращает матрицу в верхнюю треугольную
Matrix upper_triangle(Matrix mat);


double m_det(Matrix mat);


// Рекурсивная функция определителя матрицы
double recursive_det(Matrix mat);


// След (trace) матрицы
double m_tr(Matrix mat);


// Обратная матрица
Matrix m_inv(Matrix mat);


void iterate_exp(const Matrix* ans, Matrix mat);


// Экспонентная матрицы
Matrix m_exp(Matrix mat);