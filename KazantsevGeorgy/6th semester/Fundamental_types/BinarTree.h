//
// Created by delta on 24.02.2023.
//

#ifndef CLIONPROJECTS_BINARTREE_H
#define CLIONPROJECTS_BINARTREE_H

#endif //CLIONPROJECTS_BINARTREE_H

#include <iostream>
using namespace std;


template <typename SPIDER>
//каждый элемент будет иметь свой класс
class Node
{
public:
    SPIDER data; //число, которое хранится в вершине
    Node * left; //указатель на левого потомка этой вершины
    Node * right; //указатель на правого потомка этой вершины

    Node(SPIDER val);
};
//конструктор класс для записи значения в вершину и инициализации двух потомков
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
    Node <SPIDER>* root; //указатель на корень дерева
    int BinaryTreeSize; // количество элементов в дерева
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
    if (curr)
    {
        deleteTree(curr->left);
        deleteTree(curr->right);
        delete curr;
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
    if (!curr)
        return;
    if (curr->left == nullptr)
    {
        // Вместо curr подвешивается его правое поддерево
        if (parent && parent->left == curr)
            parent->left = curr->right;
        if (parent && parent->right == curr)
            parent->right = curr->right;
        --BinaryTreeSize;
        delete curr;
        return;
    }
    if (curr->right == nullptr)
    {
        // Вместо curr подвешивается его левое поддерево
        if (parent && parent->left == curr)
            parent->left = curr->left;
        if (parent && parent->right == curr)
            parent->right = curr->left;
        --BinaryTreeSize;
        delete curr;
        return;
    }
    // У элемента есть два потомка, тогда на место элемента поставим
    // наименьший элемент из его правого поддерева
    Node <SPIDER>* replace = curr->right;
    while (replace->left)
        replace = replace->left;
    int replace_value = replace->data;
    erase(replace_value);
    curr->data = replace_value;
}

template <typename SPIDER>
int Tree<SPIDER>::BTSize() {
    return BinaryTreeSize;
}
