// можно работать через узлы (push_next()/next())
// или через итераторы для двух связного списка
// tail хранить не нужно
// нельзя делать доступ по индексу
#ifndef DYNAMIC_ARRAY_LIST_H
#define DYNAMIC_ARRAY_LIST_H


#include <iostream>

class List {
protected:
     class Node{ // класс узел, для добавления и удаления будем менять его поля в супер классе.
     public:
         double data;
         Node *next_ptr;


         explicit Node(double new_data){
             data = new_data;
             next_ptr = nullptr;
         }


         ~Node(){
              data = 0;
              next_ptr = nullptr;
          }


         Node &operator= (Node* const other){
              if(this == other) return *this;
              data = other->data;
              next_ptr = other->next_ptr;
             return *this;
         };

         Node &operator== (Node* &&other){
             if(this == other) {
                 other->data = 0;
                 other->next_ptr = nullptr;
                 return *this;
             }
             data = other->data;
             next_ptr = other->next_ptr;
             other->data = 0;
             other->next_ptr = nullptr;
             return *this;
         };
     };

public:
    Node *head;

    List(){
        head = nullptr;
    };


    class Iterator{
    public:
        Node *node_ptr;


        explicit Iterator() {
            node_ptr = nullptr;
        };

        Iterator(Node *in_node) {
            node_ptr = in_node;
        };

        Iterator &operator++ () {
            if (node_ptr == nullptr) return *this;
            node_ptr = node_ptr->next_ptr;
            return *this;
        };


        Iterator &operator= (Node* const other) {
            if (node_ptr == other) return *this;
            node_ptr = other;
            return *this;
        };


        Iterator &operator= (Iterator const other) {
            if (node_ptr == other.node_ptr) return *this;
            node_ptr = other.node_ptr;
            return *this;
        };


      /*  Iterator &operator= (Node* &&other) noexcept {
            if (node_ptr == other){
                other = nullptr;
                return *this;
            }
            node_ptr = other;
            other = nullptr;
            return *this;
        };*/


       /* Iterator &operator= (Iterator &&other) noexcept {
            if (node_ptr == other.node_ptr){
                other.node_ptr = nullptr;
                return *this;
            }
            node_ptr = other.node_ptr;
            other.node_ptr = nullptr;
            return *this;
        }; */

        bool operator== (Node* &&other) {
            if (node_ptr == other) return true;
            return false;
        };
        bool operator!= (Node* &&other) {
            if (node_ptr != other) return true;
            return false;
        };
    };



    bool is_empty(){
        if (head == nullptr) return true;
        return false;
    };


    unsigned int size(){
        if (is_empty()) return 0;
        Iterator iter = head->next_ptr;
        unsigned int counter = 1;
        while(iter != nullptr){
            counter++;
            iter = iter.node_ptr->next_ptr;
        }
        return counter;
    };


    void push_head (double in) {
        Node *new_node = new Node(in);
        if (is_empty()){
           head = new_node;
            return;
        }
        new_node->next_ptr = head;
        head = new_node;
    };


    void pop_head () {
        if (is_empty()) return;
        Node *buffer_ptr = head;
        head = head->next_ptr;
        delete buffer_ptr;
    };


    void push (double in, Iterator in_itr) {
        if (is_empty()) {
            push_head(in);
            return;
        }
        Node *new_node = new Node(in);
        new_node->next_ptr = in_itr.node_ptr;
        in_itr.node_ptr = new_node;
    };


    void pop (Iterator in_itr) {
        if (is_empty()) {
            return;
        }
        Iterator buffer_itr;
        for (buffer_itr = head; buffer_itr.node_ptr->next_ptr != in_itr.node_ptr; ++buffer_itr);
        buffer_itr.node_ptr->next_ptr = in_itr.node_ptr->next_ptr;
        delete in_itr.node_ptr;
    }; // удаление произвольного


    void print(){
        if (is_empty()) return;
        for(Iterator iter = head; iter.node_ptr != nullptr; ++iter)
            std::cout<<iter.node_ptr->data;
    };
};


#endif //DYNAMIC_ARRAY_LIST_H