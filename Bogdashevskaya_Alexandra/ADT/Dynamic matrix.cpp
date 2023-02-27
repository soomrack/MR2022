#include <iostream>

template <typename T = double>
class Dynamic_matrix {
protected:
	unsigned int size = 0;
	T* values = nullptr;

public:
	Dynamic_matrix() = default;
	Dynamic_matrix(unsigned int size, T = 0.);
	Dynamic_matrix(const Dynamic_matrix& matrix);
	Dynamic_matrix(Dynamic_matrix&& matrix) noexcept;
	
	~Dynamic_matrix();

	T& operator [](unsigned int idx);

	void shrink(unsigned int size);
	void expand_head(unsigned int size);
	void expand_tail(unsigned int size);

	void push_head(T value);
	void push_tail(T value);

	void remove(unsigned int rem_idx);

	void print_matrix();
};


template <typename T>
Dynamic_matrix<T>::Dynamic_matrix(unsigned int size, T value) {
	this->size = size;
	values = new T[size];
	for (unsigned int idx = 0; idx < size; ++idx) {
		values[idx] = value;
	}
}

template <typename T>
Dynamic_matrix<T>::Dynamic_matrix(const Dynamic_matrix& matrix) {
	values = new T[matrix.size];
	memcpy(values, matrix.values, size * sizeof(T));
}

template <typename T>
Dynamic_matrix<T>::Dynamic_matrix(Dynamic_matrix&& matrix) noexcept {
	size = matrix.size;
	values = matrix.values;

	matrix.size = 0;
	matrix.values = nullptr;
}

template <typename T>
Dynamic_matrix<T>::~Dynamic_matrix() {
	delete[] values;
}


template <typename T>
T& Dynamic_matrix<T> :: operator [](unsigned int idx) {
	return values[idx];
}


template <typename T>
void Dynamic_matrix<T>::shrink(unsigned int size) {
	if (this->size <= size) return;
	T* new_values(size);
	for (unsigned int idx = 0; idx <= size; ++idx) {
		new_values[idx] = values[idx];
	}
	delete[] values;
	values = new_values;
	this->size = size;
}

template <typename T>
void Dynamic_matrix<T>::expand_head(unsigned int size) {
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
void Dynamic_matrix<T>::expand_tail(unsigned int size) {
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
void Dynamic_matrix<T>::push_head(T value) {
	expand_head(size + 1);
	values[0] = value;
}

template <typename T>
void Dynamic_matrix<T>::push_tail(T value) {
	expand_tail(size + 1);
	values[size - 1] = value;
}

template <typename T>
void Dynamic_matrix<T>::remove(unsigned int rem_idx) {
	T* new_values = new T[size - 1];
	unsigned int offset = 0;
	for (unsigned int idx = 0; idx <= this->size; ++idx) {
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
void Dynamic_matrix<T>::print_matrix() {
	std::cout << "Size: " << size << std::endl;
	for (unsigned int idx = 0; idx < size; ++idx) {
		std::cout << values[idx] << " ";
	}
	std::cout  << "\n\n";
}


//int main() {
//	Dynamic_matrix<> A(5, 3.);
//	A.print_matrix();
//	A[2] = 5;
//	A.print_matrix();
//	A.push_tail(4.);
//	A.print_matrix();
//	A.push_head(7.1);
//	A.print_matrix();
//	A.remove(2);
//	A.print_matrix();
//	
//
//	return 0;
//}