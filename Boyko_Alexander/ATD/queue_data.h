#ifndef ATD_QUEUE_DATA_H
#define ATD_QUEUE_DATA_H

#include "linked_list.h"

typedef char Type;
class Queue{
public:
	ListMember<Type>* first = nullptr;
	ListMember<Type>* last = nullptr;
	LinkedList<Type> StackList;
	void push(Type new_item);
	void pop();
};

void Queue::push(Type new_item) {
	StackList.push_tail(new_item);
	last = StackList.get_tail();
}

void Queue::pop() {
	StackList.pop_front();
	first = StackList.get_head();
}

#endif //ATD_QUEUE_DATA_H
