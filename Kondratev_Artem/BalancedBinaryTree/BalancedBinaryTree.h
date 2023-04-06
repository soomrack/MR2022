//
// Created by user on 3/19/23.
//

#ifndef HELLO_WORLD_BINARYTREE_H
#define HELLO_WORLD_BINARYTREE_H


class Node {
    friend class BalancedBinaryTree;

private:
    Node* parent;
    Node* left;
    Node* right;
    void* data;

public:
    unsigned int key;

public:
    explicit Node(unsigned int _key, void* _data);
    void* get_data();
};


class BalancedBinaryTree {
private:
    Node* root;
    unsigned int height;

public:
    BalancedBinaryTree();

private:
    static void changeHeight(Node* node);
    void append(Node* new_node, Node* node);

public:
    void append(unsigned int key, void* data=nullptr);
    int pop(int key);
    unsigned int getHeight() const;

private:
    static unsigned int findHeight(Node* node);
    Node* find(Node* node, unsigned int key);

public:
    Node* find(unsigned int key);

private:
    void LLTurn(Node* node);
    void RRTurn(Node* node);
    void LRTurn(Node* node);
    void RLTurn(Node* node);
    void balance(Node* node, Node* prev1=nullptr, Node* prev2=nullptr);
};


Node::Node(unsigned int _key, void* _data) {
    key = _key;
    data = _data;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}


void* Node::get_data() {
    return data;
}


BalancedBinaryTree::BalancedBinaryTree() {
    root = nullptr;
    height = 0;
}


void BalancedBinaryTree::changeHeight(Node* node) {
    if (!node->parent) {
        return;
    }
    if (node->parent->left && node->parent->right) {
        return;
    }
    changeHeight(node->parent);
}


void BalancedBinaryTree::append(Node* new_node, Node* node) {

    if (new_node->key < node->key) {
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


void BalancedBinaryTree::append(unsigned int key, void* data) {
    if (find(key)) {
        return;
    }

    auto* new_node = new Node(key, data);

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


int BalancedBinaryTree::pop(int key) {

}


unsigned int BalancedBinaryTree::getHeight() const {
    return height;
}


unsigned int BalancedBinaryTree::findHeight(Node* node) {
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


Node* BalancedBinaryTree::find(Node* node, unsigned int key) {
    if (!node || node->key == key) {
        return node;
    }
    if (node->key > key) {
        if (!node->left) {
            return node->left;
        }
        return find(node->left, key);
    }
    else {
        if (!node->right) {
            return node->right;
        }
        return find(node->right, key);
    }
}


Node* BalancedBinaryTree::find(unsigned int key) {
    return find(root, key);
}


void BalancedBinaryTree::LLTurn(Node* node) {  //  z?
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


void BalancedBinaryTree::RRTurn(Node* node) {  //  z?
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


void BalancedBinaryTree::LRTurn(Node* node) {
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


void BalancedBinaryTree::RLTurn(Node* node) {
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


void BalancedBinaryTree::balance(Node* node, Node* prev1, Node* prev2) {
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
