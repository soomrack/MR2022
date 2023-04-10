#include "dinamic_array.h"

#include <iostream>


template<class Type>
int DinArray<Type>::size() const{
	return arr_size;
}

template<class Type>
void DinArray<Type>::append(Type new_data) {
	arr_size += 1;
	if(arr_size >= data_size){
		resize(arr_size+10);
	}
	data[arr_size-1] = new_data;
}

template<class Type>
void DinArray<Type>::append_at(Type new_data, int ind) {
	arr_size += 1;
	if(arr_size >= data_size){
		resize(arr_size+10);
	}
	memcpy(data + ind + 1, data + ind, (arr_size - ind - 1)  * sizeof(Type));
	data[ind] = new_data;
}

template<class Type>
void DinArray<Type>::pop_front() {
	arr_size -= 1;
	memcpy(data, data + 1, arr_size  * sizeof(Type));
}

template<class Type>
void DinArray<Type>::pop_back() {
	arr_size -= 1;
}

template<class Type>
void DinArray<Type>::pop_at(int ind) {
	arr_size -= 1;
	memcpy(data + ind, data + ind + 1, (arr_size-ind+1) * sizeof(Type));
}

template<class Type>
void DinArray<Type>::clear() {
	resize(10);
	arr_size = 0;
}

template<class Type>
void DinArray<Type>::resize(int new_size) {
	Type* mid_data;
	mid_data = new Type[arr_size];
	memcpy(mid_data,data,arr_size * sizeof(Type));
	delete[] data;
	data = new Type[new_size];
	memcpy(data,mid_data,arr_size * sizeof(Type));
	data_size = new_size;
}

template<class Type>
DinArray<Type>::DinArray() {
	data = new Type[data_size];
	arr_size = 0;
}

template<class Type>
DinArray<Type>::~DinArray() {
	delete[] data;
}

template<class Type>
Type DinArray<Type>::operator[](int ind) {
	if(ind > data_size - 1){
		std::cout << "\nOut of bounds\n";
		return 0;
	}
	return data[ind];
}

// copy constructor
template<class Type>
DinArray<Type>::DinArray(DinArray& other) {
	*this = other;
}

// move constructor
template<class Type>
DinArray<Type>::DinArray(DinArray &&other) noexcept{
	*this = other;
}

template<class Type>
DinArray<Type>& DinArray<Type>::operator=(const DinArray<Type> &other) {
	if(*this == other){
		return *this;
	}
	resize(other.size());
	arr_size = other.arr_size;
	memcpy(data, other.data, arr_size * sizeof (Type));
	return *this;
}

template<class Type>
DinArray<Type> &DinArray<Type>::operator=(DinArray<Type> &&other) noexcept{
	delete[] data;
	arr_size = other.size();
	data = other.data;
	return *this;
}

template<class Type>
bool DinArray<Type>::operator==(const DinArray<Type> &other) {
	if(arr_size != other.arr_size){
		return false;
	}
	for(int ind = 0; ind < arr_size; ind++){
		if( data[ind] != other.data[ind]){
			return false;
		}
	}
	return true;
}

template<class Type>
bool DinArray<Type>::operator!=(const DinArray<Type> &other) {
	return !(*this == other);
}

template<class Type>
void DinArray<Type>::append(DinArray<Type> &new_datas) {
	int new_size = arr_size + new_datas.size();
	int old_size = arr_size;
	arr_size = new_size;
	resize(new_size+10);
	memcpy(data + old_size,new_datas.data,new_datas.size() * sizeof(Type));
}

template<class Type>
void DinArray<Type>::append_at(DinArray<Type> &new_datas, int ind) {
	int new_size = arr_size + new_datas.size();
	int old_size = arr_size;
	resize(new_size+10);
	arr_size = new_size;
	memcpy(data + ind + new_datas.size(), data + ind, (old_size - ind) * sizeof(Type));
	memcpy(data + ind,new_datas.data,new_datas.size() * sizeof(Type));
}






