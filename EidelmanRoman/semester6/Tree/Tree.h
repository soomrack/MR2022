#ifndef MR2022_TREE_H
#define MR2022_TREE_H


class Node {
public:
    int8_t key;
    double value;
    Node* left_node = nullptr;
    Node* right_node = nullptr;

    Node() = default;
    Node(int8_t key, double value);
};


Node::Node(int8_t key, double value){
    this->key = key; this->value = value;
}


class Tree {
private:
    int8_t items;
public:
    Tree() = default;

    void insert(Node*& node, int key, int value);
    Node*& search(Node*& node, int8_t key);
    Node*& get_min(Node*& node);
    Node*& get_max(Node*& node);
    Node*& delete_node(Node*& node, int8_t key);
    void print_Tree(Node*& node);
    void delete_Tree(Node*& node);
};


void Tree::insert(Node*& node, int key, int value) {
    if (key < node->key) {
        if (node->left_node == nullptr)
            node->left_node = new Node(key, value);
        else
            insert(node->left_node, key, value);
    }
    else if (key >= node->key) {
        if (node->right_node == nullptr)
            node->right_node = new Node(key, value);
        else
            insert(node->right_node, key, value);
    }
}


Node*& Tree::search(Node*& node, int8_t key) {
    if (node->key == key)
        return node;
    return (key < node->key) ? search(node->left_node, key) : search(node->right_node, key);
}


Node*& Tree::get_min(Node*& node) {
    if (node->left_node == nullptr)
        return node;
    return get_min(node->left_node);
}


Node*& Tree::get_max(Node*& node) {
    if (node->right_node == nullptr)
        return node;
    return get_max(node->right_node);
}


Node*& Tree::delete_node(Node*& node, int8_t key) {
    if (key < node->key)
        node->left_node = delete_node(node->left_node, key);
    else if (key > node->key)
            node->right_node = delete_node(node->right_node, key);
         else {
             if (node->left_node == nullptr || node->right_node == nullptr)
                 node = (node->left_node == nullptr) ? node->right_node : node->left_node;
             else {
                 Node*& maxInLeft = get_max(node->left_node);
                 node->key = maxInLeft->key;
                 node->value = maxInLeft->value;
                 node->right_node = delete_node(node->right_node, maxInLeft->key);
             }
         }
    return node;
}


void Tree::print_Tree(Node*& node) {
    print_Tree(node->left_node);
    std::cout<<node->value;
    print_Tree(node->right_node);
}


void Tree::delete_Tree(Node*& node) {
    delete_Tree(node->left_node);
    delete_Tree(node->right_node);
    std::cout<<node->value;
}


#endif //MR2022_TREE_H
