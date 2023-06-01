#include <iostream>

class Array_Exception : public std::runtime_error
{
public:
	Array_Exception(const char* const& msg) : runtime_error(msg)
	{}
};

Array_Exception NOINDEX("There is no such index\n");

template <typename T = double>
class Array {
protected:
	unsigned int extra;
	T* values;
	int begin;
	int end;

public:
	Array();
	Array(unsigned int size, T value = 0, unsigned int extra = 5);
	//Array(const Array& array);
	//Array(Array&& array) noexcept;
	
	~Array();

	T& operator [](unsigned int idx);

	void shrink_head(unsigned int size);
	void shrink_tail(unsigned int size);
	void expand_head(unsigned int size);
	void expand_tail(unsigned int size);

	void push_head(T value);
	void push_tail(T value);

	void remove(unsigned int rem_idx);

	void print_matrix();

	unsigned int size;
	unsigned int capacity;
};

template<typename T>
Array<T>::Array(): Array(0) {}

template <typename T>
Array<T>::Array(unsigned int size, T value, unsigned int extra) {
	this->capacity = extra + size + extra;
	this->size = size;
	this->extra = extra;
	this->values = new T[this->capacity];
	this->begin = extra;
	this->end = extra + size;
	for (unsigned int idx = 0; idx < size; ++idx) {
		this->values[begin + idx] = value;
	}

	if (size == 0) {
		this->begin = extra + 1;
		this->end = extra + 1;
	}
}

//template <typename T>
//Array<T>::Array(const Array& array) {
//	values = new T[array.size];
//	memcpy(values, array.values, size * sizeof(T));
//}
//
//template <typename T>
//Array<T>::Array(Array&& array) noexcept {
//	size = array.size;
//	values = array.values;
//
//	array.size = 0;
//	array.values = nullptr;
//}

template <typename T>
Array<T>::~Array() {
	delete[] values;
}


template <typename T>
T& Array<T> :: operator [](unsigned int idx) {
	if (idx >= size || idx < 0) throw NOINDEX;
	return values[begin + idx];
}


template <typename T>
void Array<T>::shrink_head(unsigned int capacity) {
	if (this->capacity <= capacity) return;
	T* new_values = new T[capacity];

	int new_size = std::min(size, capacity);
	for (unsigned int idx = 0; idx < new_size; ++idx) {
		new_values[idx] = values[begin + idx];
	}
	delete[] values;

	values = new_values;
	if (new_size == 0) {
		begin = 1;
		end = 1;
	} else {
		begin = 0;
		end = new_size;
	}
	this->size = new_size;
	this->capacity = capacity;
}


template <typename T>
void Array<T>::shrink_tail(unsigned int capacity) {
	if (this->capacity <= capacity) return;
	T* new_values = new T[capacity];

	int new_size = std::min(size, capacity);
	for (unsigned int idx = 0; idx < new_size; ++idx) {
		new_values[capacity - 1 - idx] = values[end - 1 - idx];
	}
	delete[] values;

	values = new_values;
	end = capacity;
	begin = end - new_size;	
	this->size = new_size;
	this->capacity = capacity;
}

template <typename T>
void Array<T>::expand_head(unsigned int capacity) {
	if (this->capacity >= capacity) return;
	T* new_values = new T[capacity];

	unsigned int difference = capacity - this->capacity;
	// for (unsigned int idx = 0; idx < difference; ++idx) {
	// 	new_values[idx] = 0.;
	// }

	for (unsigned int idx = 0; idx < size; ++idx) {
		new_values[begin + difference + idx] = values[begin + idx];
	}
	delete[] values;

	values = new_values;
	end = difference + end;
	begin = difference + begin;
	this->capacity = capacity;
}

template <typename T>
void Array<T>::expand_tail(unsigned int capacity) {
	if (this->capacity >= capacity) return;
	T* new_values = new T[capacity];

	for (unsigned int idx = 0; idx < size; ++idx) {
		new_values[begin + idx] = values[begin + idx];
	}
	delete[] values;

	values = new_values;
	this->capacity = capacity;
}

template <typename T>
void Array<T>::push_head(T value) {
	if (begin == 0) {
		expand_head(capacity + extra);
	}

	values[--begin] = value;
	size++;
}

template <typename T>
void Array<T>::push_tail(T value) {
	if (end == capacity) {
		expand_tail(capacity + extra);
	}
	values[end++] = value;
	size++;
}

template <typename T>
void Array<T>::remove(unsigned int rem_idx) {
	if (rem_idx >= size || rem_idx < 0) throw NOINDEX;
	for (unsigned int idx = rem_idx; idx < size - 1; idx++) {
		values[begin + idx] = values[begin + idx + 1];
	}

	size--;
	if (size == 0) {
		begin = size / 2 + 1;
		end = size / 2 + 1;
	} else {
		end--;
	}

	return;
}

template <typename T>
void Array<T>::print_matrix() {
	std::cout << "Size: " << size << std::endl;
	for (unsigned int idx = 0; idx < size; ++idx) {
		std::cout << values[begin + idx] << " ";
	}
	std::cout  << "\n\n";
}
/*
signed main() {
	Array<int> arr(2, 1, 1);
	arr.push_head(1);
	arr.push_head(2);
	arr.push_tail(3);
	arr.print_matrix();
	arr.remove(1);
	arr.print_matrix();
	arr.remove(0);
	arr.remove(0);
	arr.print_matrix();
	arr.remove(1);
	arr.remove(0);
	arr.print_matrix();

	arr.shrink_head(1);
	arr.push_tail(1);
	arr.push_tail(2);
	arr.push_tail(3);
	arr.print_matrix();
}
*/
