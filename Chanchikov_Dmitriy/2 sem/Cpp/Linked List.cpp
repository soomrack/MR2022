#include <iostream>
#include <exception>

const double COMPARATION_CONST = 0.0001;


double abs(double x){
    if (x < COMPARATION_CONST) return -x;
    return x;
}


class Item {

protected:
    Item* next_item;
    Item* prev_item;

public:
    double value;

    Item();
    explicit Item(double x);
    ~Item();

    Item& operator=(const double& x);
    Item& operator=(const Item& x);

    void push_next(Item* x);
    void push_prev(Item* x);

    Item* next();
    Item* prev();

    void del_current();

};


class LinkedList {

protected:
    Item* list_head;
    Item* list_tail;

public:
    LinkedList();
    explicit LinkedList(double list_head_val);
    ~LinkedList();

    void push_head(double val);
    void push_tail(double val);

    Item* find_first(double val);
    Item* pop(double val);

    Item* head();
    Item* tail();

    void print();

};



Item::Item() {
    value = double(NULL);
    next_item = nullptr;
    prev_item = nullptr;
}


Item::Item(const double x) {
    value = x;
    next_item = nullptr;
    prev_item = nullptr;
}


Item::~Item() {
    next_item = nullptr;
    prev_item = nullptr;
}


Item& Item::operator=(const double &x) {
    value = x;
    next_item = this;
    prev_item = this;
    return *this;
}


Item& Item::operator=(const Item &x) = default;


Item* Item::next() {
    return next_item;
}


Item* Item::prev() {
    return prev_item;
}


void Item::push_next(Item *x) {
    next_item = x;
}


void Item::push_prev(Item *x) {
    prev_item = x;
}


void Item::del_current() {
    if (prev_item != nullptr)
        prev_item->push_next(next_item);
    if (next_item != nullptr)
        next_item->push_prev(prev_item);
    push_next(nullptr);
    push_prev(nullptr);
}


LinkedList::LinkedList() {
    list_head = nullptr;
    list_tail = nullptr;
}


LinkedList::LinkedList(double list_head_value) {
    list_head = nullptr;
    list_tail = nullptr;
    push_head(list_head_value);
}


LinkedList::~LinkedList() {
    list_head = nullptr;
    list_tail = nullptr;
}


void LinkedList::push_head(double val) {
    Item* elm = new Item(val);
    if (list_head == nullptr){
        list_head = elm;
        list_tail = elm;
    }
    else {
        elm->push_next(list_head);
        list_head->push_prev(elm);
        list_head = elm;
    }
}


void LinkedList::push_tail(double val) {
    Item* elm = new Item(val);
    if (list_head == nullptr){
        list_head = elm;
        list_tail = elm;
    } else {
        list_tail->push_next(elm);
        elm->push_prev(list_tail);
        list_tail = elm;
    }
}


Item* LinkedList::find_first(double val) {
    Item* item_idx = list_head;
    while (item_idx != nullptr){
        if (abs(item_idx->value - val) < COMPARATION_CONST) return item_idx;
        item_idx = item_idx->next();
    }
    return item_idx;
}


Item* LinkedList::pop(double val) {
    if (list_head == nullptr) return nullptr;
    Item* current = list_head;
    do {
        if (abs(current->value - val) < COMPARATION_CONST){
            if (current == list_head) list_head = current->next();
            if (current == list_tail) list_tail = current->prev();
            current->del_current();
            return current;
        }
        current = current->next();
    } while (current != nullptr);
    return nullptr;
}


Item* LinkedList::head() {
    return list_head;
}


Item* LinkedList::tail() {
    return list_tail;
}


void LinkedList::print() {
    if (head() == nullptr) return;
    std::cout << "The list_head is " << list_head->value << ";  the list_tail is " << list_tail->value << "\n";
    Item* current = list_head;
    while (current != nullptr){
        std::cout << current->value << "  ";
        if (current->prev() != nullptr) std::cout << "his prev is " << current->prev()->value << "  ";
        if (current->prev() != nullptr && current->next() != nullptr) std::cout << "and ";
        if (current->next() != nullptr) std::cout << "his next is " << current->next()->value;
        std::cout << "\n";
        current = current->next();
    }
    std::cout << "\n";
}


int main() {

    LinkedList A = LinkedList();
    A.push_head(10.1);
    A.print();

    LinkedList B = LinkedList(0.1);
    B.print();
    B.push_head(1.2);
    B.print();
    B.push_tail(2.3);
    B.print();

    if (B.find_first(0.1) != nullptr)
        std::cout << B.find_first(0.1)->value << "\n\n";

    B.pop(2.3);
    B.print();

    LinkedList C = LinkedList(1);

    return 0;
}
