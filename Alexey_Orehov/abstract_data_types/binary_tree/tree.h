#ifndef PROGRAMMING_TREE_H
#define PROGRAMMING_TREE_H

#include <exception>
#include <functional>

//#define HASH_WORKAROUND


template<class T>
struct TreeNode {
    TreeNode<T>* right;
    TreeNode<T>* left;
    T element = {};
    int hash = 0;
#ifndef HASH_WORKAROUND
    TreeNode(const T& element, const std::hash<T> &hash_fn);
#else
    TreeNode(const T& element, const std::function<int(T)> &hash_fn);
#endif
};


template<class T>
class Tree {
private:
    TreeNode<T>* root;

#ifndef HASH_WORKAROUND
    std::hash<T> hash_fn;
#else
    std::function<int(T)> hash_fn = [](T value){ return (int)value; };
#endif

    TreeNode<T>** find_smallest_ptr(TreeNode<T>* subtree);

public:
    Tree();
    explicit Tree(const T &element);

    void insert(const T& element);
    bool find(const T& element);
    void remove(const T& element);
};


template<typename T>
Tree<T>::Tree() : root(nullptr) {}

#ifndef HASH_WORKAROUND
template<typename T>
TreeNode<T>::TreeNode(const T &element, const std::hash<T> &hash_fn)
        : element(element), hash(hash_fn(element)), right(nullptr), left(nullptr) {}
#else
template<typename T>
TreeNode<T>::TreeNode(const T &element, const std::function<int(T)> &hash_fn)
        : element(element), hash(hash_fn(element)), right(nullptr), left(nullptr) {}
#endif

template<typename T>
Tree<T>::Tree(const T &element) : root(new TreeNode<T>(element, hash_fn)) {}


template<typename T>
void Tree<T>::insert(const T &element) {
    if (root == nullptr) {
        root = new TreeNode<T>(element, hash_fn);
        return;
    }
    TreeNode<T>* subtree_root = root;
    TreeNode<T>** insert_cand = nullptr;
    int element_hash = hash_fn(element);
    while (element_hash != subtree_root->hash) {
        if (element_hash > subtree_root->hash) {
            insert_cand = &subtree_root->right;
            if (subtree_root->right == nullptr) break;
            else subtree_root = subtree_root->right;
        } else {
            insert_cand = &subtree_root->left;
            if (subtree_root->left == nullptr) break;
            else subtree_root = subtree_root->left;
        }
    }
    *insert_cand = new TreeNode<T>(element, hash_fn);
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
    TreeNode<T>** parent_ptr = &root;
    int element_hash = hash_fn(element);
    while (*parent_ptr != nullptr) {
        if (element_hash == (*parent_ptr)->hash) break;
        parent_ptr = (element_hash > (*parent_ptr)->hash) ? &((*parent_ptr)->right) : &((*parent_ptr)->left);
    }
    if (*parent_ptr == nullptr) return;
    TreeNode<T>* remove_cand = *parent_ptr;

    if (remove_cand == nullptr) return;
    if (remove_cand->right == nullptr) { *parent_ptr = remove_cand->left; return; }
    if (remove_cand->left == nullptr) { *parent_ptr = remove_cand->right; return; }

    TreeNode<T>** smallest_ptr = find_smallest_ptr(remove_cand->right);
    *parent_ptr = *smallest_ptr;
    (*parent_ptr)->left = remove_cand->left;
    *smallest_ptr = (*parent_ptr)->right;
    (*parent_ptr)->right = remove_cand->right;
    delete remove_cand;
}


template<typename T>
TreeNode<T>** Tree<T>::find_smallest_ptr(TreeNode<T> *subtree) {
    TreeNode<T>** smallest = &subtree;
    while ((*smallest)->left != nullptr) smallest = &((*smallest)->left);
    return smallest;
}


#endif //PROGRAMMING_TREE_H