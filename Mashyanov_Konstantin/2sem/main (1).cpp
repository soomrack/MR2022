#include <iostream>
using namespace std;

class Node {
public:
    int value;  // Значение узла
    Node* left_child;  // Левый потомок
    Node* right_child;  // Правый потомок

    Node(int val) {
        value = val;
        left_child = nullptr;
        right_child = nullptr;
    }
};

class BinaryTree {
private:
    Node* root;  // Корень дерева

    Node* insert_recursive(Node* current, int value) {
        if (current == nullptr) {
            return new Node(value);
        }

        if (value < current->value) {
            current->left_child = insert_recursive(current->left_child, value);
        } else if (value > current->value) {
            current->right_child = insert_recursive(current->right_child, value);
        } else {
            return current;
        }

        return current;
    }

    bool search_recursive(Node* current, int value) {
        if (current == nullptr) {
            return false;
        }

        if (current->value == value) {
            return true;
        } else if (value < current->value) {
            return search_recursive(current->left_child, value);
        } else {
            return search_recursive(current->right_child, value);
        }
    }

    void inorder_recursive(Node* current) {
        if (current == nullptr) {
            return;
        }

        inorder_recursive(current->left_child);
        cout << current->value << " ";
        inorder_recursive(current->right_child);
    }

public:
    BinaryTree() {
        root = nullptr;
    }

    void insert(int value) {
        root = insert_recursive(root, value);
    }

    bool search(int value) {
        return search_recursive(root, value);
    }

    void inorder() {
        inorder_recursive(root);
        cout << endl;
    }
};

int main() {
    BinaryTree tree;

    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(9);

    tree.inorder();

    cout << "Search 7: " << tree.search(7) << endl;
    cout << "Search 2: " << tree.search(2) << endl;

    return 0;
}