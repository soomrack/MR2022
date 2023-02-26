//
// Created by delta on 25.02.2023.
//

#ifndef CLIONPROJECTS_LIST_H
#define CLIONPROJECTS_LIST_H

#endif //CLIONPROJECTS_LIST_H

#include <iostream>
using namespace std;

template <class Q>
class List;

template <class Q>
 class ListNode
{
    Q field;
    class ListNode *ptr;
    friend class List<Q>;
};

template <class Q>
class List
{
    ListNode<Q> *head;
    int count = 0;
    ListNode<Q>* Prev(ListNode<Q>*);
public:

    List() { head = nullptr; }
    int getCount() { return count; }
    bool isEmpty() { return head == nullptr; }
    static int getValue(ListNode<Q>* p) { return p->field; }
    static void setValue(ListNode<Q>*p, int val) { p->field = val; }
    ListNode<Q>* getFirst() { return head; }

    ListNode<Q>& operator=(const ListNode<Q>& x);
    ListNode<Q>* getLast();
    void Clear();
    ListNode<Q>* Next(ListNode<Q>*);
    ListNode<Q>* Add(int, ListNode<Q>*);
    ListNode<Q>* Delete(ListNode<Q>*);
    void Print();
    void Swap(ListNode<Q>*, ListNode<Q>*);
};

template <typename Q>
ListNode<Q>* List<Q>::Add(int num, ListNode<Q>* node)
{
    node = nullptr;
    auto*elem = new ListNode<Q>();
    elem->field = num;
    count++;
    if (node == nullptr)
    {
        if (head == nullptr) {
            elem->ptr = nullptr;
            head = elem;
        }
        else {
            elem->ptr = head;
            head = elem;
        }
        return elem;
    }
    elem->ptr = node->ptr;
    node->ptr = elem;
    return elem;
}

template <typename Q>
ListNode<Q>* List<Q>::Delete(ListNode<Q>* node)
{
    if (node == nullptr) { return nullptr; }
    count--;
    if (node == head)
    {
        head = node->ptr;
        delete node;
        return head;
    }
    ListNode<Q>* prev = Prev(node);
    prev->ptr = node->ptr;
    delete node;
    return prev;
}

template <typename Q>
ListNode<Q>* List<Q>::Next(ListNode<Q>* node)
{
    if (isEmpty()) return nullptr;
    return node->ptr;
}

template <typename Q>
ListNode<Q>* List<Q>::Prev(ListNode<Q>* node)
{
    if (isEmpty()) return nullptr;
    if (node == head) return nullptr;
    ListNode<Q>*p = head;
    while (p->ptr != node)
        p = p->ptr;
    return p;
}

template <typename Q>
ListNode<Q>* List<Q>::getLast()
{
    ListNode<Q>* p = head;
    while (Next(p) != nullptr)
        p = Next(p);
    return p;
}

template <typename Q>
void List<Q>::Clear()
{
    class ListNode<Q> *p = head;
    if (p == nullptr) return;
    do {
        ListNode<Q> *d = p;
        p = Next(p);
        delete d;
    } while (p != nullptr);
    count = 0;
    head = nullptr;
}

template <typename Q>
void List<Q>::Print()
{
    if (isEmpty()) { cout << "list is empty" << endl; return; }
    ListNode<Q>*p = head;
    do {
        cout << getValue(p) << " ";
        p = Next(p);
    } while (p != nullptr);
    cout << endl;
}

template <typename Q>
void List<Q>::Swap(ListNode<Q>* node1, ListNode<Q>* node2)
{
    if (node1 == nullptr || node2 == nullptr) return;
    if (node1 == node2) return;
    if (node2->ptr == node1)
    {
        ListNode<Q>*p = node1;
        node1 = node2;
        node2 = p;
    }
    ListNode<Q>*prev1 = Prev(node1);
    ListNode<Q>*prev2 = Prev(node2);
    ListNode<Q>*next1 = Next(node1);
    ListNode<Q>*next2 = Next(node2);
    if (next1 == node2)
    {
        if (prev1 != nullptr)
            prev1->ptr = node2;
        else
            head = node2;
        node2->ptr = node1;
        node1->ptr = next2;
        return;
    }
    if (prev1 != nullptr)
        prev1->ptr = node2;
    else
        head = node2;
    if (prev2 != nullptr)
        prev2->ptr = node1;
    else
        head = node1;
    node2->ptr = next1;
    node1->ptr = next2;
}