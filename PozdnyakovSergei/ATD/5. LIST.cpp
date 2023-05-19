#include <iostream>


class Node {
private:
    Node *next;
public:
    double value;

    Node(double data) : value(value), next(nullptr) {}
    ~Node() = default;

    Node *get_next() { return next; }
    void set_next(Node *new_next) { next = new_next; }
    void push_next(double item);
    void delete_next();
};


void Node::push_next(double item) {
    Node *temp = new Node(item);
    if (next == nullptr) {
        next = temp;
    } else {
        Node *temp2 = next;
        temp->next = temp2;
        next = temp;
    }
}


void Node::delete_next() {
    if (next == nullptr) throw std::runtime_error("Next node doesn't exist!");

    Node *temp = next;
    if (temp->next == nullptr) {
        next = nullptr;
    } else {
        Node *temp2 = temp->next;
        next = temp2;
    }
    delete temp;
}


class LinkedList {
private:
    unsigned int size;

public:
    Node *head;

    LinkedList() : head(nullptr), size(0) {}
    ~LinkedList() { clear(); }

    void push_head(double data);
    Node *pop_head();
    int get_size() const { return size; }
    bool is_empty() const { return size == 0; }
    void clear();
    Node *get_head() { return head; }
    void push_next(double data, unsigned int index);
    void delete_next(unsigned int index);

};


void LinkedList::push_head(double value) {
    Node *temp = new Node(value);
    if (head == nullptr) {
        head = temp;
    } else {
        temp->set_next(head);
        head = temp;
    }
    size++;
}


Node *LinkedList::pop_head() {
    if (head == nullptr) throw std::underflow_error("List is empty!");

    Node *temp = head;
    if (head->get_next() == nullptr) {
        head = nullptr;
    } else {
        head = head->get_next();
    }
    size--;
    return temp;
}


void LinkedList::clear() {
    while (head != nullptr) {
        Node *temp = head;
        head = head->get_next();
        delete temp;
    }
    head = nullptr;
    size = 0;
}


void LinkedList::push_next(double value, unsigned int number) {
    Node *temp = head;
    for (int i = 0; i < number; ++i) {
        temp = temp->get_next();
    }
    size++;
    temp->push_next(value);
}


void LinkedList::delete_next(unsigned int number) {
    Node *temp = head;
    for (int i = 0; i < number; ++i) {
        temp = temp->get_next();
    }
    size--;
    temp->delete_next();
}


int main() {

}
