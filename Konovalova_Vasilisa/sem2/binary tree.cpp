#include <iostream>
using namespace std;

class BinaryTree {
private:
    struct Node {
        int data;
        Node* left;
        Node* right;
        Node(int value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* root;

public:
    BinaryTree();
    ~BinaryTree();
    void add(int value);
    void del(int value);
    bool get(int value);
private:
    void del_tree(Node* node);
    void add(int value, Node* node);
    void del(int value, Node* node);
    bool get(int value, Node* node);
    Node* find_min(Node* node);
    Node* find_max(Node* node);
};


BinaryTree::BinaryTree() : root(nullptr) {}

BinaryTree::~BinaryTree() {
    del_tree(root);
}

void BinaryTree::add(int value) {
    if (root == nullptr) {
        root = new Node(value);
    } else {
        add(value, root);
    }
}

void  BinaryTree::del(int value) {
    del(value, root);
}

bool  BinaryTree::get(int value) {
    return get(value, root);
}


void  BinaryTree::del_tree(Node* node) {
    if (node != nullptr) {
        del_tree(node->left);
        del_tree(node->right);
        delete node;
    }
}

void  BinaryTree::add(int value, Node* node) {
    if (value < node->data) {
        if (node->left == nullptr) {
            node->left = new Node(value);
        } else {
            add(value, node->left);
        }
    } else if (value > node->data) {
        if (node->right == nullptr) {
            node->right = new Node(value);
        } else {
            add(value, node->right);
        }
    }
}

void  BinaryTree::del(int value, Node* node) {
    if (node == nullptr) {
        return;
    }
    if (value < node->data) {
        del(value, node->left);
    } else if (value > node->data) {
        del(value, node->right);
    } else {
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            node = nullptr;
        } else if (node->left == nullptr) {
            Node* temp = node;
            node = node->right;
            delete temp;
        } else if (node->right == nullptr) {
            Node* temp = node;
            node = node->left;
            delete temp;
        } else {
            Node* temp = find_min(node->right);
            node->data = temp->data;
            del(temp->data, node->right);
        }
    }
}


bool  BinaryTree::get(int value, Node* node) {
    if (node == nullptr) {
        return false;
    } else if (node->data == value) {
        return true;
    } else if (value < node->data) {
        return get(value, node->left);
    } else {
        return get(value, node->right);
    }
}

Node*  BinaryTree::find_min(Node* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

Node*  BinaryTree::find_max(Node* node) {
    while (node->right != nullptr) {
        node = node->right;
    }
    return node;
}

int main() {
    BinaryTree bt;

    bt.add(0);
    bt.add(1);
    bt.add(2);
    bt.add(3);
    bt.add(4);
    bt.add(5);
    bt.add(6);

    bt.del(1);


    return 0;
}
