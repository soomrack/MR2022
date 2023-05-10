#include <iostream>


class Node {
public:
    unsigned int value;
    Node* left;
    Node* right;
    Node(unsigned int new_value);
};


class Tree {
private:
    Node* get_node (unsigned int find_value);
    Node* get_parent (unsigned int find_value);
public:
    Node* root;
    Tree() {root = nullptr;};
    void insert(unsigned int new_value);
    void del(unsigned int del_value);
    bool find_val(unsigned int find_value);
};


void Tree::insert(unsigned int new_value) {
    Node** link = &root;
    while (*link != nullptr) {
        link = new_value < (*link)->value ? &((*link)->left) : &((*link)->right);
    }
    *link = new Node(new_value);
}


void Tree::del(unsigned int del_value) {
    auto parent_node = get_parent(del_value);
    Node* current_node;
    current_node = current_node;
}


bool Tree::find_val(unsigned int find_value) {
    auto current_node = root;
    if (get_node(find_value) != nullptr) {
        return true;
    }
    return false;
}


Node* get_right (Node* first_node) {
    auto current_node = first_node;
    while (current_node != nullptr) {
        if (current_node->right == nullptr) {
            break;
        }
        current_node = current_node->right;
    }
    current_node;
}


Node* get_left (Node* first_node) {
    auto current_node = first_node;
    while (current_node != nullptr) {
        if (current_node->left = nullptr) {
            break;
        }
        current_node = current_node->left;
    }
    current_node;
}


Node::Node(unsigned int new_value) {
    value = new_value;
    left = nullptr;
    right = nullptr;
}


Node *Tree::get_node(unsigned int find_value) {
    Node** link = &root;
    while (*link != nullptr) {
        link = find_value < (*link)->value ? &((*link)->left) : &((*link)->right);
        if ((*link)->value = find_value) {
            return *link;
        }
    }
    return nullptr;
}


Node *Tree::get_parent(unsigned int find_value) {
    Node** link = &root;
    Node** parent_link = nullptr;
    while (*link != nullptr) {
        parent_link = link;
        link = find_value < (*link)->value ? &((*link)->left) : &((*link)->right);
        if ((*link)->value == find_value) {
            return *parent_link;
        }
    }
    return nullptr;
}


void tree(){
    Tree tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);

    std::cout << std::endl;

    tree.del(8);

    std::cout << tree.find_val(2);
}


int main() {
    void tree();
    return 0;
}
