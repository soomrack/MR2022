#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <cstddef>
#include <iostream>
#include <vector>
#include <algorithm>

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

        explicit Node(T data);
        ~Node() = default;

    };

    Node* root;
    size_t size;
    mutable size_t height;

    void showImpl(const Node* node) const;
    Node* findImpl(Node* node, T data) const;
    void removeLeaf(Node* parent, Node* removable);
    void removeOneChild(Node* parent, Node* removable);
    void removeTwoChild(Node* parent, Node* removable);

    size_t calcHeight(Node* node) const;
    Node* findParentMin(Node* node) const;

public:

    explicit BinaryTree();
    explicit BinaryTree(T data);
    ~BinaryTree();
    BinaryTree(const BinaryTree& other) = delete;  
    BinaryTree& operator=(const BinaryTree& other) = delete;

    size_t getSize() const;
    size_t getHeight() const;

    void append(T data);
    void remove(T data);
    bool find(T data) const;
    void show() const;
    void showTree() const;

};

template<class T>
BinaryTree<T>::Node::Node(T data)
        : data{data}, left{nullptr}, right{nullptr} {}

template<class T>
BinaryTree<T>::BinaryTree()
        : root{nullptr}, size{0}, height{0} {}

template<class T>
BinaryTree<T>::BinaryTree(T data)
        : root{new Node(data)}, size{1}, height{1} {}


template<class T>
BinaryTree<T>::~BinaryTree()
{
  while (root)
      remove(root->data);
}


template<class T>
size_t BinaryTree<T>::getSize() const 
{
    return size;
}

template<class T>
size_t BinaryTree<T>::getHeight() const 
{
    if (height == 0)
    {
        height = calcHeight(root);
        return height;
    }

    return height;
}

template<class T>
size_t BinaryTree<T>::calcHeight(Node *node) const {
    size_t h1{}, h2{};
    if (node == nullptr)
        return 0;
    if (node->left)
        h1 = calcHeight(node->left);
    if(node->right)
        h2 = calcHeight(node->right);
    return (h1 > h2 ? h1 : h2) + 1;
}

template<class T>
void BinaryTree<T>::append(T data)
{
    if (!size)
    {
        root = new Node(data);
        size = 1;
        height = 1;
    }


    for (Node* ptr = root; ptr != nullptr;)
    {
        if (data > ptr->data)
        {
            if (!ptr->right)
            {
                ptr->right = new Node(data);
                ++size;
                height = 0;
                return;
            }
            ptr = ptr->right;
        } else if (data < ptr->data) {
            if (!ptr->left)
            {
                ptr->left = new Node(data);
                ++size;
                height = 0;
                return;
            }
            ptr = ptr->left;
        } else {
            return;
        }
    }
}

template<class T>
void BinaryTree<T>::remove(T data)
{
    if (!root) return;      // tree is empty
    if (root->data == data)
    {
        if (root->left || root->right)    // if the node has at least one child
        {
            if (root->left && root->right)
                removeTwoChild(nullptr, root);
            else
                removeOneChild(nullptr, root);
        } else {
            removeLeaf(nullptr, root);
        }
        return;
    }

    Node* parent = findImpl(root, data);  // get the parent of the node searched for
    if (!parent) return;  // if the node doesn't exist

    Node* removable;
    removable = data > parent->data ?  parent->right : parent->left;

    height = 0;
    if (removable->left || removable->right)    // if the node has at least one child
    {
        if (removable->left && removable->right)
            removeTwoChild(parent, removable);
        else
            removeOneChild(parent, removable);
    } else {
        removeLeaf(parent, removable);
    }
}

template<class T>
void BinaryTree<T>::removeLeaf(Node* parent, Node* removable)
{
    if (parent)
        parent->left == removable ? parent->left = nullptr : parent->right = nullptr;
    else
        root = nullptr;
    delete removable;
    --size;
}

template<class T>
void BinaryTree<T>::removeOneChild(Node* parent, Node* removable)
{
    Node* child;
    removable->left ? child = removable->left : child = removable->right;
    if (parent)
        parent->data > removable->data ? parent->left = child : parent->right = child;
    else
        root = child;
    delete removable;
    --size;
}

template<class T>
void BinaryTree<T>::removeTwoChild(Node* parent, Node* removable)
{
    Node* leftChild {removable->left};
    Node* rightChild {removable->right};
    Node* parentMin {findParentMin(removable->right)};  // if removable->right is min node
    Node* min;
    parentMin->left ? min = parentMin->left  : min = parentMin;

    if (min->right && parentMin != min)
    {
        parentMin->left = min->right;
        min->right = nullptr;
    } else {
        parentMin->left = nullptr;
    }

    if (parent)
        parent->left == removable ? parent->left = min : parent->right = min;

    if (removable == root)
        root = min;

    if (min != rightChild)
        min->right = rightChild;

    min->left = leftChild;
    delete removable;
    --size;
}

template<class T>
bool BinaryTree<T>::find(T data) const
{
    if (!root) return false;
    if (root->data == data) return true;

    Node* found = findImpl(root, data);  // get the parent of the node searched for
    return found != nullptr;                  // if got the parent, then the node is exists
}

template<class T>
typename BinaryTree<T>::Node* BinaryTree<T>::findImpl(Node* node, T data) const
{
    if (node->data == data)
      return node;

    if (node == nullptr || (node->right && node->right->data == data) || (node->left && node->left->data == data))
        return node;                          // find the node's parent

    return data > node->data ? findImpl(node->right, data) : findImpl(node->left, data);
}

template<class T>
void BinaryTree<T>::show() const
{
    if (!root) return;
    showImpl(root);
    std::cout << "\n";
}

template<class T>
void BinaryTree<T>::showImpl(const Node *node) const
{
    if (!node) return;
    showImpl(node->left);
    std::cout << node->data << " ";
    showImpl(node->right);
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
typename BinaryTree<T>::Node* BinaryTree<T>::findParentMin(Node* node) const
{
    if (node->left && node->left->left)
        return findParentMin(node->left);
    return node;
}



#endif  // BINARY_TREE_H

