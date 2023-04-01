//
// use try/catch for work with it
//

#ifndef ATD_LIST_H
#define ATD_LIST_H
#include "iostream"

#ifndef exceptions  // Q: how to dell this shit
#define exceptions
class common_exc: public std::domain_error{
public:
    common_exc(const char* massage): std::domain_error(massage){}
};
common_exc LIST_ZERO_SIZE("zero size error");
common_exc OUT_OF_TRE_RANGE_1("index out of the range(operator [])");
common_exc CANT_ADD_ELEMENT("can`t add element in empty list");
#endif

template<typename T>
class Node{
public:
    T data;
    Node* p_next;

    void add_next(T data, Node* head);
    void del_next();

    Node(T data = T(), Node* p_next = nullptr)
    {
        this->data =  data;
        this->p_next = p_next;
    }
};

template<typename T>
class list {
private:
    unsigned int size;
    Node<T>* head;

public:
    list();
    list(list& other);
    list(T* array, unsigned array_length);

    void clear();
    void push_front(T data);
    void pop_front();
    int lenght(){ return size; }

    T& operator[] (const unsigned num);
    bool operator==(const list& other);
    bool operator!=(const list& other);

    void TEST();



    ~list();

};

template<typename T>
void list<T>::TEST() {
    head->add_next(10, head);

    size++;
    //#TODO
    /*head->p_next->add_next(100, head);
    size++;*/
    std::cout << "TEST WORK\n";
}

template<typename T>
void Node<T>::del_next() {
    Node* tmp = this->p_next;
    delete this->p_next;
    this->p_next = tmp;
}

template<typename T>
void Node<T>::add_next(T data, Node* head) {
    if (head == nullptr)
    {
        Node<T>* new_node = new Node<T>(data, head);
        head = new_node;
    }
    else{
        Node<T>* new_node = new Node<T>(data, this->p_next);
        this->p_next = new_node;
    }


}

template<typename T>
list<T>::list(T *array, unsigned int array_length) {

}


template<class T>
list<T>::list()
{
    size = 0;
    head = nullptr;
}

template<typename T>
list<T>::~list()
{
    clear();
}

template<typename T>
T& list<T>::operator[] (const unsigned num)
{
    if (size == 0)
        throw LIST_ZERO_SIZE;
    else if (num >= size)
        throw OUT_OF_TRE_RANGE_1;
    else if (num < 0)
        throw std::runtime_error("index can`t be less zero");

    Node<T>* current_node = head;
    int counter = 0;
    while (current_node != nullptr)
    {
        if (counter == num)
            return current_node->data;
        current_node = current_node->p_next;
        counter++;
    }
}

template<typename T>
void list<T>::pop_front() {
    if (size == 0)
        throw std::runtime_error("can`t pop zero size list");

    Node<T> *tmp = head;
    head = head->p_next;
    delete tmp;

    size--;
}

template<typename T>
void list<T>::clear()
{
    while (size)
        pop_front();
}

template<typename T>
void list<T>::push_front(T data) {
    Node<T>* new_node = new Node<T>(data, head);
    head = new_node;

    size++;
}

template<typename T>
list<T>::list(list &other) {
    this->size = other.size;
    if (other.head == nullptr)
    {
        this->head = nullptr;
    }
    else {
        head = new Node<T>(other.head->data);

        Node<T> *current_node = head;
        for (unsigned idx = 1; idx < other.size; idx++) {
            current_node->p_next = new Node<T>(other[idx]);
            current_node = current_node->p_next;
        }
    }
}

template<typename T>
bool list<T>::operator==(const list &other) {
    if (size != other.size)
        throw std::runtime_error("for comparison lists mast have equal length");

    Node<T>* first_current = this->head;
    Node<T>* second_current = this->head;

    for (unsigned idx = 0; idx < size; idx++) {
        if (first_current->data != second_current->data)
            return false;
        first_current = first_current->p_next;
        second_current = second_current->p_next;
    }

    return true;
}

template<typename T>
bool list<T>::operator!=(const list &other) {
    return !(this == other);
}



#endif //ATD_LIST_H


