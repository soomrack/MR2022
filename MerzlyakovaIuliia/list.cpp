#include <iostream>

class linked_list_exception: public std::exception {
private:
    const char* message;
public:
    linked_list_exception(const char* const msg) : message(msg) {}
    const char* what() const noexcept override {
        return message;
    }
};

linked_list_exception invalid_index("Invalid index");

template <typename T>
class linked_list {
public:
    linked_list() = default;
    ~linked_list();

    void push_back(const T& value);
    void push_front(const T& value);
    void insert(size_t index, const T& value);
    void del(size_t index);
    T get(size_t index);

    void print_list();

private:
    struct Node {
        explicit Node(const T& value);
        ~Node();
        T value;
        Node* next;
        Node* prev;
    };

    Node* traverse(size_t index);
    Node* head;
};

template<typename T>
linked_list<T>::Node::Node(const T& value): value(value), next(nullptr), prev(nullptr) { }

template<typename T>
linked_list<T>::Node::~Node() {
    delete next;
}

template<typename T>
linked_list<T>::~linked_list() {
    delete head;
}

template<typename T>
typename linked_list<T>::Node* linked_list<T>::traverse(size_t index) {
    Node* cur = head;
    while (index-- > 0) {
        if (cur == nullptr)
            throw invalid_index;
        cur = cur->next;
    }
    if (cur == nullptr)
        throw invalid_index;
    return cur;
}

template<typename T>
void linked_list<T>::push_back(const T &value) {
    if (head == nullptr) {
        head = new Node(value);
        return;
    }

    Node* tail = head;
    while (tail->next != nullptr) {
        tail = tail->next;
    }

    tail->next = new Node(value);
    tail->next->prev = tail;
}

template<typename T>
void linked_list<T>::push_front(const T &value) {
    if (head == nullptr) {
        head = new Node(value);
        return;
    }

    head->prev = new Node(value);
    head->prev->next = head;
    head = head->prev;
}

template<typename T>
void linked_list<T>::insert(size_t index, const T &value) {
    if (index == 0) {
        if (head == nullptr) {
            head = new Node(value);
            return;
        }
        Node* new_node = new Node(value);
        new_node->next = head;
        head = new_node;
        return;
    }

    Node* insert_place = traverse(index - 1);
    Node* new_node = new Node(value);
    new_node->prev = insert_place;
    new_node->next = insert_place->next;
    if (insert_place->next != nullptr) {
        insert_place->next->prev = new_node;
    }
    insert_place->next = new_node;
}

template<typename T>
void linked_list<T>::del(size_t index) {
    if (index == 0) {
        if (head == nullptr)
            throw invalid_index;
        Node* tmp = head;
        head = head->next;
        tmp->next = nullptr;
        delete tmp;
        return;
    }

    Node* del_node = traverse(index);
    if (del_node->prev != nullptr) {
        del_node->prev->next = del_node->next;
    }
    if (del_node->next != nullptr) {
        del_node->next->prev = del_node->prev;
    }
    del_node->prev = del_node->next = nullptr;
    delete del_node;
}

template<typename T>
T linked_list<T>::get(size_t index) {
    return traverse(index)->value;
}

template<typename T>
void linked_list<T>::print_list() {
    Node* cur = head;
    while (cur != nullptr) {
        std::cout << cur->value << " ";
        cur = cur->next;
    }
    std::cout << std::endl;
}

int main() {
    linked_list<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_front(0);
    l.insert(1, 1);
    l.print_list();

    l.del(1);
    l.del(2);
    l.print_list();

    l.del(0);
    l.print_list();
    l.del(0);
    l.print_list();

    l.push_back(1);
    l.insert(0, 0);
    l.insert(1, 2);
    l.print_list();

    std::cout << l.get(1) << std::endl;
    return 0;
}
