#include "tree.h"

tree_names::Node::Node() {
    value = 0;
    left = nullptr;
    right = nullptr;
}

tree_names::Node::Node(double value, int key, tree_names::Node *right, tree_names::Node *left) {
    this->value = value;
    this->right = right;
    this->left = left;
    this->key = key;
}

tree_names::Node::~Node() {
    value = 0;
    left = nullptr;
    right = nullptr;

}

tree_names::tree::tree() {
    depth = 0;
    root = nullptr;

}

tree_names::tree::tree(double value, int key) {
    depth = 1;
    root = new Node(value, key);
}

void tree_names::tree::insert(int key, double value) {
    if (root == nullptr){
        root = new Node(value, key);
        depth=1;
        return;
    }

    Node* undertree = root;
    Node** newNodePointer = nullptr;

    while (key != undertree->key){
        if (key > undertree->key){
            newNodePointer = &undertree->right;
            if (undertree->right == nullptr) {
                *newNodePointer = new Node(value, key);
                undertree->right = *newNodePointer;
                break;
            } else {
                undertree = undertree->right;
            }

        } else {
            newNodePointer = &undertree->left;
            if (undertree->left == nullptr){
                *newNodePointer = new Node(value, key);
                undertree->left = *newNodePointer;
                break;
            } else{
                undertree = undertree->left;
            }
        }
    }
    depth++;
}

tree_names::Node *tree_names::tree::find(int key) {
    Node* underTree = root;
    while (underTree != nullptr) {
        if (key == underTree->key) return underTree;
        underTree = (key - underTree->key > 0) ? underTree->right : underTree->left;
    }
    return nullptr;
}



tree_names::Node *tree_names::tree::get_max(tree_names::Node *node) {
    if (node == nullptr) return nullptr;
    if (node->right == nullptr) return node;
    return get_max(node->right);
}

bool tree_names::tree::delete_node(int key, double value) {
    Node** parentNodePointer = &root;

    // find deleted node
    while (*parentNodePointer != nullptr) {
        if (key == (*parentNodePointer)->key) break;
        parentNodePointer = (key > (*parentNodePointer)->key) ? &((*parentNodePointer)->right) : &((*parentNodePointer)->left);
    }
    if (*parentNodePointer == nullptr) return false;
    Node* deletedNode = *parentNodePointer;

    //check if only one neighbour
    if (deletedNode->right == nullptr) { *parentNodePointer = deletedNode->left;  depth--; return true; }
    if (deletedNode->left == nullptr)  { *parentNodePointer = deletedNode->right; depth--; return true; }

    // find node with min key (left) in right undertree
    Node** smallest_ptr = &deletedNode->right;
    while ((*smallest_ptr)->left != nullptr) smallest_ptr = &((*smallest_ptr)->left);


    *parentNodePointer = *smallest_ptr;
    (*parentNodePointer)->left = deletedNode->left;

    *smallest_ptr = (*parentNodePointer)->right;
    (*parentNodePointer)->right = deletedNode->right;

    delete deletedNode;
    depth--;
    return true;
}


void tree_names::tree::print_right() {
    Node* currentNode = root;
    std::cout << currentNode->key << "\t";


    while (currentNode->right != nullptr){
        std::cout << currentNode->right->key << "\t";
        currentNode = currentNode->right;
    }
    std::cout <<  "\n";


}









/*void tree_names::tree::clear() {
    while (depth) {
        delete_node(root->key, root->value);
    }
}*/