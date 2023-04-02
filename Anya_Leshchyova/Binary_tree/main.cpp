#include <iostream>
#include <stack>



struct Node {
    int data;  // хранит ключ - число
   // Node *parent;
    Node *left;
    Node *right;

};
typedef Node *NodePtr;

std::stack <int> steck;
std::stack <NodePtr> ST_left;
std::stack <NodePtr> ST_right;
std::stack <NodePtr> Pst;

class Tree{
public:
    Tree();
 //   Tree(double data = double(), Node *left = nullptr, Node *right = nullptr);
    int search(int k) ;
    void del(int data);
    void print();
    void insert(int key);

private:
    int height;
    NodePtr root;
    NodePtr TNULL;
    NodePtr search(NodePtr node, int key);
    void print(NodePtr root, std::string indent, bool last);
    void del(NodePtr node, int key);
    NodePtr min(NodePtr node);
    void transplant (NodePtr , NodePtr, bool);
};


Tree:: Tree(){
    height = 0;
    TNULL = new Node;
    TNULL->left = nullptr;
    TNULL->right = nullptr;
    root = TNULL;
}
/*
Tree:: Tree(double data,Node *left , Node *right ){
    TNULL->data = data;
    TNULL-> right = right;
    TNULL->left = left;
}

*/

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

    if (last_leaf == nullptr) { // можно написать в начале
        root = node;
    } else if (node->data <  last_leaf->data) {
        last_leaf->left = node;
    } else {
        last_leaf->right = node;
    }
    return;

}



NodePtr Tree:: min(NodePtr node) {
    while (node->left != TNULL) {
        node = node->left;
    }
    return node;
}

