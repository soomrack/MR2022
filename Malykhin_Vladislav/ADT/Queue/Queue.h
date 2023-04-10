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
    list->pop(list->tail());
}

double Queue::get() {
    return list->tail().node_ptr->data;
}


#endif //QUEUE_H
