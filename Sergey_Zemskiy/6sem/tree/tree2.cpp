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
    Node* find(int value) ;// не должно быть доступно пользователю
    Node* list(Node* x);
    Node* leave(Node* x);
    void remove(Node* del);
    void remove_right(Node* del);
    void remove_left(Node* del);
    Node* find_parent(int value);

    void print();
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
    Node* r = root;// пока р не равен нуллптр
    while ((r->left != p) && (r->right != p)) {
        if(value == r->val) {
            std::cout << "value " << value << " already exists" << std::endl;
            return;
        }
        if (value > r->val) {
            r->right? r = r->right : r->right = p;
        }
        if (value < r->val) {
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

Node* Tree::find(int value) {
    if ( is_empty()) {
        std::cout << "tree is empty" << std::endl;
        return nullptr;
    }
    Node* p =root;
    while ((p != nullptr) && (p->val != value)) { // тоже пока не будет нуллптр
        if (p == nullptr) {return nullptr;}
        if (value > p->val) {
            if (p->right == nullptr) {
                std::cout << "this value doesn't exist" << std::endl;
            }
            p = p->right;
        }
        else {
            if (p->left == nullptr) {
                std::cout << "this value doesn't exist" << std::endl;
            }
            p =p->left;
        }
    }
    return p;
}

/*Node* Tree::list(Node* x){ //leave
    if ((x->left == nullptr) && (x->right == nullptr)) return x ;
    Node* p = x;
    if (x->right != nullptr) {
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
}*/


Node *Tree::find_parent(int value) {
    Node* p = root;
    if (p->val == value) {
        std::cout << "this Node is root" << std::endl;
        return nullptr;
    }
    while (true) { // пока не нуллптр
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
    if (del == root) {
        root = nullptr;
        delete del;
        return;
    }
    Node* parent = find_parent(del->val);
    if (del == parent->right) remove_right(del); // если удаляемый узел - правый у своего родителя
    else remove_left(del); // если левый
}

void Tree::remove_right( Node* del) {
    std::cout << "right" << std::endl;
    Node *p = del;
    Node *parent = find_parent(del->val);
    Node *p_parent;
    if ((p->left == nullptr) && (p->right == nullptr)) { // если это лист
        parent->right == nullptr;
        delete del;
        return;
    }
    if (p->left == nullptr) { // если нет левого поддерева
        p = p->right;
        if (p->left == nullptr) {
            parent->right = p;
            p->left = del->left;
            delete del;
            return;
        }
        else {
            while (p->left != nullptr) p = p->left;
            if (p->right) {
                p_parent = find_parent(p->val);
                p_parent->left = p->right;
                parent->right = p;
                p->right = del->right;
                delete del;
                return;
            }
            parent->right = p;
            p->right = del->right;
            delete del;
            return;
        }
    }

    if (p->right == nullptr) { // если нет правого поддерева
        p = p->left;
        if (p->right == nullptr) {
            parent->right = p;
            p->right = del->right;
            delete del;
            return;
        }
        else {
            while (p->right != nullptr) p = p->right;
            if (p->left) {
                p_parent = find_parent(p->val);
                p_parent->right = p->left;
                parent->left = p;
                p->right = del->left;
                delete del;
                return;
            }
            parent->right = p;
            p->left = del->left;
            delete del;
            return;
        }
    }

      // если есть оба поддерева
    p = p->right;
    if (p->left == nullptr) {
        parent->right = p;
        p->left = del->left;
        delete del;
        return;
    }
    while (p->left != nullptr) p = p->left;
    if (p->right) {
        p_parent = find_parent(p->val);
        p_parent->left = p->right;
        parent->right = p;
        p->right = del->right;
        p->left = del->left;
        delete del;
        return;
    }
    parent->right = p;
    p->right = del->right;
    delete del;
    return;
}


void Tree::remove_left( Node* del) {
    std::cout << "left" << std::endl;
    Node *p = del;
    Node *parent = find_parent(del->val);
    Node *p_parent;
    if ((p->left == nullptr) && (p->right == nullptr)) { // если это лист
        parent->left == nullptr;
        delete del;
        return;
    }
    if (p->left == nullptr) { // если нет левого поддерева
        p = p->right;
        if (p->left == nullptr) {
            parent->left = p;
            p->left = del->left;
            delete del;
            return;
        }
        else {
            while (p->left != nullptr) p = p->left;
            if (p->right) {
                p_parent = find_parent(p->val);
                p_parent->left = p->right;
                parent->left = p;
                p->right = del->right;
                delete del;
                return;
            }
            parent->left = p;
            p->right = del->right;
            delete del;
            return;
        }
    }

    if (p->right == nullptr) { // если нет правого поддерева
        p = p->left;
        if (p->right == nullptr) {
            parent->left = p;
            p->right = del->right;
            delete del;
            return;
        }
        else {
            while (p->right != nullptr) p = p->right;
            if (p->left) {
                p_parent = find_parent(p->val);
                p_parent->right = p->left;
                parent->left = p;
                p->right = del->left;
                delete del;
                return;
            }
            parent->left = p;
            p->left = del->left;
            delete del;
            return;
        }
    }

    // если есть оба поддерева
    p = p->right;
    if (p->left == nullptr) {
        parent->right = p;
        p->left = del->left;
        delete del;
        return;
    }
    while (p->left != nullptr) p = p->left;
    if (p->right) {
        p_parent = find_parent(p->val);
        p_parent->left = p->right;
        parent->left = p;
        p->right = del->right;
        p->left = del->left;
        delete del;
        return;
    }
    parent->left = p;
    p->right = del->right;
    delete del;
    return;
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
    l.print();
    int n = 20;
    Node* o = l.find(n);
    std::cout << "o is " << o->val<< std::endl;
    std::cout << "parent " << l.find_parent(n)->val<< std::endl;
    l.remove(o);
    l.print();
    return 0;
}
