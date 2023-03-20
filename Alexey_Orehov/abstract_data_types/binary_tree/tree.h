#ifndef PROGRAMMING_TREE_H
#define PROGRAMMING_TREE_H

#include <exception>
#include <functional>


class TreeException: public std::exception {
public:
    explicit TreeException(const char* msg) : std::exception() {}
};


template<class T>
struct TreeNode {
    TreeNode<T>* right;
    TreeNode<T>* left;
    T element = {};
    int hash = 0;

    TreeNode(TreeNode<T>* right, TreeNode<T>* left): right(right), left(left) {}

    void init(T value, const std::hash<T> &hash_fn);
};


template<class T>
class Tree {
private:
    TreeNode<T>* root;
    unsigned long long int size;

    std::hash<T> hash_fn;

    void insert(TreeNode<T>* subtree, const T& element);
    bool find(TreeNode<T>* subtree, const T& element);

public:
    Tree();
    explicit Tree(const T &element);

    void insert(const T& element);
    bool find(const T& element);
};


template<typename T>
Tree<T>::Tree() {
    size = 0;
    root = new TreeNode<T>(nullptr, nullptr);
}


template<typename T>
Tree<T>::Tree(const T &element) {
    size = 0;
    root = new TreeNode<T>(nullptr, nullptr);
    this->insert(root, element);
}


template<typename T>
void TreeNode<T>::init(T value, const std::hash<T> &hash_fn) {
    this->element = value;
    this->hash = hash_fn(value);
}


template<typename T>
void Tree<T>::insert(const T &element) {
    this->insert(root, element);
}


template<typename T>
void Tree<T>::insert(TreeNode<T> *subtree, const T &element) {
    if (subtree->hash == 0) {
        subtree->init(element, hash_fn);
        subtree->right = new TreeNode<T>(nullptr, nullptr);
        subtree->left = new TreeNode<T>(nullptr, nullptr);
        size += 1;
        return;
    }

    int hash_diff = hash_fn(element) - subtree->hash;

    if (hash_diff > 0) {
        insert(subtree->right, element);
        return;
    }
    // if (hash_diff < 0)
    insert(subtree->left, element);
}


template<typename T>
bool Tree<T>::find(const T &element) {
    return find(root, element);
}


template<typename T>
bool Tree<T>::find(TreeNode<T> *subtree, const T &element) {
    if (subtree->hash == 0) return false;

    int hash_diff = hash_fn(element) - subtree->hash;
    if (hash_diff == 0) return true;
    if (hash_diff > 0) return find(subtree->right, element);
    // if (hash_diff < 0)
    return find(subtree->left, element);
}

#endif //PROGRAMMING_TREE_H
