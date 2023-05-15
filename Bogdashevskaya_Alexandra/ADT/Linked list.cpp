#include <iostream>

template <typename T = double>
class Node {
protected:
	T value = NULL;
	Node* prev = nullptr;
	Node* next = nullptr;

public:
	Node() = default;
	Node(const Node& node);
	~Node();

	template <typename T = double> friend class LinkedList;
};



//template <typename T = double>
//struct node {
//	T value;
//	node* next;
//	node* prev;
//};


template <typename T = double>
class LinkedList { 
protected:
	Node<T>* head = nullptr;
	Node<T>* tail = nullptr;

public:
	LinkedList() = default;

	~LinkedList();

	void push_head(T value);
	void push_tail(T value);
	//T get_item(unsigned int k);
	//void delete_item(unsigned int k);

	void print_list();
};


template <typename T>
Node<T>::~Node() {
	prev = nullptr;
	next = nullptr;
}

template <typename T>
Node<T>::Node(const Node& node) {
	value = node->value;
	prev = node->prev;
	next = node->next;
}


template <typename T>
LinkedList<T>::~LinkedList() { 
	head = nullptr;
	tail = nullptr;
}

template <typename T>
void LinkedList<T>::push_head(T value) {
	Node<T>* new_node = new Node<T>();
	new_node->value = value;
	new_node->prev = nullptr;

	if (head == nullptr) {
		new_node->next = nullptr;
		head = new_node;
		tail = new_node;
		return;
	}
	
	new_node->next = head;
	head = new_node;
	
}

template <typename T>
void LinkedList<T>::push_tail(T value) {
	Node<T>* new_node = new Node<T>();
	new_node->value = value;
	new_node->next = nullptr;

	if (head == nullptr) {
		new_node->prev = nullptr;
		head = new_node;
		tail = new_node;
		return;
	}
	tail->next = new_node;
	new_node->prev = tail;
	tail = new_node;
}

//template <typename T>
//T Linked_list<T>::get_item(unsigned int k) { //k>
//	node<>* temp = head;
//	for (unsigned int i = 1; i <= k; ++i) {
//		temp = temp->next;
//	}
//	return temp->value;
//}
//
//template <typename T>
//void Linked_list<T>::delete_item(unsigned int k) {
//	node<>* delete_node = head;
//	for (unsigned int i = 1; i <= k; ++i) {
//		delete_node = delete_node->next;
//	}
//	delete_node->prev->next = delete_node->next;
//	delete_node->next->prev = delete_node->prev;
//	delete[] delete_node;
//}

template <typename T>
void LinkedList<T>::print_list() {
	Node<T>* temp = head;
	while (temp != nullptr) {
		std::cout << temp->value << " ";
		temp = temp->next;
	}
	std::cout << "\n\n";
}
//
//int main() {
//	LinkedList<> A;
//	A.push_tail(2);
//	A.print_list();
//	A.push_head(3.5);
//	A.print_list();
//	A.push_head(1);
//	A.print_list();
//	A.push_tail(4);
//	A.print_list();
//
//	return 0;
//}