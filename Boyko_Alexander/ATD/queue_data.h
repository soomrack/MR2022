#ifndef ATD_QUEUE_DATA_H
#define ATD_QUEUE_DATA_H

#include "linked_list.h"

typedef char Type;
class Queue{
public:
	Node<Type>* head = nullptr;
	Node<Type>* tail = nullptr;
	LinkedList<Type> QueueList;
	void push(Type new_item);
	Type pop();
	int size();
	Node<Type>* get(unsigned int ind);
};

void Queue::push(Type new_item) {
	QueueList.push_tail(new_item);
	tail = QueueList.get_tail();
}

Type Queue::pop() {
	Type data = QueueList.pop_head();
	head = QueueList.get_head();
	return data;
}

int Queue::size() {
	return QueueList.size();
}

Node<Type> *Queue::get(unsigned int ind) {
	return QueueList.get_in_order(ind);
}

#endif //ATD_QUEUE_DATA_H
