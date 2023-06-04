#include <iostream>

#include "StackArray.h"
#include "QueueArray.h"

void test_Stack() {
    std::cout << "\n------------ТЕСТЫ Stack------------\n";
    StackArray<int> stack1(4);
    std::cout << stack1.isEmpty() << std::endl;

    try {
        std::cout << stack1.pop() << std::endl;
        std::cout << stack1.pop() << std::endl;
    }
    catch (StackException &e) {
        std::cout << e.what() << std::endl;
    }

    stack1.push(1);
    stack1.push(2);
    stack1.push(3);
    stack1.push(4);

    try {
        stack1.push(5);
    }
    catch (StackException &e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << stack1.isEmpty() << std::endl;
    std::cout << stack1.pop() << std::endl;
    std::cout << stack1.pop() << std::endl;
    std::cout << stack1.pop() << std::endl;
    std::cout << stack1.pop() << std::endl;
}

void test_Queue() {
    std::cout << "\n------------ТЕСТЫ Queue------------\n";
    QueueArray<int> queue1(4);
    std::cout << queue1.isEmpty() << std::endl;

    try {
        queue1.pop();
    }
    catch (QueueException &e) {
        std::cout << e.what() << std::endl;
    }

    queue1.push(1);
    queue1.push(2);
    queue1.push(3);
    queue1.push(4);

    try {
        queue1.push(5);
    }
    catch (QueueException &e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << queue1.isEmpty() << std::endl;
    std::cout << queue1.pop() << std::endl;
    std::cout << queue1.pop() << std::endl;
    queue1.push(5);
    std::cout << queue1.pop() << std::endl;
    std::cout << queue1.pop() << std::endl;
    queue1.push(6);
    queue1.push(7);
    queue1.push(8);
    std::cout << queue1.pop() << std::endl;
    std::cout << queue1.pop() << std::endl;
    std::cout << queue1.pop() << std::endl;
    std::cout << queue1.pop() << std::endl;

    QueueArray<const char *> queue2(2);
    queue2.push("sca");
    queue2.push("safahajsckb");
    std::cout << queue2.pop() << std::endl;
    std::cout << queue2.pop() << std::endl;
    std::cout << queue2.isEmpty() << std::endl;
}

int main() {
    system("chcp 65001");

    test_Stack();
    test_Queue();
    return 0;
}
