#include <iostream>
#include <vector>

using namespace std;


int main()
{
  std::vector<int> vector = {5, 2, 12, 7, 4, 24, 8, 15, 32, 6};
  for (int i = 1; i < vector.size(); i++)
    for (int j = i; j > 0 && vector[j - 1] > vector[j]; j--)// пока j>0 и элемент j-1 > j, x-массив int
    {
      std::swap(vector[j - 1], vector[j]);        // меняем местами элементы j и j-1
    }
  cout << "Sorted array is \n";
  for (int i : vector)
    cout << i << " ";
  cout << "\n";
}