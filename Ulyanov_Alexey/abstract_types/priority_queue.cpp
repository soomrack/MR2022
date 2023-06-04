#include <iostream>
#include <cmath>
//#include <exception>

const double COMPARATION_CONST = 0.0001;


class QItem {

protected:
    int item_prtet;
    QItem* next_item;
    QItem* prev_item;

public:
    double value;

    QItem();
    QItem(const double x, const int prtet = 0);
    QItem(const double val,const int prtet, QItem* his_next, QItem* his_prev);
    QItem(const QItem& x);
    QItem(QItem&& x);
    ~QItem();

    QItem& operator=(const QItem& x);

    void push_next(QItem* x);
    void push_prev(QItem* x);

    int priority();
    QItem* next();
    QItem* prev();

};


class PriorityQueue {

protected:

    QItem *pq_head;
    QItem *pq_tail;


public:

    PriorityQueue();
    PriorityQueue(double head_val, int head_prtet = 0);
    ~PriorityQueue();

    void push(double val, int prtet = 0);

    QItem* find_first(double val, int prtet);
    QItem pop();

    QItem* head();
    QItem* tail();
    void print(bool show_data = false);

};



QItem::QItem() {
    value = 0.0;
    item_prtet = 7;
    next_item = nullptr;
    prev_item = nullptr;
}


QItem::QItem(const double x, const int prtet) {
    value = x;
    item_prtet = prtet;
    next_item = nullptr;
    prev_item = nullptr;
}


QItem::QItem(const double val, const int prtet, QItem *his_next, QItem *his_prev) {
    value = val;
    item_prtet = prtet;
    next_item = his_next;
    prev_item = his_prev;
}


QItem::QItem(const QItem &x) {
    value = x.value;
    item_prtet = x.item_prtet;
    next_item = x.next_item;
    prev_item = x.prev_item;
}


QItem::QItem(QItem &&x) {
    value = x.value;
    item_prtet = x.item_prtet;
    next_item = x.next_item;
    prev_item = x.prev_item;

    x.value = 0.0;
    x.item_prtet = 0;
    x.next_item = nullptr;
    x.prev_item = nullptr;
}


QItem::~QItem() {
    next_item = nullptr;
    prev_item = nullptr;
}


QItem& QItem::operator=(const QItem &x) {
    value = x.value;
    item_prtet = x.item_prtet;
    next_item = x.next_item;
    prev_item = x.prev_item;
}


int QItem::priority() {
    return item_prtet;
}


QItem* QItem::next() {
    return next_item;
}


QItem* QItem::prev() {
    return prev_item;
}


void QItem::push_next(QItem *x) {
    next_item = x;
}


void QItem::push_prev(QItem *x) {
    prev_item = x;
}


PriorityQueue::PriorityQueue() {
    pq_head = nullptr;
    pq_tail = nullptr;
}


PriorityQueue::PriorityQueue(double head_value, int head_prtet) {
    pq_head = nullptr;
    pq_tail = nullptr;
    push(head_value, head_prtet);
}


PriorityQueue::~PriorityQueue() {
    pq_head = nullptr;
    pq_tail = nullptr;
}


void PriorityQueue::push(double val, int prtet) {
    QItem* elm = new QItem(val, prtet);
    if (pq_head == nullptr){
        pq_head = elm;
        pq_tail = elm;
        return;
    }

    if (pq_head->priority() > prtet){
        elm->push_next(pq_head);
        pq_head->push_prev(elm);
        pq_head = elm;
    }

    QItem* current = pq_head;
    while (current != nullptr){
        if (current->priority() <= prtet) {
            current = current->next();
            continue;
        }

        current->prev()->push_next(elm);
        elm->push_prev(current->prev());
        elm->push_next(current);
        current->push_prev(elm);
        return;
    }

    pq_tail->push_next(elm);
    elm->push_prev(pq_tail);
    pq_tail = elm;
}


QItem* PriorityQueue::find_first(double val, int prtet) {
    QItem* item_idx = pq_head;
    while (item_idx != nullptr){
        if ((fabs(item_idx->value - val) < COMPARATION_CONST) && (prtet == item_idx->priority())) return item_idx;
        item_idx = item_idx->next();
    }
    if (item_idx == nullptr) item_idx = new QItem();
    return item_idx;
}


QItem PriorityQueue::pop() {
    if (pq_head == nullptr){
        //throw exception("Nothing to pop");
        return QItem();
    }

    QItem ans = *pq_head;

    if (ans.next() != nullptr) ans.next()->push_prev(nullptr);
    pq_head = ans.next();

    return ans;
}


QItem* PriorityQueue::head() {
    return pq_head;
}


QItem* PriorityQueue::tail() {
    return pq_tail;
}


void PriorityQueue::print(bool show_data) {

    if (head() == nullptr) return;
    std::cout << "The pq_head is " << pq_head->value << "[" << pq_head->priority() << "]" <<
              ";  the pq_tail is " << pq_tail->value << "[" << pq_tail->priority() << "]\n";

    QItem* current = pq_head;
    while (current != nullptr){
        std::cout << current->value << "[" << current->priority() << "]  ";
        if (show_data){
            if (current->prev() != nullptr) std::cout << "his prev is " << current->prev()->value << "[" << current->prev()->priority() << "]  ";
            if (current->prev() != nullptr && current->next() != nullptr) std::cout << "and ";
            if (current->next() != nullptr) std::cout << "his next is " << current->next()->value << "[" << current->next()->priority() << "]";
            std::cout << "\n";
        }
        current = current->next();
    }
    if (!show_data) std::cout << "\n";
    std::cout << "\n";
}


int main() {

    PriorityQueue A = PriorityQueue();
    A.push(0.1);
    A.print(true);

    A.push(1.2, 1);
    A.push(2.3, 1);
    A.push(3.4, 0);
    A.push(4.5, -1);
    A.print();

    A.pop();
    A.print(true);

    PriorityQueue B = PriorityQueue(9.9, 1);
    B.print(true);
    QItem v = B.pop();
    B.print(true);
    B.pop();

    B.push(8.8, 1);
    B.print(true);

    std::cout << v.value << "\n";
    std::cout << A.find_first(3.40001, 0)->value << "\n";

    return 0;
}