#include <iostream>


class Node {
public:
    Node* left;
    Node* right;
    int val;
    int key;
    Node(int val_temp, int key_temp) : val(val_temp), key(key_temp), left(nullptr), right(nullptr) {}
};

class Exception : public std::domain_error
{
public:
    Exception(const char* const message) : std::domain_error(message) {}
};
Exception incoorect_val("you try to find incoorect val");

class Tree {
private:
    Node* root;

public:
    Tree() : root(nullptr) {}
    int find_val (int key);
    bool push(int value, int key);
    bool print();
    bool remove(int key);
};


bool Tree::push(int value, int key) {
    Node** link = &root;
    while (*link != nullptr) {
        if ((*link)->key == key) return false;
        link = key > (*link)->key ? &(*link)->right : &(*link)->left;
    }
    *link = new Node(value, key);
    return true;
}

bool Tree::print() {
    if (root == nullptr) return false;
    Node* pointer = root;
    std::cout << pointer->val << " ";
    while (pointer->right != nullptr) {
        pointer = pointer->right;
        std::cout << pointer->val << " ";
    }
    std::cout << std::endl;
    return true;
}

bool Tree::remove( int key) {
    Node** del_link = &root;
    while (*del_link != nullptr) {
        if (key == (*del_link)->key) break;
        del_link = key > (*del_link)->key? &(*del_link)->right:  &(*del_link)->left;
    }
    if (*del_link == nullptr) return false;
    Node* del = *del_link;
    if (((*del_link)->left == nullptr) && ((*del_link)->right == nullptr)) { // if deletable - leave
        *del_link = nullptr;
        delete (*del_link);
        return true;
    }
    if ((*del_link)->left == nullptr) { // if deletable doesn't have left child
        *del_link = (*del_link)->right;
        delete del;
        return true;
    }
    if ((*del_link)->right == nullptr) { // if deletable doesn't have right child
        *del_link = (*del_link)->left;
        delete del;
        return true;
    }
    Node** temp_link = &((*del_link)->right);// if deletable has 2 children find least key in right half
    while ((*temp_link)->left) temp_link = &((*temp_link)->left);
    *del_link = *temp_link;
    (*del_link)->right = del->right;
    (*del_link)->left = del->left;
    *temp_link = (*temp_link)->right;
    delete del;
    return true;
}

int Tree::find_val(int key) {
    Node** link = &root;
    while (*link != nullptr) {
        if (key == (*link)->key) break;
        link = key > (*link)->key? &(*link)->right: &(*link)->left;
    }
    if (*link == nullptr) throw incoorect_val;
    return (*link)->val;
}


int main()
{
    Tree l;
    //l.remove(1);
    l.push(100, 10);
    l.push( 50,  5);
    l.push(200, 20);
    l.push(300, 30);
    l.push(400, 40);
    l.push(160, 16);
    l.push(140, 14);
    l.push(170, 17);
    l.push(120, 12);
    l.push(130, 13);
    l.print();
    int n = 10;
    l.remove(n);
    l.print();
    std::cout << l.find_val( 5) << std::endl;
    return 0;
}
