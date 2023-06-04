#ifndef DINARRAY_LIBRARY_H
#define DINARRAY_LIBRARY_H

template<class Type>
class DinArray{
private:
	Type* data;
	int data_size = 10;
	int arr_size = 0;
	void resize(int new_size);
public:
	DinArray();
	~DinArray();
	DinArray(DinArray& other);
	DinArray(DinArray&& other) noexcept;
	Type operator[](int ind);
	DinArray<Type>& operator=(const DinArray<Type>& other);
	DinArray<Type>& operator=(DinArray<Type>&& other) noexcept;
	bool operator==(const DinArray<Type>& other);
	bool operator!=(const DinArray<Type>& other);
	int size() const;
	void append(Type new_data);
	void append(DinArray<Type>& new_datas);
	void append_at(Type new_data, int ind);
	void append_at(DinArray<Type>& new_datas, int ind);
	void pop_front();
	void pop_back();
	void pop_at(int ind);
	void clear();
	int find(Type find_data);
};


#endif //DINARRAY_LIBRARY_H
