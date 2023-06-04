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

linked_list_exception empty_list("empty list");
linked_list_exception node_does_not_exist("node does not exist");

template <typename T>
class linked_list {
public:
    class Node {
    public:
        explicit Node(const T& value);
        ~Node();

        Node* get_next();
        Node* add_next(const T& value);
        void delete_next();

    private:
        T value;
        Node* next;

        // добавляем friend, чтобы из методов листа были доступны поля Node
        friend class linked_list<T>;
    };

    linked_list() = default;
    ~linked_list();

    Node* add_head(const T& value);
    Node* get_head();
    void delete_head();

    void print_list();

private:
    Node* head;
};

template<typename T>
linked_list<T>::Node::Node(const T& value): value(value), next(nullptr) { }

template<typename T>
linked_list<T>::Node::~Node() {
    // вызываем деструктор у следующей Node, таким образом удаляя весь хвост списка начиная с этой Node
    delete next;
}

template<typename T>
typename linked_list<T>::Node* linked_list<T>::Node::add_next(const T& value) {
    Node* new_node = new Node(value);
    new_node->next = next;
    next = new_node;
    return new_node;
}

template<typename T>
void linked_list<T>::Node::delete_next() {
    if (next == nullptr)
        throw node_does_not_exist;

    Node* new_next = next->next;

    // зануляем next->next чтобы деструктор Node не удалил весь хвост списка
    next->next = nullptr;
    delete next;
    next = new_next;
}

template<typename T>
typename linked_list<T>::Node* linked_list<T>::Node::get_next() {
    return next;
}

template<typename T>
linked_list<T>::~linked_list() {
    delete head;
}

template<typename T>
typename linked_list<T>::Node *linked_list<T>::get_head() {
    return head;
}

template<typename T>
typename linked_list<T>::Node* linked_list<T>::add_head(const T &value) {
    Node* new_head = new Node(value);
    new_head->next = head;
    head = new_head;
    return head;
}

template<typename T>
void linked_list<T>::delete_head() {
    if (head == nullptr)
        throw empty_list;

    Node* delete_node = head;
    head = head->next;
    delete_node->next = nullptr;
    delete delete_node;
}

template<typename T>
void linked_list<T>::print_list() {
    Node* cur = head;
    while (cur != nullptr) {
        std::cout << cur->value << " ";
        cur = cur->get_next();
    }
    std::cout << std::endl;
}

int main() {
    linked_list<int> l;
    l.add_head(0);
    auto head = l.get_head();
    head->add_next(1);
    head->get_next()->add_next(2);
    l.add_head(-1);

    l.print_list();

    l.delete_head();
    l.get_head()->delete_next();

    l.print_list();
    return 0;
}
