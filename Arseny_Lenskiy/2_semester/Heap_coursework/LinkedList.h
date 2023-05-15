#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template<typename T>
class ListNode {
private:
    ListNode *next;
public:
    T data;

    ListNode(T data) : data(data), next(nullptr) {}
    ~ListNode() = default;

    ListNode *get_next() { return next; }
    void set_next(ListNode *new_next) { next = new_next; }
    void push_next(T item);
};

template<typename T>
void ListNode<T>::push_next(T item) {
    auto *temp = new ListNode(item);
    if (next == nullptr) {
        next = temp;
    } else {
        ListNode *temp2 = next;
        temp->next = temp2;
        next = temp;
    }
}

template<typename T>
class LinkedList {

private:
    unsigned int size;

public:
    ListNode<T> *head;

    LinkedList() : head(nullptr), size(0) {}
    ~LinkedList() { clear(); }

    void push_head(T data);
    ListNode<T> *pop_head();
    int get_size() const { return size; }
    bool is_empty() const { return size == 0; }
    void clear();
    ListNode<T> *get_head() { return head; }
    void push_next(T data, unsigned int index);
};

template<typename T>
void LinkedList<T>::push_head(T data) {
    auto *temp = new ListNode<T>(data);
    if (head == nullptr) {
        head = temp;
    } else {
        temp->set_next(head);
        head = temp;
    }
    size++;
}

template<typename T>
ListNode<T> *LinkedList<T>::pop_head() {
    if (head == nullptr) throw std::underflow_error("List is empty!");

    ListNode<T> *temp = head;
    if (head->get_next() == nullptr) {
        head = nullptr;
    } else {
        head = head->get_next();
    }
    size--;
    return temp;
}

template<typename T>
void LinkedList<T>::clear() {
    while (head != nullptr) {
        ListNode<T> *temp = head;
        head = head->get_next();
        delete temp;
    }
    size = 0;
}

template<typename T>
void LinkedList<T>::push_next(T data, unsigned int index) {
    if (index >= size) throw std::out_of_range("Invalid index!");

    ListNode<T> *temp = head;
    for (int i = 0; i < index; ++i) {
        temp = temp->get_next();
    }
    size++;
    temp->push_next(data);
}

#endif
