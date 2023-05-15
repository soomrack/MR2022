#include <iostream>


template <typename Q>
class BinaryTreeNode {
public:
    BinaryTreeNode(Q data,
                   BinaryTreeNode * left = nullptr,
                   BinaryTreeNode * right = nullptr);
    Q Value;
    BinaryTreeNode<Q>* Left;
    BinaryTreeNode<Q>* Right;
};


template <typename Q>
class BinaryTree
{
public:
    BinaryTree();
    ~BinaryTree();

    int Size();

    bool Find(Q value);
    void Erase(Q value);
    void Clear();
    void Insert(Q value);
    template <typename R>friend std::ostream& operator <<(std::ostream& ostr, const BinaryTree<R> &rhs);


private:
    BinaryTreeNode<Q>* head;
    template <typename R>std::ostream& Print(std::ostream& ostr, BinaryTreeNode<R>* rhs) const ; //tree node pointer
    void DeleteNodeButChildrenFirst(BinaryTreeNode<Q>* Node);
    int FindSize(BinaryTreeNode<Q>* Node);
};