#include <stdio.h>

#include <stdlib.h>
#include <malloc.h>

struct Matrix
{
  unsigned int columns, rows;
  double *values;
};

struct Point
{
  int x, y;
};

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
}

int main()
{
  struct Matrix matrix1, matrix2;
  matrix1.columns = 2;
  matrix1.rows = 2;
  matrix1.values = malloc(sizeof(double) * matrix1.columns * matrix1.rows);
  matrix2.columns = 2;
  matrix2.rows = 2;
  matrix2.values = malloc(sizeof(double) * matrix2.columns * matrix2.rows);
  fillMatrix(&matrix1);
  fillMatrix(&matrix2);
  struct Matrix matrix3 = sumMatrix(&matrix1, &matrix2);
  printMatrix(&matrix3);
  matrix3 = subMatrix(&matrix1, &matrix2);
  printMatrix(&matrix3);
  matrix3 = multMatrix(&matrix1, &matrix2);
  printMatrix(&matrix3);
  free(matrix1.values);
  free(matrix2.values);
  free(matrix3.values);
}
