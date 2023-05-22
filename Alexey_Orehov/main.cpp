#include <iostream>
#include "dynamic_array.h"
#include "stack.h"
#include "list.h"
#include "tree.h"
#include "graph.h"
#include "FSM.h"

void test_dynamic_array() {
    int A_data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    DynamicArray<int> A = {A_data, 10};

    A.resize(15);
    A[10] = 1;
    std::cout << A[10] << std::endl;
    A.resize(5);
    std::cout << A[6] << std::endl;
}


void test_stack() {
    Stack<int> A(10);
    for (int i = 0; i < 10; i++) {
        std::cout << "Inserted " << i << " to stack\n";
        A.push(i);
    }
    for (int i = 0; i < 10; i++) {
        std::cout << A.pop() << std::endl;
    }
}


void test_list() {
    using namespace list;
    int A_data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    List<int> A(A_data, 10);
    A.push_back(3);
    A.push_front(10);
    A.push_front(5);

    A.head() = 100;
    A.tail() = 200;
}

void test_tree() {
    int data[15] = {50, 55, 6, 1, 51, 52, -10, 9, -8, 7, 10, 13, 15, -1, -2};
    Tree<int> tree;

    for (auto& element : data) {
        tree.insert(element);
    }

    tree.remove(50);
    tree.remove(51);
    tree.remove(6);
    tree.remove(52);
    tree.remove(13);

    for (auto& element : data) {
        if (tree.find(element)) std::cout << "Found element " << element << std::endl;
        else std::cout << "Element " << element << " not found" << std::endl;
    }
}

void test_graph() {
    using namespace graph;
    Graph<int> G;
    G.add_node(1);
    G.add_node(2);
    G.add_node(3);
    G.add_node(4);
    G.add_node(5);

    G.add_edge(1, 3, true);
    G.add_edge(3, 2, true);
    G.add_edge(4, 5);
    G.add_edge(1, 4);
    G.add_edge(2, 5, true);

    G.delete_node(2);

    auto ref = G.get_node(5);
}

void test_game() {
    Game G;

    State start = {"start", [](Game* game){
        std::cout << "Go back and choose your next move" << std::endl;
    }};

    State battle = {"Battle. You might get injured, but reward is 50 gold coins", [](Game* game){
        if (game->armor) {
            std::cout << "You went to battle. You won, but damage was 20pts. You've earned 50 gold coins\n";
            game->health -= 20;
        } else {
            std::cout << "You went to battle. You won, but damage was 50pts. You've earned 50 gold coins\n";
            game->health -= 50;
        }
        game->money += 50;
        game->armor = false;
        game->print_stats();
    }};

    State shop = {"Shop, where you can buy armor", [](Game* game){
        std::cout << "You have options to buy armor for 40 golds or to go back\n";
    }};

    State buy_armor_confirm = {"Buy armor for 40 golds", [](Game* game) {
        if (game->money >= 40) {
            std::cout << "You've bought armor, now you'll be tougher in battle\n";
            game->armor = true;
            game->money -= 40;
            game->print_stats();
        } else {
            std::cout << "You don't have enough money\n";
        }
    }};

    State heal = {"Heal your battle wounds", [](Game* game) {
        std::cout << "Here you can heal for or to go back\n";
    }};

    State heal_confirm = {"Heal for 30 golds", [](Game* game){
        if (game->money >= 30) {
            std::cout << "You are now healed\n";
            game->health = 100;
            game->money -= 30;
            game->print_stats();
        } else {
            std::cout << "You don't have enough money\n";
        }
    }};

    G.add_node(start);
    G.add_edge(start, battle, true);
    G.add_edge(start, shop, true);
    G.add_edge(start, heal, true);

    G.add_edge(shop, buy_armor_confirm);
    G.add_edge(heal, heal_confirm);

    G.add_edge(buy_armor_confirm, start);
    G.add_edge(heal_confirm, start);

    G.play(start);
}

int main() {
    test_game();
    return 0;
}
