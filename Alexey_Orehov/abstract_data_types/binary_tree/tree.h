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

//    void init(T value, const std::hash<T> &hash_fn);
    void init(T value, const std::function<int(T)> &hash_fn);
};


template<class T>
class Tree {
private:
    TreeNode<T>* root;
    unsigned long long int size;

//    std::hash<T> hash_fn;
    std::function<int(T)> hash_fn = [](T value){ return (int)value; };
    void insert(TreeNode<T>* subtree, const T& element);
    bool find(TreeNode<T>* subtree, const T& element);
    void remove(TreeNode<T>* subtree, TreeNode<T>* parent, int element);
    TreeNode<T>* delete_node(TreeNode<T>* subtree);

public:
    Tree();
    explicit Tree(const T &element);

    TreeNode<T>* get_root() { return this->root; }

    void insert(const T& element);
    bool find(const T& element);
    void remove(const T& element);

    TreeNode<T>* find_smallest(TreeNode<T>* subtree);

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


//template<typename T>
//void TreeNode<T>::init(T value, const std::hash<T> &hash_fn) {
//    this->element = value;
//    this->hash = hash_fn(value);
//}

template<typename T>
void TreeNode<T>::init(T value, const std::function<int(T)> &hash_fn) {
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
    if (hash_diff < 0) {
        insert(subtree->left, element);
        return;
    }
    // std::cout << "inserted value is already in tree" << std::endl;
}


template<typename T>
bool Tree<T>::find(const T &element) {
    return find(root, element);
}


template<typename T>
bool Tree<T>::find(TreeNode<T> *subtree, const T &element) {
    if (subtree->right == nullptr && subtree->left == nullptr) return false;  // Дошли до конца, элемент не найден

    int hash_diff = hash_fn(element) - subtree->hash;
    if (hash_diff == 0) return true;
    if (hash_diff > 0) return find(subtree->right, element);
    return find(subtree->left, element);  // if (hash_diff < 0)
}


template<typename T>
void Tree<T>::remove(const T &element) {
    this->remove(root, nullptr, hash_fn(element));
}


template<typename T>
void Tree<T>::remove(TreeNode<T> *subtree, TreeNode<T>* parent, int element) {
    if (subtree->right == nullptr && subtree->left == nullptr) return; // Дошли до конца дерева, элемент не найден

    if (element - subtree->hash > 0) {
        if (hash_fn(subtree->right) == element) subtree->right = delete_node(subtree->right);
        else remove(subtree->right, subtree, element);
    }
    else {
        if (hash_fn(subtree->left) == element) subtree->left = delete_node(subtree->left);
        else remove(subtree->left, subtree, element);
    }
}


template<typename T>
TreeNode<T> *Tree<T>::delete_node(TreeNode<T> *subtree) {
    if (subtree->right == nullptr && subtree->left == nullptr) return nullptr;
    if (subtree->right == nullptr) return subtree->left;
    if (subtree->left == nullptr) return subtree->right;
}


template<typename T>
TreeNode<T>* Tree<T>::find_smallest(TreeNode<T> *subtree) {
    if (subtree->left->hash != 0) return find_smallest(subtree->left);
    else return subtree;
}


#endif //PROGRAMMING_TREE_H
