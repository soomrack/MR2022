template<typename T>
class Node {
private:
    Node *next;
public:
    T data;

    Node(T data) : data(data), next(nullptr) {}
    ~Node() = default;

    Node *get_next() { return next; }
    void set_next(Node *new_next) { next = new_next; }
    void push_next(T item);
    void delete_next();
};

template<typename T>
void Node<T>::push_next(T item) {
    Node *temp = new Node(item);
    if (next == nullptr) {
        next = temp;
    } else {
        Node *temp2 = next;
        temp->next = temp2;
        next = temp;
    }
}

template<typename T>
void Node<T>::delete_next() {
    if (next == nullptr) throw std::runtime_error("Next node doesn't exist!");

    Node *temp = next;
    if (temp->next == nullptr) {
        next = nullptr;
    } else {
        Node *temp2 = temp->next;
        next = temp2;
    }

    delete temp;
}

template<typename T>
class LinkedList {

private:
    unsigned int size;

public:
    Node<T> *head;

    LinkedList() : head(nullptr), size(0) {}
    ~LinkedList() { clear(); }

    void push_head(T data);
    Node<T> *pop_head();
    int get_size() const { return size; }
    bool is_empty() const { return size == 0; }
    void clear();
    Node<T> *get_head() { return head; }
    void push_next(T data, unsigned int index);
    void delete_next(unsigned int index);
};

template<typename T>
void LinkedList<T>::push_head(T data) {
    Node<T> *temp = new Node<T>(data);
    if (head == nullptr) {
        head = temp;
    } else {
        temp->set_next(head);
        head = temp;
    }
    size++;
}

template<typename T>
Node<T> *LinkedList<T>::pop_head() {
    if (head == nullptr) throw std::underflow_error("List is empty!");

    Node<T> *temp = head;
    if (head->get_next() == nullptr) {
        head = nullptr;
    } else {
        head = head->get_next();
    }
    size--;
    return temp;
}

template<typename T>
void LinkedList<T>::clear() {
    while (head != nullptr) {
        Node<T> *temp = head;
        head = head->get_next();
        delete temp;
    }
    size = 0;
}

template<typename T>
void LinkedList<T>::push_next(T data, unsigned int index) {
    if (index >= size) throw std::out_of_range("Invalid index!");

    Node<T> *temp = head;
    for (int i = 0; i < index; ++i) {
        temp = temp->get_next();
    }
    size++;
    temp->push_next(data);
}

template<typename T>
void LinkedList<T>::delete_next(unsigned int index) {
    if (index >= size) throw std::out_of_range("Invalid index!");

    Node<T> *temp = head;
    for (int i = 0; i < index; ++i) {
        temp = temp->get_next();
    }

    size--;
    temp->delete_next();
}