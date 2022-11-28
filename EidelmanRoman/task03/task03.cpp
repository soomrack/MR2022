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
};

Matrix A(2, 2);
Matrix B(2, 2);

int main()
{

    return 0;
}