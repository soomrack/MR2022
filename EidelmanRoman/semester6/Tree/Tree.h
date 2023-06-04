#ifndef MR2022_TREE_H
#define MR2022_TREE_H

#include <iostream>


class Node {
public:
    int key;
    double value;
    Node* left_node = nullptr;
    Node* right_node = nullptr;

    Node() = default;
    Node(int key_, double value_);
};


Node::Node(int key_, double value_){
    key = key_; value = value_;
}


class Tree {
public:
    Node* root;
    Tree(Node tree_root);

    void insert(Node node);
    Node find_node(int key); // ???
};


Tree::Tree(Node tree_root) {
    root = &tree_root;
};


void Tree::insert(Node node) {
    Node* link = root;
    while (link != nullptr) {
        link = (link->key > node.key) ? (link = link->left_node) : (link = link->right_node);
    }
    link = &node;
}


//
//
//    if (key < node.key) {
//        if (node.left_node == nullptr)
//            node.left_node = new Node(key, value);
//        else
//            insert(node->left_node, key, value);
//    }
//    else if (key >= node->key) {
//        if (node->right_node == nullptr)
//            node->right_node = new Node(key, value);
//        else
//            insert(node->right_node, key, value);
//    }
//}


//Node*& Tree::search(Node*& node, int key) {
//    if (node->key == key)
//        return node;
//    return (key < node->key) ? search(node->left_node, key) : search(node->right_node, key);
//}
//
//
//Node*& Tree::get_min(Node*& node) {
//    if (node->left_node == nullptr)
//        return node;
//    return get_min(node->left_node);
//}
//
//
//Node*& Tree::get_max(Node*& node) {
//    if (node->right_node == nullptr)
//        return node;
//    return get_max(node->right_node);
//}
//
//
//Node*& Tree::delete_node(Node*& node, int key) {
//    if (key < node->key)
//        node->left_node = delete_node(node->left_node, key);
//    else if (key > node->key)
//            node->right_node = delete_node(node->right_node, key);
//         else {
//             if (node->left_node == nullptr || node->right_node == nullptr)
//                 node = (node->left_node == nullptr) ? node->right_node : node->left_node;
//             else {
//                 Node*& maxInLeft = get_max(node->left_node);
//                 node->key = maxInLeft->key;
//                 node->value = maxInLeft->value;
//                 node->right_node = delete_node(node->right_node, maxInLeft->key);
//             }
//         }
//    return node;
//}
//
//
//void Tree::print_Tree(Node*& node) {
//    print_Tree(node->left_node);
//    std::cout<<node->value;
//    print_Tree(node->right_node);
//}
//
//
//void Tree::delete_Tree(Node*& node) {
//    delete_Tree(node->left_node);
//    delete_Tree(node->right_node);
//    std::cout<<node->value;
//}


#endif //MR2022_TREE_H
