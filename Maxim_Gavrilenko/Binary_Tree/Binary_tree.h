#include "Stack.h"
#ifndef MR2022_BINARY_TREE_H
#define MR2022_BINARY_TREE_H

struct Node
{
public:
    double data;
    Node* left;
    Node* right;
    explicit Node(const double& value, Node* left = nullptr, Node* right = nullptr): data(value), left(left), right(right) {}
};



class BinaryTree
{
public:
    BinaryTree();
    ~BinaryTree();
    void add(double);
    void remove(double);
    void print();
    bool search(double);

private:
    Node* root;
    void add(Node**, double);
    void remove(Node**, double);
    void remove_tree(Node**);
    void print(Node** node);
    bool search(Node** node, double data);
};


BinaryTree::BinaryTree()
{
    root = nullptr;
}


BinaryTree::~BinaryTree()
{
    remove_tree(&root);
}


void BinaryTree::remove_tree(Node** node)
{
    if (root == nullptr) {
        return;
    }
    stack<Node*> nodes(100);
    nodes.push(root);

    while (!nodes.is_empty()) {
        Node* current = nodes.pop();

        if (current->right != nullptr) {
            nodes.push(current->right);
        }

        if (current->left != nullptr) {
            nodes.push(current->left);
        }

        delete current;
    }
}

void BinaryTree::add(double value) {
    add(&root, value);
}


void BinaryTree::print() {
    print(&root);
}

void BinaryTree::add(Node** node, double value) {
    if (*node == nullptr) {
        *node = new Node(value, nullptr, nullptr);
        return;
    }
    if (value < (*node)->data) {
        add(&(*node)->left, value);
        return;
    }
    add(&(*node)->right, value);
}


void BinaryTree::print(Node** node) {
    if ((*node) == nullptr) return;

    print(&(*node)->left); // рекурсивно обрабатываем левое поддерево
    std::cout << (*node)->data << " "; // выводим значение текущего узла
    print(&(*node)->right); // рекурсивно обрабатываем правое поддерево
}

void BinaryTree::remove(double value) {
    remove(&root, value);
}


void BinaryTree::remove(Node ** node, double value) {
    Node **current = node;
    while (*current && (*current)->data != value) {
        if (value < (*current)->data)
            current = &((*current)->left);
        else
            current = &((*current)->right);
    }
    if (!*current) return; // элемент не найден

    Node *temp = *current;
    if (!(*current)->left) { //Если правый потомок
        *current = (*current)->right;
        delete temp;
        return;
    }
    if (!(*current)->right) { //Если левый потомок
        *current = (*current)->left;
        delete temp;
        return;
    }
        Node **successor = &((*current)->left); //Если оба, то родителем становится правый потомок самого левого
        while ((*successor)->right) {
            successor = &((*successor)->right);
        }
        (*current)->data = (*successor)->data;
        temp = *successor;
        *successor = (*successor)->left;
        delete temp;
    }


bool BinaryTree::search(double value) {
    return search(&root, value);
}


bool BinaryTree::search(Node **node, double data) {
    if ((*node) == nullptr) {
        return false;
    }
    if (data < (*node)->data) {
        return search(&(*node)->left, data);
    }
    if (data > (*node)->data) {
        return search(&(*node)->right, data);
    }
    return true; //В случае, если искомый элемент это корень дерева
}


#endif //MR2022_BINARY_TREE_H
