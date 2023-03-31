#include <iostream>

class Queue_Exception : public std::exception
{
public:
	Queue_Exception(const char* const& msg) : exception(msg)
	{}
};

Queue_Exception ISFULL("Queue is full. New items cannot be included\n");
Queue_Exception ISEMPTY("Queue is empty. Items cannot be excluded\n");

template <typename T = double>
class Queue {
protected:
	unsigned int size;
	T* values;
	int head_idx;
	int tail_idx;


public:
	Queue(unsigned int size);
	//Queue(const Queue& stack);
	//Queue(Queue&& stack) noexcept;

	~Queue();

	bool is_empty();
	bool is_full();

	unsigned int size_engaged();  // возвращает количество занятых ячеек

	void push(T value);
	void pop();

	void print_queue();
};


template <typename T>
Queue<T>::Queue(unsigned int size) {
	this->size = size;
	values = new T[size];
	head_idx = -1;
	tail_idx = -1;
}

//template <typename T>
//Queue<T>::Queue(const Queue& queue) {
//	values = new T[queue.size];
//	memcpy(values, queue.values, size * sizeof(T));
//	head_idx = queue.head_idx;
//	tail_idx = queue.tail_idx;
//}
//
//template <typename T>
//Queue<T>::Queue(Queue&& queue) noexcept {
//	size = queue.size;
//	values = queue.values;
//	head_idx = queue.head_idx;
//	tail_idx = queue.tail_idx;
//
//	queue.size = 0;
//	queue.head_idx = -1;
//	queue.tail_idx = -1;
//	queue.values = nullptr;
//}

template <typename T>
Queue<T>::~Queue() {
	delete[] values;
}


template <typename T>
bool Queue<T>::is_empty() {
	return head_idx == -1 && tail_idx == -1 ? 1 : 0;
}

template <typename T>
bool Queue<T>::is_full() {
	return size_engaged() == size ? 1 : 0;
}


template <typename T>
unsigned int Queue<T>::size_engaged() {
	return head_idx > tail_idx ? head_idx - tail_idx + 1 : tail_idx - head_idx + 1;
}


template <typename T>
void Queue<T>::push(T value) {
	if (is_full()) throw ISFULL;

	if (is_empty()) {
		head_idx = 0;
		tail_idx = 0;
	}
	else {
		if (head_idx == size - 1) head_idx = 0;
		else ++head_idx;
	}

	values[head_idx] = value;
}

template <typename T>
void Queue<T>::pop() {
	if (is_empty()) throw ISEMPTY;

	values[tail_idx] = NULL;

	if (tail_idx == size - 1) tail_idx = 0;
	else ++tail_idx;
}

template <typename T>
void Queue<T>::print_queue() {
	std::cout << "Place left: " << size - size_engaged() + 1 << std::endl;
	if (is_empty()) {
		std::cout << "Queue is empty" << std::endl;
		return;
	}
	for (unsigned int idx = tail_idx; idx <= head_idx; ++idx) {
		std::cout << values[idx] << " ";
		if (tail_idx > head_idx && idx == size - 1) idx = -1;
	}
	std::cout << "\n\n";
}


//int main() {
//	Queue<> A(2);
//	A.print_queue();
//
//	try {
//		A.pop();
//		A.print_queue();
//	}
//	catch (const Queue_Exception& e) {
//		std::cerr << e.what() << std::endl;
//	}
//
//	try {
//		A.push(5);
//		A.print_queue();
//	}
//	catch (const Queue_Exception& e) {
//		std::cerr << e.what() << std::endl;
//	}
//
//	try {
//		A.push(5);
//		A.print_queue();
//	}
//	catch (const Queue_Exception& e) {
//		std::cerr << e.what() << std::endl;
//	}
//
//	try {
//		A.pop();
//		A.print_queue();
//	}
//	catch (const Queue_Exception& e) {
//		std::cerr << e.what() << std::endl;
//	}
//
//	try {
//		A.push(5);
//		A.print_queue();
//	}
//	catch (const Queue_Exception& e) {
//		std::cerr << e.what() << std::endl;
//	}
//
//	try {
//		A.push(5);
//		A.print_queue();
//	}
//	catch (const Queue_Exception& e) {
//		std::cerr << e.what() << std::endl;
//	}
//
//	return 0;
//}