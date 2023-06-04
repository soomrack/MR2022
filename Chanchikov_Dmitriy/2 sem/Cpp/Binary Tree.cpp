#include <iostream>


struct Node {
    explicit Node(const double &value, Node* left = nullptr, Node* right = nullptr):
        data(value), left(left), right(right)  {}

    double data;
    Node* left;
    Node* right;
};


class BinaryTree {
private:
    Node* root;

    static Node* find_parent_of_biggest_ptr(Node *subtree);
    void destroy_rec(Node *node);

public:
    BinaryTree() : root(nullptr) {};
    ~BinaryTree() {destroy_rec(root); root = nullptr;}

    void insert(double);
    void remove(double);
    bool search(double);
    void print() {print_rec(root, 0);}
    void print_rec(Node* node, int indent);
};


Node* BinaryTree::find_parent_of_biggest_ptr(Node *subtree) {
    Node* parent_of_biggest_ptr = nullptr;
    Node* current = subtree;
    while (current->right != nullptr) {
        parent_of_biggest_ptr = current;
        current = current->right;
    }
    return parent_of_biggest_ptr;
}


void BinaryTree::destroy_rec(Node *node) {
    if (node == nullptr)
        return;
    destroy_rec(node->left);
    destroy_rec(node->right);
    delete node;
}


void BinaryTree::insert(double value) {
    auto node = &root;
    while (*node != nullptr) {
        if (value == (*node)->data)
            return;
        value < (*node)->data ? node = &(*node)->left : node = &(*node)->right;
    }
    *node = new Node(value);
}


bool BinaryTree::search(double value) {
    auto node = &root;
    while (*node != nullptr) {
        if ((*node)->data == value)
            return true;
        (*node)->data > value ? node = &(*node)->left : node = &(*node)->right;
    }
    return false;
}


void BinaryTree::remove(double value) {
    auto node = &root;    // ук. на ук. на корневой узел
    auto current = node;  // ук. на ук. на текущий узел
    while (*current != nullptr && (*current)->data != value)  // ищем текущий узел, кот. соотв-ет value
        value < (*current)->data ? current = &(*current)->left : current = &(*current)->right;
    if (*current == nullptr || *current == root)  // если текущий узел не найден или явл. корневым узлом,
        return;                                   // возврат

    Node* node_to_remove = *current;  // ук. на удаляемый узел
    if (node_to_remove->left == nullptr) {  // если удаляемый узел не имеет левого потомка,
        *current = (*current)->right;       // ук. на текущий узел = ук. на его правого потомка,
        delete node_to_remove;              // удаляемый узел удаляется,
        return;                             // возврат
    }  /*
    if (node_to_remove->right == nullptr) {  // если удаляемый узел не имеет правого потомка,
        *current = (*current)->left;         // ук. на текущий узел = ук. на его левого потомка,
        delete node_to_remove;               // удаляемый узел удаляется
        return;
    }  */  // условие для правого потомка не нужно, т. к. будет обработано ниже

    Node* parent_of_biggest_ptr = find_parent_of_biggest_ptr(node_to_remove->left);
                                            // ук. на родителя самого большого узла в левом поддереве
    if (parent_of_biggest_ptr == nullptr) { // если ук. на родителя не найден,
        *current = node_to_remove->left;    // ук. на текущий узел = ук. на левого потомка удаляемого узла,
    } else {                                              // в ином случае
        *current = parent_of_biggest_ptr->right;          // ук. на текущий узел = ук. на правого потомка родителя,
        parent_of_biggest_ptr->right = (*current)->left;  // ук. на правого п. родителя = ук. на левого п. текущего узла,
        (*current)->left = node_to_remove->left;          // ук. на левого п. текущего узла = ук. на левого п. удаляемого узла
    }
    (*current)->right = node_to_remove->right;  // ук. на правого п. текущего узла = ук. на правого п. удаляемого узла
    delete node_to_remove;  // удаляемый узел удаляется
}


void BinaryTree::print_rec(Node* node, int indent) {
    if (node == nullptr)
        return;
    if (node->right != nullptr)
        print_rec(node->right, indent + 4);
    for (int i = 0; i < indent; i++)
        std::cout << " ";
    std::cout << node->data << std::endl;
    if (node->left != nullptr)
        print_rec(node->left, indent + 4);
}


int main() {
    double find = 8;
    double del = find;

    BinaryTree tree;

    tree.insert(1);
    tree.insert(-2);
    tree.insert(-2);
    tree.insert(5);
    tree.insert(8);
    tree.insert(7);
    tree.insert(7.1);
    tree.insert(7.05);
    tree.insert(7.15);
    tree.insert(6.9);
    tree.insert(9);

    tree.print();

    tree.search(find) != 0
        ? std::cout << "Node " << find << " found" << std::endl
        : std::cout << "Node " << find << " not found" << std::endl;

    std::cout << "================================" << std::endl;

    tree.remove(del);

    tree.print();

    tree.search(find) != 0
        ? std::cout << "Node " << find << " found" << std::endl
        : std::cout << "Node " << find << " not found" << std::endl;

    return 0;
}
