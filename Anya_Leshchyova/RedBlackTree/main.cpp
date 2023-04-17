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

class Stack {
    NodePtrPtr *stack;
    int sp;  //stack point
    int capacity; // размер стека

public:
    Stack();

    ~Stack();

    void push(NodePtrPtr); // вставить элемент
    void pop();  // извлечь элемент
    NodePtrPtr peek();  // посмотреть самый верхний элемент ( без извлечения )

    int size();  // размер стека
    inline bool isEmpty();  // заполнен ли стек?
    inline bool isFull(); //  пуст ли стек?
    void print(); // вывести стек
    void search(int); //  найти элемент


};

Stack::Stack(){
    capacity = 40;
    stack = new NodePtrPtr[capacity];
    sp = -1;
}

Stack::~Stack() {
    delete[] stack;
}



void Stack::push(NodePtrPtr item) {
    if (isFull()){
        print();
        std:: cout << "STACK if FULL\n";
        exit(EXIT_FAILURE);
    }

    stack[++sp] = item;
}

void Stack::pop() {
    if (isEmpty()) exit(EXIT_FAILURE);
    sp--;
}



NodePtrPtr Stack::peek() {
    if (!isEmpty()) {
        return stack[sp];
    }
    else {
        exit(EXIT_FAILURE);
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




class RedBlackTree{
public:
    RedBlackTree();

    bool search(int k) ;
    void del(int data);
    void print();
    void insert(int key);

private:
    int hash ();
    NodePtr root;
    NodePtr TNULL;
    int count;
    std::stack <NodePtr> stack_parent;
    Stack PARENT_PTR;
    NodePtr search(NodePtr node, int key);
    void print(NodePtr root, std::string indent, bool last);
    void del(NodePtr node, int key);
    NodePtr min(NodePtr node);  // node =! TNULL
    NodePtr parent_min(NodePtr  node);  // node =! TNULL
    NodePtrPtr max();
    void insert_fix (NodePtrPtr parent_node_ptr,NodePtrPtr node_ptr  ) ;
    void right_rotate (NodePtrPtr node_ptr, NodePtrPtr parent_node_ptr, NodePtrPtr parent_parent_node_ptr);
    void left_rotate (NodePtrPtr node_ptr, NodePtrPtr parent_node_ptr, NodePtrPtr parent_parent_node_ptr);
    NodePtrPtr min(NodePtrPtr node);  // node =! TNULL
    NodePtrPtr parent_min(NodePtrPtr  node);  // node =! TNULL
    // void del_fix (NodePtrPtr parent_node_ptr,NodePtrPtr node_ptr  ) ;
    void del_fix(NodePtr node_to_del, int key);
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
        PARENT_PTR.print();
        PARENT_PTR.pop();

        if ((*PARENT_PTR.peek())->left == *parent_node_ptr) {
            std::cout << "-------MY PARENT IS LEFT-------\n";
            if ((*PARENT_PTR.peek())->right->color == 1) {
                std::cout << "-------MY UNKLE IS RED-------\n";
                (*PARENT_PTR.peek())->color = 1;
                (*PARENT_PTR.peek())->right->color = 0;
                (*parent_node_ptr)->color = 0;
                if ((*PARENT_PTR.peek()) != root) PARENT_PTR.pop();
            } else {
                std::cout << "-------MY UNKLE IS BLACK-------\n";
                if ((*parent_node_ptr)->right == *node_ptr) {
                    left_rotate(node_ptr, node_ptr, parent_node_ptr);
                }
                (*PARENT_PTR.peek())->color = 1;
                (*parent_node_ptr)->color = 0;
                right_rotate(node_ptr, parent_node_ptr, PARENT_PTR.peek());
                break;
            }
        } else {
            std::cout << "-------MY PARENT IS RIGHT-------\n";
            if ((*PARENT_PTR.peek())->left->color == 1) {
                std::cout << "-------MY UNKLE IS RED-------\n";

                (*PARENT_PTR.peek())->color = 1;
                (*PARENT_PTR.peek())->left->color = 0;
                (*parent_node_ptr)->color = 0;
                // count = *PARENT_PTR.peek();
                if ((*PARENT_PTR.peek()) != root) PARENT_PTR.pop();


            } else {
                std::cout << "-------MY UNKLE IS BLACK-------\n";

                if ((*parent_node_ptr)->left == *node_ptr) {
                    right_rotate(node_ptr, node_ptr, parent_node_ptr);

                }
                (*PARENT_PTR.peek())->color = 1;
                (*parent_node_ptr)->color = 0;
                left_rotate(node_ptr, parent_node_ptr, PARENT_PTR.peek());


                break;

            }

        }
        root->color = 0;
        node_ptr = parent_node_ptr;
        parent_node_ptr = PARENT_PTR.peek();
        count = *PARENT_PTR.peek();
        // std::cout <<"_______________________________________________________________________\n";
    }


}





void RedBlackTree:: insert(int key) {
    NodePtr node = new Node;
    node->data = key;
    node->left = TNULL;
    node->right = TNULL;
    //  NodePtr last_leaf = nullptr;
    //  NodePtr root_help = this->root;
    node->color = 1;
    node->key = hash();
    NodePtrPtr parent_new_node_ptr = &(this->root);

    std::cout << "\n";
    std::cout << "\n";
    std:: cout << " DATA =  " << node->data << "\n";

    if (root == TNULL){
        std:: cout << "I AM ROOT "  <<"\n";
        root = node;
        root->color = 0;
        return;
    }
    do {
        PARENT_PTR.push(&(*parent_new_node_ptr));
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
    while (PARENT_PTR.isEmpty() != true){
        PARENT_PTR.pop();
    }


    return;
}


void RedBlackTree:: right_rotate (NodePtrPtr node_ptr, NodePtrPtr parent_node_ptr, NodePtrPtr parent_parent_node_ptr){
    // #1
//сохраним ссылки для рекурсии
    NodePtrPtr child = node_ptr;

    std:: cout << "R_ROTARY" << "\n";
    std:: cout << "node_ptr =  " <<  (*node_ptr)->data << "\n";
    std:: cout <<"parent_node_ptr->data =   " <<(*parent_node_ptr)->data <<"\n";
    std:: cout <<"parent_parent_node_ptr->data =   " <<(*parent_parent_node_ptr)->data <<"\n";
    if ((*node_ptr)->data == 90) print();
    if (*parent_parent_node_ptr == nullptr){
        // #1
        const NodePtr buffer = (*node_ptr)->right; // =b
        root = (*node_ptr); // x=y -> y is root
        root->right = (*parent_node_ptr);
        (*parent_node_ptr)->left = buffer;
        return;
    }
    //#2
    const NodePtr buffer = (*parent_node_ptr)->right; // = c
    const NodePtr ded = (*parent_parent_node_ptr); // = x
    (*parent_parent_node_ptr) = *parent_node_ptr; // x= y
    (*parent_parent_node_ptr)->right = ded;
    ded->left= buffer;
    // PARENT_PTR.peek() = child;
    std:: cout << "node_ptr =  " <<  (*node_ptr)->data << "\n";
    std:: cout <<"parent_node_ptr->data =   " <<(*parent_node_ptr)->data <<"\n";
    std:: cout <<"parent_parent_node_ptr->data =   " <<(*parent_parent_node_ptr)->data <<"\n";
    std:: cout  <<"\n";
    std:: cout  <<"\n";
    if ((*node_ptr)->data == 90) print();
}




void RedBlackTree:: left_rotate (NodePtrPtr node_ptr, NodePtrPtr parent_node_ptr, NodePtrPtr parent_parent_node_ptr) {
    PARENT_PTR.print();
    NodePtrPtr child = node_ptr;
    std::cout << "L_ROTARY" << "\n";
    std::cout << "node_ptr =  " << (*node_ptr)->data << "\n";
    std::cout << "parent_node_ptr->data =   " << (*parent_node_ptr)->data << "\n";
    std::cout << "parent_parent_node_ptr->data =   " << (*parent_parent_node_ptr)->data << "\n";
    if ((*node_ptr)->data == 90) print();
    if ((*parent_parent_node_ptr) == nullptr){
        //#1
        const NodePtr buffer = (*node_ptr)->left; // = a
        this->root = *node_ptr; // x = y
        root->left = *parent_node_ptr; // a = x
        root->left->right = buffer; // +a
        std::cout << "AAAAAAAAAAAAAAAAAAA" << "\n";
        PARENT_PTR.print();
        return;
    }
    //#2
    const NodePtr buffer = (*parent_node_ptr)->left;
    const NodePtr ded = (*parent_parent_node_ptr);
    *parent_parent_node_ptr = *parent_node_ptr;
    (*parent_parent_node_ptr)->left = ded;
    ded->right = buffer;
    parent_node_ptr = child;
    std:: cout << "node_ptr =  " <<  (*node_ptr)->data << "\n";
    std:: cout <<"parent_node_ptr->data =   " <<(*parent_node_ptr)->data <<"\n";
    std:: cout <<"parent_parent_node_ptr->data =   " <<(*parent_parent_node_ptr)->data <<"\n";
    std:: cout  <<"\n";
    std:: cout  <<"\n";
    PARENT_PTR.print();
    std:: cout  <<"\n";
    std:: cout  <<"\n";
    std:: cout  <<"\n";
    std:: cout  <<"\n";
    if ((*node_ptr)->data == 90) print();


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
            //#1
            (*node_to_del_ptr)->color = color_node_to_del;
            *node_to_del_ptr = (*node_to_del_ptr)->left;
            //#2
            if(color_node_to_del == 0) del_fix( (*node_to_del_ptr),  key);
            return;
        }
        // #3
        (*node_to_del_ptr)->color = color_node_to_del;
        *node_to_del_ptr = (*node_to_del_ptr)->left;
        return;
    }
    if ((*node_to_del_ptr)->left == TNULL) {
        // #3
        const NodePtr dop_for_stack = ((*node_to_del_ptr)->right);
        *node_to_del_ptr = (*node_to_del_ptr)->right;
        (*node_to_del_ptr)->color = color_node_to_del;

        return;
    }

    if ((*node_to_del_ptr)->right->left == TNULL){  //ОСОБЫЙ СЛУЧАЙ
        const NodePtr dop_for_stack = ((*node_to_del_ptr)->right->right);

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

        return;
    }

    NodePtrPtr minimum = (min(&((*node_to_del_ptr)->right)));
    //  const NodePtr dop_for_stack = (*minimum)->right;
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

}


