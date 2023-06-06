//
// Created by ivan on 23/05/23.
//

#ifndef ATD_PRIORITY_QUEUE_H
#define ATD_PRIORITY_QUEUE_H
#include <iostream>

namespace priority_queue_names {
    /**
    * @brief myPrimaryQueue container with early sort
    *
    * head of queue has max key, tail - min key \n
    * use try/catch for work with Primary Queue
    * @class PrimaryQueueExceptions has these exceptions(objects):
    *
    * @objects PrimaryQueueExceptions OPERATOR_EQ("Operator== in Tvalue and Tkey must be defined");
    * @objects PrimaryQueueExceptions
    * @objects PrimaryQueueExceptions
    * @objects PrimaryQueueExceptions
    */

    class PrimaryQueueExceptions: public std::domain_error{
    public:
        PrimaryQueueExceptions(const char* massage): std::domain_error(massage){}
    };


    template<typename Tvalue, typename Tkey>
    class Node {
    public:
        Node<Tvalue, Tkey> *p_next;
        Tkey key;
        Tvalue value;

        Node();
        Node(Tvalue value, Tkey key);
        Node<Tvalue, Tkey>& operator=(const Node<Tvalue, Tkey>&) = delete;
        ~Node();

        bool operator==(Node<Tvalue, Tkey> const& other);
    };

    template<typename Tvalue, typename Tkey>
    class PriorityQueue {
    private:
        unsigned size;
        Node<Tvalue, Tkey> *p_tail;
        Node<Tvalue, Tkey> *p_head;
    public:
        PriorityQueue();
        PriorityQueue<Tvalue, Tkey>& operator=(const PriorityQueue<Tvalue, Tkey>&) = delete;
        ~PriorityQueue();
    public:
        bool show();
        void clear();
        bool is_empty(){ return (p_head == nullptr);}
        bool is_data_in_queue(Tvalue value, Tkey key);
    public:
        void push(Tvalue value, Tkey key);
        bool pop_min();
        bool pop_max();

        Node<Tvalue, Tkey> *front() { return p_head; }
        Node<Tvalue, Tkey> *back()  { return p_tail; }
    };

    template<typename Tvalue, typename Tkey>
    bool PriorityQueue<Tvalue, Tkey>::pop_max() {
        if (p_head == nullptr) {
            return false;
        }

        // if only one element in queue
        if (p_head->p_next == nullptr)    {
            delete p_head;
            p_head = nullptr;
            p_tail = nullptr;
            size--;
            return true;
        }
        auto tmp = p_head->p_next;
        delete p_head;
        p_head = tmp;

        size--;
    }

    template<typename Tvalue, typename Tkey>
    bool PriorityQueue<Tvalue, Tkey>::pop_min() {
        if (p_head == nullptr) {
            return false;
        }

        // if one element in queue
        if (p_head == p_tail){
            delete p_head;
            p_head = nullptr;
            p_tail = nullptr;
            size--;
            return true;
        }

        auto new_tail = p_head;
        while (new_tail->p_next != p_tail){
            new_tail = new_tail->p_next;
        }
        delete p_tail;
        p_tail = new_tail;
        p_tail->p_next = nullptr;

        size--;
        return true;
    }

    template<typename Tvalue, typename Tkey>
    void PriorityQueue<Tvalue, Tkey>::push(Tvalue value, Tkey key) {
        if (p_head == nullptr and p_tail == nullptr){
            Node<Tvalue, Tkey>* first_node = new Node<Tvalue, Tkey>(value, key);
            p_head = first_node;
            p_tail = first_node;
            size++;
            return;
        }

        Node<Tvalue, Tkey>* new_node = new Node<Tvalue, Tkey>(value, key);
        if (new_node->key < p_tail->key){
            p_tail->p_next = new_node;
            size++;
            return;
        }

        if (new_node->key > p_head->key){
            new_node->p_next = p_head;
            p_head = new_node;
            size++;
            return;
        }

        auto current_node = p_head;
        while (new_node->key < current_node->p_next->key){
            current_node = current_node->p_next;
        }
        new_node->p_next = current_node->p_next;
        current_node->p_next = new_node;
        size++;
    }


    template<typename Tvalue, typename Tkey>
    bool Node<Tvalue, Tkey>::operator==(const Node<Tvalue, Tkey> &other) {
        try {
            return key == other.key and value == other.value;}
        catch (std::exception& ex){
            PrimaryQueueExceptions OPERATOR_EQ("Operator== in Tvalue and Tkey "
                                               "must be define");
            throw OPERATOR_EQ;
        }  // TODO fix operator define check
    }

    template<typename Tvalue, typename Tkey>
    Node<Tvalue, Tkey>::~Node() {

        p_next = nullptr;
    }

    template<typename Tvalue, typename Tkey>
    Node<Tvalue, Tkey>::Node(Tvalue value, Tkey key): key(key), value(value), p_next(nullptr) {}

    template<typename Tvalue, typename Tkey>
    Node<Tvalue, Tkey>::Node(): key(Tkey()), value(Tvalue()), p_next(nullptr) {}



    template<typename Tvalue, typename Tkey>
    bool PriorityQueue<Tvalue, Tkey>::is_data_in_queue(Tvalue value, Tkey key) {
        Node<Tvalue, Tkey>* input_node = new Node<Tvalue, Tkey>(value, key);

        Node<Tvalue, Tkey>* running_pointer = p_head;
        while (running_pointer != nullptr){
            if (running_pointer->key == input_node->key and running_pointer->value == input_node->value){
                delete input_node;
                return true;
            }
            running_pointer = running_pointer->p_next;
        }
        delete input_node;
        return false;
    }

    template<typename Tvalue, typename Tkey>
    bool PriorityQueue<Tvalue, Tkey>::show() {
        if (p_head == nullptr) {
            return false;}
        Node<Tvalue, Tkey>* running_pointer = p_head;
        while (running_pointer != nullptr){
            std::cout << "{" << running_pointer->value <<";"
            << running_pointer->key<< "}" << "\t";
            running_pointer = running_pointer->p_next;
        }
        std::cout  << "\n";
    }

    template<typename Tvalue, typename Tkey>
    void PriorityQueue<Tvalue, Tkey>::clear() {
        while (!is_empty()){
            pop_max();
        }
        p_head = nullptr;
        p_tail = nullptr;
    }

    template<typename Tvalue, typename Tkey>
    PriorityQueue<Tvalue, Tkey>::~PriorityQueue() {
        clear();
    }

    template<typename Tvalue, typename Tkey>
    PriorityQueue<Tvalue, Tkey>::PriorityQueue(): size(0), p_head(nullptr), p_tail(nullptr){}


} // priority_queue_names

#endif //ATD_PRIORITY_QUEUE_H
