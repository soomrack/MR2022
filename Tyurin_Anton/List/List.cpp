#include <iostream>
#include "../List/List.h"

bool List::is_empty() {
    return head == nullptr;
}

void List::push_tail(std::string data){
    Node *local = new Node(data);
    if (is_empty()) {
        head = local;
        tail = local;
        size++;
        return;
    }
    tail->next = local;
    tail = local;
    size++;
}

void List::push_head(std::string data){
    Node *local = new Node(data);
    if (is_empty()) {
        head = local;
        tail = local;
        size++;
        return;
    }
    local->next = head;
    head = local;
    size++;
}

void List::print() {
    if (is_empty()) {return;}
    Node *local = head;
    while (local) {
        std::cout << local->data << " ";
        local = local->next;
    }
    std::cout << std::endl;
}

void List::find(unsigned int id) {
    if (is_empty()) {return;}
    auto *local = head;
    for(unsigned int idx; idx < id; idx++ ){
        local = local->next;
    }
   std::cout << local->data << std::endl;
}

void List::remove_first() {
    if (is_empty()) return;
    Node* local = head;
    head = local->next;
    delete local;
    size--;
}

void List::remove_last() {
    if (is_empty()) return;
    if (head == tail) {
        remove_first();
        return;
    }
    Node* local = head;
    while (local->next != tail) local = local->next;
    local->next = nullptr;
    delete tail;
    tail = local;
    size--;
}

void List::pop(unsigned int id) {
    if (is_empty()) return;
    if (id > size) return;
    if (0 == id ) {
        remove_first();
        return;
    }
    else if (id + 1 == size) {
        remove_last();
        return;
    }
    Node* local = head;
    for (int idx = 0; idx < id - 1; idx++) {
        local = local->next;
    }
    local->next = local->next->next;
    size--;
}

unsigned int List::get_size() {
    return size;
}


int main(){
    List List;
    List.print();

    List.push_tail("he");
    List.push_tail("ll");
    List.push_tail("ow");
    List.push_tail(" ");
    List.push_tail("wo");
    List.push_tail("rl");
    List.push_tail("d");
    List.print();
    std::cout << List.get_size() << std::endl;
    List.find(4);
    List.pop(4);
    List.print();

    return 0;
}