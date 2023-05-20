#include <iostream>
using namespace std;

class BinaryTree {
private:
    struct Node {
        int data;
        Node* left;
        Node* right;
        Node(int value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* root;

public:
    BinaryTree();
     ~BinaryTree();
     void add(int value);  //  добавление элемента в дерево
     void del(int value);  //  удаление элемента из дерева
     bool get(int value);  //  поиск элемента в дереве
private:
     void destroy_tree(Node* node);  //  рекурсивное удаление дерева
     void add(int value, Node* node);  //  рекурсивное добавление элемента в дерево
     void del(int value, Node* node);  //  рекурсивное удаление элемента из дерева 
     bool get(int value, Node* node);  //  рекурсивный поиск элемента в дереве
     Node* find_min(Node* node);  //  поиск узла с минимальным значением в дереве
    
};
    
    
    BinaryTree::BinaryTree() : root(nullptr) {}
    
    BinaryTree::~BinaryTree() {
        destroy_tree(root);
    }

    void BinaryTree::add(int value) {
        if (root == nullptr) {
            root = new Node(value);
        } else {
            add(value, root);
            
    void  BinaryTree::del(int value) {
        del(value, root);
    }

    bool  BinaryTree::get(int value) {
        return get(value, root);
    }

  
    void  BinaryTree::destroy_tree(Node* node) {
        if (node != nullptr) {
            destroy_tree(node->left);
            destroy_tree(node->right);
            delete node;
        }
    }

   void  BinaryTree::add(int value, Node* node) {
    Node* next_step = nullptr; 
        if (value < node->data) {
            if (node->left == nullptr) {
                node->left = new Node(value);
            }
            
             else {
                next_step = node->left);
            }
        } else if (value > node->data) {
            if (node->right == nullptr) {
                node->right = new Node(value);
            } else {
                next_step = node->right;
            }
        }
        add(value, next_step ); 
    }

void BinaryTree::del(int value, Node*& node) {
    if (node == nullptr) {
        return;
    }
    if (value < node->data) {
        del(value, node->left);
        return;
    }
    if (value > node->data) {
        del(value, node->right);
        return;
    }
    if (node->left == nullptr) {
        Node* temp = node;
        node = node->right;
        delete temp;
    } else if (node->right == nullptr) {
        Node* temp = node;
        node = node->left;
        delete temp;
    } else {
        Node* temp = find_min(node->right);
        node->data = temp->data;
        del(temp->data, node->right);
    }
}
    bool  BinaryTree::get(int value, Node* node) {
        if (node == nullptr) {
            return false;
        } else if (node->data == value) {
            return true;
        } else if (value < node->data) {
            return get(value, node->left);
        } else {
            return get(value, node->right);
        }
    }

    Node*  BinaryTree::find_min(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

int main() {
    BinaryTree tree;

    tree.add(5);
    tree.add(3);
    tree.add(7);
    tree.add(2);
    tree.add(4);
    tree.add(6);
    tree.add(8);

    if (tree.get(5)) {
        cout << "Element 5 is in the tree" << endl;
    }

    tree.del(5);

    if (!tree.get(5)) {
        cout << "Element 5 is not in the tree anymore" << endl;
    }

    return 0;
}
