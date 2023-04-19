#include <iostream>
#include <stack>

struct Node {
    int data;
    int key;
    int color;
    Node *left;
    Node *right;
};

typedef Node *NodePtr;
typedef NodePtr *NodePtrPtr;

class Exception {
    int kod_mistake;
public:
    Exception(int kod);
};


Exception::Exception(int kod) {
    kod_mistake = kod;
}

Exception stack_full = 1;
Exception stack_empty = 2;


class Stack {
    NodePtrPtr *stack;
    int sp;  //stack point
    int capacity; // размер стека
public:
    Stack();
    ~Stack();
    void push(NodePtrPtr);
    void pop();
    NodePtrPtr peek();  // посмотреть самый верхний элемент ( без извлечения )
    inline bool isEmpty();
    inline bool isFull();
    void print();
    void clear();
};

Stack::Stack(){
    capacity = 10;
    stack = new NodePtrPtr[capacity];
    sp = -1;
}

Stack::~Stack() {
    delete[] stack;
}


void Stack::push(NodePtrPtr item) {
    if (isFull()) throw stack_full;
    stack[++sp] = item;
}


void Stack::pop() {
    if (isEmpty()) throw stack_empty;
    sp--;
}


NodePtrPtr Stack::peek() {
    if (!isEmpty()) {
        return stack[sp];
    }
    else {
        throw stack_empty;
    }
}


inline bool Stack::isEmpty() {
    return sp == -1;
}


inline bool Stack::isFull() {
    return sp == capacity - 1;
}


void Stack::print() {
    for (int number = sp; number >= 0; number--){
        std::cout << (*(stack[number]))->data<< " ";
    }
    std::cout <<  " \n";
}


void Stack::clear(){
    while (isEmpty() != true){
        pop();
    }
}


class RedBlackTree{
public:
    RedBlackTree();
    bool search(int data) ;
    void del(int data);
    void print();
    void insert(int data);

private:
    NodePtr root;
    NodePtr TNULL;
    int hash ();
    int count;  // для hash функции
    Stack stack_parent_ptr;
    NodePtr search(NodePtr node, int data);
    void print(NodePtr root, std::string indent, bool last);
    void del(NodePtr node, int data);
    void insert_fix (NodePtrPtr parent_node_ptr,NodePtrPtr node_ptr  ) ;
    void right_rotate (NodePtrPtr node_ptr, NodePtrPtr parent_node_ptr, NodePtrPtr parent_parent_node_ptr);
    void left_rotate (NodePtrPtr node_ptr, NodePtrPtr parent_node_ptr, NodePtrPtr parent_parent_node_ptr);
    NodePtrPtr min(NodePtrPtr node);  // node =! TNULL
    NodePtrPtr parent_min(NodePtrPtr  node);  // node =! TNULL
    void del_fix(NodePtr node_to_del, int data);
};


RedBlackTree:: RedBlackTree(){
    TNULL = new Node;
    TNULL->left = nullptr;
    TNULL->right = nullptr;
    root = TNULL;
    TNULL->color = 0;
    TNULL->key = 0;
    count = -1;
}


int RedBlackTree:: hash (){
    count ++;
    return count + 1;
}


