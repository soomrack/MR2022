#include "btree.h"
#include <exception>
#include "except.h"


AtypesException FAILTOERASE("Trying to erase from empty binary tree!");
AtypesException FAILTOFIND("Trying to find into empty binary tree!");

template <typename Q>
BinaryTreeNode<Q>::BinaryTreeNode(Q data,
                                  BinaryTreeNode<Q>* left,
                                  BinaryTreeNode<Q>* right)
        : Value(data),
          Left(left),
          Right(right)
{
    //?
}

template <typename Q>
BinaryTree<Q>::BinaryTree() : head(nullptr) {

}

template <typename Q>
void BinaryTree<Q>::Insert(Q value)
{
    if (head == nullptr) head = new BinaryTreeNode(value);
    else
    {
        BinaryTreeNode<Q>* Current = head;
        while (true)
            if(value < Current->Value)
                if(Current->Left == nullptr)
                {
                    Current->Left = new BinaryTreeNode(value);
                    break;
                }
                else Current = Current->Left;
            else if (value > Current->Value)
                if(Current->Right == nullptr)
                {
                    Current->Right = new BinaryTreeNode(value);
                    break;
                }
                else Current = Current->Right;
            else break;
    }
}

template <typename R>
std::ostream &operator<<(std::ostream &ostr, const BinaryTree<R> &rhs)   {
    return rhs.Print(ostr, rhs.head);
}

// declare Q templates int the operator<< as friends
template <class Q> template<typename R>
std::ostream &BinaryTree<Q>::Print(std::ostream &ostr, BinaryTreeNode<R> *rhs) const {
    // print tree from left to right
    if (rhs != nullptr)
    {
        Print(ostr, rhs->Left);
        std::cout << " " << rhs->Value;
        Print(ostr, rhs->Right);
    }
    return  ostr;
}

template <typename Q>
BinaryTree<Q>::~BinaryTree() {
    Clear();
}

template <typename Q>
void BinaryTree<Q>::Clear() {
    DeleteNodeButChildrenFirst(head);
    head = nullptr;
}

template <typename Q>
void BinaryTree<Q>::DeleteNodeButChildrenFirst(BinaryTreeNode<Q>* Node) {
    if (Node != nullptr) {
        DeleteNodeButChildrenFirst(Node->Left);
        DeleteNodeButChildrenFirst(Node->Right);
        delete Node;
    }
}

template <typename Q>
void BinaryTree<Q>::Erase(Q value) {
    BinaryTreeNode<Q>* temp = head, * parent = head, * marker;
    // temp - current pointer
    if (temp == nullptr)
        throw FAILTOERASE;

    else {
        while (temp != nullptr && temp->Value != value) {
            parent = temp;
            if (temp->Value < value) {
                temp = temp->Right;
            } else {
                temp = temp->Left;
            }
        }
    }
    marker = temp;
    if (temp == nullptr) {}
    else if(temp == head) {
        if (temp->Right == nullptr && temp->Left == nullptr) head = nullptr;
        else if (temp->Left == nullptr) head = temp->Right;
        else if (temp->Right == nullptr) head = temp->Left;
        else {
            BinaryTreeNode<Q>* temp1;
            temp1 = temp->Right;
            while (temp1->Left != nullptr) {
                temp = temp1;
                temp1 = temp1->Left;
            }
            if (temp1 != temp->Right) {
                temp->Left = temp1->Right;
                temp1->Right = head->Right;
            }
            temp1->Left = head->Left;
            head = temp1;
        }
    }
    else {
        if (temp->Right == nullptr && temp->Left == nullptr)
        {
            if (parent->Right == temp) parent->Right = nullptr;
            else parent->Left = nullptr;
        }
        else if (temp->Left == nullptr)
        {
            if (parent->Right == temp) parent->Right = temp->Right;
            else parent->Left = temp->Left;
        }
        else if (temp->Right == nullptr)
        {
            if (parent->Right == temp) parent->Right = temp->Left;
            else parent->Left = temp->Left;
        }
        else {
            BinaryTreeNode<Q>* temp1;
            parent = temp;
            temp1 = temp->Right;
            while (temp1->Left != nullptr) {
                parent = temp1;
                temp1 = temp1->Left;
            }
            if (temp1 != temp->Right) {
                temp->Left = temp1->Right;
                temp1->Right = parent->Right;
            }
            temp1->Left = parent->Left;
        }
    }
    delete marker;
}

template <typename Q>
bool BinaryTree<Q>::Find(Q value) {
    BinaryTreeNode<Q>* Current = head;
    if (Current == nullptr) throw FAILTOFIND;
    while (Current != nullptr)
    {
        if (Current->Value == value) return true;
        else if (Current->Value > value) Current = Current->Left;
        else Current = Current->Right;
    }
    return false;
}

template <typename Q>
int BinaryTree<Q>::Size() {
    return FindSize(head);
}

template <typename Q>
int BinaryTree<Q>::FindSize(BinaryTreeNode<Q>* Node) {
    if (Node != nullptr) return 1 + FindSize(Node->Left) + FindSize(Node->Right);
}


int main() {
    BinaryTree <double>A;
    for (int i = 1; i <= 10; ++i)
    {
        int val = i;
        A.Insert(val);
        std::cout << val << "\t";
    }

    std::cout << A << std::endl;

    try {
        A.Erase(1);
    }
    catch(std::exception e)
    {
        std::cerr << "Caught: " << e.what() << std::endl;
        std::cerr << "Type: " << typeid(e).name() << std::endl;
    }
    std::cout << "Erasing..." << A << std::endl;

    try {
        std::cout << "FIND 1: " << A.Find(1) << std::endl;
        std::cout << "FIND 2: " << A.Find(2) << std::endl;
    }
    catch(std::exception e)
    {
        std::cerr << "Caught: " << e.what() << std::endl;
        std::cerr << "Type: " << typeid(e).name() << std::endl;
    }
    std::cout << "Binary tree SIZE: " << A.Size() << std::endl;
    A.Clear();
    std::cout << A << std::endl;
    return 0;
}