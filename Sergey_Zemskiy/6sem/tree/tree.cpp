#include <iostream>


class Node {
public:
    Node* left;
    Node* right;
    int val;
    Node(int _val) : val(_val), left(nullptr), right(nullptr) {}
};


class Tree {
private:
    Node* root;
public:
    Tree() : root(nullptr) {}

    bool is_empty() ;
    void push(int value);
    Node* find(int value) ;
    Node* list(Node* root);
    void remove(Node* del);
    Node* find_parent(int value);
};

bool Tree::is_empty() {
    return root == nullptr;
}

void Tree::push(int value) {
    Node* p = new Node(value);
    if (is_empty()) {
        root = p;
        return;
    }
    Node* r = root;
    bool run = true;
    while (run) {
        if(value == r->val) {
            std::cout << "value " << value << " already exists" << std::endl;
            return;
        }
        if (value > r->val) {
            if (r->right) {
                r = r->right;
            }
            else {
                r->right = p;
                run = false;
            }
        }
        if (value < r->val) {
            r->left != nullptr ? r = r->left : r->left;
            if (r->left) {
                r = r->left;
            }
            else {
                r->left  = p;
                run = false;
            }
        }
    }
}

/*void Tree::print() {
    if (is_empty()) return;
    Node* r = root;
    Node* l = root;
    bool exit = false;
    while (!exit) {
        l = l->left;
        r = r->right;
        std::cout << r->val << l->val << " ";
        if (r->right == nullptr) exit = true;
        if (!l) exit = true;
    }
    std::cout << std::endl;
}*/

Node* Tree::find(int value) {
    if ( is_empty()) {
        std::cout << "tree is empty" << std::endl;
        return nullptr;
    }
    Node* p =root;
    while (true) {
        if (p == nullptr) {return nullptr;}
        if (value == p->val) {return p;}
        if (value > p->val) {
            if (p->right == nullptr) {
                std::cout << "this value doesn't exist" << std::endl;
                return nullptr;
            }
            p = p->right;
        }
        else {
            if (p->left == nullptr) {
                std::cout << "this value doesn't exist" << std::endl;
                return nullptr;
            }
            p =p->left;
        }
    }
}

Node* Tree::list(Node* first){
    if ((first->left == nullptr) && (first->right == nullptr)) return first ;
    Node* p = first;
    if (first->right != nullptr) {
        p = p->right;
        while (((p->left != nullptr) || (p->right != nullptr))){
            if (p->left != nullptr) p = p->left;
            else if (p->right != nullptr) p = p->right;
        }
    }
    else {
        p = p->left;
        while ((p->left != nullptr) || (p->right != nullptr)) {
            if (p->right != nullptr) p = p->right;
            else if (p->left != nullptr) p = p->left;
        }
    }
    return p;
}


Node *Tree::find_parent(int value) {
    Node* p = root;
    if (p->val == value) {
        std::cout << "this Node is root" << std::endl;
        return p;
    }
    while (true) {
        if (p == nullptr) {return nullptr;}
        if (value >= p->val) {
            if (value == p->right->val) return p;
            else p = p->right;
        }
        else {
            if (value == p->left->val) return p;
            else p = p->left;
        }
    }
}

void Tree::remove( Node* del) {
    if (is_empty()) return;
    Node* p = del;
    Node* p_list = list(p);
    p->val = p_list->val;
    Node* list_parent = find_parent( p_list->val);
    if (p_list->val == list_parent->right->val) list_parent->right == nullptr;
    else list_parent->left == nullptr;
    delete p_list;
}


int main()
{
    Tree l;
    l.push(10);
    l.push(20);
    l.push(30);
    l.push(40);
    l.push(16);
    l.push(14);
    l.push(17);
    l.push(14);
    l.push(12);
    l.push(13);
    int n = 16;
    Node* o = l.find(n);
    std::cout << "o is " << o->val<< std::endl;
    Node* listik = l.list(o);
    std::cout << "list is " << listik->val<< std::endl;
    std::cout << "parent " << l.find_parent(n)->val<< std::endl;
    l.remove(o);
    std::cout << "new value: " << o->val<< std::endl;
    std::cout << l.find(n)<< std::endl;
    std::cout << "end " << std::endl;
    return 0;
}
