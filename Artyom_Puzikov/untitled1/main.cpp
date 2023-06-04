#include <iostream>
#include <vector>
int main()
{
  std::vector<int> vector{5, 2, 12, 7, 4, 24, 8, 15, 32, 6};

  for (int i = 0; i < 10; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      if (vector[j] > vector[j + 1])
      {
        int b = vector[j]; // создали дополнительную переменную
        vector[j] = vector[j + 1]; // меняем местами
        vector[j + 1] = b; // значения элементов
      }
    }
  }

  for (int i = 0; i < 10; i++)
  {
    std::cout << vector[i] << " "; // выводим элементы массива
  }

  return 0;
}