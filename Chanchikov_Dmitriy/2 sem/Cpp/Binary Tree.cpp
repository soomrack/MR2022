#include <iostream>


struct Node {
    explicit Node(const double &value, Node *parent = nullptr, Node *left = nullptr, Node *right = nullptr):
        data(value), parent(parent), left(left), right(right)  {}

    double data;
    Node *parent;
    Node *left;
    Node *right;
};


class BinaryTree {
private:
    Node *root;

    static Node **find_biggest_ptr(Node *subtree);
    void destroy(Node *node);

public:
    BinaryTree() : root(nullptr) {};
    ~BinaryTree() {destroy(root);}

    void insert(double);
    void remove(double);
    Node* search(double);
    void print() {print_rec(root, 0);}
    void print_rec(Node* node, int indent);
};


Node** BinaryTree::find_biggest_ptr(Node *subtree) {
    Node **biggest = new Node*(nullptr);
    Node *current = subtree;
    while (current->right != nullptr)
        current = current->right;
    *biggest = current;
    return biggest;
}


void BinaryTree::destroy(Node *node) {
    Node *current = node;
    Node *parent = nullptr;

    while (current != nullptr) {
        if (current->left != nullptr) {
            Node *leftChild = current->left;
            current->left = nullptr;
            current = leftChild;
        } else if (current->right != nullptr) {
            Node *rightChild = current->right;
            current->right = nullptr;
            current = rightChild;
        } else {
            parent = current->parent;

            if (parent != nullptr) {
                if (parent->left == current) {
                    parent->left = nullptr;
                } else {
                    parent->right = nullptr;
                }
            }

            delete current;
            current = parent;
        }
    }
}

/*
void BinaryTree::destroy(Node *node) {
    while (node != nullptr) {
        Node* current = node;

        if (current->left != nullptr) {
            node = current->left;
            current->left = nullptr;
        } else if (current->right != nullptr) {
            node = current->right;
            current->right = nullptr;
        } else {
            node = current->parent;
            delete current;
        }
    }
}
*/


void BinaryTree::insert(double value) {
    auto **node = &root;
    Node* parent = nullptr;

    while (*node != nullptr) {
        if (value == (*node)->data) {
            return;
        } else if (value < (*node)->data) {
            parent = *node;
            node = &(*node)->left;
        } else {
            parent = *node;
            node = &(*node)->right;
        }
    }
    *node = new Node(value, parent);
}


Node* BinaryTree::search(double value) {
    Node** node = &root;
    while (*node) {
        if ((*node)->data == value)
            return *node;
        if ((*node)->data > value) {
            node = &(*node)->left;
        } else {
            node = &(*node)->right;
        }
    }
    return nullptr;
}


void BinaryTree::remove(double value) {
    auto **node = &root;
    Node **current = node;
    while (*current && (*current)->data != value) {
        if (value < (*current)->data) {
            current = &(*current)->left;
        } else {
            current = &(*current)->right;
        }
    }
    if (*current == nullptr)
        return;
    if (*current == root)
        return;

    Node *node_to_remove = *current;

    if (node_to_remove->left == nullptr) {
        *current = node_to_remove->right;
        if (*current != nullptr)
            (*current)->parent = node_to_remove->parent;
        delete node_to_remove;
        return;
    }
    if (node_to_remove->right == nullptr) {
        *current = node_to_remove->left;
        if (*current != nullptr)
            (*current)->parent = node_to_remove->parent;
        delete node_to_remove;
        return;
    }

    int left_or_right = 0;
    if (node_to_remove->parent->right == node_to_remove)
        left_or_right = 1;

    Node **largest_on_left_ptr = find_biggest_ptr(node_to_remove->left);
    *current = *largest_on_left_ptr;

    if (node_to_remove->left != *largest_on_left_ptr) {
        *largest_on_left_ptr = (*current)->left;
        if (*largest_on_left_ptr != nullptr)
            (*largest_on_left_ptr)->parent = (*current)->parent;
        (*current)->parent->right = *largest_on_left_ptr;
        (*current)->left = node_to_remove->left;
        (*current)->left->parent = *current;
    }

    (*current)->right = node_to_remove->right;
    if ((*current)->right != nullptr)
        (*current)->right->parent = *current;

    (*current)->parent = node_to_remove->parent;
    if (left_or_right == 1)
        (*current)->parent->right = *current;
    else
        (*current)->parent->left = *current;

    delete largest_on_left_ptr;
    delete node_to_remove;
}


void BinaryTree::print_rec(Node* node, int indent) {
    if (node == nullptr)
        return;

    if (node->right != nullptr) {
        print_rec(node->right, indent + 4);
    }

    for (int i = 0; i < indent; i++)
        std::cout << " ";
    std::cout << node->data << std::endl;

    if (node->left != nullptr) {
        print_rec(node->left, indent + 4);
    }
}


int main() {
    BinaryTree tree;

    tree.insert(1);
    tree.insert(-2);
    tree.insert(-2);
    tree.insert(5);
    tree.insert(8);
    tree.insert(7);
    tree.insert(7.1);
    tree.insert(7.05);
    tree.insert(7.15);
    tree.insert(6.9);
    tree.insert(9);

    tree.print();

    if (tree.search(8) != nullptr)
        std::cout << "Found node with value: " << tree.search(8)->data << std::endl;
    else
        std::cout << "Node not found" << std::endl;


    std::cout << "================================" << std::endl;

    tree.remove(8);

    tree.print();

    if (tree.search(8) != nullptr)
        std::cout << "Found node with value: " << tree.search(8)->data << std::endl;
    else
        std::cout << "Node not found" << std::endl;


    return 0;
}
