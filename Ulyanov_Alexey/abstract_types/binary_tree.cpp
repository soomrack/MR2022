#include <iostream>


const double COMPARATION_CONST = 0.0001;


struct branch {

    double value;
    branch* left;
    branch* right;

    branch();
    branch(const double vle);

    bool is_leaf();

};


class Binary_tree {

protected:
    branch* root;

public:
    Binary_tree();
    Binary_tree(const double root_vle);
    Binary_tree(const Binary_tree& x);
    Binary_tree(Binary_tree&& x);
    ~Binary_tree();

    void add_root(const double vle);
    void add(const double vle);
    void add(const double vle, branch* sub_tree);

    unsigned int contains(const double vle);  // считает кол-во вхождений во всё дерево
    unsigned int contains(const double vle, branch* sub_tree);
    unsigned int height();
    unsigned int height(branch* sub_tree);

    branch* get(const double vle);
    branch* get(const double vle, branch* sub_tree);  // нужно ли в get(vle) и del(vle) добавить contains(vle) ??
    void del();
    void del(const double vle);
    void del(const double vle, branch* sub_tree);

    branch* get_root();
    void output();
    void print(branch* sub_tree);

};


branch::branch() {
    value = NULL;
    left = nullptr;
    right = nullptr;
}


branch::branch(const double vle) {
    value = vle;
    left = nullptr;
    right = nullptr;
}


bool branch::is_leaf() {
    return ((left->value == NULL) && (right->value == NULL));
}


Binary_tree::Binary_tree() {
    root = nullptr;
}


Binary_tree::Binary_tree(const double root_vle) {
    root = nullptr;
    add_root(root_vle);
}


Binary_tree::~Binary_tree() {
    root = nullptr;
}


void Binary_tree::add_root(const double vle) {
    branch* new_brch = new branch(vle);
    new_brch->left = new branch();
    new_brch->right = new branch();
    if (root == nullptr){
        root = new_brch;
    } else {
        if (vle - root->value > COMPARATION_CONST) {  // vle < root->value
            new_brch->left = root;
        } else {
            new_brch->right = root;
        }
        root = new_brch;
    }

}


void Binary_tree::add(const double vle) {
    add(vle, this->get_root());
}


void Binary_tree::add(const double vle, branch* sub_tree) {
    if (sub_tree == nullptr){
        add_root(vle);
        return;
    }

    if (sub_tree->value == NULL) {
        sub_tree->value = vle;
        sub_tree->left = new branch();
        sub_tree->right = new branch();
        return;
    }

    if (sub_tree->value - vle < COMPARATION_CONST){    // vle >= sub_tree->value
        add(vle, sub_tree->right);
    } else {
        add(vle, sub_tree->left);
    }

}


branch* Binary_tree::get(const double vle) {
    return get(vle, this->get_root());
}


branch* Binary_tree::get(const double vle, branch *sub_tree) {
    if (sub_tree == nullptr) return new branch();
    if (sub_tree->value == NULL) return new branch();

    if (abs(sub_tree->value - vle) < COMPARATION_CONST) return sub_tree;

    branch* in_left = get(vle, sub_tree->left);
    branch* in_right = get(vle, sub_tree->right);

    if (in_left->value == NULL){
        return in_right;
    }
    return in_left;
}


unsigned int Binary_tree::contains(const double vle) {
    return contains(vle, this->get_root());
}


unsigned int Binary_tree::contains(const double vle, branch *sub_tree) {
    if (sub_tree == nullptr) return 0;
    if (sub_tree->value == NULL) return 0;

    unsigned int ans = 0;
    if (abs(sub_tree->value - vle) < COMPARATION_CONST) ans = 1;
    return contains(vle, sub_tree->left) + contains(vle, sub_tree->right) + ans;
}


unsigned int Binary_tree::height() {
    return height(this->get_root());
}


unsigned int Binary_tree::height(branch* sub_tree) {
    if (sub_tree == nullptr) return 0;
    if (sub_tree->value == NULL) return 0;
    return std::max(height(sub_tree->left), height(sub_tree->right)) + 1;
}


void Binary_tree::del() {
    root = nullptr;
}


void Binary_tree::del(const double vle) {
    if (abs(this->get_root()->value - vle) < COMPARATION_CONST) {
        root = nullptr;
        return;
    }
    del(vle, this->get_root());
}


void Binary_tree::del(const double vle, branch *sub_tree) {
    if (sub_tree == nullptr) return;
    if (sub_tree == this->get_root()){
        root = nullptr;
        return;
    }
    if (sub_tree->value == NULL) return;

    if (abs(sub_tree->value - vle) < COMPARATION_CONST) {
        sub_tree->value = NULL;
        sub_tree->left = nullptr;
        sub_tree->right = nullptr;
        return;
    }

    del(vle, sub_tree->left);
    del(vle, sub_tree->right);
}


branch* Binary_tree::get_root() {
    return root;
}


void Binary_tree::print(branch* sub_tree) {
    if (sub_tree == nullptr) return;
    if (sub_tree->value == NULL) return;

    std::cout << "The " << sub_tree->value << " has on the left side " << sub_tree->left->value <<
                    " and " << sub_tree->right->value << " on the right\n";
    print(sub_tree->left);
    print(sub_tree->right);
}


void Binary_tree::output() {
    if (root == nullptr){
        std::cout << "There is no one element in this tree\n";
        return;
    }

    std::cout << "The root is " << this->root->value << "\n";
    this->print(this->get_root());
    std::cout << "\n";
}


int main()
{

    Binary_tree A = Binary_tree();
    A.add(9.0, A.get_root());
    A.output();

    Binary_tree B = Binary_tree();
    B.add_root(5.0);
    B.add_root(4.0);
    B.output();

    B.add(7.0);
    B.add(3.0);
    B.output();

    std::cout << B.height() << "\n\n";
    std::cout << B.contains(9.0) << "\n\n";
    std::cout << B.get(4.0)->value << "\n\n";

    B.del(9.0);
    B.output();

    return 0;
}