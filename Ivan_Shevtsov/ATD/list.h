#ifndef ATD_LIST_H
#define ATD_LIST_H
#include <iostream>

namespace list_names {
    class list_exceptions: public std::domain_error{
    public:
        list_exceptions(const char* massage): std::domain_error(massage){}
    };

/*    list_exceptions ZERO_SIZE("zero size error");
    list_exceptions OUT_OF_THE_RANGE("index out of the range(operator [])");
    list_exceptions SHOW_ERROR("can`t show zero size list");
    list_exceptions DELL_AFTER_OUT_OF_THE_RANGE("index out of the range(delete operation)");
    list_exceptions DELL_AFTER_LAST("can`t delete after last element");
    list_exceptions POP_ERROR("can`t pop from empty list");
    list_exceptions INSERT_AFTER_OUT_OF_THE_RANGE("index out of the range(insert operation)");
    list_exceptions INSERT_WARNING("[WARNING] list was empty and you wanted to add zero position element. "
                                   "List was created and data pushed");*/


    template<typename T>
    class Node {
    protected:
        Node *p_next;
    public:
        T data;

        Node();
        Node(T data, Node<T> *p_next = nullptr);
        ~Node() { p_next = nullptr; }

        void push_next(Node<T> *other) { p_next = other; };
        Node** next() {return &p_next;}
    };

    template<typename T>
    class list {
    private:
        unsigned int size;
        Node<T> *head;

    public:
        list();
        list(list &other);
        ~list();

        void clear();
        void show();

        void insert_after(T data, unsigned element_number);  // element number starting from 0
        void delete_after(unsigned element_number);
        void push(T data);
        void pop();

        int lenght() { return size; }
        Node<T> *front() { return head; }
        T &operator[](unsigned element_number);
        bool operator==(const list &other);
        bool operator!=(const list &other);
    };



    template<typename T>
    bool list<T>::operator!=(const list &other) {
        return !(this == other);
    }

    template<typename T>
    bool list<T>::operator==(const list &other) {
        if (size != other.size)
            return false;

        Node<T> *first_current = head;
        Node<T> *second_current = head;
        for (unsigned idx = 0; idx < size; idx++) {
            if (first_current->data != second_current->data)
                return false;
            first_current = *(first_current->next());
            second_current = *(second_current->next());
        }
        return true;
    }

    template<typename T>
    T &list<T>::operator[](unsigned int element_number) {
        if (size == 0) {
            list_exceptions ZERO_SIZE("zero size error");
            throw ZERO_SIZE; }  // THIS
        else if (element_number >= size) {
            list_exceptions OUT_OF_THE_RANGE("index out of the range(operator [])");
            throw OUT_OF_THE_RANGE; } // THIS

        Node<T> *current_node = head;
        int counter = 0;
        while (current_node != nullptr) {
            if (counter == element_number)
                return current_node->data;
            current_node = *(current_node->next());
            counter++;
        }
    }

    template<typename T>
    list<T>::list(list &other) {
        this->size = other.size;
        if (other.head == nullptr) {
            this->head = nullptr;
        } else {
            head = new Node<T>(other.head->data);

            Node<T> *current_node = head;
            for (unsigned idx = 1; idx < other.size; idx++) {
                *(current_node->next()) = new Node<T>(other[idx]);
                current_node = *(current_node->next());
            }
        }
    }

    template<typename T>
    list<T>::~list() {
        clear();
    }

    template<typename T>
    void list<T>::show() {
        if (size == 0){
            list_exceptions SHOW_ERROR("can`t show zero size list");
            throw SHOW_ERROR; } // THIS

        Node<T>* running_pointer = head;
        for (unsigned counter = 0; counter < size; counter++){
            std::cout << running_pointer->data << "\t";
            running_pointer = *(running_pointer->next());
        }
        std::cout << "\n";
    }

    template<typename T>
    void list<T>::clear() {
        while (size){ pop();}
    }

    template<typename T>
    void list<T>::delete_after(unsigned int element_number) {
        if (size == 0){
            list_exceptions ZERO_SIZE("zero size error");
            throw ZERO_SIZE;} // THIS
        if (element_number >= size) {
            list_exceptions DELL_AFTER_OUT_OF_THE_RANGE("index out of the range(delete operation)");
            throw DELL_AFTER_OUT_OF_THE_RANGE; }// THIS
        if (element_number == size - 1) {
            list_exceptions DELL_AFTER_LAST("can`t delete after last element");
            throw DELL_AFTER_LAST; }// THIS

        Node<T>* running_pointer = head;
        for (unsigned counter = 0; counter < element_number; counter++){
            running_pointer = *(running_pointer->next());
        }
        Node<T>* del = *(running_pointer->next());
        auto tmp = *(del->next());
        delete del;
        *(running_pointer->next()) = tmp;
        size--;
    }

    template<typename T>
    void list<T>::push(T data) {
        if (size == 0){
            Node<T>* first_node = new Node<T>(data);
            head = first_node;
            size++;
            return;
        }
        Node<T>* new_node = new Node<T>(data, head);
        head = new_node;
        size++;
    }

    template<typename T>
    void list<T>::pop() {
        if (head == nullptr) {
            list_exceptions POP_ERROR("can`t pop from empty list");
            throw POP_ERROR; } // THIS
        if (*(head->next()) == nullptr){
            delete head;
            head = nullptr;
            size--;
            return;
        }
        Node<T>* tmp = *(head->next());
        delete head;
        head = tmp;
        size--;
    }

    template<typename T>
    Node<T>::Node(T data, Node<T> *p_next) {
        this->data = data;
        this->p_next = p_next;
    }

    template<typename T>
    void list<T>::insert_after(T data, unsigned int element_number) {  // element number starts from 0
        if (size == 0 and element_number == 0){
            push(data);
            list_exceptions INSERT_WARNING("[WARNING] list was empty and you wanted to add zero position element."
                                           "List was created and data pushed");
            throw INSERT_WARNING; // THIS
        }
        if (element_number >= size){
            list_exceptions INSERT_AFTER_OUT_OF_THE_RANGE("index out of the range(insert operation)");
            throw INSERT_AFTER_OUT_OF_THE_RANGE; // THIS
        }
        Node<T>* new_node = new Node<T>(data);
        Node<T>* running_pointer = head;
        for (unsigned counter = 0; counter < element_number; counter++){
            running_pointer = *(running_pointer->next());
        }
        *(new_node->next()) = *(running_pointer->next());
        *(running_pointer->next()) = new_node;
        size++;
    }

    template<typename T>
    list<T>::list() {
        size = 0;
        head = nullptr;
    }

    template<typename T>
    Node<T>::Node() {
        p_next = nullptr;
        data = T();
    }
}

#endif //ATD_LIST_H