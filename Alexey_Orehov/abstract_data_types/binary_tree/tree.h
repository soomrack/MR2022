#ifndef PROGRAMMING_TREE_H
#define PROGRAMMING_TREE_H


template<class T>
struct Node {
    Node<T>* parent;
    Node<T>* right;
    Node<T>* left;
    T data;
};


template<class T>
class Tree {
private:
    Node<T>* root;
    unsigned long long int size;

public:
    Tree();
    Tree(const Tree<T>& tree);
    Tree(Tree<T>&& tree) noexcept;

};

#endif //PROGRAMMING_TREE_H
