#include <iostream>
#include "vector"


int GetKey(double val){  // тут должна быть нормальная хэш-функция
    return int(val) + (int(val * 10) - int(val) * 10) * 10;
}


struct Branch {

    double value;
    int key;
    Branch* left;
    Branch* right;

    Branch();
    Branch(const double vle, const int new_key);

    bool IsLeaf();

};


class BinaryTree {

protected:
    Branch* root;

    void AddRoot(const double vle);
    void Add(const double vle, const int new_key, Branch* sub_tree);

    bool Contains(const int sup_key, Branch* sub_tree);
    unsigned int Height(Branch* sub_tree);

    void Remove(Branch* sub_tree);
    void Print(Branch* sub_tree);
// вспомогательная для Del рекурсивная функция
    void NodesToAdd(Branch* sub_tree, std::vector<double> vec_keys, std::vector<int> vec_vals);

public:
    BinaryTree();
    BinaryTree(const double root_vle);
    ~BinaryTree();

    void Add(const double vle);
    bool Contains(const int sup_key);  // считает кол-во вхождений во всё дерево
    unsigned int Height();

    Branch* Get(const int sup_key);
    void Remove(const int sup_key);  // удаляет элемент со всеми его поддеревьями
    void Del(const int sup_key);  // замещает удаленный элемент

    Branch* GetRoot();
    void Output();

};


Branch::Branch() {
    value = 0.0;
    key = 0;
    left = nullptr;
    right = nullptr;
}


Branch::Branch(const double vle, const int new_key) {
    value = vle;
    key = new_key;
    left = nullptr;
    right = nullptr;
}


bool Branch::IsLeaf() {
    return ((left == nullptr) && (right == nullptr));
}


BinaryTree::BinaryTree() {
    root = nullptr;
}


BinaryTree::BinaryTree(const double root_vle) {
    root = nullptr;
    AddRoot(root_vle);
}


BinaryTree::~BinaryTree() {
    if (root != nullptr)
        Remove(root->key);
}


void BinaryTree::AddRoot(const double vle) {  // корень не переопределяется
    if (root != nullptr) return;
    root = new Branch(vle, GetKey(vle));
}


void BinaryTree::Add(const double vle) {
    if (GetRoot() == nullptr){
        AddRoot(vle);
        return;
    }
    int new_key = GetKey(vle);
    Add(vle, new_key, root);
}


void BinaryTree::Add(const double vle, const int new_key, Branch* sub_tree) {

    //Branch* next_step = (sub_tree->key > new_key) ? sub_tree->left : sub_tree->right;
    // из-за необходимости проверки ссылки (sub_tree->left(right)) на пустоту (nullptr)
    //                                              применение торнарного оператора невозиможно

    if (sub_tree->key > new_key){
        if (sub_tree->left == nullptr){
            sub_tree->left = new Branch(vle, new_key);
            return;
        }
        Add(vle, new_key, sub_tree->left);
    } else {
        if (sub_tree->right == nullptr){
            sub_tree->right = new Branch(vle, new_key);
            return;
        }
        Add(vle, new_key, sub_tree->right);
    }

}


Branch* BinaryTree::Get(const int sup_key) {
    if (root == nullptr) return new Branch();

    Branch* node = root;
    while (true){
        if(node == nullptr) return new Branch();
        if (node->key == sup_key) return node;

        node = (node->key > sup_key) ? node->left : node->right;
    }
}


bool BinaryTree::Contains(const int sup_key) {
    if (root == nullptr){
        return false;
    }
    return Contains(sup_key, this->GetRoot());
}


bool BinaryTree::Contains(const int sup_key, Branch *sub_tree) {
    if (sub_tree == nullptr) return false;
    if (sub_tree->key == sup_key) return true;

    Branch* next_step = (sup_key < sub_tree->key) ? sub_tree->left : sub_tree->right;
    return Contains(sup_key, next_step);
}


unsigned int BinaryTree::Height() {

    return Height(this->GetRoot());
}


unsigned int BinaryTree::Height(Branch* sub_tree) {
    if (sub_tree == nullptr) return 0;
    if (sub_tree->IsLeaf()) return 1;
    return std::max(Height(sub_tree->left), Height(sub_tree->right)) + 1;
}


void BinaryTree::Remove(const int sup_key) {
    if (root == nullptr || !Contains(sup_key)) return;

    if (root->key == sup_key){
        Remove(root);
        root = nullptr;
        return;
    }

    Branch* node = root;
    while (true){
        if (node->left != nullptr)
            if (node->left->key == sup_key){
                Remove(node->left);
                node->left = nullptr;
                return;
            }

        if (node->right != nullptr)
            if (node->right->key == sup_key){
                Remove(node->right);
                node->right = nullptr;
                return;
            }

        node = (sup_key < node->key) ? node->left : node->right;
    }

}


void BinaryTree::Remove(Branch *sub_tree) {
    if (sub_tree == nullptr) return;

    if (sub_tree->IsLeaf()){
        delete sub_tree;
        return;
    }

    Remove(sub_tree->left);
    sub_tree->left = nullptr;
    Remove(sub_tree->right);
    sub_tree->right = nullptr;

}


