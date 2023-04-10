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

    TreeNode(const T& element, const std::hash<T> &hash_fn);
//    TreeNode(const T& element, const std::function<int(T)> &hash_fn);

    TreeNode(TreeNode<T>* right, TreeNode<T>* left): right(right), left(left) {}
};


template<class T>
class Tree {
private:
    TreeNode<T>* root;
    unsigned long long int size;

    std::hash<T> hash_fn;
//    std::function<int(T)> hash_fn = [](T value){ return (int)value; };

    void insert(TreeNode<T>* subtree, const T& element);
    bool find(TreeNode<T>* subtree, const T& element);
    void find_remove_cand(TreeNode<T>* subtree, TreeNode<T>* parent, int element);
    TreeNode<T>* delete_node(TreeNode<T>* subtree);
    TreeNode<T>* find_smallest(TreeNode<T>* subtree);

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
//TreeNode<T>::TreeNode(const T &element, const std::function<int(T)> &hash_fn)
//        : element(element), hash(hash_fn(element)), right(nullptr), left(nullptr) {}

template<typename T>
TreeNode<T>::TreeNode(const T &element, const std::hash<T> &hash_fn)
        : element(element), hash(hash_fn(element)), right(nullptr), left(nullptr) {}


template<typename T>
Tree<T>::Tree(const T &element) {
    size = 0;
    root = new TreeNode<T>(element, hash_fn);
}


template<typename T>
void Tree<T>::insert(const T &element) {
    if (root == nullptr) root = new TreeNode<T>(element, hash_fn);
    else this->insert(root, element);
}


template<typename T>
void Tree<T>::insert(TreeNode<T> *subtree, const T &element) {
    int hash_diff = hash_fn(element) - subtree->hash;
    if (hash_diff > 0) {
        if (subtree->right != nullptr) insert(subtree->right, element);
        else {
            subtree->right = new TreeNode<T>(element, hash_fn);
            size += 1;
        }
        return;
    }
    if (hash_diff < 0) {
        if (subtree->left != nullptr) insert(subtree->left, element);
        else {
            subtree->left = new TreeNode<T>(element, hash_fn);
            size += 1;
        }
        return;
    }
}


template<typename T>
bool Tree<T>::find(const T &element) {
    return find(root, element);
}


template<typename T>
bool Tree<T>::find(TreeNode<T> *subtree, const T &element) {
    if (subtree == nullptr) return false;  // Дошли до конца, элемент не найден

    int hash_diff = hash_fn(element) - subtree->hash;
    if (hash_diff == 0) return true;
    if (hash_diff > 0) return find(subtree->right, element);
    return find(subtree->left, element);  // if (hash_diff < 0)
}


template<typename T>
void Tree<T>::remove(const T &element) {
    this->find_remove_cand(root, nullptr, hash_fn(element));
}


template<typename T>
void Tree<T>::find_remove_cand(TreeNode<T> *subtree, TreeNode<T>* parent, int element) {
    if (subtree->right == nullptr && subtree->left == nullptr) return; // Дошли до конца дерева, элемент не найден

    if (element - subtree->hash > 0) {
        if (subtree->right->hash == element) subtree->right = delete_node(subtree->right);
        else find_remove_cand(subtree->right, subtree, element);
    }
    else {
        if (subtree->left->hash == element) subtree->left = delete_node(subtree->left);
        else find_remove_cand(subtree->left, subtree, element);
    }
}


template<typename T>
TreeNode<T> *Tree<T>::delete_node(TreeNode<T> *subtree) {
    if (subtree->right == nullptr && subtree->left == nullptr) return nullptr;
    if (subtree->right == nullptr) return subtree->left;
    if (subtree->left == nullptr) return subtree->right;

    TreeNode<T>* min_right_node = find_smallest(subtree->right);
    subtree->element = min_right_node->element;
    subtree->hash = min_right_node->hash;
    find_remove_cand(subtree->right, subtree, min_right_node->hash);
    return subtree;
}


template<typename T>
TreeNode<T>* Tree<T>::find_smallest(TreeNode<T> *subtree) {
    if (subtree->left != nullptr) return find_smallest(subtree->left);
    else {
        subtree->left = nullptr;
        return subtree;
    }
}


#endif //PROGRAMMING_TREE_H
