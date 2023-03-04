#include <conio.h>
#include <iostream>

class Tree_Exception {
public:
    int kod_mistake;

    Tree_Exception();
    Tree_Exception(int kod_mistake);
    //~Matrix_Exception() ;

    void set_mistake (int kod_mistake, int what);
};


//Объявление исключений
Tree_Exception dyplication=(1);
Tree_Exception exceeds_the_capacity=(2);




//Операторы класса иcключений
Tree_Exception:: Tree_Exception(){
    kod_mistake = 999;
}


Tree_Exception:: Tree_Exception(int kod){
    kod_mistake = kod;
}


void Tree_Exception::set_mistake (int error, int what){
    switch (error) {
        case 1:
            std::cout << "\n"<< "       Duplicate removed "<<what<< "\n";
            break;
        case 2:
            std::cout<< "\n" << "       Digit capacity exceeded "<<what<<"\n";
            break;
        default:
            std::cout << "       Unknown error \n";
    }
}

class Tree{
public:
    struct node;
    int* line;
    int quantity;

    Tree(const  int n);
    Tree(const Tree &x) ;
    Tree(Tree&& x);


    void print (node *t, int u);
    void push(int a, node **t);
    void search (const int a, node *t, int u );
    void delet (const int a, node *t, Tree root );

};

struct Tree::node{
    int info;
    node *left, *right;                        //Левая и Правая часть дерева
};


Tree::Tree (const  int n){
    Tree:: node r = {n, NULL};
    quantity = n;
    line = new int[n];
}
Tree::Tree(const Tree &x) {
    quantity = x.quantity;
    line = new int[quantity];
    for (unsigned int idx = 0; idx < quantity; idx++){
        line[idx] = x.line[idx];
    }
}

Tree::Tree(Tree&& x){
    quantity = x.quantity;
    line = x.line;
    x.quantity = 0;
    x.line = nullptr;
}

Tree::node *tree = NULL;                      //Объявляем переменную, тип которой структура Дерево
Tree::node *tree2 = NULL;


//запись
void Tree:: push(int a, node **t) {
    if ((*t) == NULL) {                   //Если дерева не существует
        (*t) = new node;
        (*t)->info = a;
        (*t)->left = (*t)->right = NULL;
        return;
    }
    //Дерево есть
    if (a == (*t)->info) {
        try{ throw dyplication;}
        catch (Tree_Exception error){ error.set_mistake(1, a);}

    }

    if (a > (*t)->info) push(a, &(*t)->right); //Если аргумент а больше чем текущий элемент, кладем его вправо
 //   else push(a, &(*t)->left);         //Иначе кладем его влево
    if (a < (*t)->info) push(a, &(*t)->left);

}
// поиск
int LEVEL =0;
void Tree:: search (const int a, node *t, int u) {
    if (t == NULL) return; // Дерева нет
    search(a, t->left, ++u);
    for (int i = 0; i < u; ++i) {
        if (a == (t)->info) LEVEL = u;
        u--;
        search(a, t->right, ++u);
    }

}

//удаление
void Tree:: delet (const int del, node *t, Tree root ){
    for ( int i = 0; i < root.quantity; i++){
        if (del == root.line[0] )root.line[i] = root.line[i+1];
        if (del == root.line[i] & i != 0 )root.line[i] = root.line[i-1];
        root.push(root.line[i], &tree2);
        }
    std::cout << "You removed the number"<< "  "<< del <<"\n";
    root.print(tree2, 0);
}


//Вывод
void Tree:: print (node *t, int u) {
    if (t == NULL) return;                  //Если дерево пустое
    print(t->left, ++u);
        for (int i = 0; i < u; ++i)
            if (i > 0) {
                std::cout << "|";
                std::cout << " ";
            }
            std::cout << t->info;
            std::cout << "\n";
            u--;
            print(t->right, ++u);                       //С помощью рекурсии посещаем правое поддерево
}

int main () {

    Tree My_Tree = Tree {10};
    for (int i=0; i < My_Tree.quantity; ++i) {
        My_Tree.line[i] = i;
        if (i == 0)  My_Tree.line[i]=5;
        if (i == 1)  My_Tree.line[i]=8;
        if (i == 2)  My_Tree.line[i]=2;
        if (i == 6)  My_Tree.line[i]=1;
        if (i == 5)  My_Tree.line[i]=9;
        My_Tree.push(My_Tree.line[i], &tree);
    }
    std::cout << "Initial series of numbers  ";
    for (int i=0; i < My_Tree.quantity; ++i) {

        std::cout <<My_Tree.line[i] << "  ";
    }
    std::cout << "\n";
    std::cout << "Tree\n";
    My_Tree.print(tree, 0);  // Вывод дерева


    My_Tree.search(3, tree, 0);
    std::cout << "Number "<< 3 << " is at the level "<< LEVEL -1 << "\n";
    My_Tree.delet(3,tree,My_Tree);

    return 0;
}
