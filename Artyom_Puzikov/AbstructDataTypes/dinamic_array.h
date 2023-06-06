#ifndef ABSTRUCTDATATYPES_DINAMIC_ARRAY_H
#define ABSTRUCTDATATYPES_DINAMIC_ARRAY_H

template<class Type>
class Vector
{
private:
  Type *data;
  int capacity = 10;
  int arr_size = 0;
public:

  Vector()
  {
    data = new Type[capacity];
    arr_size = 0;
  }

  ~Vector()
  {
    delete[] data;
  }

  Type operator[](int index)
  {
    if (index >= arr_size)
    {
      std::cerr << "\nOut of bounds\n";
      return 1;
    }
    return data[index];
  }

  int size() const
  {
    return arr_size;
  }

  void append(Type new_data)
  {
    arr_size++;
    if (arr_size >= capacity)
    {
      resize(capacity * 2);
    }
    data[arr_size - 1] = new_data;
  }

  void pop_at(int index)
  {
    if (index < 0 || index >= arr_size)
    {
      std::cerr << "\n";
      return;
    }
    arr_size--;
  }

  void resize(int new_size)
  {
    capacity = new_size;
    Type *tmp = new Type[capacity];
    for (int i = 0; i < arr_size; ++i)
    {
      tmp[i] = data[i];
    }
    delete []data;
    data = tmp;
  }
};


#endif