void Tree::transplant(NodePtr Ptr_node, NodePtr Ptr_child, bool left_child_null) {
    /*
    if (Ptr_node == nullptr) { // Если ссылки на удаляемый узел нет - то он корень
        root = Ptr_child;
        return;
    }
     */
    std::cout << "Ptr_node = " << Ptr_node << "    "<<Ptr_node ->data <<"\n";
    std::cout << "Ptr_child = " << Ptr_child << "    "<<Ptr_child ->data <<"\n";
    std::cout << "ST_right.top() = " << ST_right.top() << "    "<<ST_right.top() ->data <<"\n";
    std::cout << "ST_left.top = " << ST_left.top() << "    "<<ST_left.top() ->data <<"\n";
    std::cout << "=============== " << Pst.top() << "    "<<Pst.top() ->data <<"\n";
    std::cout <<  "\n";
    std::cout <<  "\n";
    if (Ptr_node == ST_right.top() and left_child_null == true) {
        std::cout <<  "DAAAAAAAAAAAAA\n";

        if (Pst.top() == root and Pst.top()->left == Ptr_node) {
            Pst.top()->left = ST_right.top()->right;
            Ptr_node->right = TNULL;
            std::cout << " shag 1 " << "\n";
            return;
        }
            Pst.top()->right = ST_right.top()->right;
            Ptr_node->right = TNULL;
            std::cout << " shag 3 " << "\n";
        }
        if (Ptr_node == ST_right.top() and left_child_null == false) {
            if (Pst.top() == root and Pst.top()->right == Ptr_node) {
                Pst.top()->right = ST_right.top()->left;
                Ptr_node->left = TNULL;
                std::cout << " shag 5 " << "\n";
                return;
            }

            Pst.top()->left = ST_right.top()->left;
            Ptr_node->left = TNULL;
            std::cout << " shag 4 " << "\n";
        }
        std::cout << "ST_right.top() = " << ST_right.top() << "    " << ST_right.top()->data << "\n";
        std::cout << "ST_left.top = " << ST_left.top() << "    " << ST_left.top()->data << "\n";
        std::cout << "Ptr_node = " << Ptr_node << "    " << Ptr_node->data << "\n";
        std::cout << "Ptr_child = " << Ptr_child << "    " << Ptr_child->data << "\n";






        //  if (Ptr_node == )


}
void Tree:: del(NodePtr node, int key) {
    NodePtr node_to_del = TNULL;

    int k = 1;
    while (node != TNULL) {

        if (node->data == key) {
            node_to_del = node;
            k = 0;
        }
        if(k == 1){
            steck.push(node->data);
            Pst.push(node);
        }
        if (node->data <= key){
            ST_right.push(node);
            node = node->right;
        } else {
            ST_left.push(node);
            node = node->left;
        }
        //(node->data <= key) ? node = node->right: node = node->left;

    }
    if (node_to_del == TNULL) {
        return;
    }

    if (node_to_del->left == TNULL and node_to_del->right == TNULL){
        Pst.top()->left = TNULL;
        Pst.top()->right = TNULL;
        delete node_to_del; //ЕСЛИ ЛОМАЕТСЯ ПРОВЕРЬ ЭТО
        return;
    }

    NodePtr buffer;
    if (node_to_del->left == TNULL){
        buffer = node_to_del->right;
        transplant(node_to_del,buffer, true);
         delete node_to_del; //ЕСЛИ ЛОМАЕТСЯ ПРОВЕРЬ ЭТО
         return;
    }
    if (node_to_del->right == TNULL){
        buffer = node_to_del->left;
        transplant(node_to_del,buffer,false);
        delete node_to_del; //ЕСЛИ ЛОМАЕТСЯ ПРОВЕРЬ ЭТО
        return;
    }

    NodePtr minimum = min(node_to_del->right);
    ST_left.pop();
    //NodePtr minimum_child_right = minimum->right; // 91
   // buffer = ST_right.top();
    std::cout << "buffer = " << ST_left.top() << "    "<<buffer ->data <<"\n";
if (root->data < node_to_del->data){
    ST_right.push(ST_left.top()->left);
    if (minimum->right != TNULL)
    ST_left.top()->left = minimum->right;
    node_to_del->data = minimum->data;
} else{ //ЛОМАЕТСЯ
    ST_right.push(ST_left.top()->left);
    if (minimum->right != TNULL)
        ST_left.top()->left = minimum->right;
    node_to_del->left=minimum->left;
    node_to_del->data = minimum->data;

}








   // ST_right.top()->data =minimum->data;

   // minimum->right=ST_right.top()->right;
   // Pst.top()->right =ST_left.top()->left;
   // ST_left.top()->left ->right = ST_right.top()->right;
   // ST_left.top()->left ->left = ST_right.top()->left;


    std::cout << "ST_right.top() = " << ST_right.top() << "    "<<ST_right.top() ->data <<"\n";
    std::cout << "ST_left.top = " << ST_left.top() << "    "<<ST_left.top() ->data <<"\n";
    std::cout << "=============== " << Pst.top() << "    "<<Pst.top() ->data <<"\n";
    std::cout << "minimum=  " << minimum << "    "<<minimum ->data <<"\n";


    /*
    if (node_to_del->right == TNULL){
        node_to_del->data = node_to_del->left->data;
        delete node_to_del->left; // случай когда у левого ребенка есть левый ребенок и ссылка на него пропадет.
        node_to_del->left = TNULL;

    } else if (node_to_del->left == TNULL) {
        node_to_del->data = node_to_del->right->data; // можно работать с указателем при удалении узла
        delete node_to_del->right;
        node_to_del->right = TNULL;

    } else {
        an1 = min(node_to_del->right);
        node_to_del->data = an1->data;
        if (an1->right == TNULL){
            delete an1;
            an1 = TNULL;
            return;
        }
        an1->data = an1->right->data;
        delete an1->right;
        an1->right = TNULL;
    }
*/
    std::cout << "buffer = " << ST_left.top() << "    "<<buffer ->data <<"\n";
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
    bst.insert(41);
    bst.insert(555);
    bst.insert(42);
    bst.insert(57);
    bst.insert(5);
    bst.insert(1);
    bst.insert(69);
    bst.insert(90);
    bst.insert(91);




    bst.print();

    std::cout << "\n"
         << "After deleting" << "\n";
         bst.del(65);
    bst.print();
/*
    a = bst.search(75);
    std::cout << "\n"
              << a << "\n";
*/

    return 0;
}

