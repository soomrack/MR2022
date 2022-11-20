#include <stdio.h>
#include <malloc.h>


typedef struct {
    unsigned int cols;
    unsigned int rows;
    double *values;
    
} Matrix;

Matrix matrix_make (const unsigned int cols, const unsigned int rows){  // Инициализация матрицы
    Matrix matrix;
    matrix.cols = cols;
    matrix.rows = rows;
    matrix.values = malloc(cols * rows * sizeof(double));
    for (unsigned int idx = 0; idx < cols * rows; idx++){
        matrix.values[idx] = 0.0;
    }
    return matrix;
}

Matrix data_input(Matrix matrix, double arr[]){
    for (unsigned int idx = 0; idx < matrix.cols * matrix.rows; idx++){
        matrix.values[idx] = arr[idx];
    }
    return matrix;
}

Matrix zero(const unsigned int cols, const unsigned int rows){  // Инициализация нулевой матрицы
    Matrix zero;
    zero.cols = cols;
    zero.rows = rows;
    zero.values = malloc(cols * rows * sizeof(double));
    for (unsigned int idx = 0; idx < cols * rows; idx++){
        zero.values[idx] = 0.0;
    }
    return zero;
};

Matrix one(const unsigned int cols, const unsigned int rows){  // Инициализация единичной матрицы
    Matrix one;
    one.cols = cols;
    one.rows = rows;
    one.values = malloc(cols * rows * sizeof(double));
    for (unsigned int row = 0; row < one.rows; row++){
        for(unsigned int col = 0; col < one.cols; col++){
            if (row == col) {
                one.values[row * one.cols + col] = 1.0;}
            else {
                one.values[row * one.cols + col] = 0.0;}
        }
    }
    return one;
};


void print_matrix(const Matrix x){// Вывод матрицы на экран
    printf("Matrix \n");
    for (unsigned int row = 0; row < x.rows; row++){
        for(unsigned int col = 0; col < x.cols; col++){
            printf("%.1lf\t", x.values[row * x.cols + col]);
        }
        printf("\n");
    }
}


Matrix error(void){  // Ошибка
    Matrix error;
    error.cols = 0;
    error.rows = 0;
    error.values = NULL;
    return error;
}


Matrix matrix_output(const Matrix a,char symbol) {  //  Вывод матрицы
    printf("A %c B=\n", symbol);
    for (unsigned int row = 0; row < a.rows; row++) {
        for (unsigned int col = 0; col < a.cols; col++) {
            printf("%.1lf\t",a.values[row * a.cols + col]);
        }
        printf("\n");
    }
}


Matrix matrix_sum(const Matrix a,const Matrix b){  //  Сумма матриц
    if ((a.cols != b.cols)||(a.rows != b.rows)) return error();
    Matrix c = matrix_make(a.cols,a.rows);
    for (unsigned int row = 0; row < a.rows; row++) {
        for (unsigned int col = 0; col < a.cols; col++) {
            c.values[row * c.cols + col] = a.values[row * a.cols + col] + b.values[row * b.cols + col];

        }
    }
    return c;
}


Matrix matrix_sub(const Matrix a, const Matrix b) {  //  Разность матриц
    if ((a.cols != b.cols)||(a.rows != b.rows)) return error();
    Matrix c = matrix_make(a.cols,a.rows);
    for (unsigned int row = 0; row < a.rows; row++) {
        for (unsigned int col = 0; col < a.cols; col++) {
            c.values[row * c.cols + col] = a.values[row * a.cols + col] - b.values[row * b.cols + col];
        }
    }
    return c;
}


Matrix matrix_output1(Matrix c) {
    printf("exponent a =\n");
    for (unsigned int row = 0; row < c.rows; row++) {
        for (unsigned int col = 0; col < c.cols; col++) {
            printf("%.1lf\t", c.values[row * c.cols + col]);
        }
        printf("\n");
    }
}

Matrix matrix_mult(const Matrix a, const Matrix b) {  //  Умножение матриц
    if ((a.cols != b.rows)||(a.rows != b.cols)) return error();
    Matrix c = matrix_make(b.cols,a.rows);
    for (unsigned int row = 0; row < a.rows; row++) {
        for (unsigned int col = 0; col < b.cols; col++) {
            c.values[row * c.rows + col] = 0;
            for(unsigned int k = 0; k < a.cols; k++) {
                c.values[row * c.cols + col] += a.values[row * a.cols + k] * b.values[k * b.cols + col];
            }
        }
    }
    return c;
}