void RedBlackTree::del_fix(NodePtr node_to_del, int key) {
    NodePtrPtr  node = {&this->root};
    while (*node != TNULL){
        if (*node == node_to_del)break;
        //PARENT_PTR.push(node);
        node = ((*node)->data > key) ? &((*node)->left) : &((*node)->right);
        PARENT_PTR.push(node);
    }
    if (*node != TNULL) PARENT_PTR.push(node);



    NodePtrPtr parent= node;

    while ((*PARENT_PTR.peek()) != root && (*PARENT_PTR.peek())->color == 0){

        if ((*PARENT_PTR.peek())= TNULL) PARENT_PTR.pop();

        if ( (*PARENT_PTR.peek())->left == *parent){
            std:: cout << "I AM LEFT\n";
            if ((*PARENT_PTR.peek())->right->color == 1){
                std::cout << "MY BROTHER IS RED\n";
                //#4
                (*PARENT_PTR.peek())->right->color = 0;
                (*PARENT_PTR.peek())->color = 1;
                left_rotate(node, &((*PARENT_PTR.peek())->left),PARENT_PTR.peek());

            }

            if ((*PARENT_PTR.peek())->right->right->color == 0 and  (*PARENT_PTR.peek())->right->left->color == 0) {
                std::cout << "BOTH NEPHEWS ARE BLACK\n";
                //#5
                (*PARENT_PTR.peek())->right->color = 1;
                (*PARENT_PTR.peek())->color = 0;

                parent = PARENT_PTR.peek();
                PARENT_PTR.pop();


            } else {
                // у брата правый ребенок черный
                //#6

                if ( (*PARENT_PTR.peek())->right->right->color == 0){
                    k=1;
                    print();
                    std::cout << "RIGHT NEPHEWS is BLACK\n";
                    (*PARENT_PTR.peek())->right->left->color = 0;
                    (*PARENT_PTR.peek())->right->color = 1;
                    right_rotate(node,&((*PARENT_PTR.peek())->right->right),&((*PARENT_PTR.peek())->right) );

                }
                std::cout << "RIGHT NEPHEWS is RED\n";
                (*PARENT_PTR.peek())->right->color =(*PARENT_PTR.peek())->color;
                (*PARENT_PTR.peek())->right->right->color = 0;
                (*PARENT_PTR.peek())->color = 0;

                left_rotate(node,&((*PARENT_PTR.peek())->right),PARENT_PTR.peek() );
                return;
            }

        } if ( (*PARENT_PTR.peek())->right== *parent) {
            std:: cout << "I AM RIGHT\n";

            if ((*PARENT_PTR.peek())->left->color == 1){
                std::cout << "MY BROTHER IS RED\n";

                (*PARENT_PTR.peek())->left->color = 0;
                (*PARENT_PTR.peek())->color = 1;
                right_rotate(node, &((*PARENT_PTR.peek())->right),PARENT_PTR.peek());

            }

            if((*PARENT_PTR.peek())->left->left->color == 0 and (*PARENT_PTR.peek())->left->right->color == 0 ){
                std::cout << "BOTH NEPHEWS ARE BLACK\n";
                (*PARENT_PTR.peek())->left->color = 1;
                (*PARENT_PTR.peek())->color = 0;

                parent = PARENT_PTR.peek();
                PARENT_PTR.pop();

            } else {
                if ((*PARENT_PTR.peek())->left->left->color == 0) {
                    std::cout << "LEFT NEPHEWS is BLACK\n";
                    (*PARENT_PTR.peek())->left->right->color = 0;

                    (*PARENT_PTR.peek())->left->color = 1;
                    left_rotate(node, &((*PARENT_PTR.peek())->right->right), &((*PARENT_PTR.peek())->right));
                }
                std::cout << "LEFT NEPHEWS is RED\n";
                (*PARENT_PTR.peek())->left->color = (*PARENT_PTR.peek())->color;
                (*PARENT_PTR.peek())->color = 0;
                (*PARENT_PTR.peek())->left->left->color = 0;

                right_rotate(node, &((*PARENT_PTR.peek())->left), PARENT_PTR.peek());
                break;
            }
        }
    }

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
    RedBlackTree bst;
    int a;
    bst.insert(55);
    bst.print();

    bst.insert(40);
    bst.print();



    bst.insert(65);
    bst.print();

    bst.insert(60);
    bst.print();
    bst.insert(59);
    bst.print();
    bst.insert(75);

    bst.print();

    bst.insert(56);
    bst.print();
    bst.insert(42);
    bst.print();
    bst.insert(555);
    bst.print();

    bst.insert(57);
    bst.print();
    bst.insert(5);
    bst.insert(41);

    bst.insert(1);
    bst.insert(69);
    bst.print();
    bst.insert(90);
    // bst.print();
    bst.insert(91);
    bst.insert(68);
    bst.insert(85);
    bst.insert(86);
    bst.insert(6);
    bst.insert(7);





    bst.print();
    std:: cout << "AFTER DELETE\n";
    bst.del (1);
    bst.print();
    return 0;
}

