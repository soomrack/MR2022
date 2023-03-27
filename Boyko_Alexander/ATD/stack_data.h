#ifndef ATD_STACK_DATA_H
#define ATD_STACK_DATA_H

#include "linked_list.h"

typedef char Type;
class Stack{
public:
	ListMember<Type>* top = nullptr;
	LinkedList<Type> StackList;
	void push(Type new_item);
	void pop();
};

void Stack::push(Type new_item) {
	StackList.push_head(new_item);
	top = StackList.get_head();
}

void Stack::pop() {
	StackList.pop_front();
	top = StackList.get_head();
}


#endif //ATD_STACK_DATA_H
