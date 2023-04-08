#include "queue.h"
#include <iostream>


using namespace queue_names;

queue::queue() {
    size = 0;
    p_head = nullptr;
    p_head= nullptr;
}

void queue::clear() {
    while (size) { pop(); }
    p_head = nullptr;
    p_tail = nullptr;
}

queue::~queue() {
    clear();
}

void queue::pop() {
    if (p_head == nullptr) {
        queue_exceptions QUEUE_POP_ERROR("can`t pop from empty queue");
        throw QUEUE_POP_ERROR;
    }
    if (*(p_head->prev()) == nullptr)    {
        delete p_head;
        p_head = nullptr;
        p_tail = nullptr;
        size--;
        return;
    }
    p_head = *(p_head->prev());
    delete *(p_head->next());
    *(p_head->next()) = nullptr;

    size--;
}

void queue::push(double data) {
    if (p_head == nullptr and p_tail == nullptr){
        Node* first_node = new Node(data, nullptr, nullptr);
        p_head = first_node;
        p_tail = first_node;
        size++;
        return;
    }
    Node* new_node = new Node(data, p_tail, nullptr);
    p_tail->push_next(new_node);
    p_tail = new_node;
    size++;
}

void queue::show() {
    if (p_head == nullptr) {
        queue_exceptions QUEUE_SHOW_ERROR("can`t show zero size queue");
        throw QUEUE_SHOW_ERROR; }
    Node* running_pointer = p_head;
    while (running_pointer != nullptr){
        std::cout << running_pointer->data << "\t";
        running_pointer = *(running_pointer->prev());
    }
    std::cout  << "\n";

}

double queue::get_element(unsigned int element_number) {
    if (element_number >= size) {
        queue_exceptions QUEUE_OUT_OF_THE_RANGE("index out of the range");
        throw QUEUE_OUT_OF_THE_RANGE; }
    if (size == 0) {
        queue_exceptions ZERO_SIZE("zero size error");
        throw ZERO_SIZE; }

    Node* running_pointer = p_head;
    for (unsigned counter = 1; counter <= element_number; counter++){
        running_pointer = *(running_pointer->prev());
    }
    return running_pointer->data;
}

Node::Node() {
    p_next = nullptr;
    p_prev = nullptr;
    data = 0;
}

Node::Node(double data) {
    p_next = nullptr;
    p_prev = nullptr;
    this->data = data;
}

void Node::push_next(Node *other) {
    this->p_prev = other;
    other->p_next = this;
}

Node::Node(double data, Node *p_next, Node *p_prev) {
    this->p_next = p_next;
    this->p_prev = p_prev;
    this->data = data;
}

void Node::push_prev(Node *other) {
    other->p_prev = this;
    this->p_next = other;
}

Node::~Node() {
    p_next = nullptr;
    p_prev = nullptr;
}


