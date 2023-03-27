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
Exception same_val("this value already exists");
Exception no_val("this value doesn't exist");
Exception proot("Node p is root");




class Tree {
private:
    Node* root;
    Node* find_Node(int key_temp) ;
    Node* find_parent(int key_temp);
public:
    Tree() : root(nullptr) {}
    int find_val ( int key_temp);
    bool is_empty() ;
    void push(int value, int key_temp);
    void print();
    void remove(int key_temp);
};

bool Tree::is_empty() {
    return root == nullptr;
}

void Tree::push(int value, int key_temp) {
    Node* p = new Node(value, key_temp);
    if (root == nullptr) {
        root = p;
        return;
    }
    Node* r = root;
    while ((r->left != p) && (r->right != p)) {
        if(key_temp == r->key) {
            throw same_val;
            return;
        }
        if (key_temp > r->key) {
            r->right? r = r->right : r->right = p;
        }
        else {
            r->left? r = r->left : r->left = p;
        }
    }
}

void Tree::print() {
    if (is_empty()) return;
    Node* r = root;
    std::cout << r->val << " ";
    r = r->right;
    std::cout << r->val << " ";
    while (r->left != nullptr) {
        r = r->left;
        std::cout << r->val << " ";
    }
    std::cout << std::endl;
}

Node* Tree::find_Node(int key_temp) {
    if ( is_empty()) {
        throw empty;
        return nullptr;
    }
    Node* p =root;
    while ((p != nullptr) && (p->key != key_temp)) { 
        if (p == nullptr) {return nullptr;}
        if (key_temp > p->key) {
            if (p->right == nullptr) {
                throw no_val;
            }
            p = p->right;
        }
        else {
            if (p->left == nullptr) {
                throw no_val;
            }
            p = p->left;
        }
    }
    return p;
}


Node *Tree::find_parent(int key_temp) {
    Node* p = root;
    if (root->key == key_temp) {
        throw proot;
    }
    while (true) { // пока не нуллптр
        if (p == nullptr) {return nullptr;}
        if (key_temp >= p->key) {
            if (key_temp == p->right->key) return p;
            else p = p->right;
        }
        else {
            if (key_temp == p->left->key) return p;
            else p = p->left;
        }
    }
}



void Tree::remove( int key_temp) {
    Node* del = find_Node(key_temp);
    if (del == root) {
        root = nullptr;
        delete del;
        return;
    }
    Node* parent = find_parent(del->key);
    Node **x;
    if (del == parent->right) x = &(parent->right); // если удаляемый узел - правый у своего родителя
    else  x = &(parent->left); // если левый


    Node *p = del;
    Node *p_parent;
    if ((p->left == nullptr) && (p->right == nullptr)) { // если это лист
        *x = nullptr;
        delete del;
        return;
    }
    if (p->left == nullptr) { // если нет левого поддерева
        p = p->right;
        if (p->left == nullptr) {
            *x = p;
            p->left = del->left;
            delete del;
            return;
        }
        else {
            while (p->left != nullptr) p = p->left;
            if (p->right) {
                p_parent = find_parent(p->key);
                p_parent->left = p->right;
                *x = p;
                p->right = del->right;
                delete del;
                return;
            }
            *x = p;
            p->right = del->right;
            delete del;
            return;
        }
    }

    if (p->right == nullptr) { // если нет правого поддерева
        p = p->left;
        if (p->right == nullptr) {
            *x = p;
            p->right = del->right;
            delete del;
            return;
        }
        else {
            while (p->right != nullptr) p = p->right;
            if (p->left) {
                p_parent = find_parent(p->key);
                p_parent->right = p->left;
                *x = p;
                p->right = del->left;
                delete del;
                return;
            }
            *x = p;
            p->left = del->left;
            delete del;
            return;
        }
    }

    // если есть оба поддерева
    p = p->right;
    if (p->left == nullptr) {
        *x = p;
        p->left = del->left;
        delete del;
        return;
    }
    while (p->left != nullptr) p = p->left;
    if (p->right) {
        p_parent = find_parent(p->key);
        p_parent->left = p->right;
        *x = p;
        p->right = del->right;
        p->left = del->left;
        delete del;
        return;
    }
    *x = p;
    p->right = del->right;
    delete del;
    return;
}


int Tree::find_val(int key_temp) {
    if ( is_empty()) {
        throw empty;
    }
    Node* p =root;
    while ((p != nullptr) && (p->key != key_temp)) { // тоже пока не будет нуллптр
        if (p == nullptr) {return NULL;}
        if (key_temp > p->key) {
            if (p->right == nullptr) throw no_val;
            p = p->right;
        }
        else {
            if (p->left == nullptr) throw no_val;
            p =p->left;
        }
    }
    return p->val;
}


int main()
{
    Tree l;
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
    int n = 20;
    l.remove(n);
    l.print();
    return 0;
}
