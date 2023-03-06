#include <iostream>


template <typename T = double>
struct node {
	T value;
	node* next;
	node* prev;
};


template <typename T = double>
class Linked_list {
protected:
	node<>* head = nullptr;
	node<>* tail = nullptr;

public:
	Linked_list() = default;

	~Linked_list();

	void push_head(T value);
	void push_tail(T value);
	T get_item(unsigned int k);
	void delete_item(unsigned int k);

	void print_list();
};

template <typename T>
Linked_list<T>::~Linked_list() {
	node<>* temp = head;
	node<>* next;
	while (temp != nullptr) {
		next = temp->next;
		delete[] temp;
		temp = next;
	}
}

template <typename T>
void Linked_list<T>::push_head(T value) {
	node<>* new_node = new node<>;
	new_node->value = value;
	new_node->prev = nullptr;

	if (head == nullptr) {
		new_node->next = nullptr;
		head = new_node;
		tail = new_node;
	}
	else {
		new_node->next = head;
		head = new_node;
	}
}

template <typename T>
void Linked_list<T>::push_tail(T value) {
	node<>* new_node = new node<>;
	new_node->value = value;
	new_node->next = nullptr;

	if (head == nullptr) {
		new_node->prev = nullptr;
		head = new_node;
		tail = new_node;
	}
	else {
		tail->next = new_node;
		new_node->prev = tail;
		tail = new_node;
	}
}

template <typename T>
T Linked_list<T>::get_item(unsigned int k) {
	node<>* temp = head;
	for (unsigned int i = 1; i <= k; ++i) {
		temp = temp->next;
	}
	return temp->value;
}

template <typename T>
void Linked_list<T>::delete_item(unsigned int k) {
	node<>* delete_node = head;
	for (unsigned int i = 1; i <= k; ++i) {
		delete_node = delete_node->next;
	}
	delete_node->prev->next = delete_node->next;
	delete_node->next->prev = delete_node->prev;
	delete[] delete_node;
}

template <typename T>
void Linked_list<T>::print_list() {
	node<>* temp = head;
	while (temp != nullptr) {
		std::cout << temp->value << " ";
		temp = temp->next;
	}
	std::cout << "\n\n";
}

//int main() {
//	Linked_list<> A;
//	A.push_tail(2);
//	A.print_list();
//	A.push_head(3.5);
//	A.print_list();
//	A.push_head(1);
//	A.print_list();
//	A.push_tail(4);
//	A.print_list();
//
//	std::cout << A.get_item(1) << "\n\n";
//
//	//A.delete_item(2);
//	//A.print_list();
//	return 0;
//}