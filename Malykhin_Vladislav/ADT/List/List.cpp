#include "List.h"

List::List() {
    head = nullptr;
    tail = nullptr;
}

bool List::is_empty() {
    if (head == nullptr) return true;
    return false;
}


unsigned int List::size() {
    if(is_empty()) return 0;
    Node *iter = head;
    unsigned int size = 1;
    while(iter != tail) {
        ++size;
        iter = iter->next;
    }
    return size;
}


void  List::push_head(int in) {
    if(is_empty()) {
        Node *new_node = new Node(in);
        head = new_node;
        tail = new_node;
        return;
    }
    Node* new_node = new Node(in);
    new_node->next = head;
    head = new_node;
}


void List::pop_head() {
    if(is_empty()) return; // для пустого списка
    if(size() == 1) { // для списка из одного элемента
        delete head;
        head = nullptr;
        tail = nullptr;
        return;
    }
    Node *iter = head->next;
    delete head;
    head = iter;
}


void  List::push_tail(int in) {
    if(is_empty()) {  // для пустого списка
        Node *new_node = new Node(in);
        head = new_node;
        tail = new_node;
        return;
    }
    Node *new_node = new Node(in);
    tail->next = new_node;
    tail = new_node;
}


void List::pop_tail() {
    if(is_empty()) return; // для пустого списка
    if(size() == 1) { // для списка из одного элемента
        delete head;
        head = nullptr;
        tail = nullptr;
        return;
    }
    Node *iter = head; // для остальных списков
    for(unsigned int new_size = 1; new_size < size() - 1; new_size++) { // возможен баг, при возникновении < заменить на <=
        iter = iter->next;
    }
    delete tail;
    tail = iter;
    tail->next = nullptr;
}


void List::push(int in, unsigned int in_idx) {
    if(in_idx == 0){
        push_head(in);
        return;
    }
    if(in_idx >= size()) {
        push_tail(in);
        return;
    }
    Node *new_node = new Node(in);
    Node* iter = head;
    for(unsigned int idx = 1; idx <= in_idx - 1; ++idx) {
        iter = iter->next;
    }
    Node* iter_buff = iter->next;
    iter->next = new_node;
    new_node->next = iter_buff;
}


void List::pop(unsigned int in_idx) {
    if (in_idx == 0) {
        pop_head();
        return;
    }
    if (in_idx >= size()) {
        pop_tail();
        return;
    }
    Node *iter = head;
    for (unsigned int idx = 1; idx < in_idx - 1; ++idx) {
        iter = iter->next;
    } // дописать
    Node *iter_buff= iter->next->next; // нужно тестировать
    delete iter->next;
    iter = iter_buff;
}