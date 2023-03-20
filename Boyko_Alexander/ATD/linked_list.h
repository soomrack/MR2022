#ifndef ATD_LINKED_LIST_H
#define ATD_LINKED_LIST_H

#include <iostream>

template<class T>
class ListMember{
private:
	T data;
	ListMember* next;
public:
	ListMember();
	~ListMember();
	ListMember(ListMember& other);
	ListMember(ListMember&& other) noexcept;
	ListMember<T>& operator=(const ListMember<T>& other);
	ListMember<T>& operator=(ListMember<T>&& other) noexcept;
	bool operator==(ListMember<T> other);
	bool operator!=(ListMember<T> other);
	void set_data(T new_data);
	T get_data();
	ListMember* get_next();
	void set_next(ListMember* next_member);
};

template<typename Type>
ListMember<Type> empty;

template<class Type>
class LinkList{
private:
	ListMember<Type>* head;
	ListMember<Type>* tail;
	ListMember<Type>* real_tail;
	int data_size = 10;
	int list_size = 0;
	void resize(int new_size);
public:
	LinkList();
	~LinkList();
	//LinkList(LinkList& other);
	//LinkList(LinkList&& other) noexcept;
	ListMember<Type>* operator[](int ind);
	//LinkList<Type>& operator=(const LinkList<Type>& other);
	//LinkList<Type>& operator=(LinkList<Type>&& other) noexcept;
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
ListMember<T>::ListMember() {
	data = 0;
	next = NULL;
}

template<class T>
ListMember<T>::~ListMember() {
	//data = 0;
	//next = &empty<T>;
}

template<class T>
void ListMember<T>::set_data(T new_data) {
	data = new_data;
}

template<class T>
T ListMember<T>::get_data() {
	return data;
}

template<class T>
ListMember<T>* ListMember<T>::get_next() {
	return next;
}

template<class T>
void ListMember<T>::set_next(ListMember* next_member) {
	next = next_member;
}

template<class T>
ListMember<T> &ListMember<T>::operator=(const ListMember<T> &other) {
	data = other.data;
	if (other.next){
		next = new ListMember<T>();
		next->data = other.next->data;
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

template<class Type>
LinkList<Type>::LinkList() {
	data_size = 10;
	list_size = 0;
	head = new ListMember<Type>();
	head->set_data(0);
	tail = head;
	real_tail = head;
	for(int i = 0; i < data_size - 1; i++){
		ListMember<Type>* old_tail = real_tail;
		real_tail = new ListMember<Type>();
		real_tail->set_data(i+1);
		old_tail->set_next(real_tail);
	}
}

template<class Type>
LinkList<Type>::~LinkList() {

}

template<class Type>
void LinkList<Type>::push_tail(Type new_member) {
	list_size += 1;
	if(list_size >= data_size){
		resize(list_size+10);
	}
	if(list_size == 1){
		tail->set_data(new_member);
	}
	else{
		tail->get_next()->set_data(new_member);
		tail = tail->get_next();
	}

}

template<class Type>
void LinkList<Type>::push_head(Type new_member) {
	list_size += 1;
	if(list_size >= data_size){
		resize(list_size+10);
	}
	if(list_size == 1){
		head->set_data(new_member);
	}
	else{
		ListMember<Type>* old_head = head;
		head = tail->get_next();
		head->set_data(new_member);
		tail->set_next(head->get_next());
		head->set_next(old_head);
	}

}

template<class Type>
void LinkList<Type>::resize(int new_size) {
	for(int i = 0; i < new_size - data_size ; i++){
		ListMember<Type>* old_tail = real_tail;
		real_tail = new ListMember<Type>();
		real_tail->set_data(data_size+i);
		old_tail->set_next(real_tail);
	}
	data_size = new_size;
}


template<class Type>
ListMember<Type>* LinkList<Type>::operator[](int ind) {
	ListMember<Type>* next_member = head;
	if(ind > data_size - 1){
		std::cout << "\nOut of bounds\n";
		next_member = &empty<Type>;
		return next_member;
	}

	for(int i = 1; i <= ind; i++){
		next_member = next_member->get_next();
	}
	return next_member;
}



template<class Type>
int LinkList<Type>::size() const {
	return list_size;
}

template<class Type>
void LinkList<Type>::pop_front() {
	if(list_size < 1){
		return;
	}
	if(list_size == 1){
		list_size = 0;
		return;
	}
	ListMember<Type>* old_head = head;
	head = old_head->get_next();
	old_head->set_next(NULL);
	old_head->set_data(0);
	ListMember<Type>* old_tail = real_tail;
	real_tail = old_head;
	old_tail->set_next(real_tail);
	list_size -= 1;
}

template<class Type>
void LinkList<Type>::pop_back() {
	ListMember<Type>* old_tail = tail;
	tail = head;
	while(tail->get_next() != old_tail){
		tail = tail->get_next();
	}
	list_size -= 1;
}

template<class Type>
void LinkList<Type>::clear() {
	tail = head;
	list_size = 0;
	data_size = 10;
	resize(data_size);
}

template<class Type>
ListMember<Type> *LinkList<Type>::get_head() {
	return head;
}

template<class Type>
ListMember<Type> *LinkList<Type>::get_tail() {
	return tail;
}


#endif //ATD_LINKED_LIST_H
