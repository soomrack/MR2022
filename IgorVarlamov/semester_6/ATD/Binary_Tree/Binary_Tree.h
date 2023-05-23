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
        current = value < (*current)->data ? &(*current)->left : &(*current)->right;
    }
    if (!*current)
        return;

    Node *temp = *current;
    if (((*current)->left) != nullptr)
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
    *current = *smallest_ptr;
    (*current)->left = temp->left;
    *smallest_ptr = (*current)->right;
    (*current)->right = temp->right;
    delete temp;
}

Node **BinaryTree::find_smallest_ptr(Node *subtree)
{
    Node **smallest = &subtree;
    while ((*smallest)->left != nullptr)
        smallest = &((*smallest)->left);
    return smallest;
}

#endif // MR2022_BINARY_TREE_H
