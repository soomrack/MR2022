//
// Created by user on 3/19/23.
//

#ifndef HELLO_WORLD_BINARYTREE_H
#define HELLO_WORLD_BINARYTREE_H


class Node {
    friend class BinaryTree;

private:
    Node* parent;
    Node* left;
    Node* right;

public:
    int data;

public:
    explicit Node(int _data);
};


class BinaryTree {
private:
    Node* root;
    unsigned int height;

public:
    BinaryTree();

private:
    static void changeHeight(Node* node);
    void append(Node* new_node, Node* node);

public:
    void append(int data);
    int pop(int data);
    unsigned int getHeight() const;

private:
    static unsigned int findHeight(Node* node);
    Node* find(Node* node, int data);

public:
    Node* find(int data);

private:
    void LLTurn(Node* node);
    void RRTurn(Node* node);
    void LRTurn(Node* node);
    void RLTurn(Node* node);
    void balance(Node* node, Node* prev1=nullptr, Node* prev2=nullptr);
};


Node::Node(int _data) {
    data = _data;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}


BinaryTree::BinaryTree() {
    root = nullptr;
    height = 0;
}


void BinaryTree::changeHeight(Node* node) {
    if (!node->parent) {
        return;
    }
    if (node->parent->left && node->parent->right) {
        return;
    }
    changeHeight(node->parent);
}


void BinaryTree::append(Node* new_node, Node* node) {

    if (new_node->data < node->data) {
        if (!node->left) {
            node->left = new_node;
            new_node->parent = node;
        }
        else {
            append(new_node, node->left);
        }
    }
    else {
        if (!node->right) {
            node->right = new_node;
            new_node->parent = node;
        }
        else {
            append(new_node, node->right);
        }
    }
}


void BinaryTree::append(int data) {
    if (find(data)) {
        return;
    }

    auto* new_node = new Node(data);

    if (!root) {
        root = new_node;
        height = 1;
        return;
    }

    append(new_node, root);
    changeHeight(new_node);
    balance(new_node->parent, new_node);
    height = findHeight(root);
}


unsigned int BinaryTree::getHeight() const {
    return height;
}


unsigned int BinaryTree::findHeight(Node* node) {
    if (!node) {
        return 0;
    }
    if (!node->left && !node->right) {
        return 1;
    }
    unsigned int left_height = findHeight(node->left);
    unsigned int right_height = findHeight(node->right);

    return (left_height > right_height) ? left_height + 1 : right_height + 1;
}


Node* BinaryTree::find(Node* node, int data) {
    if (!node || node->data == data) {
        return node;
    }
    if (node->data > data) {
        if (!node->left) {
            return node->left;
        }
        return find(node->left, data);
    }
    else {
        if (!node->right) {
            return node->right;
        }
        return find(node->right, data);
    }
}


Node* BinaryTree::find(int data) {
    return find(root, data);
}


void BinaryTree::LLTurn(Node* node) {  //  z?
    /*      c     ->     b
     *     /            / \
     *    b            a   c
     *   / \              /
     *  a   z            z
     */
    Node* c = node;
    Node* b = c->left;
    Node* z = b->right;

    if (c == root) {
        root = b;
    }
    else {
        if (c == c->parent->left) {
            c->parent->left = b;
        }
        else {
            c->parent->right = b;
        }
    }

    if (z) {
        z->parent = c;
    }

    c->left = z;
    b->parent = c->parent;
    b->right = c;
    c->parent = b;
}


void BinaryTree::RRTurn(Node* node) {  //  z?
    /*      c     ->     b
     *       \          / \
     *        b        c   a
     *       / \        \
     *      z   a        z
     */
    Node* c = node;
    Node* b = c->right;
    Node* z = b->left;

    if (c == root) {
        root = b;
    }
    else {
        if (c == c->parent->left) {
            c->parent->left = b;
        }
        else {
            c->parent->right = b;
        }
    }

    if (z) {
        z->parent = c;
    }

    c->right = z;
    b->parent = c->parent;
    b->left = c;
    c->parent = b;
}


void BinaryTree::LRTurn(Node* node) {
    /*      c     ->     a
     *     /           /   \
     *    b           b     c
     *     \           \   /
     *      a           x y
     *     / \
     *    x   y
     */
    Node* c = node;
    Node* b = c->left;
    Node* a = b->right;
    Node* x = a->left;
    Node* y = a->right;

    if (c == root) {
        root = a;
    }
    else {
        if (c == c->parent->left) {
            c->parent->left = a;
        }
        else {
            c->parent->right = a;
        }
    }

    if (x) {
        x->parent = b;
    }
    if (y) {
        y->parent = c;
    }

    a->parent = c->parent;
    a->left = b;
    b->parent = a;
    b->right = x;
    a->right = c;
    c->parent = a;
    c->left = y;
}


void BinaryTree::RLTurn(Node* node) {
    /*         c     ->     a
     *          \         /   \
     *           b       c     b
     *          /         \   /
     *         a           x y
     *        / \
     *       x   y
     */
    Node* c = node;
    Node* b = c->right;
    Node* a = b->left;
    Node* x = a->left;
    Node* y = a->right;

    if (c == root) {
        root = a;
    }
    else {
        if (c == c->parent->left) {
            c->parent->left = a;
        }
        else {
            c->parent->right = a;
        }
    }

    if (x) {
        x->parent = c;
    }
    if (y) {
        y->parent = b;
    }

    a->parent = c->parent;
    a->left = c;
    c->parent = a;
    c->right = x;
    a->right = b;
    b->parent = a;
    b->left = y;
}


void BinaryTree::balance(Node* node, Node* prev1, Node* prev2) {
    long int right_h = findHeight(node->right);
    long int left_h = findHeight(node->left);
    long int delta_height = right_h - left_h;

    if (delta_height == -2) {
        if (prev1 && prev2 == prev1->left) {
            LLTurn(node);
        }
        else {
            LRTurn(node);
        }
        return;
    }

    if (delta_height == 2) {
        if (prev1 && prev2 == prev1->right) {
            RRTurn(node);
        }
        else {
            RLTurn(node);
        }
        return;
    }

    if (node->parent) {
        balance(node->parent, node, prev1);
    }
}


#endif //HELLO_WORLD_BINARYTREE_H
