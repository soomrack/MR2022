#include <iostream>

using namespace std;

class Node {
    friend class Tree;
private:
    Node* left;
    Node* right;
    void* value;
public:
    unsigned int key;
    explicit Node(unsigned int in_key, void* in_value=nullptr);
    void* get_value();
};


class Tree {
private:
    Node* root;
    void deleteNode(Node* node);
public:
    Tree();
    ~Tree();

    void insert(unsigned int add_key, void* in_value);
    void* find(unsigned int find_key);
    void* remove(unsigned int rem_key);
};


Tree::Tree() {
    root = nullptr;
}


Tree::~Tree() {
    deleteNode(root);
}


Node::Node(unsigned int in_key, void *in_value) {
    key = in_key;
    value = in_value;
    right = nullptr;
    left = nullptr;
}


void* Node::get_value() {
    return value;
}


void Tree::deleteNode(Node *node) {
    if (!node) {
        return;
    }
    deleteNode(node->left);
    deleteNode(node->right);
    delete node;
}


void Tree::insert(unsigned int add_key, void *in_value) {
    auto* new_node = new Node(add_key, in_value);
    if (!root) {
        root = new_node;
        return;
    }
    Node* node = root;
    while (node) {
        if (node->key > new_node->key) {
            if (!node->right) {
                node->right = new_node;
            }
            node = node->right;
        }
        else {
            if (!node->left) {
                node->left = new_node;
                return;
            }
            node = node->left;
        }
    }
}


void* Tree::find(unsigned int find_key) {
    Node* node = root;
    while (node) {
        if (node->key == find_key) {
            return node->value;
        }
        node = (node->key > find_key) ? node->left : node->right;
    }
    return nullptr;
}


void* Tree::remove(unsigned int rem_key) {
    Node* prev_node = nullptr;
    Node* node = root;
    while (node) {
        if (node->key == rem_key) {
            break;
        }
        prev_node = node;
        node = (node->key > rem_key) ? node->left : node->right;
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
    return node->value;
}


int main() {
    Tree Tree;
    Tree.insert(1, 0);
    Tree.insert(2, 0);
    Tree.insert(3, 0);
    Tree.insert(4, 0);
    Tree.insert(5, 0);
    Tree.remove(3);
    return 0;
}