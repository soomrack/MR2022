#include <iostream>
#include <cmath>

const double COMPARATION_CONST = 0.0001;


class Item {

protected:
    int item_prt;
    Item *next_item;
    Item *prev_item;

public:
    double value;

    Item();
    Item(double x, int prt = 0);
    Item(double x, int prt, Item *his_next, Item *his_prev);
    Item(const Item& x);
    ~Item();

    Item& operator=(const Item& x);

    void push_next(Item *x);
    void push_prev(Item *x);

    int priority();
    Item* next();
    Item* prev();

};

Item::Item() {
    value = 0.0;
    item_prt = 7;
    next_item = nullptr;
    prev_item = nullptr;
}


class PrtQueue {

protected:
    Item *pq_head;
    Item *pq_tail;

public:
    PrtQueue();
    PrtQueue(double head_val, int head_prt = 0);
    ~PrtQueue();

    void push(double val, int prt = 0);

    Item* find_first(double val, int prt);
    Item pop();

    Item* head();
    Item* tail();
    void print(bool extra_data = false);
};


Item::Item(const double x, const int prt) {
    value = x;
    item_prt = prt;
    next_item = nullptr;
    prev_item = nullptr;
}


Item::Item(const double x, const int prt, Item *his_next, Item *his_prev) {
    value = x;
    item_prt = prt;
    next_item = his_next;
    prev_item = his_prev;
}

Item::Item(const Item &x) {
    value = x.value;
    item_prt = x.item_prt;
    next_item = x.next_item;
    prev_item = x.prev_item;
}

Item::~Item() {
    next_item = nullptr;
    prev_item = nullptr;
}

Item &Item::operator=(const Item &x) {
    value = x.value;
    item_prt = x.item_prt;
    next_item = x.next_item;
    prev_item = x.prev_item;
}

void Item::push_next(Item *x) {
    next_item = x;
}

void Item::push_prev(Item *x) {
    prev_item = x;
}

int Item::priority() {
    return item_prt;
}

Item *Item::next() {
    return next_item;
}

Item *Item::prev() {
    return prev_item;
}

PrtQueue::PrtQueue() {
    pq_head = nullptr;
    pq_tail = nullptr;
}

PrtQueue::PrtQueue(double head_val, int head_prt) {
    pq_head = nullptr;
    pq_tail = nullptr;
    push(head_val, head_prt);
}

PrtQueue::~PrtQueue() {
    pq_head = nullptr;
    pq_tail = nullptr;
}

void PrtQueue::push(double val, int prt) {
    Item *elm = new Item(val, prt);
    if (pq_head == nullptr){
        pq_head = elm;
        pq_tail = elm;
        return;
    }

    if (pq_head->priority() > prt){
        elm->push_next(pq_head);
        pq_head->push_prev(elm);
        pq_head = elm;
    }

    Item *cur = pq_head;
    while (cur != nullptr){
        if (cur->priority() <= prt){
            cur = cur->next();
            continue;
        }

        cur->prev()->push_next(elm);
        elm->push_next(cur);
        elm->push_prev(cur->prev());
        cur->push_prev(elm);
        return;
    }

    pq_tail->push_next(elm);
    elm->push_prev(pq_tail);
    pq_tail = elm;
}

Item* PrtQueue::find_first(double val, int prt) {
    Item* item_idx = pq_head;
    while (item_idx != nullptr){
        if((fabs(item_idx->value - val) < COMPARATION_CONST) && (prt == item_idx->priority())) return item_idx;
        item_idx = item_idx->next();
    }
    if (item_idx == nullptr) item_idx = new Item();
    return item_idx;
}

Item PrtQueue::pop() {
    if (pq_head == nullptr){
        return Item();
    }

    Item ans = *pq_head;
    if (ans.next() != nullptr) ans.next()->push_prev(nullptr);
    pq_head = ans.next();

    return ans;
}

Item* PrtQueue::head() {
    return pq_head;
}

Item* PrtQueue::tail() {
    return pq_tail;
}

void PrtQueue::print(bool show_data) {

    if (head() == nullptr) return;
    std::cout << "The pq_head is " << pq_head->value << "[" << pq_head->priority() << "]" <<
              ";  the pq_tail is " << pq_tail->value << "[" << pq_tail->priority() << "]\n";

    Item* current = pq_head;
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
    PrtQueue A = PrtQueue();
    A.push(0.1);
    A.print(true);

    A.push(1.2, 1);
    A.push(2.3, 1);
    A.push(3.4, 0);
    A.push(4.5, -1);
    A.print();

    A.pop();
    A.print(true);

    PrtQueue B = PrtQueue(9.9, 1);
    B.print(true);
    Item v = B.pop();
    B.print(true);
    B.pop();

    B.push(8.8, 1);
    B.print(true);

    std::cout << v.value << "\n";
    std::cout << A.find_first(3.40001, 0)->value << "\n";

    return 0;
}

