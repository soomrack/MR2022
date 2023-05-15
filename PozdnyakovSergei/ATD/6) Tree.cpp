#include <iostream>


class Node{
public:
    int value;
    Node* left;
    Node* right;
    explicit Node(int new_data);
};


class Tree{
private:
    Node* get_node(int find_data);
    Node* get_parent_node(int find_data);
    void delete_all(Node* del_root);
public:
    Node* root;
    Tree(){root = nullptr;};
    ~Tree();
    void add(int new_data);
    bool find(int find_data);
    void del(int del_data);
};

void Tree::add(int new_data) {
    Node** link = &root;
    while(*link != nullptr){
        link = new_data < (*link)->value ? &((*link)->left) : &((*link)->right);
    }
    *link = new Node(new_data);
}

bool Tree::find(int find_data) {
    auto current_node = root;
    if(get_node(find_data) != nullptr){
        return true;
    }
    return false;
}

void Tree::del(int del_data) {
    auto parent_node = get_parent_node(del_data);
    auto current_node_link = del_data < parent_node->value ? &(parent_node->left) : &(parent_node->right);
    auto del_node = *current_node_link;

    if((*current_node_link)->right == nullptr){
        *current_node_link = (*current_node_link)->left;
        delete del_node;
        return;
    }
    if((*current_node_link)->left == nullptr) {
        *current_node_link = (*current_node_link)->right;
        delete del_node;
        return;
    }
    auto del_left_link = &((*current_node_link)->left);
    auto del_right_link = &((*current_node_link)->right);
    auto del_link = current_node_link;

    // Поиск самого левого справа
    auto most_left_link = del_right_link;
    auto next_node = (*most_left_link)->left;
    while (next_node != nullptr) {
        most_left_link = &((*most_left_link)->left);
        next_node = next_node->left;
    }

    auto most_left = *most_left_link;
    (*del_link) = most_left;
    most_left->left = (*del_left_link);
    auto mem_link = most_left->right;
    most_left->right = (*del_right_link);
    (*most_left_link) = mem_link;

    delete del_node;
}

Node *Tree::get_node(int find_data) {
    Node** link = &root;
    while(*link != nullptr){
        if((*link)->value == find_data) return *link;
        link = find_data < (*link)->value ? &((*link)->left) : &((*link)->right);
    }
    return nullptr;
}

Node *Tree::get_parent_node(int find_data) {
    Node** link = &root;
    Node** parent_link = nullptr;
    while(*link != nullptr){
        parent_link = link;
        link = find_data < (*link)->value ? &((*link)->left) : &((*link)->right);
        if((*link)->value == find_data) return *parent_link;
    }
    return nullptr;
}

Tree::~Tree() {
    delete_all(root);
}

void Tree::delete_all(Node* del_root) {
    if (del_root == nullptr)   // Базовый случай
    {
        return;
    }
    delete_all(del_root->left);
    delete_all(del_root->right);
    delete del_root;
}


Node::Node(int new_data) {
    value = new_data;
    left = nullptr;
    right = nullptr;
}

void preorder_print(Node *root)
{
    if (root == nullptr)   // Базовый случай
    {
        return;
    }
    std::cout << root->value << " ";
    preorder_print(root->left);
    preorder_print(root->right);
}


void main(){
    Tree tree;
    tree.add(1);
    tree.add(2);
    tree.add(3);
    tree.add(4);
    tree.add(5);

    preorder_print(tree.root);

    std::cout << std::endl;

    tree.del(6);

    preorder_print(tree.root);

    std::cout << tree.find(6) << std::endl;
}
