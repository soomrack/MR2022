#ifndef ABSTRUCTDATATYPES_BINARY_TREE_H
#define ABSTRUCTDATATYPES_BINARY_TREE_H


#include<iostream>

using namespace std;

template<class T>
struct Node
{
  Node<T> *left;
  Node<T> *right;
  T key;

  Node(const T &key)
    : left(nullptr), right(nullptr), key(key)
  {}
};

template<class T>
class BSTree
{
  typedef Node<T> Node;
public:
  bool Insert(const T &key)
  {
    if (root == nullptr)
    {
      root = new Node(key);
      return true;
    }
    Node *parent = nullptr;
    Node *cur = root;
    while (cur)
    {
      if (cur->key < key)
      {
        parent = cur;
        cur = cur->right;
      } else if (cur->key > key)
      {
        parent = cur;
        cur = cur->left;
      } else
      {
        return false;
      }
    }
    cur = new Node(key);
    if (parent->key < key)
    {
      parent->right = cur;
    } else
    {
      parent->left = cur;
    }
    return true;
  }

  Node* Find(const T &key)
  {
    Node *cur = root;
    while (cur)
    {
      if (cur->key < key)
        cur = cur->right;
      else if (cur->key > key)
        cur = cur->left;
      else
        return cur;
    }
    return nullptr;
  }

  bool Erase(const T &key)
  {
    Node *parent = nullptr;
    Node *cur = root;
    while (cur)
    {
      if (cur->key < key)
      {
        parent = cur;
        cur = cur->right;
      } else if (cur->key > key)
      {
        parent = cur;
        cur = cur->left;
      } else
      {
        //Found it, start deleting
        //1, left is empty
        //2, right is empty
        //3, neither left nor right are empty
        if (cur->left == nullptr)
        {
          if (cur == root)
          {
            root = cur->right;
          } else
          {
            if (parent->right == cur)
              parent->right = cur->right;
            else
              parent->left = cur->right;
          }

          delete cur;
        } else if (cur->right == nullptr)
        {
          if (cur == root)
          {
            root = cur->left;
          } else
          {
            if (parent->left == cur)
              parent->left = cur->left;
            else
              parent->right = cur->left;
          }

          delete cur;
        } else
        {
          Node *rightMinParent = cur;
          Node *rightMin = cur->right;
          while (rightMin->left)
          {
            rightMinParent = rightMin;
            rightMin = rightMin->left;
          }
          cur->key = rightMin->key;
          if (rightMin == rightMinParent->left)
            rightMinParent->left = rightMin->right;
          else
            rightMinParent->right = rightMin->left;
          delete rightMin;
        }
        return true;
      }
    }
    return false;
  }

  void print()
  {
    printTree(root);
  }

  void printTree(Node *node)
  {
    if (node)
    {
      printTree(node->left);
      std::cout << node->key << ' ';
      printTree(node->right);
    }
  }


private:
  Node *root = nullptr;
};


#endif
