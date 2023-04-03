#ifndef ATD_QUEUE_H
#define ATD_QUEUE_H

#include <iostream>


namespace queue_names {
    class queue_exceptions: public std::domain_error{
    public:
        queue_exceptions(const char* massage): std::domain_error(massage){}
    };

    queue_exceptions ZERO_SIZE("zero size error");
    queue_exceptions QUEUE_OUT_OF_TRE_RANGE("index out of the range");
    queue_exceptions QUEUE_POP_ERROR("can`t pop from empty queue");
    queue_exceptions QUEUE_SHOW_ERROR("can`t show zero size queue");

    class Node {
    protected:
        Node *p_next;
        Node *p_prev;
    public:
        double data;

        Node();
        Node(double data);
        Node(double data, Node *p_next, Node *p_prev);
        ~Node();

        void push_next(Node *other);
        void push_prev(Node *other);

        Node **next() { return &p_next; }
        Node **prev() { return &p_prev; }
    };

    class queue {
    private:
        unsigned size;
        Node *p_tail;
        Node *p_head;
    public:
        queue();
        ~queue();

        void show();
        void clear();

        void push(double data);
        void pop();

        Node *front() { return p_head; }
        Node *back() { return p_tail; }

        double get_element(unsigned element_number);  // element number starting from 0
    };

}
#endif //ATD_QUEUE_H
