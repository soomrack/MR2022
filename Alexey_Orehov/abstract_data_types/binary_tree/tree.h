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

//    TreeNode(const T& element, const std::hash<T> &hash_fn);
    TreeNode(const T& element, const std::function<int(T)> &hash_fn);

    TreeNode(TreeNode<T>* right, TreeNode<T>* left): right(right), left(left) {}
};


template<class T>
class Tree {
private:
    TreeNode<T>* root;
    unsigned long long int size;

//    std::hash<T> hash_fn;
    std::function<int(T)> hash_fn = [](T value){ return (int)value; };

    TreeNode<T>* delete_node(TreeNode<T>* subtree);
    TreeNode<T>** find_smallest_ptr(TreeNode<T>* subtree);

public:
    Tree();
    explicit Tree(const T &element);

    TreeNode<T>* get_root() { return this->root; }

    void insert(const T& element);
    bool find(const T& element);
    void remove(const T& element);
};


template<typename T>
Tree<T>::Tree() {
    size = 0;
    root = nullptr;
}


//template<typename T>
//TreeNode<T>::TreeNode(const T &element, const std::hash<T> &hash_fn)
//        : element(element), hash(hash_fn(element)), right(nullptr), left(nullptr) {}


template<typename T>
TreeNode<T>::TreeNode(const T &element, const std::function<int(T)> &hash_fn)
        : element(element), hash(hash_fn(element)), right(nullptr), left(nullptr) {}

template<typename T>
Tree<T>::Tree(const T &element) {
    size = 0;
    root = new TreeNode<T>(element, hash_fn);
}


template<typename T>
void Tree<T>::insert(const T &element) {
    if (root == nullptr) {
        root = new TreeNode<T>(element, hash_fn);
        return;
    }

    TreeNode<T>* subtree_root = root;
    for (;;) {
        int hash_diff = hash_fn(element) - subtree_root->hash;
        if (hash_diff == 0) return;
        if (hash_diff > 0) {
            if (subtree_root->right == nullptr) subtree_root->right = new TreeNode<T>(element, hash_fn);
            else subtree_root = subtree_root->right;
        } else {
            if (subtree_root->left == nullptr) subtree_root->left = new TreeNode<T>(element, hash_fn);
            else subtree_root = subtree_root->left;
        }
    }
}


template<typename T>
bool Tree<T>::find(const T &element) {
    TreeNode<T>* subtree_root = root;
    while (subtree_root != nullptr) {
        int hash_diff = hash_fn(element) - subtree_root->hash;
        if (hash_diff == 0) return true;
        subtree_root = (hash_diff > 0) ? subtree_root->right : subtree_root->left;
    }
    return false;
}


template<typename T>
void Tree<T>::remove(const T &element) {
    TreeNode<T>* remove_cand = root;
    TreeNode<T>** parent_ptr = nullptr;
    while (remove_cand != nullptr) {
        int hash_diff = hash_fn(element) - remove_cand->hash;
        if (hash_diff == 0) break;
        if (hash_diff > 0) {
            parent_ptr = &remove_cand->right;
            remove_cand = remove_cand->right;
        } else {
            parent_ptr = &remove_cand->left;
            remove_cand = remove_cand->left;
        }
    }
    if (remove_cand == nullptr) return;
    if (remove_cand->right == nullptr && remove_cand->left == nullptr) { *parent_ptr = nullptr; return; }
    if (remove_cand->right == nullptr) { *parent_ptr = remove_cand->left; return; }
    if (remove_cand->left == nullptr) { *parent_ptr = remove_cand->right; return; }

    TreeNode<T>** smallest_ptr = find_smallest_ptr(remove_cand->right);
    *parent_ptr = *smallest_ptr;  // A = B
    (*parent_ptr)->left = remove_cand->left;
    *smallest_ptr = (*parent_ptr)->right;
    (*parent_ptr)->right = remove_cand->right;
    delete remove_cand;
}


template<typename T>
TreeNode<T>** Tree<T>::find_smallest_ptr(TreeNode<T> *subtree) {
    TreeNode<T>** smallest = &subtree->left;  // Указатель на указатель на левый элемент в поддереве
    for (;;) {
        if ((*smallest)->left == nullptr) break;
        smallest = &((*smallest)->left);
    }
    return smallest;
}


#endif //PROGRAMMING_TREE_H
