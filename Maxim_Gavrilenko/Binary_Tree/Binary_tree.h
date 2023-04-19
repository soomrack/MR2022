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
    Node(const Node& other) {
        data = other.data;
        left = other.left ? new Node(*other.left) : nullptr;  // рекурсивно копируем левую ноду
        right = other.right ? new Node(*other.right) : nullptr;  // рекурсивно копируем правую ноду
    }

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
    void replaceNode(Node** node, Node* oldNode, Node* newNode);

};

void BinaryTree::replaceNode(Node **node, Node *oldNode, Node *newNode) {
    if (*node == oldNode) {
        *node = newNode;
    } else if (oldNode->data < (*node)->data) {
        replaceNode(&(*node)->left, oldNode, newNode);
    } else {
        replaceNode(&(*node)->right, oldNode, newNode);
    }
}
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
        *node = new Node(value);
        return;
    }
    Node** next_node = value < (*node)->data ? &(*node)->left : &(*node)->right;
    return add(next_node, value);
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
        current = value < (*current)->data ? &(*current)->left : &(*current)->right;
    }
    if (!*current) return; // элемент не найден

    Node *temp = *current;
    if (!((*current)->left)) {
        *current = (*current)->right;
        delete temp;
        return;
    }
    if (!(*current)->right) {
        *current = (*current)->left;
        delete temp;
        return;
    }
    Node **successor = &((*current)->left);
    while ((*successor)->right || (*successor)->left) {
        successor = (!(*successor)->right) ? &((*successor)->left) : &((*successor)->right);
    }
    Node * temp_node(*successor);
    *successor = nullptr;
    *current = temp_node;
    (*current)->right = temp->right;
    (*current)->left = temp ->left;
    delete temp;
}


bool BinaryTree::search(double value) {
    return search(&root, value);
}


bool BinaryTree::search(Node **node, double value) {
    if ((*node) == nullptr) return false;
    if ((*node)->data == value) return true;
    Node** next_node = value < (*node)->data ? &(*node)->left : &(*node)->right;
    return search(next_node, value);
}


#endif //MR2022_BINARY_TREE_H
