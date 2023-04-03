#include <iostream>




struct Node {
    int data;  // хранит ключ - число
    Node *left;
    Node *right;

};
typedef Node *NodePtr;
typedef NodePtr *NodePtrPtr;


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
    NodePtrPtr max();
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

    if (last_leaf == nullptr){
        root = node;
        return;
    }

    (node->data <  last_leaf->data) ? last_leaf->left = node:  last_leaf->right = node;


    return;
}


NodePtrPtr Tree:: max(){
    NodePtrPtr buffer;
    NodePtr node = root;
    while (node ->right != TNULL){
        node = node->right;
        buffer ={&node};
    }
    return buffer;
}



NodePtr Tree:: min(NodePtr node) {
    while (node->left != TNULL) {
        node = node->left;
    }
    return node;
}


NodePtr Tree:: parent_min(NodePtr  node) {
    if (node->right->left == TNULL) return node;
    node = node->right;
    int count = 0;
    NodePtr buffer = node;
    while (node != TNULL) {
        node = node->left;
        count++;
    }
   for (int number = 0; number < count-2; number++){
       buffer = buffer->left;
   }

    return buffer;
}



void Tree:: del(NodePtr node, int key) {
    NodePtr parent_node_to_del = TNULL;
    NodePtr node_to_del = TNULL;
    do {
        if (node->right->data == key || node->left->data == key) {
            parent_node_to_del = node;

        }
        if (node->data == key ) {
            node_to_del = node;
        }

        if (node->data <= key) {
            node = node->right;
        } else {
            node = node->left;


        }


    } while (node != TNULL);

    NodePtrPtr parent_node_to_del_ptr{&(parent_node_to_del)};
    NodePtrPtr node_to_del_ptr{&node_to_del};


    if (node_to_del->left == TNULL and node_to_del->right == TNULL){
        std:: cout << "                     Not children\n";
        (parent_node_to_del->left->data == node_to_del->data) ?
                (*parent_node_to_del_ptr)->left = TNULL:
                (*parent_node_to_del_ptr)->right = TNULL;
        return;
    }



    if (node_to_del->left == TNULL){
        std:: cout << "                     Not left child\n";
        NodePtrPtr child_node_to_del_ptr{&(node_to_del->right)};

        if ((*parent_node_to_del_ptr)->left->data == (*node_to_del_ptr)->data) {
            std:: cout <<"-----------------------I am left child\n";
            (*parent_node_to_del_ptr)->left = *child_node_to_del_ptr;
            return;
        } else {
            std:: cout <<"-----------------------I am right child\n";
            (*parent_node_to_del_ptr)->right = *child_node_to_del_ptr;
            return;
        }
    }



    if (node_to_del->right == TNULL){
        std:: cout << "                     Not right child\n";
        NodePtrPtr child_node_to_del_ptr{&(node_to_del->left)};
        if ((*parent_node_to_del_ptr)->left->data == (*node_to_del_ptr)->data) {
            std:: cout <<"-----------------------I am left child\n";
            (*parent_node_to_del_ptr)->left = *child_node_to_del_ptr;
            return;
        } else {
            std:: cout <<"-----------------------I am right child\n";
            (*parent_node_to_del_ptr)->right = *child_node_to_del_ptr;
            return;
        }
    }
    NodePtr minimum = min(node_to_del->right);
    NodePtr parent_minimum = parent_min(node_to_del);
    NodePtrPtr minimum_ptr = {&minimum};
    NodePtrPtr parent_minimum_ptr = {&parent_minimum};


    NodePtr buffer = minimum->right;


if (node_to_del == root) {
    NodePtrPtr root_ptr = {&root};
    // (*parent_minimum_ptr)->left =TNULL;
    (*parent_minimum_ptr)->left = buffer;
    (*minimum_ptr)->left = (*node_to_del_ptr)->left;
    (*minimum_ptr)->right = (*node_to_del_ptr)->right;
    *root_ptr = *minimum_ptr;
    return;
}

    NodePtrPtr parent_minimum_right_ptr = {&parent_minimum->right};
    (*minimum_ptr)->left = (*node_to_del_ptr)->left;
    (*minimum_ptr)->right = (*node_to_del_ptr)->right;
    if((*parent_node_to_del_ptr)->left->data ==  (*node_to_del_ptr)->data ){
        std:: cout <<"-----------------------I am left child\n";
        (*parent_node_to_del_ptr)->left = *parent_minimum_right_ptr;
        (*parent_minimum_right_ptr)->right = TNULL; ;
    } else {
        std:: cout <<"-----------------------I am right child\n";
         (*parent_node_to_del_ptr)->right = (*parent_minimum_ptr)->left;
        (*parent_minimum_ptr)->left = TNULL;
    }

    if (buffer != TNULL) (*parent_minimum_right_ptr)->right = buffer;

}

NodePtr Tree:: search(NodePtr node, int key) {

    if (node == TNULL || key == node->data) {
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
    bst.insert(6);
    bst.insert(6);






    bst.print();

    std::cout << "\n"
         << "After deleting" << "\n";
         bst.del(40);


    bst.print();

    a = bst.search(90);
    std::cout << "\n"
              << a << "\n";


    return 0;
}


