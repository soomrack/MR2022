#include <iostream>
#include <vector>

#include "BinaryTree.h"

int main() {
    system("chcp 65001");
    BinaryTree<int> tree;

    std::vector<int> vector;
    std::string answer;

    int seed, random;
    std::cout << "\nВведи любое целое для генерации набора чисел: ";
    std::cin >> seed;

    srand(seed);

    for (int i = 0; i < 10; ++i) {
        random = rand() % 10 + 1;
        vector.push_back(random);
        tree.insert(random);
    }

    std::cout << "переданные числа:";
    for(int item : vector) {
        std::cout << ' ' << item;
    }

    for (int i = 0; i < 11; ++i) {
        answer = (tree.search(i)) ? "да" : "нет";
        std::cout << "\n\nесть ли в дереве элемент со значением " << i << "?\nОтвет: " << answer;
    }

    std::cout << "\n\nудаляю элементы равные " << vector[vector.size() - 1] << "!";

    while ((tree.search(vector[vector.size() - 1]))) {
        tree.remove(vector[vector.size() - 1]);
    }

    answer = (tree.search(vector[vector.size() - 1])) ? "да" : "нет";
    std::cout << "\n\nесть ли в дереве элемент со значением " << vector[vector.size() - 1] << "?\nОтвет: " << answer;

    return 0;
}