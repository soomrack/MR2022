// можно работать через узлы (push_next()/next())
// или через итераторы для двух связного списка
// tail хранить не нужно
// нельзя делать доступ по индексу
#ifndef DYNAMIC_ARRAY_LIST_H
#define DYNAMIC_ARRAY_LIST_H


#include "Node.h"


class List {
protected:
    Node *head;
    Node *tail;
public:
    List();

    unsigned int size();
    void push_head(int in);
    void pop_head();
    void push_tail(int in);
    void pop_tail();
    void push(int in, unsigned int in_idx);
    void pop(unsigned int in_idx); // удаление произвольного
    bool is_empty();

};


#endif //DYNAMIC_ARRAY_LIST_H
