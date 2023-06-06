#include <iostream>
#include <vector>
#define vl std::vector<int>
using std::cout;

int partition(vl &vector, int start, int pivot)
{
  int i = start;
  while(i < pivot)
  {
    if(vector[i] > vector[pivot] && i == pivot-1)
    {
      std::swap(vector[i], vector[pivot]);
      pivot--;
    }

    else if(vector[i] > vector[pivot])
    {
      std::swap(vector[pivot - 1], vector[pivot]);
      std::swap(vector[i], vector[pivot]);
      pivot--;
    }

    else i++;
  }
  return pivot;
}

void quickSort(vl &vector, int start, int end)
{
  if(start < end)
  {
    int pivot = partition(vector, start, end);

    quickSort(vector, start, pivot - 1);
    quickSort(vector, pivot + 1, end);
  }
}

int main()
{
  vl vector = {5, 2, 12, 7, 4, 24, 8, 15, 32, 6};

  quickSort(vector, 0, vector.size());

  cout<<"Sorted array\n";
  for (int i : vector)
  {
    cout<<i<<" ";
  }

  return 0;
}