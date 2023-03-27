
#ifndef MR2022_BINARY_TREE_H
#define MR2022_BINARY_TREE_H

class Node
{
public:
    double data;
    Node* left;
    Node* right;
    Node(double);
    Node();
};

Node::Node(double value)
{
    data = value;
    left = nullptr;
    right = nullptr;
}


Node::Node()
{
    data = NULL;
    left = nullptr;
    right = nullptr;
}

class BinaryTree
{
public:
    BinaryTree();
    ~BinaryTree();
    void add_node(double);
    void remove(double);
    void print();
    bool search(double);
    double get_max();
    double get_min();
private:
    Node* root;
    Node* delete_node(Node*, double);
    void deleteTree(Node*);
    bool searchNode(Node* node, double data);
    void printNode(Node* node);
    Node* find_min(Node* node);
    Node* find_max(Node* node);
};

double BinaryTree::get_max()
{
    Node* temp;
    temp = find_max(root);
    return temp->data;
}

double BinaryTree::get_min()
{
    Node* temp;
    temp = find_min(root);
    return temp->data;
}

void BinaryTree::print()
{
    printNode(root);
    std:: cout << std:: endl;
}
void BinaryTree::printNode(Node* node)
{
    if (node == nullptr) return;

    printNode(node->left); // рекурсивно обрабатываем левое поддерево
    std::cout << node->data << " "; // выводим значение текущего узла
    printNode(node->right); // рекурсивно обрабатываем правое поддерево
}
void BinaryTree::remove(double data)
{
    root = delete_node(root,data);
}

BinaryTree::BinaryTree()
{
    root = nullptr;
}

void BinaryTree::deleteTree(Node* node)
{
    if (node != nullptr) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

Node* BinaryTree::find_min(Node *node)
{
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

Node* BinaryTree::find_max(Node *node)
{
    while (node->right != nullptr) {
        node = node->right;
    }
    return node;
}

BinaryTree::~BinaryTree()
{
    deleteTree(root);
}

void BinaryTree::add_node(double val)
{
    Node* newNode = new Node(val);
    if (root == nullptr) {
        root = newNode;
    } else
    {
        Node* current = root;
        while (true)
        {
            if (val < current->data)
            {
                if (current->left == nullptr)
                {
                    current->left = newNode;
                    break;
                }
                else current = current->left;
            }
                else
                {
                if (current->right == nullptr) {
                    current->right = newNode;
                    break;
                }
                else current = current->right;
            }
        }
    }
}

Node* BinaryTree::delete_node(Node* node, double value)
{
    if (node == nullptr) {
        return node;
    } else if (value < node->data) {
        node->left = delete_node(node->left, value);
    } else if (value > node->data) {
        node->right = delete_node(node->right, value);
    } else {
        // Узел со значением val найден
        if (node->left == nullptr && node->right == nullptr) {
            // Узел - лист, можно просто удалить
            delete node;
            node = nullptr;
        } else if (node->left == nullptr) {
            // У узла есть только правый потомок
            Node* temp = node;
            node = node->right;
            delete temp;
        } else if (node->right == nullptr) {
            // У узла есть только левый потомок
            Node* temp = node;
            node = node->left;
            delete temp;
        } else {
            // У узла есть и левый, и правый потомок
            // Найдем самый левый узел в правом поддереве
            Node* temp = find_min(node->right);
            // Заменим значение удаляемого узла на значение temp
            node->data = temp->data;
            // Удалим узел с найденным значением из правого поддерева
            node->right = delete_node(node->right, temp->data);
        }
    }
    return node;
}

bool BinaryTree::searchNode(Node *node, double data)
{
    if (node == nullptr) {
        return false;
    }
    if (data < node->data) {
        return searchNode(node->left, data);
    }
    else if (data > node->data) {
        return searchNode(node->right, data);
    }
    else {
        return true;
    }
}

bool BinaryTree::search(double data)
{
    return searchNode(root,data);
}
#endif //MR2022_BINARY_TREE_H
