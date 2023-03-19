#ifndef ATD_LINKED_LIST_H
#define ATD_LINKED_LIST_H

#include <iostream>

template<class Type>
class LinkList{
private:

	class ListMember{
	private:
		Type* data;
		ListMember* next;
	public:
		ListMember();
		~ListMember();
		void set_data(Type new_data);
		Type get_data();
		Type* get_next();
		void set_next(ListMember next_member);
	};
	ListMember empty;
	ListMember* list;
	Type* head = 0;
	int data_size = 10;
	int arr_size = 0;
	void set_head(Type* obj);
	void resize(int new_size);
public:
	LinkList();
	~LinkList();
	LinkList(LinkList& other);
	LinkList(LinkList&& other) noexcept;
	ListMember operator[](int ind);
	LinkList<Type>& operator=(const LinkList<Type>& other);
	LinkList<Type>& operator=(LinkList<Type>&& other) noexcept;
	int size() const;
	void push_head(Type new_member);
	void push_tail(Type new_member);
	void pop_front();
	void pop_back();
	void clear();
	Type* next();
	Type* get_head();
};

template<class Type>
LinkList<Type>::ListMember::ListMember() {
	data = new Type;
	next = new ListMember;
}

template<class Type>
LinkList<Type>::ListMember::~ListMember() {
	delete data;
	delete next;
}

template<class Type>
void LinkList<Type>::ListMember::set_data(Type new_data) {
	data = &new_data;
}

template<class Type>
Type LinkList<Type>::ListMember::get_data() {
	return *data;
}

template<class Type>
Type *LinkList<Type>::ListMember::get_next() {
	return *next;
}

template<class Type>
void LinkList<Type>::ListMember::set_next(ListMember next_member) {
	next = &next_member;
}

template<class Type>
LinkList<Type>::LinkList() {
	list = new ListMember[data_size];
	arr_size = 0;
}

template<class Type>
LinkList<Type>::~LinkList() {
	delete[] list;
}

template<class Type>
LinkList<Type>::LinkList(LinkList &other) {
	*this = other;
}

template<class Type>
LinkList<Type>::LinkList(LinkList &&other) noexcept {
	*this = other;
}

template<class Type>
typename LinkList<Type>::ListMember LinkList<Type>::operator[](int ind) {
	if(ind > data_size - 1){
		std::cout << "\nOut of bounds\n";
		return empty;
	}
	return list[ind];
}

template<class Type>
LinkList<Type> &LinkList<Type>::operator=(const LinkList<Type> &other) {
	resize(other.size());
	arr_size = other.arr_size;
	memcpy(list, other.list, arr_size * sizeof (ListMember));
	return *this;
}

template<class Type>
LinkList<Type> &LinkList<Type>::operator=(LinkList<Type> &&other) noexcept {
	delete[] list;
	arr_size = other.size();
	list = other.list;
	return *this;
}

template<class Type>
void LinkList<Type>::resize(int new_size) {
	ListMember* mid_list;
	mid_list = new ListMember[arr_size];
	memcpy(mid_list,list,arr_size * sizeof(ListMember));
	delete[] list;
	list = new ListMember[new_size];
	memcpy(list,mid_list,arr_size * sizeof(ListMember));
	data_size = new_size;
}

template<class Type>
int LinkList<Type>::size() const {
	return arr_size;
}

template<class Type>
void LinkList<Type>::push_head(Type new_member) {
	arr_size += 1;
	if(arr_size >= data_size){
		resize(arr_size+10);
	}
	list[arr_size-1] = new_member;

	head = *new_member;
}

template<class Type>
void LinkList<Type>::set_head(Type * obj) {
	head = *obj;
}

template<class Type>
Type *LinkList<Type>::get_head() {
	return head;
}

template<class Type>
void LinkList<Type>::push_tail(Type new_member) {
	arr_size += 1;
	if(arr_size >= data_size){
		resize(arr_size+10);
	}
	ListMember new_list_member;
	new_list_member.set_data(new_member);
	list[arr_size-1] = new_list_member;
	if(arr_size > 1){
		list[arr_size-2].set_next(list[arr_size-1]);
	}
}

template<class Type>
void LinkList<Type>::pop_front() {

}




#endif //ATD_LINKED_LIST_H
