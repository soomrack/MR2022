#include <iostream>
#include <limits>


int get_key(double val){  // тут должна быть нормальная хэш-функция
    return int(val) + (int(val * 10) - int(val) * 10) * 10;
}


class Node {

public:
    double value;
    int key;
    Node* left;
    Node* right;

    Node();
    Node(const double vle, const int new_key);
    Node(const Node& x);
    Node(const Node&& x);

    bool is_leaf();

};


class BinaryTree {

protected:
    Node* root;

public:
    BinaryTree();
    BinaryTree(const double root_vle);
    ~BinaryTree();

    void add(const double vle);
    bool find(const int sup_key);
    unsigned int height();

    double get(const int sup_key);
    void del(const int sup_key);  // замещает удаленный элемент

    void print();


protected:


    unsigned int height(Node* sub_tree);

    Node* get_node(const int sup_key);

    void remove(Node* sub_tree);
    void print(Node* sub_tree);

    Node** max_in_left(Node* sup_node);

};


Node::Node() {
    value = 0.0;
    key = 0;
    left = nullptr;
    right = nullptr;
}


Node::Node(const double vle, const int new_key) {
    value = vle;
    key = new_key;
    left = nullptr;
    right = nullptr;
}


Node::Node(const Node &x) {
    value = x.value;
    key = x.key;
    left = x.left;
    right = x.right;
}


Node::Node(const Node &&x) {
    value = x.value;
    key = x.key;
    left = x.left;
    right = x.right;
}


bool Node::is_leaf() {
    return ((left == nullptr) && (right == nullptr));
}


BinaryTree::BinaryTree() {
    root = nullptr;
}


BinaryTree::BinaryTree(const double root_vle) {
    root = new Node(root_vle, get_key(root_vle));
}


BinaryTree::~BinaryTree() {
    remove(root);
}


void BinaryTree::add(const double vle) {
    if (root == nullptr){
        root = new Node(vle, get_key(vle));
        return;
    }
    int new_key = get_key(vle);
    Node** node = &root;
    while (*node != nullptr)
    {
        node = new_key < (*node)->key ? &(*node)->left : &(*node)->right;
    }
    *node = new Node(vle, new_key);
}


Node* BinaryTree::get_node(const int sup_key) {
    if (root == nullptr) return nullptr;

    Node* node = root;
    while (node != nullptr){
        //if(node == nullptr) return nullptr;
        if (node->key == sup_key) return node;

        node = (node->key > sup_key) ? node->left : node->right;
    }
    return nullptr;
}


double BinaryTree::get(const int sup_key) {
    if (get_node(sup_key) == nullptr) return std::numeric_limits<double>::quiet_NaN();
    return get_node(sup_key)->value;
}


bool BinaryTree::find(const int sup_key) {
    Node* current = root;
    do{
        if (current->key == sup_key) return true;
        current = (sup_key < current->key) ? current->left : current->right;
    } while (current != nullptr);
    return false;
}


unsigned int BinaryTree::height() {
    return height(root);
}


unsigned int BinaryTree::height(Node* sub_tree) {
    if (sub_tree == nullptr) return 0;
    if (sub_tree->is_leaf()) return 1;
    return std::max(height(sub_tree->left), height(sub_tree->right)) + 1;
}


void BinaryTree::remove(Node *sub_tree) {
    if (sub_tree == nullptr) return;

    if (sub_tree->is_leaf()){
        delete sub_tree;
        return;
    }

    remove(sub_tree->left);
    sub_tree->left = nullptr;
    remove(sub_tree->right);
    sub_tree->right = nullptr;

}


void BinaryTree::del(const int sup_key) {

    Node** parent_link = &root;
    while (*parent_link && (*parent_link)->key != sup_key)
    {
        parent_link = sup_key < (*parent_link)->key ? &(*parent_link)->left : &(*parent_link)->right;
    }
    if (!*parent_link)
        // элемент не был найден
        return;

    Node* temp = (*parent_link);

    if ((*parent_link)->left == nullptr) {

        (*parent_link) = (*parent_link)->right;
        delete temp;
        return;
    }

    Node** replacing_node = max_in_left((*parent_link)->left);
    std::cout << (*parent_link)->value << "  " << (*replacing_node)->value << "\n\n";

    Node* copy = (*replacing_node)->left;

    (*replacing_node)->right = (*parent_link)->right;
    (*replacing_node)->left = (*parent_link)->left;

    *parent_link = *replacing_node;

    (*replacing_node) = copy;

    delete temp;

}


Node** BinaryTree::max_in_left(Node *sup_node) {
    //sup_node гарантированно не nullptr
    Node** ans = &sup_node;
    Node* left_handed_node = sup_node;
    while (!left_handed_node->is_leaf()){
        if (left_handed_node->right != nullptr){
            ans = &left_handed_node->right;
            left_handed_node = left_handed_node->right;
        } else
            left_handed_node = left_handed_node->left;
    }
    return ans;
}


void BinaryTree::print(Node* sub_tree) {
    if (sub_tree == nullptr) return;

    std::cout << "The " << sub_tree->value << "[" << sub_tree->key << "]";
    if (sub_tree->is_leaf()){
        std::cout << "\n";
        return;
    }

    if (sub_tree->left != nullptr) {
        std::cout << " has on the left side " << sub_tree->left->value;
        if (sub_tree->right != nullptr)
            std::cout << "  and ";
    }
    if (sub_tree->right != nullptr){
        std::cout << " has on the right side " << sub_tree->right->value;
    }
    std::cout << "\n";

    print(sub_tree->left);
    print(sub_tree->right);
}


void BinaryTree::print() {
    if (root == nullptr){
        std::cout << "There is no one element in this tree\n\n";
        return;
    }

    std::cout << "The root is " << this->root->value << "\n";
    this->print(root);
    std::cout << "\n";
}


int main()
{

    BinaryTree A = BinaryTree();
    A.add(9.0);
    A.print();

    BinaryTree B = BinaryTree();
    B.add(5.0);
    B.add(4.0);
    B.print();

    //B.del(4);
    B.print();

    B.add(7.0);
    B.add(3.0);
    B.print();

    std::cout << B.height() << "\n\n";
    std::cout << B.find(7) << "\n\n";
    std::cout << B.get(4) << "\n\n";

    double c_array[10] = {5.0, 8.0, 4.4, 2.0, 3.0, 9.0, 1.0, 7.0, 6.0, 3.3};
    BinaryTree C = BinaryTree();
    for (unsigned int idx = 0; idx < 10; idx++){
        C.add(c_array[idx]);
    }
    C.print();

    C.del(5);
    C.print();


    return 0;
}