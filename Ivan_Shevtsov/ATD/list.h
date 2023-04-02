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

namespace list_names {
    template<typename T>
    class Node {
    protected:
        Node *p_next;
    public:
        T data;

        Node();
        Node(T data, Node<T> *p_next = nullptr);

        void push_next(Node<T> *other) { p_next = other; };
        Node** next() {return &p_next;}

        ~Node() { p_next = nullptr; }
    };

    template<typename T>
    class list {
    private:
        unsigned int size;
        Node<T> *head;

    public:
        list();
        list(list &other);

        void clear();
        void show();

        void insert_after(T data, unsigned element_number);
        void delete_after(unsigned element_number);
        void push(T data);
        void pop();

        int lenght() { return size; }
        Node<T> *front() { return head; }
        T &operator[](unsigned element_number);
        bool operator==(const list &other);
        bool operator!=(const list &other);

        ~list();
    };



    template<typename T>
    bool list<T>::operator!=(const list &other) {
        return !(this == other);
    }

    template<typename T>
    bool list<T>::operator==(const list &other) {
        if (size != other.size)
            throw "for comparison lists mast have equal length"; // #TODO

        Node<T> *first_current = this->head;
        Node<T> *second_current = this->head;

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
        if (size == 0)
            throw LIST_ZERO_SIZE; //#TODO
        else if (element_number >= size)
            throw OUT_OF_TRE_RANGE_1; //#TODO

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
        if (size == 0){ throw "LIST_SHOW_ERROR"; }  // #TODO
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
            throw "LIST_CANT_DELL_IN_ZERO_SIZE";  // #TODO
        } else if (element_number >= size) {
            throw "LIST_INDEX_OUT_OF_THE_RANGE";  // #TODO
        }else if (element_number == size - 1) {
                throw "can`t delete after last element";     // #TODO
        } else {
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
    }

    template<typename T>
    void list<T>::push(T data) {
        if (size == 0){
            Node<T>* first_node = new Node<T>(data);
            head = first_node;
        } else{
            Node<T>* new_node = new Node<T>(data, head);
            head = new_node;
        }
        size++;
    }

    template<typename T>
    void list<T>::pop() {
        if (head == nullptr)
            throw "LIST_POP_ERROR";  // #TODO
        else if (*(head->next()) == nullptr){
            delete head;
            head = nullptr;
            size--;
        }
        else {
            Node<T>* tmp = *(head->next());
            delete head;
            head = tmp;
            size--;
        }
    }

    template<typename T>
    Node<T>::Node(T data, Node<T> *p_next) {
        this->data = data;
        this->p_next = p_next;
    }

    template<typename T>
    void list<T>::insert_after(T data, unsigned int element_number) {  // Q: как добавить документацию к функции
        if (size == 0 and element_number == 0){
            push(data);  // Q: возможно ворнинг какой нибудь добавить
        } else if (element_number >= size){
            throw "LIST_INDEX_OUT_OF_THE_RANGE";
        } else {
            Node<T>* new_node = new Node<T>(data);
            Node<T>* running_pointer = head;
            for (unsigned counter = 0; counter < element_number; counter++){
                running_pointer = *(running_pointer->next());
            }
            *(new_node->next()) = *(running_pointer->next());
            *(running_pointer->next()) = new_node;
            size++;
        }
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