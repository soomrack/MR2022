#include <iostream>

struct Node {
    int data;  // хранит ключ - число
    Node *parent;  // родитель
    Node *left;  // левый ребенок
    Node *right;  // правый ребенок

};
typedef Node *NodePtr;

class Tree{
private:
    NodePtr root; // корень
    NodePtr TNULL; // лист
    NodePtr searchTreeHelper(NodePtr node, int key);
    void printHelper(NodePtr root, std::string indent, bool last);
    void deleteNodeHelper(NodePtr node, int key);
    void rbTransplant(NodePtr u, NodePtr v);
    void searchTreeHelperPrint(NodePtr node);

public:
    Tree();
    Tree(NodePtr node, NodePtr parent);
    NodePtr searchTree(int k) ;
    void deleteNode(int data);
    void printTree();
    void insert(int key);
    NodePtr minimum(NodePtr node);

};


Tree:: Tree(){
    TNULL = new Node;
    TNULL->left = nullptr;
    TNULL->right = nullptr;
    root = TNULL;
}

Tree:: Tree(NodePtr node, NodePtr parent){
    node->data = 0;
    node->parent = parent;
    node->left = nullptr;
    node->right = nullptr;
}

// Вставка узла
void Tree:: insert(int key) {
    NodePtr node = new Node;  // создаём новый узел, у него всё ноль, цвет красный
    node->parent = nullptr;
    node->data = key;
    node->left = TNULL;
    node->right = TNULL;
    NodePtr y = nullptr;  // пусть  у - лист
    NodePtr x = this->root;  // пусть х - корень
    while (x != TNULL) {  // пока х не доберется до листа
        y = x;  // сохранит последний не нулевой лист
        if (node->data <  x->data) {  // если узел дерева меньше нового узла с Х
            x = x->left;  // кладем х влево
        } else {
            x = x->right; // иначе кладем вправо
        }
    }
    node->parent = y;   // так как У это последний ненулевой лист, то делаем его родителем для нового узла
    if (y == nullptr) {
        root = node;   // если дерева не существовало - то Х становится корнем
    } else if (node->data <  y->data) {   // дерево было, сравниваем если узел больше У ( родителя)
        y->left = node;  // кладем влево
    } else {
        y->right = node;
    }
    return;

}


void Tree:: rbTransplant(NodePtr u, NodePtr v) {  // спасает ребенка (правого/ левого) удаляемого родителя
    if (u->parent == nullptr) {
        root = v;
    } else if (u == u->parent->left) { // если у U есть родитель и  U это его левый ребенок
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}


void Tree:: searchTreeHelperPrint(NodePtr node){

    if ( node == root) {
        std:: cout << "Element is root = "<< node->data<< "\n";
        return;
    }
    if (node != TNULL){
        std:: cout << "Element  = "<< node->data<< "\n";
        std:: cout << "     "<< node->parent->data<< "\n";
        std:: cout << "   |    |   "<<  "\n";
        std:: cout<<"  " << node->parent->left->data<< "    " << node->parent->right->data << "\n";
        return;
    }
    std:: cout << "Element  = "<< node->data<< "\n";
}


NodePtr Tree:: minimum(NodePtr node) { // помогает при удалении, отдает последний левый узел
    while (node->left != TNULL) {
        node = node->left;
    }

    return node;
}


void Tree:: deleteNodeHelper(NodePtr node, int key) {  //удаление узла
    // Z - будет потом тем узлом, который нужно будет удалить
    NodePtr z = TNULL; // создаем лист

    NodePtr x, y; // и два узла

    while (node != TNULL) { // пока нужный узел не дойдет до конца дерева
        if (node->data == key) { // если это то число, которое нужно удалить
            z = node;  // сохраняем узел
        }
        if (node->data <= key) {  // если число больше либо  рравен корневого узла идем вправо
            node = node->right;
        } else {
            node = node->left;
        }
    }

    if (z == TNULL) { // если узел не был равен  -- то такого числа в дереве нет
        std::cout << "Key not found in the tree" << "\n";
        return;
    }
    y = z;
    if (z->left == TNULL) { // если узел не имеет левого ребенка
        x = z->right;  //сохряняем правого ребенка этого узла
        rbTransplant(z, z->right); //
    } else if (z->right == TNULL) { // аналогично наоборот
        x = z->left;
        rbTransplant(z, z->left);
    } else {  // если есть и правый и левый ребенок
        y = minimum(z->right); // находим минимум в правом поддереве (В левой ветке )

        x = y->right;
        if (y->parent == z) {  // если родитель минимума равен этому узлу
            x->parent = y;
        } else {
            rbTransplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rbTransplant(z, y);
        y->left = z->left;
        y->left->parent = y;
    }
}


NodePtr Tree:: searchTreeHelper(NodePtr node, int key) {
    if (node == TNULL || key == node->data) {
        searchTreeHelperPrint(node);
        return node;
    }

    if (key < node->data) {
        return searchTreeHelper(node->left, key);
    }
    return searchTreeHelper(node->right, key);
}


void Tree::printHelper(NodePtr root, std::string indent, bool last) {
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
        printHelper(root->left, indent, false);
        printHelper(root->right, indent, true);
    }
}


NodePtr Tree:: searchTree(int k) {
    return searchTreeHelper(this->root, k);
}

void  Tree:: deleteNode(int data) {  // удаление узла, публичное
    deleteNodeHelper(this->root, data);
}


void Tree:: printTree() {
    if (root) {
        printHelper(this->root, "", true);
    }
}


int main () {

    Tree bst;
    NodePtr  a;
    bst.insert(55);
    bst.insert(40);
    bst.insert(65);
    bst.insert(60);
    bst.insert(75);
    bst.insert(56);
    bst.insert(5);
    bst.insert(555);


    bst.printTree();

    std::cout << "\n"
         << "After deleting" << "\n";bst.deleteNode(55);
    bst.printTree();

    a = bst.searchTree(65);


    return 0;
}
