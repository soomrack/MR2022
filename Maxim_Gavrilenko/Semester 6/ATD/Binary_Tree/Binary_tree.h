#include "../Stack/Stack.h"
#ifndef MR2022_BINARY_TREE_H
#define MR2022_BINARY_TREE_H

struct Node
{
public:
    double data;
    Node *left;
    Node *right;
    explicit Node(const double &value, Node *left = nullptr, Node *right = nullptr) : data(value), left(left), right(right) {}
};

class BinaryTree
{
public:
    BinaryTree();
    ~BinaryTree();
    void add(double);
    void remove(double);
    bool search(double);

private:
    Node *root;
    void add(Node **, double);
    void remove(Node **, double);
    void remove_tree(Node *node);
    bool search(Node **node, double data);
    Node **find_smallest_ptr(Node *subtree);
};

BinaryTree::BinaryTree()
{
    root = nullptr;
}

BinaryTree::~BinaryTree()
{
    remove_tree(root);
}

void BinaryTree::remove_tree(Node *node)
{
    if (node != nullptr)
    {
        remove_tree(node->left);
        remove_tree(node->right);
        delete node;
    }
}

void BinaryTree::add(double value)
{
    add(&root, value);
}

void BinaryTree::add(Node **node, double value)
{
    while (*node != nullptr)
    {
        node = value < (*node)->data ? &(*node)->left : &(*node)->right;
    }
    *node = new Node(value);
}

void BinaryTree::remove(double value)
{
    remove(&root, value);
}

void BinaryTree::remove(Node **node, double value)
{
    Node **current = node;
    while (*current && (*current)->data != value)
    {
        current = value < (*current)->data ? &(*current)->left : &(*current)->right;
    }
    if (!*current)
        return; // элемент не найден

    Node *temp = *current;
    if (!((*current)->left))
    {
        *current = (*current)->right;
        delete temp;
        return;
    }
    if (!(*current)->right)
    {
        *current = (*current)->left;
        delete temp;
        return;
    }
    Node **smallest_ptr = find_smallest_ptr(temp->right);

    if (temp->right == *smallest_ptr)
    {
        *current = *smallest_ptr;
    }
    else
    {
        *current = *smallest_ptr;
        *smallest_ptr = (*current)->right;
        (*current)->right = temp->right;
    }
    (*current)->left = temp->left;
    delete temp;
}

bool BinaryTree::search(double value)
{
    return search(&root, value);
}

bool BinaryTree::search(Node **node, double value)
{
    while (*node != nullptr)
    {
        if ((*node)->data == value)
        {
            return true;
        }
        node = value < (*node)->data ? &(*node)->left : &(*node)->right;
    }
    return false;
}

Node **BinaryTree::find_smallest_ptr(Node *subtree)
{
    Node **smallest = &subtree;
    while ((*smallest)->left != nullptr)
        smallest = &((*smallest)->left);
    return smallest;
}

#endif // MR2022_BINARY_TREE_H
