#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <limits>
#include <cmath>
#include <iostream>


class Node{
protected:
    Node *l_child;
    Node *r_child;
    double data;
public:
    explicit Node(double in_data);
    ~Node() = default;
    Node* get_l();
    Node* get_r();
    [[nodiscard]] double get_data() const;
    void add_l(Node* new_node);
    void add_r(Node* new_node);
    void set_data(double in_data);
    void set_link(Node * setting_link, Node * in_link);
};



class BinaryTree{
protected:
    Node * root;
    Node * p_find(double data);
public:
    BinaryTree();
    ~BinaryTree() = default;
    void add_node(Node *node, Node *fork_node);
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


double Node::get_data() const {
    return data;
}


Node* Node::get_l() {
    return l_child;
}


Node* Node::get_r() {
    return r_child;
}


void Node::add_l(Node *new_node) {
    l_child = new_node;
}


void Node::add_r(Node *new_node) {
    r_child = new_node;
}


void Node::set_data(double in_data) {
    data = in_data;
}


void Node::set_link(Node * setting_link, Node * in_link = nullptr) {
    if (!setting_link) return;
    if (setting_link == r_child) {
        r_child = in_link;
        return;
    }
    if(setting_link == l_child) {
        l_child = in_link;
        return;
    }
}


BinaryTree::BinaryTree() {
    root = nullptr;
}


void BinaryTree::add_node(Node *node, Node *fork_node = nullptr) {
    if (fork_node == nullptr) {  // вставка корня или проверка 1ой итерации.
        if (root == nullptr) {
            root = node;
            return;
        }
        fork_node = root;
    }
    if(node->get_data() < fork_node->get_data()) // сравнение входа с развилочным значением
        if (fork_node->get_l()) fork_node = fork_node->get_l();  // шаг буфера налево
        else {
            fork_node->add_l(node);
            return;
        }
    else
        if (fork_node->get_r()) fork_node = fork_node->get_r();  // шаг буфера налево
        else {
            fork_node->add_r(node);
            return;
        }
    BinaryTree::add_node(node, fork_node);
}


void BinaryTree::add_node(double in_data) {
    auto *new_node = new Node(in_data);
    BinaryTree::add_node(new_node);
}


Node* BinaryTree::p_find(double data) {
    Node * fork_node = root;
    while (fork_node){
        if(data == fork_node->get_data()) return fork_node;
        if(data < fork_node->get_data()) fork_node = fork_node->get_l();
        else fork_node = fork_node->get_r();
    }
    return nullptr;
}


double BinaryTree::find(double data) {
    return BinaryTree::p_find(data)->get_data();
}


void BinaryTree::print(double data){
    Node *buffer = p_find(data);
    if(buffer == nullptr) {
        std::cout << "There is no such object:" << data <<"\n";
        return;
    }
    std::cout<<"l:";
    if(buffer->get_l() != nullptr)
        std::cout<<p_find(data)->get_l()->get_data();
    else
        std::cout<<"null";
    std::cout<<" m:"<<find(data)<<" r:";
    if(buffer->get_r() != nullptr)
        std::cout<<p_find(data)->get_r()->get_data()<<"\n";
    else
        std::cout<<"null\n";
}


void BinaryTree::remove(double in_data) {
    Node * removed_node = p_find(in_data);
    if(!removed_node) {
        std::cout << "There is nothing to remove.\n";
        return;
    }
    Node * previous;  // Переменная нужна, чтобы удалить ссылку на переносимый node. Нужно задать точку за 1 до removed_node.
    Node * fork_node = root;  // Переменная нужна, чтобы задать начальное значение для previous
    while (fork_node){
        if(in_data == fork_node->get_data()) break;
        if(in_data < fork_node->get_data()) {
            previous = fork_node;
            fork_node = fork_node->get_l(); }
        else {
            previous = fork_node;
            fork_node = fork_node->get_r();
        }
    }
    Node * replacement;
    if(removed_node->get_l()){
        previous = removed_node;
        replacement = removed_node->get_l();
        while (replacement->get_r()){
            previous = replacement;
            replacement = replacement->get_r();
        }
        if(removed_node == root) previous->set_link(previous->get_l(),replacement->get_l());
        previous->set_link(replacement);
        removed_node->set_data(replacement->get_data());
        delete replacement;
        return;
    }
    else if(removed_node->get_r()) {
        previous = removed_node;
        replacement = removed_node->get_r();
        while (replacement->get_l()) {
            previous = replacement;
            replacement = replacement->get_l();
        }
        if(removed_node == root) previous->set_link(previous->get_r(), replacement->get_r());
        previous->set_link(replacement);
        removed_node->set_data(replacement->get_data());
        delete replacement;
        return;
    }
    if(previous->get_l() == removed_node && !removed_node->get_l())
       previous->set_link(removed_node );
    if(previous->get_r() == removed_node && !removed_node->get_r())  // можно сделать красивее.
        previous->set_link(removed_node);
    delete removed_node;
}
#endif //BINARYTREE_H
