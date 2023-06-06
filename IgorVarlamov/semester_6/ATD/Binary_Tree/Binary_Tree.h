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
    Node **find_smallest_ptr(Node *subtree);
    Node **find_biggest_ptr(Node *subtree);
    void delete_root(Node *root);
};

BinaryTree::BinaryTree()
{
    root = nullptr;
}

BinaryTree::~BinaryTree()
{
    delete_root(root);
}

bool BinaryTree::search(double value)
{
    auto **node = &root;
    while (*node != nullptr)
    {
        if ((*node)->data == value)
            return true;
        if ((*node)->data > value)
        {
            node = &(*node)->left;
        }
        else
        {
            node = &(*node)->right;
        }
    }
}

void BinaryTree::delete_root(Node *node)
{
    if (node != nullptr)
    {
        delete_root(node->left);
        delete_root(node->right);
        delete node;
    }
}

void BinaryTree::add(double value)
{
    auto **node = &root;
    while (*node != nullptr)
    {
        node = value < (*node)->data ? &(*node)->left : &(*node)->right;
    }
    *node = new Node(value);
}

void BinaryTree::remove(double value)
{
    auto **node = &root;
    Node **current = node;
    while (*current && (*current)->data != value)
    {
        current = value < (*current)->data ? &((*current)->left) : &((*current)->right);
    }
    if (*current == nullptr)
        return;

    Node *nodeToRemove = *current;

    if (nodeToRemove->left == nullptr)
    {
        *current = nodeToRemove->right;
        delete nodeToRemove;
        return;
    }
    if (nodeToRemove->right == nullptr)
    {
        *current = nodeToRemove->left;
        delete nodeToRemove;
        return;
    }
    Node **largestOnLeftPtr = find_biggest_ptr(nodeToRemove->left);
    *current = *largestOnLeftPtr;

    (nodeToRemove->left == *largestOnLeftPtr) 
    ? (nodeToRemove->left = nullptr) 
    : (*largestOnLeftPtr = (*current)->left);
    (*current)->left = nodeToRemove->left;
    (*current)->right = nodeToRemove->right;
    delete nodeToRemove;
}

Node **BinaryTree::find_smallest_ptr(Node *subtree)
{
    Node **smallest = &subtree;
    while ((*smallest)->left != nullptr)
        smallest = &((*smallest)->left);
    return smallest;
}

Node **BinaryTree::find_biggest_ptr(Node *subtree)
{
    Node **biggest = &subtree;
    while ((*biggest)->right != nullptr)
        biggest = &((*biggest)->right);
    return biggest;
}

#endif // MR2022_BINARY_TREE_H
