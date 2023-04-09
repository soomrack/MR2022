//
// Created by ivan on 03/04/23.
//

#include "tree.h"

tree_names::Node::Node() {
    value = 0;
    left = nullptr;
    right = nullptr;
}

tree_names::Node::Node(double value, int key, tree_names::Node *right, tree_names::Node *left) {
    this->value = value;
    this->right = right;
    this->left = left;
    this->key = key;
}

tree_names::Node::~Node() {
    value = 0;
    left = nullptr;
    right = nullptr;

}

tree_names::tree::tree() {
    depth = 0;
    root = nullptr;

}

tree_names::tree::tree(double value, int key) {
    depth = 1;
    root = new Node(value, key);
}

void tree_names::tree::insert(tree_names::Node *node, int key, double value) {
    if (key < node->key){
        if (node->left == nullptr)
            node->left = new Node(key, value);
        else insert(node->left, key, value);
    }
    else if (key >= node->key){
        if (node->right == nullptr)
            node->right = new Node(key, value);
        else insert(node->right, key, value);
    }
}

tree_names::Node *tree_names::tree::find(tree_names::Node *node, int key) {
    if (node == nullptr)
        return nullptr;
    if (node->key == key)
        return node;
    if (key < node->key)
        find(node->left,key);
    else find (node->right, key);
}

tree_names::Node *tree_names::tree::delete_node(tree_names::Node *node, int key) {
    if (node == nullptr)
        return nullptr;
    else if (key < node->key)
        node->left = delete_node(node->left, key);
    else if (key > node->key)
        node->right = delete_node(node->right, key);
    else {
        if (node->left == nullptr or node->right == nullptr)
            if (node->left == nullptr)
                node = node->right;
            else
                node = node->left;
        else {
            Node* left_max = get_max(node->left);
            node->key = left_max->key;
            node->value = left_max->value;
            node->right = delete_node(node->right, left_max->key);
        }

    }
    return node;
}

tree_names::Node *tree_names::tree::get_max(tree_names::Node *node) {
    if (node == nullptr) return nullptr;
    if (node->right == nullptr) return node;
    return get_max(node->right);
}




/*tree_names::tree::~tree() {
    clear();
    depth = 0;

}

void tree_names::tree::clear() {
    Node* running_pointer = root;
    while (depth) {
        if (running_pointer->left != nullptr)
            running_pointer

    }

}*/
