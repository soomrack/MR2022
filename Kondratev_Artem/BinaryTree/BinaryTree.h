//
// Created by user on 4/6/23.
//

#ifndef HELLO_WORLD_BINARYTREE_H
#define HELLO_WORLD_BINARYTREE_H


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

    void* get_data();
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
    void add(unsigned int add_key, void* add_data);
    void* find(unsigned int find_key);
    void* del(unsigned int del_key);
};


Node::Node(unsigned int in_key, void* in_data) {
    key = in_key;
    data = in_data;
    left = nullptr;
    right = nullptr;
}


void* Node::get_data() {
    return data;
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


void BinaryTree::add(unsigned int add_key, void* add_data) {
    auto* new_node = new Node(add_key, add_data);

    if (!root) {
        root = new_node;
        return;
    }

    Node* node = root;
    while (node) {
        if (node->key > new_node->key) {
            if (!node->left) {
                node->left = new_node;
                return;
            }
            node = node->left;
        }
        else {
            if (!node->right) {
                node->right = new_node;
                return;
            }
            node = node->right;
        }
    }
}


void* BinaryTree::find(unsigned int find_key) {
    Node* node = root;
    while (node) {
        if (node->key == find_key) {
            return node->data;
        }
        node = (node->key > find_key) ? node->left : node->right;
    }
    return nullptr;
}


void* BinaryTree::del(unsigned int del_key) {
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


#endif //HELLO_WORLD_BINARYTREE_H
