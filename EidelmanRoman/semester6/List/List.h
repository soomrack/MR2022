#ifndef MR2022_LIST_H
#define MR2022_LIST_H


class List {
private:

    class Node {
    public:
        Node* next;
        double data;

        Node(double data = 0.0, Node* next = nullptr) {
            this->data = data;
            this->next = next;
        }
    };
    unsigned int Size;
    Node* head;

public:

    List();
    ~List();

    void push_back(double data);
    void push_front(double data);
    void push_to(double data, int index);
    void pop_front();
    void pop_from(int index);
    void pop_back();
    void clear();
    unsigned int getSize() {
        return Size;
    };

    double& operator[](const int index);


};


List::List() {
    Size = 0;
    head = nullptr;
};


List::~List() {
    clear();
}


void List::pop_front() {

    Node* temp = head;

    head = head->next;

    delete temp;

    --Size;
}


void List::push_back(double data) {

    if (head == nullptr)
        head = new Node(data);
    else {
        Node* current = this->head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = new Node(data);
    }

    ++Size;
}


void List::push_front(double data) {
    head = new Node(data, head);
    ++Size;
}


void List::push_to(double data, int index) {
    if (index == 0) {
        push_front(data);
    }
    else {
        Node* previous = this->head;

        for (int i = 0; i < index - 1; ++i)
            previous = previous->next;

        Node* newNode = new Node(data, previous->next);
        previous->next = newNode;
        ++Size;
    }
}

void List::pop_from(int index) {
    if (index == 0) {
        pop_front();
    }
    else {
        Node* previous = this->head;

        for (int i = 0; i < index - 1; ++i)
            previous = previous->next;

        Node* fromDelete = previous->next;
        previous->next = fromDelete->next;
        --Size;
    }
}


void List::pop_back() {
    pop_from(Size - 1);
}


void List::clear() {
    while (Size) {
        pop_front();
    }
}


double& List::operator[](const int index) {

    int counter = 0;

    Node* current = this->head;

    while (current != nullptr) {
        if (counter == index) {
            return current->data;
        }
        current = current->next;
        ++counter;
    }
}


#endif
