#ifndef tree_h
#define tree_h
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
    NodePtrPtr min(NodePtrPtr node);  // node =! TNULL
    NodePtrPtr parent_min(NodePtrPtr  node);  // node =! TNULL
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
    (node->data <  last_leaf->data) ? last_leaf->left = node :  last_leaf->right = node;
    return;
}




NodePtrPtr Tree:: min(NodePtrPtr node) {
    while ((*node)->left != TNULL)
        node = &((*node)->left);
    return node;
}


NodePtrPtr Tree:: parent_min(NodePtrPtr   node) {
    while ((*node)->left->left != TNULL)
        node = &((*node)->left);
    return node;
}



void Tree:: del( int key) {
    NodePtrPtr node_to_del_ptr = &(this->root);
    while ((*node_to_del_ptr) != TNULL){
        if ((*node_to_del_ptr)->data == key) break;
        node_to_del_ptr = ((*node_to_del_ptr)->data > key) ? &((*node_to_del_ptr)->left) : &((*node_to_del_ptr)->right);
    }

    if ((*node_to_del_ptr) == TNULL) return;

    if ((*node_to_del_ptr)->right == TNULL) {
        *node_to_del_ptr = (*node_to_del_ptr)->left;
        return;
    }
    if ((*node_to_del_ptr)->left == TNULL) {
        *node_to_del_ptr = (*node_to_del_ptr)->right;
        return;
    }
    if ((*node_to_del_ptr)->right->left == TNULL){  //ОСОБЫЙ СЛУЧАЙ
        //          | ->A
        //         N1
        //    E<-/    \->B
        //     N2      N3
        //         R<-/   \
        //         TNULL    N4
        (*node_to_del_ptr)->right->left = (*node_to_del_ptr)->left; // R = E
        (*node_to_del_ptr) = (*node_to_del_ptr)->right; //A = B
        return;
    }

    NodePtrPtr minimum = (min(&((*node_to_del_ptr)->right)));
    //          | ->A                                             A = R
    //         N1                                                 D = E
    //    E<-/    \->B                                            T = B
    //     N2      N3                                             R = T
    //         R<-/   \
    //          MIN    N4
    //      D <-/ \->T
    //              N6
    const NodePtr buffer = *node_to_del_ptr; // = A
    const NodePtr buffer_min = (*minimum)->right; // = T
    const NodePtrPtr parent_min_ptr = parent_min(&((*node_to_del_ptr)->right)); // = B
    (*node_to_del_ptr) = *minimum; // A = R
    (*minimum)->left = (buffer)->left; // D = E
    (*minimum)->right = (buffer)->right; // T = B
    (*parent_min_ptr)->left = buffer_min ; //R = T

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



void Tree:: print() {
    if (root) {
        print(this->root, "", true);
    }
}

#endif /* tree_h */
