#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Node {
public:
    int key;
    Node *left;
    Node *right;

    Node(int k);
    }
};
Node::Node(int k) {
    key = k;
    left = right = NULL;
}
class BST {
private:
    Node *root;

public:
    BST();
    ~BST();
    void insert(int key);
    void remove(int key);
    bool search(int key);
    void traverse();

private:
    Node* insert(Node* node, int key);
    Node* remove(Node* node, int key);
    Node* minValueNode(Node* node);
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
    if (node == NULL) {
        return new Node(key);
    }

    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    }

    return node;
}


Node* BST::remove(Node* node, int key) {
    if (node == NULL) {
        return NULL;
    }

    if (key < node->key) {
        node->left = remove(node->left, key);
    } else if (key > node->key) {
        node->right = remove(node->right, key);
    } else {
        if (node->left == NULL && node->right == NULL) {
            delete node;
            node = NULL;
        } else if (node->left == NULL) {
            Node* tmp = node;
            node = node->right;
            delete tmp;
        } else if (node->right == NULL) {
            Node* tmp = node;
            node = node->left;
            delete tmp;
        } else {
            Node* tmp = minValueNode(node->right);
            node->key = tmp->key;
            node->right = remove(node->right, tmp->key);
        }
    }

    return node;
}

Node* BST::minValueNode(Node* node) {
    Node* current = node;

    while (current->left != NULL) {
        current = current->left;
    }

    return current;
}

bool BST::search(Node* node, int key) {
    if (node == NULL) {
        return false;
    }

    if (key < node->key) {
        return search(node->left, key);
    } else if (key > node->key) {
        return search(node->right, key);
    } else {
        return true;
    }
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
