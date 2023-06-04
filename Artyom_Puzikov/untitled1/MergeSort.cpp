#include <iostream>
#include <vector>

#define vl std::vector<int>
using std::cout;

void merge(vl &vector, int start, int end, int mid);

void mergeSort(vl &vector, int start, int end)
{
  int mid;
  if (start < end)
  {

    mid = (start + end) / 2;
    mergeSort(vector, start, mid);
    mergeSort(vector, mid + 1, end);
    merge(vector, start, end, mid);
  }
}

void merge(vl &vector, int start, int end, int mid)
{
  vl mergedList;
  mergedList.resize(vector.size());
  int i, j, k;
  i = start;
  k = start;
  j = mid + 1;

  while (i <= mid && j <= end)
  {
    if (vector[i] < vector[j])
    {
      mergedList[k] = vector[i];
      k++;
      i++;
    } else
    {
      mergedList[k] = vector[j];
      k++;
      j++;
    }
  }

  while (i <= mid)
  {
    mergedList[k] = vector[i];
    k++;
    i++;
  }

  while (j <= end)
  {
    mergedList[k] = vector[j];
    k++;
    j++;
  }

  for (i = start; i < k; i++)
  {
    vector[i] = mergedList[i];
  }
}

int main()
{
  vl vector = {5, 2, 12, 7, 4, 24, 8, 15, 32, 6};
  mergeSort(vector, 0, vector.size() - 1);
  cout << "Sorted array\n";
  for (int i: vector)
  {
    cout << i << " ";
  }
}