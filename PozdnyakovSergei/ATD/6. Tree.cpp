#include <iostream>


class Node {
public:
    unsigned int value;
    Node* left;
    Node* right;
    Node(unsigned int new_value);
    int key;
};


class Tree {
private:
    Node* get_node (unsigned int find_value);
    Node* get_parent (unsigned int find_value);
    void delete_all(Node* del_root);
public:
    Node* root;
    Tree();
    ~Tree();
    void insert(unsigned int new_value);
    void del(unsigned int del_value);
    bool find_val(unsigned int find_value);
};


Tree::Tree() {
    root = nullptr;
}


void Tree::insert(unsigned int new_value) {
    Node** link = &root;
    while (*link != nullptr) {
        link = new_value < (*link)->value ? &((*link)->left) : &((*link)->right);
    }
    *link = new Node(new_value);
}


/*void Tree::del(unsigned int del_value) {

    Node **node_to_del = &root;
    while (*node_to_del != nullptr) {
        if (del_value == (*node_to_del))
    }

    auto parent_node = get_parent(del_value);
    auto current_node_link = del_value < parent_node->value ? &(parent_node->left) : &(parent_node->right);
    auto del_node = *current_node_link;

    if (get_node(del_value) == nullptr) {
        return;
    }

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
    (*most_left_link) = mem_link;
    most_left->right = (*del_right_link);

    delete del_node;
}*/


void Tree::del(unsigned int del_value) {
    Node** to_del = &root;
    while (*to_del != nullptr) {
        if (del_value == (*to_del)->key) break;
        to_del = del_value > (*to_del)->key? &(*to_del)->right:  &(*to_del)->left;
    }
    if (*to_del == nullptr) return;
    Node* del = *to_del;
    if (((*to_del)->left == nullptr) && ((*to_del)->right == nullptr)) {
        *to_del = nullptr;
        delete (*to_del);
    }
    if ((*to_del)->left == nullptr) {
        *to_del = (*to_del)->right;
        delete del;
    }
    if ((*to_del)->right == nullptr) {
        *to_del = (*to_del)->left;
        delete del;
    }
    Node** temp_link = &((*to_del)->right);
    while ((*temp_link)->left) temp_link = &((*temp_link)->left);
    *to_del = *temp_link;
    (*to_del)->right = del->right;
    (*to_del)->left = del->left;
    *temp_link = (*temp_link)->right;
    delete del;
}


bool Tree::find_val(unsigned int find_value) {
    if (get_node(find_value) != nullptr) {
        return true;
    }
    return false;
}


Node* get_right (Node* first_node) {
    auto current_node = first_node;
    while (current_node != nullptr) {
        if (current_node->right == nullptr) {
            break;
        }
        current_node = current_node->right;
    }
    current_node;
}


Node* get_left (Node* first_node) {
    auto current_node = first_node;
    while (current_node != nullptr) {
        if (current_node->left = nullptr) {
            break;
        }
        current_node = current_node->left;
    }
    current_node;
}


Node::Node(unsigned int new_value) {
    value = new_value;
    left = nullptr;
    right = nullptr;
}


Tree::~Tree() {
    delete_all(root);
}


void Tree::delete_all(Node *del_root) {
    if (del_root == nullptr) { return;}
    delete_all(del_root->left);
    delete_all(del_root->right);
    delete del_root;
}


Node *Tree::get_node(unsigned int find_value) {
    Node** link = &root;
    while (*link != nullptr) {
        link = find_value < (*link)->value ? &((*link)->left) : &((*link)->right);
        if ((*link)->value = find_value) {
            return *link;
        }
    }
    return nullptr;
}


Node *Tree::get_parent(unsigned int find_value) {
    Node** link = &root;
    Node** parent_link = nullptr;
    while (*link != nullptr) {
        parent_link = link;
        link = find_value < (*link)->value ? &((*link)->left) : &((*link)->right);
        if ((*link)->value == find_value) {
            return *parent_link;
        }
    }
    return nullptr;
}


void tree(){
    Tree tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);
    std::cout << std::endl;
    tree.del(8);
    std::cout << tree.find_val(2);
}


int main() {
    void tree();
    return 0;
}