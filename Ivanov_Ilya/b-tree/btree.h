#ifndef btree_h
#define btree_h
#include <iostream>

struct Node {
    double data;
    Node* left;
    Node* right;

    explicit Node(const double& value, Node* left = nullptr, Node* right = nullptr)
        : data(value), left(left), right(right) {}
};

class Tree {
public:
    Tree();
    ~Tree();
    void insert(double value);
    void del(double value);
    bool search(double value);
    void print();

private:
    Node* root;
    Node** findSmallestPtr(Node* subtree);
    Node** findLargestPtr(Node* subtree);
    void deleteSubtree(Node* subtree);
    void print(Node* root, std::string indent, bool last);
};

Tree::Tree() {
    root = nullptr;
}

Tree::~Tree() {
    deleteSubtree(root);
}

bool Tree::search(double value) {
    Node** node = &root;
    while (*node != nullptr) {
        if ((*node)->data == value)
            return true;
        if ((*node)->data > value) {
            node = &(*node)->left;
        }
        else {
            node = &(*node)->right;
        }
    }
    return false;
}

void Tree::deleteSubtree(Node* subtree) {
    if (subtree != nullptr) {
        deleteSubtree(subtree->left);
        deleteSubtree(subtree->right);
        delete subtree;
    }
}

void Tree::insert(double value) {
    Node** node = &root;
    while (*node != nullptr) {
        node = value < (*node)->data ? &(*node)->left : &(*node)->right;
    }
    *node = new Node(value);
}

void Tree::del(double value) {
    Node** node = &root;
    Node** current = node;
    while (*current && (*current)->data != value) {
        current = value < (*current)->data ? &((*current)->left) : &((*current)->right);
    }
    if (*current == nullptr)
        return;

    Node* nodeToRemove = *current;

    if (nodeToRemove->left == nullptr) {
        *current = nodeToRemove->right;
        delete nodeToRemove;
        return;
    }
    if (nodeToRemove->right == nullptr) {
        *current = nodeToRemove->left;
        delete nodeToRemove;
        return;
    }
    Node** largestOnLeftPtr = findLargestPtr(nodeToRemove->left);
    *current = *largestOnLeftPtr;

    (nodeToRemove->left == *largestOnLeftPtr)
        ? (nodeToRemove->left = nullptr)
        : (*largestOnLeftPtr = (*current)->left);
    (*current)->left = nodeToRemove->left;
    (*current)->right = nodeToRemove->right;
    delete nodeToRemove;
}

Node** Tree::findSmallestPtr(Node* subtree) {
    Node** smallest = &subtree;
    while ((*smallest)->left != nullptr)
        smallest = &((*smallest)->left);
    return smallest;
}

Node** Tree::findLargestPtr(Node* subtree) {
    Node** largest = &subtree;
    while ((*largest)->right != nullptr)
        largest = &((*largest)->right);
    return largest;
}

void Tree::print() {
    if (root) {
        print(root, "", true);
    }
}

void Tree::print(Node* root, std::string indent, bool last) {
    if (root != nullptr) {
        std::cout << indent;
    
        if (last) {
            std::cout << "R----";
            indent += " ";
        }
        else {
            std::cout << "L----";
            indent += "| ";
        }
        std::cout << root->data << "\n";
        print(root->left, indent, false);
        print(root->right, indent, true);
    }
}

    #endif // btree_h
