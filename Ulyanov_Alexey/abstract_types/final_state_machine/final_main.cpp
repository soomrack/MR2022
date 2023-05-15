#include <iostream>
#include "dynamic_array.h"
#include "graphh.h"

class Node {

public:
    unsigned int value;
    char* description;

    Dynamic_array<Node*> neighbors;

private:
    void (*function)() {nullptr};


public:

    Node();
    Node(const unsigned int x);
    Node(const unsigned int x, char* about, void (*new_func)());
    Node(const Node& x);

    Node& operator=(const Node& x);
    friend bool operator==(const Node &x, const Node &y);

    void play();

};


Node::Node() {
    value = 0;
    neighbors = Dynamic_array<Node*>();
}


Node::Node(const unsigned int x) {
    value = x;
    description = nullptr;
    function = nullptr;
    neighbors = Dynamic_array<Node*>();
}


Node::Node(const unsigned int x, char* about, void (*new_func)()) {
    value = x;
    description = about;
    function = new_func;
    neighbors = Dynamic_array<Node*>();
}


Node::Node(const Node &x) {
    value = x.value;
    description = x.description;
    function = x.function;
    neighbors = x.neighbors;
}


Node& Node::operator=(const Node &x) {
    value = x.value;
    description = x.description;
    function = x.function;
    neighbors = x.neighbors;
}


bool operator==(const Node &x, const Node &y) {
    if (x.value == y.value) return true;
    return false;
}


void Node::play() {
    function();
}


template <typename T>
void Graph<T>::output() {
    if (vertexs.length() == 0) {
        std::cout << "There is no elements in this graph\n\n";
        return;
    }

    for (unsigned int idx = 0; idx < vertexs.length(); idx++){
        std::cout << vertexs[idx].description << "\n\tafter that you can   [\n";

        if (vertexs[idx].neighbors.length() != 0){
            for (unsigned int jdx = 0; jdx < vertexs[idx].neighbors.length(); jdx++){
                std::cout << "\t\t" << vertexs[idx].neighbors[jdx]->description << "\n";
            }
        }

        std::cout << "\t]\n";
    }
    std::cout << "\n";

}


void stay(){
    std::cout << "You decided to stop and rest. Birds sing in the distance, somewhere the river noises.\n";
}


void run(){
    std::cout << "Looks like you're gonna have to run (or you decided it yourself). Better don't look back, or you'll fall!\n";
}


void ready_to_attack(){
    std::cout << "You feel threatened, prepare for battle!\n";
}


void battle(){
    std::cout << "Oh no! There is no places to hide anymore. Nothing left to do, FIGHT!!!\n";
}


void be_treated(){
    std::cout << "You decided to sit down and repair the wounds, for as long as it possible.\n";
}


void lets_play(Graph<Node> place){
    Node status = *place.get(0);
    while (true){
        status.play();
        std::cout << "What do you want to do next? \n[\n"; // (choose 0 to " << status.neighbors.length() - 1 << ")";
        for (unsigned int idx = 0; idx < status.neighbors.length(); idx++){
            std::cout << "\t" << idx << ":" << status.neighbors[idx]->description << "\n";
        }
        std::cout << "]\n";

        unsigned int chose;
        std::cin >> chose;
        std::cout << "\n";

        if (chose >= status.neighbors.length()){
            std::cout << "It seems you've decided to finish the game, goodbye!";
            return;
        }
        status = *status.neighbors[chose];

    }

}


int main() {
    Graph<Node> A;

    Node x = Node(0, "stay", &stay);
    A.add_node(x);
    Node y = Node(1, "run", &run);
    A.add_node(y);
    Node u = Node(2, "get_ready", &ready_to_attack);
    A.add_node(u);
    Node z = Node(3, "battle", &battle);
    A.add_node(z);
    Node v = Node(4, "heal", &be_treated);
    A.add_node(v);

    A.output();

    A.add_path(0, 1, true);
    A.add_path(1, 2, true);
    A.add_path(0, 2, true);
    A.add_path(0, 4, true);
    A.add_path(1, 4, true);

    A.add_path(2, 3);
    A.add_path(3, 0);
    A.add_path(3, 1);
    A.add_path(3, 4);

    A.output();

    lets_play(A);

    return 0;
}
