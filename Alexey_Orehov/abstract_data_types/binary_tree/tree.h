#ifndef PROGRAMMING_TREE_H
#define PROGRAMMING_TREE_H

#include <exception>


class TreeException: public std::exception {
public:
    explicit TreeException(const char* msg) : std::exception() {}
};


template<class T>
struct TreeNode {
    TreeNode<T>* parent;
    TreeNode<T>* right;
    TreeNode<T>* left;
    T element = {};

    bool is_leaf = true;

    TreeNode(TreeNode<T>* parent, TreeNode<T>* right, TreeNode<T>* left): parent(parent), right(right), left(left) {}
};


template<class T>
class Tree {
private:
    TreeNode<T>* root;
    unsigned long long int size;

    void insert(TreeNode<T>* new_root, const T& element);
    bool find(TreeNode<T>* new_root, const T& element);

public:
    Tree();
    explicit Tree(const T &element);
//    Tree(const Tree<T>& tree);
//    Tree(Tree<T>&& tree) noexcept;

    void insert(const T& element);
    bool find(const T& element);
};


template<typename T>
Tree<T>::Tree() {
    size = 0;
    root = new TreeNode<T>(nullptr, nullptr, nullptr);
}


template<typename T>
Tree<T>::Tree(const T &element) {
    size = 0;
    root = new TreeNode<T>(nullptr, nullptr, nullptr);
    this->insert(root, element);
}


template<typename T>
void Tree<T>::insert(const T &element) {
    this->insert(root, element);
}


template<typename T>
void Tree<T>::insert(TreeNode<T> *new_root, const T &element) {
    if (new_root->is_leaf) {
        new_root->element = element;
        new_root->right = new TreeNode<T>(new_root, nullptr, nullptr);
        new_root->left = new TreeNode<T>(new_root, nullptr, nullptr);
        new_root->is_leaf = false;
        size += 1;
        return;
    }
    if (new_root->element < element) {
        insert(new_root->left, element);
        return;
    }
    if (new_root->element > element) {
        insert(new_root->right, element);
        return;
    }
}


template<typename T>
bool Tree<T>::find(const T &element) {
    return find(root, element);
}


template<typename T>
bool Tree<T>::find(TreeNode<T> *new_root, const T &element) {
    if (new_root != nullptr) {
        if (new_root->element == element) return true;
        if (new_root->element > element) return find(new_root->right, element);
        if (new_root->element < element) return find(new_root->left, element);
    }
    return false;
}

#endif //PROGRAMMING_TREE_H
