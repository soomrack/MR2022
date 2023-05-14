#ifndef ATD_STACK_DATA_H
#define ATD_STACK_DATA_H

#include "linked_list.h"

typedef char Type;
class Stack{
public:
	Node<Type>* top = nullptr;
	LinkedList<Type> StackList;
	void push(Type new_item);
	Type pop();
	int size();
	Node<Type>* get(unsigned int ind);
};

void Stack::push(Type new_item) {
	StackList.push_tail(new_item);
	top = StackList.get_tail();
}

Type Stack::pop() {
	Type pop_data = StackList.pop_tail();
	top = StackList.get_tail();
	return  pop_data;
}

int Stack::size() {
	return StackList.size();
}

Node<Type>* Stack::get(unsigned int ind) {
	return StackList.get_in_order(ind);
}


#endif //ATD_STACK_DATA_H
