#ifndef LIST_ITERATOR_H
#define LIST_ITERATOR_H

#include "List.h"


class Iterator{
private:
    Node*  node_ptr;
public:
    Iterator();
    Iterator(Node *in_node);

    Iterator  operator+ (int number) const;
    Iterator  operator- (int number) const;
    Iterator&  operator++ (int n);
    Iterator &operator= (Iterator const &other) ;
    Iterator &operator= (Iterator &&other) noexcept;
};

Iterator::Iterator(){
    node_ptr = nullptr;
}

Iterator::Iterator(Node *in_node) {
    node_ptr = in_node;
}
#endif //LIST_ITERATOR_H