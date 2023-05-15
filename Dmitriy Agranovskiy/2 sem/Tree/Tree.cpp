#include <iostream>

struct Node {
    int value;
    Node *left;
    Node *right;
};

class BinaryTree {
public:
    BinaryTree() : root(nullptr) {}

    void add_node(int value) {
        Node *new_node = new Node{value, nullptr, nullptr};
        if (root == nullptr) {
            root = new_node;
        } else {
            add_node_helper(root, new_node);
        }
    }

    void delete_node(int value) {
        root = delete_node_helper(root, value);
    }

    Node *find_node(int value) {
        return find_node_helper(root, value);
    }

    int getRoot(){
        return root->value;
    }

private:
    Node *root;

    void add_node_helper(Node *curr_node, Node *new_node) {
        if (new_node->value < curr_node->value) {
            if (curr_node->left == nullptr) {
                curr_node->left = new_node;
            } else {
                add_node_helper(curr_node->left, new_node);
            }
        } else {
            if (curr_node->right == nullptr) {
                curr_node->right = new_node;
            } else {
                add_node_helper(curr_node->right, new_node);
            }
        }
    }

    Node *delete_node_helper(Node *curr_node, int value) {  // Находим и удаляем минимальный элемент правого поддерева
                                                            // и используем его значение в качестве корневого или промежуточного узла
        if (curr_node == nullptr) {
            return nullptr;
        }

        if (value < curr_node->value) {
            curr_node->left = delete_node_helper(curr_node->left, value);  // Восстанавливаем связь с правым бОльшим
        } else if (value > curr_node->value) {
            curr_node->right = delete_node_helper(curr_node->right, value);  // Восстанавливаем связь с левым бОльшим
        } else {
            if (curr_node->left == nullptr) {
                Node *temp = curr_node->right;
                delete curr_node;
                return temp;
            } else if (curr_node->right == nullptr) {
                Node *temp = curr_node->left;
                delete curr_node;
                return temp;
            }

            Node *temp = find_min(curr_node->right);  // Ищем минимальный элемент в правом поддереве
            curr_node->value = temp->value; // Используем его значение в качестве корневого или промежуточного узла
            curr_node->right = delete_node_helper(curr_node->right, temp->value); // Удаляем нужный узел
        }

        return curr_node;
    }

    Node *find_node_helper(Node *curr_node, int value) {
        if (curr_node == nullptr) {
            return nullptr;
        }

        if (value == curr_node->value) {
            return curr_node;
        } else if (value < curr_node->value) {
            return find_node_helper(curr_node->left, value);
        } else {
            return find_node_helper(curr_node->right, value);
        }
    }

    Node *find_min(Node *curr_node) {
        while (curr_node->left != nullptr) {
            curr_node = curr_node->left;
        }
        return curr_node;
    }
};


int main() {
    BinaryTree Tree;
    Tree.add_node(19);
    Tree.add_node(14);
    Tree.add_node(53);
    Tree.add_node(3);
    Tree.add_node(15);
    Tree.add_node(26);
    Tree.add_node(58);
    Tree.add_node(29);

    Tree.delete_node(19);
    std::cout << Tree.getRoot();
    return 0;
}
