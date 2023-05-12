#include <iostream>


// класс узла
class Node {
public:
    explicit Node(double val);
    ~Node();

    double value;
    Node* left;
    Node* right;
};


// класс бинарного дерева
class BinaryTree {
private:
    Node* root;

    void insert_req(Node* node, double value);  // рекурсивная функция вставки узла
    void traverse_req_list(Node* node);  // рекурсивная функция обхода узлов (in-order traversal)
    void traverse_req_tree(Node* node, int level);  // рекурсивная функция обхода узлов (in-order traversal)
    Node* find_req(Node* node, double value);  // рекурсивная функция поиска узла
    Node* remove_req(Node* node, double value);  // рекурсивная функция удаления узла

    static Node* minValueNode(Node* node);  // функция поиска узла с минимальным значением
    static Node* maxValueNode(Node* node);  // функция поиска узла с максимальным значением

public:
    BinaryTree();
    ~BinaryTree();

    void insert(double value);  // метод вставки узла
    void traverse();  // метод обхода узлов (in-order traversal)
    Node* find(double value);  // метод поиска узла
    void remove(double value);  // метод удаления узла
    //void root_value();  // метод, который выводит значение корневого узла
};


// конструктор класса узла
Node::Node(double val) {
    value = val;
    left = nullptr;
    right = nullptr;
    //std::cout << "Node created with value " << value << std::endl;
}

// деструктор класса узла
Node::~Node() {
    delete left;
    delete right;
    //std::cout << "Node with value " << value << " deleted" << std::endl;
}


// конструктор класса бинарного дерева
BinaryTree::BinaryTree() {
    root = nullptr;
    //std::cout << "Binary Tree created with value " << root << std::endl;
}

// деструктор класса бинарного дерева
BinaryTree::~BinaryTree() {
    delete root;
    //std::cout << "Binary Tree with value " << root << " deleted" << std::endl;
}


// рекурсивная функция вставки узла
void BinaryTree::insert_req(Node* node, double value) {
    if (value == node->value) {
        node->value = value;
    } else if (value < node->value) {
        if (node->left == nullptr) {
            node->left = new Node(value);
        } else {
            insert_req(node->left, value);
        }
    } else {
        if (node->right == nullptr) {
            node->right = new Node(value);
        } else {
            insert_req(node->right, value);
        }
    }
}

// рекурсивная функция обхода узлов (in-order traversal)
void BinaryTree::traverse_req_list(Node* node) {
    if (node != nullptr) {
        traverse_req_list(node->left);
        std::cout << node->value << " ";
        traverse_req_list(node->right);
    }
}
void BinaryTree::traverse_req_tree(Node* node, int level) {
    if (node != nullptr) {
        traverse_req_tree(node->right, level + 1);
        for (int i = 0; i < level; i++) {
            std::cout << "    ";
        }
        std::cout << node->value << std::endl;
        traverse_req_tree(node->left, level + 1);
    }
}

// рекурсивная функция поиска узла
Node* BinaryTree::find_req(Node* node, double value) {
    if (node == nullptr || node->value == value) {
        return node;
    } else if (value < node->value) {
        return find_req(node->left, value);
    } else {
        return find_req(node->right, value);
    }
}

// рекурсивная функция удаления узла
Node* BinaryTree::remove_req(Node* node, double value) {
    if (node == nullptr) {
        return node;
    }
    if (value < node->value) {
        node->left = remove_req(node->left, value);
    } else if (value > node->value) {
        node->right = remove_req(node->right, value);
    } else {
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        } else if (node->left == nullptr) {
            Node* temp = minValueNode(node->right);
            node->value = temp->value;
            node->right = remove_req(node->right, temp->value);
            //node->right = nullptr;
            //*node = *temp;
            //delete temp;
        } else if (node->right == nullptr) {
            Node* temp = maxValueNode(node->left);
            node->value = temp->value;
            node->left = remove_req(node->left, temp->value);
            //node->left = nullptr;
            //*node = *temp;
            //delete temp;
        } else {
            Node* temp = minValueNode(node->right);
            node->value = temp->value;
            node->right = remove_req(node->right, temp->value);
        }
    }
    return node;
}

// функция поиска узла с минимальным значением
Node* BinaryTree::minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

// функция поиска узла с максимальным значением
Node* BinaryTree::maxValueNode(Node* node) {
    Node* current = node;
    while (current->right != nullptr) {
        current = current->right;
    }
    return current;
}


// метод вставки узла
void BinaryTree::insert(double value) {
    if (root == nullptr) {
        root = new Node(value);
    } else {
        insert_req(root, value);
    }
}

// метод обхода узлов (in-order traversal)
void BinaryTree::traverse() {
    traverse_req_list(root);
    std::cout << std::endl;
    traverse_req_tree(root, 0);
    std::cout << std::endl;
}

// метод поиска узла
Node* BinaryTree::find(double value) {
    return find_req(root, value);
}

// метод удаления узла
void BinaryTree::remove(double value) {
    root = remove_req(root, value);
}

// метод, который выводит значение корневого узла
/*
void BinaryTree::root_value() {
    if (root == nullptr) {
        std::cout << "Binary Tree is empty" << std::endl;
        return;
    }
    std::cout << "Root value: " << root->value << std::endl;
}
*/

int main() {
    BinaryTree tree;

    tree.insert(1);
    tree.insert(-2);
    tree.insert(-2);
    tree.insert(5);
    tree.insert(8);
    tree.insert(7);
    //tree.insert(7.1);
    //tree.insert(6.9);
    tree.insert(9);
    tree.traverse();

    std::cout << "==================" << std::endl;

    tree.remove(5);
    tree.traverse();

    Node* found = tree.find(7);
    if (found != nullptr) {
        std::cout << "Found node with value: " << found->value << std::endl;
    } else {
        std::cout << "Node not found." << std::endl;
    }

    return 0;
}
