#ifndef ATD_LINKED_LIST_H
#define ATD_LINKED_LIST_H

#include <iostream>

template<class T>
class Node{
public:
	T data;
	Node* next;
	void push_next(T new_data);
	T pop_next();
	explicit Node(T new_data){data = new_data; next = NULL;}
};


template<typename Type>
Node<Type> empty(0);

template<class Type>
class LinkedList{
private:
	Node<Type>* head;
public:
	LinkedList();
	~LinkedList();
	int size() const;
	void push_head(Type new_data);
	void push_tail(Type new_data);
	Type pop_head();
	Type pop_tail();
	Node<Type>* get_head();
	Node<Type>* get_tail();
	Node<Type>* get_in_order(unsigned int ind);
	Node<Type>* find(Type find_data);
};


template<class T>
void Node<T>::push_next(T new_data) {
	auto new_next = new Node<T>(new_data);
	new_next->next = next;
	next = new_next;
}

template<class T>
T Node<T>::pop_next() {
	if(next){
		T pop_data = next->data;
		Node<T>* new_next = next->next;
		delete next;
		next = new_next;
		return pop_data;
	}
	else{
		return NULL;
	}
}


template<class Type>
LinkedList<Type>::LinkedList() {
	head = NULL;
}

template<class Type>
LinkedList<Type>::~LinkedList() {
	auto iter_member = head;
	while (iter_member != NULL){
		auto next_iter = iter_member->next;
		delete iter_member;
		iter_member = next_iter;
	}
}


template<class Type>
void LinkedList<Type>::push_head(Type new_data) {
	Node<Type> *old_head = head;
	head = new Node<Type>(new_data);
	head->next = old_head;
}

template<class Type>
void LinkedList<Type>::push_tail(Type new_data) {
	auto tail = get_tail();
	if(tail == NULL){
		head = new Node<Type>(new_data);
		return;
	}
	auto new_tail = new Node<Type>(new_data);
	tail->next = new_tail;
}


template<class Type>
int LinkedList<Type>::size() const {
	int list_size = 0;
	Node<Type>* iter_member = head;
	while (iter_member != NULL){
		list_size += 1;
		iter_member = iter_member->next;
	}
	return list_size;
}


template<class Type>
Type LinkedList<Type>::pop_head() {
	if(head == NULL){
		return NULL;
	}
	Type pop_data = head->data;
	Node<Type>* old_head = head;
	head = old_head->next;
	delete old_head;
	return pop_data;
}


template<class Type>
Type LinkedList<Type>::pop_tail() {
	auto new_tail = head;
	auto old_tail = get_tail();
	if(new_tail == NULL) {
		return NULL;
	}
	if(new_tail == old_tail){
		Type pop_data = old_tail->data;
		delete old_tail;
		head = NULL;
		return pop_data;
	}
	while (new_tail->next != old_tail) {
		new_tail = new_tail->next;
	}
	return new_tail->pop_next();
}


template<class Type>
Node<Type> *LinkedList<Type>::get_head() {
	return head;
}


template<class Type>
Node<Type> *LinkedList<Type>::get_tail() {
	Node<Type>* tail = head;
	if(tail != NULL) {
		while (tail->next != NULL) {
			tail = tail->next;
		}
	}
	return tail;
}

template<class Type>
Node<Type> *LinkedList<Type>::get_in_order(unsigned int ind) {
	auto need_node = head;
	for(unsigned int i = 0; i < ind; i++){
		if(need_node != NULL){
			need_node = need_node->next;
		}
		else{
			std::cout << "Out of bounds!";
			need_node = &empty<Type>;
			return need_node;
		}
	}
	return need_node;
}

template<class Type>
Node<Type>* LinkedList<Type>::find(Type find_data) {
	Node<Type>* tail = head;
	if(tail != nullptr) {
		if(tail->data == find_data){
			return tail;
		}
		tail = tail->next;
	}
	return nullptr;
}


#endif //ATD_LINKED_LIST_H
