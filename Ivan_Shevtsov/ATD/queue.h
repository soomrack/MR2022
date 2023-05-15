#ifndef ATD_QUEUE_H
#define ATD_QUEUE_H

#include <iostream>


namespace queue_names {
    /**
    * @brief myQueue container
    *
    * use try/catch for work with Queue
    * @class queue_exceptions has these exceptions(objects):
    *
    * @objects queue_exceptions ZERO_SIZE("zero size error");
    * @objects queue_exceptions QUEUE_OUT_OF_TRE_RANGE("index out of the range");
    * @objects queue_exceptions QUEUE_POP_ERROR("can`t pop from empty queue");
    * @objects queue_exceptions QUEUE_SHOW_ERROR("can`t show zero size queue");
    */

    class queue_exceptions: public std::domain_error{
    public:
        queue_exceptions(const char* massage): std::domain_error(massage){}
    };

    template<typename T>
    class Node {
    public:
        Node<T> *p_next;
        Node<T> *p_prev;
        T data;

        Node();
        Node(T data);
        Node(T data, Node *p_next, Node *p_prev);
        ~Node();

        void push_next(Node *other);
        void push_prev(Node *other);

        bool operator==(Node<T> const& other);
    };

    template<typename T>
    class queue {
    private:
        unsigned size;
        Node<T> *p_tail;
        Node<T> *p_head;
    public:
        queue();
        ~queue();

        void show();
        void clear();
        bool is_empty(){ return (p_head == nullptr);};

        void push(T data);
        void pop();

        Node<T> *front() { return p_head; }
        Node<T> *back() { return p_tail; }

        bool value_in_queue(T value);
        T get_element(unsigned element_number);  // element number starting from 0
    };

    template<typename T>
    bool queue<T>::value_in_queue(T value) {
        auto current_pointer = p_head;
        while (true){
            if (current_pointer->data == value)
                return true;
            current_pointer = current_pointer->p_next;
            if (current_pointer == nullptr){
                break;
            }
        }
        return false;
    }

    template<typename T>
    queue<T>::queue() {
        size = 0;
        p_head = nullptr;
        p_head= nullptr;
    }

    template<typename T>
    void queue<T>::clear() {
        while (size) { pop(); }
        p_head = nullptr;
        p_tail = nullptr;
    }

    template<typename T>
    queue<T>::~queue() {
        clear();
    }

    template<typename T>
    void queue<T>::pop() {
        if (p_head == nullptr) {
            queue_exceptions QUEUE_POP_ERROR("can`t pop from empty queue");
            throw QUEUE_POP_ERROR;
        }
        if (p_head->p_prev == nullptr)    {
            delete p_head;
            p_head = nullptr;
            p_tail = nullptr;
            size--;
            return;
        }
        p_head = p_head->p_prev;
        delete p_head->p_next;
        p_head->p_next = nullptr;

        size--;
    }

    template<typename T>
    void queue<T>::push(T data) {
        if (p_head == nullptr and p_tail == nullptr){
            Node<T>* first_node = new Node<T>(data, nullptr, nullptr);
            p_head = first_node;
            p_tail = first_node;
            size++;
            return;
        }
        Node<T>* new_node = new Node<T>(data, p_tail, nullptr);
        p_tail->push_next(new_node);
        p_tail = new_node;
        size++;
    }

    template<typename T>
    void queue<T>::show() {
        if (p_head == nullptr) {
            queue_exceptions QUEUE_SHOW_ERROR("can`t show zero size queue");
            throw QUEUE_SHOW_ERROR; }
        Node<T>* running_pointer = p_head;
        while (running_pointer != nullptr){
            std::cout << running_pointer->data << "\t";
            running_pointer = running_pointer->p_next;
        }
        std::cout  << "\n";

    }

    template<typename T>
    T queue<T>::get_element(unsigned int element_number) {
        if (element_number >= size) {
            queue_exceptions QUEUE_OUT_OF_THE_RANGE("index out of the range");
            throw QUEUE_OUT_OF_THE_RANGE; }
        if (size == 0) {
            queue_exceptions ZERO_SIZE("zero size error");
            throw ZERO_SIZE; }

        Node<T>* running_pointer = p_head;
        for (unsigned counter = 1; counter <= element_number; counter++){
            running_pointer = running_pointer->p_prev;
        }
        return running_pointer->data;
    }

    template<typename T>
    Node<T>::Node() {
        p_next = nullptr;
        p_prev = nullptr;
        data = T();
    }

    template<typename T>
    bool Node<T>::operator==(const Node<T> &other) {
        return data == other.data;
    }


    template<typename T>
    Node<T>::Node(T data) {
        p_next = nullptr;
        p_prev = nullptr;
        this->data = data;
    }

    template<typename T>
    void Node<T>::push_next(Node *other) {
        this->p_prev = other;
        other->p_next = this;
    }

    template<typename T>
    Node<T>::Node(T data, Node *p_next, Node *p_prev) {
        this->p_next = p_next;
        this->p_prev = p_prev;
        this->data = data;
    }

    template<typename T>
    void Node<T>::push_prev(Node *other) {
        other->p_prev = this;
        this->p_next = other;
    }

    template<typename T>
    Node<T>::~Node() {
        p_next = nullptr;
        p_prev = nullptr;
    }



}
#endif //ATD_QUEUE_H
