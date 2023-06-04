#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <cstddef>
#include <iostream>
#include <vector>


template<class T = int>
class BinaryTree
{
private:

    class Node
    {
        friend class BinaryTree;
    private:
        T data;
        Node* left;
        Node* right;
        explicit Node(T data) : data{data}, left{nullptr}, right{nullptr} {}
        ~Node() = default;
    };
    
    Node* root;
    size_t size;
    mutable size_t height;

    void show(const Node* node) const;
    Node** min(Node** node);
    size_t calcHeight(Node* node) const;

    void removeLeaf(Node** link);
    void removeOneChild(Node** link);
    void removeTwoChildren(Node** link);

public:

    explicit BinaryTree() : root{nullptr}, size{0}, height{0} {}
    explicit BinaryTree(T data) : root{new Node(data)}, size{1}, height{1} {}
    ~BinaryTree() { while (root) remove(root->data); }

    BinaryTree(const BinaryTree& other) = delete;
    BinaryTree& operator=(const BinaryTree& other) = delete;
    BinaryTree(BinaryTree&& other) = delete;
    BinaryTree&& operator=(BinaryTree&& other) = delete;

    size_t getSize() const { return size; };
    size_t getHeight() const;

    void add(T data);
    void remove(T data);
    bool find(T data) const;
    void show() const;
    void showTree() const;

};


template<class T>
size_t BinaryTree<T>::getHeight() const // the height changes when added or removed
{                                       // otherwise the height is const and so
    if (height == 0)                    // there is no need to calculate it
    {
        height = calcHeight(root);
        return height;
    }

    return height;
}

template<class T>
size_t BinaryTree<T>::calcHeight(Node *node) const
{
    if (node == nullptr)
        return 0;

    size_t left{}, right{};
    if (node->left)
        left = calcHeight(node->left);
    if(node->right)
        right = calcHeight(node->right);
    return (left > right ? left : right) + 1;
}

template<class T>
void BinaryTree<T>::add(T data)
{
    Node** link = &root;
    while (*link)
    {
        if (data == (*link)->data) return;
        link = data > (*link)->data ? &(*link)->right : &(*link)->left;
    }
    *link = new Node(data);
    ++size;
    height = 0;
}

template<class T>
void BinaryTree<T>::remove(T data)
{
    if (!root) // if empty
        return;

    Node** link = &root;
    while (*link && (*link)->data != data)  // searching removable node
        link = data > (*link)->data ? &(*link)->right : &(*link)->left;

    if (!*link) return; // if there is no the data

    --size;
    height = 0;  // height changes, need to recalculate it

    if ((*link)->left && (*link)->right)
        removeTwoChildren(link);
    else if ((*link)->left || (*link)->right)
        removeOneChild(link);
    else
        removeLeaf(link);
}

template<class T>
void BinaryTree<T>::removeLeaf(BinaryTree::Node **link)
{
    delete *link;
    *link = nullptr;
}

template<class T>
void BinaryTree<T>::removeOneChild(BinaryTree::Node **link)
{
    Node** link_child = (*link)->left ? &(*link)->left : &(*link)->right;
    delete *link;
    *link = *link_child;
}

template<class T>
void BinaryTree<T>::removeTwoChildren(BinaryTree::Node **link)
{
    Node** minimum = min(&(*link)->right);
    Node* left {(*link)->left};
    Node* right{(*link)->right};
    delete *link;
    *link = *minimum;
    *minimum = (*minimum)->right ? (*minimum)->right : nullptr; // the minimum can either be leaf or
    (*link)->left = left;                                       // have one child in the right branch
    if (right != *link)          // the right child of removable can be
        (*link)->right = right;  // the minimum in the right branch
}


template<class T>
bool BinaryTree<T>::find(T data) const
{
    if (!root) return false;
    if (root->data == data) return true;

    Node** link = &root;
    while (*link)
    {
        if (data == (*link)->data) return true;
        link = data > (*link)->data ? &(*link)->right : &(*link)->left;
    }
    return false;
}


template<class T>
void BinaryTree<T>::show() const
{
    if (!root) return;
    show(root);
    std::cout << "\n";
}

template<class T>
void BinaryTree<T>::show(const Node *node) const  // show implementation
{
    if (!node) return;
    show(node->left);
    std::cout << node->data << " ";
    show(node->right);
}

template<class T>
void BinaryTree<T>::showTree() const {
    if (!root) return;
    std::vector<Node*> nodes{root};
    while (!nodes.empty()) {
        std::vector<Node*> buffer {};
        for (auto& node : nodes) {
            std::cout << node->data << " ";
            if (node->left)
                buffer.push_back(node->left);
            if (node->right)
                buffer.push_back(node->right);
        }
        std::cout << "\n";
        nodes = buffer;
    }
}

template<class T>
typename BinaryTree<T>::Node** BinaryTree<T>::min(Node** node)
{
    if (node == nullptr)
        return node;

    Node** link = node;
    while ((*link)->left)
        link = &(*link)->left;
    return link;
}

#endif  // BINARY_TREE_H
