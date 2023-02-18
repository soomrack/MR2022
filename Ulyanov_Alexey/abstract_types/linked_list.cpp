#include <iostream>

const double COMPARATION_CONST = 0.0001;

class Linked_list {

public:

    class element {

    protected:
        element * next;   // next последнего указывает на начало
        element * previous;


    public:
        double value;

        element();
        element(const double x);
        element(const element& x);
        element(element&& x);
        ~element();

        element& operator=(const double& x);
        element& operator=(const element& x);

        void setNext(element* x);
        void setPrevios(element* x);

        element* getNext();
        element* getPrevios();

    };

protected:

    unsigned int size;
    element* data;

public:

    Linked_list();
    Linked_list(element head);
    Linked_list(const Linked_list& x);
    Linked_list(Linked_list&& x);
    ~Linked_list();

    Linked_list& operator=(const Linked_list& x);

    void add_tail(element elm);
    unsigned int contains(double vle);
    void del(double vle);
    element get(double vle);
    void add(element elm, unsigned int position = 0);

    void output(bool show_data = false);

};


const Linked_list::element UNDEFINDED_ELEMENT = Linked_list::element(0.0);


Linked_list::element::element() {
    value = 0.0;
    next = nullptr;
    previous = nullptr;
}


Linked_list::element::element(const double x) {
    value = x;
    next = this;
    previous = this;
}


Linked_list::element::element(const Linked_list::element &x) {
    value = x.value;
    next = x.next;
    previous = x.previous;
}


Linked_list::element::element(Linked_list::element &&x) {
    value = x.value;
    next = x.next;
    previous = x.previous;

    x.value = 0.0;
    x.next = nullptr;
    x.previous = nullptr;
}


Linked_list::element::~element() {
    next = nullptr;
    previous = nullptr;
}


Linked_list::element& Linked_list::element::operator=(const double &x) {
    value = x;
    next = nullptr;
    previous = nullptr;
}


Linked_list::element& Linked_list::element::operator=(const element &x) {
    value = x.value;
    next = x.next;
    previous = x.previous;
}


Linked_list::element* Linked_list::element::getNext() {
    return next;
}


Linked_list::element* Linked_list::element::getPrevios() {
    return previous;
}


void Linked_list::element::setNext(Linked_list::element *x) {
    next = x;
}


void Linked_list::element::setPrevios(Linked_list::element *x) {
    previous = x;
}


Linked_list::Linked_list() {
    size = 0;
    data = nullptr;
}


Linked_list::Linked_list(element head) {
    size = 1;
    data = new element[size];
    data[0] = head;
}


Linked_list::Linked_list(const Linked_list& x) {
    size = x.size;
    data = new element[size];

    for (unsigned int idx = 0; idx < x.size; idx++){
        data[idx] = x.data[idx];
    }
}


Linked_list::Linked_list(Linked_list &&x) {
    size = x.size;
    data = x.data;

    x.size = 0;
    x.data = nullptr;
}


Linked_list::~Linked_list() {
    delete[] data;
}


Linked_list &Linked_list::operator=(const Linked_list &x) {
    if (this != &x){
        if (!data)
            delete[] data;

        size = x.size;

        this->data = new element[size];
        for (unsigned int idx = 0; idx < size; idx++){
            data[idx] = x.data[idx];
        }
    }

    return *this;
}


void Linked_list::add_tail(Linked_list::element elm) {
    Linked_list::element* temp = new Linked_list::element[size + 1];
    for (unsigned int idx = 0; idx < size; idx++){
        temp[idx] = data[idx];
    }
    delete[] data;
    data = temp;
    data[size] = elm;

    data[size - 1].setNext(&data[size]);
    data[size].setPrevios(&data[size - 1]);

    data[size].setNext(&data[0]);
    data[0].setPrevios(&data[size++]);
}


unsigned int Linked_list::contains(double vle) {
    for (unsigned int idx = 0; idx < size; idx++){
        if (abs(data[idx].value - vle) < COMPARATION_CONST){
            return idx + 1;
        }
    }
    return 0;
}


void Linked_list::del(double vle) {
    unsigned int point = contains(vle);
    if (point == 0) return;

    if (point == size){
        data[point - 2].setNext(&data[0]);
        data[0].setPrevios(&data[point - 2]);
    } else if (point == 1){
        data[size - 1].setNext(&data[point]);
        data[point].setPrevios(&data[size - 1]);
    } else {
        data[point - 2].setNext(&data[point]);
        data[point].setPrevios(&data[point - 2]);
    }

    element *temp = new element [size - 1];
    for (unsigned int idx = 0; idx < point - 1; idx++){
        temp[idx] = data[idx];
    }
    for (unsigned int idx = point; idx < size; idx++){
        temp[idx - 1] = data[idx];
    }
    //delete[] data;
    data = temp;
    size--;
}


Linked_list::element Linked_list::get(double vle) {
    unsigned int point = contains(vle);
    if (point == 0) return UNDEFINDED_ELEMENT;
    return data[point - 1];
}


void Linked_list::add(Linked_list::element elm, unsigned int position) {
    if (position >= size) return;

}


void Linked_list::output(bool show_data) {
    for (unsigned int idx = 0; idx < size; idx++){
        std::cout << data[idx].value << " ";
        if (show_data){
            std::cout << "  his previous is " << data[idx].getPrevios()->value <<
                         " and his next is " << data[idx].getNext()->value << "\n";
        }
    }
    std::cout << "\n";
}


int main() {
    Linked_list A;
    Linked_list B(Linked_list::element(5.1));
    B.output(true);

    Linked_list::element x = Linked_list::element(6.5);
    B.add_tail(x);
    x = 6.7;
    B.add_tail(x);

    B.output(true);

    B.del(6.7);

    B.output(true);

    return 0;
}
