#include <iostream>

class Node {
    friend class BinaryTree;

private:
    Node* left;
    Node* right;
    int* data = nullptr;

public:
    unsigned int key;

    explicit Node(unsigned int in_key, int* in_data = nullptr);

    void* get_data();
};

class BinaryTree {
private:
    Node* root;

    void deleteNode(Node* node);
    static Node* deleteNode(Node* root, unsigned int del_key);
    static Node* minValueNode(Node* node);

public:
    BinaryTree();
    ~BinaryTree();

    void add(unsigned int add_key, int* add_data);
    int* find(unsigned int find_key);
    void del(unsigned int del_key);
};

Node::Node(unsigned int in_key, int* in_data) {
    key = in_key;
    if (in_data != nullptr) {
        data = in_data;
    }
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
    if (!node) return;

    deleteNode(node->left);
    deleteNode(node->right);
    delete node->data;
    delete node;
}

BinaryTree::~BinaryTree() {
    deleteNode(root);
}

void BinaryTree::add(unsigned int add_key, int* add_data) {
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

int* BinaryTree::find(unsigned int find_key) {
    Node* node = root;
    while (node) {
        if (node->key == find_key) return node->data;

        node = (node->key > find_key) ? node->left : node->right;
    }
    return nullptr;
}

Node* BinaryTree::minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left) {
        current = current->left;
    }
    return current;
}

Node* BinaryTree::deleteNode(Node* root, unsigned int del_key) {
    if (!root) {
        return root;
    }

    if (del_key < root->key) {
        root->left = deleteNode(root->left, del_key);
    }
    else if (del_key > root->key) {
        root->right = deleteNode(root->right, del_key);
    }
    else {
        if (!root->left) {
            Node* temp = root->right;
            delete root->data;
            delete root;
            return temp;
        }
        else if (!root->right) {
            Node* temp = root->left;
            delete root->data;
            delete root;
            return temp;
        }

        Node* temp = minValueNode(root->right);
        root->key = temp->key;
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

void BinaryTree::del(unsigned int del_key) {
    root = deleteNode(root, del_key);
}


int main() {
    BinaryTree tree;
    int ar[3] = {2, 1, 21};

    tree.add(5, ar);
    tree.add(3, nullptr);
    tree.add(7, nullptr);
    tree.add(2, nullptr);
    tree.add(4, nullptr);
    tree.add(6, nullptr);
    tree.add(9, nullptr);

    std::cout << "find(5): " << *tree.find(5) << std::endl;
    std::cout << "find(2): " << tree.find(2) << std::endl;

    tree.del(5);
    tree.del(1);
    tree.del(9);

    return 0;
}