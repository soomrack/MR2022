#include <iostream>

class Node {
    friend class BinaryTree;

private:
    Node* left;
    Node* right;
    void* data;

public:
    unsigned int key;

public:
    explicit Node(unsigned int in_key, void* in_data=nullptr);
};


class BinaryTree {
private:
    Node* root;

public:
    BinaryTree();
    ~BinaryTree();

private:
    void deleteNode(Node* node);

public:
    void add_node(unsigned int add_key, void* add_data);

    void* find_node(unsigned int find_key);

    void* delete_node(unsigned int del_key);

    unsigned int getRoot();

    void add(unsigned int new_key, void* add_data);
};


Node::Node(unsigned int in_key, void* in_data) {
    key = in_key;
    data = in_data;
    left = nullptr;
    right = nullptr;
}


unsigned int BinaryTree::getRoot(){
    return root->key;
}


BinaryTree::BinaryTree() {
    root = nullptr;
}


void BinaryTree::deleteNode(Node* node) {
    if (!node) {
        return;
    }
    deleteNode(node->left);
    deleteNode(node->right);
    delete node;
}


BinaryTree::~BinaryTree() {
    deleteNode(root);
}


void BinaryTree::add(unsigned int new_key, void* add_data) {
    Node* new_node = new Node(new_key);
    Node** link = &root;
    while(*link != nullptr) {
        ((*link)->key > new_key) ? link = &((*link)->left) : link = &((*link)->right);
    }
    *link = new_node;
}


void* BinaryTree::find_node(unsigned int find_key) {
    Node* node = root;
    while (node) {
        if (node->key == find_key) {
            return node->data;
        }
        node = (node->key > find_key) ? node->left : node->right;
    }
    return nullptr;
}


void* BinaryTree::delete_node(unsigned int del_key) {
    Node* prev_node = nullptr;
    Node* node = root;

    while (node) {
        if (node->key == del_key) {
            break;
        }
        prev_node = node;
        node = (node->key > del_key) ? node->left : node->right;
    }

    if (!node) {
        return nullptr;
    }

    Node* parent_node = node;
    Node* child_node = node->right;
    if (child_node) {
        while (child_node->left) {
            parent_node = child_node;
            child_node = child_node->left;
        }
        child_node->left = node->left;
        if (parent_node != node) {
            parent_node->left = child_node->right;
            child_node->right = node->right;
        }
    }
    else {
        child_node = node->left;
    }

    if (node == root) {
        root = child_node;
    }
    else {
        if (prev_node->left == node) {
            prev_node->left = child_node;
        }
        else {
            prev_node->right = child_node;
        }
    }

    void* data = node->data;
    delete node;
    return data;
}

int main() {
    BinaryTree Tree;
    Tree.add(19, nullptr);
    Tree.add(14, nullptr);
    Tree.add(53, nullptr);
    Tree.add(3, nullptr);
    Tree.add(15, nullptr);
    Tree.add(26, nullptr);
    Tree.add(58, nullptr);
    Tree.add(29, nullptr);
    std::cout <<"Root before delete: " << Tree.getRoot() << std::endl;


    Tree.delete_node(19);
    std::cout <<"Root after delete: "<< Tree.getRoot();
    return 0;
}
