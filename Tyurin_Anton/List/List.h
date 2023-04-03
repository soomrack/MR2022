
#ifndef UNTITLED_LIST_H
#define UNTITLED_LIST_H

#include <string>

class List;
class Node {
    friend class List;
protected:
    Node *next;
    std::string data;
public:
    Node(std::string data) : data(data), next(nullptr){}
};

class List {
protected:
    Node *head; // head
    Node *tail;  // tail
    unsigned int size;
public:
    List() : head(nullptr), tail(nullptr), size(0) {}
    bool is_empty();
    void push_tail(std::string data);
    void print();
    void push_head(std::string data);
    void find(unsigned int id);
    void pop(unsigned int id);
    Node loop(unsigned int id, auto *local);
    Node *operator[](const int index);
    void remove_first();
    void remove_last();
    unsigned int get_size();
};

#endif //UNTITLED_LIST_H
