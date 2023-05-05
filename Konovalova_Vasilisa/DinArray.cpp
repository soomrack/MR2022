#include <iostream>

class Array_Exception : public std::exception
{
public:
	Array_Exception(const char* const& msg) : exception(msg)
	{}
};

Array_Exception NOINDEX("There is no such index\n");


template <typename T = double>
class Array {
protected:
	unsigned int size = 0;
	T* values = nullptr;

public:
	Array() = default;
	Array(unsigned int size, T value = 0., unsigned int reserve = 30);

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
};


template <typename T>
Array<T>::Array(unsigned int size, T value, unsigned int reserve) {
	this->size = size + reserve;
	values = new T[size + reserve];
	for (unsigned int idx = 0; idx < size + reserve; ++idx) {
		values[idx] = value;
	}
}
template <typename T>
Array<T>::Array(const Array& array) {
	values = new T[array.size];
	memcpy(values, array.values, size * sizeof(T));
}

template <typename T>
Array<T>::Array(Array&& array) noexcept {
	size = array.size;
	values = array.values;

	array.size = 0;
	array.values = nullptr;
}


template <typename T>
Array<T>::~Array() {
	delete[] values;
}


template <typename T>
T& Array<T> :: operator [](unsigned int idx) {
	if (idx >= size || idx < 0) throw NOINDEX;
	return values[idx];
}


template <typename T>
void Array<T>::shrink_head(unsigned int size) {
	if (this->size <= size) return;
	T* new_values = new T[size];
	for (unsigned int idx = 0; idx < size; ++idx) {
		new_values[idx] = values[this->size - size + idx];
	}
	delete[] values;
	values = new_values;
	this->size = size;
}


template <typename T>
void Array<T>::shrink_tail(unsigned int size) {
	if (this->size <= size) return;
	T* new_values = new T[size];
	for (unsigned int idx = 0; idx < size; ++idx) {
		new_values[idx] = values[idx];
	}
	delete[] values;
	values = new_values;
	this->size = size;
}

template <typename T>
void Array<T>::expand_head(unsigned int size) {
	if (this->size >= size) return;
	T* new_values = new T[size];
	unsigned int difference = size - this->size;
	for (unsigned int idx = 0; idx < difference; ++idx) {
		new_values[idx] = 0.;
	}
	for (unsigned int idx = difference; idx < size; ++idx) {
		new_values[idx] = values[idx-difference];
	}
	delete[] values;
	values = new_values;
	this->size = size;
}

template <typename T>
void Array<T>::expand_tail(unsigned int size) {
	if (this->size >= size) return;
	T* new_values = new T[size];
	for (unsigned int idx = 0; idx <= this->size; ++idx) {
		new_values[idx] = values[idx];
	}
	delete[] values;
	values = new_values;
	this->size = size;
}

template <typename T>
void Array<T>::push_head(T value) {
	expand_head(size + 1);
	values[0] = value;
}

template <typename T>
void Array<T>::push_tail(T value) {
	expand_tail(size + 1);
	values[size - 1] = value;
}

template <typename T>
void Array<T>::remove(unsigned int rem_idx) {
	if (rem_idx >= size || rem_idx < 0) throw NOINDEX;
	T* new_values = new T[size - 1];
	unsigned int offset = 0;
	for (unsigned int idx = 0; idx < this->size; ++idx) {
		if (idx == rem_idx) {
			offset = 1;
			continue;
		}
		new_values[idx - offset] = values[idx];
	}
	delete[] values;
	values = new_values;
	this->size = size - 1;
}

template <typename T>
void Array<T>::print_matrix() {
	std::cout << "Size: " << size << std::endl;
	for (unsigned int idx = 0; idx < size; ++idx) {
		std::cout << values[idx] << " ";
	}
	std::cout  << "\n\n";
}


int main() {
	Array<> A(5, 3.);
	A.print_matrix();

	try {
		A[9] = 5;
		A.print_matrix();
	}
	catch (const Array_Exception& e) {
		std::cerr << e.what() << std::endl;
	}

	try {
	A[2] = 5;
		A.print_matrix();
	}
	catch (const Array_Exception& e) {
		std::cerr << e.what() << std::endl;
	}

	A.push_tail(4.);
	A.print_matrix();
	A.push_head(7.1);
	A.print_matrix();

	try {
		A.remove(2);
		A.print_matrix();
	}
	catch (const Array_Exception& e) {
		std::cerr << e.what() << std::endl;
	}

	try {
		A.remove(9);
		A.print_matrix();
	}
	catch (const Array_Exception& e) {
		std::cerr << e.what() << std::endl;
	}

	A.shrink_head(4);
   A.print_matrix();
	return 0;
}