void BinaryTree::Del(const int sup_key) {
    if (root == nullptr || !Contains(sup_key)) return;

    Branch* sup_node = root;
    while (sup_node->key != sup_key) {
        sup_node = (sup_key < sup_node->key) ? sup_node->left : sup_node->right;
    }

    if (sup_node->IsLeaf()){
        Remove(sup_key);
        return;
    }

// поиск вершины для замены (самое левое в правом поддереве или самое правое в левом)
    Branch* replacing_node = nullptr;
    // сюда бы еще сравнение высоты левого и правого поддеревьев.
    bool in_right_subtree = false;
    if (sup_node->right != nullptr){  // !in_left_subtree
        Branch* right_handed_node = sup_node->right;
        while(!right_handed_node->IsLeaf()){
            if (right_handed_node->left != nullptr){
                in_right_subtree = true;
                replacing_node = right_handed_node->left;
                right_handed_node = right_handed_node->left;
            } else
                right_handed_node = right_handed_node->right;
        }
    }
    bool in_left_subtree = false;
    if (!in_right_subtree && sup_node->left != nullptr) {
        Branch *left_handed_node = sup_node->left;
        while (!left_handed_node->IsLeaf()){
            if (left_handed_node->right != nullptr){
                in_left_subtree = true;
                replacing_node = left_handed_node->right;
                left_handed_node = left_handed_node->right;
            } else
                left_handed_node = left_handed_node->left;
        }

    }

    if (replacing_node == nullptr){
        if (sup_node->left == nullptr){
            replacing_node = sup_node->right;
        } else if (sup_node->right == nullptr) {
            replacing_node = sup_node->left;
        } else {
            replacing_node = (Height(sup_node->right) >= Height(sup_node->left)) ?
                             sup_node->right : sup_node->left;
        }
    }

/*
    std::cout << sup_node->value << "[" << sup_node->key << "]";
    if (replacing_node != nullptr){
        std::cout << "  |  " << replacing_node->value << "[" << replacing_node->key << "]";
    }
    std::cout << "\n\n";
*/

// сохраняем все вершины под replacing_node
    std::vector<double> values_to_add;
    std::vector<int> keys_to_add;

    NodesToAdd(replacing_node->left, values_to_add, keys_to_add);
    NodesToAdd(replacing_node->right, values_to_add, keys_to_add);

// перезаписываем значения (value и key) sup_node на replacing_node
    int rep_key = replacing_node->key;
    double rep_val = replacing_node->value;
    Remove(rep_key);
    Get(sup_key)->value = rep_val;
    Get(sup_key)->key = rep_key;

// добавление всех сохраненных nodes
    int length = values_to_add.size();
    for (unsigned int idx = 0; idx < length; idx++){
        Add(values_to_add[idx], keys_to_add[idx], root);
    }

}


void BinaryTree::NodesToAdd(Branch *sub_tree, std::vector<double> vec_keys, std::vector<int> vec_vals) {
    if (sub_tree == nullptr) return;

    vec_keys.push_back(sub_tree->key);
    vec_vals.push_back(sub_tree->value);

    NodesToAdd(sub_tree->left, vec_keys, vec_vals);
    NodesToAdd(sub_tree->right, vec_keys, vec_vals);
}


Branch* BinaryTree::GetRoot() {
    return root;
}


void BinaryTree::Print(Branch* sub_tree) {
    if (sub_tree == nullptr) return;

    std::cout << "The " << sub_tree->value << "[" << sub_tree->key << "]";
    if (sub_tree->IsLeaf()){
        std::cout << "\n";
        return;
    }

    if (sub_tree->left != nullptr) {
        std::cout << " has on the left side " << sub_tree->left->value;
        if (sub_tree->right != nullptr)
            std::cout << " and ";
    }
    if (sub_tree->right != nullptr){
        std::cout << " has on the right side " << sub_tree->right->value;
    }
    std::cout << "\n";

    Print(sub_tree->left);
    Print(sub_tree->right);
}


void BinaryTree::Output() {
    if (root == nullptr){
        std::cout << "There is no one element in this tree\n";
        return;
    }

    std::cout << "The root is " << this->root->value << "\n";
    this->Print(this->GetRoot());
    std::cout << "\n";
}


int main()
{

    BinaryTree A = BinaryTree();
    A.Add(9.0);
    A.Output();

    BinaryTree B = BinaryTree();
    B.Add(5.0);
    B.Add(4.0);
    B.Output();

    B.Del(5);
    B.Output();

    B.Add(7.0);
    B.Add(3.0);
    B.Output();

    std::cout << B.Height() << "\n\n";
    std::cout << B.Contains(7) << "\n\n";
    std::cout << B.Get(4)->value << "\n\n";

    double c_array[10] = {5.0, 8.0, 4.4, 2.0, 3.0, 9.0, 1.0, 7.0, 6.0, 3.3};
    BinaryTree C = BinaryTree();
    for (unsigned int idx = 0; idx < 10; idx++){
        C.Add(c_array[idx]);
    }
    C.Output();

    C.Del(1);
    C.Output();

    C.Remove(44);
    C.Output();

    return 0;
}