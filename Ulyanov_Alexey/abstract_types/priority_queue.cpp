#include <iostream>

const double COMPARATION_CONST = 0.0001;


class item {

protected:
    int priority;  // наивысший приоритет есть минимальное число
    item *next;   // next последнего указывает на начало
    item *previous;

public:
    double value;

    item();
    item(const double x);
    item(const double x, const int p);
    item(const item& x);
    item(item&& x);
    ~item();

    item& operator=(const double& x);
    item& operator=(const item& x);

    friend std::ostream& operator<<(std::ostream& out, item x);

    void setNext(item* x);
    void setPrevios(item* x);

    int getPriority();
    item* getNext();
    item* getPrevios();

};

const item NULL_ITEM = item(0.0);


class Priority_queue {

protected:

    unsigned int size;
    item *head;

public:

    Priority_queue();
    Priority_queue(const double head_vle, const int prtet = 0);
    Priority_queue(const Priority_queue& x);
    Priority_queue(Priority_queue&& x);
    ~Priority_queue();

    Priority_queue& operator=(const Priority_queue& x);

    void add_head(const double vle, const int prtet = 0);
    void add_tail(const double vle, const int prtet = 0);
    void add(const double vle, const int prtet = 0);

    unsigned int contains(const double vle, const int prtet);
    void del(const double vle, const int prtet);  // вычленяет head, сокращая size на 1
    item get();

    item get_head();
    void output(bool show_data = false);

};



item::item() {  // is undefinded item;
    value = 0.0;
    next = nullptr;
    previous = nullptr;
    priority = 0;
}


item::item(const double x) {
    value = x;
    next = nullptr;
    previous = nullptr;
    priority = 0;
}


item::item(const double x, const int p) {
    value = x;
    priority = p;
    previous = nullptr;
    next = nullptr;
}


item::item(const item &x) {
    value = x.value;
    priority = x.priority;
    next = x.next;
    previous = x.previous;
}


item::item(item &&x) {
    value = x.value;
    priority = x.priority;
    next = x.next;
    previous = x.previous;

    x.value = 0.0;
    x.priority = 0;
    x.next = nullptr;
    x.previous = nullptr;
}


item::~item() {
    next = nullptr;
    previous = nullptr;
}


item& item::operator=(const double &x) {
    value = x;
    priority = 0;
    next = this;
    previous = this;
}


item& item::operator=(const item &x) {
    value = x.value;
    priority =  x.priority;
    next = x.next;
    previous = x.previous;
}


std::ostream& operator<<(std::ostream& out, item x) {
    out << x.value << "[" << x.getPriority() <<  "]\n\n";
    return (out);
}


int item::getPriority() {
    return priority;
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


Priority_queue::Priority_queue() {
    head = nullptr;
    size = 0;
}


Priority_queue::Priority_queue(const double head_value, const int prtet) {
    size = 0;
    add_head(head_value, prtet);
}


Priority_queue::~Priority_queue() {
    head = nullptr;
}


Priority_queue &Priority_queue::operator=(const Priority_queue &x) {
    head = x.head;
    size = x.size;
}


void Priority_queue::add_head(const double vle, const int prtet) {  // не добавит элемент с приоритетом, равным головному
    item* elm = new item(vle, prtet);
    if (size == 0){
        elm->setNext(elm);
        elm->setPrevios(elm);
        head = elm;
    } else {
        if (head->getPriority() >= prtet) return;

        head->getPrevios()->setNext(elm);
        elm->setNext(head);
        elm->setPrevios(head->getPrevios());
        head->setPrevios(elm);
        head = elm;
    }
    size++;
}


void Priority_queue::add_tail(const double vle, const int prtet) {
    item* elm = new item(vle, prtet);
    if (size == 0){
        elm->setNext(elm);
        elm->setPrevios(elm);
        head = elm;
    } else {
        if (head->getPrevios()->getPriority() > prtet) return;

        elm->setPrevios(head->getPrevios());
        elm->setNext(head);
        head->getPrevios()->setNext(elm);
        head->setPrevios(elm);
    }
    size++;
}


void Priority_queue::add(const double vle, const int prtet) {
    if (size == 0){
        add_head(vle, prtet);
        return;
    }
    item* elm = head;
    for (unsigned int idx = 0; idx < size; idx++){
        if (elm->getPriority() > prtet) break;
        elm = elm->getNext();
    }
    if (elm == head) {
        add_tail(vle, prtet);
        return;
    }
    item* new_elm = new item(vle, prtet);

    elm->getPrevios()->setNext(new_elm);
    new_elm->setPrevios(elm->getPrevios());
    elm->setPrevios(new_elm);
    new_elm->setNext(elm);

    size++;
}


unsigned int Priority_queue::contains(const double vle, const int prtet) {
    if (size == 0) return 0;

    item* elm = head;
    for (unsigned int idx = 0; idx < size; idx++){
        if ((abs(elm->value - vle) < COMPARATION_CONST) && (elm->getPriority() == prtet)){
            return idx + 1;
        }
        elm = elm->getNext();
    }
    return 0;
}


void Priority_queue::del(const double vle, const int prtet) {
    unsigned int point = contains(vle, prtet);
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


item Priority_queue::get() {
    if (size == 0) return item();

    item* rez = head;
    head->getPrevios()->setNext(head->getNext());
    head->getNext()->setPrevios(head->getPrevios());

    head = rez->getNext();
    size--;

    rez->setPrevios(nullptr);
    rez->setNext(nullptr);
    return *rez;
}


 item Priority_queue::get_head() {
    return *head;
}


void Priority_queue::output(bool show_data) {
    if (show_data){
        std::cout << "The chain's length: " << size << "\n";
    }
    if (size == 0) return;

    item* current = head;
    for (unsigned int idx = 0; idx < size; idx++){
        std::cout << current->value << "[" << current->getPriority() << "]   ";
        if (show_data){
            std::cout << "his previous is " << current->getPrevios()->value << "  and " <<
                         "his next is " << current->getNext()->value << "\n";
        }
        current = current->getNext();
    }
    std::cout << "\n";
}


int main() {

    Priority_queue A = Priority_queue();
    A.add_head(10.1, 1);
    A.output(true);


    Priority_queue B = Priority_queue(0.1);
    B.output(true);

    B.add(1.2, 1);
    B.add(2.3, 0);
    B.add_tail(3.4, 0);
    B.output(true);

    std::cout << B.get();
    B.output(true);

    B.add(4.5, 2);
    B.add(5.6, 1);
    B.output(true);

    B.del(2.3, 0);
    B.output(true);

    return 0;
}
