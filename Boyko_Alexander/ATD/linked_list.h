#ifndef ATD_LINKED_LIST_H
#define ATD_LINKED_LIST_H

#include <iostream>

template<class T>
class ListMember{
public:
	T data;
	int* list_size = nullptr;
	ListMember* next = NULL;
	explicit ListMember(int* size = nullptr){ list_size = size;};
	~ListMember(){};
	ListMember(ListMember& other);
	ListMember(ListMember&& other) noexcept;
	ListMember<T>& operator=(const ListMember<T>& other);
	ListMember<T>& operator=(ListMember<T>&& other) noexcept;
	bool operator==(ListMember<T> other);
	bool operator!=(ListMember<T> other);
	void push_next(T new_member);
	void pop_next();
};

template<typename Type>
ListMember<Type> empty;

template<class Type>
class LinkedList{
private:
	ListMember<Type>* head;
	ListMember<Type>* tail;
	int list_size = 0;
public:
	LinkedList();
	~LinkedList(){};
	ListMember<Type>* operator[](int ind);
	int size() const;
	void push_head(Type new_member);
	void push_tail(Type new_member);

	void pop_front();
	void pop_back();

	void clear();
	ListMember<Type>* get_head();
	ListMember<Type>* get_tail();
};

template<class T>
ListMember<T> &ListMember<T>::operator=(const ListMember<T> &other) {
	data = other.data;
	if (other.next){
		next = &other.next;
	}
	return *this;
}

template<class T>
ListMember<T> &ListMember<T>::operator=(ListMember<T> &&other) noexcept {
	data = other.data;
	next = other.next;
	return *this;
}

template<class T>
ListMember<T>::ListMember(ListMember &other) {
	*this = other;
}

template<class T>
ListMember<T>::ListMember(ListMember &&other) noexcept {
	*this = other;
}

template<class T>
bool ListMember<T>::operator==(ListMember<T> other) {
	if(data != other.data){
		return false;
	}
	if(&next != &other.next){
		return false;
	}
	return true;
}


template<class T>
bool ListMember<T>::operator!=(ListMember<T> other) {
	return !(*this==other);
}

template<class T>
void ListMember<T>::push_next(T new_member) {
	ListMember<T>* new_next = new ListMember<T>(list_size);
	new_next->data = new_member;
	new_next->next = next;
	next = new_next;
	*list_size += 1;
}

template<class T>
void ListMember<T>::pop_next() {
	if(next){
		ListMember<T>* new_next = next->next;
		next->next = NULL;
		next = new_next;
		*list_size -= 1;
	}
}

template<class Type>
LinkedList<Type>::LinkedList() {
	list_size = 0;
	head = NULL;
	tail = NULL;
}

template<class Type>
void LinkedList<Type>::push_tail(Type new_member) {
	list_size += 1;
	if(list_size == 1){
		head = new ListMember<Type>(&list_size);
		head->data = new_member;
		tail = head;
	}
	else{
		ListMember<Type>* old_tail = tail;
		tail = new ListMember<Type>(&list_size);
		tail->data = new_member;
		old_tail->next = tail;
	}

}

template<class Type>
void LinkedList<Type>::push_head(Type new_member) {
	list_size += 1;

	if (list_size == 1) {
		head = new ListMember<Type>(&list_size);
		head->data = new_member;
		tail = head;
	} else {
		ListMember<Type> *old_head = head;
		head = new ListMember<Type>(&list_size);
		head->data = new_member;
		head->next = old_head;
	}

}


template<class Type>
ListMember<Type>* LinkedList<Type>::operator[](int ind) {
	ListMember<Type>* next_member = head;
	if(ind > list_size - 1){
		std::cout << "\nOut of bounds\n";
		return &empty<Type>;
	}

	for(int i = 1; i <= ind; i++){
		next_member = next_member->next;
	}
	return next_member;
}



template<class Type>
int LinkedList<Type>::size() const {
	return list_size;
}

template<class Type>
void LinkedList<Type>::pop_front() {
	if(list_size < 1){
		return;
	}
	if(list_size == 1){
		list_size = 0;
		head->next = NULL;
		head = NULL;
		tail = NULL;
		return;
	}
	ListMember<Type>* old_head = head;
	head = old_head->next;
	old_head->next = NULL;
	list_size -= 1;
}

template<class Type>
void LinkedList<Type>::pop_back() {
	if(list_size < 1){
		return;
	}
	if(list_size == 1){
		list_size = 0;
		head->next = NULL;
		head = NULL;
		tail = NULL;
		return;
	}
	ListMember<Type>* old_tail = tail;
	tail = head;
	while(tail->next != old_tail){
		tail = tail->next;
	}
	tail->next = NULL;
	list_size -= 1;
}

template<class Type>
void LinkedList<Type>::clear() {
	head = NULL;
	tail = NULL;
	list_size = 0;
}

template<class Type>
ListMember<Type> *LinkedList<Type>::get_head() {
	return head;
}

template<class Type>
ListMember<Type> *LinkedList<Type>::get_tail() {
	return tail;
}




#endif //ATD_LINKED_LIST_H
