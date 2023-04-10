#ifndef QUEUE_H
#define QUEUE_H

#include "List.h"


class Queue {
private:
    List *list;
public:
    Queue();
    void push(double in_val);
    void pop();
    double get();
};

Queue::Queue() {
    list = new List();
}

void  Queue::push(double in_val) {
    list->push_head(in_val);
}

void Queue::pop() {
    list->pop_tail();
}

double Queue::get() {
    return list->get_tail().data;
}


#endif //QUEUE_H
