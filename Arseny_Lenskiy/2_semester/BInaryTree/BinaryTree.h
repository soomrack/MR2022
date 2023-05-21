template<typename T>
class BinaryTree {
private:
    struct Node {
        T data;
        Node *left;
        Node *right;

        Node(T data) : data(data), left(nullptr), right(nullptr) {}
    };

private:
    Node *root;

    Node *getSuccessor(Node *delNode);

public:
    BinaryTree() : root(nullptr) {}

    void insert(T data);
    bool search(T data);
    void remove(T data);
};

template<typename T>
void BinaryTree<T>::insert(T data) {
    Node **node = &root;

    while (*node != nullptr) {
        node = (*node)->data > data ? &((*node)->left) : &((*node)->right);
    }

    *node = new Node(data);
}

template<typename T>
bool BinaryTree<T>::search(T data) {
    Node *current = root;
    while (current != nullptr) {
        if (data == current->data) {
            return true;
        } else current = data < current->data ? current->left : current->right;
    }
    return false;
}

template<typename T>
void BinaryTree<T>::remove(T data) {
    Node *current = root;
    Node *parent = nullptr;
    bool isLeft = true;

    while (current != nullptr && current->data != data) {
        parent = current;
        if (data < current->data) {
            current = current->left;
            isLeft = true;
        } else {
            current = current->right;
            isLeft = false;
        }
    }

    if (current != nullptr) {
        if (current->left == nullptr && current->right == nullptr) {
            if (current == root) {
                root = nullptr;
            } else if (isLeft) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
            delete current;
        } else if (current->left == nullptr) {
            if (current == root) {
                root = current->right;
            } else if (isLeft) {
                parent->left = current->right;
            } else {
                parent->right = current->right;
            }
            delete current;
        } else if (current->right == nullptr) {
            if (current == root) {
                root = current->left;
            } else if (isLeft) {
                parent->left = current->left;
            } else {
                parent->right = current->left;
            }
            delete current;
        } else {
            Node *successor = getSuccessor(current);
            if (current == root) {
                root = successor;
            } else if (isLeft) {
                parent->left = successor;
            } else {
                parent->right = successor;
            }
            successor->left = current->left;
            delete current;
        }
    }
}

template<typename T>
typename BinaryTree<T>::Node *BinaryTree<T>::getSuccessor(BinaryTree::Node *delNode) {
    Node *successorParent = delNode;
    Node *successor = delNode;
    Node *current = delNode->right;
    while (current != nullptr) {
        successorParent = successor;
        successor = current;
        current = current->left;
    }
    if (successor != delNode->right) {
        successorParent->left = successor->right;
        successor->right = delNode->right;
    }
    return successor;
}
