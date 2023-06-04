#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Node {
public:
    int key;
    Node *left;
    Node *right;

public:
    Node(int k);

    }
};
Node::Node(int k) {
    key = k;
    left = right = nullptr;
}
class BST {
private:
    Node *root;

public:
    BST();
    ~BST();

public:
    void insert(int key);
    void remove(int key);
    bool search(int key);
    void traverse();

private:
    Node* insert(Node* node, int key);
    Node* remove(Node* node, int key);
    Node* min(Node* node);
    bool search(Node* node, int key) ;
    void traverse(Node* node);
    void destroy(Node *node);
};


BST::BST() {
    root = NULL;
}

BST::~BST() {
    destroy(root);
}

void BST::insert(int key) {
    root = insert(root, key);
}

void BST::remove(int key) {
    root = remove(root, key);
}

bool BST::search(int key) {
    return search(root, key);
}

void BST::traverse() {
    traverse(root);
    cout << endl;
}


Node* BST::insert(Node* node, int key) {
    Node* curr = node;
    Node* parent = nullptr;
    while (curr != nullptr) {
        parent = curr;
        if (key < curr->key) {
            curr = curr->left;
        } else if (key > curr->key) {
            curr = curr->right;
        } else {
            return node;
        }
    }


    Node* BST::remove(Node* node, int key) {
        if (node == nullptr) {
            return nullptr;
        }

        if (key < node->key) {
            node->left = remove(node->left, key);
        } else if (key > node->key) {
            node->right = remove(node->right, key);
        } else {
            if (node->left == nullptr && node->right == nullptr) {
                Node* parent = node->parent;
                if (parent != nullptr) {
                    if (parent->left == node) {
                        parent->left = nullptr;
                    } else {
                        parent->right = nullptr;
                    }
                }
                delete node;
                node = nullptr;
            } else if (node->left == nullptr) {
                Node* tmp = node;
                node = node->right;
                node->parent = tmp->parent;
                delete tmp;
            } else if (node->right == nullptr) {
                Node* tmp = node;
                node = node->left;
                node->parent = tmp->parent;
                delete tmp;
            } else {
                Node* tmp = min(node->right);
                node->key = tmp->key;
                node->right = remove(node->right, tmp->key);
            }
        }

        return node;
    }

Node* BST::min(Node* node) {
    Node* current = node;

    while (current->left != NULL) {
        current = current->left;
    }

    return current;
}

    bool BST::search(int key) {
        Node* current = root;
        while (current != NULL) {
            if (key < current->key) {
                current = current->left;
            } else if (key > current->key) {
                current = current->right;
            } else {
                return true;
            }
        }
        return false;
    }

void BST::traverse(Node* node) {
    if (node != NULL) {
        traverse(node->left);
        cout << node->key << " ";
        traverse(node->right);
    }
}

void BST::destroy(Node *node) {
    if (node != NULL) {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}


int main() {
    srand(time(NULL));

    BST tree;

    for (int i = 0; i < 10; i++) {
        int key = rand() % 100;
        tree.insert(key);
    }

    cout << "Initial tree: ";
    tree.traverse();

    int key = rand() % 100;
    cout << "Search for key " << key << ": " << tree.search(key) << endl;

    key = rand() % 100;
    tree.remove(key);
    cout << "After removing key " << key << ": ";
    tree.traverse();

    tree.~BST();
    cout << "Tree destroyed." << endl;


    return 0;
}
