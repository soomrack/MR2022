#include <iostream>

const double COMPARATION_CONST = 0.0001;

double abs(double x) {
    if (x < COMPARATION_CONST) return -x;
    return x;
}


class Unit {

protected:
    Unit* next_unit;
    Unit* prev_unit;

public:
    double value;

    Unit();
    Unit(const double x);
    Unit(const double val, Unit* his_next, Unit* his_prev);
    Unit(const Unit& x);
    Unit(Unit&& x);
    ~Unit();

    Unit& operator=(const double& x);
    Unit& operator=(const Unit& x);

    void push_next(Unit* x);
    void push_prev(Unit* x);

    Unit* next();
    Unit* prev();

    void del_cur();
};

class Linked_list{

protected:
    Unit* list_head;
    Unit* list_tail;

public:
    Linked_list();
    Linked_list(double list_head_val);
    ~Linked_list();

    void push_head(double val);
    void push_tail(double val);

    Unit* find_first(double val);
    Unit* pop(double val);

    void del_head();
    void del_tail();

    Unit* head();
    Unit* tail();

    void print(bool show_data = false);
};

Unit::Unit() {
    value = NULL;
    next_unit = nullptr;
    prev_unit = nullptr;
}

Unit::Unit(const double x) {
    value = x;
    next_unit = nullptr;
    prev_unit = nullptr;
}

Unit::Unit(const double val, Unit* his_next, Unit* his_prev) {
    value = val;
    next_unit = his_next;
    prev_unit = his_prev;
}

Unit::Unit(const Unit& x) {
    value = x.value;
    next_unit = x.next_unit;
    prev_unit = x.prev_unit;
}

Unit::Unit(Unit&& x) {
    value = x.value;
    next_unit = x.next_unit;
    prev_unit = x.prev_unit;

    x.value = 0;
    x.next_unit = nullptr;
    x.prev_unit = nullptr;
}

Unit::~Unit() {
    next_unit = nullptr;
    prev_unit = nullptr;
}

Unit& Unit::operator=(const double &x) {
    value = x;
}

Unit& Unit::operator=(const Unit &x) {
    value = x.value;
    next_unit = x.next_unit;
    prev_unit = x.prev_unit;
}

Unit* Unit::next() {
    return next_unit;
}

Unit* Unit::prev() {
    return prev_unit;
}

void Unit::push_next(Unit *x) {
    next_unit = x;
}

void Unit::push_prev(Unit *x) {
    prev_unit = x;
}

void Unit::del_cur(){
   if (prev_unit != nullptr) prev_unit->push_next(next_unit);
   if (next_unit != nullptr) next_unit->push_prev(prev_unit);

    push_next(nullptr);
    push_prev(nullptr);
}


Linked_list::Linked_list() {
    list_head = nullptr;
    list_tail = nullptr;
}

Linked_list::Linked_list(double list_head_val) {
    list_head = nullptr;
    list_tail = nullptr;

    push_head(list_head_val);
}

Linked_list::~Linked_list() {
    list_head = nullptr;
    list_tail = nullptr;
}

void Linked_list::push_head(double val) {
    Unit* elm = new Unit(val);
    if (list_head == nullptr) {
        list_head = elm;
        list_tail = elm;
    }
    else {
        elm->push_prev(list_head);
        list_head->push_next(elm);
        list_head = elm;
    }
}

void Linked_list::push_tail(double val) {
    Unit* elm = new Unit(val);
    if (list_tail == nullptr) {
        list_head = elm;
        list_tail = elm;
    }
    else {
        elm->push_next(list_tail);
        list_tail->push_prev(elm);
        list_tail = elm;
    }
}

Unit* Linked_list::find_first(double val) {
    Unit* idx = list_head;

    while(idx != nullptr) {
        if (abs(idx->value - val) < COMPARATION_CONST) return idx;
        idx = idx->prev();
    }
    return idx;
}

Unit* Linked_list::pop(double val) {
    if (list_head == nullptr) return nullptr;

    Unit* cur = list_head;

    do {
        if (abs(cur->value - val) < COMPARATION_CONST) {
            if (cur == list_head) list_head = cur->prev();
            if (cur == list_tail) list_tail = cur->next();
            cur->del_cur();
            return cur;
        }
        cur = cur->prev();
    } while (cur != nullptr);
    return nullptr;
}

void Linked_list::del_head() {
    if(list_head == list_tail) {
        list_head = nullptr;
        list_tail = nullptr;
        return;
    }

    list_head->prev()->push_next(nullptr);
    list_head = list_head->prev();
}

void Linked_list::del_tail() {
    if(list_head == list_tail) {
        list_head = nullptr;
        list_tail = nullptr;
        return;
    }

    list_tail->next()->push_prev(nullptr);
    list_tail = list_tail->next();
}

Unit* Linked_list::head() {
    return list_head;
}

Unit* Linked_list::tail() {
    return list_tail;
}

void Linked_list::print(bool show_data) {

    if (head() == nullptr) return;
    std::cout << "The list_head is " << list_head->value << ";  the list_tail is " << list_tail->value << "\n";

    Unit* current = list_head;
    while (current != nullptr){
        std::cout << current->value << "  ";
        if (show_data){
            if (current->prev() != nullptr) std::cout << "his prev is " << current->prev()->value << "  ";
            if (current->prev() != nullptr && current->next() != nullptr) std::cout << "and ";
            if (current->next() != nullptr) std::cout << "his next is " << current->next()->value;
            std::cout << "\n";
        }
        current = current->prev();
    };
    std::cout << "\n";
}

int main() {


    Linked_list B = Linked_list(0.1);
    B.push_head(7.7);
    B.push_tail(3.3);
    B.print(true);

//    if (B.find_first(0.1) != nullptr)
//       std::cout << B.find_first(0.1)->value << "\n\n";

    B.pop(0.1);
    B.print();



    return 0;
}
