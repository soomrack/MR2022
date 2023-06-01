#include <iostream>


struct Node {
    explicit Node(const double &value, Node *left = nullptr, Node *right = nullptr):
        data(value), left(left), right(right)  {}

    double data;
    Node *left;
    Node *right;
};


class BinaryTree {
private:
    Node *root;

    static Node *find_parent_of_biggest_ptr(Node *subtree);
    void destroy_rec(Node *node);

public:
    BinaryTree() : root(nullptr) {};
    ~BinaryTree() {destroy_rec(root); root = nullptr;}

    void insert(double);
    void remove(double);
    bool search(double);
    void print() {print_rec(root, 0);}
    void print_rec(Node* node, int indent);
};


Node* BinaryTree::find_parent_of_biggest_ptr(Node *subtree) {
    Node* parent_of_biggest_ptr = nullptr;
    Node* current = subtree;

    while (current->right != nullptr) {
        parent_of_biggest_ptr = current;
        current = current->right;
    }

    return parent_of_biggest_ptr;
}


void BinaryTree::destroy_rec(Node *node) {
    if (node == nullptr)
        return;

    destroy_rec(node->left);

    destroy_rec(node->right);

    delete node;
}


void BinaryTree::insert(double value) {
    auto **node = &root;

    while (*node != nullptr) {
        if (value == (*node)->data)
            return;
        value < (*node)->data ? node = &(*node)->left : node = &(*node)->right;
    }
    *node = new Node(value);
}


bool BinaryTree::search(double value) {
    auto** node = &root;
    while (*node != nullptr) {
        if ((*node)->data == value)
            return true;
        (*node)->data > value ? node = &(*node)->left : node = &(*node)->right;

    }
    return false;
}


void BinaryTree::remove(double value) {
    auto node = &root;
    auto current = node;

    while (*current && (*current)->data != value)
        value < (*current)->data ? current = &(*current)->left : current = &(*current)->right;
    if (*current == nullptr || *current == root)
        return;

    Node *node_to_remove = *current;

    if (node_to_remove->left == nullptr){
        *current = (*current)->right;
        delete node_to_remove;
        return;
    }
    if (node_to_remove->right == nullptr) {
        *current = (*current)->left;
        delete node_to_remove;
        return;
    }

    Node *parent_of_biggest_ptr = find_parent_of_biggest_ptr(node_to_remove->left);
    *current = parent_of_biggest_ptr->right;

    if (node_to_remove != parent_of_biggest_ptr) {
        parent_of_biggest_ptr->right = (*current)->left;
        (*current)->left = node_to_remove->left;
    }

    (*current)->right = node_to_remove->right;
    *current = node_to_remove;

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

    if (tree.search(8) != 0)
        std::cout << "Node found" << std::endl;
    else
        std::cout << "Node not found" << std::endl;


    std::cout << "================================" << std::endl;

    tree.remove(8);

    tree.print();

    if (tree.search(8) != 0)
        std::cout << "Node found" << std::endl;
    else
        std::cout << "Node not found" << std::endl;


    return 0;
}
