#include <iostream>

class Stack_Exception : public std::exception
{
public:
	Stack_Exception(const char* const& msg) : exception(msg)
	{}
};

Stack_Exception ISFULL("Stack is full. New items cannot be included\n");
Stack_Exception ISEMPTY("Stack is empty. Items cannot be excluded\n");

template <typename T = double>
class Stack {
protected:
	unsigned int size;
	T* values;
	int top_idx;


public:
	Stack(unsigned int size);
	//Stack(const Stack& stack);
	//Stack(Stack&& stack) noexcept;

	~Stack();

	bool is_empty();
	bool is_full();

	void push(T value);
	void pop();

	void print_stack();
};


template <typename T>
Stack<T>::Stack(unsigned int size) {
	this->size = size;
	values = new T[size];
	top_idx = -1;
}

//template <typename T>
//Stack<T>::Stack(const Stack& stack) {
//	values = new T[stack.size];
//	memcpy(values, stack.values, size * sizeof(T));
//	top_idx = stack.top_idx;
//}
//
//template <typename T>
//Stack<T>::Stack(Stack&& stack) noexcept {
//	size = stack.size;
//	values = stack.values;
//	top_idx = stack.top_idx;
//
//	stack.size = 0;
//	stack.top_idx = -1;
//	stack.values = nullptr;
//}

template <typename T>
Stack<T>::~Stack() {
	delete[] values;
}


template <typename T>
bool Stack<T>::is_empty() {
	return top_idx == -1 ? 1 : 0;
}

template <typename T>
bool Stack<T>::is_full() {
	return top_idx == size - 1 ? 1 : 0;
}


template <typename T>
void Stack<T>::push(T value) {
	if (is_full()) throw ISFULL;
	++top_idx;
	values[top_idx] = value;
}

template <typename T>
void Stack<T>::pop() {
	if (is_empty()) throw ISEMPTY;
	values[top_idx] = NULL;
	--top_idx;
}

template <typename T>
void Stack<T>::print_stack() {
	std::cout << "Place left: " << size - top_idx - 1 << std::endl;
	if (is_empty()) {
		std::cout << "Stack is empty" << std::endl;
	}
	else {
		for (unsigned int idx = 0; idx <= top_idx; ++idx) {
			std::cout << values[idx] << " ";
		}
		std::cout << "\n\n";
	}
}


//int main() {
//	Stack<> A(2);
//	A.print_stack();
//
//	try {
//		A.pop();
//		A.print_stack();
//	}
//	catch (const Stack_Exception& e) {
//		std::cerr << e.what() << std::endl;
//	}
//
//	try {
//		A.push(5);
//		A.print_stack();
//	}
//	catch (const Stack_Exception& e) {
//		std::cerr << e.what() << std::endl;
//	}
//
//	try {
//		A.push(5);
//		A.print_stack();
//	}
//	catch (const Stack_Exception& e) {
//		std::cerr << e.what() << std::endl;
//	}
//
//	try {
//		A.pop();
//		A.print_stack();
//	}
//	catch (const Stack_Exception& e) {
//		std::cerr << e.what() << std::endl;
//	}
//
//	try {
//		A.push(5);
//		A.print_stack();
//	}
//	catch (const Stack_Exception& e) {
//		std::cerr << e.what() << std::endl;
//	}
//
//	try {
//		A.push(5);
//		A.print_stack();
//	}
//	catch (const Stack_Exception& e) {
//		std::cerr << e.what() << std::endl;
//	}
//
//	return 0;
//}