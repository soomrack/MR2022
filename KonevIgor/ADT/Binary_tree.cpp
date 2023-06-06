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

template<typename N>
class Tree_node {
public:
    N key;
    Tree_node* left;
    Tree_node* right;

    explicit Tree_node(N data = N(),
                       Tree_node* left = nullptr, Tree_node* right = nullptr) {
        this->key = data;
        this->left = left;
        this->right = right;
    }
};

template <typename T>
class Binary_tree {

private:

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
    Tree_node<T>* find_elem(T elem);
    Tree_node<T>* find_parent(T elem);
    void delete_tree();
    void del(T element);

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
    Tree_node<T>** temp = &root;
    int temp_height = 0;
    while(*temp != nullptr) {
        temp = elem < (*temp)->key ? &((*temp)->left) : &((*temp)->right);
        temp_height++;
    }
    *temp = new Tree_node<T>(elem);
    height = std::max(height, temp_height);
}

// нужно ли бросать исключение, когда пытаемся внести существующий элемент?
template<typename T>
bool Binary_tree<T>::is_find(const T elem) {
    Tree_node<T>** temp = &root;
    while (*temp != nullptr) {
        if (elem == (*temp)->key) return true;
        *temp = (elem < (*temp)->key) ? (*temp)->left : (*temp)->right;
    }
    return false;
}

template<typename T>
Tree_node<T>* Binary_tree<T>::find_parent(T elem) {
    Tree_node<T>* temp = root;
    while (temp != nullptr) {
        if ((temp->left != nullptr) && (elem == temp->left->key)) return temp;
        if ((temp->right != nullptr) && (elem == temp->right->key)) return temp;
        temp = (elem < temp->key) ? temp->left : temp->right;
    }
    return nullptr;
}

template<typename T>
Tree_node<T>* Binary_tree<T>::find_elem(T elem) {
    Tree_node<T>* temp = root;
    while (temp != nullptr) {
        if (elem == temp->key) return temp;
        temp = (elem < temp->key) ? temp->left : temp->right;
    }
    return nullptr;
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
void Binary_tree<T>::add_child(Tree_node<T> * node) {
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
void Binary_tree<T>::delete_child(Tree_node<T>* node) {
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
    Tree_node<T>* temp = find_elem(element);

    if ((temp == root) && (temp->right == nullptr || temp->left == nullptr)) {
        if (temp->right != nullptr) {
            root->right->left = root->left;
            root = temp->right;
        } else {
            root->left->right = root->right;
            root = temp->left;
        }
        return;
    }

    if (temp->left == nullptr && temp->right == nullptr) {
        Tree_node<T>* parent = find_parent(element);
        if (parent->key < element) {parent->right = nullptr; return;}
        if (parent->key > element) {parent->left = nullptr; return;}
    }

    if (temp->left == nullptr || temp->right == nullptr) {
        Tree_node<T>* parent = find_parent(element);
        if (parent->key < element) {
            parent->right = (temp->left == nullptr) ? temp->right : temp->left;
            return;}
        if (parent->key > element) {
            parent->left = (temp->left == nullptr) ? temp->right : temp->left;
            return;}
    }

    Tree_node<T>* temp_2 = temp->left;
    while (temp_2->right != nullptr) temp_2 = temp_2->right;
    del(temp_2->key);
    temp->key = temp_2->key;
}

int main() {
    Binary_tree<int> test(10);
//    test.add(15);
//    test.add(5);
//    test.add(1);
//    test.add(7);
//    test.add(100);
//    test.add(12);
//    test.add(6);
//    test.add(2);
    Binary_tree<int> test2(test);
    test2.delete_tree();
    std::cout << test.get_height() << "\t" << test.is_find(10) << std::endl;
    test.del(10);
    return 0;
}