void RedBlackTree::insert_fix(NodePtrPtr parent_node_ptr,NodePtrPtr node_ptr  ) {
    NodePtr count = (*parent_node_ptr);
    while (count->color == 1) {
        stack_parent_ptr.pop();
        if ((*stack_parent_ptr.peek())->left == *parent_node_ptr) {
            //  MY PARENT IS LEFT
            if ((*stack_parent_ptr.peek())->right->color == 1) {
                //  MY UNCLE IS RED
                //             G(B)                         G(R)
                //            /    \                       /   \
                //          P(R)    U(R)      ->         P(B)  U(B)
                //          |                             |
                //         X(R)                          X(R)
                (*stack_parent_ptr.peek())->color = 1;
                (*stack_parent_ptr.peek())->right->color = 0;
                (*parent_node_ptr)->color = 0;
                if ((*stack_parent_ptr.peek()) != root) stack_parent_ptr.pop();
            } else {
                //  MY UNCLE IS BLACK
                if ((*parent_node_ptr)->right == *node_ptr) {
                    //             G(B)                         G(B)
                    //            /    \                       /   \
                    //          P(R)    U(B)      ->         X(R)  G(R)
                    //             \                         /
                    //            X(R)                     P(R)
                    left_rotate(node_ptr, node_ptr, parent_node_ptr);
                }
                //             G(B)                         P(B)
                //            /    \                       /   \
                //          P(R)    U(B)      ->         X(R)  G(R)
                //         /                                     \
                //        X(R)                                    X(B)
                (*stack_parent_ptr.peek())->color = 1;
                (*parent_node_ptr)->color = 0;
                right_rotate(node_ptr, parent_node_ptr, stack_parent_ptr.peek());
                break;
            }
        } else {
            //  MY PARENT IS RIGHT
            if ((*stack_parent_ptr.peek())->left->color == 1) {
                //  MY UNCLE IS RED
                //             G(B)                         G(R)
                //            /    \                       /   \
                //          U(R)    P(R)      ->         P(B)  U(B)
                //                   |                            |
                //                  X(R)                         X(R)
                (*stack_parent_ptr.peek())->color = 1;
                (*stack_parent_ptr.peek())->left->color = 0;
                (*parent_node_ptr)->color = 0;
                if ((*stack_parent_ptr.peek()) != root) stack_parent_ptr.pop();
            } else {
                //  MY UNKLE IS BLACK
                if ((*parent_node_ptr)->left == *node_ptr) {
                    //             G(B)                         G(R)
                    //            /    \                       /   \
                    //          U(R)    P(R)      ->         P(B)   X(B)
                    //                   /                            \
                    //                 X(R)                          U(R)
                    right_rotate(node_ptr, node_ptr, parent_node_ptr);
                }
                //             G(B)                         P(B)
                //            /    \                       /   \
                //          U(R)    P(R)      ->         G(R)   X(R)
                //                   \                   /
                //                   X(R)              U(B)
                (*stack_parent_ptr.peek())->color = 1;
                (*parent_node_ptr)->color = 0;
                left_rotate(node_ptr, parent_node_ptr, stack_parent_ptr.peek());
                break;
            }
        }
        root->color = 0;
        node_ptr = parent_node_ptr;
        parent_node_ptr = stack_parent_ptr.peek();
        count = *stack_parent_ptr.peek();
    }
}


void RedBlackTree:: insert(int key) {
    NodePtr node = new Node;
    node->data = key;
    node->left = TNULL;
    node->right = TNULL;
    node->color = 1;
    node->key = hash();
    NodePtrPtr parent_new_node_ptr = &(this->root);
    if (root == TNULL){
        root = node;
        root->color = 0;
        return;
    }
    do {
        stack_parent_ptr.push(&(*parent_new_node_ptr));
        if (((*parent_new_node_ptr)->data > key)){
            if( (*parent_new_node_ptr)->left == TNULL) break;
            parent_new_node_ptr = &((*parent_new_node_ptr)->left);
        } else {
            if( (*parent_new_node_ptr)->right == TNULL) break;
            parent_new_node_ptr = &((*parent_new_node_ptr)->right);
        }
    } while ((*parent_new_node_ptr) != TNULL );
    ((*parent_new_node_ptr)->data > key) ? &((*parent_new_node_ptr)->left = node) :
    &((*parent_new_node_ptr)->right = node);
    NodePtrPtr  new_node_ptr = &node;
    insert_fix(parent_new_node_ptr, new_node_ptr);
    stack_parent_ptr.clear();
    return;
}


void RedBlackTree:: right_rotate (NodePtrPtr node_ptr, NodePtrPtr parent_node_ptr, NodePtrPtr parent_parent_node_ptr){
    NodePtrPtr child = node_ptr; //сохраним ссылки для рекурсии
    if (*parent_parent_node_ptr == nullptr){
        const NodePtr buffer = (*node_ptr)->right; // =b
        root = (*node_ptr); // x=y -> y is root
        root->right = (*parent_node_ptr);
        (*parent_node_ptr)->left = buffer;
        return;
    }
    const NodePtr buffer = (*parent_node_ptr)->right; // = c
    const NodePtr ded = (*parent_parent_node_ptr); // = x
    (*parent_parent_node_ptr) = *parent_node_ptr; // x= y
    (*parent_parent_node_ptr)->right = ded;
    ded->left= buffer;
}




