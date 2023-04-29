#ifndef QUEUE_H
#define QUEUE_H

#include "List.h"


class Queue {
private:
    List *list;
public:
    Queue();
    void push(double in_val, int in_prio);
    void pop();
    double get();
};

Queue::Queue() {
    list = new List();
}

void  Queue::push(double in_val, int in_prio) {
    list->push(in_val, in_prio);
}

void Queue::pop() {
    list->pop_tail();
}

double Queue::get() {
    return list->get_tail().data;
}


#endif //QUEUE_H
