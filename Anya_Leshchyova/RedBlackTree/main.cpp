#include <iostream>
using namespace std;

struct Node {  // узел
    int data;  // хранит ключ - число
    Node *parent;  // родитель
    Node *left;  // левый ребенок
    Node *right;  // правый ребенок
    int color;  // цвет красный (1) чёрный (0)
};

typedef Node *NodePtr;


class RedBlackTree {
private:
    NodePtr root; // корень
    NodePtr TNULL; // лист

    RedBlackTree(NodePtr node, NodePtr parent);

    void preOrderHelper(NodePtr node);  // выведет от корня до листьев
    void inOrderHelper(NodePtr node); //сначала все левые, потом все правые ( в порядке возрастания получится)
    void postOrderHelper(NodePtr node); // выведет от листа до корня


    NodePtr searchTreeHelper(NodePtr node, int key); // ищет заданный узел
    void deleteFix(NodePtr x); // балансировка после удаления ( свойство глубины )
    void rbTransplant(NodePtr u, NodePtr v); // доп. для удаления, спасает правого/левого ребенка удаляемого родителя
    void deleteNodeHelper(NodePtr node, int key);  //удаление узла
    void insertFix(NodePtr k); // балансировка после вставки ( свойство цвета )
    void printHelper(NodePtr root, string indent, bool last); // вывод
    void printSearch( NodePtr node);

public:
    RedBlackTree();

    void preOrder();
    void inOrder();
    void postOrder();

    NodePtr searchTree(int k) ;
    NodePtr minimum(NodePtr node); // нужно для одного случая удаления
    NodePtr maximum(NodePtr node);
    NodePtr successor(NodePtr x);  // преемник
    NodePtr predecessor(NodePtr x);  // предшественник

    void leftRotate(NodePtr x);  // левое вращение
    void rightRotate(NodePtr x);  // правое вращение
    void insert(int key);  // вставка узла
    NodePtr getRoot();  // отдаст корень
    void deleteNode(int data);  // удаление узла
    void printTree();
};


RedBlackTree:: RedBlackTree(){
    TNULL = new Node;
    TNULL->color = 0;
    TNULL->left = nullptr;
    TNULL->right = nullptr;
    root = TNULL;
}


RedBlackTree:: RedBlackTree(NodePtr node, NodePtr parent) {
    node->data = 0;
    node->parent = parent;
    node->left = nullptr;
    node->right = nullptr;
    node->color = 0;
}


void RedBlackTree::preOrderHelper(NodePtr node) {
    if (node != TNULL) {
        cout << node->data << " ";
        preOrderHelper(node->left);
        preOrderHelper(node->right);
    }
}


void RedBlackTree::inOrderHelper(NodePtr node) {
    if (node != TNULL) {
        inOrderHelper(node->left);
        cout << node->data << " ";
        inOrderHelper(node->right);
    }
}


void RedBlackTree::postOrderHelper(NodePtr node) {
    if (node != TNULL) {
        postOrderHelper(node->left);
        postOrderHelper(node->right);
        cout << node->data << " ";
    }
}



void RedBlackTree::printSearch(NodePtr node) {
    if (node == root) {
        cout << endl << "Element - > root = " << node->data << endl;
        return;
    }
    cout  << endl <<"Element = " << node-> data << endl;
    cout  <<"     Node"  << endl;
    cout  <<"      " << node-> parent->data << endl;
    cout  <<"    |    |    " <<  endl;
    cout  <<"    " << node-> parent->left->data <<"   ";
    cout  << node-> parent->right->data << endl;
}


NodePtr RedBlackTree:: searchTreeHelper(NodePtr node, int key) {
    if (node == TNULL || key == node->data) {
        if (key != node->data ){
            cout << "Node not found  " << key <<endl;
            return node;
        }
        printSearch(node);
        return node;
    }
    if (key < node->data) {
        return searchTreeHelper(node->left, key);
    }
    return searchTreeHelper(node->right, key);
}



