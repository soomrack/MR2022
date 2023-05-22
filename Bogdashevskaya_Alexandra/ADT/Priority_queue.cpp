#include <iostream>

typedef double T;

class PriorityQueue_Exception : public std::exception
{
public:
	PriorityQueue_Exception(const char* const& msg) : exception(msg)
	{}
};

PriorityQueue_Exception ISFULL("PriorityQueue is full. New items cannot be included\n");
PriorityQueue_Exception ISEMPTY("PriorityQueue is empty. Items cannot be excluded\n");


class QueueNode {
protected:
	T value;
	int priority;
	QueueNode* next;
	QueueNode* prev;

public:
	QueueNode(T value, int priority = 0);
	QueueNode(const QueueNode& node);

	~QueueNode();

	friend class PriorityQueue;
};


class PriorityQueue {
protected:
	unsigned int size;
	unsigned int engaged_size;
	QueueNode* head;
	QueueNode* tail;


public:
	PriorityQueue(unsigned int size);

	~PriorityQueue();

	bool is_empty();
	bool is_full();

	void push(T value, int priority = 0);
	void pop();

	void print_queue();
};


QueueNode::QueueNode(T value, int priority) {
	this->value = value;
	this->priority = priority;
	next = nullptr;
	prev = nullptr;
}

QueueNode::QueueNode(const QueueNode& node) {
	this->value = node.value;
	this->priority = node.priority;
	this->next = node.next;
	this->prev = node.prev;
}

QueueNode::~QueueNode() {
	prev = nullptr;
	next = nullptr;
}


PriorityQueue::PriorityQueue(unsigned int size) {
	this->size = size;
	this->engaged_size = 0;
	this->head = nullptr;
	this->tail = nullptr;
}


PriorityQueue::~PriorityQueue() {
	head = nullptr;
	tail = nullptr;
}



bool PriorityQueue::is_empty() {
	return engaged_size == 0;
}


bool PriorityQueue::is_full() {
	return engaged_size == size;
}


void PriorityQueue::push(T value, int priority) {
	if (is_full()) throw ISFULL;

	QueueNode* new_node = new QueueNode(value, priority);
	++engaged_size;

	if (head == nullptr) {
		head = new_node;
		tail = new_node;
		return;
	}
	if (tail->priority >= new_node->priority) {
		new_node->prev = tail;
		tail->next = new_node;
		tail = new_node;
		return;
	}

	QueueNode* temp = tail;


	while (temp->priority < new_node->priority)
	{
		if (temp == head) {
			head->prev = new_node;
			new_node->next = head;
			head = new_node;
			return;
		}
		temp = temp->prev;

	}
	new_node->prev = temp;
	new_node->next = temp->next;
	temp->next->prev = new_node;
	temp->next = new_node;
}


void PriorityQueue::pop() {
	if (is_empty()) throw ISEMPTY;

	head = head->next;
}


void PriorityQueue::print_queue() {
	QueueNode* temp = head;
	while (temp != nullptr) {
		std::cout << temp->value << " ";
		temp = temp->next;
	}
	std::cout << "\n\n";
}


//int main() {
//	PriorityQueue A(5);
//
//	try {
//		A.pop();
//		A.print_queue();
//	}
//	catch (const PriorityQueue_Exception& e) {
//		std::cerr << e.what() << std::endl;
//	}
//
//	try {
//		A.push(1);
//		A.print_queue();
//	}
//	catch (const PriorityQueue_Exception& e) {
//		std::cerr << e.what() << std::endl;
//	}
//
//	try {
//		A.push(2, 10);
//		A.print_queue();
//	}
//	catch (const PriorityQueue_Exception& e) {
//		std::cerr << e.what() << std::endl;
//	}
//
//	try {
//		A.push(3);
//		A.print_queue();
//	}
//	catch (const PriorityQueue_Exception& e) {
//		std::cerr << e.what() << std::endl;
//	}
//
//	try {
//		A.push(4, 5);
//		A.print_queue();
//	}
//	catch (const PriorityQueue_Exception& e) {
//		std::cerr << e.what() << std::endl;
//	}
//
//	try {
//		A.push(5, 5);
//		A.print_queue();
//	}
//	catch (const PriorityQueue_Exception& e) {
//		std::cerr << e.what() << std::endl;
//	}
//
//	try {
//		A.pop();
//		A.print_queue();
//	}
//	catch (const PriorityQueue_Exception& e) {
//		std::cerr << e.what() << std::endl;
//	}
//
//	return 0;
//}