void RedBlackTree:: left_rotate (NodePtrPtr node_ptr, NodePtrPtr parent_node_ptr, NodePtrPtr parent_parent_node_ptr) {
    NodePtrPtr child = node_ptr;
    if ((*parent_parent_node_ptr) == nullptr){
        const NodePtr buffer = (*node_ptr)->left; // = a
        this->root = *node_ptr; // x = y
        root->left = *parent_node_ptr; // a = x
        root->left->right = buffer; // +a
        return;
    }
    const NodePtr buffer = (*parent_node_ptr)->left;
    const NodePtr ded = (*parent_parent_node_ptr);
    *parent_parent_node_ptr = *parent_node_ptr;
    (*parent_parent_node_ptr)->left = ded;
    ded->right = buffer;
    parent_node_ptr = child;
}


NodePtrPtr RedBlackTree:: min(NodePtrPtr node) {
    while ((*node)->left != TNULL){
        node = &((*node)->left);
    }
    return node;
}


NodePtrPtr RedBlackTree:: parent_min(NodePtrPtr   node) {
    while ((*node)->left->left != TNULL)
        node = &((*node)->left);
    return node;
}


void RedBlackTree:: del( int key) {
    NodePtrPtr node_to_del_ptr = &(this->root);
    while ((*node_to_del_ptr) != TNULL){
        if ((*node_to_del_ptr)->data == key) break;
        node_to_del_ptr = ((*node_to_del_ptr)->data > key) ? &((*node_to_del_ptr)->left) : &((*node_to_del_ptr)->right);
    }
    if ((*node_to_del_ptr) == TNULL) return;
    int color_node_to_del = (*node_to_del_ptr)->color;
    if ((*node_to_del_ptr)->right == TNULL) {
        if ((*node_to_del_ptr)->left == TNULL){
            (*node_to_del_ptr)->color = color_node_to_del;
            *node_to_del_ptr = (*node_to_del_ptr)->left;
            if(color_node_to_del == 0) del_fix( (*node_to_del_ptr),  key);
            stack_parent_ptr.clear();
            return;
        }
        (*node_to_del_ptr)->color = color_node_to_del;
        *node_to_del_ptr = (*node_to_del_ptr)->left;
        return;
    }
    if ((*node_to_del_ptr)->left == TNULL) {
        *node_to_del_ptr = (*node_to_del_ptr)->right;
        (*node_to_del_ptr)->color = color_node_to_del;
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
        (*node_to_del_ptr)->color = color_node_to_del;
        (*node_to_del_ptr)->color = color_node_to_del;
        if(color_node_to_del == 0) del_fix( (*node_to_del_ptr),  key);
        stack_parent_ptr.clear();
        return;
    }
    NodePtrPtr minimum = (min(&((*node_to_del_ptr)->right)));
    int color_minimum = (*minimum)->color;
    int minimum_data = (*minimum)->data;
    (*minimum)->right->color = color_minimum;
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
    (*node_to_del_ptr)->color = color_node_to_del;
    if(color_node_to_del == 0) del_fix( (*parent_min_ptr)->left,  minimum_data);
    stack_parent_ptr.clear();
}


