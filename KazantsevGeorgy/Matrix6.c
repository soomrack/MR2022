#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Matrix{
    double *values;
    int rows;
    int cols;
};
typedef struct Matrix Matrix;
Matrix matrix_1, matrix_2, adde, subt, mult, powe;

void m_rows_cols(Matrix *matrix) {
    scanf("%d", &matrix->rows);
    scanf("%d", &matrix->cols);
}

Matrix m_setsize(int rows, int cols) {
    Matrix matrix;
    matrix.cols = cols;
    matrix.rows = rows;
    int n_values = matrix.cols * matrix.rows;
    matrix.values = malloc(sizeof(double) * n_values);
    return matrix;
}

void m_init(Matrix *matrix) {
    for (int i = 0; i < matrix -> cols * matrix -> rows; i++)
        matrix->values[i] = i;
}

void m_output(const Matrix matrix) {
    for (int i = 0; i < matrix.rows; i++) {
        printf("\n");
        for (int j = 0; j < matrix.cols; j++)
            printf("%f ", matrix.values[i * matrix.cols + j]);
    }
    printf("\n");
}

Matrix addition(Matrix matr1, Matrix matr2) {
    if ((matr1.cols == matr2.cols) && (matr1.rows == matr2.rows)) {
        Matrix resultmatrix = m_setsize(matr1.rows, matr2.cols);
        resultmatrix.values = malloc(sizeof(double) * matr1.cols * matr2.rows);
        for (int i = 0; i < matr1.cols * matr1.rows; i++) {
            resultmatrix.values[i] = matr1.values[i] + matr2.values[i];
        }
        return resultmatrix;
    } else {
        printf("imp");
        exit(EXIT_FAILURE);
    }
}

Matrix subtraction(Matrix matr1, Matrix matr2) {
    if ((matr1.cols == matr2.cols) && (matr1.rows == matr2.rows)) {
        Matrix resultmatrix = m_setsize(matr1.rows, matr2.cols);
        resultmatrix.values = malloc(sizeof(double) * matr1.cols * matr2.rows);
        for (int i = 0; i < matr1.cols * matr1.rows; i++) {
            resultmatrix.values[i] = matr1.values[i] - matr2.values[i];
        }
        return resultmatrix;
    } else {
        printf("imp");
        exit(EXIT_FAILURE);
    }
}

void transposition_out(Matrix matr) {
    Matrix resultmatrix = m_setsize(matr.rows, matr.cols);
    resultmatrix.values = malloc(sizeof(double) * matr.rows * matr.cols);
    for(int i = 0; i < matr.cols; i++) {
        printf("\n");
        for(int j =0; j < matr.rows; j++) {
            resultmatrix.values[i * matr.rows +j] = matr.values[j * matr.cols + i];
            printf("%f ", resultmatrix.values[i * matr.rows +j]);
        }
    }
}

Matrix transposition(Matrix matr) {
    Matrix resultmatrix = m_setsize(matr.rows, matr.cols);
    resultmatrix.values = malloc(sizeof(double) * matr.rows * matr.cols);
    for(int i = 0; i < matr.cols; i++) {
        for(int j =0; j < matr.rows; j++) {
            resultmatrix.values[i * matr.rows +j] = matr.values[j * matr.cols + i];
        }
    }
    return resultmatrix;
}

Matrix multiply(Matrix matrix1, Matrix matrix2) {
    if (matrix1.cols == matrix2.rows) {
        int cols = matrix2.cols;
        int rows = matrix1.rows;
        Matrix resultmatrix = m_setsize(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                double temp = 0.00;
                for (int k = 0; k < matrix1.cols; ++k) {
                    temp += matrix1.values[i * matrix1.cols + k] * matrix2.values[k * matrix2.cols + j];
                }
                resultmatrix.values[i * cols + j] = temp;
            }
        }
        return resultmatrix;
    }
    else {
        printf("IMP");
        exit(EXIT_FAILURE);
    }
}

double determinant(Matrix matrix) {
    if (matrix.cols != matrix.rows) {
        printf("imp");
        exit(EXIT_FAILURE);
    }
    double deter = 0;
    int size = matrix.cols;
    if (size == 1) {
        deter = matrix.values[0];
    }
    else {
        for (int i = 0; i < size; i++) {
            int j = 0;
            Matrix minor = m_setsize(size - 1, size - 1);
            int row_temp = 0;
            int col_temp = 0;
            for (int row = 0; row < size - 1; row++) {
                for (int col = 0; col < size - 1; col++) {
                    if (row == i)
                        row_temp = 1;
                    if (col == j)
                        col_temp = 1;
                    minor.values[row * (size - 1) + col] = matrix.values[(row + row_temp) * size + (col + col_temp)];
                }
            }
            deter += pow(-1, i + j) * matrix.values[i * size + j] * determinant(minor);
        }
    }
    return deter;
}

Matrix power(Matrix matrix, int n) {
    int rows = matrix.rows;
    int cols = matrix.cols;
    int k = 0;
    Matrix resultmatrix = matrix;
    if (n == 1) {
        return resultmatrix;
    }
    if (n > 1) {
        if (rows == cols) {
            k = 1;
            do {
                resultmatrix = multiply(resultmatrix, matrix);
                k =k + 1;
            } while (k < n);
        } else {
            printf("imp");
            exit(EXIT_FAILURE);
        }
    }
    return resultmatrix;
}

void start_calculating() {
    printf("select an action\n");
    printf("q - out1\nw - out2\ne - add\nt - subt\ny - tran1\nu - tran2\ni - det\no - mult\n1 - init\n");
    int condition;
    do {
        condition = getchar();
        switch (condition) {
            case 'q':
                printf("output first matrix\n");
                m_output(matrix_1);
                break;
            case 'w':
                printf("output second matrix\n");
                m_output(matrix_2);
                break;
            case 'e':
                printf("addititon of two matrix\n");
                adde = addition(matrix_1, matrix_2);
                m_output(adde);
                break;
            case 't':
                printf("subtraction of two matrix\n");
                subt = subtraction(matrix_1, matrix_2);
                m_output(subt);
                break;
            case 'y':
                printf("transposition of first matrix\n");
                transposition(matrix_1);
                break;
            case 'u':
                printf("transposition of second matrix\n");
                transposition(matrix_2);
                break;
            case 'i':
                printf("calculate the determinant of the first matrix\n");
                double dete;
                dete = determinant(matrix_1);
                printf("%f\n", dete);
                break;
            case 'o':
                printf("calculate the product of matrices\n");
                mult = multiply(matrix_1, matrix_2);
                m_output(mult);
                break;
            case '1':
                printf("--initialization\n");
                printf("Enter ows and cols\n");
                m_rows_cols(&matrix_1);
                matrix_1 = m_setsize(matrix_1.rows, matrix_1.cols);
                m_init(&matrix_1);

                printf("Enter ows and cols\n");
                m_rows_cols(&matrix_2);
                matrix_2 = m_setsize(matrix_2.rows, matrix_2.cols);
                m_init(&matrix_2);
                printf("complete\n");
            case '2':
                printf("power");
                powe = power(matrix_1, 3);
                m_output(powe);
            default:
                printf("...\n");
                break;
        }
    }
        while (condition != 'f');
        printf("the program has been stopped");
}

int main() {
    //start_calculating();
    printf("--initialization\n");
    printf("Enter ows and cols\n");
    m_rows_cols(&matrix_1);
    matrix_1 = m_setsize(matrix_1.rows, matrix_1.cols);
    m_init(&matrix_1);
    m_output(matrix_1);


    powe = power(matrix_1, 4);
    m_output(powe);
}