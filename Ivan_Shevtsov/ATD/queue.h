//
// Created by ivan on 01/04/23.
//

#ifndef ATD_QUEUE_H
#define ATD_QUEUE_H

#include <iostream>




namespace queue_names {

    class Node {
    protected:
        Node *p_next;
        Node *p_prev;
    public:
        double data;

        Node();
        Node(double data);
        Node(double data, Node *p_next, Node *p_prev);

        void push_next(Node *other);
        void push_prev(Node *other);

        Node **next() { return &p_next; }
        Node **prev() { return &p_prev; }

        ~Node();
    };

    class queue {
    private:
        unsigned size;
        Node *p_tail;
        Node *p_head;
    public:
        queue();

        void show();
        void clear();

        void push(double data);
        void pop();

        Node *front() { return p_head; }
        Node *back() { return p_tail; }

        double get_element(unsigned element_number);  // starting from 0

        ~queue();
    };

}
#endif //ATD_QUEUE_H
