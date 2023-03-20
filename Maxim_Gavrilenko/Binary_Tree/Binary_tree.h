//
// Created by El1x3r7714 on 21/03/2023.
//
#ifndef MR2022_BINARY_TREE_H
#define MR2022_BINARY_TREE_H
class BINARY_EXCEPTION: public std::domain_error
{
public:
    BINARY_EXCEPTION(const char* const str): std::domain_error(str) {};
};

BINARY_EXCEPTION BADALLOC("Memory is not allocated");

class Node
{
public:
    int data;
    Node* left;
    Node* right;
    Node(int);
    Node();
};

Node::Node(int value)
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

class BinaryTree:Node
{
public:
    BinaryTree();
    ~BinaryTree();
    void addNode(int);
    Node deleteNode(Node*, int);
private:
    Node* root;
    void deleteTree(Node*);
};


BinaryTree::BinaryTree()
{
    root = nullptr;
}

void BinaryTree::deleteTree(Node* node) {
    if (node != nullptr) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}


BinaryTree::~BinaryTree()
{
    deleteTree(root);
}




void BinaryTree::addNode(int val)
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

/*Node* BinaryTree::deleteNode(Node* node, int value)
{
    if (node == nullptr) {
        return node;
    } else if (value < node->data) {
        node->left = deleteNode(node->left, value);
    } else if (value > node->data) {
        node->right = deleteNode(node->right, value);
    } else {
        // Узел со значением val найден
        if (node->left == nullptr && node->right == nullptr) {
            // Узел - лист, можно просто удалить
            delete node;
            node = nullptr;
        } else if (node->left == nullptr) {
            // У узла есть только правый потомок
            Node<T>* temp = node;
            node = node->right;
            delete temp;
        } else if (node->right == nullptr) {
            // У узла есть только левый потомок
            Node<T>* temp = node;
            node = node->left;
            delete temp;
        } else {
            // У узла есть и левый, и правый потомок
            // Найдем самый левый узел в правом поддереве
            Node<T>* temp = findMin(node->right);
            // Заменим значение удаляемого узла на значение temp
            node->value = temp->value;
            // Удалим узел с найденным значением из правого поддерева
            node->right = deleteNode(node->right, temp->value);
        }
    }
    return node;
}*/
#endif //MR2022_BINARY_TREE_H
