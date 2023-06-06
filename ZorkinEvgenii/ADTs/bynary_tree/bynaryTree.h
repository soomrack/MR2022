#ifndef PROGRAMMING_TREE_H
#define PROGRAMMING_TREE_H

#include <functional>  // для хеша

template<class T>
class TreeNode {
public:
    TreeNode<T>* right;
    TreeNode<T>* left;
    int hash = 0;

    TreeNode(const T& element, const std::hash<T> &hash_fn);
};


template<class T>
class Tree {
private:
    TreeNode<T>* root;

    std::hash<T> hash_fn;

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

template<typename T>
TreeNode<T>::TreeNode(const T &element, const std::hash<T> &hash_fn)
        : hash(hash_fn(element)), right(nullptr), left(nullptr) {}

template<typename T>
Tree<T>::Tree(const T &element) : root(new TreeNode<T>(element, hash_fn)) {}


template<typename T>
void Tree<T>::insert(const T &element) {
    if (root == nullptr) {                         // если дерево пустое то повторяет конструктор выше
        root = new TreeNode<T>(element, hash_fn);
        return;
    }
    TreeNode<T>* subtree_root = root;
    TreeNode<T>** insert_cand = nullptr;   // ** тк у дерева его листа нет ссылки на родителя
    int element_hash = hash_fn(element);
    while (element_hash != subtree_root->hash) {
        if (element_hash > subtree_root->hash) {
            insert_cand = &subtree_root->right;
            if (subtree_root->right == nullptr) break;  // и в итоге выход из цикла
            else subtree_root = subtree_root->right;  // постепенно перенос корня (если не было выхода выше)
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
    /// ^^^^ Поиск элемента для удаления ^^^^

    if (remove_cand == nullptr) return; // если не нашли эл для удаления то нечего удалять
    if (remove_cand->right == nullptr) { *parent_ptr = remove_cand->left; delete remove_cand; return; } // замена птр перента на птр левый дочерний удаляемого эл
    if (remove_cand->left == nullptr) { *parent_ptr = remove_cand->right; delete remove_cand; return; } // наоборот
    /// ^^^^ Обработка случаев где есть 0 или 1 наследник

    TreeNode<T>** smallest_ptr = find_smallest_ptr(remove_cand->right);
    *parent_ptr = *smallest_ptr;  // Ссылка в отцовском указателе на удаляемый элемент заменяется на наименьший элемент в правом (большем) поддереве удаляемого  A = B
    (*parent_ptr)->left = remove_cand->left;  // Левое поддерево удаляемого подставляем в новый элемент на месте удаленного  C = E
    *smallest_ptr = (*parent_ptr)->right;  // Правое поддерево нового элемента на месте удаленного равно правому поддереву удаленного элемента D = F
    (*parent_ptr)->right = remove_cand->right;  // Правое поддерево наименьшего элемента удаляем с его места  B = D
    delete remove_cand;
}


template<typename T>
TreeNode<T>** Tree<T>::find_smallest_ptr(TreeNode<T> *subtree) {   // Находим ссылку на наименьший элемент следуя влево (лево=самый малый) всегда
    TreeNode<T>** smallest = &subtree;
    while ((*smallest)->left != nullptr) smallest = &((*smallest)->left);
    return smallest;
}


#endif //PROGRAMMING_TREE_H