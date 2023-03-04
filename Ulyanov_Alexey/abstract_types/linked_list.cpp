#include <iostream>

const double COMPARATION_CONST = 0.0001;  // ???


double abs(double x){
    if (x < COMPARATION_CONST) return -x;
    return x;
}


class Item {

protected:
    Item *Next;
    Item *Prev;

public:
    double value;

    Item();
    Item(const double x);
    Item(const Item& x);
    Item(Item&& x);
    ~Item();

    Item& operator=(const double& x);
    Item& operator=(const Item& x);

    void SetNext(Item* x);
    void SetPrevios(Item* x);

    Item* GetNext();
    Item* GetPrev();

};

const Item NULL_ITEM = Item(0.0);


class LinkedList {

protected:

    Item *head;
    Item *tail;
    unsigned int size;

    void Add(double val, unsigned int position);

public:

    LinkedList();
    LinkedList(double head_val);
    ~LinkedList();

    void AddHead(double val);
    void AddTail(double val);

    void AddNextTo(double sup_val, double new_val);
    void AddPrevTo(double sup_val, double new_val);

    unsigned int Contains(double val);
    void Del(double val);
    //void Del(Item* elm);  а нужен он?
    Item Get(double val);

    Item GetHead();
    Item GetTail();
    void Output(bool show_data = false);

};



Item::Item() {  // is undefinded Item;
    value = NULL;
    Next = nullptr;
    Prev = nullptr;
}


Item::Item(const double x) {
    value = x;
    Next = nullptr;
    Prev = nullptr;
}


Item::Item(const Item &x) {
    value = x.value;
    Next = x.Next;
    Prev = x.Prev;
}


Item::Item(Item &&x) {
    value = x.value;
    Next = x.Next;
    Prev = x.Prev;

    x.value = 0.0;
    x.Next = nullptr;
    x.Prev = nullptr;
}


Item::~Item() {
    Next = nullptr;
    Prev = nullptr;
}


Item& Item::operator=(const double &x) {
    value = x;
    Next = this;
    Prev = this;
}


Item& Item::operator=(const Item &x) {
    value = x.value;
    Next = x.Next;
    Prev = x.Prev;
}


Item* Item::GetNext() {
    return Next;
}


Item* Item::GetPrev() {
    return Prev;
}


void Item::SetNext(Item *x) {
    Next = x;
}


void Item::SetPrevios(Item *x) {
    Prev = x;
}


LinkedList::LinkedList() {
    head = nullptr;
    size = 0;
}


LinkedList::LinkedList(double head_value) {
    size = 0;
    AddHead(head_value);
}


LinkedList::~LinkedList() {
    head = nullptr;
    tail = nullptr;
}


void LinkedList::AddHead(double val) {
    Item* elm = new Item(val);
    if (size == 0){
        head = elm;
        tail = elm;
    } else {
        elm->SetNext(head);
        head->SetPrevios(elm);
        head = elm;
    }
    size++;
}


void LinkedList::AddTail(double val) {
    Item* elm = new Item(val);
    if (size == 0){
        head = elm;
        tail = elm;
    } else {
        tail->SetNext(elm);
        elm->SetPrevios(tail);
        tail = elm;
    }
    size++;
}


void LinkedList::Add(double val, unsigned int position) {
    if (position > size) return;
    if (position == 0){
        AddHead(val);
        return;
    }
    if (position == size){
        AddTail(val);
        return;
    }

    Item* elm = head;
    for (unsigned int idx = 0; idx < position; idx++){
        elm = elm->GetNext();
    }
    Item* new_item = new Item(val);

    elm->GetPrev()->SetNext(new_item);
    new_item->SetPrevios(elm->GetPrev());
    new_item->SetNext(elm);
    elm->SetPrevios(new_item);

    size++;
}


void LinkedList::AddNextTo(double sup_val, double new_val) {
    unsigned int point = Contains(sup_val);
    if (point == 0) return;

    Add(new_val, point);
}


void LinkedList::AddPrevTo(double sup_val, double new_val) {
    unsigned int point = Contains(sup_val);
    if (point == 0) return;

    Add(new_val, point - 1);
}


unsigned int LinkedList::Contains(double val) {
    if (size == 0) return 0;

    Item* elm = head;
    for (unsigned int idx = 0; idx < size; idx++){
        if (abs(elm->value - val) < COMPARATION_CONST){
            return idx + 1;
        }
        elm = elm->GetNext();
    }
    return 0;
}


void LinkedList::Del(double val) {
    unsigned int point = Contains(val);
    if (point == 0) return;

    Item* elm = head;
    for (unsigned int idx = 1; idx < point; idx++){
        elm = elm->GetNext();
    }

    if (size == 1){
        head = nullptr;
        tail = nullptr;

    } else {
        if (point == 1)
            head = elm->GetNext();
        else
            elm->GetPrev()->SetNext(elm->GetNext());

        if (point == size)
            tail = elm->GetPrev();
        else
            elm->GetNext()->SetPrevios(elm->GetPrev());
    }

    delete elm;
    size--;
}


Item LinkedList::Get(double val) {
    if (size == 0) return NULL_ITEM;

    Item* elm = head;
    for (unsigned int idx = 0; idx < size; idx++){
        if (abs(elm->value - val) < COMPARATION_CONST){
            return *elm;
        }
        elm = elm->GetNext();
    }
    return NULL_ITEM;
}


Item LinkedList::GetHead() {
    return *head;
}


Item LinkedList::GetTail() {
    return *tail;
}


void LinkedList::Output(bool show_data) {
    if (show_data){
        std::cout << "The chain's length: " << size << "\n";
    }
    if (size == 0) return;
    std::cout << "The head is " << head->value << ";  the tail is " << tail->value << "\n";

    Item* current = head;
    for (unsigned int idx = 0; idx < size; idx++){
        std::cout << current->value << "  ";
        if (show_data){
            if (current->GetPrev() != nullptr) std::cout << "his Prev is " << current->GetPrev()->value << "  ";
            if (current->GetPrev() != nullptr && current->GetNext() != nullptr) std::cout << "and ";
            if (current->GetNext() != nullptr) std::cout << "his Next is " << current->GetNext()->value;
            std::cout << "\n";
        }
        current = current->GetNext();
    }
    std::cout << "\n";
}


int main() {

    LinkedList A = LinkedList();
    A.AddHead(10.1);
    A.Output(true);
    A.Del(10.1);
    A.Output(true);

    LinkedList B = LinkedList(0.1);
    B.Output(true);

    B.AddHead(1.2);
    B.Output(true);

    B.AddTail(2.3);
    B.Output(true);

//    B.Add(9.9, 2);  теперь не работает так как
//    B.Output(true);

    B.Del(2.3);
    B.Output(true);

    B.AddNextTo(9.9, 3.4);
    B.Output(true);

    B.AddPrevTo(0.1, 4.5);
    B.Output(true);

    std::cout << B.Get(9.9001).value << "\n";

    return 0;
}
