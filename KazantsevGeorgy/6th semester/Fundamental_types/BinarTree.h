#include <iostream>
#include <limits>
using namespace std;



template <typename SPIDER>
class Node
{
public:
    SPIDER value;
    int key;
    Node *left;
    Node *right;
    Node();
    Node(SPIDER _value, int _key);
    Node(const Node &other);
    bool is_leaf();
};


template <typename SPIDER>
class BinaryTree
{

protected:
    Node<SPIDER> *root;
    int BinaryTreeSize = 0;
public:
    unsigned int height();
    BinaryTree();
    BinaryTree(SPIDER _value);
    ~BinaryTree();
    void add(SPIDER _value);
    SPIDER get(int _key);
    bool find(int _key);
    void remove(int _key);
    void print();
    Node<SPIDER>* get_node(int _key);
    bool find(int _key, Node<SPIDER>* _tree);
    unsigned int height(Node<SPIDER>* _tree);
    void remove(Node<SPIDER>* _tree);
    void print(Node<SPIDER>* _tree);
    void add(SPIDER _value, int _key, Node<SPIDER> *_tree);
};


template <typename SPIDER>
Node<SPIDER>::Node() {
    value = 0.0;
    key = 0;
    left = nullptr;
    right = nullptr;
}


template <typename SPIDER>
Node<SPIDER>::Node(SPIDER _value, int _key) {
    value = _value;
    key = _key;
    left = nullptr;
    right = nullptr;
}

template <typename SPIDER>
bool Node<SPIDER>::is_leaf() {
    return ((left == nullptr) && (right == nullptr));
}

template <typename SPIDER>
Node<SPIDER>::Node(const Node &other) {
    value = other.value;
    key = other.key;
    left = other.left;
    right = other.right;
}


// ''' '''
template <typename SPIDER>
BinaryTree<SPIDER>::BinaryTree() {
    root = nullptr;
}

template <typename SPIDER>
BinaryTree<SPIDER>::BinaryTree(SPIDER _value) {
    root = new Node<SPIDER>(_value, get_key(_value));
}

template <typename SPIDER>
BinaryTree<SPIDER>::~BinaryTree() {
    remove(root->key);
}


//void Tree<SPIDER>::deleteTree(Node <SPIDER> *curr)
//{
   // if (curr==0)
  //  {
 //       deleteTree(curr->left);
 //       deleteTree(curr->right);
  //      delete curr;
 //   }
 //   BinaryTreeSize = 0;
//}
template <typename SPIDER>
void BinaryTree<SPIDER>::add(SPIDER _value) {
    if (root == nullptr){
        root = new Node<SPIDER>(_value, get_key(_value));
        return;
    }
    add(_value, get_key(_value), root);
}


template <typename SPIDER>
void BinaryTree<SPIDER>::add(SPIDER _value, int _key, Node<SPIDER>* _tree) {
    Node<SPIDER>* next_branch = nullptr; //создаем новую ветку
    if (_tree->key > _key){
        if (_tree->left == nullptr){
            _tree->left = new Node<SPIDER>(_value, _key);
            return;
        }
        next_branch = _tree->left;
    } else {
        if (_tree->right == nullptr){
            _tree->right = new Node<SPIDER>(_value, _key);
            return;
        }
        next_branch = _tree->right;
    }
    add(_value, _key, next_branch);
}

template <typename SPIDER>
Node<SPIDER>* BinaryTree<SPIDER>::get_node(int _key) {
    if (root == nullptr) return nullptr;
    Node<SPIDER>* node = root;
    while (node != nullptr){
        if (node->key == _key) return node;
        node = (node->key > _key) ? node->left : node->right;
    }
    return nullptr;
}

template <typename SPIDER>
SPIDER BinaryTree<SPIDER>::get(int _key) {
    return get_node(_key)->value;
}

template <typename SPIDER>
bool BinaryTree<SPIDER>::find(int _key, Node<SPIDER> *_tree) {
    if (_tree == nullptr) return false;
    if (_tree->key == _key) return true;

    Node<SPIDER>* next_branch = (_key < _tree->key) ? _tree->left : _tree->right;
    return find(_key, next_branch);
}


template <typename SPIDER>
bool BinaryTree<SPIDER>::find(int _key) {
    return find(_key, root);
}


template <typename SPIDER>
unsigned int BinaryTree<SPIDER>::height() {
    return height(root);
}


template <typename SPIDER>
unsigned int BinaryTree<SPIDER>::height(Node<SPIDER>* _tree) {
    if (_tree == nullptr) return 0;
    if (_tree->is_leaf()) return 1;
    return max(height(_tree->left), height(_tree->right)) + 1;
}

template <typename SPIDER>
void BinaryTree<SPIDER>::remove(int _key) {

    if (root->key == _key){
        remove(root);
        root = nullptr;
        return;
    }

    Node<SPIDER>* node = root;
    while (true){
        if (node->left != nullptr)
            if (node->left->key == _key){
                remove(node->left);
                node->left = nullptr;
                return;
            }

        if (node->right != nullptr)
            if (node->right->key == _key){
                remove(node->right);
                node->right = nullptr;
                return;
            }

        node = (_key < node->key) ? node->left : node->right;
    }
}

template <typename SPIDER>
void BinaryTree<SPIDER>::remove(Node<SPIDER>*_tree) {
    if (_tree == nullptr) return;

    if (_tree->is_leaf()){
        delete _tree;
        return;
    }

    remove(_tree->left);
    _tree->left = nullptr;
    remove(_tree->right);
    _tree->right = nullptr;

}

template <typename SPIDER>
void BinaryTree<SPIDER>::print(Node<SPIDER>* _tree) {
    if (_tree == nullptr) return;

    std::cout << "The " << _tree->value << "[" << _tree->key << "]";
    if (_tree->is_leaf()){
        std::cout << "\n";
        return;
    }

    if (_tree->left != nullptr) {
        std::cout << " has on the left side " << _tree->left->value;
        if (_tree->right != nullptr)
            std::cout << "  and ";
    }
    if (_tree->right != nullptr){
        std::cout << " has on the right side " << _tree->right->value;
    }
    std::cout << "\n";

    print(_tree->left);
    print(_tree->right);
}

template <typename SPIDER>
void BinaryTree<SPIDER>::print() {
    if (root == nullptr){
        std::cout << "There is no one element in this tree\n";
        return;
    }

    std::cout << "The root is " << this->root->value << "\n";
    this->print(root);
    std::cout << "\n";
}

int get_key(double val) {
    return int(179 + 179 * val + 179 * val * val);
}
//https://www.strchr.com/hash_functions#results