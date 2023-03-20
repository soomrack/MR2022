//
// use try/catch for work with it
//

#ifndef ATD_LIST_H
#define ATD_LIST_H

template<typename T>
class Node{
public:
    T data;
    Node* p_next;

    Node(T data = T(), Node* p_next = nullptr)
    {
        this->data =  data;
        this->p_next = p_next;
    }
    T* next;
};

template<typename T>
class list {
public:
    list();
    list(list& other);

    void clear();
    void push_front(T data);
    void pop_front();
    int lenght(){ return size; }

    void push_back(T data);
    void removeEl(int idx);
    void pop_back();
    void insert(T value, int idx);

    T& operator[] (const int idx);
    bool operator==(const list& other);
    bool operator!=(const list& other);

    ~list();
private:
    int size;
    Node<T>* head;
};



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
void list<T>::push_back(T data) {
    if (head == nullptr)
    {
        head = new Node<T>(data);
    }
    else
    {
        Node<T>* current_node = head;
        while (current_node->p_next != nullptr)
        {
            current_node = current_node->p_next;
        }
        current_node->p_next = new Node<T>(data);
    }
    size++;
}

template<typename T>
T& list<T>::operator[] (const int idx)
{
    if (size == 0)
        throw ZERO_SIZE;
    else if (idx >= size)
        throw OUT_OF_TRE_RANGE_1;
    else if (idx < 0)
        throw std::runtime_error("index can`t be less zero");

    Node<T>* current_node = head;
    int counter = 0;
    while (current_node != nullptr)
    {
        if (counter == idx)
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
void list<T>::pop_back() {
    if (head == nullptr)
        throw std::runtime_error("can`t pop zero size list");
    Node<T>* current_node = head;
    for(int idx = 1; idx < size; idx++)
        current_node = current_node->p_next;
    delete current_node;
    size--;
}

template<typename T>
void list<T>::insert(T value, int idx) {
    if (size == 0)  // i know, that it contained in next con
        throw std::runtime_error("can`t insert from zero size list");
    else if (idx > size or idx < 0)
        throw std::runtime_error("index out of the range(insert)");
    else if (idx == 0)
        push_front(value);
    else {
        Node<T> *current_node = head;
        for (int cur_idx = 0; cur_idx != idx - 1; cur_idx++)  // move to [idx - 1] node (prev)
        {
            current_node = current_node->p_next;
        }

        current_node->p_next = new Node<T>(value, current_node->p_next);
    }
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
        for (int idx = 1; idx < other.size; idx++) {
            current_node->p_next = new Node<T>(other[idx]);
            current_node = current_node->p_next;
        }
    }
}

template<typename T>
void list<T>::removeEl(int idx) {
    if (size == 0)  // i know, that it contained in next con
        throw std::runtime_error("can`t remove from zero size list");
    else if (idx > size or idx < 0)
        throw std::runtime_error("index out of the range(remove)");
    else if (idx == 0)

        pop_front();
    else {
        Node<T>* prev = head;
        for (int cur_idx = 0; cur_idx != idx - 1; cur_idx++)  // move to [idx - 1] node (prev)
        {
            prev = prev->p_next;
        }

        Node<T>* del_node = prev->p_next;
        prev->p_next = del_node->p_next;
        delete del_node;
        size--;
    }
}

template<typename T>
bool list<T>::operator==(const list &other) {
    if (size != other.size)
        throw std::runtime_error("for comparison lists mast have equal length");

    Node<T>* first_current = this->head;
    Node<T>* second_current = this->head;

    for (int idx = 0; idx < size; idx++) {
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