int similar_is(Matrix a, Matrix b){
    for (int index = 0; index < a.rows * a.cols; index++){
        if ((int)(a.values[index] * 1000) != (int)(b.values[index] * 1000)){
            return 0;
        }
    }
    return 1;
}

Matrix matrix_exp (const Matrix a) {  //  Экспонента матрицы
    Matrix exp1 = one(a.cols, a.rows);
    Matrix exp = matrix_sum(exp1,a);
    free(exp1.values);
    int factorial = 1;
    Matrix numerator = matrix_make(a.cols, a.rows);
    for (unsigned int row = 0; row < a.rows; row++) {
        for (unsigned int col = 0; col < a.cols; col++) {
            numerator.values[row * a.cols + col] = a.values[row * a.cols + col];
        }
    }
    Matrix numerator1;
    for (int n = 2; n < 11; n++) {
        factorial *= n;
        numerator1 = matrix_mult(numerator,a);
        free(numerator.values);
        numerator = numerator1;
        for (unsigned int idx = 0; idx < numerator.cols * numerator.rows; idx++){
            numerator.values[idx] /= factorial;
        }
        exp1 = matrix_sum(exp,numerator);
        free(exp.values);
        exp = exp1;
        for (unsigned int idx = 0; idx < numerator.cols * numerator.rows; idx++){
            numerator.values[idx] *= factorial;
        }
    }
    free(numerator.values);
    return exp;

}
void incorrect_case (int a, int b, int c , int d) {  // Вывод неккоректного ввода
    if (a == 0) {
        printf("Sum work incorrectly\n");
    }
    if (b == 0) {
        printf("Substruction work incorrectly\n");
    }
    if (c == 0) {
        printf("Multiplication work incorrectly\n");
    }
    if (d == 0) {
        printf("Matrix exponent work incorrectly\n");
    }
}
void test(){  //  Проверка 
    Matrix zero = zero(3,3);
    Matrix one = one(3,3);

    Matrix summa = matrix_make(3,3);
    double arr_summa[] = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};
    data_input(summa, arr_summa);
    Matrix sum = matrix_sum(one,zero);
    int sum_clk = similar_is(sum, summa);
    free(summa.values);
    free(sum.values);

    Matrix substruction = matrix_make(3,3);
    double arr_substruction[] = {-1.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0, 0.0, -1.0};
    data_input(substruction, arr_substruction);
    int sub_clk =similar_is(matrix_sub(zero,one), substruction);
    free(substruction.values);

    Matrix mult = matrix_make(3,3);
    double arr_mult[] = {6.0, 5.0, 4.0, 3.0, 2.0, 1.0, 8.0, 7.0, 0.0};
    data_input(mult, arr_mult);
    int mult_clk =similar_is(matrix_mult(mult,one),mult);
    free(mult.values);

    Matrix exp = matrix_make(3,3);
    double arr_exp[] = {2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0};
    data_input(exp, arr_exp);
    Matrix real_exp = matrix_make(3,3);
    double arr_real_exp[] = {129.411, 128.411, 128.411, 128.411, 129.411, 128.411, 128.411, 128.411, 129.411};
    data_input(real_exp, arr_real_exp);
    int exp_clk = similar_is(matrix_exp(exp),real_exp);
    free(exp.values);
    free(real_exp.values);

    if (sum_clk * sub_clk * mult_clk * exp_clk == 1){
        printf("Functions work correctly\n");
    }
    else{
        printf("Functions work incorrectly\n");
        incorrect_case(sum_clk, sub_clk, mult_clk, exp_clk);
    }
}

int main() {
// тест функций
    test();
// создание первой матрицы
    Matrix a = matrix_make(3,3);
    double arr_a[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    data_input(a, arr_a);
    print_matrix(a);
// создание второй матрицы
    Matrix b = matrix_make(3,3);
    double arr_b[] = {9.0,8.0,7.0,6.0, 5.0, 4.0, 3.0, 2.0, 1.0};
    data_input(b, arr_b);
    print_matrix(b);
// математические операции с матрицами
    Matrix sum = matrix_sum(a,b);  // сумма
    matrix_output(sum,'+');
    Matrix sub = matrix_sub(a,b);  // разность
    matrix_output(sub,'-');
    Matrix mult = matrix_mult(a,b);  // умножение
    matrix_output(mult,'*');
    Matrix exp = matrix_exp(a);  // матричная экспонента
    matrix_output1(exp);
// освобождение памяти
    free(a.values);
    free(b.values);
    free(sum.values);
    free(sub.values);
    free(mult.values);
    free(exp.values);
    return 0;
}