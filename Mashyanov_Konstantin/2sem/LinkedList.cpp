#include <iostream>
#include <string>
using namespace std;

typedef double MyData;

// Объявление класса Node
class Node {
public:
    MyData data;
    Node* next;
    Node() = delete;
    Node(const MyData data, const Node* next = nullptr);
};

// Определение конструктора класса Node
Node::Node(const MyData data, const Node* next) {
    this->data = data;
    this->next = const_cast<Node*>(next);
}

class List {
private:
    Node* head; // Указатель на первый узел списка
public:
    List() {
        head = nullptr;
    }

    ~List() {
        clear();
    }

public:
    void add_head(const MyData value);
    void del_head();
    Node* get_head();
    void clear();
    void add_next(Node* node, const MyData value);
    void del_next(Node* node);
};

// Добавление элемента в начало списка
void List::add_head(const MyData value) {
    head = new Node(value, head);
}

// Удаление первого элемента списка
void List::del_head() {
    if (head == nullptr) {
        return;
    }

    Node* temp = head;
    head = head->next;
    delete temp;
}

// Получение указателя на первый элемент списка
Node* List::get_head() {
    return head;
}

// Удаление всех элементов списка
void List::clear() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

// Добавление узла
void List::add_next(Node* node, const MyData value) {
    if (node == nullptr) {
        return;
    }

    node->next = new Node(value, node->next);
}

// Удаление узла
void List::del_next(Node* node) {
    if (node == nullptr || node->next == nullptr) {
        return;
    }

    Node* temp = node->next;
    node->next = temp->next;
    delete temp;
}

int main() {
    // Пример использования класса List
    List list;
    list.add_head(1.0);
    list.add_head(2.0);
    list.add_head(3.0);
    list.del_next(list.get_head());
    list.clear();
    return 0;
}
