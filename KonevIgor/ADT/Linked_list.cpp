#include <iostream>
#include <stdexcept>
#include <string>

class Linked_list_exception: public std::logic_error
{
public:
    explicit Linked_list_exception(const std::string& message):
            std::logic_error(message)
    {}
};

template<typename N>
class Node {
public:
    explicit Node(N data = N(), Node* next = nullptr) {
        this->data = data;
        this->next = next;
    }

    N data;
    Node* next;
};

template<typename T>
class Linked_list {

private:

    size_t size;
    Node<T>* head;

public:
    Linked_list();
    Linked_list(const Linked_list&);
    ~Linked_list();

    Linked_list& operator=(const Linked_list&);
    bool operator==(const Linked_list&);
    bool operator!=(const Linked_list& other) {return !(this == other);}

    void push_head(T elem);
    void push_tail(T elem);
    void push_elem(T elem, size_t idx);
    void pop_elem(size_t idx);
    void pop_head();
    void pop_tail();

    void clear();
    size_t get_size() const {return size;}
    T& operator[](size_t n);
    void print();

};

template<typename T>
Linked_list<T>::Linked_list():
    size(0),
    head(nullptr)
{}

template<typename T>
Linked_list<T>::Linked_list(const Linked_list& other):
    size(0),
    head(nullptr)
{
    Node<T>* temp = other.head;
    while (temp != nullptr) {
        push_tail(temp->data);
        temp = temp->next;
    }
}

template<typename T>
Linked_list<T> &Linked_list<T>::operator=(const Linked_list& other) {
    if (this == &other) {
        return *this;
    }
    Linked_list temp(other);
    std::swap(this->size, temp.size);
    std::swap(this->head, temp.head);
    return *this;
}

template<typename T>
void Linked_list<T>::clear() {
    while (size) pop_head();
}

template<typename T>
Linked_list<T>::~Linked_list() {
    clear();
}

template<typename T>
void Linked_list<T>::push_head(T elem) {
    if (head == nullptr) {
        head = new Node<T>(elem);
    } else {
        Node<T>* temp = head;
        head = new Node<T>(elem, temp);
    }
    size++;
}

template<typename T>
void Linked_list<T>::push_tail(T elem) {
    if (head == nullptr) {
        head = new Node<T>(elem);
    } else {
        Node<T>* temp = this->head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = new Node<T>(elem);
    }
    size++;
}

template<typename T>
void Linked_list<T>::push_elem(T elem, size_t idx) {
    if (idx > size) throw Linked_list_exception("Linked list out of bounds!");
    if (head == nullptr) {
        head = new Node<T>(elem);
    } else {
        Node<T>* temp = this->head;
        size_t num = 1;
        while (num < idx) {
            temp = temp->next;
            num++;
        }
        temp->next = new Node<T>(elem, temp->next);
    }
    size++;
}

template<typename T>
void Linked_list<T>::pop_elem(size_t idx) {
    if (idx > size) throw Linked_list_exception("Linked list out of bounds!");
    if (head == nullptr) {
        throw Linked_list_exception("Linked list is empty!");
    } else {
        Node<T>* temp = this->head;
        Node<T>* temp_last = temp;
        size_t num = 0;
        while (num < idx) {
            temp_last = temp;
            temp = temp->next;
            num++;
        }
        temp_last->next = temp->next;
        delete[] temp;
    }
    size--;
}

template<typename T>
void Linked_list<T>::pop_head() {
    if (head == nullptr)
        throw Linked_list_exception("Linked list is empty!");
    Node<T>* temp = head;
    head = head->next;
    delete[] temp;
    size--;
}

template<typename T>
void Linked_list<T>::pop_tail() {
    if (head == nullptr)
        throw Linked_list_exception("Linked list is empty!");
    Node<T>* temp = head;
    Node<T>* temp_last = temp;
    while (temp->next != nullptr) {
        temp_last = temp;
        temp = temp->next;
    }
    delete[] temp;
    temp_last->next = nullptr;
    // нужно ли стирать данные из предыдущего "хвоста"?
    size--;
    if (!size) head = nullptr;
}

template<typename T>
bool Linked_list<T>::operator==(const Linked_list& other) {
    if (this == &other) {
        return true;
    }
    if (this->size != other.size) {
        return false;
    }
    if (this->head != other.head) {
        return false;
    }
    return true;
}

template<typename T>
T &Linked_list<T>::operator[](const size_t n) {
    size_t i = 0;
    Node<T>* temp = this->head;
    while (i < n) {
        temp = temp->next;
        if (temp == nullptr)
            throw Linked_list_exception("Linked list out of bounds!");
        i++;
    }
    return temp->data;
}

template<typename T>
void Linked_list<T>::print() {
    if (head == nullptr)
        throw Linked_list_exception("Linked list is empty!");
    Node<T>* temp = this->head;
    while (temp != nullptr) {
        std::cout << temp->data << "\t";
        temp = temp->next;
    }
    std::cout << std::endl;
}

int main() {
    Linked_list<int> test;
    for (size_t idx = 0; idx < 5; idx++) {
        test.push_head((int)(2 * idx));
    }
    test.print();
    test.push_elem(9, 3);
    test.print();
    test.pop_elem(2);
    test.print();
    Linked_list<int> test2(test);
    for (size_t idx = 0; idx < 5; idx++) {
        test2.push_tail((int)(5 * idx));
    }
    test2.print();
    for (size_t idx = 0; idx < 3; idx++) {
        test2.pop_head();
    }
    for (size_t idx = 0; idx < 3; idx++) {
        test2.pop_tail();
    }
    test2.print();
    std::cout << test2.get_size() << std::endl;
    test.clear();
    std::cout << test2[2] << std::endl;
    return 0;
}