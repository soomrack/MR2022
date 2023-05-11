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
    Node(double in_data);
    ~Node();
    Node* get_l();
    Node* get_r();
    double get_data();
    void add_l(Node* l_node);
    void  add_r( Node* r_node);
};



class Iterator {
public:
    Node *ptr;
    Iterator();
    ~Iterator();
    void go_l();
    void go_r();
    void set(Node *in_node);
    double get_data();
};



class BinaryTree{
protected:
    Node *root;
public:
    BinaryTree();
    ~BinaryTree();
    void add_node(Node *node, Node *fork_node);
    void add_node(double node, Node *fork_node);
    Node *find(double data, Node *fork_node);
   void  print(double data);
};



Node::Node(double in_data) {
    data = in_data;
    l_child = nullptr;
    r_child = nullptr;
}


Node::~Node() = default;


double Node::get_data() {
    return data;
}


Node* Node::get_l() {
    return l_child;
}


Node* Node::get_r() {
    return r_child;
}


void Node::add_l(Node *l_node) {
    l_child = l_node;
}


void Node::add_r(Node *r_node) {
    r_child = r_node;
}


Iterator::Iterator() {
    ptr = nullptr;
}


Iterator::~Iterator() = default;


void Iterator::go_l() {
    ptr = ptr->get_l();
}


void  Iterator::go_r() {
    ptr = ptr->get_r();
}


void Iterator::set(Node *in_node) {
    ptr = in_node;
}


double Iterator::get_data() {
    return ptr->get_data();
}



BinaryTree::BinaryTree() {
    root = nullptr;
}



BinaryTree::~BinaryTree() = default;


void BinaryTree::add_node(Node *node, Node *fork_node = nullptr) {
    if (fork_node == nullptr) {  // вставка корня или проверка 1ой итерации.
        if (root == nullptr) {
            root = node;
            return;
        }
        fork_node = root;
    }
    Iterator iterator;  // инициализация и присвоение значения итератору
    iterator.set(fork_node);
    if(node->get_data() <= iterator.get_data()) // сравнение входа с развилочным значением
        if(iterator.ptr->get_l() != nullptr)
            iterator.go_l();  // шаг итератора налево
        else {
            iterator.ptr->add_l(node);
            return;
        }
    else
        if(iterator.ptr->get_r() != nullptr)
            iterator.go_r();  // шаг итератора налево
        else {
            iterator.ptr->add_r(node);
        return;
        }
    if (iterator.ptr == nullptr) {  // если указатель пустой - запись и прекращение метода
        std::cout<<"An error occurred\n";
        return;
    }
    add_node(node, iterator.ptr);  // вызов следующей итерации
}


void BinaryTree::add_node(double in_data, Node *fork_node = nullptr) {
    auto *new_node = new Node(in_data);
    if (fork_node == nullptr) {  // вставка корня или проверка 1ой итерации.
        if (root == nullptr) {
            root = new_node;
            return;
        }
        fork_node = root;
    }
    Iterator iterator;  // инициализация и присвоение значения итератору
    iterator.set(fork_node);
    if(new_node->get_data() <= iterator.get_data()) // сравнение входа с развилочным значением
        if(iterator.ptr->get_l() != nullptr)
            iterator.go_l();  // шаг итератора налево
        else {
            iterator.ptr->add_l(new_node);
            return;
        }
    else
        if(iterator.ptr->get_r() != nullptr)
            iterator.go_r();  // шаг итератора налево
        else {
            iterator.ptr->add_r(new_node);
            return;
        }
    if (iterator.ptr == nullptr) {  // если указатель пустой - запись и прекращение метода
        std::cout<<"An error occurred\n";
        return;
    }
    add_node(new_node, iterator.ptr);  // вызов следующей итерации
}

Node* BinaryTree::find(double data, Node *fork_node = nullptr) {
    if (fork_node == nullptr) {  // проверка корня или 1ой итерации.
        if (root == nullptr) {
            std::cout<<"Tree is empty\n";
            return nullptr;
        }
        fork_node = root;
    }
    Iterator iterator;  // инициализация и присвоение значения итератору
    iterator.set(fork_node);
    if(data == iterator.get_data()) return iterator.ptr;
    if(data < iterator.get_data()) // сравнение входа с развилочным значением
        iterator.go_l();  // шаг итератора налево
    else
        iterator.go_r();  // шаг итератора направо
    if (iterator.ptr == nullptr) {  // если указатель пустой - запись и прекращение метода
        std::cout<<"Tree does not contain this element\n";
        return nullptr;
    }
    return find(data, iterator.ptr);  // вызов следующей итерации
}


void BinaryTree::print(double data){
    Node *buffer = find(data);
    if(buffer == nullptr) return;
    std::cout<<"l:";
    if(buffer->get_l() != nullptr)
        std::cout<<find(data)->get_l()->get_data();
    else
        std::cout<<"null";
    std::cout<<" m:"<<buffer->get_data()<<" r:";
    if(buffer->get_r() != nullptr)
        std::cout<<find(data)->get_r()->get_data()<<"\n";
    else
        std::cout<<"null\n";
}
#endif //BINARYTREE_H
