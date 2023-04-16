#ifndef MR2022_STACK_H
#define MR2022_STACK_H

#include "List.h"


class Stack{
private:
    List *list;
public:
    Stack();
    void push(double in_val);
    void pop();
    double get();
};


Stack::Stack() {
    list = new List();
}

void  Stack::push(double in_val) {
    list->push_head(in_val);
}

void Stack::pop() {
    list->pop_head();
}

double Stack::get() {
    return list->head->data;
}


#endif //MR2022_STACK_H
