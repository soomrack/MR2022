#include <stdio.h>
#include <stdlib.h>
#include <math.h>


struct Matrix
{
  unsigned int columns;
  unsigned int rows;
  double *values;
};


struct Matrix empty_matrix()
{
  struct Matrix empty;
  empty.columns = 0;
  empty.rows = 0;
  empty.values = NULL;
  return empty;
}


struct Matrix minor(const struct Matrix *matrix, const unsigned int minor_row, const unsigned int minor_column)
{
  struct Matrix answer;
  answer.rows = matrix->rows - 1;
  answer.columns = matrix->columns - 1;
  answer.values = malloc(sizeof(double) * answer.rows * answer.columns);
  int minor_index = 0;
  for (unsigned int rows = 0; rows < matrix->rows; ++rows)
  {
    for (unsigned int cols = 0; cols < matrix->columns; ++cols)
    {
      if (rows != minor_row && cols != minor_column)
      {
        answer.values[minor_index++] = matrix->values[rows * matrix->rows + cols];
      }
    }
  }
  return answer;
}


struct Determinant
{
  double value;
  int error_code;
};


struct Determinant det_matrix(const struct Matrix matrix)
{
  struct Determinant determinant;
  determinant.value = 0.0;
  determinant.error_code = 0;
  if (matrix.rows != matrix.columns)
  {
    determinant.error_code = 1;
    return determinant;
  }
  double answer = 0;
  if (matrix.rows == 1)
  {
    determinant.value = matrix.values[0];
  }
  if (matrix.rows == 2)
  {
    answer = matrix.values[0] * matrix.values[3] - matrix.values[1] * matrix.values[2];
    determinant.value = answer;
    return determinant;
  }
  for (unsigned int i = 0; i < matrix.columns; ++i)
  {
    struct Matrix m = minor(&matrix, 0, i);
    answer += pow(-1.0, i) * matrix.values[i] * det_matrix(m).value;
    free(m.values);
  }
  determinant.value = answer;
  return determinant;
}


void fill_matrix(struct Matrix *matrix)
{
  for (unsigned int i = 0; i < matrix->rows * matrix->columns; ++i)
  {
    matrix->values[i] = rand() % 10;
  }
}


struct Matrix sum_matrix(const struct Matrix *matrix1, const struct Matrix *matrix2)
{
  if (!(matrix1->rows == matrix2->rows && matrix1->columns == matrix2->columns))
  {
    return empty_matrix();
  }
  struct Matrix result;
  result.rows = matrix1->rows;
  result.columns = matrix1->columns;
  result.values = malloc(sizeof(double) * matrix1->columns * matrix1->rows);
  for (unsigned int i = 0; i < matrix1->columns * matrix1->rows; ++i)
  {
    result.values[i] = matrix1->values[i] + matrix2->values[i];
  }
  return result;
}


struct Matrix sub_matrix(const struct Matrix *matrix1, const struct Matrix *matrix2)
{
  if (!(matrix1->rows == matrix2->rows && matrix1->columns == matrix2->columns))
  {
    return empty_matrix();
  }
  struct Matrix result;
  result.rows = matrix1->rows;
  result.columns = matrix1->columns;
  result.values = malloc(sizeof(double) * matrix1->columns * matrix1->rows);
  for (unsigned int i = 0; i < matrix1->columns * matrix1->rows; ++i)
  {
    result.values[i] = matrix1->values[i] - matrix2->values[i];
  }
  return result;
}


struct Matrix mult_matrix(const struct Matrix *matrix1, const struct Matrix *matrix2)
{
  if (matrix1->columns != matrix2->rows)
  {
    return empty_matrix();
  }
  struct Matrix result;
  result.rows = matrix1->rows;
  result.columns = matrix2->columns;
  result.values = calloc(matrix2->columns * matrix1->rows, sizeof(double));
  for (unsigned int row = 0; row < matrix1->rows; ++row)
  {
    for (unsigned int col = 0; col < matrix2->columns; ++col)
    {
      for (unsigned int k = 0; k < matrix1->columns; ++k)
      {
        result.values[row * result.columns + col] +=
          matrix1->values[row * matrix1->columns + k] * matrix2->values[k * matrix2->columns + col];
      }
    }
  }
  return result;
}


