/*
del O(h) Справа по дереву берем сразу левый или слева по дереву берем самый правый
 */

#include <iostream>
#include <stdexcept>
#include <string>

class Binary_tree_exception: public std::logic_error
{
public:
    explicit Binary_tree_exception(const std::string& message):
            std::logic_error(message)
    {}
};

template <typename T>
class Binary_tree {

private:
    template<typename N>
    struct Tree_node {
        T key;
        Tree_node* left;
        Tree_node* right;

        explicit Tree_node(N data = N(),
                  Tree_node* left = nullptr, Tree_node* right = nullptr) {
            this->key = data;
            this->left = left;
            this->right = right;
        }
    };

    Tree_node<T>* root;
    int height;

    void add_child(Tree_node<T>*);
    void delete_child(Tree_node<T>*);

public:
    Binary_tree();
    explicit Binary_tree(int);
    Binary_tree(const Binary_tree&);
    ~Binary_tree();
    Binary_tree& operator=(const Binary_tree&);

    void add(T elem);
    bool is_find(T elem);
    void delete_tree();
    void del(T element); // TODO:

    unsigned get_height() {return height;}
};

template<typename T>
Binary_tree<T>::Binary_tree():
    root(nullptr),
    height(-1)
{}

template<typename T>
Binary_tree<T>::Binary_tree(int root_element):
    height(0)
{
    root = new Tree_node<T>(root_element, nullptr, nullptr);
}

template<typename T>
Binary_tree<T>::~Binary_tree() {
    delete_tree();
}

template<typename T>
void Binary_tree<T>::add(const T elem) {
    Tree_node<T>** link = &root;
    int temp_height = 0;
    while(*link != nullptr) {
        link = elem < (*link)->key ? &((*link)->left) : &((*link)->right);
        temp_height++;
    }
    *link = new Tree_node<T>(elem);
    height = std::max(height, temp_height);
}

// нужно ли бросать исключение, когда пытаемся внести существующий элемент?
template<typename T>
bool Binary_tree<T>::is_find(const T elem) {
    Tree_node<T>* temp = root;
    while (temp != nullptr) {
        if (elem == temp->key) return true;
        temp = (elem < temp->key) ? temp->left : temp->right;
    }
    return false;
}

template<typename T>
Binary_tree<T>::Binary_tree(const Binary_tree& other):
    height(-1),
    root(nullptr)
{
    add(other.root->key);
    add_child(other.root);
}

template<typename T>
Binary_tree<T> &Binary_tree<T>::operator=(const Binary_tree& other) {
    if (this == &other) {
        return *this;
    }
    Binary_tree<T> temp(other);
    std::swap(this->height, temp.height);
    std::swap(this->root, temp.root);
    return *this;
}

template<typename T>
void Binary_tree<T>::add_child(Binary_tree::Tree_node<T> * node) {
    if (node->left != nullptr) {
        add(node->left->key);
        add_child(node->left);
    }
    if (node->right != nullptr) {
        add(node->right->key);
        add_child(node->right);
    }
}

template<typename T>
void Binary_tree<T>::delete_child(Binary_tree::Tree_node<T>* node) {
    if ((node->left != nullptr) || (node->right != nullptr)) height--;
    if (node->left != nullptr) {
        delete_child(node->left);
        node->left = nullptr;
    }
    if (node->right != nullptr) {
        delete_child(node->right);
        node->right = nullptr;
    }
    delete[] node;
}

template<typename T>
void Binary_tree<T>::delete_tree() {
    if (root == nullptr) return;
    delete_child(root);
    root = nullptr;
}

template<typename T>
void Binary_tree<T>::del(const T element) {

}

int main() {
    Binary_tree<int> test(10);
    test.add(15);
    test.add(5);
    test.add(1);
    test.add(7);
    test.add(100);
    test.add(12);
    test.add(6);
    Binary_tree<int> test2(test);
    test2.delete_tree();
    std::cout << test.get_height() << "\t" << test.is_find(100) << std::endl;
    return 0;
}