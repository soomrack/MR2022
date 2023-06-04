#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <limits>
#include <cmath>
#include <iostream>


class Node{
public: // можно сделать паблик и убрать гетеры, возможно нужно переписать
    Node *l_child;
    Node *r_child;
    double data;
    explicit Node(double in_data);
    ~Node() = default;
};


class BinaryTree{
protected:
    Node * root;
    Node * get_node(double data);
    void delete_all(Node* del_root);
public:
    BinaryTree();
    ~BinaryTree();
    void add_node(double in_data);
    void  print(double data);
    double find(double data);
    void remove(double in_data);
};



Node::Node(double in_data) {
    data = in_data;
    l_child = nullptr;
    r_child = nullptr;
}


BinaryTree::BinaryTree() {
    root = nullptr;
}


void BinaryTree::add_node(double in_data) {
    Node ** link = &root;
    while(*link){  // bcrk.xtybt yf le,kbhjdfybt
        if(in_data == (*link)->data){
            std::cout << "Duplicate data entered. Error.\n";
            return;
        }
        link = in_data < (*link)->data ? &((*link)->l_child) : &((*link)->r_child);
    }
    *link = new Node(in_data);
}


Node* BinaryTree::get_node(double data) {
    Node * node = root;
    while (node){
        if(data == node->data) return node;
        node = (data < node->data) ? node->l_child : node->r_child ;
    }
    return nullptr;
}


double BinaryTree::find(double data) {
    return BinaryTree::get_node(data)->data;
}


void BinaryTree::print(double data){
    Node *buffer = get_node(data);
    if(buffer == nullptr) {
        std::cout << "There is no such object:" << data <<"\n";
        return;
    }
    std::cout<<"l:";
    if(buffer->l_child != nullptr)
        std::cout << get_node(data)->l_child->data;
    else
        std::cout<<"null";
    std::cout<<" m:"<<find(data)<<" r:";
    if(buffer->r_child != nullptr)
        std::cout << get_node(data)->r_child->data<< "\n";
    else
        std::cout<<"null\n";
}


void BinaryTree::remove(double in_data) {
    Node * removed_node = get_node(in_data);  // проверка на возможность удаления
    if(!removed_node) {
        std::cout << "There is nothing to remove.\n";
        return;
    }
    Node * previous;  // Переменная нужна, чтобы удалить ссылку на переносимый node. Нужно задать точку за 1 до removed_node.
    Node * buffer = root;  // Переменная нужна, чтобы задать начальное значение для previous
    Node * replacement; // создание узла для замены
    if(!removed_node->l_child) {
        while (buffer) { //  задание значения переменной previous
            if (in_data == buffer->data) break;
            previous = buffer;
            buffer = in_data < buffer->data ? buffer->l_child : buffer->r_child;
        }
        if(previous->r_child == removed_node) previous->r_child = removed_node->r_child ? removed_node->r_child : removed_node->l_child;
        else previous->l_child = removed_node->r_child;
        delete removed_node;
        return;
    }   // замена на наибольшего элемента левого ребёнка
    previous = removed_node;
    replacement = removed_node->l_child;
    while (replacement->r_child){
        previous = replacement;
        replacement = replacement->r_child;
    }
    if(removed_node == root) previous->l_child = replacement->l_child;
    else previous->r_child = nullptr;
    if(previous->l_child == replacement) previous->l_child = nullptr;
    removed_node->data = replacement->data;
    delete replacement;
}


void BinaryTree::delete_all(Node* del_root) {
    if (del_root == nullptr)  return; // Базовый случай
    delete_all(del_root->l_child);   // рекурсивный вызов левого поддерева
    delete_all(del_root->r_child);  // рекурсивный вызов правого поддерева
    delete del_root;
}


BinaryTree::~BinaryTree() {
    delete_all(root);
}

#endif //BINARYTREE_H