struct Matrix mult_scalar(const struct Matrix *matrix1, const double scalar)
{
  struct Matrix result;
  result.rows = matrix1->rows;
  result.columns = matrix1->columns;
  result.values = calloc(matrix1->columns * matrix1->rows, sizeof(double));
  for (unsigned int i = 0; i < matrix1->columns * matrix1->rows; ++i)
  {
    result.values[i] += matrix1->values[i] * scalar;
  }
  return result;
}


struct Matrix transpose_matrix(const struct Matrix *matrix)
{
  struct Matrix result;
  result.rows = matrix->columns;
  result.columns = matrix->rows;
  result.values = calloc(matrix->columns * matrix->rows, sizeof(double));
  for (unsigned int row = 0; row < result.rows; ++row)
  {
    for (unsigned int col = 0; col < result.columns; ++col)
    {
      result.values[row * result.columns + col] = matrix->values[col * result.rows + row];
    }
  }
  return result;
}


struct Matrix unit(unsigned int dimention)
{
  struct Matrix result;
  result.rows = dimention;
  result.columns = dimention;
  result.values = calloc(result.columns * result.rows, sizeof(double));
  for (unsigned int row = 0; row < result.rows; ++row)
  {
    for (unsigned int col = 0; col < result.columns; ++col)
    {
      result.values[row * result.columns + col] = (row == col) ? 1. : 0.;
    }
  }
  return result;
}


struct Matrix copy(const struct Matrix *matrix)
{
  struct Matrix result;
  result.rows = matrix->rows;
  result.columns = matrix->columns;
  result.values = calloc(result.columns * result.rows, sizeof(double));
  for (unsigned int index = 0; index < matrix->columns * matrix->rows; ++index)
  {
    result.values[index] = matrix->values[index];
  }
  return result;
}


struct Matrix exp_matrix(const struct Matrix matrix, unsigned int accuracy)
{
  if (matrix.columns != matrix.rows)
  {
    return empty_matrix();
  }
  struct Matrix result_, pow_, multiplied;
  struct Matrix result = unit(matrix.rows);
  struct Matrix pow = unit(matrix.rows);
  int factorial = 1;
  for (int acc = 1; acc <= accuracy; ++acc)
  {
    factorial *= acc;
    pow_ = mult_matrix(&pow, &matrix);
    pow = copy(&pow_);
    free(pow_.values);
    multiplied = mult_scalar(&pow, 1. / factorial);
    result_ = sum_matrix(&result, &multiplied);
    result = copy(&result_);
    free(result_.values);
    free(multiplied.values);
  }
  free(pow.values);
  return result;
}


void print_matrix(const char *name, const struct Matrix *matrix)
{
  printf("%s\n", name);
  for (unsigned int i = 0; i < matrix->rows; ++i)
  {
    for (unsigned int j = 0; j < matrix->columns; ++j)
    {
      printf("%f ", matrix->values[i * matrix->columns + j]);
    }
    printf("\n");
  }
  printf("\n");
  free(matrix->values);
}


void test(const char *name, const struct Matrix *matrix)
{
  if (matrix->values == NULL)
  {
    printf("Matrix can not be calculated\n\n");
  } else
  {
    print_matrix(name, matrix);
  }
}


void test_det(const struct Determinant determinant)
{
  if (determinant.error_code != 0)
  {
    printf("Determinant can not be calculated");
  } else
  {
    printf("Determinant\n");
    printf("%d\n\n", determinant.value);
  }
}


int main()
{
  struct Matrix matrix1, matrix2;
  matrix1.columns = 3;
  matrix1.rows = 3;
  matrix1.values = malloc(sizeof(double) * matrix1.columns * matrix1.rows);
  matrix2.columns = 3;
  matrix2.rows = 3;
  matrix2.values = malloc(sizeof(double) * matrix2.columns * matrix2.rows);

  fill_matrix(&matrix1);
  fill_matrix(&matrix2);

  struct Matrix matrix3 = sum_matrix(&matrix1, &matrix2);
  test("Sum", &matrix3);

  matrix3 = sub_matrix(&matrix1, &matrix2);
  test("Sub", &matrix3);

  matrix3 = transpose_matrix(&matrix1);
  test("Transpose", &matrix3);

  matrix3 = mult_scalar(&matrix1, 5.0);
  test("Mult on scalar", &matrix3);

  matrix3 = mult_matrix(&matrix1, &matrix2);
  test("Mult", &matrix3);

  struct Determinant d;
  d = det_matrix(matrix1);
  test_det(d);

  matrix3 = exp_matrix(matrix1, 3);
  test("Exp", &matrix3);

  free(matrix1.values);
  free(matrix2.values);
}
