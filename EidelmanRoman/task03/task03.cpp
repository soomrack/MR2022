short n = 2;
short m = 2;


class Matrix
{
private:
    unsigned int rows;
    unsigned int cols;
    double **values;
    double *data;
public:
    Matrix(unsigned int input_rows, unsigned int input_cols)
    {
        rows = input_rows;
        cols = input_cols;
        data = new double[rows * cols + rows];  // new ...[]   // delete[] data;
        for (int row = 0; row < rows; row++)
            values[row] = data + row * cols;
    };

    ~Matrix()
    {
        delete[] data;
    }

    Matrix operator + (Matrix second_matrix);
    Matrix operator - (Matrix second_matrix);
    Matrix operator * (Matrix second_matrix);
    Matrix operator ^ (int x);
    Matrix operator / (double x);
};

Matrix Matrix::operator + (Matrix second_matrix)
{
    Matrix addition_matrix(rows, cols);
    for (int row = 0; row < addition_matrix.rows; row++)
    {
        for (int col = 0; col < addition_matrix.cols; col++)
        {
            addition_matrix.values[row][col] = values[row][col] + second_matrix.values[row][col];
        }
    }
    return addition_matrix;
}

Matrix Matrix::operator - (Matrix second_matrix)
{
    Matrix subtraction_matrix(rows, cols);
    for (int row = 0; row < subtraction_matrix.rows; row++)
    {
        for (int col = 0; col < subtraction_matrix.cols; col++)
        {
            subtraction_matrix.values[row][col] = values[row][col] - second_matrix.values[row][col];
        }
    }
    return subtraction_matrix;
}

Matrix Matrix::operator * (Matrix second_matrix)
{
    Matrix multiplication_matrix(rows, cols);
    for (int row = 0; row < multiplication_matrix.rows; row++)
    {
        for (int col = 0; col < multiplication_matrix.cols; col++)
        {
            for (int k = 0; k < multiplication_matrix.rows; k++)
            {
                multiplication_matrix.values[rows][cols] = multiplication_matrix.values[rows][cols] + values[rows][k] * second_matrix.values[k][cols];
            }
        }
    }
    return multiplication_matrix;
}

Matrix Matrix::operator ^ (int x) {

    Matrix result_matrix(rows, cols);
    result_matrix.values = values;
    for (int i = 1; i < x; x++)
    {
        result_matrix = result_matrix * result_matrix;
    }
    return result_matrix;
}

Matrix Matrix::operator / (double x)
{
    Matrix result_matrix(rows, cols);
    for (int row = 0; row < result_matrix.rows; row++)
    {
        for (int col = 0; col < result_matrix.cols; col++)
        {
            result_matrix.values[row][col] = values[row][col] / x;
        }
    }
    return result_matrix;
}

Matrix A(n, m);
Matrix B(n, m);

int main()
{

    return 0;
}