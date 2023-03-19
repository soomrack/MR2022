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

    void remove(const int sup_key);  // удаляет элемент со всеми его поддеревьями
    void del(const int sup_key);  // замещает удаленный элемент

    void print();


protected:

    //void addRoot(const double vle);
    void add(const double vle, const int new_key, Node* sub_tree);

    bool find(const int sup_key, Node* sub_tree);
    unsigned int height(Node* sub_tree);

    Node* get_node(const int sup_key);
    Node* get_parent_to(const int sup_key);

    void remove(Node* sub_tree);
    void print(Node* sub_tree);

    Node* find_node_to_replace(Node* sup_node);
    Node* max_in_left(Node* sup_node);
    Node* min_in_right(Node* sup_node);

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
    remove(root->key);
    //root = nullptr;
}


void BinaryTree::add(const double vle) {
    if (root == nullptr){
        root = new Node(vle, get_key(vle));
        return;
    }
    add(vle, get_key(vle), root);
}


void BinaryTree::add(const double vle, const int new_key, Node* sub_tree) {
    Node* next_step = nullptr;
    if (sub_tree->key > new_key){
        if (sub_tree->left == nullptr){
            sub_tree->left = new Node(vle, new_key);
            return;
        }
        next_step = sub_tree->left;
    } else {
        if (sub_tree->right == nullptr){
            sub_tree->right = new Node(vle, new_key);
            return;
        }
        next_step = sub_tree->right;
    }

    add(vle, new_key, next_step);
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


Node* BinaryTree::get_parent_to(const int sup_key) {
    if (root == nullptr || root->is_leaf()) return nullptr;

    Node* current = root;
    while (current != nullptr){
        Node* next_step = (current->key > sup_key) ? current->left : current->right;
        if (next_step != nullptr)
            if (next_step->key == sup_key)
                return current;

        current = next_step;
    }
    return nullptr;
}


double BinaryTree::get(const int sup_key) {
    if (get_node(sup_key) == nullptr) return std::numeric_limits<double>::quiet_NaN();
    return get_node(sup_key)->value;
}


bool BinaryTree::find(const int sup_key) {
    return find(sup_key, root);
}


bool BinaryTree::find(const int sup_key, Node *sub_tree) {
    if (sub_tree == nullptr) return false;
    if (sub_tree->key == sup_key) return true;

    Node* next_step = (sup_key < sub_tree->key) ? sub_tree->left : sub_tree->right;
    return find(sup_key, next_step);
}


unsigned int BinaryTree::height() {
    return height(root);
}


unsigned int BinaryTree::height(Node* sub_tree) {
    if (sub_tree == nullptr) return 0;
    if (sub_tree->is_leaf()) return 1;
    return std::max(height(sub_tree->left), height(sub_tree->right)) + 1;
}


void BinaryTree::remove(const int sup_key) {
    if (/*root == nullptr || */!find(sup_key)) return;

    if (root->key == sup_key){
        remove(root);
        root = nullptr;
        return;
    }

    Node* node = root;
    while (true){
        if (node->left != nullptr)
            if (node->left->key == sup_key){
                remove(node->left);
                node->left = nullptr;
                return;
            }

        if (node->right != nullptr)
            if (node->right->key == sup_key){
                remove(node->right);
                node->right = nullptr;
                return;
            }

        node = (sup_key < node->key) ? node->left : node->right;
    }

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
    if (root == nullptr || !find(sup_key)) return;

    Node* sup_node = get_node(sup_key);

    if (sup_node->is_leaf()){
        remove(sup_key);
        return;
    }

    Node* replacing_node = find_node_to_replace(sup_node);
    std::cout << sup_node->value << "[" << sup_node->key << "]  |  " << replacing_node->value << "[" << replacing_node->key << "]\n\n";

    int new_key = replacing_node->key;
    double new_val = replacing_node->value;
    del(replacing_node->key);
    sup_node->key = new_key;
    sup_node->value = new_val;

}


Node* BinaryTree::find_node_to_replace(Node *sup_node) {
    //if (sup_node->is_leaf()) return nullptr;  //  на данном этапе гарантируется, что sup_node не лист

    if (height(sup_node->right) >= height(sup_node->left))
        return min_in_right(sup_node->right);
    else
        return max_in_left(sup_node->left);
}


Node* BinaryTree::max_in_left(Node *sup_node) {
    //sup_node гарантированно не nullptr
    Node* ans = sup_node;
    Node* left_handed_node = sup_node;
    while (!left_handed_node->is_leaf()){
        if (left_handed_node->right != nullptr){
            ans = left_handed_node->right;
            left_handed_node = left_handed_node->right;
        } else
            left_handed_node = left_handed_node->left;
    }
    return ans;
}


Node* BinaryTree::min_in_right(Node *sup_node) {
    //sup_node гарантированно не nullptr
    Node* ans = sup_node;
    Node* right_handed_node = sup_node;
    while(!right_handed_node->is_leaf()){
        if (right_handed_node->left != nullptr){
            ans = right_handed_node->left;
            right_handed_node = right_handed_node->left;
        } else
            right_handed_node = right_handed_node->right;
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
        std::cout << "There is no one element in this tree\n";
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

    B.del(5);
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

    //C.remove(44);
    //C.print();

    return 0;
}