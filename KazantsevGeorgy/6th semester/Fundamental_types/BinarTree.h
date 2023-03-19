#include <iostream>
using namespace std;


template <typename SPIDER>
class Node
{
public:
    SPIDER data;
    Node * left;
    Node * right;
    explicit Node(SPIDER val);
};

template <typename SPIDER>
Node<SPIDER>::Node(SPIDER val)
{
    left = nullptr;
    right = nullptr;
    data = val;
}

template <typename SPIDER>
class Tree
{
private:
    Node<SPIDER> *root;
    int BinaryTreeSize;
    // методы класса
    void printTree(Node <SPIDER>*);
    void deleteTree(Node <SPIDER>*);

public:
    //конструктор класса
    Tree(int);
    //деструктор
    ~Tree();

    //методы класса
    void print();
    bool find(SPIDER);
    void insert(SPIDER);
    void erase(SPIDER);
    int BTSize();
};

template <typename SPIDER>
Tree<SPIDER>::Tree(int key)
{
    root = new Node <SPIDER>(key);
    BinaryTreeSize = 1;
}

template <typename SPIDER>
Tree<SPIDER>::~Tree()
{
    deleteTree(root);
}

template <typename SPIDER>
void Tree<SPIDER>::deleteTree(Node <SPIDER>* curr)
{
    if (curr==0)
    {
        deleteTree(curr->left);
        deleteTree(curr->right);
        delete curr;
        // BinaryTreeSize = 0;
    }
}

template <typename SPIDER>
void Tree<SPIDER>::print()
{
    printTree(root);
    cout << endl;
}

template <typename SPIDER>
void Tree<SPIDER>::printTree(Node <SPIDER>* curr)
{
    if (curr)
    {
        printTree(curr->left);
        cout << curr->data << " ";
        printTree(curr->right);
    }
}

// возвращать значение
template <typename SPIDER>
bool Tree<SPIDER>::find(SPIDER key)
{
    Node <SPIDER>* curr = root;
    while (curr && curr->data != key)
    {
        if (curr->data > key)
            curr = curr->left;
        else
            curr = curr->right;
    }
    return curr != nullptr;
}

// возвращать данные
template <typename SPIDER>
void Tree<SPIDER>::insert(SPIDER key)
{
    Node <SPIDER>* curr = root;
    while (curr && curr->data != key)
    {
        if (curr->data > key && curr->left == nullptr)
        {
            curr->left = new Node<SPIDER>(key);
            ++BinaryTreeSize;
            return;
        }
        if (curr->data < key && curr->right == nullptr)
        {
            curr->right = new Node<SPIDER>(key);
            ++BinaryTreeSize;
            return;
        }
        if (curr->data > key)
            curr = curr->left;
        else
            curr = curr->right;
    }
}


// find сохранять родителя и возвращать родителя
template <typename SPIDER>
void Tree<SPIDER>::erase(SPIDER key)
{
    Node <SPIDER>* curr = root;
    Node <SPIDER>* parent = nullptr;
    while (curr && curr->data != key)
    {
        parent = curr;
        if (curr->data > key)
        {
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
    }
    if (curr->left == nullptr)
    {
        if (parent && parent->left == curr)
            parent->left = curr->right;
        if (parent && parent->right == curr)
            parent->right = curr->right;
        --BinaryTreeSize;
        delete curr;
        // if parent == nullptr delete root;
        return;
    }
    if (curr->right == nullptr)
    {
        if (parent && parent->left == curr)
            parent->left = curr->left;
        if (parent && parent->right == curr)
            parent->right = curr->left;
        --BinaryTreeSize;
        delete curr;
        return;
    }
    // лучше менять узлы
    Node <SPIDER>* replace = curr->right;
    while (replace->left)
        replace = replace->left;
    SPIDER replace_value = replace->data;
    // добаить ключ в Node
    erase(replace_value);
    curr->data = replace_value;
}

template <typename SPIDER>
int Tree<SPIDER>::BTSize() {
    return BinaryTreeSize;
}
