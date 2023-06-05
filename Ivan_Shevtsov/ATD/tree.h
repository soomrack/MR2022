//
// Created by ivan on 03/04/23.
//

#ifndef ATD_TREE_H
#define ATD_TREE_H

#include <iostream>
// убрать this переделать под концевую рекурсию
// if + return, убирать else, добавить цикл, в делит добавить удаление ноды и доступ по указаттелю

namespace tree_names {
    class tree_exceptions: public std::domain_error{
    public:
        tree_exceptions(const char* massage): std::domain_error(massage){}
    };

/*    tree_exceptions ZERO_SIZE("zero size error");
    tree_exceptions QUEUE_OUT_OF_TRE_RANGE("index out of the range");
    tree_exceptions QUEUE_POP_ERROR("can`t pop from empty queue");
    tree_exceptions QUEUE_SHOW_ERROR("can`t show zero size queue");*/


    class Node {
    public:
        int key;
        double value;
        Node* right;
        Node* left;

        Node();
        Node(double value, int key, Node* right = nullptr, Node* left = nullptr);

        ~Node();
    };

    class tree {
    private:
        unsigned depth;
        Node* root;
    public:
        tree();
        tree(double value, int key);

        void insert(int key, double value);
        bool delete_node(int key, double value);
        Node* find (int key);


        unsigned get_depth() {return depth;}
        Node* get_max(Node* node);
        void clear();
        //~tree() {clear();};

        void print_right();
    };
}

#endif //ATD_TREE_H
