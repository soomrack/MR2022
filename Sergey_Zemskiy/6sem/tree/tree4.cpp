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
    Exception(const char* const message) : std::domain_error(message)
    {}
};

Exception empty("No elements in tree");
Exception no_val("this value doesn't exist");

class Tree {
private:
    Node* root;

public:
    Tree() : root(nullptr) {}
    int find_val ( int key_temp);
    void push(int value, int key_temp);
    void print();
    void remove(int key_temp);

private:
    Node* find_parent(int key_temp);
};



void Tree::push(int value, int key_temp) {
    Node* node_new = new Node(value, key_temp);
    if (root == nullptr) {
        root = node_new;
        return;
    }
    Node* pointer = root;
    while ((pointer->left != node_new) && (pointer->right != node_new)) {
        if(key_temp == pointer->key) {
            return;
        }
        if (key_temp > pointer->key) {
            pointer->right? pointer = pointer->right : pointer->right = node_new;
        }
        else {
            pointer->left? pointer = pointer->left : pointer->left = node_new;
        }
    }
}

void Tree::print() {
    if (root == nullptr) return;
    Node* pointer = root;
    std::cout << pointer->val << " ";
    while (pointer->right != nullptr) {
        pointer = pointer->right;
        std::cout << pointer->val << " ";
    }
    std::cout << std::endl;
}


Node *Tree::find_parent(int key_temp) { // if Node has no parent and Node is not root there is no this element
    if (root == nullptr) {
        return nullptr;
    }
    if (root->key == key_temp) {
        return nullptr;
    }
    Node* pointer = root;

    while (pointer != nullptr) {
        if (key_temp > pointer->key) { // "<" because of impossibility 2 same keys
            if (pointer->right == nullptr)  return nullptr; // necessary to check before next condition
            if (key_temp == pointer->right->key) return pointer;
            pointer = pointer->right;
        }
        else {
            if (pointer->left == nullptr) return nullptr;
            if (key_temp == pointer->left->key) return pointer;
            pointer = pointer->left;
        }
    }
}



void Tree::remove( int key_temp) {
    if (root == nullptr) return; // if tree is empty
    Node* parent = find_parent(key_temp);
    if ((parent == nullptr)  && (key_temp != root->key)) return; // if Node has no parent and Node is not root do nothing
    Node* del;
    Node **del_link;
    if (root->key == key_temp) {
        del_link = &root;
        del = root;
    }
    else if ((parent->right != nullptr) && (key_temp == parent->right->key)) {
        del_link = &(parent->right); // if deletable - right child
        del = parent->right;
    }
    else if ((parent->left != nullptr) && (key_temp == parent->left->key)) {
        del_link = &(parent->left); // if deletable - left child
        del = parent->left;
    }
    if ((del->left == nullptr) && (del->right == nullptr)) { // if deletable - leave
        *del_link = nullptr;
        delete del;
        return;
    }
    if (del->left == nullptr) { // if deletable doesn't have left child
        *del_link = del->right;
        del->right = nullptr;
        delete del;
        return;
    }
    if (del->right == nullptr) { // if deletable doesn't have right child
        *del_link = del->left;
        del->left = nullptr;
        delete del;
        return;
    }
    // if deletable has 2 children
    Node *temp_parent = del;
    Node *temp = del->right; // temporary pointer of Node for search
    if (temp->left == nullptr) { // if right child of deletable doesn't have left child
        *del_link = temp;
        temp->left = del->left;
        delete del;
        return;
    }
    while (temp->left != nullptr) {
        temp_parent = temp_parent->left;
        temp = temp->left;
    }
    if (temp->right != nullptr) {
        temp_parent->left = temp->right;
        *del_link = temp;
        temp->right = del->right;
        temp->left = del->left;
        delete del;
        return;
    }
    *del_link = temp;
    temp->right = del->right;
    delete del;
}


int Tree::find_val(int key_temp) {
    if ( root == nullptr) {
        throw empty;
    }
    Node* pointer = root;
    while ((pointer != nullptr) && (pointer->key != key_temp)) {
        if (key_temp > pointer->key) {
            if (pointer->right == nullptr) throw no_val;
            pointer = pointer->right;
        }
        else {
            if (pointer->left == nullptr) throw no_val;
            pointer = pointer->left;
        }
    }
    return pointer->val;
}


int main()
{
    Tree l;
    int n = 20;
    l.remove(n);
    l.push(100, 10);
    l.push(200, 20);
    l.push(300, 30);
    l.push(400, 40);
    l.push(160, 16);
    l.push(140, 14);
    l.push(170, 17);
    l.push(120, 12);
    l.push(130, 13);
    l.print();
    l.remove(n);
    l.print();
    std::cout << l.find_val( 30) << std::endl;
    return 0;
}
