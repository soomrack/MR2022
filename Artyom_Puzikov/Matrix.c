#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Matrix
{
  unsigned int columns, rows;
  double *values;
};

struct Matrix minor(const struct Matrix *matrix, const unsigned int minor_row, const unsigned int minor_column)
{
  struct Matrix answer;
  answer.rows = matrix->rows - 1;
  answer.columns = matrix->columns - 1;
  answer.values = malloc(sizeof(double) * answer.rows * answer.columns);
  int minor_index = 0;
  for (int i = 0; i < matrix->rows; ++i)
  {
    for (int j = 0; j < matrix->columns; ++j)
    {
      if (i != minor_row && j != minor_column)
      {
        answer.values[minor_index++] = matrix->values[i * matrix->rows + j];
      }
    }
  }
  return answer;
}

double detMatrix(const struct Matrix matrix){
  if (matrix.rows != matrix.columns){
    printf("The determinant cannot be calculated");
    exit(1);
  }
  double answer = 0;
  if (matrix.rows == 2){
    answer = matrix.values[0] * matrix.values[3] - matrix.values[1] * matrix.values[2];
    return answer;
  }
  for (int i = 0; i < matrix.columns; ++i)
  {
    answer += pow(-1.0, i) * matrix.values[i] * detMatrix(minor(&matrix, 0, i));
  }
  return answer;
}

void fillMatrix(struct Matrix *matrix)
{
  for (int i = 0; i < matrix->rows * matrix->columns; ++i)
  {
    matrix->values[i] = i + 1;
  }
}

struct Matrix sumMatrix(const struct Matrix *matrix1, const struct Matrix *matrix2)
{
  if (!(matrix1->rows == matrix2->rows && matrix1->columns == matrix2->columns))
  {
    printf("These matrices cannot be folded");
    _Exit(1);
  }
  struct Matrix result;
  result.rows = matrix1->rows;
  result.columns = matrix1->columns;
  result.values = malloc(sizeof(double) * matrix1->columns * matrix1->rows);
  for (int i = 0; i < matrix1->columns * matrix1->rows; ++i)
  {
    result.values[i] = matrix1->values[i] + matrix2->values[i];
  }
  return result;
}

struct Matrix subMatrix(const struct Matrix *matrix1, const struct Matrix *matrix2)
{
  if (!(matrix1->rows == matrix2->rows && matrix1->columns == matrix2->columns))
  {
    printf("These matrices cannot be folded");
    _Exit(1);
  }
  struct Matrix result;
  result.rows = matrix1->rows;
  result.columns = matrix1->columns;
  result.values = malloc(sizeof(double) * matrix1->columns * matrix1->rows);
  for (int i = 0; i < matrix1->columns * matrix1->rows; ++i)
  {
    result.values[i] = matrix1->values[i] - matrix2->values[i];
  }
  return result;
}

struct Matrix multMatrix(const struct Matrix *matrix1, const struct Matrix *matrix2)
{
  if (matrix1->columns != matrix2->rows)
  {
    printf("These matrices cannot be multiplied");
    _Exit(1);
  }
  struct Matrix result;
  result.rows = matrix1->rows;
  result.columns = matrix2->columns;
  result.values = calloc(matrix2->columns * matrix1->rows, sizeof(double));
  for (int i = 0; i < matrix1->rows; ++i)
  {
    for (int j = 0; j < matrix2->columns; ++j)
    {
      for (int k = 0; k < matrix1->columns; ++k)
      {
        result.values[i * result.columns + j] +=
          matrix1->values[i * matrix1->columns + k] * matrix2->values[k * matrix2->columns + j];
      }
    }
  }
  return result;
}

struct Matrix multScalar(const struct Matrix *matrix1, const double scalar)
{
  struct Matrix result;
  result.rows = matrix1->rows;
  result.columns = matrix1->columns;
  result.values = calloc(matrix1->columns * matrix1->rows, sizeof(double));
  for (int i = 0; i < matrix1->rows; ++i)
  {
    for (int j = 0; j < matrix1->columns; ++j)
    {
      result.values[i * result.columns + j] +=
        matrix1->values[i * matrix1->columns + j] * scalar;
    }
  }
  return result;
}

void printMatrix(const struct Matrix *matrix)
{
  for (int i = 0; i < matrix->rows; ++i)
  {
    for (int j = 0; j < matrix->columns; ++j)
    {
      printf("%f ", matrix->values[i * matrix->columns + j]);
    }
    printf("\n");
  }
  printf("\n");
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
  fillMatrix(&matrix1);
  fillMatrix(&matrix2);
  struct Matrix matrix3 = sumMatrix(&matrix1, &matrix2);
  printMatrix(&matrix3);
  matrix3 = subMatrix(&matrix1, &matrix2);
  printMatrix(&matrix3);
  matrix3 = multMatrix(&matrix1, &matrix2);
  printMatrix(&matrix3);
  matrix3 = multScalar(&matrix1, 5.0);
  printMatrix(&matrix3);
  printf("%f",detMatrix(matrix1));
  free(matrix1.values);
  free(matrix2.values);
  free(matrix3.values);
}