void RedBlackTree::del_fix(NodePtr node_to_del, int key) {
    NodePtrPtr  node = {&this->root};
    while (*node != TNULL){
        if (*node == node_to_del)break;
        node = ((*node)->data > key) ? &((*node)->left) : &((*node)->right);
        stack_parent_ptr.push(node);
    }
    if (*node != TNULL) stack_parent_ptr.push(node);
    NodePtrPtr parent = node;
    while ((*stack_parent_ptr.peek()) != root && (*stack_parent_ptr.peek())->color == 0){
        if ((*stack_parent_ptr.peek()) == TNULL) stack_parent_ptr.pop();
        if ( (*stack_parent_ptr.peek())->left == *parent){
            // I AM LEFT
            if ((*stack_parent_ptr.peek())->right->color == 1){
                // MY BROTHER IS RED
                //             G(B)                         P(B)
                //            /    \                       /   \
                //          P(B)    U(R)      ->         X(B)  G(R)
                //          |                                    |
                //         X(B)                                  U(B)
                //#4
                (*stack_parent_ptr.peek())->right->color = 0;
                (*stack_parent_ptr.peek())->color = 1;
                left_rotate(node, &((*stack_parent_ptr.peek())->left),stack_parent_ptr.peek());
            }
            if ((*stack_parent_ptr.peek())->right->right->color == 0 and  (*stack_parent_ptr.peek())->right->left->color == 0) {
                //  BOTH NEPHEWS ARE BLACK
                //             G(?)                         G(B)
                //            /    \                       /   \
                //          X(B)    U(R)      ->         X(B)   U(R)
                //                  /  \                       /  \         |
                //               n1(B) n2(B)                 n1(B) n2(B)
                //#5
                (*stack_parent_ptr.peek())->right->color = 1;
                (*stack_parent_ptr.peek())->color = 0;
                parent = stack_parent_ptr.peek();
                stack_parent_ptr.pop();
            } else {
                if ( (*stack_parent_ptr.peek())->right->right->color == 0){
                    //  RIGHT NEPHEWS is BLACK
                    //             G(?)                         G(B)
                    //            /    \                       /   \
                    //          X(B)    U(B)      ->         X(B)   n1(B)
                    //                  /  \                           \
                    //               n1(R) n2(B)                       U(R)
                    //                                                    \
                    //                                                    n2(B)
                    (*stack_parent_ptr.peek())->right->left->color = 0;
                    (*stack_parent_ptr.peek())->right->color = 1;
                    right_rotate(node,&((*stack_parent_ptr.peek())->right->right),&((*stack_parent_ptr.peek())->right) );
                }
                //  RIGHT NEPHEWS is RED
                //             G(?)                         U(color-G)
                //            /    \                       /   \
                //          X(B)    U(B)      ->         G(B)   n2(B)
                //                  /  \                 /  \
                //               n1(?) n2(R)          X(B)  n2(B)
                (*stack_parent_ptr.peek())->right->color =(*stack_parent_ptr.peek())->color;
                (*stack_parent_ptr.peek())->right->right->color = 0;
                (*stack_parent_ptr.peek())->color = 0;
                left_rotate(node,&((*stack_parent_ptr.peek())->right),stack_parent_ptr.peek() );
                return;
            }
        } if ( (*stack_parent_ptr.peek())->right== *parent) {
            //  I AM RIGHT
            if ((*stack_parent_ptr.peek())->left->color == 1){
                //  MY BROTHER IS RED
                (*stack_parent_ptr.peek())->left->color = 0;
                (*stack_parent_ptr.peek())->color = 1;
                right_rotate(node, &((*stack_parent_ptr.peek())->right),stack_parent_ptr.peek());
            }
            if((*stack_parent_ptr.peek())->left->left->color == 0 and (*stack_parent_ptr.peek())->left->right->color == 0 ){
                //  BOTH NEPHEWS ARE BLACK
                (*stack_parent_ptr.peek())->left->color = 1;
                (*stack_parent_ptr.peek())->color = 0;
                parent = stack_parent_ptr.peek();
                stack_parent_ptr.pop();
            } else {
                if ((*stack_parent_ptr.peek())->left->left->color == 0) {
                    //  LEFT NEPHEWS is BLACK
                    (*stack_parent_ptr.peek())->left->right->color = 0;
                    (*stack_parent_ptr.peek())->left->color = 1;
                    left_rotate(node, &((*stack_parent_ptr.peek())->right->right), &((*stack_parent_ptr.peek())->right));
                }
                //  LEFT NEPHEWS is RED
                (*stack_parent_ptr.peek())->left->color = (*stack_parent_ptr.peek())->color;
                (*stack_parent_ptr.peek())->color = 0;
                (*stack_parent_ptr.peek())->left->left->color = 0;
                right_rotate(node, &((*stack_parent_ptr.peek())->left), stack_parent_ptr.peek());
                break;
            }
        }
    }
}


bool RedBlackTree::search(int data_) {
    NodePtr root_help = this->root;
    while (root_help != TNULL){
        if (root_help->data == data_) return true;
        root_help = (root_help->data > data_) ? root_help->left : root_help->right;
    }
    return false;
}


void RedBlackTree:: print(NodePtr root, std::string indent, bool last) {
    if (root != TNULL) {
        std::cout << indent;
        if (last) {
            std::cout << "R----";
            indent += "   ";
        } else {
            std::cout << "L----";
            indent += "|  ";
        }
        std::string sColor = root->color ? "RED" : "BLACK";
        std::cout << root->data << "(" << sColor << ")" << "\n";
        print(root->left, indent, false);
        print(root->right, indent, true);
    }
}


void RedBlackTree:: print() {
    if (root) {
        print(this->root, "", true);
    }
}


int main() {
    return 0;
}