void RedBlackTree:: deleteFix(NodePtr x) {
    NodePtr s;
    // пока х не станет корнем и цвет черным ( корень всегда черный)
    while (x != root && x->color == 0) {

        if (x == x->parent->left) {  // если Х это левый ребенок
            s = x->parent->right; // тогда s - правый ребенок  - брат

            //случай когда Брат Красный, тогда Брат --> черный, отец красный и левый поворот.
            if (s->color == 1) {
                s->color = 0;
                x->parent->color = 1;
                leftRotate(x->parent);
                s = x->parent->right;
            }

            //Брат черный ( после ифа/ был)

            //Случай: оба ребенка брата Черные ( племянники) -->
            // Брат красный, отец - черный
            if (s->left->color == 0 && s->right->color == 0) {
                s->color = 1;
                x = x->parent;
            } else {  //СЛУЧАИ:  ПРАВЫЙ/ ЛЕВЫЙ/ ОБА ПЛЕМЯННИКИ КРАСНЫЕ

                //
                // Правый племянник - черный ( значит Левый красный) -->
                // Левый племянник в черный, брат в красный, правый поворот
                if (s->right->color == 0) {
                    s->left->color = 0;
                    s->color = 1;
                    rightRotate(s);
                    s = x->parent->right;
                }

                // Случай
                // После поворота появится брат с Правым красным ребенком ( либо был/либо после ифа)
                // Брат в цвет отца, правый племянник и отец в черный и левый поворот
                s->color = x->parent->color;
                x->parent->color = 0;
                s->right->color = 0;
                leftRotate(x->parent);
                x = root;
            }

        } else {  // Если Х - правый ребенок
            // Все аналогично
            s = x->parent->left;
            if (s->color == 1) {
                s->color = 0;
                x->parent->color = 1;
                rightRotate(x->parent);
                s = x->parent->left;
            }
            if (s->right->color == 0 && s->left->color == 0) {
                s->color = 1;
                x = x->parent;
            } else {
                if (s->left->color == 0) {
                    s->right->color = 0;
                    s->color = 1;
                    leftRotate(s);
                    s = x->parent->left;
                }
                s->color = x->parent->color;
                x->parent->color = 0;
                s->left->color = 0;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = 0; // корень всегда чёрный
}


void RedBlackTree:: rbTransplant(NodePtr u, NodePtr v) {
    if (u->parent == nullptr) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}


void RedBlackTree::deleteNodeHelper(NodePtr node, int key) {
    NodePtr z = TNULL; // создает лист
    NodePtr x, y;  // два узла

    //Пока не дойдем до листа
    while (node != TNULL) {
        if (node->data == key) { // сохраняем удаляемый узел
            z = node;
        }
        if (node->data <= key) {
            node = node->right;
        } else {
            node = node->left;
        }
    }

    if (z == TNULL) {
        cout << "Key not found in the tree" << endl;
        return;
    }

    y = z;
    int y_original_color = y->color;
    //СЛУЧАЙ: Когда левый ребенок равен нулю
    //Ребенок встает на место удаляемого отца
    if (z->left == TNULL) {
        x = z->right;
        rbTransplant(z, z->right);

        //СЛУЧАЙ: Когда правый ребенок равен нулю
        //Ребенок встает на место удаляемого отца
    } else if (z->right == TNULL) {
        x = z->left;
        rbTransplant(z, z->left);

        //СЛУЧАЙ: Оба ребенка НЕ равны нулю
        // ищем самый левый элемент в правом поддереве, удаляем его и вставляем его на место удаляемого
    } else {
        y = minimum(z->right); // ищем самый левый элемент в правом поддереве
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            rbTransplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rbTransplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    //СЛУЧАЙ: Если нет детей - просто удаляем
    delete z;
    if (y_original_color == 0) { // если цвет удаляемого элемента - черный, проверяем свойство глубины
        deleteFix(x);
    }
}


void RedBlackTree:: insertFix(NodePtr k) {
    NodePtr u;

    //СЛУЧАЙ: Родитель был красный --> стало два красных подряд
    while (k->parent->color == 1) {

        //  СЛУЧАЙ 1: Если родитель нового узла Правый ребенок
        if (k->parent == k->parent->parent->right) {
            u = k->parent->parent->left;
            //Если он красный
            if (u->color == 1) {
                u->color = 0;
                k->parent->color = 0;
                k->parent->parent->color = 1;
                k = k->parent->parent;
            } else {  //Если он черный
                if (k == k->parent->left) {
                    k = k->parent;
                    rightRotate(k);
                }
                k->parent->color = 0;
                k->parent->parent->color = 1;
                leftRotate(k->parent->parent);
            }

            // СЛУЧАЙ 2: Если родитель нового узла Левый ребенок
        } else {
            u = k->parent->parent->right;

            if (u->color == 1) {
                u->color = 0;
                k->parent->color = 0;
                k->parent->parent->color = 1;
                k = k->parent->parent;
            } else {
                if (k == k->parent->right) {
                    k = k->parent;
                    leftRotate(k);
                }
                k->parent->color = 0;
                k->parent->parent->color = 1;
                rightRotate(k->parent->parent);
            }
        }

        //СЛУЧАЙ 3: Дерева не было
        if (k == root) {
            break;
        }
    }
    root->color = 0;  // Корень всегда черный
}


void RedBlackTree:: printHelper(NodePtr root, string indent, bool last) {
    if (root != TNULL) {
        cout << indent;
        if (last) {
            cout << "R----";
            indent += "   ";
        } else {
            cout << "L----";
            indent += "|  ";
        }

        string sColor = root->color ? "RED" : "BLACK";
        cout << root->data << "(" << sColor << ")" << endl;
        printHelper(root->left, indent, false);
        printHelper(root->right, indent, true);
    }
}


void RedBlackTree:: preOrder() {
    preOrderHelper(this->root);
}

void RedBlackTree:: inOrder() {
    inOrderHelper(this->root);
}

void RedBlackTree:: postOrder() {
    postOrderHelper(this->root);
}

NodePtr RedBlackTree:: searchTree(int k) {
    return searchTreeHelper(this->root, k);
}

NodePtr RedBlackTree:: minimum(NodePtr node) { // помогает при удалении, отдает последний левый узел
    while (node->left != TNULL) {
        node = node->left;
    }

    return node;
}

NodePtr RedBlackTree:: maximum(NodePtr node) {
    while (node->right != TNULL) {
        node = node->right;
    }
    return node;
}

NodePtr RedBlackTree:: successor(NodePtr x) {
    if (x->right != TNULL) {
        return minimum(x->right);
    }

    NodePtr y = x->parent;
    while (y != TNULL && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}

NodePtr RedBlackTree:: predecessor(NodePtr x) {
    if (x->left != TNULL) {
        return maximum(x->left);
    }

    NodePtr y = x->parent;
    while (y != TNULL && x == y->left) {
        x = y;
        y = y->parent;
    }

    return y;
}

void RedBlackTree:: leftRotate(NodePtr x) { // левое вращение
    NodePtr y = x->right; // равен сыну
    x->right = y->left;  // брат равен левому ребенку сына
    if (y->left != TNULL) { // если левого ребенка сына нет
        y->left->parent = x; //х занимает место сына
    }
    y->parent = x->parent; // дед становится на место отца
    if (x->parent == nullptr) { // если деда нет
        this->root = y; // сын ставится в корень
    } else if (x == x->parent->left) { // если дед есть -- если х = дяди
        x->parent->left = y;  // дядя становится У (равен сыну)
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void RedBlackTree:: rightRotate(NodePtr x) {  // правое вращение
    NodePtr y = x->left;
    x->left = y->right;
    if (y->right != TNULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        this->root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}


void RedBlackTree:: insert(int key) {
    NodePtr node = new Node;  // создаём новый узел, у него всё ноль, цвет красный
    node->parent = nullptr;
    node->data = key;
    node->left = TNULL;
    node->right = TNULL;
    node->color = 1;

    NodePtr y = nullptr;
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

    if (node->parent == nullptr) { // если  дерева не было, то корень окрашеваем обязательно в черный
        node->color = 0;
        return;
    }

    if (node->parent->parent == nullptr) {
        return;
    }

    insertFix(node);  // проверяем балансировку дерева после вставки
}


NodePtr RedBlackTree:: getRoot() {
    return this->root;
}

void RedBlackTree:: deleteNode(int data) {  // удаление узла, публичное
    deleteNodeHelper(this->root, data);
}

void RedBlackTree:: printTree() {
    if (root) {
        printHelper(this->root, "", true);
    }
}



int main() {
    RedBlackTree bst;
    NodePtr  search;
    bst.insert(55);
    bst.insert(40);
    bst.insert(65);
    bst.insert(60);
    bst.insert(75);
    bst.insert(56);
    bst.insert(5);
    bst.insert(555);
    bst.insert(70);
    bst.insert(57);
    bst.insert(61);

    bst.printTree();

    cout << endl << "After deleting" << endl;
    bst.deleteNode(55);
    bst.printTree();


    cout << endl << "After search" << endl;
    search = bst.searchTree(56);

    cout << endl;
    bst.inOrder();
    cout << endl;

    return 0;
}

