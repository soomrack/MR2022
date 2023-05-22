#include <iostream>
using namespace std;

struct Node {
    int data;
    int value;
    Node* left;
    Node* right;
    Node(int value) : data(value), value(value), left(nullptr), right(nullptr) {}
};

class BinaryTree {
    
public:
    Node* root;
    BinaryTree();
    ~BinaryTree();
    void add(int value);
    void del(int del_value);
    bool get(int get_value);

private:
    Node* get_node(int get_value);
    Node* get_parent_node(int get_value);
    void destroy_tree(Node* node);
    Node* find_min(Node* node);

};

BinaryTree::BinaryTree() : root(nullptr) {}

BinaryTree::~BinaryTree() {
    destroy_tree(root);
}

void BinaryTree::add(int value) {
    Node** link = &root;
    while (*link != nullptr) {
        link = value < (*link)->value ? &((*link)->left) : &((*link)->right);
    }
    *link = new Node(value);
}

void BinaryTree::del(int del_value) {
    auto get_parent = get_parent_node(del_value);
    auto current_node_link = del_value < get_parent->value ? &(get_parent->left) : &(get_parent->right);
    auto del_node = *current_node_link;

    if (get_node(del_value) == nullptr) {
        return;
    }

    if ((*current_node_link)->right == nullptr) {
        *current_node_link = (*current_node_link)->left;
        delete del_node;
        return;
    }
    if ((*current_node_link)->left == nullptr) {
        *current_node_link = (*current_node_link)->right;
        delete del_node;
        return;
    }

    auto del_left_link = &((*current_node_link)->left);
    auto del_right_link = &((*current_node_link)->right);
    auto del_link = current_node_link;

    auto most_left_link = del_right_link;
    auto next_node = (*most_left_link)->left;
    while (next_node != nullptr) {
        most_left_link = &((*most_left_link)->left);
        next_node = next_node->left;
    }

    auto most_left = *most_left_link;
    (*del_link) = most_left;
    most_left->left = (*del_left_link);
    auto mem_link = most_left->right;
    (*most_left_link) = mem_link;
    most_left->right = (*del_right_link);

    delete del_node;
}

bool BinaryTree::get(int get_value) {
    auto current_node = root;
    if (get_node(get_value) != nullptr) {
        return true;
    }
    return false;
}

void BinaryTree::destroy_tree(Node* node) {
    if (node != nullptr) {
        destroy_tree(node->left);
        destroy_tree(node->right);
        delete node;
    }
}

Node* BinaryTree::get_node(int get_value) {
    Node** link = &root;
    while (*link != nullptr) {
        link = get_value > (*link)->value ? &((*link)->left) : &((*link)->right);
        if ((*link)->value == get_value) {
            return *link;
        }
    }
    return nullptr;
}

Node* BinaryTree::get_parent_node(int get_value) {
    Node** link = &root;
    Node** get_parent_link = nullptr;
    while (*link != nullptr) {
        get_parent_link = link;
        link = get_value < (*link)->value ? &((*link)->left) : &((*link)->right);
        if ((*link)->value == get_value) {
            return *get_parent_link;
        }
    }
    return nullptr;
}

Node* BinaryTree::find_min(Node* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

int main() {
    BinaryTree tree;

    tree.add(5);
    tree.add(3);
    tree.add(7);
    tree.add(2);
    tree.add(4);
    tree.add(6);
    tree.add(8);

    if (tree.get(5)) {
        cout << "Element 5 is in the tree" << endl;
    }

    tree.del(5);

    if (!tree.get(5)) {
        cout << "Element 5 is not in the tree anymore" << endl;
    }

    return 0;
}
