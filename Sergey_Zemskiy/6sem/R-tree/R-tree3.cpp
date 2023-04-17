#include <iostream>
#include <math.h>

#define childs 5

class Rectangle{
public:
    double x1;
    double y1;
    double x2;
    double y2;
public:
    bool inclusion (double x, double y);
    bool inclusion (Rectangle temp);
public:
    Rectangle (double x1, double y1, double x2, double y2);
    Rectangle (const Rectangle &other);
    Rectangle ();
    Rectangle operator=(const Rectangle &other);
} ;

bool Rectangle::inclusion(double x, double y) {
    if ((x1 <= x) && (y1 <= y) && (x2 >= x) && (y2 >= y)) return true;
    return false;
}

bool Rectangle::inclusion(Rectangle temp) {
    if ((x1 <= temp.x1) && (y1 <= temp.y1) && (x2 >= temp.x2) && (y2 >= temp.y2)) return true;
    return false;
}

Rectangle Rectangle::operator=(const Rectangle &other) {
    if (this == &other) return *this;
    x1 = other.x1;
    y1 - other.y1;
    x2 = other.x2;
    y2 = other.y2;
}

Rectangle::Rectangle(const Rectangle &other) {
    x1 = other.x1;
    y1 = other.y1;
    x2 = other.x2;
    y2 = other.y2;
}

Rectangle::Rectangle(double x1, double y1, double x2, double y2) {
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
}

Rectangle::Rectangle() {
    this->x1 = this->y1 = this->x2 = this->y2 = 0.0;
}
//сделать класс с функцией попадания точки в ректангл



class Node {
public:
    Node *child[childs];
    Rectangle node_rectangle[childs];

    Node();
};

Node::Node() {
    for (int count = 0; count < childs; count ++){
        child[count] = nullptr;
        node_rectangle[count] = Rectangle();
    }
}

class Exception : public std::domain_error
{
public:
    Exception(const char* const message) : std::domain_error(message)
    {}
};

Exception too_much("You try to push too much elements");

class Target {
public:
    std::string name[childs];
    Rectangle node_rectangle[childs];

    Target();
};

Target::Target() {
    for (int count = 0; count < childs; count ++){
        child[count] = nullptr;
        node_rectangle[count] = Rectangle();
    }
}

class Tree {
private:
    Node* root;
public:
    Tree() : root(nullptr) {}
    // первым всегда вставляем изначальные масштабы, т.е. корень
    void push(double x1_temp, double y1_temp, double x2_temp, double y2_temp, std::string type_temp);
    void print();
    Node *find(double x, double y,std::string type_temp);
    Node *find_recursive(double x, double y,Node* temp, std::string type_temp);
private:
    void vstavka(Node *new_node, Node *temp,unsigned number);
    void print_out(Node *temp);


};



void Tree::push(double x1_temp, double y1_temp, double x2_temp, double y2_temp, std::string type_temp) {
    Node* new_node = new Node(x1_temp, y1_temp, x2_temp, y2_temp, type_temp);
    if (root == nullptr) {
        root = new_node;
        std::cout << "map has pushed" << std::endl;
        return;
    }
    Node* temp = root;
    vstavka(new_node, temp, 0);
    std::cout << "rectangle " << new_node->type << " has pushed" << std::endl;
}

void Tree::vstavka (Node* new_node, Node* temp, unsigned number_child) {
    if (number_child >= 5) throw too_much;
    if (temp->child[number_child] ) {
        if ((new_node->x1 >= temp->child[number_child]->x1) &&
            (new_node->y1 >= temp->child[number_child]->y1) &&
            (new_node->x2 <= temp->child[number_child]->x2) &&
            (new_node->y2 <= temp->child[number_child]->y2)) {
            vstavka(new_node, temp->child[number_child], 0);
        }
        else if ((new_node->x1 <= temp->child[number_child]->x1) &&
                 (new_node->y1 <= temp->child[number_child]->y1) &&
                 (new_node->x2 >= temp->child[number_child]->x2) &&
                 (new_node->y2 <= temp->child[number_child]->y2)) {
            new_node->child[0] = temp->child[number_child];
            temp->child[number_child] = new_node;
            unsigned count_child = 0;
            for (int count = 0; count < childs; count++) {
                if (count == number_child) continue;
                if ((new_node->x1 <= temp->child[count]->x1) &&
                    (new_node->y1 <= temp->child[count]->y1) &&
                    (new_node->x2 >= temp->child[count]->x2) &&
                    (new_node->y2 >= temp->child[count]->y2)) {
                    count_child++;
                    new_node->child[count_child] = temp->child[count];
                    temp->child[count] = nullptr;
                }
            }
            return;
        }
        else vstavka(new_node, temp, number_child + 1);
    }

    else {
        temp->child[number_child] = new_node;
    }
}

/*void Tree::print() {
    if (root == nullptr) return;
    print_out(root);
    std::cout << std::endl;
}


void Tree::print_out(Node *temp) {
    std::cout << temp->type << " ";
    for (unsigned count = 0; count < childs; count++) {
        if (temp->child[count] !=nullptr) print_out(temp->child[count]);
    }
}

static double distance;
static double distance_temp;
static Node* find_temp = nullptr;
Node* Tree::find (double x, double y, std::string type_temp) {
    if (root == nullptr) return nullptr;
    distance = sqrt(pow(root->x2 - root->x1, 2) + pow(root->y2 - root->y1, 2));
    std::cout << distance;
    find_recursive(x, y, root, type_temp);
    return find_temp;
}

Node *Tree::find_recursive(double x, double y, Node* temp, std::string type_temp) {
    if( temp->type == type_temp) {
        distance_temp = sqrt(pow((temp->x2 + temp->x1) / 2 - x, 2) + pow((temp->y2 + temp->y1) / 2 - y, 2));
        if (distance_temp < distance) {
            find_temp = temp;
            distance = distance_temp;
        }
    }
    for (unsigned count = 0; count < childs; count++) {
        if (temp->child[count] != nullptr) find_recursive(x, y, temp->child[count], type_temp);
    }
    return find_temp;
}*/


int main()
{
    Rectangle a (  0,   0, 100, 100);
    std::cout << a.x1 << std::endl;
    /*Tree l;
    l.push(  0,   0, 100, 100, "root");
    l.push( 99,  99, 100, 100, "aa");
    l.push( 98,  98,  99,  99, "ab");
    l.push( 97,  97,  98,  98, "ac");
    l.push( 96,  96,  97,  97, "ad");
    l.push( 95,  95,  96,  96, "ae");
    l.push(  1,   1, 100, 100, "a");
    l.push(  0,  99,   1, 100, "b");
    l.push(99.1,99.1, 100, 100, "a");
    l.push(99,99.5, 100, 100, "a");
    l.print();
    Node* p = l.find(50,50,"a");
    std::cout << std::endl << p->x1 << " , " << p->x2;
    std::cout << std::endl << distance << std::endl;*/
    //l.push(94, 94, 95, 95, 'g');
    return 0;
}
