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
    explicit Node(unsigned int key_, void* data_=nullptr);

    void* get_data();
};


class BinaryTree {
private:
    Node* root;
    unsigned int height;

public:
    BinaryTree();

    void append(unsigned int key_, void* data_);
    void* find(unsigned int key_);
    void* pop(unsigned int key_);

private:
    static unsigned int findHeight(Node* node);

public:
    unsigned int get_height() const;
};


Node::Node(unsigned int key_, void* data_) {
    key = key_;
    data = data_;
    left = nullptr;
    right = nullptr;
}


void* Node::get_data() {
    return data;
}


BinaryTree::BinaryTree() {
    root = nullptr;
    height = 0;
}


void BinaryTree::append(unsigned int key_, void* data_) {
    auto* new_node = new Node(key_, data_);

    if (!root) {
        root = new_node;
        height = 1;
        return;
    }

    Node* node = root;
    while (node) {
        if (node->key > new_node->key) {
            if (node->left) {
                node = node->left;
            }
            else {
                node->left = new_node;
                height = findHeight(root);
                return;
            }
        }
        else {
            if (node->right) {
                node = node->right;
            }
            else {
                node->right = new_node;
                height = findHeight(root);
                return;
            }
        }
    }
}


void* BinaryTree::find(unsigned int key_) {
    Node* node = root;
    while (node) {
        if (node->key == key_) {
            return node->data;
        }
        else {
            node = (node->key > key_) ? node->left : node->right;
        }
    }
    return nullptr;
}


void* BinaryTree::pop(unsigned int key_) {
    Node* prev_node = nullptr;
    Node* node = root;
    while (node) {
        if (node->key != key_) {
            prev_node = node;
            node = (node->key > key_) ? node->left : node->right;
            continue;
        }

        if (!node->right && !node->left) {
            if (prev_node->left == node) {
                prev_node->left = nullptr;
            }
            else {
                prev_node->right = nullptr;
            }
            height = findHeight(root);
            return node->data;
        }

        if (node->left && !node->right) {
            if (prev_node->left == node) {
                prev_node->left = node->left;
            }
            else {
                prev_node->right = node->left;
            }
            node->left->right = node->right;
            height = findHeight(root);
            return node->data;
        }

        if (!node->left && node->right) {
            if (prev_node->left == node) {
                prev_node->left = node->right;
            }
            else {
                prev_node->right = node->right;
            }
            node->right->left = node->left;
            height = findHeight(root);
            return node->data;
        }

        if (node->left && node->right) {
            Node* min_node = node->right;
            while (min_node->left) {
                if (min_node->key < min_node->left->key) {
                    min_node = min_node->left;
                }
            }
            if (prev_node->left == node) {
                prev_node->left = min_node;
            }
            else {
                prev_node->right = min_node;
            }
            if (min_node != node->right) {
                min_node->right = node->right;
            }
            min_node->left = node->left;
            height = findHeight(root);
            return node->data;
        }
    }
    return nullptr;
}


unsigned int BinaryTree::findHeight(Node* node) {
    if (!node) {
        return 0;
    }
    if (!node->left && !node->right) {
        return 1;
    }
    unsigned int left_height = findHeight(node->left);
    unsigned int right_height = findHeight(node->right);
    return (left_height > right_height) ? left_height + 1 : right_height + 1;
}


unsigned int BinaryTree::get_height() const {
    return height;
}


#endif //HELLO_WORLD_BINARYTREE_H
