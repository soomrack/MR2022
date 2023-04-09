#include <iostream>
#include <stack>



struct Node {
    int data;  // хранит ключ - число
    Node *left;
    Node *right;

};
typedef Node* NodePtr;
typedef NodePtr* NodePtrPtr;


class Tree{
public:
    Tree();
    bool search(int k) ;
    void del(int data);
    void print();
    void insert(int key);

private:
    NodePtr root;
    NodePtr TNULL;
    NodePtr search(NodePtr node, int key);
    void print(NodePtr root, std::string indent, bool last);
    void del(NodePtr node, int key);
    NodePtr min(NodePtr node);  // node =! TNULL
    NodePtr parent_min(NodePtr  node);  // node =! TNULL
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
        root_help = (node->data <  root_help->data) ?  root_help->left :  root_help->right;
    }

    if (last_leaf == nullptr){
        root = node;
        return;
    }
    (node->data <  last_leaf->data) ? last_leaf->left = node:  last_leaf->right = node;
    return;
}




NodePtr Tree:: min(NodePtr node) {
    while (node->left != TNULL)
        node = node->left;
    return node;
}


NodePtr Tree:: parent_min(NodePtr  node) {
    do  node = node->left;
    while (node->left->left != TNULL);
    return node;
}



void Tree:: del(NodePtr node, int key) {
    NodePtr parent_node_to_del = TNULL;
    NodePtr node_to_del = TNULL;
    NodePtrPtr buffer;
    do {
        if (node->right->data == key || node->left->data == key) {
            parent_node_to_del = node;
        }
        if (node->data == key ) {
            node_to_del = node;
        }
        node = (node->data <= key) ? node->right: node->left;

    } while (node != TNULL);

    NodePtrPtr parent_node_to_del_ptr{&(parent_node_to_del)};
    NodePtrPtr node_to_del_ptr{&node_to_del};
    if ((*node_to_del_ptr)->right == TNULL){
        ((*parent_node_to_del_ptr)->left == *node_to_del_ptr) ? (*parent_node_to_del_ptr)->left = (*node_to_del_ptr)->left:
                (*parent_node_to_del_ptr)->right = (*node_to_del_ptr)->left;

        return;
    }
    if ((*node_to_del_ptr)->left == TNULL){
        ((*parent_node_to_del_ptr)->left == *node_to_del_ptr) ? (*parent_node_to_del_ptr)->left = (*node_to_del_ptr)->right:
                (*parent_node_to_del_ptr)->right = (*node_to_del_ptr)->right;
        return;
    }

    if ((*node_to_del_ptr)->right->left == TNULL){  // ОСОБЫЙ СЛУЧАЙ
        //      A
        //    /    \
        //   E       B
        //         /   \
        //      TNULL    C
        buffer = node_to_del_ptr;  // = A
        ((*parent_node_to_del_ptr)->left == *node_to_del_ptr) ? (*parent_node_to_del_ptr)->left = (*node_to_del_ptr)->right :
                (*parent_node_to_del_ptr)->right = (*node_to_del_ptr)->right; // A=B
        ((*buffer)->right->left) = ((*buffer)->left); // TNULL = Е
        return;
    }
    //      A
    //    /    \
    //   E       B
    //         /   \
    //        D     C
    //          \
    //            N

    NodePtr rrr= min(node_to_del->right);
    NodePtrPtr  minimum = {&rrr};
    buffer = &((*minimum)->right); // = N
    ((*parent_node_to_del_ptr)->left == *node_to_del_ptr) ? (*parent_node_to_del_ptr)->left = parent_min( node_to_del ->right)->left:
            (*parent_node_to_del_ptr)->right =  parent_min( node_to_del ->right)->left; // А = D
    parent_min( node_to_del ->right)->left = (*buffer); // D=N
    (*minimum)->left =(*node_to_del_ptr)->left; // E становится ребенком D ( который стал А)
    (*minimum)->right =(*node_to_del_ptr)->right; // B становится ребенком D ( который стал А)
    delete node_to_del;
}

NodePtr Tree:: search(NodePtr node, int key) {
    while (node != TNULL and key != node->data)
        node = (node->data <= key) ? node->right: node->left;
    return node;
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
bool Tree:: search(int k) {
    NodePtr buffer =search(this->root, k);
    return (buffer != TNULL);
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
    bst.insert(41);
    bst.insert(555);
    bst.insert(42);
    bst.insert(57);
    bst.insert(5);
    bst.insert(1);
    bst.insert(69);
    bst.insert(90);
    bst.insert(91);
    bst.insert(68);
    bst.insert(85);
    bst.insert(86);
    bst.insert(7);
    bst.insert(6);






    bst.print();

    std::cout << "\n"
              << "After deleting" << "\n";
    bst.del(555);


    bst.print();

    a = bst.search(960);
    std::cout << "\n"
              << a << "\n";


    return 0;
}
