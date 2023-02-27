#include <iostream>

const double COMPARATION_CONST = 0.0001;


class item {

protected:
    item *next;   // next последнего указывает на начало
    item *previous;

public:
    double value;

    item();
    item(const double x);
    item(const item& x);
    item(item&& x);
    ~item();

    item& operator=(const double& x);
    item& operator=(const item& x);

    void setNext(item* x);
    void setPrevios(item* x);

    item* getNext();
    item* getPrevios();

};

const item NULL_ITEM = item(0.0);


class Linked_list {

protected:

    unsigned int size;
    item *head;

public:

    Linked_list();
    Linked_list(double head_vle);
    Linked_list(const Linked_list& x);
    Linked_list(Linked_list&& x);
    ~Linked_list();

    Linked_list& operator=(const Linked_list& x);

    void add_head(double vle);
    void add_tail(double vle);
    void add(double vle, unsigned int position = 0);
    void add_next_to(double sup_vle, double new_vle);  // от support_value
    void add_previous_to(double sup_vle, double new_vle);

    unsigned int contains(double vle);
    void del(double vle);
    item get(double vle);

    item get_head();
    void output(bool show_data = false);

};



item::item() {  // is undefinded item;
    value = 0.0;
    next = nullptr;
    previous = nullptr;
}


item::item(const double x) {
    value = x;
    next = nullptr;
    previous = nullptr;
}


item::item(const item &x) {
    value = x.value;
    next = x.next;
    previous = x.previous;
}


item::item(item &&x) {
    value = x.value;
    next = x.next;
    previous = x.previous;

    x.value = 0.0;
    x.next = nullptr;
    x.previous = nullptr;
}


item::~item() {
    next = nullptr;
    previous = nullptr;
}


item& item::operator=(const double &x) {
    value = x;
    next = this;
    previous = this;
}


item& item::operator=(const item &x) {
    value = x.value;
    next = x.next;
    previous = x.previous;
}


item* item::getNext() {
    return next;
}


item* item::getPrevios() {
    return previous;
}


void item::setNext(item *x) {
    next = x;
}


void item::setPrevios(item *x) {
    previous = x;
}


Linked_list::Linked_list() {
    head = nullptr;
    size = 0;
}


Linked_list::Linked_list(double head_value) {
    size = 0;
    add_head(head_value);
}


Linked_list::~Linked_list() {
    head = nullptr;
}


Linked_list &Linked_list::operator=(const Linked_list &x) {
    head = x.head;
    size = x.size;
}


void Linked_list::add_head(double vle) {
    item* elm = new item(vle);
    if (size == 0){
        elm->setNext(elm);
        elm->setPrevios(elm);
        head = elm;
    } else {
        head->getPrevios()->setNext(elm);
        elm->setNext(head);
        elm->setPrevios(head->getPrevios());
        head->setPrevios(elm);
        head = elm;
    }
    size++;
}


void Linked_list::add_tail(double vle) {
    item* elm = new item(vle);
    if (size == 0){
        elm->setNext(elm);
        elm->setPrevios(elm);
        head = elm;
    } else {
        elm->setPrevios(head->getPrevios());
        elm->setNext(head);
        head->getPrevios()->setNext(elm);
        head->setPrevios(elm);
    }
    size++;
}


void Linked_list::add(double vle, unsigned int position) {
    if (position > size) return;
    if (position == 0){
        add_head(vle);
        return;
    }
    if (position == size){
        add_tail(vle);
        return;
    }

    item* elm = head;
    for (unsigned int idx = 0; idx < position; idx++){
        elm = elm->getNext();
    }
    item* new_item = new item(vle);

    elm->getPrevios()->setNext(new_item);
    new_item->setPrevios(elm->getPrevios());
    new_item->setNext(elm);
    elm->setPrevios(new_item);

    size++;
}


void Linked_list::add_next_to(double sup_vle, double new_vle) {
    unsigned int point = contains(sup_vle);
    if (point == 0) return;

    item* elm = head;
    for (unsigned int idx = 1; idx < point; idx++){
        elm = elm->getNext();
    }

    item* new_elm = new item(new_vle);
    elm->getNext()->setPrevios(new_elm);
    new_elm->setNext(elm->getNext());
    elm->setNext(new_elm);
    new_elm->setPrevios(elm);

    size++;
}


void Linked_list::add_previous_to(double sup_vle, double new_vle) {
    unsigned int point = contains(sup_vle);
    if (point == 0) return;

    if (point == 1){
        add_head(new_vle);
        return;
    }
    item* elm = head;
    for (unsigned int idx = 1; idx < point - 1; idx++){
        elm = elm->getNext();
    }

    item* new_elm = new item(new_vle);
    elm->getNext()->setPrevios(new_elm);
    new_elm->setNext(elm->getNext());
    elm->setNext(new_elm);
    new_elm->setPrevios(elm);

    size++;
}


unsigned int Linked_list::contains(double vle) {
    if (size == 0) return 0;

    item* elm = head;
    for (unsigned int idx = 0; idx < size; idx++){
        if (abs(elm->value - vle) < COMPARATION_CONST){
            return idx + 1;
        }
        elm = elm->getNext();
    }
    return 0;
}


void Linked_list::del(double vle) {
    unsigned int point = contains(vle);
    if (point == 0) return;

    item* elm = head;
    for (unsigned int idx = 1; idx < point; idx++){
        elm = elm->getNext();
    }

    elm->getPrevios()->setNext(elm->getNext());
    elm->getNext()->setPrevios(elm->getPrevios());
    if (point == 1) head = elm->getNext();
    size--;
}


item Linked_list::get(double vle) {
    if (size == 0) return NULL_ITEM;

    item* elm = head;
    for (unsigned int idx = 0; idx < size; idx++){
        if (abs(elm->value - vle) < COMPARATION_CONST){
            return *elm;
        }
        elm = elm->getNext();
    }
    return NULL_ITEM;
}


item Linked_list::get_head() {
    return *head;
}


void Linked_list::output(bool show_data) {
    if (show_data){
        std::cout << "The chain's length: " << size << "\n";
    }
    if (size == 0) return;

    item* current = head;
    for (unsigned int idx = 0; idx < size; idx++){
        std::cout << current->value << "  ";
        if (show_data){
            std::cout << "his previous is " << current->getPrevios()->value << "  and " <<
                      "his next is " << current->getNext()->value << "\n";
        }
        current = current->getNext();
    }
    std::cout << "\n";
}


int main() {

    Linked_list A = Linked_list();
    A.add_head(10.1);
    A.output(true);
    A.del(10.1);
    A.output(true);


    Linked_list B = Linked_list(0.1);
    B.output(true);

    B.add_head(1.2);
    B.output(true);

    B.add_tail(2.3);
    B.output(true);

    B.add(9.9, 2);
    B.output(true);

    B.del(1.2);
    B.output(true);

    B.add_next_to(2.3, 3.4);
    B.output(true);

    B.add_previous_to(0.1, 4.5);
    B.output(true);

    std::cout << B.get(10.9).value << "\n";

    return 0;
}
