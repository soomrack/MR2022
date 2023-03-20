#include <iostream>


struct Node {
    int data;  // хранит ключ - число
    // Node *parent;
    Node *left;
    Node *right;

};
typedef Node *NodePtr;


class Tree{
public:
    Tree();
    int search(int k) ;
    void del(int data);
    void print();
    void insert(int key);

private:
    NodePtr root;
    NodePtr TNULL;
    NodePtr search(NodePtr node, int key);
    void print(NodePtr root, std::string indent, bool last);
    void del(NodePtr node, int key);
    void search(NodePtr node);
    NodePtr min(NodePtr node);
};


Tree:: Tree(){
    TNULL = new Node;
    TNULL->left = nullptr;
    TNULL->right = nullptr;
    root = TNULL;
}



void Tree:: insert(int key) {
    NodePtr node = new Node;
    node->data = key;
    node->left = TNULL;
    node->right = TNULL;
    NodePtr last_leaf = nullptr;
    NodePtr root_help = this->root;


    while (root_help != TNULL) {
        last_leaf = root_help;
        (node->data <  root_help->data) ?  root_help = root_help->left : root_help = root_help->right;
    }


    if (last_leaf == nullptr) {
        root = node;
    } else if (node->data <  last_leaf->data) {
        last_leaf->left = node;
    } else {
        last_leaf->right = node;
    }
    return;

}


void Tree:: search(NodePtr node){

    if ( node == root) {
        std:: cout << "Element is root = "<< node->data<< "\n";
        return;
    }

    std:: cout << "Element  = "<< node->data<< "\n";

}
NodePtr Tree:: min(NodePtr node) {
    while (node->left != TNULL) {
        node = node->left;
    }
    return node;
}


void Tree:: del(NodePtr node, int key) {
    NodePtr node_del = TNULL;
    while (node != TNULL) {
        if (node->data == key) {
            node_del = node;
        }
        (node->data <= key) ? node = node->right: node = node->left;

    }
    if (node_del == TNULL) {
        return;
    }
    NodePtr an1;
    if (node_del->right == TNULL){
        node_del->data = node_del->left->data;
        delete node_del->left;
        node_del->left = TNULL;

    } else if (node_del->left == TNULL) {
        node_del->data = node_del->right->data;
        delete node_del->right;
        node_del->right = TNULL;

    } else {
        an1 = min(node_del->right);
        node_del->data = an1->data;
        if (an1->right == TNULL){
            delete an1;
            an1 = TNULL;
            return;
        }
        an1->data = an1->right->data;
        delete an1->right;
        an1->right = TNULL;
    }

}


NodePtr Tree:: search(NodePtr node, int key) {
    if (node == TNULL || key == node->data) {
        search(node);
        return node;
    }
    if (key < node->data) {
        return search(node->left, key);
    }
    return search(node->right, key);
}


void Tree::print(NodePtr root, std::string indent, bool last) {
    if (root != TNULL) {
        std::cout << indent;
        if (last) {
            std::cout << "R----";
            indent += "   ";
        } else {
            std::cout << "L----";
            indent += "|  ";
        }
        std::cout << root->data  << "\n";
        print(root->left, indent, false);
        print(root->right, indent, true);
    }
}
int Tree:: search(int k) {
    NodePtr help =search(this->root, k);
    return help ->data;
}

void  Tree:: del(int data) {
    del(this->root, data);
}

void Tree:: print() {
    if (root) {
        print(this->root, "", true);
    }
}

int main () {

    Tree bst;
    int a;
    bst.insert(55);
    bst.insert(40);
    bst.insert(65);
    bst.insert(60);
    bst.insert(75);
    bst.insert(56);
    bst.insert(5);
    bst.insert(555);



    bst.print();

    std::cout << "\n"
              << "After deleting" << "\n";
    bst.del(40);
    bst.print();

    a = bst.search(75);
    std::cout << "\n"
              << a << "\n";


    return 0;
}
