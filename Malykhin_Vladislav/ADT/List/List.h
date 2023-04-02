// можно работать через узлы (push_next()/next())
// или через итераторы для двух связного списка
// tail хранить не нужно
// нельзя делать доступ по индексу
#ifndef DYNAMIC_ARRAY_LIST_H
#define DYNAMIC_ARRAY_LIST_H


#include "Node.h"
#include "Iterator.h"

class List {
protected:
    Node *head;
    Node *tail;
public:
    List();

    unsigned int size();
    void push_head(int in);
    void pop_head();
    void push_tail(int in); // убрать
    void pop_tail(); // убрать
    void push(int in, Iterator in_idx);
    void pop(Iterator in_idx); // удаление произвольного
    bool is_empty();

};


#endif //DYNAMIC_ARRAY_LIST_H
